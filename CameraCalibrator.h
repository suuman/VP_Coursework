/*------------------------------------------------------------------------------------------*\
   This file contains material supporting chapter 9 of the cookbook:  
   Computer Vision Programming using the OpenCV Library. 
   by Robert Laganiere, Packt Publishing, 2011.

   This program is free software; permission is hereby granted to use, copy, modify, 
   and distribute this source code, or portions thereof, for any purpose, without fee, 
   subject to the restriction that the copyright notice may not be removed 
   or altered from any source or altered source distribution. 
   The software is released on an as-is basis and without any warranties of any kind. 
   In particular, the software is not guaranteed to be fault-tolerant or free from failure. 
   The author disclaims all warranties with regard to this software, any use, 
   and any consequent failure, is purely the responsibility of the user.
 
   Copyright (C) 2010-2011 Robert Laganiere, www.laganiere.name


//Modified By Suman Raj Bista for Visual Perception course work
//Masters in Computer Vision 3
//University of Burgundy

\*------------------------------------------------------------------------------------------*/

#ifndef CAMERACALIBRATOR_H
#define CAMERACALIBRATOR_H

#include <vector>
#include <opencv2/opencv.hpp>


 class CameraCalibrator {

	// input points
    std::vector<std::vector<cv::Point3f> > objectPoints;
    std::vector<std::vector<cv::Point2f> > imagePoints;
    // output Matrices
    cv::Mat cameraMatrix;
    cv::Mat distCoeffs;
	// flag to specify how calibration is done
	int flag;
	// used in image undistortion 
    cv::Mat map1,map2; 
	bool mustInitUndistort;

  public:
    CameraCalibrator() {flag = 0; mustInitUndistort = true;}
    CameraCalibrator(cv::Mat cammat, cv::Mat distcoeff){  //added for my project
        cameraMatrix = cammat.clone ();
        distCoeffs = distcoeff.clone();
        flag = 0;
        mustInitUndistort = true;
    }
	// Open the chessboard images and extract corner points
    int addChessboardPoints(const std::vector<std::string>& filelist, cv::Size & boardSize,bool showflag);
	// Add scene points and corresponding image points
    void addPoints(const std::vector<cv::Point2f>& imageCorners, const std::vector<cv::Point3f>& objectCorners);
	// Calibrate the camera
    double calibrate(cv::Size &imageSize);
    // Set the calibration flag
    void setCalibrationFlag(bool radial8CoeffEnabled=false, bool tangentialParamEnabled=false);
	// Remove distortion in an image (after calibration)
    cv::Mat remapimage(const cv::Mat &image);

    // Getters
    cv::Mat getCameraMatrix() { return cameraMatrix; }
    cv::Mat getDistCoeffs()   { return distCoeffs; }
};

#endif // CAMERACALIBRATOR_H
