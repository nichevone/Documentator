#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QProcess>
#include "duckx.hpp"
#include "filehandler.h"
#include "docxmanipulator.h"
#include "constants.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class Window;
}
QT_END_NAMESPACE

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window() override;

private:
    Ui::Window *ui;
    FileHandler fh = FileHandler();
    DocxManipulator manipulator = DocxManipulator();
    const std::string DOCUMENT_KEY = "j48";

    void processParagraphs(duckx::Paragraph& paragrpahs);
    QStringList getScrollAreaValues();
    void setScrollArea();
    QString formatBookmarkText(QString bookmark);

private slots:
    void loadDocument();
    void saveDocument();

};
#endif // WINDOW_H
