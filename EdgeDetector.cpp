// EdgeDetector.cpp

#include "EdgeDetector.h"
#include <cmath>

#include "EdgeDetector.h"
#include <cmath>

// Default constructor
EdgeDetector::EdgeDetector() {
    sobel_gx = new double*[3];
    sobel_gx[0] = new double[3]{
        -1,0,1,
    };
    sobel_gx[1] = new double[3]{
        -2,0,2
    };
    sobel_gx[2] = new double[3]{
        -1,0,1
    };

    sobel_gy = new double*[3];
    sobel_gy[0] = new double[3]{
        -1,-2,-1
    };
    sobel_gy[1] = new double [3]{
        0,0,0
    };
    sobel_gy[2] = new double [3]{
        1,2,1
    };
}

// Destructor
EdgeDetector::~EdgeDetector() {

}

// Detect Edges using the given algorithm
std::vector<std::pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix& input_image) {
    Convolution convolutionX(sobel_gx, 3, 3, 1, true);
    Convolution convolutionY(sobel_gy, 3, 3, 1, true);
    ImageMatrix Ix = convolutionX.convolve(input_image);
    ImageMatrix Iy = convolutionY.convolve(input_image);


    std::vector<std::pair<int, std::pair<int, int>>> vectorOfGradientsAndLocations;
    std::vector<std::pair<int, int>> pixelsOfEdges;
    double allSummation = 0;
    double threshold = 0;

    for(int i = 0; i < Ix.get_height(); i++) {
        for(int j = 0; j < Ix.get_width(); j++) {
            double summation = 0;

            summation = sqrt(Ix.get_data(i, j) * Ix.get_data(i, j) + Iy.get_data(i, j) * Iy.get_data(i, j));
            allSummation += summation;

            vectorOfGradientsAndLocations.push_back(std::make_pair(summation, std::make_pair(i, j)));
        }
    }

    threshold = allSummation / (Ix.get_height() * Ix.get_width());

    for(int i = 0; i < vectorOfGradientsAndLocations.size(); i++) {
        if(vectorOfGradientsAndLocations.at(i).first > threshold) {
            pixelsOfEdges.push_back(vectorOfGradientsAndLocations.at(i).second);
        }
    }

    return pixelsOfEdges;
}

