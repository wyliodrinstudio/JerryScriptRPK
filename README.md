# JerryScriptRPK

To compile you need the official NXP RPK SDK and MCUXpresso IDE (we used v11.0.0 [Build 2516] [2019-06-05])

Aditional compile instruction:
	-> Go to C/C++ Build -> Settings (Right click on the project, select properties):
		1. MCU C Compuler:
		   	1.1 Options:
				"-std=gnu99 -DCPU_MK64FN1M0VMD12 -DJERRY_VM_EXEC_STOP -DJERRY_GLOBAL_HEAP_SIZE=64 -DDISABLE_EXTRA_API -DCPU_MK64FN1M0VMD12_cm4 -DFRDM_K64F_KW41Z=1 -DFREEDOM -DSDK_OS_FREE_RTOS -DRPK_SDK_V2p5 -DRAPID_IOT -DENABLE_RAM_VECTOR_TABLE=1 -D__TARGET_FPU_VFP -DNDEBUG -DUSE_RTOS=1 -DFRDM_K64F -DSHELL_USE_PRINTF -DFSL_RTOS_FREE_RTOS -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -D__REDLIB__ -I../board -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/osa" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/usb" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/usb/device" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/usb/device/include" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/usb/device/source" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/usb/device/source/khci" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/usb/include" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/jerry" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/jerry/api" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/jerry/ecma" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/jerry/ecma/base" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/jerry/ecma/builtin-objects" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/jerry/ecma/builtin-objects/typedarray" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/jerry/ecma/operations" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/jerry/include" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/jerry/jcontext" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/jerry/jmem" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/jerry/jrt" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/jerry/lit" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/jerry/parser" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/jerry/parser/js" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/jerry/parser/regexp" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/jerry/port" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/jerry/profiles" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/jerry/vm" -I"/home/skyplane23/Documents/MCUXpresso_11.0.0_2516/workspace/v4_weather_station/source/library" -I../source -I../ -I../middleware/OSA/Interface -I../drivers -I../device -I../CMSIS -I../middleware/TimersManager/Interface -I../component/crc -I../utilities -I../middleware/FSCI/Interface -I../middleware/FSCI/Source -I../middleware/KinetisHost/Interface -I../middleware/Config -I../middleware/UIManager/Interface -I../middleware/Pictures/Interface -I../middleware/App_update/Interface -I../amazon-freertos/include -I../amazon-freertos/FreeRTOS/portable -I../middleware/Bluetooth/Interface -I../CMSIS_driver -I../component/serial_manager -I../touchpanel -I../component/sensors -I../component/a1006 -I../component/battery -I../component/ccs811 -I../component/ens210 -I../component/fxas21002 -I../component/fxos8700 -I../component/ili9341 -I../component/microseconds -I../component/mpl3115 -I../component/pcf2123 -I../component/rgb_led -I../component/sx9500 -I../component/systick -I../component/tsl2572 -I../component/uart -I../emwin/emWin_header -I../emwin/emWin_Config -I../gpio_driver -I../interfaces -I../middleware/Common/Interface -I../middleware/ModuleInfo/Interface -I../middleware/Messaging/Interface -I../middleware/Lists/Interface -I../middleware/MemManager/Interface -I../middleware/FunctionLib/Interface -I../middleware/Panic/Interface -I../middleware/GPIO/Interface -I../middleware/Reset/Interface -I../middleware/Shell/Interface -I../middleware/SerialManager/Interface -I../middleware/SerialManager/Source/SPI_Adapter -Os -fno-common -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -imacros '../middleware/Config/config.h' -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs"

			1.2 Preprocessor:
				CPU_MK64FN1M0VMD12
				JERRY_VM_EXEC_STOP
				JERRY_GLOBAL_HEAP_SIZE=64
				DISABLE_EXTRA_API
				CPU_MK64FN1M0VMD12_cm4
				FRDM_K64F_KW41Z=1
				FREEDOM
				SDK_OS_FREE_RTOS
				RPK_SDK_V2p5
				RAPID_IOT
				ENABLE_RAM_VECTOR_TABLE=1
				__TARGET_FPU_VFP
				NDEBUG
				USE_RTOS=1
				FRDM_K64F
				SHELL_USE_PRINTF
				FSL_RTOS_FREE_RTOS
				SDK_DEBUGCONSOLE=0
				CR_INTEGER_PRINTF
				PRINTF_FLOAT_ENABLE=0
				__MCUXPRESSO
				__USE_CMSIS
				__REDLIB__

			1.3 Includes:
				../board
				"${workspace_loc:/${ProjName}/source/osa}"
				"${workspace_loc:/${ProjName}/source/usb}"
				"${workspace_loc:/${ProjName}/source/usb/device}"
				"${workspace_loc:/${ProjName}/source/usb/device/include}"
				"${workspace_loc:/${ProjName}/source/usb/device/source}"
				"${workspace_loc:/${ProjName}/source/usb/device/source/khci}"
				"${workspace_loc:/${ProjName}/source/usb/include}"
				"${workspace_loc:/${ProjName}/source}"
				"${workspace_loc:/${ProjName}/source/jerry}"
				"${workspace_loc:/${ProjName}/source/jerry/api}"
				"${workspace_loc:/${ProjName}/source/jerry/ecma}"
				"${workspace_loc:/${ProjName}/source/jerry/ecma/base}"
				"${workspace_loc:/${ProjName}/source/jerry/ecma/builtin-objects}"
				"${workspace_loc:/${ProjName}/source/jerry/ecma/builtin-objects/typedarray}"
				"${workspace_loc:/${ProjName}/source/jerry/ecma/operations}"
				"${workspace_loc:/${ProjName}/source/jerry/include}"
				"${workspace_loc:/${ProjName}/source/jerry/jcontext}"
				"${workspace_loc:/${ProjName}/source/jerry/jmem}"
				"${workspace_loc:/${ProjName}/source/jerry/jrt}"
				"${workspace_loc:/${ProjName}/source/jerry/lit}"
				"${workspace_loc:/${ProjName}/source/jerry/parser}"
				"${workspace_loc:/${ProjName}/source/jerry/parser/js}"
				"${workspace_loc:/${ProjName}/source/jerry/parser/regexp}"
				"${workspace_loc:/${ProjName}/source/jerry/port}"
				"${workspace_loc:/${ProjName}/source/jerry/profiles}"
				"${workspace_loc:/${ProjName}/source/jerry/vm}"
				"${workspace_loc:/${ProjName}/source/library}"
				../source
				../
				../middleware/OSA/Interface
				../drivers
				../device
				../CMSIS
				../middleware/TimersManager/Interface
				../component/crc
				../utilities
				../middleware/FSCI/Interface
				../middleware/FSCI/Source
				../middleware/KinetisHost/Interface
				../middleware/Config
				../middleware/UIManager/Interface
				../middleware/Pictures/Interface
				../middleware/App_update/Interface
				../amazon-freertos/include
				../amazon-freertos/FreeRTOS/portable
				../middleware/Bluetooth/Interface
				../CMSIS_driver
				../component/serial_manager
				../touchpanel
				../component/sensors
				../component/a1006
				../component/battery
				../component/ccs811
				../component/ens210
				../component/fxas21002
				../component/fxos8700
				../component/ili9341
				../component/microseconds
				../component/mpl3115
				../component/pcf2123
				../component/rgb_led
				../component/sx9500
				../component/systick
				../component/tsl2572
				../component/uart
				../emwin/emWin_header
				../emwin/emWin_Config
				../gpio_driver
				../interfaces
				../middleware/Common/Interface
				../middleware/ModuleInfo/Interface
				../middleware/Messaging/Interface
				../middleware/Lists/Interface
				../middleware/MemManager/Interface
				../middleware/FunctionLib/Interface
				../middleware/Panic/Interface
				../middleware/GPIO/Interface
				../middleware/Reset/Interface
				../middleware/Shell/Interface
				../middleware/SerialManager/Interface
				../middleware/SerialManager/Source/SPI_Adapter

			1.4 Miscellaneous:
				->Set Library headers to Newlib(Auto)

		2 MCU Assembler
			2.1 All options:
				"-c -x assembler-with-cpp -D__REDLIB__ -I../board -I../source -I../ -I../middleware/OSA/Interface -I../drivers -I../device -I../CMSIS -I../middleware/TimersManager/Interface -I../component/crc -I../utilities -I../middleware/FSCI/Interface -I../middleware/FSCI/Source -I../middleware/KinetisHost/Interface -I../middleware/Config -I../middleware/UIManager/Interface -I../middleware/Pictures/Interface -I../middleware/App_update/Interface -I../amazon-freertos/include -I../amazon-freertos/FreeRTOS/portable -I../middleware/Bluetooth/Interface -I../CMSIS_driver -I../component/serial_manager -I../touchpanel -I../component/sensors -I../component/a1006 -I../component/battery -I../component/ccs811 -I../component/ens210 -I../component/fxas21002 -I../component/fxos8700 -I../component/ili9341 -I../component/microseconds -I../component/mpl3115 -I../component/pcf2123 -I../component/rgb_led -I../component/sx9500 -I../component/systick -I../component/tsl2572 -I../component/uart -I../emwin/emWin_header -I../emwin/emWin_Config -I../gpio_driver -I../interfaces -I../middleware/Common/Interface -I../middleware/ModuleInfo/Interface -I../middleware/Messaging/Interface -I../middleware/Lists/Interface -I../middleware/MemManager/Interface -I../middleware/FunctionLib/Interface -I../middleware/Panic/Interface -I../middleware/GPIO/Interface -I../middleware/Reset/Interface -I../middleware/Shell/Interface -I../middleware/SerialManager/Interface -I../middleware/SerialManager/Source/SPI_Adapter -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs"

		3 MCU Linker
			3.1 General
				-> Uncheck "No startup or default libs (-nostdlib)"
