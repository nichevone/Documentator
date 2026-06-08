#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "duckx.hpp"

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

private slots:
    void testDocOpen();

};
#endif // WINDOW_H
