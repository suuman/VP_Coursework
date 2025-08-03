//Suman Raj Bista for Visual Perception course work
//Masters in Computer Vision 3
//University of Burgundy
//MainGUI header file
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>

#include "window_QT.h" //taken from opencv high gui folder
#include <cstdlib>
#include <QThread>
//#include <QLinkedList>
#include "options.h"
#include "cvfunctions.h"
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString imfile;
    QString videofile;
    QString imfile2;
    void updateImage( const cv::Mat &image,int i );
    void updateImage( const QString &str,int i );
    void updateImageSize( const QSize &size,int i);
    cv::Mat readImage(const QString &str);
    void displayInputImage(const cv::Mat &image);
    void displayOutputImage(const cv::Mat &image);
    void updateBuffer(void);
   // int no_of_salt_pepper_noises;
    int flag;
    int index;
    bool isVideo;
    bool savevideo;
    bool pcflag;
    bool imflag2;
    int snapflag;
    bool imcap;
    bool calflag;
    int cameraID;
    CVFunctions cvfunctions;

protected:
    void closeEvent(QCloseEvent *event);

private slots:




    void on_actionAdd_Salt_and_Pepper_Noise_triggered(bool checked);

    void on_actionGray_triggered(bool checked);

    void on_actionRed_triggered(bool checked);

    void on_actionGreen_triggered(bool checked);

    void on_actionBlue_triggered(bool checked);

    void on_actionEqualise_triggered(bool checked);

    void on_actionColor_triggered(bool checked);

    void on_actionGray_2_triggered(bool checked);

    void on_actionTop_Left_triggered(bool checked);

    void on_actionTop_Right_triggered(bool checked);

    void on_actionButton_Left_triggered(bool checked);

    void on_actionButtom_Right_triggered(bool checked);

    void on_actionRGB_to_Gray_triggered(bool checked);

    void on_actionRGB_to_HSV_triggered(bool checked);

    void on_actionRGB_to_HLS_triggered(bool checked);

    void on_actionRGB_to_YCrCb_triggered(bool checked);

    void on_actionRGB_to_XYZ_triggered(bool checked);

    void on_actionRGB_to_CIE_L_a_b_triggered(bool checked);

    void on_actionRGB_to_CIE_L_u_v8_triggered(bool checked);




    void getVideoStream(void);

    void on_checkBox_ip_stateChanged(int arg1);

    void on_checkBox_op_stateChanged(int arg1);

    void on_actionImage_triggered();

    void on_actionVideo_triggered();

    void on_actionWebcam_triggered();



    void on_playButton_clicked();

    void on_stopButton_clicked();

    void on_PauseButton_clicked();

    void on_actionExit_triggered();



    void on_actionSaveImage_triggered();

    void on_actionSaveVideo_triggered();

    void on_actionGet_Logo_triggered();

    void on_actionALL_triggered(bool checked);

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_checkBox_toggled(bool checked);
    void makeMenuCheckable(bool status);
    void restorechecked(void);
    void on_actionVertical_triggered(bool checked);

    void on_actionHorizontal_triggered(bool checked);

    void on_actionBoth_triggered(bool checked);






    void on_checkBox_2_toggled(bool checked);

    void on_actionResize_triggered(bool checked);

    void on_actionDilate_triggered(bool checked);

    void on_actionErode_triggered(bool checked);

    void on_actionOpen_triggered(bool checked);

    void on_actionClose_triggered(bool checked);

    void on_actionBlur_triggered(bool checked);

    void on_actionSharpen_triggered(bool checked);

    void on_actionMedian_triggered(bool checked);

    void on_actionGaussian_triggered(bool checked);

    void on_actionSettings_triggered();

    void on_actionMorphology_Gradient_triggered(bool checked);

    void on_actionTop_Hat_triggered(bool checked);

    void on_actionBlack_Hat_triggered(bool checked);

    void on_actionBilateral_triggered(bool checked);

    void on_actionCustom_Filter_triggered(bool checked);

    void on_actionSobel_triggered(bool checked);

    void on_actionLaplacian_triggered(bool checked);

    void on_actionCanny_triggered(bool checked);

    void on_actionNormalise_triggered(bool checked);

    void on_actionLine_triggered(bool checked);

    void on_actionCircle_triggered(bool checked);

    void on_actionContours_triggered(bool checked);

    void on_actionBounding_Box_triggered(bool checked);

    void on_actionMin_Enclosing_Circle_triggered(bool checked);

    void on_actionMin_Enclosing_Ellipse_triggered(bool checked);

    void on_actionConvex_Hull_triggered(bool checked);

    void on_actionMoments_triggered(bool checked);

    void on_actionThreshold_triggered(bool checked);

    void on_actionOtsuThreshold_triggered(bool checked);

    void on_actionRotated_Rectangle_triggered(bool checked);

    void on_actionHarris_triggered(bool checked);

    void on_actionExtract_triggered(bool checked);

    void on_actionExtract_2_triggered(bool checked);

    void on_actionExtract_3_triggered(bool checked);

    void on_actionGet_second_Image_for_Matching_triggered(bool checked);

    void on_actionMatch_triggered(bool checked);

    void on_actionMatch_2_triggered(bool checked);

    void on_actionMatch_3_triggered(bool checked);

    void on_actionGet_Second_Image_triggered(bool checked);

    void on_action7_point_method_triggered(bool checked);

    void on_action_8_triggered(bool checked);

    void on_actionRANSAC_triggered(bool checked);

    void on_actionGet_Images_from_WebCam_triggered(bool checked);

    void dispalyMat(int);
    void getim();
    void getcalim();
    void on_actionHomography_triggered(bool checked);

    void on_actionCalibrate_triggered(bool checked);

    void on_actionGet_Images_for_Calibration_from_Webcam_triggered(bool checked);

    void on_actionUndistort_Image_triggered(bool checked);

    void on_actionHtml_triggered();

    void on_actionPdf_triggered();

    void on_actionAbout_triggered();



private:
    Ui::MainWindow *ui;
  //  CVFunctions cvfunctions;
    CvWindow *cvWindow[2];
    QFrame *frame[2];
    cv::VideoCapture vid;
    cv::VideoWriter vidfile,webfile;

     QList<cv::Mat> *imagebuffer;
     int imagebufferindex;
     QList<int> processlist;
  //  QCheckBox *checkBox[2];
   //  QGridLayout *layout;
    cv::Mat img_input;
    cv::Mat img;
    cv::Mat img_op;
    cv::Mat t_mat;
    cv::Mat i_disp;
    QTime t;
    bool matchflag;
    Options ui_options;

    int PID;
public slots:
     void process(int index, bool checked);

signals:
     void ProcessID(int id,bool checked);
};



//class Sleeper : public QThread
//{
//public:
//    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
//    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
//    static void sleep(unsigned long secs){QThread::sleep(secs);}
//};

#endif // MAINWINDOW_H
