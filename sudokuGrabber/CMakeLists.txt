cmake_minimum_required(VERSION 3.10)
project(sudokuGrabber)

find_package(PkgConfig REQUIRED)

find_package(OpenCV REQUIRED)
link_directories(${OPENCV_LIBRARY_DIRS})

pkg_search_module(Tesseract REQUIRED tesseract)
include_directories(${TESSERACT_INCLUDE_DIRS})
link_directories(${TESSERACT_LIBRARY_DIRS})

add_executable(sudokuGrabber sudokuGrabber.cpp)

target_link_libraries(sudokuGrabber ${OpenCV_LIBS})
target_link_libraries(sudokuGrabber ${TESSERACT_LIBRARIES})
target_link_libraries(sudokuGrabber -ltesseract)

set_target_properties(sudokuGrabber PROPERTIES OUTPUT_NAME "sudokuGrabberExe")