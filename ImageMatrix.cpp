#include "ImageMatrix.h"
#include <iostream>

// Default constructor
ImageMatrix::ImageMatrix() : height(0), width(0), data(nullptr) {
    // Initialize the members as needed.
}

// Parameterized constructor for creating a blank image of given size
ImageMatrix::ImageMatrix(int imgHeight, int imgWidth) : height(imgHeight), width(imgWidth) {
    // Initialize data as a 2D array of size height x width.
    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
        for (int j = 0; j < width; ++j) {
            // Initialize data elements to some default value, e.g., 0.
            data[i][j] = 0.0;
        }
    }
}

// Parameterized constructor for loading an image from a file (implementation provided elsewhere)
ImageMatrix::ImageMatrix(const std::string &filepath) {
    ImageLoader imageLoader(filepath);

    height = imageLoader.getHeight();
    width = imageLoader.getWidth();

    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
    }

    double** imageData = imageLoader.getImageData();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            data[i][j] = imageData[i][j];
        }
    }
}


// Destructor
ImageMatrix::~ImageMatrix() {
    // Deallocate memory for the data array.
    if (data != nullptr) {
        for (int i = 0; i < height; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }
}

// Parameterized constructor - direct initialization with a 2D matrix
ImageMatrix::ImageMatrix(const double** inputMatrix, int imgHeight, int imgWidth) : height(imgHeight), width(imgWidth) {
    // Initialize data as a 2D array of size height x width and copy data from inputMatrix.
    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
        for (int j = 0; j < width; ++j) {
            data[i][j] = inputMatrix[i][j];
        }
    }
}

// Copy constructor
ImageMatrix::ImageMatrix(const ImageMatrix &other) : height(other.height), width(other.width) {
    // Initialize data as a new 2D array and copy data from 'other'.
    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
        for (int j = 0; j < width; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
}

// Copy assignment operator
ImageMatrix& ImageMatrix::operator=(const ImageMatrix &other) {
    if (this == &other) {
        return *this; // Handle self-assignment
    }

    // Deallocate old memory and copy data from 'other'.
    for (int i = 0; i < height; ++i) {
        delete[] data[i];
    }
    delete[] data;

    height = other.height;
    width = other.width;

    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
        for (int j = 0; j < width; ++j) {
            data[i][j] = other.data[i][j];
        }
    }

    return *this;
}

// Overloaded operator + to add two matrices
ImageMatrix ImageMatrix::operator+(const ImageMatrix &other) const {
    // Implement addition of two matrices element-wise and return the result.
    ImageMatrix result(height, width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            result.data[i][j] = this->data[i][j] + other.data[i][j];
        }
    }
    return result;
}

// Overloaded operator - to subtract two matrices
ImageMatrix ImageMatrix::operator-(const ImageMatrix &other) const {
    // Implement subtraction of two matrices element-wise and return the result.
    ImageMatrix result(height, width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            result.data[i][j] = this->data[i][j] - other.data[i][j];
        }
    }
    return result;
}

// Overloaded operator * to multiply a matrix with a scalar
ImageMatrix ImageMatrix::operator*(const double &scalar) const {
    // Implement scalar multiplication of the matrix and return the result.
    ImageMatrix result(height, width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            result.data[i][j] = this->data[i][j] * scalar;
        }
    }
    return result;
}

// Getter function to access the data in the matrix
double** ImageMatrix::get_data() const {
    return data;
}

// Getter function to access the data at the index (i, j)
double ImageMatrix::get_data(int i, int j) const {
    return data[i][j];
}


int ImageMatrix::get_height() const{
    return height;
}

int ImageMatrix::get_width() const{
    return width;
}

void ImageMatrix::set_data(int i, int j, double value) {
    data[i][j] = value;
}