# groups.cmake

# group App
add_library(Group_App OBJECT
  "${SOLUTION_ROOT}/App/main.c"
  "${SOLUTION_ROOT}/App/OLEDShow.c"
)
target_include_directories(Group_App PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  ${SOLUTION_ROOT}/App
)
target_compile_definitions(Group_App PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_App_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_App_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_App PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_App PUBLIC
  Group_App_ABSTRACTIONS
)

# group System
add_library(Group_System OBJECT
  "${SOLUTION_ROOT}/System/Delay.c"
  "${SOLUTION_ROOT}/System/Interrupt.c"
  "${SOLUTION_ROOT}/System/Timer.c"
  "${SOLUTION_ROOT}/System/DMA.c"
)
target_include_directories(Group_System PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  ${SOLUTION_ROOT}/System
)
target_compile_definitions(Group_System PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_System_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_System_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_System PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_System PUBLIC
  Group_System_ABSTRACTIONS
)

# group Driver
add_library(Group_Driver OBJECT
  "${SOLUTION_ROOT}/Driver/LED.c"
  "${SOLUTION_ROOT}/Driver/PassiveBuzzer.c"
  "${SOLUTION_ROOT}/Driver/KEY.c"
  "${SOLUTION_ROOT}/Driver/LightSensor.c"
  "${SOLUTION_ROOT}/Driver/OLED.c"
  "${SOLUTION_ROOT}/Driver/Encoder.c"
  "${SOLUTION_ROOT}/Driver/ColorLED.c"
  "${SOLUTION_ROOT}/Driver/Servo.c"
  "${SOLUTION_ROOT}/Driver/Motor.c"
  "${SOLUTION_ROOT}/Driver/InputCapture.c"
  "${SOLUTION_ROOT}/Driver/AD.c"
  "${SOLUTION_ROOT}/Driver/Serial.c"
  "${SOLUTION_ROOT}/Driver/MyI2C.c"
  "${SOLUTION_ROOT}/Driver/MPU6050.c"
  "${SOLUTION_ROOT}/Driver/W25Q64.c"
  "${SOLUTION_ROOT}/Driver/SPI.c"
)
target_include_directories(Group_Driver PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  ${SOLUTION_ROOT}/Driver
)
target_compile_definitions(Group_Driver PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_Driver_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_Driver_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_Driver PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Driver PUBLIC
  Group_Driver_ABSTRACTIONS
)
