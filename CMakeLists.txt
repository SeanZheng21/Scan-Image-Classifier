cmake_minimum_required(VERSION 3.14)
project(Projet_OpenCV_CMake)


set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)

include_directories(include ${OpenCV_INCLUDE_DIRS})


add_executable(Projet_OpenCV_CMake
        include/histogram.hpp
        src/histogram.cpp
        src/Main.cpp
        include/connected.h
        src/connected.cpp
        include/cross_detector.h
        src/cross_detector.cpp
        include/matcher.h
        src/matcher.cpp
        src/reformat_image.cpp
        include/reformat_image.h
        src/SquareExtractor.cpp
        include/SquareExtractor.h
        src/thresholding.cpp
        include/thresholding.h
        src/SizeDetector.cpp
        include/SizeDetector.h src/textscan.cpp include/textscan.h)

target_link_libraries(Projet_OpenCV_CMake ${OpenCV_LIBS})
