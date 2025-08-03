// Main GUI headerfile
//By Suman Raj Bista
//Masters in Computer Vision 3
//University of Burgundy
//Visual Perception course work

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "definations.h"
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ui_options(this)
{
    ui->setupUi(this);

    ui_options.initiliseDefaults ();
    PID = 0;
    pcflag = false;
    frame[0] = new QFrame(ui->inputFrame);
    frame[1] = new QFrame(ui->outputFrame);

    ui->playButton->hide ();
    ui->stopButton->hide();
    ui->PauseButton->hide ();

    cameraID = 0;
//    checkBox[0] = new QCheckBox("Popout",ui->centralWidget);
//    checkBox[0]->setObjectName(QString::fromUtf8("checkBox_ip"));
//    checkBox[0]->setGeometry(QRect(10, 50, 91, 17));

//    checkBox[1] = new QCheckBox("Popout",ui->centralWidget);
//    checkBox[1]->setObjectName(QString::fromUtf8("checkBox_op"));
//    checkBox[1]->setGeometry(QRect(500, 50, 91, 17));


for(int i = 0 ; i<2 ; i++){
     cvWindow[i] = new CvWindow(QString("cvWindow"), CV_WINDOW_NORMAL|CV_WINDOW_FREERATIO|CV_GUI_EXPANDED);

     frame[i]->setGeometry(0,0,480,408);

     // set the location of 'cvWindow'
      cvWindow[i]->setGeometry(0,0,480,408);
      cvWindow[i]->setParent(frame[i]);

     //If the frame resizes, update the image size
    //connect(frame[i], SIGNAL(resizeImage(QSize)), this, SLOT(updateImageSize(QSize)));
    //updateImageSize(frame[i]->size(),i);
}
 img_input = cv::Mat(408, 480, CV_8U, cv::Scalar::all(0));
 img = cv::Mat(408, 480, CV_8U, cv::Scalar::all(0));
 img_op = cv::Mat(408, 480, CV_8U, cv::Scalar::all(0));
 t_mat = cv::Mat(408, 480, CV_8U, cv::Scalar::all(0));
 flag = 0;
 imagebuffer = new QList<cv::Mat>();
 imagebufferindex = 0;
 processlist.clear ();
 processlist.append(0);
 ui->actionUndo->setEnabled(false);
  ui->actionRedo->setEnabled(false);
 connect(this,SIGNAL(ProcessID(int,bool)),this,SLOT(process(int,bool)));
  ui->actionGet_second_Image_for_Matching->setDisabled (true);
  ui->actionGet_Second_Image->setDisabled(true);
  ui->actionMatch->setDisabled (true);
  ui->actionMatch_2->setDisabled (true);
  ui->actionMatch_3->setDisabled (true);
  ui->menuFundamental_Matrix->setDisabled (true);
  ui->actionHomography->setDisabled (true);
  ui->label->setVisible (false);
  imflag2 = false;
  matchflag = false;
  imcap = false;
   ui->frame->setVisible (false);
   ui->actionUndistort_Image->setDisabled (true);
   //ui->menuInvert->setDisabled (true);
}

