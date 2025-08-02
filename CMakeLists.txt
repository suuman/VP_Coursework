cmake_minimum_required(VERSION 3.26)

project(VP_QT VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


find_package(Qt6 REQUIRED COMPONENTS Widgets Test)

find_package(OpenCV 4 REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        window_QT.cpp
        mainwindow.h
        options.cpp
        cvfunctions.cpp
        CameraCalibrator.cpp
        window_QT.qrc
)

 set(PROJECT_HEADERS 
     mainwindow.h
     window_QT.h
     options.h
     cvfunctions.h
     definations.h
     matcher.h
     CameraCalibrator.h
     )

  include_directories(
  	${OpenCV_INCLUDE_DIRS}
     	)
     	
   SET(QT_LIBRARIES
        Qt6::Widgets
        Qt6::Test
    )


add_executable(vp_qt
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    )

target_link_libraries(vp_qt ${QT_LIBRARIES} ${OpenCV_LIBRARIES})


