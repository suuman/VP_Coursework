//Suman Raj Bista for Visual Perception course work
//Masters in Computer Vision 3
//University of Burgundy
//calls opencv functions
//does processing

#include "cvfunctions.h"
 #include <QFileDialog>
#include <QList>
#include <QDialog>
#include "options.h"
#include "matcher.h"
#include "CameraCalibrator.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
using namespace std;
CVFunctions::CVFunctions(QObject *parent) :
    QObject(parent)
{
}

Mat CVFunctions::process (const Mat &img_ip,int id)
{
    switch(id){
    case FLIP_HORIZONTAL: return flip(img_ip,1); break;
    case FLIP_VERTICAL: return flip(img_ip,0); break;
    case FLIP_BOTH: return flip(img_ip,-1); break;
    case ADD_SALT_N_PEPPER: return addSaltnPepperNoise (img_ip); break;
    case LOGO_TOP_RIGHT: return addLogo(img_ip,3); break;
    case LOGO_TOP_LEFT: return addLogo(img_ip,1); break;
    case LOGO_BUTTON_LEFT: return addLogo(img_ip,2); break;
    case LOGO_BUTTON_RIGHT: return addLogo(img_ip,4); break;
    case INVERT_COLOR: return invert(img_ip,id); break;
    case INVERT_GRAY: return invert(img_ip,id); break;
    case TO_GRAY: return convertColorSpace (img_ip,id); break;
    case TO_HSV: return convertColorSpace (img_ip,id); break;
    case TO_HLS: return convertColorSpace (img_ip,id); break;
    case TO_YCrCb: return convertColorSpace (img_ip,id); break;
    case TO_XYZ: return convertColorSpace (img_ip,id); break;
    case TO_CIELab: return convertColorSpace (img_ip,id); break;
    case TO_CIELuv: return convertColorSpace (img_ip,id); break;
    case GRAY_HIST: return calculateHistogram (img_ip,id); break;
    case RED_HIST:  return calculateHistogram (img_ip,id); break;
    case GREEN_HIST: return calculateHistogram (img_ip,id); break;
    case BLUE_HIST: return calculateHistogram (img_ip,id); break;
    case ALL_HIST: return calculateHistogram(img_ip); break;
    case EQUAL_HIST: return equaliseHistogram (img_ip); break;
    case RESIZE : return resizeImage(img_ip);break;
    case ERODE : return erodeImage(img_ip);break;
    case DILATE: return dilateImage(img_ip);break;
    case OPEN: return MorphologyTx (img_ip,id);break;
    case CLOSE: return MorphologyTx (img_ip,id);break;
    case GRADIENT: return MorphologyTx (img_ip,id);break;
    case TOPHAT: return MorphologyTx (img_ip,id);break;
    case BLACKHAT : return MorphologyTx (img_ip,id);break;
    case BLUR : return Filter (img_ip,id);break;
    case MEDIAN : return Filter (img_ip,id);break;
    case GAUSSIAN : return Filter (img_ip,id);break;
    case BILATERAL : return Filter (img_ip,id);break;
    case SHARPEN : return FilterCustom(img_ip,id);break;
    case CUSTOMFILTER : return FilterCustom(img_ip,id);break;
    case SOBEL: return edgeFilter(img_ip,id); break;
    case LAPLACE: return edgeFilter(img_ip,id);break;
    case CANNY: return edgeFilter(img_ip,id);break;
    case NORMALISE: return normaliseImage (img_ip);break;
    case HOUGHLINE: return houghTransform (img_ip,id);break;
    case HOUGHCIRCLE: return houghTransform (img_ip,id);break;
    case CONTOURS: return extractContours(img_ip);break;
    case BOUNDINGBOX:return ShapeDescriptors(img_ip,id);break;
    case MINCIRCLE:return ShapeDescriptors(img_ip,id);break;
    case MINELLIPSE:return ShapeDescriptors(img_ip,id);break;
    case CONVEXHULL:return ShapeDescriptors(img_ip,id);break;
    case MOMENTS:return ShapeDescriptors(img_ip,id);break;
    case THRESHOLD: return thresholdImage (img_ip);break;
    case RECTROT: return ShapeDescriptors(img_ip,id);break;
    case HARIS: return calculateCorners(img_ip);break;
    case FASTFEATURES: return getFASTfeatures(img_ip);break;
    case SURFEATURES:return getSURFfeatures(img_ip);break;
    case SIFTFEATURES: return getSIFTfeatures(img_ip);break;
    case SIFTMATCH: return findMatchesSIFT(img_ip);break;
    case SURFMATCH: return findMatchesSURF(img_ip);break;
    case FUND7P: return calcFundamentalmatrix(img_ip,id);break;
    case FUND8P: return calcFundamentalmatrix(img_ip,id);break;
    case FUNDRANSAC: return calcFundamentalmatrix(img_ip,id);break;
    case HOMOGRAPHY: return calculateHomography(img_ip);break;
    case CALIBRATE: return calibrateCamera(img_ip);break;
    case UNDISTORT: return undistortImage(img_ip);break;

    default: return img_ip;
    }
}

