cmake_minimum_required(VERSION 3.20.0)

project("EmuGB" VERSION 1.0.0)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

include_directories(
    ${CMAKE_SOURCE_DIR}/inc/
    ${CMAKE_SOURCE_DIR}/Core/inc/

)

add_compile_options(-Wall -Wno-unknown-pragmas)

#Liste des fichiers
file(GLOB HEADER_FILES ${CMAKE_SOURCE_DIR}/inc/*.hpp)
file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

file(GLOB CORE_HEADER_FILES ${CMAKE_SOURCE_DIR}/Core/inc/*.hpp)
file(GLOB CORE_SRC_FILES ${CMAKE_SOURCE_DIR}/Core/src/*.cpp)


#Exec
add_executable("${PROJECT_NAME}" ${CMAKE_SOURCE_DIR} ${SRC_FILES} ${CORE_SRC_FILES} ${CORE_HEADER_FILES} ${HEADER_FILES})

#Librairies
set(LIB_SDL2 ${CMAKE_SOURCE_DIR}/lib/SDL2.lib)
set(LIB_SDL2_MAIN ${CMAKE_SOURCE_DIR}/lib/SDL2main.lib)
target_link_libraries(${PROJECT_NAME} ${LIB_SDL2_MAIN})
target_link_libraries(${PROJECT_NAME} ${LIB_SDL2})





