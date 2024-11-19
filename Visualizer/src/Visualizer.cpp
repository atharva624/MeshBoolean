#include <QFileDialog>
#include <QGridLayout>
#include "Visualizer.h"
#include "STLReader.h"
#include "OBJReader.h"
#include "OBJWriter.h"
#include "STLWriter.h"
#include "DataWriter.h"
#include "Triangulation.h"
#include "MeshUtility.h"
#include "RealPoint.h"
#include "TransformationManager.h"



Visualizer::Visualizer(QWidget* parent)
    : QMainWindow(parent)
{
    setupUi();

    connect(loadFile, &QPushButton::clicked, this, &Visualizer::onLoadFileClick);
    connect(loadFile1, &QPushButton::clicked, this, &Visualizer::onLoadFileClick1);
    connect(join, &QPushButton::clicked, this, &Visualizer::onJoinClick);
    connect(exportFile, &QPushButton::clicked, this, &Visualizer::onExportClick);
}

Visualizer::~Visualizer()
{

}

void Visualizer::setupUi()
{
    loadFile = new QPushButton("Load File1", this);
    loadFile1 = new QPushButton("Load File2", this);
    join = new QPushButton("Join", this);
    exportFile = new QPushButton("Export", this);
    openglWidgetInput = new OpenGlWidget(this);
    openglWidgetInput1 = new OpenGlWidget1(this);
    openglWidgetOutput = new OpenGlWidget(this);
    //graphicsSynchronizer = new GraphicsSynchronizer(openglWidgetInput, openglWidgetInput1 , openglWidgetOutput);

    QGridLayout* layout = new QGridLayout(this);

    layout->addWidget(loadFile, 0, 0);
    layout->addWidget(loadFile1, 0, 1);
    layout->addWidget(join, 0, 2);
    layout->addWidget(exportFile, 0, 3);
    layout->addWidget(openglWidgetInput, 1, 0, 1, 2);
    layout->addWidget(openglWidgetInput1, 1, 2, 1, 2);
    layout->addWidget(openglWidgetOutput, 2, 0, 1, 4);
    


    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(layout);
}

void  Visualizer::onLoadFileClick()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "", tr("files (*.stl *.obj)"));

    if (!fileName.isEmpty())
    {
        inputFilePath = fileName;
        if (inputFilePath.endsWith(".stl", Qt::CaseInsensitive))
        {
            STLReader reader;
            reader.read(inputFilePath.toStdString(), triangulation);
        }
        else if (inputFilePath.endsWith(".obj", Qt::CaseInsensitive))
        {
            OBJReader reader;
            reader.read(inputFilePath.toStdString(), triangulation);
        }
        OpenGlWidget::Data data = convertTrianglulationToGraphicsObject(triangulation);
        openglWidgetInput->setData(data);
    }
}

void  Visualizer::onLoadFileClick1()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "", tr("files (*.stl *.obj)"));

    if (!fileName.isEmpty())
    {
        inputFilePath = fileName;
        if (inputFilePath.endsWith(".stl", Qt::CaseInsensitive))
        {
            STLReader reader;
            reader.read(inputFilePath.toStdString(), triangulation2);
        }
        else if (inputFilePath.endsWith(".obj", Qt::CaseInsensitive))
        {
            OBJReader reader;
            reader.read(inputFilePath.toStdString(), triangulation2);
        }
        OpenGlWidget1::Data data1 = convertTrianglulationToGraphicsObject1(triangulation2);
        openglWidgetInput1->setData1(data1);
    }
}




