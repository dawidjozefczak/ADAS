#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/ximgproc.hpp>
#include <opencv2/imgcodecs.hpp>
// #include "StrDef.hpp"

struct StereoCamParam_t
{
	int m_nNumberOfDisp; ///< number of disparity.
	int m_nWindowSize; ///< window size. It must be odd number.
	double m_dBaseLine; ///< baseline, unit : meters1
	double m_dMaxDist; ///< Maximum distance value, unit : meters
	// CameraParam_t objCamParam;
	StereoCamParam_t(){
		m_nNumberOfDisp = 80;
		m_nWindowSize = 9;
		m_dBaseLine = 0.;
		m_dMaxDist = 50.0;
	}
};


// typedef enum error { NO_PROB, IMGSIZE_ERR, IMGSCALE_ERR } MATCHING_ERROR;

class StereoMatching
{
private:
    cv::Mat imgLeftInput_;
    cv::Mat imgRightInput_;

    cv::Ptr<cv::StereoBM> bm = cv::StereoBM::create(0,0); //default constructor
    cv::Ptr<cv::ximgproc::DisparityFilter> wls_filter;
    cv::Rect rectFilterROI_;
    StereoCamParam_t objStereoParam_;

    void SetParamOCVStereo(); //Stereo parameter setting
    // MATCHING_ERROR MakeDisparity();
    // void SetImage(cv::Mat& imgLeft, cv::Mat&cimgRight);
    // void ImproveDisparity_WLSFilter(cv::Mat& imgDisp8);
    // MATCHING_ERROR SetImage(cv::Mat& imgLeft, cv::Mat& imgRight);
    
public:
    cv::Mat matDisp16_;
    cv::Mat imgDisp8_;

    StereoMatching(StereoCamParam_t&  objStereoParam);
    StereoMatching(cv::Mat& imgLeftInput, cv::Mat& imgRightInput, StereoCamParam_t& objStereoParam);
    StereoMatching(cv::Mat imgLeftInput, cv::Mat imgRightInput);


    ~StereoMatching() = default;

    void SetParamOCVStereo(StereoCamParam_t& objStereoParam);
    cv::Mat MakeDisparity();
    cv::Mat EstymateStixels();
    
    // MATCHING_ERROR MakeDisparity(cv::Mat& imgLeft, cv::Mat& imgRight, bool flgUseWLSFilter=true);
	// MATCHING_ERROR MakeDisparity(cv::Mat& imgLeft, cv::Mat& imgRight, cv::Mat& matDisp16);
	// MATCHING_ERROR ImproveDisparity_Naive(cv::Mat& imgDisp8);
	// MATCHING_ERROR ImproveDisparity_WLSFilter(cv::Mat& imgDisp8); ///< OCV310 new disparity postprocess
};

