cmake_minimum_required(VERSION 3.10)
project(ProjectLobotomy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Core Gui Widgets Multimedia REQUIRED)

qt5_add_resources(RESOURCES resources.qrc)

add_executable(ProjectLobotomy
    main.cpp
    LobotomyApp.cpp
    LobotomyApp.h
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
