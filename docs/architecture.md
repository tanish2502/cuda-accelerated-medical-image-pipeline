# Pipeline Architecture

## Overview
Four stage image processing pipeline implemented in three tiers:
CPU baseline -> Naive GPU -> Optimized GPU

## Pipeline Stages
1. Thresholding: Binary segmentation at configurable intensity
2. Histogram Equalization: Contrast improvement via CDF remapping
3. Sobel Edge Detection: Gradient based edge enhancement
4. Gaussian Blur: Noise reduction using 5x5 kernel

## Design Decisions

### Why 16-bit Grayscale Instead of DICOM
Focus is GPU performance optimization, not medical file parsing.
16-bit grayscale accurately represents medical image bit depth while keeping pipeline complexity focused on compute performance.

### Why In-Place Processing
Large images (1024x1024 = 2MB at 16-bit) make copy-per-stage expensive.
In-place modification avoids unnecessary allocations.

### Why Separate CPU/GPU Implementations
Clean performance comparison requires identical algorithms across all three tiers.
Shared headers enforce consistent interfaces.

### Memory Lifecycle
GPU memory allocated per-pipeline-run, not per-stage.
Minimizes cudaMalloc/cudaFree overhead across stages.
