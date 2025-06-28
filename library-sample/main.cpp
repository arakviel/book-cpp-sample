#include "book.h"
#include "author.h"
#include "reader.h"
#include "issue.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <iomanip>

enum class MenuOption {
    EXIT = 0,
    ADD_BOOK, LIST_BOOKS, SEARCH_BOOK, SORT_BOOKS,
    ADD_AUTHOR, LIST_AUTHORS, SEARCH_AUTHOR,
    ADD_READER, LIST_READERS, SEARCH_READER,
    ADD_ISSUE, LIST_ISSUES, RETURN_BOOK,
    GENERATE_REPORT, DEMO
};

void demoMode() {
    Author a1 = {1, "John", "Doe"};
    Author a2 = {2, "Jane", "Smith"};
    author::create(a1);
    author::create(a2);

    Book b1 = {1, "C++ Programming", a1.id, 2020, 5};
    Book b2 = {2, "Data Structures", a2.id, 2018, 3};
    book::create(b1);
    book::create(b2);

    Reader r1 = {1, "Alice", "Johnson", "+12345678901"};
    Reader r2 = {2, "Bob", "Williams", "+12345678902"};
    reader::create(r1);
    reader::create(r2);

    Issue i1 = {1, b1.id, r1.id, utils::currentDate(), ""};
    Issue i2 = {2, b2.id, r2.id, utils::currentDate(), ""};
    issue::create(i1);
    issue::create(i2);

    utils::printSuccess("Demo data loaded.");
}

