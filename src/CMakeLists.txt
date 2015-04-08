cmake_minimum_required(VERSION 2.8)
project(Segmentation_metrics)
find_package( OpenCV REQUIRED )
add_executable(main Segmentation_metrics.cpp)
target_link_libraries(main ${OpenCV_LIBS} )

