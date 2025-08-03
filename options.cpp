//Suman Raj Bista for Visual Perception course work
//Masters in Computer Vision 3
//University of Burgundy
//for options

#include "options.h"
#include "ui_options.h"
#include "mainwindow.h"
#include "cvfunctions.h"

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
    p = parent;
      ui->groupBox->setDisabled (true);
      ui->groupBox_1->setDisabled (true);
       ui->groupBox_3->setDisabled (true);
}

Options::~Options()
{
    delete ui;
}

void Options::on_buttonBox_accepted()
{
    saveOptions ();
     ui->pushButton_2->setVisible (true);
    this->close ();
}

void Options::on_buttonBox_rejected()
{
    ui->pushButton_2->setVisible (true);
    this->close();
}

void Options::show_resize_tab ()
{
    ui->tabWidget->setCurrentIndex (0);

    ui->pushButton_2->setVisible (false);
    this->show ();
}

void Options::initiliseDefaults()
{
    MainWindow *gui = (MainWindow *) p;
    gui->cvfunctions.showintermediatewindows = true;
    gui->cvfunctions.ip_image = cv::Mat(3, 4, CV_8U,cv::Scalar::all(0));
    gui->cvfunctions.ip_image2 = cv::Mat(3, 4, CV_8U,cv::Scalar::all(0));
    gui->cvfunctions.no_of_salt_pepper_noises = 10000;
    gui->cvfunctions.height = 1280;
    gui->cvfunctions.width = 800;
    gui->cvfunctions.erodeiterno = 1;
    gui->cvfunctions.dilateiterno = 1;
    gui->cvfunctions.erodelem = -1;
    gui->cvfunctions.dilatelem = -1;
    gui->cvfunctions.erodesize = 1;
    gui->cvfunctions.dilatesize = 1;
    gui->cvfunctions.morphelem = -1;
    gui->cvfunctions.morphsize = 1;
    gui->cvfunctions.mean_filter_size = 3;
    gui->cvfunctions.median_filter_size = 3;
    gui->cvfunctions.gaussian_filter_size = 3;
    gui->cvfunctions.sigmaX = 1;
    gui->cvfunctions.sigmaY = 1;
    gui->cvfunctions.bilateralfilter_diam = 3;
    gui->cvfunctions.sigmacolor = 10.0;
    gui->cvfunctions.sigmaspace = 10.0;
    gui->cvfunctions.filtermask.create (3,3,CV_64F);
    gui->cvfunctions.filtermask = cv::Scalar(0);
    gui->cvfunctions.filtermask.at<double>(0,1) = -1;
     gui->cvfunctions.filtermask.at<double>(1,0) = -1;
      gui->cvfunctions.filtermask.at<double>(1,2) = -1;
       gui->cvfunctions.filtermask.at<double>(2,1) = -1;
    gui->cvfunctions.filtermask.at<double>(1,1) =5 ;
    gui->cvfunctions.offset = 0;
    gui->cvfunctions.sobeldir = 0;
    gui->cvfunctions.sobelkersize = 3;
    gui->cvfunctions.sobeloffset = 0;
    gui->cvfunctions.sobelscale = 1;
    gui->cvfunctions.laplacekernelsize = 3;
    gui->cvfunctions.laplacescale = 1;
    gui->cvfunctions.laplaceoffset = 0;
    gui->cvfunctions.lowThreshold = 0;
    gui->cvfunctions.upperThreshold=10;
    gui->cvfunctions.kernel_size = 3;
    gui->cvfunctions.L2gradient = false;
    gui->cvfunctions.houghminlinegap = 0;
    gui->cvfunctions.houghminlinelength = 0;
    gui->cvfunctions.houghthres = 20;
    gui->cvfunctions.probhoughline = true;
    gui->cvfunctions.rho = 1;
    gui->cvfunctions.theta = CV_PI/180;
    gui->cvfunctions.dp = 2;
    gui->cvfunctions.hcmimdist = 100;
    gui->cvfunctions.param1 = 75;
    gui->cvfunctions.param2 = 50;
    gui->cvfunctions.minradius = 0;
    gui->cvfunctions.maxradius = 0;
    gui->cvfunctions.thres = 100;
    gui->cvfunctions.harrisk = 0.01;
    gui->cvfunctions.harristhreshold = 100;
    gui->cvfunctions.harrisapertureSize = 3;
    gui->cvfunctions.harrisblockSize = 2;
    gui->cvfunctions.nonmaximalsupression = false;
    gui->cvfunctions.fastthreshold = 40;
    gui->cvfunctions.hessianthreshold = 2500;
     gui->cvfunctions.matchesno = -1;
     gui->cvfunctions.cameraMatrix = cv::Mat(3, 3, CV_64F,cv::Scalar::all(0));
     gui->cvfunctions.cameraMatrix.at<double>(2,2) = 1;
     gui->cvfunctions.distCoeffs = cv::Mat(1,4,CV_64F,cv::Scalar::all(0));
     gui->cvfunctions.calstatus = false;
     gui->cvfunctions.broadlength = 6;
     gui->cvfunctions.broadwidth = 4;
     gui->cameraID = 0;
     gui->cvfunctions.resizepc = 1;
     gui->cvfunctions.resizebypc = false;

    }

