#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class Book {
public:
    std::string title;
    std::string author;
    std::string isbn;
    bool is_available;

    Book(std::string t, std::string a, std::string i)
        : title(t), author(a), isbn(i), is_available(true) {}
};

class Borrower {
public:
    std::string name;
    std::string id;

    Borrower(std::string n, std::string i) : name(n), id(i) {}
};

class Library {
private:
    std::vector<Book> books;
    std::unordered_map<std::string, std::string> borrowed_books; // ISBN -> Borrower ID
    std::unordered_map<std::string, int> fines; // Borrower ID -> Fine amount

public:
    void addBook(const Book &book) {
        books.push_back(book);
    }

    void searchBookByTitle(const std::string &title) {
        for (const auto &book : books) {
            if (book.title == title) {
                std::cout << "Found Book: " << book.title << " by " << book.author << " (ISBN: " << book.isbn << ")\n";
                return;
            }
        }
        std::cout << "Book not found.\n";
    }

    void searchBookByAuthor(const std::string &author) {
        for (const auto &book : books) {
            if (book.author == author) {
                std::cout << "Found Book: " << book.title << " by " << book.author << " (ISBN: " << book.isbn << ")\n";
            }
        }
    }

    void searchBookByISBN(const std::string &isbn) {
        for (const auto &book : books) {
            if (book.isbn == isbn) {
                std::cout << "Found Book: " << book.title << " by " << book.author << " (ISBN: " << book.isbn << ")\n";
                return;
            }
        }
        std::cout << "Book not found.\n";
    }

    void checkoutBook(const std::string &isbn, const Borrower &borrower) {
        for (auto &book : books) {
            if (book.isbn == isbn && book.is_available) {
                book.is_available = false;
                borrowed_books[isbn] = borrower.id;
                std::cout << "Book checked out successfully.\n";
                return;
            }
        }
        std::cout << "Book not available for checkout.\n";
    }

    void returnBook(const std::string &isbn, const Borrower &borrower) {
        auto it = borrowed_books.find(isbn);
        if (it != borrowed_books.end() && it->second == borrower.id) {
            for (auto &book : books) {
                if (book.isbn == isbn) {
                    book.is_available = true;
                    borrowed_books.erase(isbn);
                    std::cout << "Book returned successfully.\n";
                    return;
                }
            }
        } else {
            std::cout << "No record of this book being checked out by this borrower.\n";
        }
    }

    void calculateFine(const Borrower &borrower, int overdue_days) {
        int fine_per_day = 2; // Assume fine is $2 per day
        int total_fine = overdue_days * fine_per_day;
        fines[borrower.id] += total_fine;
        std::cout << "Fine for " << borrower.name << ": $" << total_fine << "\n";
    }
};

int main() {
    Library library;

    // Add some books to the library
    library.addBook(Book("The Great Gatsby", "F. Scott Fitzgerald", "123456789"));
    library.addBook(Book("1984", "George Orwell", "987654321"));
    library.addBook(Book("To Kill a Mockingbird", "Harper Lee", "192837465"));

    // Create a borrower
    Borrower borrower("John Doe", "ID001");

    int choice;
    do {
        std::cout << "\nLibrary Management System\n";
        std::cout << "1. Search Book by Title\n";
        std::cout << "2. Search Book by Author\n";
        std::cout << "3. Search Book by ISBN\n";
        std::cout << "4. Checkout Book\n";
        std::cout << "5. Return Book\n";
        std::cout << "6. Calculate Fine\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        std::string input;
        switch (choice) {
            case 1:
                std::cout << "Enter book title: ";
                std::cin.ignore(); // to ignore the newline character left in the buffer
                std::getline(std::cin, input);
                library.searchBookByTitle(input);
                break;
            case 2:
                std::cout << "Enter book author: ";
                std::cin.ignore();
                std::getline(std::cin, input);
                library.searchBookByAuthor(input);
                break;
            case 3:
                std::cout << "Enter book ISBN: ";
                std::cin.ignore();
                std::getline(std::cin, input);
                library.searchBookByISBN(input);
                break;
            case 4:
                std::cout << "Enter book ISBN to checkout: ";
                std::cin.ignore();
                std::getline(std::cin, input);
                library.checkoutBook(input, borrower);
                break;
            case 5:
                std::cout << "Enter book ISBN to return: ";
                std::cin.ignore();
                std::getline(std::cin, input);
                library.returnBook(input, borrower);
                break;
            case 6:
                int overdue_days;
                std::cout << "Enter overdue days: ";
                std::cin >> overdue_days;
                library.calculateFine(borrower, overdue_days);
                break;
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
