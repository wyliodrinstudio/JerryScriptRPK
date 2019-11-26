/*
 * Copyright (c) 2014 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!=================================================================================================
 \file       app_init.c
 \brief      This is a public source file for the initial system startup module. It contains
 the implementation of the interface functions.
 ==================================================================================================*/

/*==================================================================================================
Include Files
==================================================================================================*/
#include <stdio.h>
#include "fsl_device_registers.h"
#include "fsl_os_abstraction.h"
#include "fsl_sysmpu.h"
#include "fsl_port.h"
#include "pin_mux.h"
#include "board.h"

/* FSL Framework */
#include "rgb_led.h"
#include "TimersManager.h"
#include "SerialManager.h"
#include "Panic.h"
#include "sensors.h"
#include "Reset.h"

#ifdef FRDM_K64F_KW41Z
    #include "FsciInterface.h"
    #include "cmd_threadip.h"
    #include "cmd_ble.h"
    #include "shell.h"
    #include "ble_shell.h"
#endif

/* Display */
#include "BUTTON.h"
#include "CHECKBOX.h"
#include "DROPDOWN.h"
#include "GUI.h"
#include "MULTIPAGE.h"
#include "RADIO.h"
#include "SLIDER.h"
#include "emwin_support.h"

/* Graphics */
#include "NXP_logo.h"
#include "test_img.h"
#include "img_bmp_callbacks.h"

/* User Interface */
#include "ui_manager.h"

/* Port Interrupts */
#include "port_interrupts.h"

/* Flash */
#include "img_program_ext.h"
#include "spi_bus_share.h"

/* JerryScript */
#include "library.h"
#include "source.h"

/* JerryScript extern variables */
extern char* src;
extern int rpkBLEInitialized;

void *ioBase;


/*==================================================================================================
 Pivate Macros
 ==================================================================================================*/
/* FSCI utility Confirmations/Indications */
#define gFSCI_CnfOpcodeGroup_c                  0xA4
/* FSCI operation group for GATT Database (application) */
#define gFsciBleL2capOpcodeGroup_c              0x41
/* FSCI operation group for GATT */
#define gFsciBleGattOpcodeGroup_c               0x44
/* FSCI operation group for GATT Database (application) */
#define gFsciBleGattDbAppOpcodeGroup_c          0x45
/* FSCI operation group for GAP */
#define gFsciBleGapOpcodeGroup_c                0x47


/*==================================================================================================
 Private variables
 ==================================================================================================*/
/* Reset MCU timestamp <microseconds> */
static uint64_t gSwResetTimestamp = 0;

/* FSCI Interface Configuration structure */
static const gFsciSerialConfig_t mFsciSerials[] =
{
    {
        .baudrate = gUARTBaudRate38400_c,
        .interfaceType = gSerialMgrUart_c,
        .interfaceChannel = 4,
        .virtualInterface = 0

    },
#if gHybridApp_d
    {
        .baudrate = gUARTBaudRate38400_c,
        .interfaceType = gSerialMgrUart_c,
        .interfaceChannel = 4,
        .virtualInterface = 1

    }
#endif
};


/*==================================================================================================
 Public variables
 ==================================================================================================*/
osaSemaphoreId_t gOtaSem;


/*==================================================================================================
 Private prototypes
 ==================================================================================================*/
static void APP_InitDisplay();
static void APP_HandleMcuResetOnIdle(void);
static void APP_FSCIRegisterBle(uint32_t fsciInterfaceId);
static void APP_FSCIRxCbBle(void *pData, void *param, uint32_t interfaceId);


void main_task(uint32_t param)
{
    static uint8_t mainInitialized = FALSE;

    if (!mainInitialized)
    {
        mainInitialized = TRUE;

        /* Initialize memory blocks manager */
        MEM_Init();

        /* Initialize  timers module */
        TMR_Init();
        TMR_TimeStampInit();

        RGB_Led_Set_State(3,1);
        App_WaitMsec(1000);
        RGB_Led_Set_State(3,2);
        App_WaitMsec(1000);
        RGB_Led_Set_State(0,3);

        /* Initialize shell for debug */
        shell_init("$ ");

        /* Initialize FSCI (on two virtual interfaces if hybrid mode is on) */
        FSCI_Init((void *)&mFsciSerials);
    }

    APP_FSCIRegisterBle(1);

    /* Initialize all sensors */
    //Init_all_sensors();

    /* Create semaphore to disable (lock) UI manager while running OTA */
    gOtaSem = OSA_SemaphoreCreate(0U);

    if (NULL == gOtaSem)
    {
        panic(0,0,0,0);
    }

    //APP_InitDisplay();
    I2C1_init();
	I2C2_init();

    PORT_IRQ_EnablePortAIrq();
    PORT_IRQ_EnablePortBIrq();
    PORT_IRQ_EnablePortCIrq();
    PORT_IRQ_EnablePortDIrq();
    PORT_IRQ_EnablePortEIrq();

    BleApp_DemoRpk();

    ioBase = USB_VcomInit();

	jerry_setup ();
	jerry_execute(SOURCE_MAIN);
	jerry_unsetup ();
}