void Options::on_pushButton_clicked()
{

    int index = ui->tabWidget->currentIndex ();
    if(index==7){
        ui->SP_noise->setValue (10000);
        ui->radioButton33->setChecked (true);
        ui->doubleSpinBox11->setValue (0);
        ui->doubleSpinBox12->setValue (-1);
        ui->doubleSpinBox13->setValue (0);
        ui->doubleSpinBox21->setValue (-1);
        ui->doubleSpinBox22->setValue (5);
        ui->doubleSpinBox23->setValue (-1);
        ui->doubleSpinBox31->setValue (0);
        ui->doubleSpinBox32->setValue (-1);
        ui->doubleSpinBox33->setValue (0);
        ui->doubleSpinBox_fact->setValue(1);
        ui->frame_2->setVisible (true);
        ui->frame_3->setVisible (true);
        ui->spinBox_off->setValue (0);


    }
  else if(index ==0){
    ui->radioButton_7->setChecked (true);
    ui->doubleSpinBox->setValue (1280);
    ui->doubleSpinBox_2->setValue (800);
    ui->radioButton_8->setChecked (true);
    ui->radioButton_9->setChecked(false);
    ui->percent->setValue (100.0);}

    else if(index ==1){
        ui->erode_it->setValue (1);
        ui->radioButton_ErodeDefaults->setChecked (true);
        ui->radioButton_ERect->setChecked (true);
         ui->erode_kern_sz->setValue (1);
          ui->groupBox->setDisabled (true);

        ui->dilate_it->setValue (1);
        ui->radioButton_DilateDefaults->setChecked (true);
        ui->radioButton_DRect->setChecked (true);
         ui->dilate_kern_sz->setValue (1);
          ui->groupBox_1->setDisabled (true);


        ui->radioButton_MDefaults->setChecked (true);
        ui->radioButton_MRect->setChecked (true);
         ui->kern_sz->setValue (1);
          ui->groupBox_3->setDisabled (true);
    }
    else if(index == 2){
         ui->comboBox->setCurrentIndex (0);
         ui->comboBox_2->setCurrentIndex (0);
         ui->comboBox_3->setCurrentIndex (0);
         ui->comboBox_4->setCurrentIndex (0);
         ui->doubleSpinBox_sx->setValue (1.00);
         ui->doubleSpinBox_sy->setValue (1.00);
         ui->doubleSpinBox_sc->setValue (10.00);
         ui->doubleSpinBox_ss->setValue (10.00);
          ui->thresholdbox->setValue (100);
    }

    else if(index == 3){
        ui->radioButton_cl1->setChecked (true);
        ui->radioButton_sb->setChecked (true);
        ui->sobelscale->setValue (1.00);
        ui->laplacescale->setValue (1.00);
        ui->cannyscale->setValue (10);
        ui->spinBox_off_sobel->setValue (0);
        ui->spinBox_off_canny->setValue (0);
        ui->spinBox_off_laplace->setValue (0);
        ui->cannykersize->setCurrentIndex (0);
        ui->laplacekersize->setCurrentIndex (0);
        ui->sobelkersize->setCurrentIndex (0);
    }
    else if(index ==4){
        ui->radioButton_pht->setChecked(true);
       ui->hough_rho->setValue (1);
         ui->hough_angle->setValue (1);
           ui->hough_threshold->setValue (50);
         ui->hough_mumlinelen->setValue (0);
           ui->hough_mumlinegap->setValue (0);

          ui->hough_dp->setValue(2);
          ui->hough_mindist->setValue(100);
          ui->hough_param1->setValue(75);
          ui->hough_param2->setValue(50);
          ui->hough_minrad->setValue(0);
          ui->hough_maxrad->setValue(0);

    }
    else if(index ==5){
      ui->harisblock->setValue(2);
              ui->harissobelsize->setCurrentIndex (0);
              ui->haristhres->setValue(100);
              ui->harrisk->setValue(0.01);
              ui->checkBoxnms->setChecked (false);
              ui->fastthres->setValue(40);
              ui->suftthres->setValue (2500);
              ui->match2show->setValue(-1);
    }
    else if(index == 6){
        ui->boardwidth->setValue (6);
        ui->boardlength->setValue (4);
        ui->cameraID->setValue (0);
    }
}



