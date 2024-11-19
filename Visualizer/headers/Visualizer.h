#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

#include "Triangulation.h"
#include "Transformation.h"
#include "OpenGlWidget.h"
#include "OpenGlWidget1.h"
#include "MeshUtility.h"
#include "GraphicsSynchronizer.h"

using namespace Geometry;

class Visualizer : public QMainWindow
{
    Q_OBJECT

public:
    Visualizer(QWidget *parent = nullptr);
    ~Visualizer();

private slots:
    void onLoadFileClick();
    void onLoadFileClick1();
    void onJoinClick();
    void onExportClick();

private:
    void setupUi();
    OpenGlWidget::Data convertTrianglulationToGraphicsObject(const Triangulation& inTriangulation);
    OpenGlWidget1::Data convertTrianglulationToGraphicsObject1(const Triangulation& inTriangulation);

private:
    Triangulation triangulation;
    /*Triangulation TranslationTriangulation;
    Triangulation RotationTriangulation;
    Triangulation ReverseRotationTriangulation;
    Triangulation ReverseTranslationTriangulation;*/

    Triangulation triangulation2;
   /* Triangulation TranslationTriangulation2;
    Triangulation RotationTriangulation2;
    Triangulation ReverseRotationTriangulation2;
    Triangulation ReverseTranslationTriangulation2;*/

    Triangulation outputTriangulation;

    QPushButton* loadFile;
    QPushButton* loadFile1;
    QPushButton* join;
    QPushButton* exportFile;

    OpenGlWidget* openglWidgetInput;
    OpenGlWidget1* openglWidgetInput1;
    OpenGlWidget* openglWidgetOutput;

    GraphicsSynchronizer* graphicsSynchronizer;
    MeshUtility mesh;

    QVector<GLfloat> vertices;



    // translation data
    QString inputFilePath;

};

//#pragma once
//
//#include <QMainWindow>
//#include <QPushButton>
//#include "OpenGlWidget.h"
//#include "GraphicsSynchronizer.h"
//#include "Triangulation.h"

//class Visualizer : public QMainWindow
//{
//    Q_OBJECT
//
//public:
//    Visualizer(QWidget* parent = nullptr);
//    ~Visualizer();
//
//private slots:
//    void onLoadFileClick();
//    void onTranslateClick();
//    void onExportClick();
//
//private:
//    void setupUi();
//    void loadAndSetData(const QString& filePath, OpenGlWidget* widget);
//    QString getOppositeExtension(const QString& filePath);
//    void writeFile(const QString& fileName, const Triangulation& triangulationData);
//    OpenGlWidget::Data convertTrianglulationToGraphicsObject(const Triangulation& inTriangulation);
//
//    QPushButton* loadFile;
//    QPushButton* translate;
//    QPushButton* exportFile;
//    OpenGlWidget* openglWidgetInput;
//    OpenGlWidget* openglWidgetOutput;
//    GraphicsSynchronizer* graphicsSynchronizer;
//
//    QString inputFilePath;
//    Triangulation triangulation;
//    Triangulation outputTriangulation;
//};