MainWindow::~MainWindow()
{
    flag = 0;
    vid.release ();
    //delete ui_options;
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
 {
    flag = 0;
    vid.release();
    event->accept ();
 }

void MainWindow::updateImage( const cv::Mat &image, int i )
{
    CvMat c_img ;
    c_img = cvMat(image);
  double w = c_img.width;
  double h = c_img.height;
  double x0 = 0;
  double y0 = 0;



  if(h >= w)
  {
      w = w/h*360;
      h = 360 + 48;
      x0 = (480 - w)/2;
  }
  else
  {
      h = h/w*480 + 48;
      w = 480;
      y0 = (360 - h)/2 + 24;

  }

  if(h>408)
  {
      w = w/(h-48)*360;
      h = 360 + 48;
      x0 = (480 - w)/2;
      y0 = (360 - h)/2 + 24;
  }


  cvWindow[i]->setGeometry(int(x0),int(y0),int(w),int(h));

  cvWindow[i]->updateImage( &c_img );

   // updateImageSize(frame[i]->size(),i);
  //  ui->textEdit->setText(imfile);
}

void MainWindow::updateImage( const QString &str, int i )
{
   if(!str.isEmpty())
   {
    img_input = cv::imread(str.toStdString());
     if(i==0) displayInputImage(img_input);
     else displayOutputImage (img_input);

   }
}

void MainWindow::updateImageSize(const QSize &size,int i) {
    //  We need a little bit space for color and coordinate
    //  information below the image
    int width = size.width();
    int height = size.height();


    //cvWindow[i]->getView()->setSceneRect(QRect(0,0,width,height));
    //cvWindow[i]->getView()->setFixedSize(QSize(width, height));
    cvWindow[i]->setFixedSize(QSize(width, height));

    cvWindow[i]->resize(QSize(width, height));
}

cv::Mat MainWindow::readImage(const QString &str)
{
   cv::Mat im;
    if(!str.isEmpty())
       im = cv::imread(str.toStdString());
   return im;
}

void MainWindow::displayOutputImage(const cv::Mat &image)
{
    updateImage(image,1);
    if(ui->checkBox_op->checkState ())
    {
        cv::namedWindow("Output",cv::WINDOW_NORMAL);
        cv::imshow ("Output",image);

    }

    img_op = image;
    if(!matchflag)
       img = image.clone();
    else
        matchflag = false;

}

void MainWindow::displayInputImage(const cv::Mat &image)
{
    updateImage(image,0);
    if(ui->checkBox_ip->checkState ())
    {
        cv::namedWindow("Input",cv::WINDOW_NORMAL);
        cv::imshow ("Input",image);

    }
    if(!calflag){
    img_input = image.clone ();
    img = img_input.clone();
    cvfunctions.ip_image = image.clone ();
      if(!flag)
          t_mat = img_input;
    }
    i_disp = image;
}



void MainWindow::process(int index,bool checked)
{
    if(!flag){
        if(pcflag){
            displayOutputImage(cvfunctions.process (img,index));
            t_mat = img;
        }
        else
            displayOutputImage(cvfunctions.process (t_mat,index));
        if(index<HOUGHLINE)
           updateBuffer();
        if (index >= FUND7P && index <=CALIBRATE){
            if(index!=CALIBRATE)
                calflag = true;
            displayInputImage (cvfunctions.ip_pp);
            dispalyMat (index);
            calflag = false;
        }
        else if(index==HOMOGRAPHY){
                dispalyMat (index);
        }
        else{
             ui->frame->setVisible (false);
        }
    }
    else{
       PID = index;
    if(pcflag){
        if(checked)
            processlist.append (PID);
        else
            processlist.removeAll (PID);
    }
  }
}

void MainWindow::updateBuffer (void)
{
  imagebufferindex++;
    if(imagebuffer->isEmpty ()){
        imagebuffer->append (img_input.clone ());
        imagebufferindex = 1;
    }
    else
        if(imagebuffer->size ()==10){
            imagebuffer->removeFirst ();
            imagebufferindex = 9;
        }

    imagebuffer->append (img_op.clone ());
    img = img_op.clone();
     ui->actionUndo->setEnabled(true);
}

void MainWindow::on_checkBox_ip_stateChanged(int arg1)
{
 if(!img_input.empty ()){
    if(arg1 != 0){
                cv::namedWindow("Input",cv::WINDOW_AUTOSIZE );
                cv::imshow ("Input",i_disp );
        }
        else{
          cv::namedWindow("Input", cv::WINDOW_AUTOSIZE );
          cv::destroyWindow ("Input");
        }
 }
}

void MainWindow::on_checkBox_op_stateChanged(int arg1)
{
  if(!img_op.empty ()){
    if(arg1 != 0)
    {
        cv::namedWindow("Output",cv::WINDOW_AUTOSIZE );
        cv::imshow ("Output",img_op);
    }
    else{
     cv::namedWindow("Output",cv::WINDOW_AUTOSIZE );
     cv::destroyWindow ("Output");
    }
  }
}


void MainWindow::on_actionImage_triggered()
{
    imfile = QFileDialog::getOpenFileName(this,
                                                     "Select file to open",
                                                     "../Images",
                                                      "Images (*.bmp *.png *.jpg *.pgm *.ppm *.pbm *.tif)" );
   if( !imfile.isEmpty() )
   {
    if(vid.isOpened ()){flag = 0; vid.release ();}
    if(!imagebuffer->isEmpty ()) imagebuffer->clear ();
    updateImage(imfile,0);
    cvfunctions.imfile = imfile;
    //img = img_input;
    makeMenuCheckable(false);
    ui->playButton->hide ();
    ui->stopButton->hide();
    ui->PauseButton->hide ();
    ui->actionGet_second_Image_for_Matching->setEnabled (true);
    ui->actionGet_Second_Image->setEnabled(true);
     ui->menuInvert->setEnabled (true);
   }

}

void MainWindow::on_actionVideo_triggered()
{
    videofile = QFileDialog::getOpenFileName(this,
                                                     "Select file to open",
                                                     "../Images",
                                                      "Videos (*.avi *.wmv *.mpeg *.mp4)" );
  if( !videofile.isEmpty() ){
    vid.open(videofile.toStdString ());
    cvfunctions.imfile = videofile;
    if(!processlist.isEmpty ()) processlist.clear ();
    flag = 1;
    isVideo = true;
    if(vid.isOpened())
    {
       cv::Mat frame;
       vid>>(frame);
       displayInputImage (frame);
     }
    vid.set(cv::CAP_PROP_POS_AVI_RATIO,0);
     savevideo = false;
    ui->playButton->show ();
    ui->stopButton->show ();
    ui->PauseButton->hide ();
     makeMenuCheckable(flag);
  }
}



void MainWindow::on_actionWebcam_triggered()
{
    vid.open(cameraID);
    flag = 1;
    cvfunctions.imfile = QString("camfile.jpg");
    ui->playButton->hide ();
    ui->stopButton->show ();
    ui->PauseButton->show ();
     isVideo = false;
      savevideo = false;
      if(!processlist.isEmpty ()) processlist.clear ();
        makeMenuCheckable(flag);
    getVideoStream();

}

void MainWindow::getVideoStream()
{
   ui->actionUndo->setEnabled(false);
   ui->actionUndo->setEnabled (false);
    if(vid.isOpened())
    {
      cv::Mat opframe;
      cv::Mat frame;
      flag = 1;
       makeMenuCheckable(flag);
        ui->menuInvert->setEnabled (true);
       ui->actionGet_second_Image_for_Matching->setDisabled (true);
        ui->actionGet_Second_Image->setDisabled (true);
       ui->actionMatch->setDisabled (true);
       ui->actionMatch_2->setDisabled (true);
       ui->actionMatch_3->setDisabled (true);
        ui->menuFundamental_Matrix->setDisabled (true);
        ui->actionHomography->setDisabled (true);
       restorechecked();
      double delay = 0;
      if(!imagebuffer->isEmpty ()) imagebuffer->clear ();
      if(isVideo) delay =1000/vid.get(cv::CAP_PROP_FPS);
       for(;;)
           {

               vid>>(frame); // get a new frame from camera

               if(!frame.empty ())
               {
                displayInputImage (frame);
              if(!pcflag)
                opframe = cvfunctions.process (frame,PID);
              else
                  opframe = cvfunctions.process(frame,processlist);

               displayOutputImage (opframe);
               if(savevideo){
                   vidfile<<opframe;
                   if(!isVideo)
                       webfile<<frame;
               }
              }


              // t.start ();
              // while(t.elapsed ()<=100);
              //if(waitKey(30) >= 0) break;
              if(frame.empty()) {vid.release(); break ;}
               if(flag == 0) break;
               //if(isVideo) Sleep(delay);
               QCoreApplication::processEvents(QEventLoop::AllEvents,10);
           }
      }
     makeMenuCheckable(flag);
     ui->actionGet_second_Image_for_Matching->setEnabled (true);
     ui->actionMatch->setEnabled ( imflag2);
     ui->actionMatch_2->setEnabled (imflag2);
     ui->actionMatch_3->setEnabled (imflag2);
      ui->actionGet_Second_Image->setEnabled(true);
      ui->menuFundamental_Matrix->setDisabled (imflag2);
  ui->actionHomography->setEnabled (imflag2);
}



void MainWindow::on_playButton_clicked()
{
    flag = 1;
    ui->playButton->hide ();
    ui->stopButton->show ();
    ui->PauseButton->show ();
    if(!vid.isOpened ())
    {
       if(!isVideo) vid.open(cameraID );
       else vid.open(videofile.toStdString ());
        savevideo = false;
    }
    getVideoStream();

    ui->playButton->show ();
    ui->stopButton->show ();
    ui->PauseButton->hide ();
}

void MainWindow::on_stopButton_clicked()
{
 if(!imcap){

    ui->playButton->show ();
    ui->stopButton->show ();
    ui->PauseButton->hide ();
    t_mat = img_input;
    vid.release ();
 }
   flag = 0;
}

void MainWindow::on_PauseButton_clicked()
{
    if(!imcap){
        flag = 0;
        ui->playButton->show ();
        ui->stopButton->show ();
        ui->PauseButton->hide ();
        t_mat = img_input;
    }
    else
        snapflag = 1;
}

void MainWindow::on_actionExit_triggered()
{
    flag = 0;
    vid.release();
    close();
}




void MainWindow::on_actionSaveImage_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    "Save As",
                                                     "../Images",
                                                      "JPEG (*.jpg);;PNG(*.png);;BMP(*.bmp);;(*.pgm *.ppm *.pbm)");
    if(!filename.isEmpty ())
         imwrite(filename.toStdString(),img);
}

