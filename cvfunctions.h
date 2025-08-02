//Suman Raj Bista for Visual Perception course work
//Masters in Computer Vision 3
//University of Burgundy
//calls opencv functions

#ifndef CVFUNCTIONS_H
#define CVFUNCTIONS_H

#include <QObject>
#include <QStringList>
#include <opencv2/opencv.hpp>
using namespace cv;

class CVFunctions : public QObject
{
    Q_OBJECT

public:
    explicit CVFunctions(QObject *parent = nullptr);

    Mat process(const Mat &,int);
    Mat process(const Mat &,QList<int>);
    Mat ip_image;
    Mat ip_image2;
    Mat ip_pp;
    QString imfile2;
    int no_of_salt_pepper_noises;
    String logofile;
    QString imfile;
    QString calibrationfolder;
    QStringList calibrationimages;
    bool showintermediatewindows;
    Size dsize;
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
    Mat filtermask;
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
     int matchesno;
     Mat fundemental;
     Mat homography;
     Mat cameraMatrix;
     Mat distCoeffs;
     bool calstatus;
     int broadlength;
     int broadwidth;
     bool resizebypc;
     double resizepc;

signals:
    
public slots:


private:
    Mat flip(const Mat &,int);
    Mat addSaltnPepperNoise(const Mat &);
    Mat addLogo(const Mat &, int);
    Mat invert(const Mat &, int);
    Mat convertColorSpace(const Mat &,int );
    Mat calculateHistogram(const Mat &,int);
    Mat equaliseHistogram(const Mat &);
    Mat calculateHistogram(const Mat &);
    Mat resizeImage(const Mat &);
    Mat erodeImage(const Mat &);
    Mat dilateImage(const Mat &);
    Mat MorphologyTx(const Mat &,int);
    Mat Filter(const Mat &,int);
    Mat FilterCustom(const Mat &,int);
    Mat edgeFilter(const Mat &,int);
    Mat normaliseImage(const Mat &);
    Mat houghTransform(const Mat &,int);
    Mat extractContours(const Mat &);
   Mat ShapeDescriptors(const Mat &,int);
   Mat thresholdImage(const Mat &);
   Mat calculateCorners(const Mat &);
   Mat getFASTfeatures(const Mat &);
   Mat getSURFfeatures(const Mat &);
   Mat getSIFTfeatures(const Mat &);
   Mat findMatchesSURF(const Mat &);
    Mat findMatchesSIFT(const Mat &);
    Mat calcFundamentalmatrix(const Mat &,int);
    Mat calculateHomography(const Mat &);
    Mat calibrateCamera(const Mat &);
    Mat undistortImage(const Mat &);

};

#endif // CVFUNCTIONS_H
