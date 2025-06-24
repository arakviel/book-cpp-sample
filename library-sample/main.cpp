#include "utils.h"
#include "book.h"

#include <iostream>
#include <iomanip>

// Book: ID, Name, AuthorId, Year, Count
// Author: ID, Name, LastName
// Reader: ID, Name, LastName, Phone
// Issue: ID, BookId, ReaderId, DateIssued, DateReturned

// Relations:
// Book - Author: Many-to-One
// Reader - Book: Many-to-Many (through Issue)
// Issue - Book: Many-to-One

int main()
{
    // --- validateString ---
    std::string name = "John Doe-O'Connor";
    if (utils::validateString(name)) {
        std::cout << "Valid name: " << name << "\n";
    }
    else {
        utils::printError("Invalid name format");
    }

    // --- validateYear ---
    int birthYear = 1995;
    if (utils::validateYear(birthYear)) {
        std::cout << "Valid year: " << birthYear << "\n";
    }
    else {
        utils::printError("Invalid year");
    }

    // --- validatePhone ---
    std::string phone = "+3809912345672";
    if (utils::validatePhone(phone)) {
        utils::printSuccess("Valid phone number");
    }
    else {
        utils::printError("Invalid phone number");
    }

    // --- currentDate ---
    std::string today = utils::currentDate();
    std::cout << "Today is: " << today << "\n";

    // --- printTableHeader ---
    std::vector<std::string> headers = { "Name", "Year", "Phone" };
    utils::printTableHeaders(headers);

    // Example row
    std::cout << std::left << std::setw(20) << "John Doe" << "|"
        << std::setw(20) << "1995" << "|"
        << std::setw(20) << "+380991234567" << "|\n";

    // --- printError & printSuccess ---
    utils::printError("Something went wrong");
    utils::printSuccess("Operation completed successfully");

    // --- backupFile ---
    std::string fileToBackup = "data.txt";  // файл повинен існувати
    utils::backupFile(fileToBackup);
    std::cout << "Backup created for: " << fileToBackup << "\n";

    // --- split ---
    std::string csv = "apple,banana,orange";
    std::vector<std::string> fruits = utils::split(csv, ',');
    std::cout << "Fruits:\n";
    for (const auto& fruit : fruits) {
        std::cout << "- " << fruit << "\n";
    }

    std::vector<Book> books;

    // --- Створення книги ---
    Book newBook = { 3, "Clean Code 3", 101, 2008, 5 };
    book::create(newBook);

    // --- Читання всіх книг ---
    book::readAll(books);
    std::cout << "\nAll books:\n";
    utils::printTableHeaders({ "ID", "Title", "Author ID", "Year", "Copies" });
    for (const auto& b : books) {
        std::cout << std::left << std::setw(20) << b.id << "|"
            << std::setw(20) << b.title << "|"
            << std::setw(20) << b.authorId << "|"
            << std::setw(20) << b.year << "|"
            << std::setw(20) << b.copies << "|\n";
    }

    // --- Пошук книги за ID ---
    int idToFind = 1;
    Book* found = book::findById(books, idToFind);
    if (found) {
        std::cout << "\nFound book with ID = " << idToFind << ": " << found->title << "\n";
    }
    else {
        utils::printError("Book not found.");
    }

    // --- Оновлення книги ---
    if (found) {
        found->copies += 10;
        book::update(*found);
    }

    // --- Пошук по назві ---
    std::cout << "\nSearch by title 'Clean':\n";
    book::searchByTitle(books, "Clean");

    // --- Сортування по року ---
    std::cout << "\nSorting books by year descending:\n";
    book::sortByYear(books, false);
    utils::printTableHeaders({ "ID", "Title", "Author ID", "Year", "Copies" });
    for (const auto& b : books) {
        std::cout << std::left << std::setw(20) << b.id << "|"
            << std::setw(20) << b.title << "|"
            << std::setw(20) << b.authorId << "|"
            << std::setw(20) << b.year << "|"
            << std::setw(20) << b.copies << "|\n";
    }

    // --- Видалення книги ---
    int idToRemove = 3;
    book::remove(idToRemove);
    std::cout << "\nAfter deleting book with ID = " << idToRemove << ":\n";
    books.clear();
    book::readAll(books);
    utils::printTableHeaders({ "ID", "Title", "Author ID", "Year", "Copies" });
    for (const auto& b : books) {
        std::cout << std::left << std::setw(20) << b.id << "|"
            << std::setw(20) << b.title << "|"
            << std::setw(20) << b.authorId << "|"
            << std::setw(20) << b.year << "|"
            << std::setw(20) << b.copies << "|\n";
    }
}