void MainWindow::on_actionSaveVideo_triggered()
{

    if(vid.isOpened ()){
        QString filename = QFileDialog::getSaveFileName(this,
                                                        "Save As",
                                                         "../Images",
                                                          "AVI(*.avi)");
        if(!filename.isEmpty ()){
        savevideo = true;
         if(isVideo)
            vidfile.open(filename.toStdString (),1,vid.get(cv::CAP_PROP_FPS),img_input.size(),false);

        else {
             vidfile.open(filename.toStdString (),vid.get(cv::CAP_PROP_FOURCC),16,img_input.size(),false);
            filename.insert(filename.length ()-4,QString("_org"));
             webfile.open(filename.toStdString (),vid.get(cv::CAP_PROP_FOURCC),16,img_input.size(),true);
        }
    }
   }
}


void MainWindow::on_actionGet_Logo_triggered()
{
    QString logofile = QFileDialog::getOpenFileName(this,
                                                     "Select file to open",
                                                     "../Images",
                                                      "Images (*.bmp)" );
    if(!logofile.isEmpty ())
        cvfunctions.logofile = logofile.toStdString ();
}



void MainWindow::on_actionUndo_triggered()
{
   imagebufferindex--;
    cv::Mat t_im = imagebuffer->at(imagebufferindex);
   displayOutputImage (t_im);

   if(imagebufferindex==0){
       ui->actionUndo->setEnabled(false);
   }

    ui->actionRedo->setEnabled(true);
}

