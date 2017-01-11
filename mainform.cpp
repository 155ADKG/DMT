#include "mainform.h"
#include "ui_mainform.h"

#include <QXmlStreamReader>
#include <QFileDialog>
#include <QMessageBox>

MainForm::MainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::on_pushLoad_clicked()
{
    // Open file
    QFileDialog fdiag(0,trUtf8("Choose XML file"));

    fdiag.setDefaultSuffix("xml");
    fdiag.setFileMode(QFileDialog::AnyFile);

    QStringList filters;
    filters << "XML files (*.xml)";
    fdiag.setNameFilters(filters);

    if (!fdiag.exec()) return;

    QFile file(fdiag.selectedFiles()[0]);
    file.open(QIODevice::ReadOnly);

    // Clear vectors and Canvas
    points.clear();
    draw_slope.clear();
    draw_expos.clear();

    ui->Canvas->setLoadPoints(points);
    ui->Canvas->setDrawSlope(draw_slope);
    ui->Canvas->setDrawExpos(draw_expos);
    ui->labelErr->clear();

    // Read XML
    QXmlStreamReader xml(file.readAll());

    QPoint3D p;
    int lvl = 0;

    while (!xml.atEnd())
    {
        xml.readNext();

        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {

            if(xml.name().toString() == "point" && lvl==1){

                    QXmlStreamAttributes attr = xml.attributes();
                    for(QXmlStreamAttributes::Iterator it=attr.begin(); it < attr.end(); it++)
                    {
                        if(it->name().toString() == "x"){
                            p.setX(it->value().toString().toFloat());
                        }else if (it->name().toString() == "y"){
                            p.setY(it->value().toString().toFloat());
                        }else if (it->name().toString() == "z"){
                            p.setZ(it->value().toString().toFloat());
                        }
                    }
                    points.push_back(p);
            }
            lvl += 1;
        }

        if(xml.tokenType() == QXmlStreamReader::EndElement)
        {
            lvl -= 1;
        }
    }

    ui->Canvas->setLoadPoints(points);

    // After load points we generate TIN
    dt = Algorithms::createDT(points);
    dtt = Algorithms::convertDT(dt);

    qDebug() << "===SLOPE===";
    qDebug() << dtt[0].getSlope();
    qDebug() << dtt[1].getSlope();
    qDebug() << dtt[2].getSlope();

    qDebug() << "===EXPOSITION===";
    qDebug() << dtt[0].getExposition();
    qDebug() << dtt[1].getExposition();
    qDebug() << dtt[2].getExposition();

    ui->Canvas->setTriangle(dtt);

    repaint();

    if (xml.hasError())
    {
        QMessageBox::critical(this, "Read XML: ERROR", xml.errorString(), QMessageBox::Ok);
        ui->labelErr->setText("<font color='red'>XML error</font>");
    }

}

void MainForm::on_pushGenCont_clicked()
{
    contours = Algorithms::createContours(dt,0.1, 200.0, 0.1);

    ui->Canvas->setContours(contours);

    repaint();
}

void MainForm::on_pushSlope_clicked()
{
    // Clear vectors and Canvas
    draw_slope.clear();
    draw_expos.clear();

    ui->Canvas->setDrawSlope(draw_slope);
    ui->Canvas->setDrawExpos(draw_expos);

    for (int i=0;i<dtt.size();i++)
    {

        int x1 = dtt[i].getP1().getX();
        int y1 = dtt[i].getP1().getY();
        int x2 = dtt[i].getP2().getX();
        int y2 = dtt[i].getP2().getY();
        int x3 = dtt[i].getP3().getX();
        int y3 = dtt[i].getP3().getY();

        double gray = round(fabs(dtt[i].getSlope() / 180) * 255);

        draw_slope.push_back(gray);
    }

    ui->Canvas->setDrawSlope(draw_slope);

    repaint();
}

void MainForm::on_pushAspect_clicked()
{
    // Clear vectors and Canvas
    draw_slope.clear();
    draw_expos.clear();

    ui->Canvas->setDrawSlope(draw_slope);
    ui->Canvas->setDrawExpos(draw_expos);

    for (int i=0;i<dtt.size();i++)
    {

        int x1 = dtt[i].getP1().getX();
        int y1 = dtt[i].getP1().getY();
        int x2 = dtt[i].getP2().getX();
        int y2 = dtt[i].getP2().getY();
        int x3 = dtt[i].getP3().getX();
        int y3 = dtt[i].getP3().getY();

        double asp = dtt[i].getExposition()+180;

        if ((asp > 337.5 || asp < 22.5) && asp != 0){ draw_expos.push_back(QColor(255,0,0)); }
        else if (asp >= 22.5 && asp < 67.5){ draw_expos.push_back(QColor(255,128,0)); }
        else if (asp >= 67.5 && asp < 112.5){ draw_expos.push_back(QColor(255,255,0)); }
        else if (asp >= 112.5 && asp < 157.5){ draw_expos.push_back(QColor(0,255,0)); }
        else if (asp >= 157.5 && asp < 202.5){ draw_expos.push_back(QColor(0,255,255)); }
        else if (asp >= 202.5 && asp < 247.5){ draw_expos.push_back(QColor(0,150,255)); }
        else if (asp >= 247.5 && asp < 292.5){ draw_expos.push_back(QColor(0,0,255)); }
        else if (asp >= 292.5 && asp < 337.5){ draw_expos.push_back(QColor(255,0,255)); }
        else {draw_expos.push_back(QColor(0,0,0));}
    }

    ui->Canvas->setDrawExpos(draw_expos);

    repaint();
}
