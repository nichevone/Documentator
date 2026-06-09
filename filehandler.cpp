#include "filehandler.h"

FileHandler::FileHandler()
{
    // Get build directory (debug or release, the children of build directory)
    // I hope it won't change while the program runs
    baseDirectory = new QDir(QCoreApplication::applicationDirPath());

    // Convert path to just the directory name
    QString directoryName = baseDirectory->dirName().toLower();

    // If currently not in build directory, switch to it
    if (
        directoryName == "debug" ||
        directoryName == "release"
        )
    {
        baseDirectory->cdUp();
    }

}

FileHandler::~FileHandler()
{
    delete baseDirectory;
}



std::string FileHandler::getTemplateFilePath(std::string fileName)
{
    // Get source file
    std::string sourcePath =
        baseDirectory
            ->filePath("templates/" + QString::fromStdString(fileName)) // ARGUMENT fileName USED
            .toStdString();

    return sourcePath;
}

void FileHandler::copy(QString sourceFileAbsPath, QString copyFileAbsPath)
{
    if (QFile::copy(sourceFileAbsPath, copyFileAbsPath)) {
        qDebug() << "File from:\n" << sourceFileAbsPath << "\nwas copied succesfully to:\n" << copyFileAbsPath;
    }

    qDebug() << "File copy failed (somehow)";
}