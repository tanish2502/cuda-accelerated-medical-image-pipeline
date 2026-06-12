cmake_minimum_required(VERSION 3.20)
project(CudaImagePipeline)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable( pipeline_cpu
                src/common/image_loader.cpp
                src/cpu/pipeline_cpu.cpp
                src/cpu/gaussian_blur.cpp
                src/cpu/sobel_edge.cpp
                src/cpu/threshold.cpp
                src/cpu/histogram_eq.cpp
)