Mat CVFunctions::process(const Mat &img_ip,QList<int> processlist)
{
    Mat im_op = img_ip.clone();
    QList<int>::iterator iter;
    if(!processlist.isEmpty ())
    {
        int i = 0;
        for(iter = processlist.begin ();iter != processlist.end ();iter++)
        {
            im_op = process(im_op,processlist.at(i));
            i++;
        }
    }
  return im_op;
}

Mat CVFunctions::flip(const Mat &img_ip,int direction)
{
     Mat img_op;
     cv::flip(img_ip,img_op,direction);
     return img_op;
}

Mat CVFunctions::addSaltnPepperNoise(const Mat &img_ip)
{
    Mat img = img_ip.clone ();
    for (int k=0; k<no_of_salt_pepper_noises; k++)
    {
        int x = rand()%img.cols;
        int y = rand()%img.rows;

        if (img.channels () == 1) // gray-level image
            img.at<uchar>(y,x)= 255;

        else if (img.channels() == 3) // color image
        {

            img.at<Vec3b>(y,x)[0]= 255;
            img.at<Vec3b>(y,x)[1]= 255;
            img.at<Vec3b>(y,x)[2]= 255;
        }
    }
    return img;
}

Mat CVFunctions::addLogo(const Mat &img_ip, int pos)
{
    Mat t_img = img_ip.clone();
    Mat logo = cv::imread(logofile);

     int r = logo.rows;
     int c = logo.cols;
     int x = 0;
     int y = 0;
     if (logo.cols<t_img.cols && logo.rows<t_img.rows)
     {
     if (pos == 1) { x = 0; y = 0; }
     else if (pos == 2) { x = 0; y = t_img.rows-r;}
     else if (pos == 3) { y = 0; x = t_img.cols-c;}
     else { x = t_img.cols-c;  y = t_img.rows-r; }

    Mat imageROI = t_img(Rect(x,y,c,r));
    logo.copyTo(imageROI,logo);
     }
    return t_img;

}

Mat CVFunctions::invert(const Mat &img_ip, int colorspace)
{
    Mat t_img;
     if(colorspace == INVERT_GRAY){
         if(img_ip.channels ()!= 1)
            cvtColor(img_ip,t_img,CV_BGR2GRAY, 0 );
         else
             t_img = img_ip.clone();
        t_img = 255 - t_img;}
     else{
         t_img = img_ip.clone();
         t_img = Scalar(255,255,255);
         t_img = t_img - img_ip;
     }
     return t_img;
}

Mat CVFunctions::calculateHistogram(const Mat &img_ip,int channel)
{
    Mat t_img;
    MatND hist;
    int r = 0;
    int g = 0;
    int b = 0;

   int histSize[] = {256};
   float hranges[] ={0.0,255.0};

   const float* ranges[1];

    ranges[0] = hranges;

    if(img_ip.channels() == 1){
        t_img = img_ip.clone();
         calcHist (&t_img,1,0,Mat(),hist,1,histSize,ranges);
    }

    else if(channel == BLUE_HIST){
        t_img = img_ip.clone();
        int channels[] = {0};
        calcHist (&t_img,1,channels,Mat(),hist,1,histSize,ranges);
        b = 255;
    }

    else if(channel == GREEN_HIST){
        t_img = img_ip.clone();
        int channels[] = {1};
        calcHist (&t_img,1,channels,Mat(),hist,1,histSize,ranges);
        g = 255;
    }

    else if(channel == RED_HIST){
        t_img = img_ip.clone();
        int channels[] = {2};
        calcHist (&t_img,1,channels,Mat(),hist,1,histSize,ranges);
        r = 255;
    }

    else{
        cvtColor(img_ip,t_img,CV_BGR2GRAY, 0 );
        calcHist (&t_img,1,0,Mat(),hist,1,histSize,ranges);
    }

    double maxVal=0;
    minMaxLoc(hist, 0, &maxVal, 0, 0);

    Mat histImg = Mat(256, 256, CV_8UC3,Scalar::all(255));

       for( int h = 0; h < 256; h++ )
           {
               float binVal = hist.at<float>(h);
               int intensity = cvRound(binVal*250/maxVal);
               line( histImg, Point(h,256),Point(h,256-intensity),Scalar(b,g,r));
           }
    return histImg;
}

Mat CVFunctions::calculateHistogram (const Mat &img_ip)
{
    namedWindow ("Red");
    imshow("Red",calculateHistogram (img_ip,RED_HIST));
    namedWindow ("Green");
    imshow("Green",calculateHistogram (img_ip,GREEN_HIST));
    namedWindow ("Blue");
    imshow("Blue",calculateHistogram (img_ip,BLUE_HIST));
    return( calculateHistogram(img_ip,GRAY_HIST));
}

//Mat CVFunctions::drawHistogram(MatND hist)
//{
//    double maxVal=0;
//    minMaxLoc(hist, 0, &maxVal, 0, 0);

//    Mat histImg = Mat::ones(256, 256, CV_8U)*255;

//       for( int h = 0; h < 256; h++ )
//           {
//               float binVal = hist.at<float>(h);
//               int intensity = cvRound(binVal*240/maxVal);
//               line( histImg, Point(h,256),
//                           Point(h,256-intensity),
//                           Scalar::all(0));
//           }

