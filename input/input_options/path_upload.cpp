#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <filesystem>

#include "path_upload.hpp"
#include "../../general_constants.hpp"

namespace fs = std::filesystem;

// // You can define these somewhere, like in a constants header
// const std::string IMAGE_SAVE_PATH = "";       // adjust as needed
// const std::string IMAGE_SAVE_FILENAME = "input_img.jpg";

cv::Mat PathUpload::load_image(const std::string& path) {
    // Load image in BGR format
    cv::Mat img = cv::imread(path, cv::IMREAD_COLOR);
    if (img.empty()) {
        throw std::runtime_error("Failed to load image at " + path);
    }

    // Convert BGR to RGB
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    return img;
}

void PathUpload::save_image(const cv::Mat& img) {
    cv::Mat save_img;
    // Convert back to BGR for saving as jpg
    // Ensure save folder exists
            // fs::create_directories(IMAGE_SAVE_PATH);

    std::string path = fs::path(IMAGE_SAVE_PATH) / IMAGE_SAVE_FILENAME;
    cv::cvtColor(img, save_img, cv::COLOR_RGB2BGR);

    if (!cv::imwrite(path, save_img)) {
        throw std::runtime_error("Failed to save image to " + path);
    } else {
        std::cout << "Image saved to " << path << "\n"; // DEBUG
    }
}

Status PathUpload::receive_input()
{
    bool should_try_get_input = true;

    while (should_try_get_input) {
        std::cout << "Enter image path: ";
        std::string path;
        std::getline(std::cin, path);

        try {
            cv::Mat img = load_image(path);
            save_image(img);
            return SUCCESS;
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
            std::cout << "Do you want to try to upload an image again? y/n: ";
            std::string retry;
            std::getline(std::cin, retry);
            if (retry != "y" && retry != "Y") {
                should_try_get_input = false;
            }
        }
    }
    return EXIT;
}
