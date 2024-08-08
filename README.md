Image Processing using CUDA and OpenCV

Overview
This project demonstrates image processing using CUDA, a parallel computing platform developed by NVIDIA, and OpenCV, a computer vision library. The project performs morphological operations (dilation or erosion) on a grayscale image using CUDA and OpenCV.

Files
main.cpp: The main C++ file that loads an image, performs the morphological operation using CUDA, and saves the output image using OpenCV.
perform_morphology.cu: The CUDA kernel file that performs the morphological operation on the image.
How to Use
Compile the Project: Compile the project using a C++ compiler that supports CUDA (e.g., NVIDIA's nvcc compiler).
Run the Program: Run the program by executing the compiled executable file.
Input Image: Enter the filename of the input image (in JPEG, PNG, or other formats supported by OpenCV) when prompted.
Output Image: Enter the filename of the output image (in JPEG format) when prompted.
Morphological Operation: Enter 1 for dilation or 0 for erosion when prompted.
Output
The program will save the output image in the specified filename.

Dependencies

OpenCV library (for image loading and saving)
CUDA Toolkit (for parallel computing)
Note
This project assumes that the CUDA Toolkit is installed on the system and that the OpenCV library is available. The project has been tested on a system with a NVIDIA GPU.

Troubleshooting

If you're unable to find the CUDA template in Visual Studio, check the following:
Verify CUDA Toolkit installation
Verify CUDA Visual Studio Integration
Check CUDA Template Location
Register CUDA Template
Restart Visual Studio
If you're still unable to find the CUDA template, you can create a CUDA project manually by creating an empty project and adding a new CUDA file.
Code Explanation
The code uses OpenCV to load the input image and save the output image. The perform_morphology function is a CUDA kernel that performs the morphological operation on the image. The process_image function prepares the input and output buffers, copies the image data to the input buffer, performs the morphological operation using CUDA, and copies the output data to the output buffer.
