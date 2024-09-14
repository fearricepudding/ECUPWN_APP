cmake_minimum_required(VERSION 3.5)

project(ECUPWN VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Boost COMPONENTS thread system chrono REQUIRED)

set(TS_FILES ECUPWN_en_GB.ts)

include_directories(${Boost_INCLUDE_DIR})

set(PROJECT_SOURCES
        include/json.hpp

        src/main.cpp
        src/splash.cpp
        src/splash.h

        src/lookup.cpp
        src/lookup.hpp

        src/connectionsettings.h
        src/connectionsettings.cpp

        src/File.cpp
        src/File.h

        src/utils/codelookup.cpp
        src/utils/canlogger.h
        src/utils/canlogger.cpp
        src/utils/codelookup.h

       
        
        src/CAN/canworker.cpp
        src/CAN/canworker.h
        src/CAN/CanQueue.h
        src/CAN/CanQueue.cpp
        src/CAN/ConnectionManager.cpp
        src/CAN/ConnectionManager.h

        ui/codelookup.ui
        ui/splash.ui
        ui/canlogger.ui
        ui/connectionsettings.ui

        ${TS_FILES}
)

add_subdirectory(candy)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ECUPWN
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ECUPWN APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(ECUPWN SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ECUPWN
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(ECUPWN PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${Boost_LIBRARIES} candy)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ECUPWN)
endif()
set_target_properties(ECUPWN PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ECUPWN
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ECUPWN)
endif()
