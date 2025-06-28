#include "issue.h"
#include "utils.h"
#include "book.h"
#include <fstream>
#include <iostream>
#include <algorithm>

namespace issue {
    void create(Issue& issue) {
        utils::backupFile(issue::FILE_NAME);
        std::ofstream file(issue::FILE_NAME, std::ios::app);
        file << issue.id << "|" << issue.bookId << "|" << issue.readerId << "|" << issue.issueDate << "|" << issue.returnDate << "\n";
        file.close();
        utils::printSuccess("Issue created.");
    }

    void readAll(std::vector<Issue>& issues) {
        issues.clear();
        std::ifstream file(issue::FILE_NAME);
        std::string line;
        while (std::getline(file, line)) {
            auto tokens = utils::split(line, '|');
            if (tokens.size() == 5) {
                Issue issue;
                issue.id = std::stoi(tokens[0]);
                issue.bookId = std::stoi(tokens[1]);
                issue.readerId = std::stoi(tokens[2]);
                issue.issueDate = tokens[3];
                issue.returnDate = tokens[4];
                issues.push_back(issue);
            }
        }
        file.close();
    }

    void update(Issue& issue) {
        std::vector<Issue> issues;
        readAll(issues);
        for (auto& i : issues) {
            if (i.id == issue.id) {
                i = issue;
                break;
            }
        }
        utils::backupFile("issues.txt");
        std::ofstream file("issues.txt");
        for (const auto& i : issues) {
            file << i.id << "|" << i.bookId << "|" << i.readerId << "|" << i.issueDate << "|" << i.returnDate << "\n";
        }
        file.close();
        utils::printSuccess("Issue updated.");
    }

    void remove(int id) {
        std::vector<Issue> issues;
        readAll(issues);
        issues.erase(std::remove_if(issues.begin(), issues.end(), [id](const Issue& i) { return i.id == id; }), issues.end());
        utils::backupFile(issue::FILE_NAME);
        std::ofstream file(issue::FILE_NAME);
        for (const auto& i : issues) {
            file << i.id << "|" << i.bookId << "|" << i.readerId << "|" << i.issueDate << "|" << i.returnDate << "\n";
        }
        file.close();
        utils::printSuccess("Issue deleted.");
    }

    void generateReport(const std::vector<Issue>& issues, const std::vector<Book>& books) {
        std::ofstream file(issue::FILE_NAME);
        file << "Library Report: Popular Books\n";
        file << std::string(50, '-') << "\n";
        std::vector<std::pair<int, int>> bookCount;
        for (const auto& book : books) {
            bookCount.emplace_back(book.id, 0);
        }
        for (const auto& issue : issues) {
            for (auto& pair : bookCount) {
                if (pair.first == issue.bookId) pair.second++;
            }
        }
        std::sort(bookCount.begin(), bookCount.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
        for (const auto& pair : bookCount) {
            auto book = book::findById(books, pair.first);
            if (book) {
                file << "Book: " << book->title << ", Issues: " << pair.second << "\n";
            }
        }
        file.close();
        utils::printSuccess("Report generated in report.txt.");
    }
}