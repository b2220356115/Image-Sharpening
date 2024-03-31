#include "ImageSharpening.h"

// Default constructor
ImageSharpening::ImageSharpening() {
    // Define the blurring kernel
    kernel_height = 3;
    kernel_width = 3;
    blurring_kernel = new double*[kernel_height];
    for (int i = 0; i < kernel_height; i++) {
        blurring_kernel[i] = new double[kernel_width];
    }

    for (int i = 0; i < kernel_height; i++) {
        for (int j = 0; j < kernel_width; j++) {
            blurring_kernel[i][j] = 1.0 / 9.0;
        }
    }
}

// Destructor
ImageSharpening::~ImageSharpening() {
    for (int i = 0; i < kernel_height; i++) {
        delete[] blurring_kernel[i];
    }
    delete[] blurring_kernel;
}

ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k) {
    // Get the dimensions of the input image
    int height = input_image.get_height();
    int width = input_image.get_width();

    // Create an output image matrix for the sharpened image

    Convolution convolution(blurring_kernel,3, 3, 1, true);
    // Convolve the input image with the blurring kernel
    ImageMatrix blurred_image = convolution.convolve(input_image);

    ImageMatrix sharpened = input_image + (input_image - blurred_image) * k;

    // Apply the sharpening algorithm
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {


            // Ensure that the pixel values are in the valid range [0, 255]
            if(sharpened.get_data(i,j) < 0) {
                sharpened.set_data(i, j, 0);
            }
            else if(sharpened.get_data(i, j) > 255) {
                sharpened.set_data(i, j, 255);

            }
        }
    }

    return sharpened;
}
