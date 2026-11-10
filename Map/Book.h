#pragma once

#include <iostream>
#include <string>

class Book {
    public:
        enum class Status {
            BOOKSHELF,
            BORROWED
        };

        std::string author;
        std::string category;
        int numberOfPages;
        Status status; 

        Book(
            std::string author,
            std::string category,
            int numberOfPages,
            Status status
            ) : author(author), category(category), numberOfPages(numberOfPages), status(status) {}

        friend std::ostream& operator<<(std::ostream& os, const Book& book) {
            std::string statusString;

            switch (book.status) {
                case Status::BOOKSHELF: statusString = "Bookshelf"; break;
                case Status::BORROWED: statusString = "Borrowed"; break;
            }
            os << book.author <<", "<< book.category << ", " << book.numberOfPages<< ", " << statusString;
            return os;
        }

};