Mat CVFunctions::equaliseHistogram(const Mat &img_ip)
{

    Mat t_img;
     if(img_ip.channels () != 1){
         vector<Mat> temp;
         cvtColor(img_ip,t_img,CV_BGR2HSV, 0 );
         split(t_img,temp);
         equalizeHist(temp[2], temp[2]);
         merge(temp,t_img);
         cvtColor(t_img,t_img,CV_HSV2BGR);
     }
     else{
         t_img = img_ip.clone();

       equalizeHist(t_img, t_img);
     }
   if(showintermediatewindows){
       namedWindow ("Input Histogram");
       imshow("Input Histogram",calculateHistogram (img_ip,GRAY_HIST));
       namedWindow ("Output Histogram");
       imshow("Output Histogram",calculateHistogram (t_img,GRAY_HIST));
   }

       return t_img;
}

 Mat CVFunctions::convertColorSpace(const Mat &img_ip,int convert )
 {
     Mat t_img;
     vector<Mat> temp;
   if(img_ip.channels () == 1)
       t_img = img_ip.clone();
   else{
     if(convert == TO_GRAY)
        cvtColor(img_ip,t_img,CV_BGR2GRAY, 0 );

     else if(convert == TO_HSV){
         cvtColor(img_ip,t_img,CV_BGR2HSV, 0 );
         split(t_img,temp);
         namedWindow ("HUE",CV_WINDOW_NORMAL);
         imshow("HUE",temp[0]);
         namedWindow ("SATURATION",CV_WINDOW_NORMAL);
         imshow("SATURATION",temp[1]);
         namedWindow ("VALUE",CV_WINDOW_NORMAL);
         imshow("VALUE",temp[2]);
     }

     else if(convert == TO_HLS){
         cvtColor(img_ip,t_img,CV_BGR2HLS, 0 );
         split(t_img,temp);
         namedWindow ("H",CV_WINDOW_NORMAL);
         imshow("H",temp[0]);
         namedWindow ("L",CV_WINDOW_NORMAL);
         imshow("L",temp[1]);
         namedWindow ("S",CV_WINDOW_NORMAL);
         imshow("S",temp[2]);
     }

     else if(convert == TO_YCrCb){
         cvtColor(img_ip,t_img,CV_BGR2YCrCb, 0 );
         split(t_img,temp);
         namedWindow ("Y",CV_WINDOW_NORMAL);
         imshow("Y",temp[0]);
         namedWindow ("Cr",CV_WINDOW_NORMAL);
         imshow("Cr",temp[1]);
         namedWindow ("Cb",CV_WINDOW_NORMAL);
         imshow("Cb",temp[2]);
     }

     else if(convert == TO_XYZ){
         cvtColor(img_ip,t_img,CV_BGR2XYZ, 0 );
         split(t_img,temp);
         namedWindow ("X",CV_WINDOW_NORMAL);
         imshow("X",temp[0]);
         namedWindow ("Y",CV_WINDOW_NORMAL);
         imshow("Y",temp[1]);
         namedWindow ("Z",CV_WINDOW_NORMAL);
         imshow("Z",temp[2]);
    }

     else if(convert == TO_CIELab){
         cvtColor(img_ip,t_img,CV_BGR2Lab, 0 );
         split(t_img,temp);
         namedWindow ("L",CV_WINDOW_NORMAL);
         imshow("L",temp[0]);
         namedWindow ("a",CV_WINDOW_NORMAL);
         imshow("a",temp[1]);
         namedWindow ("b",CV_WINDOW_NORMAL);
         imshow("b",temp[2]);
    }

     else if(convert == TO_CIELuv){
         cvtColor(img_ip,t_img,CV_BGR2Luv, 0 );
         split(t_img,temp);
         namedWindow ("l",CV_WINDOW_NORMAL);
         imshow("l",temp[0]);
         namedWindow ("u",CV_WINDOW_NORMAL);
         imshow("u",temp[1]);
         namedWindow ("v",CV_WINDOW_NORMAL);
         imshow("v",temp[2]);
    }
    else
         t_img = img_ip.clone ();
   }

     return t_img;
}

 Mat CVFunctions::resizeImage (const Mat &img_ip)
 {
     Mat t_img = img_ip;
     double w = t_img.cols;
     double h = t_img.rows;
     if(!resizebypc){
     if(h >= w) { w = w/h*height;h = height;}
     else {h = h/w*width; w = width;}
     }
     else{
         w = w*resizepc;
         h = h*resizepc;
     }

     resize(img_ip,t_img,Size(w,h),0,0,INTER_CUBIC);
     QString resfile = imfile;
     resfile.insert(resfile.length ()-4,QString("_resized"));
     cv::imwrite(resfile.toStdString (),t_img);
     return t_img;
 }

 Mat CVFunctions::erodeImage(const Mat &img_ip)
 {
     Mat t_img;

     if(erodelem>=0 && erodelem<3){
       Mat element = getStructuringElement( erodelem,Size( 2*erodesize + 1, 2*erodesize+1 ),
                                            Point( erodesize, erodesize ));
       erode(img_ip,t_img,element,Point(-1,-1),erodeiterno);
     }
    else
     erode(img_ip,t_img,Mat(),Point(-1,-1),erodeiterno);
      return t_img;
 }

 Mat CVFunctions::dilateImage(const Mat &img_ip)
 {
     Mat t_img;
     if(dilatelem>=0 && dilatelem<3){
       Mat element = getStructuringElement(dilatelem,Size( 2*dilatesize + 1, 2*dilatesize+1 ),
                                            Point(dilatesize,dilatesize));
       dilate(img_ip,t_img,element,Point(-1,-1),dilateiterno);
     }
     else
      dilate(img_ip,t_img,Mat(),Point(-1,-1),dilateiterno);
      return t_img;
 }

