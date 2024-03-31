#include "DecodeMessage.h"
#include <iostream>

// Default constructor
DecodeMessage::DecodeMessage() {
    // Nothing specific to initialize here
}

// Destructor
DecodeMessage::~DecodeMessage() {
    // Nothing specific to clean up
}

std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels) {
    // Your decoding logic goes here
    std::string decodedMessage;
    std::string binaryFormOfMessage;

    // Iterate through edgePixels and extract binary strings
    for (const auto& pixel : edgePixels) {
        // Assuming you have a function to extract binary strings from the image
        //std::string binaryString = extractBinaryString(image, pixel);
        int pixelValue = image.get_data(pixel.first, pixel.second);
        int LSB = pixelValue % 2;
        binaryFormOfMessage += std::to_string(LSB);
    }

    while (binaryFormOfMessage.length() % 7 != 0){
        binaryFormOfMessage = '0' + binaryFormOfMessage;
    }

    for(int i = 0; i < binaryFormOfMessage.length(); i+=7) {
        std::string subStr = binaryFormOfMessage.substr(i, 7);
        int asciiValue = std::stoi(subStr, nullptr, 2);

        while(asciiValue <= 32) {
            asciiValue+=33;
        }

        if(asciiValue >126) {
            asciiValue = 126;
        }


        decodedMessage += static_cast<char>(asciiValue);

    }

    return decodedMessage;
}
