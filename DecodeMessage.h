#ifndef DECODE_MESSAGE_H
#define DECODE_MESSAGE_H

#include <string>
#include <vector>
#include "ImageMatrix.h"

class DecodeMessage {
public:
    // Constructors and destructors
    DecodeMessage(); // Default constructor
    ~DecodeMessage(); // Destructor

    std::string decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels);

private:
    // Private helper function to extract binary string
    std::string extractBinaryString(const ImageMatrix& image, const std::pair<int, int>& pixel);

    // Private helper function to convert binary to ASCII
    std::string binaryToASCII(const std::string& binaryString);
};

#endif // DECODE_MESSAGE_H
