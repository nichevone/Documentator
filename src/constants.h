#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QStringList>
#include <unordered_map>

class Constants {
private:
    static inline std::unordered_map<std::string, std::pair<QStringList, QStringList>> bookmarksValuesMap;

public:
    static void add(std::string key, QStringList bookmarks, QStringList values) {
        // Returns success flag. Possible use in the future
        bookmarksValuesMap.try_emplace(key, bookmarks, values);
    }

    static QStringList getBookmarks(std::string key) {
        return bookmarksValuesMap.at(key).first;
    }

    static QStringList getValues(std::string key) {
        return bookmarksValuesMap.at(key).second;
    }

    static bool has(std::string key) {
        return bookmarksValuesMap.count(key) > 0;
    }
};

#endif // CONSTANTS_H
