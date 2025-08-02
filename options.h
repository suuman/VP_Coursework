//Suman Raj Bista for Visual Perception course work
//Masters in Computer Vision 3
//University of Burgundy
//header files for options

#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>

using namespace std;

namespace Ui {
class Options;
}

class Options : public QDialog
{
    Q_OBJECT
    
public:
    explicit Options(QWidget *parent = 0);
    ~Options();
    void show_resize_tab();
    void initiliseDefaults();
private slots:
    void on_buttonBox_accepted();


    void on_buttonBox_rejected();




    void on_pushButton_clicked();


    void on_radioButton_ErodeCustom_clicked(bool checked);

    void on_radioButton_ErodeDefaults_clicked(bool checked);

    void on_radioButton_DilateDefaults_clicked(bool checked);

    void on_radioButton_DilateCustom_clicked(bool checked);

    void on_radioButton_MDefaults_clicked(bool checked);

    void on_radioButton_MCustom_clicked(bool checked);

    void on_radioButton33_clicked(bool checked);

    void on_radioButton22_clicked(bool checked);

    void on_pushButton_2_clicked();
    void saveOptions();
private:
    Ui::Options *ui;
     QWidget *p;  // gui pointer (it allows access to the options which are public members)
};

#endif // OPTIONS_H
