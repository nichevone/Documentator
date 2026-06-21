#ifndef DOCXMANIPULATOR_H
#define DOCXMANIPULATOR_H

#include <QStringList>
#include <QString>
#include <QDebug>
#include "duckx.hpp"

class DocxManipulator
{
public:
    DocxManipulator();
    QStringList getDocumentBookmarks(duckx::Document& doc);

    void replaceRunBookmarks(
        duckx::Run& run,
        const QStringList& bookmarks,
        const QStringList& values
        );

private:
    QStringList getParagraphsBookmarks(duckx::Paragraph& paragraphs);

    void concatBookmarkIfSplitted(
        duckx::Paragraph& paragraph
        );

    void replaceAllFound(
        std::string& text,
        const std::string& bookmarkName,
        const std::string& textToReplace
        );

    std::string onlyBraces(const std::string& str);
};

#endif // DOCXMANIPULATOR_H