void MainWindow::on_actionRedo_triggered()
{
    imagebufferindex++;
    cv::Mat t_im = imagebuffer->at(imagebufferindex);
    displayOutputImage (t_im);

    if(imagebufferindex == imagebuffer->size()-1){
        ui->actionRedo->setEnabled(false);
    }

    ui->actionUndo->setEnabled(true);
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    pcflag = checked;
    makeMenuCheckable(flag);
    if(pcflag & flag) restorechecked();
}

void MainWindow::makeMenuCheckable(bool status)
{
    status = status & pcflag;
    ui->actionVertical->setCheckable (status);
    ui->actionHorizontal->setCheckable (status);
    ui->actionBoth->setCheckable (status);
    ui->actionRGB_to_Gray->setCheckable (status);
    ui->actionAdd_Salt_and_Pepper_Noise->setCheckable (status);
    ui->actionTop_Left->setCheckable (status);
    ui->actionTop_Right->setCheckable (status);
    ui->actionButtom_Right->setCheckable (status);
    ui->actionButton_Left->setCheckable (status);
    ui->actionGray_2->setCheckable (status);
    ui->actionEqualise->setCheckable (status);
    ui->actionColor->setCheckable (status);
    ui->actionGaussian->setCheckable (status);
    ui->actionDilate->setCheckable (status);
    ui->actionErode->setCheckable (status);
    ui->actionOpen->setCheckable (status);
    ui->actionClose->setCheckable (status);
    ui->actionMorphology_Gradient->setCheckable (status);
    ui->actionBlack_Hat->setCheckable (status);
    ui->actionTop_Hat->setCheckable (status);
    ui->actionBlur->setCheckable (status);
    ui->actionSharpen->setCheckable (status);
    ui->actionMedian->setCheckable (status);
    ui->actionBilateral->setCheckable (status);
    ui->actionCustom_Filter->setCheckable (status);
    ui->actionSobel->setCheckable (status);
    ui->actionLaplacian->setCheckable (status);
    ui->actionCanny->setCheckable (status);
    ui->actionNormalise->setCheckable (status);
    ui->actionLine->setCheckable (status);
    ui->actionCircle->setCheckable (status);
    ui->actionContours->setCheckable (status);
    ui->actionBounding_Box->setCheckable (status);
    ui->actionMin_Enclosing_Circle->setCheckable (status);
    ui->actionMin_Enclosing_Ellipse->setCheckable (status);
    ui->actionConvex_Hull->setCheckable (status);
   ui->actionMoments->setCheckable (status);
   ui->actionThreshold->setCheckable (status);
   ui->actionOtsuThreshold->setCheckable (status);
   ui->actionRotated_Rectangle->setCheckable (status);
   ui->actionHarris->setCheckable (status);
   ui->actionExtract->setCheckable (status);
   ui->actionExtract_2->setCheckable (status);
   ui->actionExtract_3->setCheckable (status);

}

