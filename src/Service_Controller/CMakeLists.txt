cmake_minimum_required(VERSION 3.14)

project(Service_Controller LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core SerialPort Network RemoteObjects)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core SerialPort Network RemoteObjects)

# Agrega tus fuentes y encabezados
file(GLOB SOURCES "source/*.cpp")
file(GLOB HEADERS "include/*.h")

add_executable(Service_Controller  main.cpp ${SOURCES} ${HEADERS}
)
target_link_libraries(Service_Controller Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::SerialPort Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::RemoteObjects)

install(TARGETS Service_Controller
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
