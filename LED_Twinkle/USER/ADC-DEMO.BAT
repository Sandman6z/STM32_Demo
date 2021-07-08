SET PATH=C:\Program Files\Keil_v5\ARM\ARMCC\Bin;C:\Program Files\Python39\Scripts\;C:\Program Files\Python39\;D:\VMware\bin\;C:\ProgramData\Oracle\Java\javapath;C:\Program Files\Common Files\Oracle\Java\javapath;C:\Mingw64\bin;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility;C:\Program Files\eclipse;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files\dotnet\;C:\Program Files\Microsoft SQL Server\Client SDK\ODBC\170\Tools\Binn\;C:\Program Files\Microsoft VS Code\bin;C:\Program Files\CMake\bin;C:\Program Files\MATLAB\R2016b\runtime\win64;C:\Program Files\MATLAB\R2016b\bin;C:\Program Files\MATLAB\R2016b\polyspace\bin;C:\Users\zbn02\AppData\Roaming\Python\Python39\Scripts;C:\Program Files\Git\cmd;C:\Program Files\PuTTY\;C:\Program Files (x86)\dotnet\;C:\Program Files (x86)\MAVProxy;C:\Program Files (x86)\GNU Tools ARM Embedded\6 2017-q2-update\bin;C:\Program Files\JetBrains\PyCharm 2020.2.2\bin;;C:\Users\zbn02\AppData\Local\Microsoft\WindowsApps;C:\Users\zbn02\.dotnet\tools
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=ADC-DEMO
SET CPU_CLOCK=0x00B71B00
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\startup_stm32f10x_hd._ia"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\main.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_it.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\usart1.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\adc.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\led.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\time_test.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\key.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\exti.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_gpio.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_rcc.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_usart.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_adc.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_dma.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_flash.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_rtc.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\misc.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_tim.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_exti.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\core_cm3.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\system_stm32f10x.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\STM32-DEMO.lnp"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\STM32-DEMO.axf" --i32combined --output ".\STM32-DEMO.hex"