void MainWindow::restorechecked(void)
{
    QList<int>::iterator iter;
if(!processlist.isEmpty ()){
    int i = 0;
    for(iter = processlist.begin ();iter != processlist.end ();iter++)
    {
      switch(processlist.at (i)){
      case FLIP_HORIZONTAL: ui->actionHorizontal->setChecked (true); break;
      case FLIP_VERTICAL: ui->actionVertical->setChecked (true); break;
      case FLIP_BOTH: ui->actionBoth->setChecked (true); break;
      case ADD_SALT_N_PEPPER:  ui->actionAdd_Salt_and_Pepper_Noise->setChecked (true); break;
      case LOGO_TOP_RIGHT:  ui->actionTop_Right->setChecked (true); break;
      case LOGO_TOP_LEFT: ui->actionTop_Left->setChecked (true); break;
      case LOGO_BUTTON_LEFT: ui->actionButton_Left->setChecked (true); break;
      case LOGO_BUTTON_RIGHT:  ui->actionButtom_Right->setChecked (true); break;
      case INVERT_COLOR:  ui->actionColor->setChecked (true); break;
      case INVERT_GRAY:  ui->actionGray_2->setChecked (true); break;
      case TO_GRAY:  ui->actionRGB_to_Gray->setChecked (true); break;
      case EQUAL_HIST:ui->actionEqualise->setChecked (true); break;
      case GAUSSIAN:ui->actionGaussian->setChecked(true);break;
      case CANNY:ui->actionCanny->setChecked(true);break;
      case DILATE:ui->actionDilate->setChecked(true);break;
      case ERODE:ui->actionErode->setChecked(true);break;
      case OPEN:ui->actionOpen->setChecked(true);break;
      case CLOSE:ui->actionClose->setChecked(true);break;
      case GRADIENT:ui->actionMorphology_Gradient->setChecked(true);break;
      case BLACKHAT:ui->actionBlack_Hat->setChecked(true);break;
      case TOPHAT:ui->actionTop_Hat->setChecked(true);break;
      case BLUR:ui->actionBlur->setChecked(true);break;
      case SHARPEN:ui->actionSharpen->setChecked(true);break;
      case MEDIAN:ui->actionMedian->setChecked(true);break;
      case BILATERAL:ui->actionBilateral->setChecked(true);break;
      case CUSTOMFILTER:ui->actionCustom_Filter->setChecked(true);break;
      case SOBEL:ui->actionSobel->setChecked(true);break;
      case LAPLACE:ui->actionLaplacian->setChecked(true);break;
      case NORMALISE:ui->actionNormalise->setChecked (true);break;
      case HOUGHLINE: ui->actionLine->setChecked (true);break;
      case HOUGHCIRCLE: ui->actionCircle->setChecked (true);break;
      case CONTOURS: ui->actionContours->setChecked (true);break;
      case BOUNDINGBOX:ui->actionBounding_Box->setChecked (true);break;
      case MINCIRCLE:ui->actionMin_Enclosing_Circle->setChecked (true);break;
      case MINELLIPSE:ui->actionMin_Enclosing_Ellipse->setChecked (true);break;
      case CONVEXHULL:ui->actionConvex_Hull->setChecked (true);break;
      case MOMENTS:ui->actionMoments->setChecked (true);break;
      case THRESHOLD:ui->actionThreshold->setChecked (true);break;
      case OSTU:ui->actionOtsuThreshold->setChecked (true);break;
      case RECTROT:ui->actionRotated_Rectangle->setChecked (true);break;
      case HARIS:ui->actionHarris->setChecked (true);break;
      case FASTFEATURES:ui->actionExtract->setChecked (true);break;
      case SIFTFEATURES:ui->actionExtract_2->setChecked (true);break;
      case SURFEATURES:ui->actionExtract_3->setChecked (true);break;
      default:  break;
      }
     i++;
    }
}
}

void MainWindow::on_actionVertical_triggered(bool checked)
{
        emit ProcessID(FLIP_VERTICAL,checked);
}

void MainWindow::on_actionHorizontal_triggered(bool checked)
{
         emit ProcessID(FLIP_HORIZONTAL,checked);

}

void MainWindow::on_actionBoth_triggered(bool checked)
{
        emit ProcessID(FLIP_BOTH,checked);
}

void MainWindow::on_actionAdd_Salt_and_Pepper_Noise_triggered(bool checked)
{
     emit ProcessID(ADD_SALT_N_PEPPER,checked);
}

void MainWindow::on_actionGray_triggered(bool checked)
{
     emit ProcessID(GRAY_HIST,checked);
}

void MainWindow::on_actionRed_triggered(bool checked)
{
  emit ProcessID(RED_HIST,checked);
}

void MainWindow::on_actionGreen_triggered(bool checked)
{
     emit ProcessID(GREEN_HIST,checked);
}


void MainWindow::on_actionBlue_triggered(bool checked)
{
    emit ProcessID(BLUE_HIST,checked);
}

void MainWindow::on_actionEqualise_triggered(bool checked)
{
    emit ProcessID(EQUAL_HIST,checked);
}

void MainWindow::on_actionColor_triggered(bool checked)
{
    emit ProcessID(INVERT_COLOR,checked);
}

void MainWindow::on_actionGray_2_triggered(bool checked)
{
    emit ProcessID(INVERT_GRAY,checked);
}


void MainWindow::on_actionTop_Left_triggered(bool checked)
{
    emit ProcessID(LOGO_TOP_LEFT,checked);

}

void MainWindow::on_actionTop_Right_triggered(bool checked)
{
   emit ProcessID(LOGO_TOP_RIGHT,checked);
}

void MainWindow::on_actionButton_Left_triggered(bool checked)
{
     emit ProcessID(LOGO_BUTTON_LEFT,checked);
 }

void MainWindow::on_actionButtom_Right_triggered(bool checked)
{
     emit ProcessID(LOGO_BUTTON_RIGHT,checked);
}

void MainWindow::on_actionRGB_to_Gray_triggered(bool checked)
{
    emit ProcessID(TO_GRAY,checked);
}

void MainWindow::on_actionRGB_to_HSV_triggered(bool checked)
{
     emit ProcessID(TO_HSV,checked);
}

void MainWindow::on_actionRGB_to_HLS_triggered(bool checked)
{
    emit ProcessID(TO_HLS,checked);
}

void MainWindow::on_actionRGB_to_YCrCb_triggered(bool checked)
{
    emit ProcessID(TO_YCrCb,checked);
}

