#ifndef DOCXMANIPULATOR_H
#define DOCXMANIPULATOR_H

#include "duckx.hpp"

class DocxManipulator
{
public:
    DocxManipulator();
    void replace_all(
        std::string &text,
        const std::string &bookmarkName,
        const std::string &textToSet
        );
};

#endif // DOCXMANIPULATOR_H
