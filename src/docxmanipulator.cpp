#include "src/docxmanipulator.h"

DocxManipulator::DocxManipulator() {}

QStringList DocxManipulator::getDocumentBookmarks()
{
    return QStringList{};
}

void DocxManipulator::replaceRunBookmarks
    (
    duckx::Run& run,
    const QStringList& bookmarks,
    const QStringList& values
    )
{
    if (bookmarks.length() != values.length()) {
        qDebug() << "ERROR: In method replaceRunBookmarks(): the length of the bookmarks and value lists differs";
    }

    std::string text = run.get_text();
    if (text.empty()) {
        return;
    }

    // Replace bookmarks that current run could have
    for (int i = 0; i < bookmarks.length(); i++) {

        // DEBUG
        qDebug() << "-   B4    REPLACING" << QString::fromStdString(run.get_text());

        replaceAllFound(
            text,
            bookmarks.at(i).toStdString(),
            values.at(i).toStdString()
            );

        run.set_text(text);

        // DEBUG
        qDebug() << "-   AFTER REPLACING" << QString::fromStdString(run.get_text());


    }
}

void DocxManipulator::concatBookmarkIfSplitted(duckx::Paragraph& paragraph)
{ 
    std::vector<duckx::Run> runs;
    for (const auto& run : paragraph.runs()) {
        runs.push_back(run);
    }

    if (runs.size() < 3) {
        return;
    }

    for (size_t i = 0; i < runs.size() - 2; ++i) {

        std::string firstText  = runs[i].get_text();
        std::string secondText = runs[i+1].get_text();
        std::string thirdText  = runs[i+2].get_text();

        // DEBUG
        qDebug() << QString::fromStdString(firstText) << "-"
                 << QString::fromStdString(secondText) << "-"
                 << QString::fromStdString(thirdText);

        if (trim(firstText) == "{{" && trim(thirdText) == "}}") {

            // Get the full unsplitted bookmark
            std::string fullBookmark = firstText + secondText + thirdText;

            // DEBUG
            qDebug() << "FULL BOOKMARK" << QString::fromStdString(fullBookmark);

            // Set full bookmark in the second run
            runs[i+1].set_text(fullBookmark);

            // The runs in between should be "{{" and "}}"
            // So clear them
            runs[i].set_text("");
            runs[i+2].set_text("");

            // Move index by two because we checked two items already
            i += 2;
        }
    }
}



void DocxManipulator::replaceAllFound
    (
        std::string& text,
        const std::string& bookmarkName,
        const std::string& textToReplace
        )
{
    if (bookmarkName.empty() || text.empty()) {
        return;
    }

    size_t startPos = 0;
    while ((startPos = text.find(bookmarkName, startPos)) != std::string::npos) {
        text.replace(startPos, bookmarkName.length(), textToReplace);
        startPos += textToReplace.length();
    }
}

std::string DocxManipulator::trim(
    const std::string& str,
    const std::string& whitespace
    )
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos) {
        return ""; // no content
    }

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}