void MainWindow::on_actionRGB_to_XYZ_triggered(bool checked)
{
    emit ProcessID(TO_XYZ,checked);
}

void MainWindow::on_actionRGB_to_CIE_L_a_b_triggered(bool checked)
{
    emit ProcessID(TO_CIELab,checked);
}

void MainWindow::on_actionRGB_to_CIE_L_u_v8_triggered(bool checked)
{
     emit ProcessID(TO_CIELuv,checked);
}

void MainWindow::on_actionALL_triggered(bool checked)
{
    emit ProcessID(ALL_HIST,checked);
}


void MainWindow::on_checkBox_2_toggled(bool checked)
{
    cvfunctions.showintermediatewindows = !checked;
}

void MainWindow::on_actionResize_triggered(bool checked)
{
    if(ui->checkBox_3->isChecked ())
        ui_options.show_resize_tab ();
    emit ProcessID(RESIZE,checked);
}

void MainWindow::on_actionDilate_triggered(bool checked)
{
    emit ProcessID(DILATE,checked);
}

void MainWindow::on_actionErode_triggered(bool checked)
{
    emit ProcessID(ERODE,checked);
}

void MainWindow::on_actionOpen_triggered(bool checked)
{
    emit ProcessID(OPEN,checked);
}

void MainWindow::on_actionClose_triggered(bool checked)
{
    emit ProcessID(CLOSE,checked);
}


void MainWindow::on_actionBlur_triggered(bool checked)
{
    emit ProcessID(BLUR,checked);
}

void MainWindow::on_actionSharpen_triggered(bool checked)
{
    emit ProcessID(SHARPEN,checked);
}

void MainWindow::on_actionMedian_triggered(bool checked)
{
    emit ProcessID(MEDIAN,checked);
}

void MainWindow::on_actionBilateral_triggered(bool checked)
{
    emit ProcessID(BILATERAL,checked);
}

void MainWindow::on_actionGaussian_triggered(bool checked)
{
    emit ProcessID(GAUSSIAN,checked);
}

void MainWindow::on_actionSettings_triggered()
{
     ui_options.show();
}

void MainWindow::on_actionMorphology_Gradient_triggered(bool checked)
{
    emit ProcessID(GRADIENT,checked);
}

void MainWindow::on_actionTop_Hat_triggered(bool checked)
{
    emit ProcessID(TOPHAT,checked);
}

void MainWindow::on_actionBlack_Hat_triggered(bool checked)
{
    emit ProcessID(BLACKHAT,checked);
}


void MainWindow::on_actionCustom_Filter_triggered(bool checked)
{
    emit ProcessID(CUSTOMFILTER,checked);
}

void MainWindow::on_actionSobel_triggered(bool checked)
{
    emit ProcessID(SOBEL,checked);
}

void MainWindow::on_actionLaplacian_triggered(bool checked)
{
    emit ProcessID(LAPLACE,checked);
}

void MainWindow::on_actionCanny_triggered(bool checked)
{
    emit ProcessID(CANNY,checked);
}

void MainWindow::on_actionNormalise_triggered(bool checked)
{
    emit ProcessID(NORMALISE,checked);
}

void MainWindow::on_actionLine_triggered(bool checked)
{
    emit ProcessID(HOUGHLINE,checked);
}

void MainWindow::on_actionCircle_triggered(bool checked)
{
    emit ProcessID(HOUGHCIRCLE,checked);
}

void MainWindow::on_actionContours_triggered(bool checked)
{
    emit ProcessID(CONTOURS,checked);
}

void MainWindow::on_actionBounding_Box_triggered(bool checked)
{
    emit ProcessID(BOUNDINGBOX,checked);
}

void MainWindow::on_actionMin_Enclosing_Circle_triggered(bool checked)
{
    emit ProcessID(MINCIRCLE,checked);
}

void MainWindow::on_actionMin_Enclosing_Ellipse_triggered(bool checked)
{
    emit ProcessID(MINELLIPSE,checked);
}

void MainWindow::on_actionConvex_Hull_triggered(bool checked)
{
    emit ProcessID(CONVEXHULL,checked);
}

void MainWindow::on_actionMoments_triggered(bool checked)
{
    emit ProcessID(MOMENTS,checked);
}

void MainWindow::on_actionThreshold_triggered(bool checked)
{
    emit ProcessID(THRESHOLD,checked);
}


void MainWindow::on_actionOtsuThreshold_triggered(bool checked)
{
    emit ProcessID(OSTU,checked);
}

void MainWindow::on_actionRotated_Rectangle_triggered(bool checked)
{
    emit ProcessID(RECTROT,checked);
}

void MainWindow::on_actionHarris_triggered(bool checked)
{
    emit ProcessID(HARIS,checked);
}

void MainWindow::on_actionExtract_triggered(bool checked)
{
    emit ProcessID(FASTFEATURES,checked);
}

void MainWindow::on_actionExtract_2_triggered(bool checked)
{
     emit ProcessID(SIFTFEATURES,checked);
}