Mat CVFunctions::MorphologyTx(const Mat &img_ip,int id)
{
   Mat t_img;
   int operation = id - OPEN + 2;
    if(morphelem>=0 && morphelem<3){
       Mat element = getStructuringElement( morphelem, Size( 2*morphsize + 1, 2*morphsize+1 ), Point( morphsize, morphsize ) );
        morphologyEx(img_ip,t_img, operation, element );
    }
    else
       morphologyEx(img_ip,t_img,operation,Mat(),Point(-1,-1));
    return t_img;
}

Mat CVFunctions::Filter(const Mat &img_ip,int id)
{
    Mat t_img;
    if(id == BLUR)
        blur(img_ip,t_img,Size(mean_filter_size,mean_filter_size));
    else if(id == MEDIAN)
            medianBlur(img_ip,t_img,median_filter_size);
    else if(id == GAUSSIAN)
        GaussianBlur(img_ip,t_img,Size(gaussian_filter_size,gaussian_filter_size),sigmaX,sigmaY);
    else if(id == BILATERAL)
        bilateralFilter (img_ip,t_img,bilateralfilter_diam,sigmacolor,sigmaspace);
    else
        t_img = img_ip;

    return t_img;
}

 Mat CVFunctions::FilterCustom(const Mat & img_ip,int id)
 {
    Mat t_img;
     Mat temp;
    if(img_ip.channels () == 1){
        t_img = img_ip.clone();
        if(id==SHARPEN){
            Mat masksharpen(3,3,CV_64F,Scalar(-1/9));
            masksharpen.at<double>(1,1)+=2;
            filter2D(img_ip,t_img,-1,filtermask,Point(-1,1));
            t_img += img_ip;
        }
        else{
            filter2D (img_ip,t_img,CV_16S,filtermask,Point(-1,1),offset);
            t_img.convertTo (t_img,CV_8U);
        }
    }


    else
    {
        cvtColor(img_ip,t_img,CV_BGR2HSV, 0 );
       vector<Mat> temp;
        Mat t2;
        split(t_img,temp);
        if(id==SHARPEN){
            Mat masksharpen(3,3,CV_64F,Scalar(-1/9));
            masksharpen.at<double>(1,1)+=2;
            filter2D(temp[2],t2,-1,filtermask,Point(-1,1));
            temp[2] += t2;
            merge(temp,t_img);
            cvtColor(t_img,t_img,CV_HSV2BGR, 0 );
        }
        else {
            filter2D (img_ip,t_img,CV_16S,filtermask,Point(-1,1),offset);
            t_img.convertTo (t_img,CV_8U);
        }
}
    return t_img;
 }
 Mat CVFunctions:: edgeFilter(const Mat &img_ip, int id)
 {
    Mat t_img;
    Mat x_grad;
    Mat y_grad;
     if(id == SOBEL){
         if(sobeldir <=0){
            Sobel (img_ip,t_img,CV_16S,1,0,sobelkersize,sobelscale,sobeloffset);
            convertScaleAbs(t_img,x_grad);}
          if(sobeldir >=0){
             Sobel (img_ip,t_img,CV_16S,0,1,sobelkersize,sobelscale,sobeloffset);
              convertScaleAbs(t_img,y_grad);}

          if(sobeldir == 0)
               addWeighted(x_grad,0.5,y_grad,0.5,0,t_img);
          else if(sobeldir <0)
                  t_img = x_grad;
          else
                t_img = y_grad;
     }
     else if(id==LAPLACE){
             Laplacian(img_ip,t_img,CV_16S,laplacekernelsize,laplacescale,laplaceoffset);
              convertScaleAbs(t_img,t_img);
     }
     else{
         if(img_ip.channels () !=1){
             cvtColor(img_ip,t_img,CV_BGR2GRAY);
              Canny(t_img,t_img,lowThreshold,upperThreshold,kernel_size,L2gradient);
         }
         else
            Canny(img_ip,t_img,lowThreshold,upperThreshold,kernel_size,L2gradient);
     }

     return t_img;
 }

    Mat CVFunctions::normaliseImage(const Mat &img_ip)
    {
        Mat t_img ;
        double min, max;
        if(img_ip.channels ()==1)
           minMaxLoc(img_ip,&min,&max);
        else{
            Mat temp;
            cvtColor(img_ip,temp,CV_BGR2GRAY, 0 );
             minMaxLoc(temp,&min,&max);
        }
        img_ip.convertTo(t_img,CV_8U,255/max);
     return t_img;
    }

