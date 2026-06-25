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
- CPU Development: Intel Core Ultra 7 165H
- GPU Development: NVIDIA RTX 500 Ada (CUDA 12.4)

> 🚧 Work in progress — CPU baseline → Naive GPU → Optimized GPU implementations with benchmarking.

## Results
## Benchmark Results

### CPU Baseline (Intel Core Ultra 7 165H — Release Mode)
| Stage | Time (ms) |
|---|---|
| Gaussian Blur | 36.17 |
| Sobel Edge | 13.72 |
| Histogram Eq | 2.84 |
| Threshold | 0.35 |
| **Total Pipeline** | **56.17** |

> Image: 1024×1024 16-bit grayscale | Averaged over 5 runs

### GPU benchmark (NVIDIA RTX 500 Ada) results coming soon...
| Stage | GPU Naive | GPU Optimized |
|---|---|---|
| Gaussian Blur | TBD | TBD |
| Sobel Edge | TBD | TBD |
| Histogram Eq | TBD | TBD |
| Threshold | TBD | TBD |
| **Total** | **TBD** | **TBD** |