void Visualizer::onJoinClick()
{
    QFileDialog dialog(this);

    dialog.setFileMode(QFileDialog::Directory);

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
        "/home",
        QFileDialog::ShowDirsOnly
        | QFileDialog::DontResolveSymlinks);


    if (inputFilePath.endsWith(".stl", Qt::CaseInsensitive))
    {
        QString exportFileName = dir + "/output.obj";
        Geometry::Matrix4x4 mat;
        Transformation::Transformation t;

        ObjWriter writer;
        writer.Write(exportFileName.toStdString(), outputTriangulation);

        OBJReader reader;
        reader.read(exportFileName.toStdString(), outputTriangulation);

    
        TransformationManager manager;
        std::vector<Triangulation> tri;
        tri.push_back(triangulation);
        tri.push_back(triangulation2);
        std::vector<Triangulation> result = manager.transformObject(tri);
       
       
        OpenGlWidget::Data data3 = convertTrianglulationToGraphicsObject(result[0]);
        OpenGlWidget::Data data4 = convertTrianglulationToGraphicsObject(result[1]);
      
        for (auto i : data4.normals)
        {
            data3.normals.append(i);
        }
        for (auto j : data4.vertices)
        {
            data3.vertices.append(j);
        }
        openglWidgetOutput->setData(data3);
    }
    else if (inputFilePath.endsWith(".obj", Qt::CaseInsensitive))
    {
        QString exportFileName = dir + "/output.stl";
        Geometry::Matrix4x4 mat;
        Transformation::Transformation t;

        STLWriter writer;
        writer.Write(exportFileName.toStdString(), outputTriangulation);

        STLReader reader;
        reader.read(exportFileName.toStdString(), outputTriangulation);

        TransformationManager manager1;
        std::vector<Triangulation> tri1;
        tri1.push_back(triangulation);
        tri1.push_back(triangulation2);
        std::vector<Triangulation> result1 = manager1.transformObject(tri1);
     
        OpenGlWidget::Data data3 = convertTrianglulationToGraphicsObject(result1[0]);
        OpenGlWidget::Data data4 = convertTrianglulationToGraphicsObject(result1[1]);

        
        for (auto i : data4.normals)
        {
            data3.normals.append(i);
        }
        for (auto j : data4.vertices)
        {
            data3.vertices.append(j);
        }
        openglWidgetOutput->setData(data3);
    }
}


void Visualizer::onExportClick()
{
    QFileDialog dialog(this);

    if (inputFilePath.endsWith(".stl", Qt::CaseInsensitive))
    {
        QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save File"), "", tr("files (*.obj)"));
        ObjWriter writer;
        writer.Write(fileName.toStdString(), outputTriangulation);
    }
    else if (inputFilePath.endsWith(".obj", Qt::CaseInsensitive))
    {
        QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save File"), "", tr("files (*.stl)"));
        STLWriter writer;
        writer.Write(fileName.toStdString(), outputTriangulation);
    }
}

OpenGlWidget::Data Visualizer::convertTrianglulationToGraphicsObject(const Triangulation& inTriangulation)
{
    OpenGlWidget::Data data;
    for each (Triangle triangle in inTriangulation.Triangles)
    {
        for each (Point point in triangle.Points())
        {
            data.vertices.push_back(inTriangulation.UniqueNumbers[point.X()]);
            data.vertices.push_back(inTriangulation.UniqueNumbers[point.Y()]);
            data.vertices.push_back(inTriangulation.UniqueNumbers[point.Z()]);
        }

        Point normal = triangle.Normal();

        for (size_t i = 0; i < 3; i++)
        {
            data.normals.push_back(inTriangulation.UniqueNumbers[normal.X()]);
            data.normals.push_back(inTriangulation.UniqueNumbers[normal.Y()]);
            data.normals.push_back(inTriangulation.UniqueNumbers[normal.Z()]);
        }
    }
    return data;
}

OpenGlWidget1::Data Visualizer::convertTrianglulationToGraphicsObject1(const Triangulation& inTriangulation)
{
    OpenGlWidget1::Data data;
    for each (Triangle triangle in inTriangulation.Triangles)
    {
        for each (Point point in triangle.Points())
        {
            data.vertices.push_back(inTriangulation.UniqueNumbers[point.X()]);
            data.vertices.push_back(inTriangulation.UniqueNumbers[point.Y()]);
            data.vertices.push_back(inTriangulation.UniqueNumbers[point.Z()]);
        }

        Point normal = triangle.Normal();

        for (size_t i = 0; i < 3; i++)
        {
            data.normals.push_back(inTriangulation.UniqueNumbers[normal.X()]);
            data.normals.push_back(inTriangulation.UniqueNumbers[normal.Y()]);
            data.normals.push_back(inTriangulation.UniqueNumbers[normal.Z()]);
        }
    }

    return data;
}




