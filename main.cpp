#include <iostream>
#include <string>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <image_path> [new_width]\n";
        return 1;
    }

    const char* imagePath = argv[1];
    int newWidth = 100; // Default width
    
    if (argc >= 3) {
        try {
            newWidth = std::stoi(argv[2]);
            if (newWidth <= 0) {
                std::cerr << "Width must be positive.\n";
                return 1;
            }
        } catch (...) {
            std::cerr << "Invalid width parameter.\n";
            return 1;
        }
    }

    int width, height, channels;
    // Load image (we don't force channels, just use whatever it has)
    unsigned char* data = stbi_load(imagePath, &width, &height, &channels, 0);

    if (!data) {
        std::cerr << "Failed to load image: " << imagePath << "\n";
        return 1;
    }

    // Characters sorted by density (darkest to lightest for white background)
    // For standard dark terminal backgrounds, white pixels (255) should map to denser chars.
    std::string asciiChars = " .:-=+*#%@";

    // Aspect ratio correction (terminal chars are roughly twice as tall as they are wide)
    float aspect = (float)height / width;
    int newHeight = static_cast<int>(newWidth * aspect * 0.5f);

    if (newHeight <= 0) newHeight = 1;

    float widthRatio = (float)width / newWidth;
    float heightRatio = (float)height / newHeight;

    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            int oldY = static_cast<int>(y * heightRatio);
            int oldX = static_cast<int>(x * widthRatio);

            // Calculate offset based on number of channels
            int offset = (oldY * width + oldX) * channels;

            unsigned char r = data[offset];
            unsigned char g = channels > 1 ? data[offset + 1] : r;
            unsigned char b = channels > 2 ? data[offset + 2] : r;

            // Simple grayscale conversion
            float gray = 0.299f * r + 0.587f * g + 0.114f * b;
            
            // Map grayscale value (0-255) to ascii string index
            int charIndex = static_cast<int>((gray / 255.0f) * (asciiChars.size() - 1));
            
            // Clamp just in case
            if (charIndex < 0) charIndex = 0;
            if (charIndex >= static_cast<int>(asciiChars.size())) charIndex = static_cast<int>(asciiChars.size()) - 1;

            std::cout << asciiChars[charIndex];
        }
        std::cout << "\n";
    }

    stbi_image_free(data);
    return 0;
}
