#include <Image.hpp>

Image::Image(std::string imgName){
    image_ = image_read(imgName, cv::IMREAD_COLOR);
}

cv::Mat Image::image_read(std::string directory, size_t count) {
    image_ = cv::imread(directory, 1);
    return image_;
}

cv::Mat Image::get_image() {
    return image_;
}

void Image::image_show(std::string imgName) {
    cv::imshow(imgName, image_);
}
