#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QStringList>
#include <unordered_map>

class Constants
{
private:
    static inline std::unordered_map<std::string, std::pair<QStringList, QStringList>> bookmarksValuesMap;

public:
    static void setBookmarks(std::string key, const QStringList& bookmarks) {
        auto& pair = bookmarksValuesMap[key];
        pair.first = bookmarks;
    }

    static void setValues(std::string key, const QStringList& values) {
        auto& pair = bookmarksValuesMap[key];
        pair.second = values;
    }

    static QStringList getBookmarks(std::string key) {
        return bookmarksValuesMap.at(key).first;
    }

    static QStringList getValues(std::string key) {
        return bookmarksValuesMap.at(key).second;
    }
};

#endif // CONSTANTS_H
