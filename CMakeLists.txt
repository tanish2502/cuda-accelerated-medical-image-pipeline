cmake_minimum_required(VERSION 3.20)
project(CudaImagePipeline LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)

set(CMAKE_CUDA_ARCHITECTURE 89) #CUDA Arc for RTX 500 Ada
set(OpenCV_DIR "C:/opencv/opencv/build")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(include)

#CPU Executables
add_executable( pipeline_cpu
                src/common/image_loader.cpp
                src/cpu/pipeline_cpu.cpp
                src/cpu/gaussian_blur.cpp
                src/cpu/sobel_edge.cpp
                src/cpu/threshold.cpp
                src/cpu/histogram_eq.cpp
)
target_link_libraries(pipeline_cpu ${OpenCV_LIBS})

#GPU Naive Executables
add_executable( pipeline_gpu_naive
                src/common/image_loader.cpp
                src/gpu_naive/pipeline_gpu_naive.cu
                src/gpu_naive/threshold.cu
)
target_link_libraries(pipeline_gpu_naive ${OpenCV_LIBS})