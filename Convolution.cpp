#include <iostream>
#include "Convolution.h"

// Default constructor
Convolution::Convolution() {
    // Initialize member variables or allocate resources if needed
    customKernel = nullptr; // Initialize customKernel as needed
    kh = 0; // Initialize kh as needed
    kw = 0; // Initialize kw as needed
    stride_val = 1; // Initialize stride_val as needed
    pad = false; // Initialize pad as needed
}

// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** customKernel, int kh, int kw, int stride_val, bool pad) {
    // Initialize member variables with the provided values
    //this->customKernel = customKernel;
    this->kh = kh;
    this->kw = kw;
    this->stride_val = stride_val;
    this->pad = pad;
    this->customKernel = new double*[this->kh];
    for(int i = 0; i < this->kh; i++) {
        this->customKernel[i] = new double[this->kw];
        for(int j = 0; j < this->kw; j++) {
            this->customKernel[i][j] = customKernel[i][j];
        }
    }


}

// Destructor
Convolution::~Convolution() {
    // Deallocate any resources (e.g., dynamic memory) if needed
    // For example, if customKernel was dynamically allocated, you should deallocate it here
    if (customKernel != nullptr) {
        for (int i = 0; i < kh; i++) {
            delete[] customKernel[i];
        }
        delete[] customKernel;
    }
}

// Copy constructor
Convolution::Convolution(const Convolution &other) {
    // Implement a copy of member variables if needed
    this->kh = other.kh;
    this->kw = other.kw;
    this->stride_val = other.stride_val;
    this->pad = other.pad;

    // Copy the customKernel if it's dynamically allocated
    if (other.customKernel != nullptr) {
        this->customKernel = new double*[kh];
        for (int i = 0; i < kh; i++) {
            this->customKernel[i] = new double[kw];
            for (int j = 0; j < kw; j++) {
                this->customKernel[i][j] = other.customKernel[i][j];
            }
        }
    }
}

// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {
    if (this == &other) {
        return *this; // Self-assignment check
    }

    // Implement the assignment of member variables
    kh = other.kh;
    kw = other.kw;
    stride_val = other.stride_val;
    pad = other.pad;

    // Deallocate resources from the current object if needed (similar to the destructor)
    if (customKernel != nullptr) {
        for (int i = 0; i < kh; i++) {
            delete[] customKernel[i];
        }
        delete[] customKernel;
    }

    // Copy the customKernel from the other object if it's dynamically allocated
    if (other.customKernel != nullptr) {
        customKernel = new double*[kh];
        for (int i = 0; i < kh; i++) {
            customKernel[i] = new double[kw];
            for (int j = 0; j < kw; j++) {
                customKernel[i][j] = other.customKernel[i][j];
            }
        }
    } else {
        customKernel = nullptr; // Reset to nullptr if the other object's customKernel is nullptr
    }

    return *this;
}

// Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.
ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {
    int input_height = input_image.get_height();
    int input_width = input_image.get_width();
    int output_height = (pad) ? ((input_height - kh + 1 + 1 * 2) / stride_val) : ((input_height - kh + 1) / stride_val);
    int output_width = (pad) ? ((input_width - kw + 1 + 1 * 2) / stride_val) : (input_width - kw + 1) / stride_val;
    ImageMatrix paddedImage((pad) ? ((input_height + 2) / stride_val) : (input_height / stride_val), (pad) ? ((input_width + 2) / stride_val) : (input_width / stride_val));
    ImageMatrix output_image(output_height, output_width);

    if(pad) {
        for(int i = 1; i < input_height + 1; i++) {
            for(int j = 1; j < input_width + 1; j++) {
                paddedImage.set_data(i, j, input_image.get_data((i-1) * stride_val , (j-1) * stride_val));
            }
        }
    }
    else {
        paddedImage = input_image;
    }



    for (int i = 0; i < paddedImage.get_height(); i++) {
        reloop:
        double sum = 0.0;
        for (int j = 0; j < paddedImage.get_width(); j++) {
            for (int m = 0; m < kh; m++) {
                for (int n = 0; n < kw; n++) {
                    int x = i * stride_val + m;
                    int y = j * stride_val + n;
                    if(x < paddedImage.get_height() && y < paddedImage.get_width()) {
                        sum += paddedImage.get_data(x, y) * customKernel[m][n];

                    }

                    else if(y >= paddedImage.get_height()) {
                        i++;
                        goto reloop;
                    }

                    else if(x>= paddedImage.get_width()) {
                        goto finish;
                    }
                }
            }
            output_image.set_data(i, j, sum);
            sum = 0;
        }
    }
    finish:
    return output_image;
}