Mat CVFunctions::houghTransform(const Mat &img_ip,int id)
{
    Mat t_img;
    if(img_ip.channels () !=1)
        cvtColor(img_ip,t_img,CV_BGR2GRAY);
    else
       t_img = img_ip.clone();

    if(id == HOUGHLINE){



        if(probhoughline)
        {
            vector<Vec4i> lines;
            HoughLinesP(t_img, lines, rho, theta, houghthres, houghminlinelength,houghminlinegap);
             t_img = ip_image.clone ();
         for( size_t i = 0; i < lines.size(); i++ )
                {
                  Vec4i l = lines[i];
                  line(t_img, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,255,255), 1, CV_AA);
                }
        }
        else
        {
             vector<Vec2f> lines;
            HoughLines(t_img, lines, rho, theta, houghthres, 0, 0 );
             t_img = ip_image.clone ();
             int fac = (ip_image.rows>ip_image.cols ? ip_image.rows:ip_image.cols);

              for( size_t i = 0; i < lines.size(); i++ )
              {
                 float rho = lines[i][0], theta = lines[i][1];
                 Point pt1, pt2;
                 double a = cos(theta), b = sin(theta);
                 double x0 = a*rho, y0 = b*rho;
                 pt1.x = cvRound(x0 + fac*(-b));
                 pt1.y = cvRound(y0 + fac*(a));
                 pt2.x = cvRound(x0 - fac*(-b));
                 pt2.y = cvRound(y0 - fac*(a));
                 line(t_img, pt1, pt2, Scalar(255,255,255), 1, CV_AA);
              }
        }

}

    else{
         vector<Vec3f> circles;
         double distmin;
         if(hcmimdist <=1) distmin = img_ip.rows/10; else distmin = hcmimdist;
         HoughCircles(t_img, circles, CV_HOUGH_GRADIENT, dp, distmin, param1, param2, minradius, maxradius );
          t_img = ip_image.clone ();

         for( size_t i = 0; i < circles.size(); i++ )
           {
               Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
               int radius = cvRound(circles[i][2]);
               // circle center
               circle(t_img, center, 3, Scalar(0,255,0), -1, 8, 0 );
               // circle outline
               circle(t_img, center, radius, Scalar(255,255,255), 2, 8, 0 );
            }

    }

    return t_img;
}

