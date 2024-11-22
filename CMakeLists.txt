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
message("*******************************************************************************")

if(UNIX)
    message("\n*******************************************************************************")
    message("Build for: Linux")

    find_package(raylib 5.5 REQUIRED)
    find_package(Lua REQUIRED)
    find_package(PhysFS REQUIRED)
    find_package(SDL2 REQUIRED)

    if(raylib_FOUND)
        message("\tRaylib Found")
        include_directories(${Raylib_INCLUDE_DIRS})
    elseif(NOT Raylib_FOUND)
        message("\tRaylib Not Found")
    endif()
    if(SDL2_FOUND)
        message("\tSDL2 Found")
        include_directories(${SDL2_INCLUDE_DIRS})
    elseif(NOT SDL2_FOUND)
        message("\tSDL2 Not Found")
    endif()
    if(Lua_FOUND)
        message("\tLua Found")
        include_directories(${Lua_INCLUDE_DIRS})
    elseif(NOT Lua_FOUND)
        message("\tLua Not Found")
    endif()
    if(PhysFS_FOUND)
        message("\tPhysFS Found")
        include_directories(${PhysFS_INCLUDE_DIRS})
    elseif(NOT PhysFS_FOUND)
        message("\tPhysFS Not Found")
    endif()
    #include für Linux/Unix
    include_directories(
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/src"
    "${CMAKE_SYSTEM_INCLUDE_PATH}"
    "${PROJECT_SOURCE_DIR}/extra/"
    "${PROJECT_SOURCE_DIR}/extra/raylib-extra"
    )
    message("*******************************************************************************")

elseif(WIN32)
    message("Windows wird noch nicht unterstützt")

    #include für Windows
    include_directories(
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/src"
    "${CMAKE_SYSTEM_INCLUDE_PATH}"
    "${PROJECT_SOURCE_DIR}/extra/"
    "${PROJECT_SOURCE_DIR}/extra/raylib-extra"
    )
endif()

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
    physfs
    lua
    SDL2
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


