cmake_minimum_required(VERSION 3.15)
project(ProjectLobotomy)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /O2 /DNDEBUG")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /INCREMENTAL:NO")
endif()

find_package(Qt5 COMPONENTS Core Gui Widgets Multimedia REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.h"
    "${CMAKE_SOURCE_DIR}/src/*.hpp"
)

qt5_add_resources(RESOURCES resources.qrc)

add_executable(ProjectLobotomy
    ${SOURCES}
    ${RESOURCES}
)

if(WIN32)
    set_target_properties(ProjectLobotomy PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

target_link_libraries(ProjectLobotomy PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Multimedia
)

if(WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release")
    find_program(WINDEPLOYQT_EXE windeployqt HINTS "${Qt5_DIR}/../../../bin" ENV PATH)

    if(WINDEPLOYQT_EXE)
        add_custom_command(TARGET ProjectLobotomy POST_BUILD
            COMMAND "${WINDEPLOYQT_EXE}"
                --verbose 0
                --no-compiler-runtime
                --no-translations
                --no-angle
                --no-opengl-sw
                "$<TARGET_FILE_DIR:ProjectLobotomy>"
            COMMENT "Deploying Qt runtime dependencies..."
        )
        
        add_custom_target(deploy
            COMMAND ${CMAKE_COMMAND} -E remove_directory deploy
            COMMAND ${CMAKE_COMMAND} -E copy_directory 
                "$<TARGET_FILE_DIR:ProjectLobotomy>" 
                ${CMAKE_SOURCE_DIR}/deploy
            COMMAND ${CMAKE_COMMAND} -E remove 
                ${CMAKE_SOURCE_DIR}/deploy/*.pdb
                ${CMAKE_SOURCE_DIR}/deploy/*.ilk
                ${CMAKE_SOURCE_DIR}/deploy/*.exp
                ${CMAKE_SOURCE_DIR}/deploy/*.lib
            DEPENDS ProjectLobotomy
            COMMENT "Creating clean deploy folder..."
        )
    else()
        message(WARNING "windeployqt not found! Qt deployment skipped.")
    endif()
endif()