#include "utils.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <regex>
#include <time.h>

namespace utils {
	bool validateString(const std::string& text) {
		return !text.empty() && std::all_of(text.begin(), text.end(), [](char c) {
			return std::isalpha(c) || c == ' ' || c == '-' || c == '\'';
		});
	}

	bool validateYear(int year) {
		return year >= 1800 && year <= std::time(nullptr) / 31536000 + 1970;
	}

	bool validatePhone(const std::string& phone) {
		std::regex pattern("\\+?\\d{10,12}");
		return std::regex_match(phone, pattern);
	}

	std::string currentDate() {
		std::time_t now = std::time(nullptr);
		char buf[11];
		std::tm timeStruct{};
		localtime_s(&timeStruct, &now);
        std::strftime(buf, sizeof(buf), "%Y-%m-%d", &timeStruct);
		return buf;
	}

	void printTableHeaders(const std::vector<std::string>& headers) {
		for (auto& header : headers) {
			std::cout << std::left << std::setw(20) << header << "|";
		}
		std::cout << "\n" << std::string(headers.size() * 21, '-') << "\n";
	}

	void printError(const std::string& message) {
		std::cout << COLOR_RED << "Error: " << message << COLOR_RESET << "\n";
	}

	void printSuccess(const std::string& message) {
		std::cout << COLOR_GREEN << "Success: " << message << COLOR_RESET << "\n";
	}

	void backupFile(const std::string& fileName) {
		std::ifstream source(fileName);
		if (!source) return;
		std::ofstream destination("backup_" + fileName + "_" + currentDate() + ".txt");
		destination << source.rdbuf();
		source.close();
		destination.close();
	}

	std::vector<std::string> split(const std::string& text, char delimiter) {
		std::vector<std::string> result;
		std::string token;

		for (char c : text) {
			if (c == delimiter) {
				result.push_back(token);
				token.clear();
			}
			else {
				token += c;
			}
		}

		if (!token.empty()) result.push_back(token);
		return result;
	}
}