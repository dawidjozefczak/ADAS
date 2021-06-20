#pragma once

#include <cstddef>
#include <opencv2/opencv.hpp>
#include <string>
#include <memory>

class Image {
public:
    Image(std::string imgName);
    // Image();
    ~Image() = default;


    // show image 
    void image_show(std::string imgName);
    cv::Mat get_image();
    size_t getAvailableImage() const;

private:
    // read image from directory
    cv::Mat image_read(std::string directory, size_t count); 


    size_t count_;
    // std::unique_ptr<cv::Mat> image_;
    cv::Mat image_;
    std::string directoryName_;

};


