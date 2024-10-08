cmake_minimum_required(VERSION 3.16)

project(inputcmdtest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)  # 设置C++标准为C++14
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # 如果指定的C++标准不可用，则报错
set(CMAKE_CXX_EXTENSIONS OFF)  # 禁用编译器特定的扩展
if(MSVC)
    add_compile_options(/Zc:__cplusplus)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(inputcmdtest
    main.cpp
)

qt_add_qml_module(inputcmdtest
    URI inputcmdtest
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES inputcmd.pb.cc inputcmd.pb.h
        SOURCES singleton.h
        SOURCES tcplink.h tcplink.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(inputcmdtest PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.inputcmdtest
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(inputcmdtest
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty/boost_1_86_0/
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty/protobuf/src/
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty/protobuf/third_party/abseil-cpp
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty/jsoncpp-master/include/
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../renderbase/
)

target_link_libraries(inputcmdtest
    PRIVATE Qt6::Quick
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty/protobuf/bin/Debug/libprotobufd.lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty/protobuf/bin/Debug/libprotocd.lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty/protobuf/bin/Debug/abseil_dll.lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../renderproxy/x64/Debug/renderbase.lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty/jsoncpp-master/build/lib/Debug/jsoncpp_static.lib
)

include(GNUInstallDirs)
install(TARGETS inputcmdtest
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
