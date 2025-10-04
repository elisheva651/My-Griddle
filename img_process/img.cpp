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

Image::Image(const Matrix<RGB> &pixels)
: m_pixels(pixels) // copy the pixel matrix
{
    if (pixels.rows() == 0 || pixels.cols() == 0) {
        throw std::runtime_error("Cannot create Image from empty Matrix");
    }

    m_img_size = { static_cast<size_t>(pixels.rows()), static_cast<size_t>(pixels.cols()) };
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

void Image::save_to_file(const std::string &path) const {
    cv::Mat img_cv(m_img_size.first, m_img_size.second, CV_8UC3);

    for (size_t i = 0; i < m_img_size.first; ++i) {
        for (size_t j = 0; j < m_img_size.second; ++j) {
            const RGB& px = m_pixels[i][j];
            img_cv.at<cv::Vec3b>(i, j) = cv::Vec3b(px.b, px.g, px.r);
        }
    }

    cv::imwrite(path, img_cv);
}

} // namespace img