void MainWindow::on_actionExtract_3_triggered(bool checked)
{
       emit ProcessID(SURFEATURES,checked);
}

void MainWindow::on_actionGet_second_Image_for_Matching_triggered(bool checked)
{
    imfile2 = QFileDialog::getOpenFileName(this,
                                                     "Select file to open",
                                                     "../Images",
                                                      "Images (*.bmp *.png *.jpg *.pgm *.ppm *.pbm *.tif)" );
   if( !imfile2.isEmpty() )
   {
    cvfunctions.ip_image2 = cv::imread(imfile2.toStdString());
    updateImage(cvfunctions.ip_image2,1);
    cvfunctions.imfile2 = imfile2;
    ui->actionMatch->setEnabled (true);
    ui->actionMatch_2->setEnabled (true);
    ui->actionMatch_3->setEnabled (true);
    ui->menuFundamental_Matrix->setEnabled (true);
      ui->actionHomography->setEnabled (true);
     imflag2 = true;


   }

}

void MainWindow::on_actionMatch_triggered(bool checked)
{
    matchflag = true;
    emit ProcessID(SURFMATCH,checked);
}

void MainWindow::on_actionMatch_2_triggered(bool checked)
{
   matchflag = true;
    emit ProcessID(SIFTMATCH,checked);
}

void MainWindow::on_actionMatch_3_triggered(bool checked)
{
    matchflag = true;
    emit ProcessID(SURFMATCH,checked);
}

void MainWindow::on_actionCalibrate_triggered(bool checked)
{

    QString fold = QFileDialog::getExistingDirectory (this,
                                                     "Select folder "
                                                     "../Images");
    if(!fold.isEmpty ()){
     QStringList filters;
     filters <<"*.jpg" << "*.png" <<"*.pbm"<<"*.pgm"<<"*.ppm"<<"*.bmp";

     QDir dir(fold);
     dir.setFilter(QDir::Files);
     dir.setSorting(QDir::Name);
     dir.setNameFilters(filters);

     ui->menuInvert->setEnabled (true);
    cvfunctions.calibrationimages = dir.entryList();
    cvfunctions.calibrationfolder = fold;

    emit ProcessID(CALIBRATE,checked);
    }
}

void MainWindow::on_actionGet_Second_Image_triggered(bool checked)
{
    imfile2 = QFileDialog::getOpenFileName(this,
                                                     "Select file to open",
                                                     "../Images",
                                                      "Images (*.bmp *.png *.jpg *.pgm *.ppm *.pbm *.tif)" );
   if( !imfile2.isEmpty() )
   {
    cvfunctions.ip_image2 = cv::imread(imfile2.toStdString());
    updateImage(cvfunctions.ip_image2,1);
    cvfunctions.imfile2 = imfile2;
    ui->actionMatch->setEnabled (true);
    ui->actionMatch_2->setEnabled (true);
    ui->actionMatch_3->setEnabled (true);
    ui->menuFundamental_Matrix->setEnabled (true);
      ui->actionHomography->setEnabled (true);
     imflag2 = true;


   }
}

void MainWindow::on_action7_point_method_triggered(bool checked)
{
    emit ProcessID(FUND7P,checked);
}

void MainWindow::on_action_8_triggered(bool checked)
{
    emit ProcessID(FUND8P,checked);
}

void MainWindow::on_actionRANSAC_triggered(bool checked)
{
     emit ProcessID(FUNDRANSAC,checked);
}

void MainWindow::on_actionGet_Images_from_WebCam_triggered(bool checked)
{
   if(vid.isOpened ()){flag = 0; vid.release ();}
   if(!imagebuffer->isEmpty ()) imagebuffer->clear ();
   vid.open(cameraID);
   ui->playButton->setVisible (false);
    ui->stopButton->setVisible (false);
   ui->PauseButton->setText (QString("Take Picture"));
   ui->PauseButton->setVisible (true);
 ui->menuInvert->setEnabled (true);
   ui->label->setText (QString("Take Left Image"));
   ui->label->setVisible (true);
   imcap = true;
    snapflag = 0;
    getim();
  imflag2 = true;
   imcap = false;
    ui->PauseButton->setText (QString("Pause"));
     ui->PauseButton->setVisible (false);
     ui->menuFundamental_Matrix->setEnabled (true);
     ui->actionMatch->setEnabled (true);
     ui->actionMatch_2->setEnabled (true);
     ui->actionMatch_3->setEnabled (true);
      ui->actionGet_Second_Image->setEnabled(true);
      ui->actionGet_second_Image_for_Matching->setEnabled (true);
      ui->actionHomography->setEnabled (true);
}

