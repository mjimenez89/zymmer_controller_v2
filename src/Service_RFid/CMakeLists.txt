cmake_minimum_required(VERSION 3.14)

project(Service_RFid LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network RemoteObjects)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network RemoteObjects)

# Agrega tus fuentes y encabezados
file(GLOB SOURCES "src/*.cpp" "src/remoteobjects/*.cpp")
file(GLOB HEADERS "src/*.h" "src/remoteobjects/*.h")

include_directories(src
    src/remoteobjects
                )
#qt5_generate_repc(SOURCES src/remoteobjects/rfid.rep SOURCE)
add_executable(Service_RFid  main.cpp ${SOURCES} ${HEADERS}
)
target_link_libraries(Service_RFid Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::RemoteObjects)

install(TARGETS Service_RFid
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