Mat CVFunctions::extractContours (const Mat &img_ip)
{
    Mat t_img;
    if(img_ip.channels () !=1)
        cvtColor(img_ip,t_img,CV_BGR2GRAY);
    else
       t_img = img_ip.clone();


      vector<vector<Point> > contours;
      vector<Vec4i> hierarchy;

    /// Find contours
      findContours(t_img, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

      /// Draw contours
      RNG rng(12345);
      t_img = ip_image.clone ();

      for( int i = 0; i< contours.size(); i++ )
         {
          Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
          drawContours( t_img, contours, i, color, 2, 8, hierarchy, 0, Point() );
         }

      return t_img;

}

Mat CVFunctions::ShapeDescriptors(const Mat &img_ip,int id)
{

    Mat t_img;
    if(img_ip.channels () !=1)
        cvtColor(img_ip,t_img,CV_BGR2GRAY);
    else
       t_img = img_ip.clone();


      vector<vector<Point> > contours;
      vector<Vec4i> hierarchy;


      /// Find contours
      findContours(t_img, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

      /// Approximate contours to polygons + get bounding rects and circles
      vector<vector<Point> > contours_poly( contours.size() );
      vector<Rect> boundRect( contours.size() );
      vector<RotatedRect> minRect( contours.size() );
      vector<RotatedRect> minEllipse( contours.size() );
      vector<Point2f>center( contours.size() );
      vector<float>radius( contours.size() );
       vector<vector<Point> >hull( contours.size() );
        vector<Moments> mu(contours.size() );
         vector<Point2f> mc( contours.size() );

         RNG rng(12345);
        t_img = ip_image.clone ();
      for( int i = 0; i < contours.size(); i++ )
         {
          approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
           Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
          if(id == BOUNDINGBOX){
            boundRect[i] = boundingRect( Mat(contours_poly[i]) );
            rectangle( t_img, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
          }
          else if(id == MINCIRCLE){
            minEnclosingCircle( contours_poly[i], center[i], radius[i] );
            circle( t_img, center[i], (int)radius[i], color, 2, 8, 0 );
           }
          else if(id == MINELLIPSE){
              if( contours[i].size() > 5 ){
                        minEllipse[i] = fitEllipse( Mat(contours[i]) );
                         ellipse( t_img, minEllipse[i], color, 2, 8 );
              }
          }
          else if(id == RECTROT){
                minRect[i] = minAreaRect( Mat(contours[i]) );
                Point2f rect_points[4]; minRect[i].points( rect_points );
                       for( int j = 0; j < 4; j++ )
                          line( t_img, rect_points[j], rect_points[(j+1)%4], color, 2, 8 );
              }
          else if(id == CONVEXHULL){
                  convexHull( Mat(contours[i]), hull[i], false );
                   drawContours( t_img, hull, i, color, 2, 8, vector<Vec4i>(), 0, Point() );
         }
          else{
                  mu[i] = moments( contours[i], false );
                   mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 );
                   drawContours(t_img, contours, i, color, 2, 8, hierarchy, 0, Point() );
                   circle(t_img, mc[i], 2, color, -1, 8, 0 );
          }
      }
 return t_img;
}

Mat CVFunctions::thresholdImage(const Mat &img_ip)
{
    Mat t_img;
    if(img_ip.channels () !=1)
        cvtColor(img_ip,t_img,CV_BGR2GRAY);
    else
       t_img = img_ip.clone();


   threshold(t_img, t_img, thres, 255, THRESH_BINARY );
   return t_img;
}

Mat CVFunctions::calculateCorners(const Mat &img_ip)
{

    Mat t_img;
    if(img_ip.channels () !=1)
        cvtColor(img_ip,t_img,CV_BGR2GRAY);
    else
       t_img = img_ip.clone();



      Mat dst;
        dst = Mat::zeros( img_ip.size(), CV_32FC1 );



          /// Detecting corners
          cornerHarris( t_img, dst, harrisblockSize, harrisapertureSize,harrisk, BORDER_DEFAULT );
          normalize( dst, dst, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
            t_img = ip_image.clone ();
          /// Normalizing
          if(!nonmaximalsupression) {

          /// Drawing a circle around corners
          for( int j = 0; j < dst.rows ; j++ )
             { for( int i = 0; i < dst.cols; i++ )
                  {
                    if( (int) dst.at<float>(j,i) > harristhreshold )
                      {
                       circle( t_img, Point( i, j ), 5,  Scalar(255,0,0), 2, 8, 0 );
                      }
                  }
             }
          }
          else{
              Mat temp; // temporary image
              Mat maximg;
              dilate(dst,temp,cv::Mat());
              cv::compare(dst,temp,maximg,cv::CMP_EQ);
              threshold(dst,temp,harristhreshold,255,THRESH_BINARY);
              temp.convertTo(dst,CV_8U);
              maximg.convertTo (temp,CV_8U);
              bitwise_and(dst,temp,dst);
              for( int j = 0; j < dst.rows ; j++ )
                 { for( int i = 0; i < dst.cols; i++ )
                      {
                        if(dst.at<uchar>(j,i) )
                          {
                           circle( t_img, Point( i, j ), 5,  Scalar(255,0,0), 2, 8, 0 );
                          }
                      }
                 }
          }




      return t_img;
}

Mat CVFunctions::getFASTfeatures (const Mat &img_ip)
{
    std::vector<KeyPoint> keypoints;
    Mat t_img = ip_image.clone();
    // Construction of the Fast feature detector object
    FastFeatureDetector fast(fastthreshold); // threshold for detection
    // feature point detection
    fast.detect(img_ip,keypoints);
    drawKeypoints(t_img,keypoints,t_img, Scalar(255,255,255), DrawMatchesFlags::DRAW_OVER_OUTIMG);
     return t_img;
}

Mat CVFunctions::getSURFfeatures(const Mat &img_ip)
{
    // vector of keypoints
    std::vector<cv::KeyPoint> keypoints;
    // Construct the SURF feature detector object
    SurfFeatureDetector surf(hessianthreshold); // threshold
    // Detect the SURF features
    surf.detect(img_ip,keypoints);
    Mat t_img = ip_image.clone();
    if(!keypoints.empty ())
    drawKeypoints(t_img,keypoints,t_img,Scalar(255,255,255),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS); //flag
    return t_img;
}

 Mat CVFunctions::getSIFTfeatures(const Mat &img_ip)
 {
    std::vector<cv::KeyPoint> keypoints;
    SiftFeatureDetector sift;
    sift.detect(img_ip,keypoints);
    Mat t_img = ip_image.clone();
    drawKeypoints(t_img,keypoints,t_img,Scalar(255,255,255),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS); //flag
    return t_img;
 }

 Mat CVFunctions::findMatchesSURF(const Mat &img_ip)
 {
     SurfFeatureDetector detector(hessianthreshold);
     std::vector<KeyPoint> keypoints_1, keypoints_2;

       detector.detect( img_ip, keypoints_1 );
       detector.detect( ip_image2, keypoints_2 );

       //-- Step 2: Calculate descriptors (feature vectors)
       SurfDescriptorExtractor extractor;

       Mat descriptors_1, descriptors_2;

       extractor.compute( img_ip, keypoints_1, descriptors_1 );
       extractor.compute( ip_image2, keypoints_2, descriptors_2 );

       //-- Step 3: Matching descriptor vectors with a brute force matcher
       BruteForceMatcher< L2<float> > matcher;
       std::vector< DMatch > matches;
       matcher.match( descriptors_1, descriptors_2, matches );
       if(matchesno >0 && matchesno<matches.size ()){
           std::nth_element(matches.begin(), // initial position
           matches.begin()+matchesno, // position of the sorted element
           matches.end()); // end position
           // remove all elements after the 25th
           matches.erase(matches.begin()+matchesno+1, matches.end());
       }


       //-- Draw matches
       Mat t_img;
       drawMatches( ip_image, keypoints_1, ip_image2, keypoints_2, matches, t_img );
       return t_img;

 }

 Mat CVFunctions::findMatchesSIFT(const Mat &img_ip)
 {
     SiftFeatureDetector detector;
     std::vector<KeyPoint> keypoints_1, keypoints_2;

       detector.detect( img_ip, keypoints_1 );
       detector.detect( ip_image2, keypoints_2 );

       //-- Step 2: Calculate descriptors (feature vectors)
       SiftDescriptorExtractor extractor;

       Mat descriptors_1, descriptors_2;

       extractor.compute( img_ip, keypoints_1, descriptors_1 );
       extractor.compute( ip_image2, keypoints_2, descriptors_2 );

       //-- Step 3: Matching descriptor vectors with a brute force matcher
       BruteForceMatcher< L2<float> > matcher;
       std::vector< DMatch > matches;
       matcher.match( descriptors_1, descriptors_2, matches );

       if(matchesno >0 && matchesno<matches.size ()){
           std::nth_element(matches.begin(), // initial position
           matches.begin()+matchesno, // position of the sorted element
           matches.end()); // end position
           // remove all elements after the 25th
           matches.erase(matches.begin()+matchesno+1, matches.end());
       }

       //-- Draw matches
       Mat t_img;
       drawMatches( ip_image, keypoints_1, ip_image2, keypoints_2, matches, t_img );
       return t_img;

 }

 Mat CVFunctions::calcFundamentalmatrix(const Mat &img_ip,int id)
 {
         RobustMatcher rmatcher;
         rmatcher.setConfidenceLevel(0.98);
         rmatcher.setMinDistanceToEpipolar(1.0);
         rmatcher.setRatio(0.65f);
         Ptr<FeatureDetector> pfd= new SurfFeatureDetector(10);
         rmatcher.setFeatureDetector(pfd);

         // Match the two images
         std::vector<DMatch> matches;
         std::vector<KeyPoint> keypoints1, keypoints2;
         fundemental= rmatcher.match(ip_image,ip_image2,matches, keypoints1, keypoints2,id);
         cout<<fundemental<<endl;
         // draw the matches
     if(showintermediatewindows){
         Mat imageMatches;
         drawMatches(ip_image,keypoints1,ip_image2,keypoints2,matches,imageMatches,Scalar(255,255,255));
         namedWindow("Matches",WINDOW_AUTOSIZE);
         imshow("Matches",imageMatches);
      }
         // Convert keypoints into Point2f
         std::vector<cv::Point2f> points1, points2;
         Mat image1 = ip_image.clone();
         Mat image2 = ip_image2.clone();
         for (std::vector<cv::DMatch>::const_iterator it= matches.begin();
                  it!= matches.end(); ++it) {

                  // Get the position of left keypoints
                  float x= keypoints1[it->queryIdx].pt.x;
                  float y= keypoints1[it->queryIdx].pt.y;
                  points1.push_back(cv::Point2f(x,y));
                  circle(image1,cv::Point(x,y),3,cv::Scalar(255,255,255),3);
                  // Get the position of right keypoints
                  x= keypoints2[it->trainIdx].pt.x;
                  y= keypoints2[it->trainIdx].pt.y;
                  circle(image2,cv::Point(x,y),3,cv::Scalar(255,255,255),3);
                  points2.push_back(cv::Point2f(x,y));
         }

         // Draw the epipolar lines
         std::vector<cv::Vec3f> lines1;
         computeCorrespondEpilines(Mat(points1),1,fundemental,lines1);

         for (vector<cv::Vec3f>::const_iterator it= lines1.begin();
              it!=lines1.end(); ++it) {

              line(image2,cv::Point(0,-(*it)[2]/(*it)[1]),Point(image2.cols,-((*it)[2]+(*it)[0]*image2.cols)/(*it)[1]),Scalar(255,255,255));
         }

         std::vector<cv::Vec3f> lines2;
         computeCorrespondEpilines(Mat(points2),2,fundemental,lines2);

         for (vector<cv::Vec3f>::const_iterator it= lines2.begin();
          it!=lines2.end(); ++it) {

          line(image1,Point(0,-(*it)[2]/(*it)[1]),Point(image1.cols,-((*it)[2]+(*it)[0]*image1.cols)/(*it)[1]),Scalar(255,255,255));
         }

         ip_pp  = image1.clone();
    return image2;
 }

 Mat CVFunctions::calculateHomography(const Mat &img_ip)
 {
     //-- Step 1: Detect the keypoints using SURF Detector
       int minHessian = 400;

       SurfFeatureDetector detector( minHessian );

       std::vector<KeyPoint> keypoints_object, keypoints_scene;

       Mat img_object = ip_image.clone();
       Mat img_scene = ip_image2.clone();

       detector.detect( img_object, keypoints_object );
       detector.detect( img_scene, keypoints_scene );

       //-- Step 2: Calculate descriptors (feature vectors)
       SurfDescriptorExtractor extractor;

       Mat descriptors_object, descriptors_scene;

       extractor.compute( img_object, keypoints_object, descriptors_object );
       extractor.compute( img_scene, keypoints_scene, descriptors_scene );

       //-- Step 3: Matching descriptor vectors using FLANN matcher

       FlannBasedMatcher matchers;
       std::vector< DMatch > matches;
       matchers.match( descriptors_object, descriptors_scene, matches );

       double max_dist = 0; double min_dist = 100;

       //-- Quick calculation of max and min distances between keypoints
       for( int i = 0; i < descriptors_object.rows; i++ )
       { double dist = matches[i].distance;
         if( dist < min_dist ) min_dist = dist;
         if( dist > max_dist ) max_dist = dist;
       }

       printf("-- Max dist : %f \n", max_dist );
       printf("-- Min dist : %f \n", min_dist );

       //-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
       std::vector< DMatch > good_matches;

       for( int i = 0; i < descriptors_object.rows; i++ )
       { if( matches[i].distance < 3*min_dist )
          { good_matches.push_back( matches[i]); }
       }

       Mat img_matches;
       drawMatches( img_object, keypoints_object, img_scene, keypoints_scene,
                    good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
                    vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

       //-- Localize the object
       std::vector<Point2f> obj;
       std::vector<Point2f> scene;

       for( int i = 0; i < good_matches.size(); i++ )
       {
         //-- Get the keypoints from the good matches
         obj.push_back( keypoints_object[ good_matches[i].queryIdx ].pt );
         scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );
       }

       homography = findHomography( obj, scene, CV_RANSAC );
        cout<<homography<<endl;

       //-- Get the corners from the image_1 ( the object to be "detected" )
       std::vector<Point2f> obj_corners(4);
       obj_corners[0] = cvPoint(0,0); obj_corners[1] = cvPoint( img_object.cols, 0 );
       obj_corners[2] = cvPoint( img_object.cols, img_object.rows ); obj_corners[3] = cvPoint( 0, img_object.rows );
       std::vector<Point2f> scene_corners(4);

       perspectiveTransform( obj_corners, scene_corners, homography);

       //-- Draw lines between the corners (the mapped object in the scene - image_2 )
       line( img_matches, scene_corners[0] + Point2f( img_object.cols, 0), scene_corners[1] + Point2f( img_object.cols, 0), Scalar(0, 255, 0), 4 );
       line( img_matches, scene_corners[1] + Point2f( img_object.cols, 0), scene_corners[2] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );
       line( img_matches, scene_corners[2] + Point2f( img_object.cols, 0), scene_corners[3] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );
       line( img_matches, scene_corners[3] + Point2f( img_object.cols, 0), scene_corners[0] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );

       Mat result;
       cv::warpPerspective(img_object, // input image
                               result, // output image
                               homography, // homography
                               cv::Size(2*img_object.cols,
                                        img_object.rows)); // size of output image
       cv::Mat half(result,cv::Rect(0,0,img_scene.cols,img_scene.rows));
          img_scene.copyTo(half); // copy image2 to image1 roi


      return result;


 }

Mat CVFunctions::calibrateCamera(const Mat &img_ip)
{


    cv::Mat image;
    std::vector<std::string> filelist;
    // generate list of chessboard image filename
    for (int i=0; i<calibrationimages.length (); i++) {

        std::stringstream str;
        str << calibrationfolder.toStdString ()<<"\\" <<calibrationimages.at(i).toStdString ();
        std::cout << str.str() << std::endl;

        filelist.push_back(str.str());
        image= cv::imread(str.str(),0);
    }

    ip_pp  = image.clone();

    // Create calibrator object
    CameraCalibrator cameraCalibrator;
    // add the corners from the chessboard
    cv::Size boardSize(broadlength,broadwidth);
   int success = 0;
   success = cameraCalibrator.addChessboardPoints(filelist,boardSize,showintermediatewindows);
   std::cout<<"success = "<<success;
        // calibrate the camera
    calstatus = false;
   if(success>0){
        //cameraCalibrator.setCalibrationFlag(true,true);

         cv::Size imsize = image.size();

         cameraCalibrator.calibrate(imsize);

        cameraMatrix= cameraCalibrator.getCameraMatrix();
        distCoeffs = cameraCalibrator.getDistCoeffs ();
       calstatus = true;
        image = cameraCalibrator.remapimage(image);

        QString opfilename = calibrationfolder;
        opfilename.append ("\\calibrationmatrix.txt" );
        QFile file(opfilename);
         file.open(QIODevice::WriteOnly | QIODevice::Text);


          if (file.isOpen ())
          {
              QTextStream out(&file);
              out << " Camera intrinsic: " << cameraMatrix.rows << "x" << cameraMatrix.cols << "\n";
                  out << cameraMatrix.at<double>(0,0) << " " << cameraMatrix.at<double>(0,1) << " " << cameraMatrix.at<double>(0,2) << endl;
                  out << cameraMatrix.at<double>(1,0) << " " << cameraMatrix.at<double>(1,1) << " " << cameraMatrix.at<double>(1,2) << endl;
                  out << cameraMatrix.at<double>(2,0) << " " << cameraMatrix.at<double>(2,1) << " " << cameraMatrix.at<double>(2,2) << endl;
            file.close();
          }


       if(showintermediatewindows)
       {
            namedWindow("Corners on Chessboard",CV_WINDOW_AUTOSIZE );
            destroyWindow ("Corners on Chessboard");
       }
    }


    return  image;
}

Mat CVFunctions::undistortImage(const Mat &img_ip)
{
    // Create calibrator object
    CameraCalibrator cameraCalibrator(cameraMatrix,distCoeffs);
    Mat uImage= cameraCalibrator.remapimage(img_ip);
    return uImage;

}
