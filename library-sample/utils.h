#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <ctime>

/*
 * Book(id, name, authorId, year, count)
 * Author(id, name, lastName)
 * Reader(id, name, lastName, phone)
 * Issue(id, bookId, readerId, issueDate, issueReturnDate (nullptr))
 */

const std::string COLOR_RED = "\033[31m";
const std::string COLOR_GREEN = "\033[32m";
const std::string COLOR_YELLOW = "\033[33m";
const std::string COLOR_RESET = "\033[0m";

namespace utils {
    const char DELIMITER = '|';

    bool validateString(const std::string& text);
    bool validateYear(int year);
    bool validatePhone(const std::string& phone);

    std::string currentDate();

    void printTableHeader(const std::vector<std::string>& headers);
    void printError(const std::string& message);
    void printSuccess(const std::string& message);

    void backupFile(const std::string& fileName);

    std::vector<std::string> split(const std::string& text, char delimiter);
}

#endif