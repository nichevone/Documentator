#include "src/docxmanipulator.h"

DocxManipulator::DocxManipulator() {}

QStringList DocxManipulator::getDocumentBookmarks(duckx::Document& doc)
{
    QStringList documentBookmarks;

    // Loop through paragraphs
    documentBookmarks.append(
        getParagraphsBookmarks(doc.paragraphs())
        );

    // Loop through tables
    for (auto table : doc.tables()) {
        for (auto row : table.rows()) {
            for (auto cell : row.cells()) {
                documentBookmarks.append(
                    getParagraphsBookmarks(cell.paragraphs())
                    );
            }
        }
    }

    return documentBookmarks;
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
        return;
    }

    std::string text = run.get_text();

    if (text.empty()) {
        return;
    }

    // Replace bookmarks that current run could have
    for (int i = 0; i < bookmarks.length(); i++) {
        replaceAllFound(
            text,
            bookmarks.at(i).toStdString(),
            values.at(i).toStdString()
            );

        run.set_text(text);
    }
}



QStringList DocxManipulator::getParagraphsBookmarks(duckx::Paragraph& paragraphs)
{
    QStringList paragraphsBookmarks;

    for (auto paragraph : paragraphs) {
        // Firstly, concatenate the bookmarks
        concatBookmarkIfSplitted(paragraph);
        for (auto run : paragraph.runs()) {

            const std::string runText = run.get_text();
            const size_t leftBracesPos = runText.find_first_of("{{");
            const size_t rightBracesPos = runText.find_first_of("}}");
            const size_t bookmarkEndPos = rightBracesPos + 2;

            if (leftBracesPos != std::string::npos &&
                rightBracesPos != std::string::npos) {

                paragraphsBookmarks.append(QString::fromStdString(
                    runText.substr(leftBracesPos, bookmarkEndPos))
                    );
            }
        }
    }

    return paragraphsBookmarks;
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

        qDebug() << QString::fromStdString(firstText) << "-"
                 << QString::fromStdString(secondText) << "-"
                 << QString::fromStdString(thirdText);

        if (onlyBraces(firstText) == "{{" && onlyBraces(thirdText) == "}}") {


            // Get the full unsplitted bookmark
            std::string fullBookmark = firstText + secondText + thirdText;

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

std::string DocxManipulator::onlyBraces(const std::string& str)
{
    const std::string leftBraces = "{{";
    const std::string rightBraces = "}}";

    const size_t leftBracesPos = str.find(leftBraces);
    const size_t rightBracesPos = str.find(rightBraces);

    if (leftBracesPos == std::string::npos && rightBracesPos == std::string::npos) {
        return "";
    }

    if (leftBracesPos != std::string::npos &&
        (rightBracesPos == std::string::npos || leftBracesPos < rightBracesPos)) {
        return leftBraces;
    }

    return rightBraces;
}