/*==================================================================================================
 Private functions
 ==================================================================================================*/

/*!*************************************************************************************************
 \fn            APP_InitDisplay
 \brief         Initialize the Display with black background and white fond
 \return        None
 ***************************************************************************************************/
static void APP_InitDisplay()
{
    /* Triggers GUI_Init() */
    Display_Connect();
    Backlight_SetLevel(BLIGHT_LEVEL_HIGH);
    GUI_SetBkColor(GUI_BLACK);
    GUI_SetColor(GUI_WHITE);
}


/*!*************************************************************************************************
 \fn            APP_FSCIRegisterBle
 \brief         Register the handler for callback for an interface
 \param [in]    fsciInterfaceId ID of the interface 0-THREAD, 1-BLE
 \return        None
 ***************************************************************************************************/
static void APP_FSCIRegisterBle(uint32_t fsciInterfaceId)
{
    /* Register Generic FSCI */
    if (FSCI_RegisterOpGroup(gFSCI_CnfOpcodeGroup_c,
                             gFsciMonitorMode_c,
                             APP_FSCIRxCbBle,
                             NULL,
                             fsciInterfaceId) != gFsciSuccess_c)
    {
        panic(0, (uint32_t)APP_FSCIRegisterBle, 0, 0);
    }

    /* Register L2CAP command handler */
    if (FSCI_RegisterOpGroup(gFsciBleL2capOpcodeGroup_c,
                             gFsciMonitorMode_c,
                             APP_FSCIRxCbBle,
                             NULL,
                             fsciInterfaceId) != gFsciSuccess_c)
    {
        panic(0, (uint32_t)APP_FSCIRegisterBle, 0, 0);
    }

    /* Register GATT command handler */
    if (FSCI_RegisterOpGroup(gFsciBleGattOpcodeGroup_c,
                             gFsciMonitorMode_c,
                             APP_FSCIRxCbBle,
                             NULL,
                             fsciInterfaceId) != gFsciSuccess_c)
    {
        panic(0, (uint32_t)APP_FSCIRegisterBle, 0, 0);
    }

    /* Register GATT Database (application) command handler */
    if (FSCI_RegisterOpGroup(gFsciBleGattDbAppOpcodeGroup_c,
                             gFsciMonitorMode_c,
                             APP_FSCIRxCbBle,
                             NULL,
                             fsciInterfaceId) != gFsciSuccess_c)
    {
        panic(0, (uint32_t)APP_FSCIRegisterBle, 0, 0);
    }

    /* Register GAP command handler */
    if (FSCI_RegisterOpGroup(gFsciBleGapOpcodeGroup_c,
                             gFsciMonitorMode_c,
                             APP_FSCIRxCbBle,
                             NULL,
                             fsciInterfaceId) != gFsciSuccess_c)
    {
        panic(0, (uint32_t)APP_FSCIRegisterBle, 0, 0);
    }
}


/*!*************************************************************************************************
 \fn            APP_FSCIRxCbBle
 \brief         Handler for data from FSCI
 \param [in]    pData data to be processed
 \param [in]    param none
 \param [in]    interfaceId 0-THREAD, 1-BLE
 \return        None
 ***************************************************************************************************/
static void APP_FSCIRxCbBle(void *pData, void *param, uint32_t interfaceId)
{
#if gHybridApp_d
    bleEvtContainer_t container; /* this could be allocated instead */
    KHC_BLE_RX_MsgHandler(pData, &container, interfaceId);
    SHELL_BleEventNotify(&container);
#endif
}


/*!*************************************************************************************************
 \fn            APP_HandleMcuResetOnIdle
 \brief         Reset the MCU on idle
 \return        None
 ***************************************************************************************************/
static void APP_HandleMcuResetOnIdle(void)
{
    if ((gSwResetTimestamp) && (gSwResetTimestamp < TMR_GetTimestamp()))
    {
        gSwResetTimestamp = 0;
        /* Disable interrupts */
        OSA_InterruptDisable();

        ResetMCU();
        /* Enable interrupts */
        OSA_InterruptEnable();
    }
}