void MainWindow::getim()
{
    int count = 0;
  if(vid.isOpened())
   {

     cv::Mat frame;
     for(;;)
          {
              vid>>(frame); // get a new frame from camera

              if(!frame.empty () )
              {
                  if(count == 0){
                      if(snapflag == 0){
                           displayInputImage (frame);
                           cvfunctions.ip_image = frame.clone ();
                      }
                      else{
                           ui->label->setText (QString("Take Right Image"));
                           snapflag = 0;
                           count ++;
                      }
                  }
                  else if(count == 1){
                      if(snapflag == 0){
                           displayOutputImage (frame);
                           cvfunctions.ip_image2 = frame.clone ();
                      }
                      else{
                           ui->label->setText (QString(" "));
                           snapflag = 0;
                           count ++;
                      }
                  }
               else{

                      vid.release(); break ;
                  }



              }

               if(frame.empty()) {vid.release(); break ;}

                QCoreApplication::processEvents(QEventLoop::AllEvents,10);

               }



     }

  }

void MainWindow::dispalyMat(int id)
{
    ui->frame->setVisible (true);
    cv::Mat matrix;

    if(id == HOMOGRAPHY){
        ui->labeltext->setText (QString("Homography  = "));
        matrix = cvfunctions.homography.clone ();
    }
    else if(id == CALIBRATE){
        ui->labeltext->setText (QString("Intrinsic Parameters  = "));
        matrix = cvfunctions.cameraMatrix.clone ();
        if(cvfunctions.calstatus){
            ui->actionUndistort_Image->setEnabled (true);
        }
        else
             ui->actionUndistort_Image->setEnabled (false);
    }
    else {
        ui->labeltext->setText (QString("Fundamental Matrix  = "));
        matrix = cvfunctions.fundemental.clone ();
    }

    ui->m11->setValue (matrix.at<double>(0,0));
    ui->m21->setValue (matrix.at<double>(1,0));
    ui->m31->setValue (matrix.at<double>(2,0));
    ui->m12->setValue (matrix.at<double>(0,1));
    ui->m22->setValue (matrix.at<double>(1,1));
    ui->m32->setValue (matrix.at<double>(2,1));
    ui->m13->setValue (matrix.at<double>(0,2));
    ui->m23->setValue (matrix.at<double>(1,2));
    ui->m33->setValue (matrix.at<double>(2,2));



}

void MainWindow::on_actionHomography_triggered(bool checked)
{
    emit ProcessID(HOMOGRAPHY,checked);
}





void MainWindow::on_actionGet_Images_for_Calibration_from_Webcam_triggered(bool checked)
{
    if(vid.isOpened ()){flag = 0; vid.release ();}
    if(!imagebuffer->isEmpty ()) imagebuffer->clear ();
    vid.open(cameraID);
    ui->playButton->setVisible (false);
    ui->stopButton->setText (QString("Done"));
     ui->stopButton->setVisible (true);
    ui->PauseButton->setText (QString("Take Picture"));
    ui->PauseButton->setVisible (true);

    ui->label->setText (QString("Take Calibration Images"));
    ui->label->setVisible (true);
    imcap = true;
     snapflag = 0;
     getcalim();
    imcap = false;
     ui->PauseButton->setText (QString("Pause"));
     ui->stopButton->setText (QString("Stop"));
      ui->PauseButton->setVisible (false);
       ui->stopButton->setVisible (false);
        ui->label->setVisible (false);

}

void MainWindow::getcalim()
{
    QString fold = QFileDialog::getExistingDirectory (this,
                                                     "Select folder "
                                                     "../Images");
    if(!fold.isEmpty ()){


      int count;
    flag = 1;
      if(vid.isOpened())
       {
          count = 1;
         cv::Mat frame;
         for(;;)
              {
                  vid>>(frame); // get a new frame from camera

                  if(!frame.empty () )
                  {


                               displayInputImage (frame);
                        if(snapflag == 1){
                               displayOutputImage (frame);
                                std::stringstream str;
                               str << fold.toStdString ()<<"\\" <<"chessboard_"<<count<<".jpg";
                               std::cout << str.str() << std::endl;
                               imwrite(str.str(),frame);
                               snapflag = 0;
                               count++;
                         }
                  }

                   if(frame.empty()) {vid.release(); break ;}
                   if(flag == 0){vid.release(); break ;}
                    QCoreApplication::processEvents(QEventLoop::AllEvents,10);

                   }



         }
    }
  }

void MainWindow::on_actionUndistort_Image_triggered(bool checked)
{
    emit ProcessID(UNDISTORT,checked);
}

void MainWindow::on_actionHtml_triggered()
{

    QString helpfile = QString("file:///");
    helpfile.append ( QFileInfo( QCoreApplication::applicationFilePath() ).absolutePath ());
    helpfile.append ("/userguide.html");
    QDesktopServices::openUrl(QUrl(helpfile));
}

void MainWindow::on_actionPdf_triggered()
{
    QString helpfile = QString("file:///");
    helpfile.append ( QFileInfo( QCoreApplication::applicationFilePath() ).absolutePath ());
    helpfile.append ("/userguide.pdf");
    QDesktopServices::openUrl(QUrl(helpfile));
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this,"About",QString("Created by Suman Raj Bista\n\n Masters Computer Vision 3\n University of Burgundy, France"
                                                  ));

}





