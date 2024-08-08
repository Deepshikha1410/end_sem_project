#include <cuda_runtime.h>
#include <algorithm>

__device__ unsigned char max(unsigned char a, unsigned char b) {
    return (a > b) ? a : b;
}

__device__ unsigned char min(unsigned char a, unsigned char b) {
    return (a < b) ? a : b;
}

__global__ void morphology_kernel(const unsigned char* input, unsigned char* output, int width, int height, int kernel_size, bool is_dilation) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < width && y < height) {
        unsigned char result = (is_dilation) ? 0 : 255;

        int half_kernel = kernel_size / 2;

        for (int ky = -half_kernel; ky <= half_kernel; ++ky) {
            for (int kx = -half_kernel; kx <= half_kernel; ++kx) {
                int nx = min(max(x + kx, 0), width - 1);
                int ny = min(max(y + ky, 0), height - 1);
                unsigned char pixel = input[ny * width + nx];
                if (is_dilation) {
                    result = max(result, pixel);
                } else {
                    result = min(result, pixel);
                }
            }
        }

        output[y * width + x] = result;
    }
}

extern "C" void perform_morphology(const unsigned char* h_input, unsigned char* h_output, int width, int height, bool is_dilation) {
    unsigned char* d_input;
    unsigned char* d_output;
    int kernel_size = 3; // Example kernel size

    cudaMalloc(&d_input, width * height * sizeof(unsigned char));
    cudaMalloc(&d_output, width * height * sizeof(unsigned char));
    cudaMemcpy(d_input, h_input, width * height * sizeof(unsigned char), cudaMemcpyHostToDevice);

    dim3 blockSize(16, 16);
    dim3 gridSize((width + blockSize.x - 1) / blockSize.x, (height + blockSize.y - 1) / blockSize.y);

    morphology_kernel<<<gridSize, blockSize>>>(d_input, d_output, width, height, kernel_size, is_dilation);

    cudaMemcpy(h_output, d_output, width * height * sizeof(unsigned char), cudaMemcpyDeviceToHost);

    cudaFree(d_input);
    cudaFree(d_output);
}
