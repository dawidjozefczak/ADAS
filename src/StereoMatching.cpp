#include <StereoMatching.hpp>

StereoMatching::StereoMatching(StereoCamParam_t&  objStereoParam) {
    SetParamOCVStereo(objStereoParam);
}

StereoMatching::StereoMatching(cv::Mat& imgLeftInput, cv::Mat& imgRightInput, StereoCamParam_t& objStereoParam) {
    imgLeftInput_ = imgLeftInput;
    imgRightInput_ = imgRightInput;
    SetParamOCVStereo(objStereoParam);
}

StereoMatching::StereoMatching(cv::Mat imgLeftInput, cv::Mat imgRightInput) {
    imgLeftInput_ = imgLeftInput;
    imgRightInput_ = imgRightInput;
    // SetParamOCVStereo();
    
}

// void StereoMatching::SetParamOCVStereo() {
//     bm->create(objStereoParam_.m_nNumberOfDisp, objStereoParam_.m_nWindowSize);

//     // bm->setPreFilterCap(31);
// 	// bm->setBlockSize(m_objStereoParam.m_nWindowSize > 0 ? m_objStereoParam.m_nWindowSize : 9);
// 	// bm->setMinDisparity(0);
// 	// bm->setNumDisparities(m_objStereoParam.m_nNumberOfDisp);
// 	// bm->setTextureThreshold(10);		/// SAD window response threshold : default=12
// 	// bm->setUniquenessRatio(5);			/// >(match_val - min_match)/min_match
// 	// bm->setSpeckleWindowSize(100);		//25;//9;
// 	// bm->setSpeckleRange(32);			//4;
// 	// //bm->setSmallerBlockSize(9);
// 	// //bm->setDisp12MaxDiff(1);
// }

void StereoMatching::SetParamOCVStereo(StereoCamParam_t& objStereoParam) {
    objStereoParam_ = objStereoParam;
    bm->create(objStereoParam_.m_nNumberOfDisp, objStereoParam_.m_nWindowSize);

    // bm->setPreFilterCap(31);
	// bm->setBlockSize(m_objStereoParam.m_nWindowSize > 0 ? m_objStereoParam.m_nWindowSize : 9);
	// bm->setMinDisparity(0);
	// bm->setNumDisparities(m_objStereoParam.m_nNumberOfDisp);
	// bm->setTextureThreshold(10);		/// SAD window response threshold : default=12
	// bm->setUniquenessRatio(5);			/// >(match_val - min_match)/min_match
	// bm->setSpeckleWindowSize(100);		//25;//9;
	// bm->setSpeckleRange(32);			//4;
	// //bm->setSmallerBlockSize(9);
	// //bm->setDisp12MaxDiff(1);
}

// void StereoMatching::SetImage(cv::Mat& imgLeft, cv::Mat& imgRight) {
//     if(imgLeft.size() != imgRight.size()) { std::cout << "Blad"; }
//     // if(imgLeft.channels() == 3) {
//         cv::cvtColor(imgLeft, imgLeftInput_, cv::COLOR_BGR2GRAY);
//         cv::cvtColor(imgRight, imgRightInput_, cv::COLOR_BGR2GRAY);
//     // }
//     imgLeftInput_ = imgLeft;
//     imgRightInput_ = imgRight;
// }

cv::Mat StereoMatching::EstymateStixels() {
    
}

cv::Mat StereoMatching::MakeDisparity() {
    
    cv::Mat left_for_matcher, right_for_matcher;
    cv::Mat left_disp,right_disp;
    cv::Mat filtered_disp;
    cv::Mat conf_map = cv::Mat(imgLeftInput_.rows, imgLeftInput_.cols, CV_8U);
    conf_map = cv::Scalar(255);
    cv::Rect ROI;
    int max_disp = objStereoParam_.m_nNumberOfDisp; //16
    int wsize = objStereoParam_.m_nWindowSize; //15

    cv::Ptr<cv::ximgproc::DisparityWLSFilter> wls_filter;

    cv::Ptr<cv::StereoBM> left_matecher = cv::StereoBM::create(max_disp, wsize);
    wls_filter = cv::ximgproc::createDisparityWLSFilter(left_matecher);
    cv::Ptr<cv::StereoMatcher> right_matcher = cv::ximgproc::createRightMatcher(left_matecher);
    cv::cvtColor(imgLeftInput_, left_for_matcher, cv::COLOR_BGR2GRAY);
    cv::cvtColor(imgRightInput_, right_for_matcher, cv::COLOR_BGR2GRAY);

    left_matecher->compute(left_for_matcher, right_for_matcher, left_disp);
    right_matcher->compute(right_for_matcher, left_for_matcher, right_disp);

    double lambda = 8000.0;
    double sigma = 1.5;

    wls_filter->setLambda(lambda);
    wls_filter->setSigmaColor(sigma);

    wls_filter->filter(left_disp, imgLeftInput_, filtered_disp, right_disp);

    conf_map = wls_filter->getConfidenceMap();

    ROI = wls_filter->getROI();
    
    //before filltration
    cv::Mat raw_disp_vis;
    cv::ximgproc::getDisparityVis(left_disp, raw_disp_vis, 21.0);
    //after filltration
    cv::Mat filtered_disp_vis;
    cv::ximgproc::getDisparityVis(filtered_disp, filtered_disp_vis, 13.0); //15.0

    // return raw_disp_vis;
    return filtered_disp_vis;
}
    


