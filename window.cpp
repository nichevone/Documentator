#include "window.h"
#include "ui_window.h"

// FOR DEBUGGING
#include <fstream>

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(testDocOpen()));
}

Window::~Window()
{
    delete ui;
}

void Window::testDocOpen()
{
    // Get build directory (debug or release, the children of build directory)
    QDir baseDirectory(QCoreApplication::applicationDirPath());

    // Get build directory
    QString directoryName = baseDirectory.dirName().toLower();

    // If not in build directory, switch to it
    if (
        directoryName == "debug" ||
        directoryName == "release"
        )
    {
        baseDirectory.cdUp();
    }

    // Get source file
    std::string sourcePath =
        baseDirectory
        .filePath("templates/source.docx")
        .toStdString();


    duckx::Document doc(sourcePath);
    doc.open();

    for (auto p : doc.paragraphs()) {
        for (auto r : p.runs()) {
            qDebug() << QString::fromStdString(r.get_text());
        }
    }
}