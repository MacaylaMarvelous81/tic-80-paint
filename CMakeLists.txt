cmake_minimum_required(VERSION 3.25.1)

project(tic-80-paint)

set(TARGET_BINARY ${CMAKE_PROJECT_NAME})
set(TARGET_CART "${CMAKE_PROJECT_NAME}.tic")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-zstack-size=8192,--no-entry,--import-memory -mexec-model=reactor -Wl,--initial-memory=262144,--max-memory=262144,--global-base=98304")

add_executable(${TARGET_BINARY} src/main.c)

configure_file(base.wasmp base.wasmp)
# tic80 will hang on the overwrite confirmation prompt if the cart file is not deleted beforehand while running in cli mode.
add_custom_target(${TARGET_CART} COMMAND rm -f '${CMAKE_CURRENT_BINARY_DIR}/${TARGET_CART}' COMMAND tic80 --fs '${CMAKE_CURRENT_BINARY_DIR}' --cli --cmd 'load base.wasmp & import binary ${TARGET_BINARY} & save ${TARGET_CART} & exit' DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/base.wasmp ${TARGET_BINARY})
