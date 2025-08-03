// Main GUI headerfile
//modified By Suman Raj Bista for Visual Perception course work
//Masters in Computer Vision 3
//University of Burgundy

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
\*------------------------------------------------------------------------------------------*/

#include "CameraCalibrator.h"

// Open chessboard images and extract corner points


int CameraCalibrator::addChessboardPoints(
         const std::vector<std::string>& filelist, 
         cv::Size & boardSize,bool showflag) {

	// the points on the chessboard
    std::vector<cv::Point2f> imageCorners;
    std::vector<cv::Point3f> objectCorners;

    // 3D Scene Points:
    // Initialize the chessboard corners 
    // in the chessboard reference frame
	// The corners are at 3D location (X,Y,Z)= (i,j,0)
	for (int i=0; i<boardSize.height; i++) {
		for (int j=0; j<boardSize.width; j++) {

            objectCorners.push_back(cv::Point3f(i, j, 0.0f));
		}
    }

    // 2D Image points:
    cv::Mat image; // to contain chessboard image
    int successes = 0;
    // for all viewpoints
    for (unsigned int i=0; i<filelist.size(); i++) {

        // Open the image
        image = cv::imread(filelist[i],0);

         //Get the chessboard corners //replaced this function from original one
        bool found = findChessboardCorners(image, boardSize, imageCorners,
                                               cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE
                                               + cv::CALIB_CB_FAST_CHECK);

        if(found){ //aaded this
        // Get subpixel accuracy on the corners
        cornerSubPix(image, imageCorners, cv::Size(11,11),cv::Size(-1,-1),
            cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 30,0.1));
          // If we have a good board, add it to our data
		  if (imageCorners.size() == boardSize.area()) {

			// Add image and scene points from one view
            addPoints(imageCorners, objectCorners);
            successes++;
          }
          if(showflag){
        //Draw the corners
        drawChessboardCorners(image, boardSize, imageCorners, found);
        imshow("Corners on Chessboard", image);
        cv::waitKey(100);
          }
        }

    }
    std::cout<<"success = "<<successes<<std::endl;
	return successes;
}

// Add scene points and corresponding image points
void CameraCalibrator::addPoints(const std::vector<cv::Point2f>& imageCorners, const std::vector<cv::Point3f>& objectCorners) {

	// 2D image points from one view
	imagePoints.push_back(imageCorners);          
	// corresponding 3D scene points
	objectPoints.push_back(objectCorners);
}

// Calibrate the camera
// returns the re-projection error
double CameraCalibrator::calibrate(cv::Size &imageSize)
{
	// undistorter must be reinitialized
	mustInitUndistort= true;

	//Output rotations and translations
    std::vector<cv::Mat> rvecs, tvecs;

	// start calibration
	return 
     calibrateCamera(objectPoints, // the 3D points
		            imagePoints,  // the image points
					imageSize,    // image size
					cameraMatrix, // output camera matrix
					distCoeffs,   // output distortion matrix
					rvecs, tvecs, // Rs, Ts 
					flag);        // set options
//					,CV_CALIB_USE_INTRINSIC_GUESS);

}

// remove distortion in an image (after calibration)
cv::Mat CameraCalibrator::remapimage(const cv::Mat &image) {

cv::Mat undistorted;

	if (mustInitUndistort) { // called once per calibration


       cv::Mat undistCammatrix = getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, image.size(), 1, image.size(),0);
            initUndistortRectifyMap(
			cameraMatrix,  // computed camera matrix
            distCoeffs,    // computed distortion matrix
            cv::Mat(),     // optional rectification (none)
            undistCammatrix,
            image.size(),  // size of undistorted
            CV_32FC1,      // type of output map
            map1, map2);   // the x and y mapping functions

		mustInitUndistort= false;
	}

	// Apply mapping functions
    remap(image, undistorted, map1, map2,
        cv::INTER_CUBIC); // interpolation type

	return undistorted;
}


// Set the calibration options
// 8radialCoeffEnabled should be true if 8 radial coefficients are required (5 is default)
// tangentialParamEnabled should be true if tangeantial distortion is present
void CameraCalibrator::setCalibrationFlag(bool radial8CoeffEnabled, bool tangentialParamEnabled) {

    // Set the flag used in cv::calibrateCamera()

    flag = 0;
    if (!tangentialParamEnabled) flag += cv::CALIB_ZERO_TANGENT_DIST;
    if (radial8CoeffEnabled) flag += cv::CALIB_RATIONAL_MODEL;
}

