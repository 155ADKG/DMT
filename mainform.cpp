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

    points.clear();
    dtt.clear();

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
                            p.setX(it->value().toString().toInt());
                        }else if (it->name().toString() == "y"){
                            p.setY(it->value().toString().toInt());
                        }else if (it->name().toString() == "z"){
                            p.setZ(it->value().toString().toInt());
                        }
                    }
                    points.push_back(p);
                    qDebug() << points[0].getZ();
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
    contours = Algorithms::createContours(dt,0.1, 200.0, 5.0);

    ui->Canvas->setContours(contours);

    repaint();
}
