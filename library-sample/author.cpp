#include "author.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <algorithm>


namespace author {
    void create(Author& author) {
        utils::backupFile(author::FILE_NAME);

        std::ofstream file(author::FILE_NAME, std::ios::app);
        file << author.id << "|" << author.firstName << "|" << author.lastName << "\n";
        file.close();

        utils::printSuccess("Author created.");
    }


    void readAll(std::vector<Author>& authors) {
        authors.clear();
        std::ifstream file(author::FILE_NAME);
        std::string line;

        while(std::getline(file, line)) {
            auto tokens = utils::split(line, utils::DELIMITER);
            if(tokens.size() == 3) {
                Author author = { std::stoi(tokens[0]), tokens[1], tokens[2] };
                authors.push_back(author);
            }
        }

        file.close();
    }

    Author* findById(const std::vector<Author>& authors, int id) {
        for(const auto& author : authors) {
            if(author.id == id) return const_cast<Author*>(&author);
        }

        return nullptr;
    }


    void update(Author& author) {
        std::vector<Author> authors;
        readAll(authors);

        bool isPresent = false;
        for(auto& a : authors) {
            if(a.id == author.id) {
                isPresent = true;
                a = author;
                break;
            }
        }

        if(isPresent) {
            utils::backupFile(author::FILE_NAME);
            std::ofstream file(author::FILE_NAME);
            for(const auto& a : authors)
                file << a.id << "|" << a.firstName << "|" << a.lastName << "\n";

            file.close();
            utils::printSuccess("Author updated.");
        }
    }
    void remove(int id) {
        std::vector<Author> authors;
        readAll(authors);

        authors.erase(std::remove_if(authors.begin(), authors.end(),
                                     [id](const Author& a) { return a.id == id; }),
                      authors.end());

        utils::backupFile(author::FILE_NAME);
        std::ofstream file(author::FILE_NAME);
        for(const auto& a : authors)
            file << a.id << "|" << a.firstName << "|" << a.lastName << "\n";

        file.close();
        utils::printSuccess("Author deleted.");
    }
    
    void searchByName(const std::vector<Author>& authors, const std::string& name) {
        utils::printTableHeader({"ID", "First Name", "Last Name"});
        for(const auto& author : authors) {
            if(author.firstName.find(name) != std::string::npos ||
                author.lastName.find(name) != std::string::npos) {
                std::cout << std::left << std::setw(20) << author.id << "|"
                          << std::setw(20) << author.firstName << "|"
                          << std::setw(20) << author.lastName << "|\n";
            }
        }
    }
}
