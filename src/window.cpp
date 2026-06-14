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
    DocxManipulator manipulator;
    const QStringList values = {"14.06.2026", "123", "456", "13.06.2026", "Иванов Иван Иванович", "06.02.2000", "г. Артём"};

    // Get source.docx absolute path
    std::string sourceFilePath = fh->getTemplateFilePath("flat_card.docx");
    // Copy source.docx with with a new name temp.docx
    fh->copy(QString::fromStdString(sourceFilePath), resultFilePath);

    duckx::Document doc(resultFilePath.toStdString());
    doc.open();

    // Loop through paragraphs
    for (auto paragraph : doc.paragraphs()) {
        manipulator.concatBookmarkIfSplitted(paragraph);
        for (auto run : paragraph.runs()) {
            manipulator.replaceRunBookmarks(run, constants::FLAT_CARD_LIST, values);
        }
    }

    // Loop through tables
    for (auto table : doc.tables()) {
        for (auto row : table.rows()) {
            for (auto cell : row.cells()) {
                for (auto paragraph : cell.paragraphs()) {
                    manipulator.concatBookmarkIfSplitted(paragraph);
                    for (auto run : paragraph.runs()) {
                        manipulator.replaceRunBookmarks(run, constants::FLAT_CARD_LIST, values);
                    }
                }
            }
        }
    }

    doc.save();
    delete fh;

    QMessageBox::information(this, "Успех", "Файл успешно сохранен!");
}