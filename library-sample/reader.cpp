#include "reader.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <algorithm>

namespace reader {
    void create(Reader& reader) {
        utils::backupFile(reader::FILE_NAME);

        std::ofstream file(reader::FILE_NAME, std::ios::app);
        file << reader.id << "|" << reader.firstName << "|" << reader.lastName << "|" << reader.phone << "\n";
        file.close();

        utils::printSuccess("Reader created.");
    }


    void readAll(std::vector<Reader>& readers) {
        readers.clear();
        std::ifstream file(reader::FILE_NAME);
        std::string line;

        while(std::getline(file, line)) {
            auto tokens = utils::split(line, utils::DELIMITER);
            if(tokens.size() == 4) {
                Reader reader = { std::stoi(tokens[0]), tokens[1], tokens[2], tokens[3] };
                readers.push_back(reader);
            }
        }

        file.close();
    }

    Reader* findById(const std::vector<Reader>& readers, int id) {
        for(const auto& reader : readers) {
            if(reader.id == id) return const_cast<Reader*>(&reader);
        }

        return nullptr;
    }


    void update(Reader& reader) {
        std::vector<Reader> readers;
        readAll(readers);

        bool isPresent = false;
        for(auto& r : readers) {
            if(r.id == reader.id) {
                isPresent = true;
                r = reader;
                break;
            }
        }

        if(isPresent) {
            utils::backupFile(reader::FILE_NAME);
            std::ofstream file(reader::FILE_NAME);
            for(const auto& r : readers)
                file << r.id << "|" << r.firstName << "|" << r.lastName << "|" << r.phone << "\n";

            file.close();
            utils::printSuccess("Reader updated.");
        }
    }
    void remove(int id) {
        std::vector<Reader> readers;
        readAll(readers);

        readers.erase(std::remove_if(readers.begin(), readers.end(),
                                     [id](const Reader& r) { return r.id == id; }),
                      readers.end());

        utils::backupFile(reader::FILE_NAME);
        std::ofstream file(reader::FILE_NAME);
        for(const auto& r : readers)
            file << r.id << "|" << r.firstName << "|" << r.lastName << "|" << r.phone << "\n";

        file.close();
        utils::printSuccess("Reader deleted.");
    }

    void searchByName(const std::vector<Reader>& readers, const std::string& name) {
        utils::printTableHeader({"ID", "First Name", "Last Name", "Phone"});
        for(const auto& reader : readers) {
            if(reader.firstName.find(name) != std::string::npos ||
               reader.lastName.find(name) != std::string::npos) {
                std::cout << std::left << std::setw(20) << reader.id << "|"
                          << std::setw(20) << reader.firstName << "|"
                          << std::setw(20) << reader.lastName << "|"
                          << std::setw(20) << reader.phone << "|\n";
            }
        }
    }
};