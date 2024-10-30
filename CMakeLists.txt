#Minimum CMake Version
cmake_minimum_required(VERSION 3.25)

set(CMAKE_MESSAGE_LOG_LEVEL "NOTICE")

#Projektname
project(
    GFW
    VERSION 1.0.0
    DESCRIPTION "Test mit Raylib"
    LANGUAGES CXX
)

#C++ Version
set(CMAKE_CXX_STANDARD 23)

add_definitions(-DDEBUG)

#Wurzelverzeichnis setzen
message("\n*******************************************************************************")
set(ROOT_DIR ${PROJECT_SOURCE_DIR})
message("Projekt: ${PROJECT_NAME}\nVerzeichnis: ${ROOT_DIR}")
message("\n*******************************************************************************")

#Zusatz Bibliotheken
set(THIRDPARTY_DIR extra)
message("\n*******************************************************************************")
set(RAYLIB_DIR ${THIRDPARTY_DIR}/raylib/raylib)
message("Raylib Verzeichnis: ${RAYLIB_DIR}")
message("\n*******************************************************************************")
add_subdirectory(${RAYLIB_DIR})

include_directories(
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/src"
    "${CMAKE_SYSTEM_INCLUDE_PATH}"
    "${PROJECT_SOURCE_DIR}/extra/"
    )

#Quelltextdateien
set(projectSOURCES
    src/Log.cpp
    src/Settings.cpp
    TestApp/main.cpp

)

#Header
set(projectHEADERS
    src/Log.hpp
    src/Settings.hpp
)

#Anwendung erstellen
add_executable(${PROJECT_NAME}_Testapp
    ${projectSOURCES}
    ${projectHEADERS}
)

#Linken
target_link_libraries(${PROJECT_NAME}_Testapp
    raylib
    lua
)

#Installationsverzeichnis festlegen
install (TARGETS ${PROJECT_NAME}_Testapp
    CONFIGURATIONS Debug
    RUNTIME DESTINATION Debug_bin
)

install(TARGETS ${PROJECT_NAME}_Testapp
    CONFIGURATIONS Release
    RUNTIME DESTINATION Release_bin
)


