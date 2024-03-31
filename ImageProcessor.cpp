#include "ImageProcessor.h"

ImageProcessor::ImageProcessor() {

}

ImageProcessor::~ImageProcessor() {

}


std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix &img) {
    ImageSharpening imageSharpening;

    ImageMatrix imageMatrix = imageSharpening.sharpen(img, 2);
    EdgeDetector edgeDetector;
    std::vector<std::pair<int, int>> locations = edgeDetector.detectEdges(imageMatrix);

    DecodeMessage decodeMessage;
    std::string uncryptedMessage = decodeMessage.decodeFromImage(imageMatrix, locations);
    return uncryptedMessage;

}

ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix &img, const std::string &message) {

}
