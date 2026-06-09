#include "window.h"
#include "ui_window.h"

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
    QString resultFilePath = QFileDialog::getSaveFileName(
        this,
        "Сохранить готовый документ docx",
        "", ""
        "Word Documents (*.docx)"
        );

    FileHandler* fh = new FileHandler();

    // Get source.docx absolute path
    std::string sourceFilePath = fh->getTemplateFilePath("source.docx");
    // Copy source.docx with with a new name temp.docx
    fh->copy(QString::fromStdString(sourceFilePath), resultFilePath);

    duckx::Document doc(resultFilePath.toStdString());
    doc.open();

    for (auto p : doc.paragraphs()) {
        for (auto r : p.runs()) {
            qDebug() << QString::fromStdString(r.get_text());
            r.set_text("Шпиониро...");
        }
    }

    doc.save();
    delete fh;
}