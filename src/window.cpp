#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
    ui->scrollArea->setWidgetResizable(true);
    setWindowTitle("Документатор");

    connect(ui->loadButton, SIGNAL(clicked(bool)), this, SLOT(loadDocument()));
    connect(ui->saveButton, SIGNAL(clicked(bool)), this, SLOT(saveDocument()));
}

Window::~Window()
{
    delete ui;
}



void Window::loadDocument()
{
    QString loadPath = QFileDialog::getOpenFileName(
        this,
        "Открыть шаблон документа docx",
        "", ""
        "Word Documents (*.docx)"
        );

    if (loadPath.isEmpty()) {
        return;
    }

    // Reset scroll area
    ui->scrollArea->setWidget(new QWidget());
    qDebug() << "Cleared QScrollArea";

    fh.addTemplateFilePath(loadPath);
    duckx::Document doc(loadPath.toStdString());
    doc.open();

    if (!doc.is_open()) {
        qDebug() << "ERROR: Could not open document:" << loadPath;
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть документ:\n" + loadPath);
        return;
    }

    // getDocumentBookmarks(doc) also concatenates bookmarks if they were splitted!
    // Need to keep that in mind
    QStringList bookmarksList = manipulator.getDocumentBookmarks(doc);
    Constants::setBookmarks(DOCUMENT_KEY, bookmarksList);

    qDebug() << "Bookmarks list:"  << bookmarksList;

    if (bookmarksList.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "В документе не найдены закладки");
        return;
    }

    setScrollArea();
    qDebug() << "Updated QScrollArea with bookmarks";
    doc.save();
}

void Window::saveDocument()
{
    QStringList valuesList = getScrollAreaValues();
    Constants::setValues(DOCUMENT_KEY, valuesList);

    QString savePath = QFileDialog::getSaveFileName(
        this,
        "Сохранить готовый документ docx",
        "", ""
        "Word Documents (*.docx)"
        );

    if (savePath.isEmpty()) {
        return;
    }

    // On linux, if you just type the file name,
    // it won't be saved with the .docx extension
    if (savePath.right(5) != ".docx") {
        savePath.append(".docx");
    }

    fh.copy(fh.getTemplateFilePath(), savePath);
    duckx::Document doc(savePath.toStdString());
    doc.open();

    if (!doc.is_open()) {
        qDebug() << "ERROR: Could not open document:" << savePath;
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить документ");
        return;
    }

    // Loop through paragraphs
    processParagraphs(doc.paragraphs());

    // Loop through tables
    for (auto table : doc.tables()) {
        for (auto row : table.rows()) {
            for (auto cell : row.cells()) {
                processParagraphs(cell.paragraphs());
            }
        }
    }

    doc.save();
    QMessageBox::information(this, "Успех", "Документ успешно сохранен");
}



void Window::processParagraphs(duckx::Paragraph& paragraphs)
{
    for (auto paragraph : paragraphs) {
        for (auto run : paragraph.runs()) {
            manipulator.replaceRunBookmarks(
                run,
                Constants::getBookmarks(DOCUMENT_KEY),
                Constants::getValues(DOCUMENT_KEY)
                );
        }
    }
}

QStringList Window::getScrollAreaValues()
{
    QStringList values;

    QList<QLineEdit*> lineEdits = ui->scrollArea->widget()->findChildren<QLineEdit*>();
    for (int i = 0; i < lineEdits.size(); ++i) {
        QString text = lineEdits.at(i)->text();
        values.append(text);
    }

    qDebug() << "Values list:" << values;
    return values;
}

void Window::setScrollArea()
{
    QStringList bookmarks = Constants::getBookmarks(DOCUMENT_KEY);
    QWidget* container = new QWidget();
    QGridLayout* gridLayout = new QGridLayout(container);

    for (int row = 0; row < bookmarks.length(); row++) {
        QLabel* label = new QLabel(formatBookmarkText(bookmarks.at(row)));
        label->setToolTip(bookmarks.at(row));
        QLineEdit* edit = new QLineEdit();

        gridLayout->addWidget(label, row, 0);
        gridLayout->addWidget(edit, row, 1);
    }

    ui->scrollArea->setWidget(container);
    gridLayout->deleteLater();
}

QString Window::formatBookmarkText(QString bookmark)
{
    // {{bookmark_name}} -> Bookmark name
    return bookmark
            .remove("{{")
            .remove("}}")
            .replace('_', ' ')
            .replace(0, 1, bookmark.at(0).toUpper());
}
