#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include "qpoint3d.h"
#include "algorithms.h"

namespace Ui {
class MainForm;
}

class MainForm : public QMainWindow
{
    Q_OBJECT

private:
    std::vector<QPoint3D> points;
    std::vector<Edge> dt;
    std::vector<Triangle> dtt;
    std::vector<Edge> contours;
    std::vector<Edge> mainContours;
    std::vector<double> draw_slope;
    std::vector<QColor> draw_expos;    
    float z_min;
    float z_max;

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

private slots:
    void on_pushLoad_clicked();

    void on_pushGenCont_clicked();

    void on_pushSlope_clicked();

    void on_pushAspect_clicked();

    void on_pushCleanCont_clicked();

    void on_pushClear_clicked();

    void on_lineEditZMin_editingFinished();

    void on_lineEditZMax_editingFinished();

private:
    Ui::MainForm *ui;
};

#endif // MAINFORM_H