void Options::on_radioButton_ErodeCustom_clicked(bool checked)
{
    if(checked)
          ui->groupBox->setDisabled (false);
}

void Options::on_radioButton_ErodeDefaults_clicked(bool checked)
{
    if(checked)
        ui->groupBox->setDisabled (true);
}

void Options::on_radioButton_DilateDefaults_clicked(bool checked)
{
    if(checked)
          ui->groupBox_1->setDisabled (true);
}

void Options::on_radioButton_DilateCustom_clicked(bool checked)
{
    if(checked)
          ui->groupBox_1->setDisabled (false);
}

void Options::on_radioButton_MDefaults_clicked(bool checked)
{
    if(checked)
          ui->groupBox_3->setDisabled (true);
}

void Options::on_radioButton_MCustom_clicked(bool checked)
{
    if(checked)
          ui->groupBox_3->setDisabled (false);
}

void Options::on_radioButton33_clicked(bool checked)
{
    if(checked){
        ui->frame_2->setVisible (true);
        ui->frame_3->setVisible (true);
    }

}

void Options::on_radioButton22_clicked(bool checked)
{
    if(checked){
        ui->frame_2->setVisible (false);
        ui->frame_3->setVisible (false);

}
}

void Options::on_pushButton_2_clicked()
{
   saveOptions ();
}

