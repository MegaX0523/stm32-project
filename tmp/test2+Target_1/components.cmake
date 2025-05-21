# components.cmake

# component ARM::CMSIS:CORE@6.1.0
add_library(ARM_CMSIS_CORE_6_1_0 INTERFACE)
target_include_directories(ARM_CMSIS_CORE_6_1_0 INTERFACE
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  ${CMSIS_PACK_ROOT}/ARM/CMSIS/6.1.0/CMSIS/Core/Include
)
target_compile_definitions(ARM_CMSIS_CORE_6_1_0 INTERFACE
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_link_libraries(ARM_CMSIS_CORE_6_1_0 INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)

# component ARM::CMSIS:OS Tick:SysTick@1.0.5
add_library(ARM_CMSIS_OS_Tick_SysTick_1_0_5 OBJECT
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/6.1.0/CMSIS/RTOS2/Source/os_systick.c"
)
target_include_directories(ARM_CMSIS_OS_Tick_SysTick_1_0_5 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  ${CMSIS_PACK_ROOT}/ARM/CMSIS/6.1.0/CMSIS/RTOS2/Include
)
target_compile_definitions(ARM_CMSIS_OS_Tick_SysTick_1_0_5 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(ARM_CMSIS_OS_Tick_SysTick_1_0_5 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(ARM_CMSIS_OS_Tick_SysTick_1_0_5 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component Keil::Device:Startup@1.0.0
add_library(Keil_Device_Startup_1_0_0 OBJECT
  "${SOLUTION_ROOT}/RTE/Device/STM32F103C8/startup_stm32f10x_md.s"
  "${SOLUTION_ROOT}/RTE/Device/STM32F103C8/system_stm32f10x.c"
)
target_include_directories(Keil_Device_Startup_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  ${SOLUTION_ROOT}/RTE/Device/STM32F103C8
  ${CMSIS_PACK_ROOT}/Keil/STM32F1xx_DFP/2.4.1/Device/Include
)
target_compile_definitions(Keil_Device_Startup_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Device_Startup_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Keil_Device_Startup_1_0_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)
set(COMPILE_DEFINITIONS
  STM32F10X_MD
  _RTE_
)
cbuild_set_defines(AS_ARM COMPILE_DEFINITIONS)
set_source_files_properties("${CMSIS_PACK_ROOT}/Keil/STM32F1xx_DFP/2.4.1/Device/Source/ARM/STM32F1xx_OPT.s" PROPERTIES
  COMPILE_FLAGS "${COMPILE_DEFINITIONS}"
)
set(COMPILE_DEFINITIONS
  STM32F10X_MD
  _RTE_
)
cbuild_set_defines(AS_ARM COMPILE_DEFINITIONS)
set_source_files_properties("${SOLUTION_ROOT}/RTE/Device/STM32F103C8/startup_stm32f10x_md.s" PROPERTIES
  COMPILE_FLAGS "${COMPILE_DEFINITIONS}"
)

# component Keil::Device:StdPeriph Drivers:ADC@3.6.0
add_library(Keil_Device_StdPeriph_Drivers_ADC_3_6_0 OBJECT
  "${CMSIS_PACK_ROOT}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/src/stm32f10x_adc.c"
)
target_include_directories(Keil_Device_StdPeriph_Drivers_ADC_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  ${CMSIS_PACK_ROOT}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/inc
)
target_compile_definitions(Keil_Device_StdPeriph_Drivers_ADC_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Device_StdPeriph_Drivers_ADC_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Keil_Device_StdPeriph_Drivers_ADC_3_6_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component Keil::Device:StdPeriph Drivers:DMA@3.6.0
add_library(Keil_Device_StdPeriph_Drivers_DMA_3_6_0 OBJECT
  "${CMSIS_PACK_ROOT}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/src/stm32f10x_dma.c"
)
target_include_directories(Keil_Device_StdPeriph_Drivers_DMA_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  ${CMSIS_PACK_ROOT}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/inc
)
target_compile_definitions(Keil_Device_StdPeriph_Drivers_DMA_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Device_StdPeriph_Drivers_DMA_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Keil_Device_StdPeriph_Drivers_DMA_3_6_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component Keil::Device:StdPeriph Drivers:EXTI@3.6.0
add_library(Keil_Device_StdPeriph_Drivers_EXTI_3_6_0 OBJECT
  "${CMSIS_PACK_ROOT}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/src/stm32f10x_exti.c"
)
target_include_directories(Keil_Device_StdPeriph_Drivers_EXTI_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  ${CMSIS_PACK_ROOT}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/inc
)
target_compile_definitions(Keil_Device_StdPeriph_Drivers_EXTI_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Device_StdPeriph_Drivers_EXTI_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Keil_Device_StdPeriph_Drivers_EXTI_3_6_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component Keil::Device:StdPeriph Drivers:Framework@3.6.0
add_library(Keil_Device_StdPeriph_Drivers_Framework_3_6_0 OBJECT
  "${SOLUTION_ROOT}/RTE/Device/STM32F103C8/stm32f10x_conf.h"
  "${CMSIS_PACK_ROOT}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/src/misc.c"
)
target_include_directories(Keil_Device_StdPeriph_Drivers_Framework_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  ${CMSIS_PACK_ROOT}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/inc
)
target_compile_definitions(Keil_Device_StdPeriph_Drivers_Framework_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Device_StdPeriph_Drivers_Framework_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Keil_Device_StdPeriph_Drivers_Framework_3_6_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component Keil::Device:StdPeriph Drivers:GPIO@3.6.0
add_library(Keil_Device_StdPeriph_Drivers_GPIO_3_6_0 OBJECT
  "${CMSIS_PACK_ROOT}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/src/stm32f10x_gpio.c"
)
target_include_directories(Keil_Device_StdPeriph_Drivers_GPIO_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  ${CMSIS_PACK_ROOT}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/inc
)
target_compile_definitions(Keil_Device_StdPeriph_Drivers_GPIO_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Device_StdPeriph_Drivers_GPIO_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Keil_Device_StdPeriph_Drivers_GPIO_3_6_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component Keil::Device:StdPeriph Drivers:I2C@3.6.0
add_library(Keil_Device_StdPeriph_Drivers_I2C_3_6_0 OBJECT
  "${CMSIS_PACK_ROOT}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/src/stm32f10x_i2c.c"
)
target_include_directories(Keil_Device_StdPeriph_Drivers_I2C_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  ${CMSIS_PACK_ROOT}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/inc
)
target_compile_definitions(Keil_Device_StdPeriph_Drivers_I2C_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Device_StdPeriph_Drivers_I2C_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Keil_Device_StdPeriph_Drivers_I2C_3_6_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component Keil::Device:StdPeriph Drivers:RCC@3.6.0
add_library(Keil_Device_StdPeriph_Drivers_RCC_3_6_0 OBJECT
  "${CMSIS_PACK_ROOT}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/src/stm32f10x_rcc.c"
)
target_include_directories(Keil_Device_StdPeriph_Drivers_RCC_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  ${CMSIS_PACK_ROOT}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/inc
)
target_compile_definitions(Keil_Device_StdPeriph_Drivers_RCC_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Device_StdPeriph_Drivers_RCC_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Keil_Device_StdPeriph_Drivers_RCC_3_6_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component Keil::Device:StdPeriph Drivers:SPI@3.6.0
add_library(Keil_Device_StdPeriph_Drivers_SPI_3_6_0 OBJECT
  "${CMSIS_PACK_ROOT}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/src/stm32f10x_spi.c"
)
target_include_directories(Keil_Device_StdPeriph_Drivers_SPI_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  ${CMSIS_PACK_ROOT}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/inc
)
target_compile_definitions(Keil_Device_StdPeriph_Drivers_SPI_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Device_StdPeriph_Drivers_SPI_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Keil_Device_StdPeriph_Drivers_SPI_3_6_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component Keil::Device:StdPeriph Drivers:TIM@3.6.0
add_library(Keil_Device_StdPeriph_Drivers_TIM_3_6_0 OBJECT
  "${CMSIS_PACK_ROOT}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/src/stm32f10x_tim.c"
)
target_include_directories(Keil_Device_StdPeriph_Drivers_TIM_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  ${CMSIS_PACK_ROOT}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/inc
)
target_compile_definitions(Keil_Device_StdPeriph_Drivers_TIM_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Device_StdPeriph_Drivers_TIM_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Keil_Device_StdPeriph_Drivers_TIM_3_6_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component Keil::Device:StdPeriph Drivers:USART@3.6.0
add_library(Keil_Device_StdPeriph_Drivers_USART_3_6_0 OBJECT
  "${CMSIS_PACK_ROOT}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/src/stm32f10x_usart.c"
)
target_include_directories(Keil_Device_StdPeriph_Drivers_USART_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  ${CMSIS_PACK_ROOT}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/inc
)
target_compile_definitions(Keil_Device_StdPeriph_Drivers_USART_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Keil_Device_StdPeriph_Drivers_USART_3_6_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Keil_Device_StdPeriph_Drivers_USART_3_6_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)
