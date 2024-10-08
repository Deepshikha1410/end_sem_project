%%writefile main.cpp
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cstring>

extern "C" void perform_morphology(const unsigned char* h_input, unsigned char* h_output, int width, int height, bool is_dilation);

void process_image(const std::string& input_filename, const std::string& output_filename, bool is_dilation) {
    std::cout << "Attempting to load image from: " << input_filename << std::endl;

    // Load the image using OpenCV
    cv::Mat img = cv::imread(input_filename, cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        std::cerr << "Error: Could not load image from: " << input_filename << std::endl;
        return;
    }

    int width = img.cols;
    int height = img.rows;

    std::cout << "Image loaded successfully. Dimensions: " << width << "x" << height << std::endl;

    // Prepare the input and output buffers
    std::vector<unsigned char> h_input(width * height);
    std::vector<unsigned char> h_output(width * height);

    // Copy image data to input buffer
    std::memcpy(h_input.data(), img.data, width * height * sizeof(unsigned char));

    // Perform the morphological operation using CUDA
    std::cout << "Performing morphological operation: " << (is_dilation ? "Dilation" : "Erosion") << std::endl;
    perform_morphology(h_input.data(), h_output.data(), width, height, is_dilation);

    // Create an output image
    cv::Mat output_img(height, width, CV_8UC1);
    std::memcpy(output_img.data, h_output.data(), width * height * sizeof(unsigned char));

    std::cout << "Saving output image as: " << output_filename << std::endl;
    // Save the output image in JPEG format
    if (!cv::imwrite(output_filename, output_img)) {
        std::cerr << "Error: Could not save image to: " << output_filename << std::endl;
        return;
    }

    std::cout << "Image processing complete. Output saved as: " << output_filename << std::endl;
}

int main() {
    std::string input_filename;
    std::string output_filename;
    bool is_dilation;

    std::cout << "Enter input image filename (jpg, jpeg, png): ";
    std::cin >> input_filename;
    std::cout << "Enter output image filename (jpg, jpeg): ";
    std::cin >> output_filename;
    std::cout << "Enter 1 for dilation or 0 for erosion: ";
    std::cin >> is_dilation;

    process_image(input_filename, output_filename, is_dilation);

    return 0;
}
