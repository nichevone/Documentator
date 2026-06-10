#include "docxmanipulator.h"

DocxManipulator::DocxManipulator() {}

void replace_all(
    std::string &text,
    const std::string &bookmarkName,
    const std::string &textToSet
    )
{
    if (bookmarkName.empty() || text.empty()) {
        return;
    }

    size_t startPos = 0;
    while ((startPos = text.find(bookmarkName, startPos)) != std::string::npos) {
        text.replace(startPos, bookmarkName.length(), textToSet);
        startPos += textToSet.length();
    }
}

// TODO: paragraph processing
// Continue working on replacing document bookmarks