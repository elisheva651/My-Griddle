#include <iostream>
#include <stdexcept>
#include <opencv2/opencv.hpp>
#include "img.hpp"

namespace img {

 
Image::Image(const std::string& jpg_path)
: m_pixels(1, 1)
, m_img_size(1, 1)
{
    cv::Mat img = cv::imread(jpg_path, cv::IMREAD_COLOR);
    if (img.empty()) {
        throw std::runtime_error("Failed to load image: " + jpg_path);
    }

    m_img_size = { static_cast<size_t>(img.rows), static_cast<size_t>(img.cols) };

    m_pixels = Matrix<RGB>(m_img_size.first, m_img_size.second);

    for (uint8_t i = 0; i < img.rows; ++i) {
        for (uint8_t j = 0; j < img.cols; ++j) {
            cv::Vec3b bgr = img.at<cv::Vec3b>(i, j);
            m_pixels[i][j] = RGB{
                static_cast<unsigned char>(bgr[2]), // R
                static_cast<unsigned char>(bgr[1]), // G
                static_cast<unsigned char>(bgr[0])  // B
            };
        }
    }
}


RGB* Image::operator[](size_t row) noexcept {
    return m_pixels[row];
}

const RGB* Image::operator[](size_t row) const noexcept {
    return m_pixels[row];
}

std::pair<size_t, size_t> Image::get_img_size() const {
    return m_img_size;
}

} // namespace img