void printMenu() {
    std::cout << COLOR_YELLOW << "\nLibrary Management System\n" << COLOR_RESET;
    std::cout << "0. Exit\n"
              << "1. Add Book\n2. List Books\n3. Search Book\n4. Sort Books\n"
              << "5. Add Author\n6. List Authors\n7. Search Author\n"
              << "8. Add Reader\n9. List Readers\n10. Search Reader\n"
              << "11. Issue Book\n12. List Issues\n13. Return Book\n"
              << "14. Generate Report\n15. Demo Mode\n"
              << "Enter choice: ";
}

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--demo") {
        demoMode();
    }

    std::vector<Book> books;
    std::vector<Author> authors;
    std::vector<Reader> readers;
    std::vector<Issue> issues;

    while (true) {
        printMenu();
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (static_cast<MenuOption>(choice)) {
            case MenuOption::EXIT:
                return 0;
            case MenuOption::ADD_BOOK: {
                Book book;
                std::cout << "Enter ID: ";
                std::cin >> book.id;
                std::cin.ignore();
                std::cout << "Enter title: ";
                std::getline(std::cin, book.title);
                std::cout << "Enter author ID: ";
                std::cin >> book.authorId;
                std::cout << "Enter year: ";
                std::cin >> book.year;
                std::cout << "Enter copies: ";
                std::cin >> book.copies;
                if (utils::validateYear(book.year) && book.copies > 0) {
                    book::create(book);
                } else {
                    utils::printError("Invalid year or copies.");
                }
                break;
            }
            case MenuOption::LIST_BOOKS:
                book::readAll(books);
                utils::printTableHeader({"ID", "Title", "Author ID", "Year", "Copies"});
                for (const auto& b : books) {
                    std::cout << std::left << std::setw(20) << b.id << "|"
                              << std::setw(20) << b.title << "|"
                              << std::setw(20) << b.authorId << "|"
                              << std::setw(20) << b.year << "|"
                              << std::setw(20) << b.copies << "|\n";
                }
                break;
            case MenuOption::SEARCH_BOOK: {
                std::string title;
                std::cout << "Enter title to search: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                book::readAll(books);
                book::searchByTitle(books, title);
                break;
            }
            case MenuOption::SORT_BOOKS: {
                book::readAll(books);
                book::sortByYear(books, true);
                utils::printTableHeader({"ID", "Title", "Author ID", "Year", "Copies"});
                for (const auto& b : books) {
                    std::cout << std::left << std::setw(20) << b.id << "|"
                              << std::setw(20) << b.title << "|"
                              << std::setw(20) << b.authorId << "|"
                              << std::setw(20) << b.year << "|"
                              << std::setw(20) << b.copies << "|\n";
                }
                break;
            }
            case MenuOption::ADD_AUTHOR: {
                Author author;
                std::cout << "Enter ID: ";
                std::cin >> author.id;
                std::cin.ignore();
                std::cout << "Enter first name: ";
                std::getline(std::cin, author.firstName);
                std::cout << "Enter last name: ";
                std::getline(std::cin, author.lastName);
                if (utils::validateString(author.firstName) && utils::validateString(author.lastName)) {
                    author::create(author);
                } else {
                    utils::printError("Invalid name.");
                }
                break;
            }
            case MenuOption::LIST_AUTHORS:
                author::readAll(authors);
                utils::printTableHeader({"ID", "First Name", "Last Name"});
                for (const auto& a : authors) {
                    std::cout << std::left << std::setw(20) << a.id << "|"
                              << std::setw(20) << a.firstName << "|"
                              << std::setw(20) << a.lastName  << "|\n";
                }
                break;
            case MenuOption::SEARCH_AUTHOR: {
                std::string name;
                std::cout << "Enter name to search: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                author::readAll(authors);
                author::searchByName(authors, name);
                break;
            }
            case MenuOption::ADD_READER: {
                Reader reader;
                std::cout << "Enter ID: ";
                std::cin >> reader.id;
                std::cin.ignore();
                std::cout << "Enter first name: ";
                std::getline(std::cin, reader.firstName);
                std::cout << "Enter last name: ";
                std::getline(std::cin, reader.lastName);
                std::cout << "Enter phone: ";
                std::getline(std::cin, reader.phone);
                if (utils::validateString(reader.firstName) && utils::validateString(reader.lastName) && utils::validatePhone(reader.phone)) {
                    reader::create(reader);
                } else {
                    utils::printError("Invalid input.");
                }
                break;
            }
            case MenuOption::LIST_READERS:
                reader::readAll(readers);
                utils::printTableHeader({"ID", "First Name", "Last Name", "Phone"});
                for (const auto& r : readers) {
                    std::cout << std::left << std::setw(20) << r.id << "|"
                              << std::setw(20) << r.firstName << "|"
                              << std::setw(20) << r.lastName << "|"
                              << std::setw(20) << r.phone << "|\n";
                }
                break;
            case MenuOption::SEARCH_READER: {
                std::string name;
                std::cout << "Enter name to search: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                reader::readAll(readers);
                reader::searchByName(readers, name);
                break;
            }
            case MenuOption::ADD_ISSUE: {
                Issue issue;
                std::cout << "Enter ID: ";
                std::cin >> issue.id;
                std::cout << "Enter book ID: ";
                std::cin >> issue.bookId;
                std::cout << "Enter reader ID: ";
                std::cin >> issue.readerId;
                issue.issueDate = utils::currentDate();
                issue.returnDate = "";
                book::readAll(books);
                auto book = book::findById(books, issue.bookId);
                if (book && book->copies > 0) {
                    book->copies--;
                    book::update(*book);
                    issue::create(issue);
                } else {
                    utils::printError("Book not available.");
                }
                break;
            }
            case MenuOption::LIST_ISSUES:
                issue::readAll(issues);
                utils::printTableHeader({"ID", "Book ID", "Reader ID", "Issue Date", "Return Date"});
                for (const auto& i : issues) {
                    std::cout << std::left << std::setw(20) << i.id << "|"
                              << std::setw(20) << i.bookId << "|"
                              << std::setw(20) << i.readerId << "|"
                              << std::setw(20) << i.issueDate << "|"
                              << std::setw(20) << i.returnDate << "|\n";
                }
                break;
            case MenuOption::RETURN_BOOK: {
                int id;
                std::cout << "Enter issue ID: ";
                std::cin >> id;
                issue::readAll(issues);
                for (auto& i : issues) {
                    if (i.id == id && i.returnDate.empty()) {
                        i.returnDate = utils::currentDate();
                        issue::update(i);
                        book::readAll(books);
                        auto book = book::findById(books, i.bookId);
                        if (book) {
                            book->copies++;
                            book::update(*book);
                        }
                        utils::printSuccess("Book returned.");
                        break;
                    }
                }
                break;
            }
            case MenuOption::GENERATE_REPORT:
                book::readAll(books);
                issue::readAll(issues);
                issue::generateReport(issues, books);
                break;
            case MenuOption::DEMO:
                demoMode();
                break;
            default:
                utils::printError("Invalid choice.");
        }
    }
}