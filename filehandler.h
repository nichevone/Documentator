#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QtWidgets>

class FileHandler
{
public:
    FileHandler();
    ~FileHandler();

    // Get the path of a file from the templates folder
    std::string getTemplateFilePath(std::string fileName);

    // Copy file so DuckX won't rewrite the original template file
    void copy(QString sourceFileAbsPath, QString copyFileName);

private:
    QDir* baseDirectory;
};

#endif // FILEHANDLER_H