void Options::saveOptions ()
{

    MainWindow *gui = (MainWindow *) p;
    int h ; int w;
     gui->cvfunctions.thres = ui->thresholdbox->value ();
    gui->cvfunctions.no_of_salt_pepper_noises = ui->SP_noise->value ();
    if(ui->radioButton->isChecked ()) { w = 640; h = 480;}
    else if(ui->radioButton_2->isChecked ()){  w = 1024; h = 768;}
    else if(ui->radioButton_3->isChecked ()) { w = 800; h = 600;}
    else if(ui->radioButton_4->isChecked ()) { w = 854; h = 480;}
    else if(ui->radioButton_5->isChecked ()) { w = 1366; h = 768;}
    else if(ui->radioButton_6->isChecked ()) { w = 1920; h = 1080;}
    else if(ui->radioButton_7->isChecked ())  {w = ui->doubleSpinBox->value ();
                                              h = ui->doubleSpinBox_2->value ();}
    gui->cvfunctions.height = h;
    gui->cvfunctions.width = w;
    gui->cvfunctions.erodeiterno = ui->erode_it->value ();

    if(ui->radioButton_ErodeDefaults->isChecked ()) gui->cvfunctions.erodelem = -1;
    else if(ui->radioButton_ErodeCustom->isChecked ()){
        if(ui->radioButton_ERect->isChecked ()) gui->cvfunctions.erodelem = 0;
        else if(ui->radioButton_ECross->isChecked ()) gui->cvfunctions.erodelem = 1;
        else if(ui->radioButton_EEllipse->isChecked ()) gui->cvfunctions.erodelem = 2;
        gui->cvfunctions.erodesize = ui->erode_kern_sz->value ();}

    gui->cvfunctions.dilateiterno = ui->dilate_it->value ();

    if(ui->radioButton_DilateDefaults->isChecked ()) gui->cvfunctions.dilatelem = -1;
    else if(ui->radioButton_DilateCustom->isChecked ()){
        if(ui->radioButton_DRect->isChecked ()) gui->cvfunctions.dilatelem = 0;
        else if(ui->radioButton_DCross->isChecked ()) gui->cvfunctions.dilatelem = 1;
        else if(ui->radioButton_DEllipse->isChecked ()) gui->cvfunctions.dilatelem = 2;
        gui->cvfunctions.dilatesize = ui->dilate_kern_sz->value ();}

    if(ui->radioButton_MDefaults->isChecked ()) gui->cvfunctions.morphelem = -1;
    else if(ui->radioButton_MCustom->isChecked ()){
        if(ui->radioButton_MRect->isChecked ()) gui->cvfunctions.morphelem = 0;
        else if(ui->radioButton_MCross->isChecked ()) gui->cvfunctions.morphelem = 1;
        else if(ui->radioButton_MEllipse->isChecked ()) gui->cvfunctions.morphelem = 2;
        gui->cvfunctions.morphsize = ui->kern_sz->value ();}


    gui->cvfunctions.mean_filter_size = 2*(ui->comboBox->currentIndex ())+ 3;
    gui->cvfunctions.median_filter_size = 2*(ui->comboBox_2->currentIndex ())+ 3;
    gui->cvfunctions.gaussian_filter_size = 2*(ui->comboBox_3->currentIndex ())+ 3;
    gui->cvfunctions.bilateralfilter_diam = 2*(ui->comboBox_3->currentIndex ())+ 3;

    gui->cvfunctions.sigmaX = ui->doubleSpinBox_sx->value ();
    gui->cvfunctions.sigmaY = ui->doubleSpinBox_sy->value ();
    gui->cvfunctions.sigmacolor = ui->doubleSpinBox_sc->value();
    gui->cvfunctions.sigmaspace = ui->doubleSpinBox_ss->value();
    double factor = ui->doubleSpinBox_fact->value();
    if (factor == 0) factor = 1;
    if(ui->radioButton22->isChecked ()){
        gui->cvfunctions.filtermask.create (2,2,CV_64F);
        gui->cvfunctions.filtermask.at<double>(0,0)= ui->doubleSpinBox11->value();
        gui->cvfunctions.filtermask.at<double>(0,1)= ui->doubleSpinBox12->value();
        gui->cvfunctions.filtermask.at<double>(1,0)= ui->doubleSpinBox21->value();
        gui->cvfunctions.filtermask.at<double>(1,1)= ui->doubleSpinBox22->value();
    }
    else if(ui->radioButton33->isChecked ()){
        gui->cvfunctions.filtermask.create (3,3,CV_64F);
        gui->cvfunctions.filtermask.at<double>(0,0)= ui->doubleSpinBox11->value();
        gui->cvfunctions.filtermask.at<double>(0,1)= ui->doubleSpinBox12->value();
        gui->cvfunctions.filtermask.at<double>(0,2)= ui->doubleSpinBox13->value();
        gui->cvfunctions.filtermask.at<double>(1,0)= ui->doubleSpinBox21->value();
        gui->cvfunctions.filtermask.at<double>(1,1)= ui->doubleSpinBox22->value();
        gui->cvfunctions.filtermask.at<double>(1,2)= ui->doubleSpinBox23->value();
        gui->cvfunctions.filtermask.at<double>(2,0)= ui->doubleSpinBox31->value();
        gui->cvfunctions.filtermask.at<double>(2,1)= ui->doubleSpinBox32->value();
        gui->cvfunctions.filtermask.at<double>(2,2)= ui->doubleSpinBox33->value();
    }
     gui->cvfunctions.filtermask/=factor;
     gui->cvfunctions.offset = ui->spinBox_off->value();



     if(ui->radioButton_sh->isChecked ()) gui->cvfunctions.sobeldir = 1;
     if(ui->radioButton_sv->isChecked ()) gui->cvfunctions.sobeldir = -1;
     if(ui->radioButton_sb->isChecked ()) gui->cvfunctions.sobeldir = 0;
     gui->cvfunctions.sobeloffset = ui->spinBox_off_sobel->value ();
     gui->cvfunctions.sobelkersize = 2*(ui->sobelkersize->currentIndex ()) +3;
     gui->cvfunctions.sobelscale = ui->sobelscale->value ();

     gui->cvfunctions.laplaceoffset = ui->spinBox_off_laplace->value ();
     gui->cvfunctions.laplacekernelsize = 2*(ui->laplacekersize->currentIndex ()) +3;
     gui->cvfunctions.laplacescale = ui->laplacescale->value ();

     gui->cvfunctions.lowThreshold = ui->spinBox_off_canny->value ();
     gui->cvfunctions.kernel_size = 2*(ui->cannykersize->currentIndex ()) +3;
     gui->cvfunctions.upperThreshold = ui->cannyscale->value ();

     if(ui->radioButton_cl1->isChecked ()) gui->cvfunctions.L2gradient = false;
     if(ui->radioButton_cl2->isChecked ()) gui->cvfunctions.L2gradient = true;

     if(ui->radioButton_ht->isChecked ()) gui->cvfunctions.probhoughline = false;
     if(ui->radioButton_pht->isChecked ()) gui->cvfunctions.probhoughline = true;

     gui->cvfunctions.rho = ui->hough_rho->value ();
      gui->cvfunctions.theta = (ui->hough_angle->value ())*CV_PI/180;;
       gui->cvfunctions.houghthres = ui->hough_threshold->value ();
        gui->cvfunctions.houghminlinelength = ui->hough_mumlinelen->value ();
         gui->cvfunctions.houghminlinegap = ui->hough_mumlinegap->value ();

         gui->cvfunctions.dp = ui->hough_dp->value();
         gui->cvfunctions.hcmimdist =  ui->hough_mindist->value();
         gui->cvfunctions.param1 =  ui->hough_param1->value();
         gui->cvfunctions.param2 = ui->hough_param2->value();
         gui->cvfunctions.minradius = ui->hough_minrad->value();
         gui->cvfunctions.maxradius =ui->hough_maxrad->value();

         gui->cvfunctions.harrisk = ui->harrisk->value();
         gui->cvfunctions.harristhreshold = ui->haristhres->value();
         gui->cvfunctions.harrisapertureSize = 2*(ui->harissobelsize->currentIndex ()) +3;
         gui->cvfunctions.harrisblockSize = ui->harisblock->value();
         gui->cvfunctions.nonmaximalsupression = ui->checkBoxnms->checkState ();
         gui->cvfunctions.fastthreshold = ui->fastthres->value();
         gui->cvfunctions.hessianthreshold = ui->suftthres->value();
         gui->cvfunctions.matchesno = ui->match2show->value();

         gui->cvfunctions.broadlength = ui->boardwidth->value ();
         gui->cvfunctions.broadwidth = ui->boardlength->value ();
         gui->cameraID = ui->cameraID->value ();
         if(ui->radioButton_9->isChecked ()) gui->cvfunctions.resizebypc = true;
          else gui->cvfunctions.resizebypc = false;
          gui->cvfunctions.resizepc = (ui->percent->value ()/100);
}
