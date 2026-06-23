#include "filehandler.h"

FileHandler::FileHandler() {}

void FileHandler::copy(QString templateFileAbsPath, QString copyFileAbsPath)
{
    if (QFile::copy(templateFileAbsPath, copyFileAbsPath)) {
        qDebug() << "File from:\n" << templateFileAbsPath << "\nwas copied succesfully to:\n" << copyFileAbsPath;
        return;
    }

    qDebug() << "File copy failed (somehow)";
}

void FileHandler::addTemplateFilePath(QString path)
{
    templateFilePath = path;
}

QString FileHandler::getTemplateFilePath()
{
    return templateFilePath;
}