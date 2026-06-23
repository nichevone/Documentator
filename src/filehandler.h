#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QFile>
#include <QDebug>
#include <QString>

class FileHandler
{
public:
    FileHandler();

    // Copy file so DuckX won't rewrite the original template file
    void copy(QString templateFileAbsPath, QString copyFileAbsPath);
    void addTemplateFilePath(QString path);
    QString getTemplateFilePath();

private:
    QString templateFilePath;
};

#endif // FILEHANDLER_H
