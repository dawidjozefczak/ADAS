#include "Image.hpp"
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
std::string directoryOfImageLeftPath = "/home/dawid/Documents/STEREOVISION/ADAS/L";
std::string directoryOfImageRightPath = "/home/dawid/Documents/STEREOVISION/ADAS/R";


int main() {
    std::cout<<"Hello World\n";

    std::vector<std::string> imRPath;
    std::vector<Image> imR;
    std::vector<std::string> imLPath;
    std::vector<Image> imL;
    
    for(const auto& entry : std::filesystem::directory_iterator(directoryOfImageLeftPath)) {
        std::cout << "LeftImage: " << entry.path() << "\n";     
        imL.push_back(Image(entry.path()));
        imLPath.push_back(entry.path());
    }

     for(const auto& entry : std::filesystem::directory_iterator(directoryOfImageRightPath)) {
        std::cout << "RightImage: " << entry.path() << "\n";
        imR.push_back(Image(entry.path()));
        imRPath.push_back(entry.path());
    }
    
    for(int i = 0; i < 2; i++) {
        imR[i].image_show("prawy");
        imL[i].image_show("lewy");
        waitKey(0);
    }
    return 0;
}