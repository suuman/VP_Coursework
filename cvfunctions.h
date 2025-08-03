//Suman Raj Bista for Visual Perception course work
//Masters in Computer Vision 3
//University of Burgundy
//calls opencv functions

#ifndef CVFUNCTIONS_H
#define CVFUNCTIONS_H

#include <QObject>
#include <QStringList>
#include <opencv2/opencv.hpp>


class CVFunctions : public QObject
{
    Q_OBJECT

public:
    explicit CVFunctions(QObject *parent = nullptr);

    cv::Mat process(const cv::Mat &,int);
    cv::Mat process(const cv::Mat &,QList<int>);
    cv::Mat ip_image;
    cv::Mat ip_image2;
    cv::Mat ip_pp;
    QString imfile2;
    int no_of_salt_pepper_noises;
    cv::String logofile;
    QString imfile;
    QString calibrationfolder;
    QStringList calibrationimages;
    bool showintermediatewindows;
    cv::Size dsize;
    int width;
    int height;
    int erodeiterno;
    int dilateiterno;
    int dilatelem;
    int dilatesize;
    int erodelem;
    int erodesize;
    int morphelem;
    int morphsize;
    int mean_filter_size;
    int median_filter_size;
    int gaussian_filter_size;
    double sigmaX;
    double sigmaY;
    int bilateralfilter_diam;
    double sigmacolor;
    double sigmaspace;
    double offset;
    cv::Mat filtermask;
    int sobeldir;
    int sobelkersize;
    double sobelscale;
    int sobeloffset;
    int laplacekernelsize;
    double laplacescale;
    int laplaceoffset;
    int lowThreshold;
    int upperThreshold;
    double ratio;
    int kernel_size;
    bool L2gradient;
    double houghthres;
    double houghminlinelength;
    double houghminlinegap;
    bool probhoughline;
    double rho;
    double theta;
     double dp,hcmimdist, param1, param2;
     int minradius, maxradius;
     int thres;
     int harrisblockSize ,harrisapertureSize,harristhreshold;
     double harrisk;
     bool nonmaximalsupression;
     int fastthreshold;
     int hessianthreshold;
     unsigned long matchesno;
     cv::Mat fundemental;
     cv::Mat homography;
     cv::Mat cameraMatrix;
     cv::Mat distCoeffs;
     bool calstatus;
     int broadlength;
     int broadwidth;
     bool resizebypc;
     double resizepc;

signals:
    
public slots:


private:
    cv::Mat flip(const cv::Mat &,int);
    cv::Mat addSaltnPepperNoise(const cv::Mat &);
    cv::Mat addLogo(const cv::Mat &, int);
    cv::Mat invert(const cv::Mat &, int);
    cv::Mat convertColorSpace(const cv::Mat &,int );
    cv::Mat calculateHistogram(const cv::Mat &,int);
    cv::Mat equaliseHistogram(const cv::Mat &);
    cv::Mat calculateHistogram(const cv::Mat &);
    cv::Mat resizeImage(const cv::Mat &);
    cv::Mat erodeImage(const cv::Mat &);
    cv::Mat dilateImage(const cv::Mat &);
    cv::Mat MorphologyTx(const cv::Mat &,int);
    cv::Mat Filter(const cv::Mat &,int);
    cv::Mat FilterCustom(const cv::Mat &,int);
    cv::Mat edgeFilter(const cv::Mat &,int);
    cv::Mat normaliseImage(const cv::Mat &);
    cv::Mat houghTransform(const cv::Mat &,int);
    cv::Mat extractContours(const cv::Mat &);
    cv::Mat ShapeDescriptors(const cv::Mat &,int);
    cv::Mat thresholdImage(const cv::Mat &);
    cv::Mat OstuthresholdImage(const cv::Mat &);
    cv::Mat calculateCorners(const cv::Mat &);
    cv::Mat getFASTfeatures(const cv::Mat &);
    cv::Mat getSURFfeatures(const cv::Mat &);
    cv::Mat getSIFTfeatures(const cv::Mat &);
    cv::Mat findMatchesSURF(const cv::Mat &);
    cv::Mat findMatchesSIFT(const cv::Mat &);
    cv::Mat calcFundamentalmatrix(int);
    cv::Mat calculateHomography();
    cv::Mat calibrateCamera();
    cv::Mat undistortImage(const cv::Mat &);

};

#endif // CVFUNCTIONS_H
