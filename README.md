# CUDA Accelerated Medical Image Processing Pipeline

A high-performance image processing pipeline implemented in three stages:
- CPU baseline (C++)
- Naive GPU implementation (CUDA)
- Optimized GPU implementation (CUDA - shared memory, coalescing)

## Pipeline Stages
1. Thresholding — Binary segmentation
2. Histogram Equalization — Contrast improvement
3. Sobel Edge Detection — Edge enhancement  
4. Gaussian Blur — Noise reduction

## Hardware
- CPU Development: Apple M1
- GPU Development: NVIDIA RTX 500 Ada (CUDA 12.4)

> 🚧 Work in progress — CPU baseline → Naive GPU → Optimized GPU implementations with benchmarking.

## Results
*(CPU baseline results coming soon)*
*(GPU benchmark results coming soon)*
