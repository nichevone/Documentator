#ifndef DOCXMANIPULATOR_H
#define DOCXMANIPULATOR_H

#include "duckx.hpp"
#include <QStringList>
#include <QString>
#include <QDebug>

class DocxManipulator
{
public:
    DocxManipulator();
    QStringList getDocumentBookmarks();
    void replaceRunBookmarks(
        duckx::Run& run,
        const QStringList& bookmarks,
        const QStringList& values
        );

    void concatBookmarkIfSplitted(
        duckx::Paragraph& paragraph
        );

private:
    void replaceAllFound(
        std::string& text,
        const std::string& bookmarkName,
        const std::string& textToReplace
        );

    std::string trim(
        const std::string& str,
        const std::string& whitespace = " \t"
        );
};

#endif // DOCXMANIPULATOR_H
