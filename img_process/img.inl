#pragma once

#include <iostream>
#include "img.hpp"
#include <vector>

namespace img
{

template <typename T>
Image<T>::Image(const std::string& jpg_path, std::vector<std::pair<T, T>> ranges)
    : range_each_channel_(ranges)
{
    static_assert(!std::is_same<T, uint8_t>::value, "T must not be uint8_t");

    // Load image using OpenCV
    cv::Mat img = cv::imread(jpg_path, cv::IMREAD_COLOR);
    assert(!img.empty() && "Failed to load image");

    // Convert OpenCV BGR to your Matrix<PixelRgb<T>>
    img_size_ = { static_cast<size_t>(img.rows), static_cast<size_t>(img.cols) };
    pixels_ = Matrix<PixelRgb<T>>(img.rows, img.cols); // assuming you have such constructor

    for (int i = 0; i < img.rows; ++i) {
        for (int j = 0; j < img.cols; ++j) {
            cv::Vec3b bgr = img.at<cv::Vec3b>(i, j);
            pixels_(i, j) = PixelRgb<T>{
                static_cast<T>(bgr[2]), // R
                static_cast<T>(bgr[1]), // G
                static_cast<T>(bgr[0])  // B
            };
        }
    }

    assert(img_size_.first > 0 && img_size_.second > 0);
}

template <typename T>
PixelRgb<T> *Image<T>::operator[](size_t row) noexcept
{
    return pixels_[row];
}

template <typename T>
const PixelRgb<T> *Image<T>::operator[](size_t row) const noexcept
{
    return pixels_[row];
}

template <typename T>
std::pair<size_t, size_t> Image<T>::get_img_size() const
{
    return img_size_;
}

template <typename T>
std::vector<std::pair<T, T>> Image<T>::get_ranges() const
{
    return range_each_channel_;
}
    
} // namespace img