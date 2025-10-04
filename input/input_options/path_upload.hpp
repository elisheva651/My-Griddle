#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include "abs_get_img.hpp"
#include "../../status.hpp"

class PathUpload : public AbsGetImg
{

public:
    PathUpload() {}
    ~PathUpload() = default;

    Status receive_input() override;

private:
    cv::Mat load_image(const std::string& path);
    void save_image(const cv::Mat& img);
};
