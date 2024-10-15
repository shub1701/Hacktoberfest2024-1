#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

class Book {
public:
    string title;
    string author;
    string isbn;
    bool available;

    Book(string t, string a, string i) : title(t), author(a), isbn(i), available(true) {}
};

class Borrower {
public:
    string name;
    vector<Book*> borrowedBooks;

    Borrower(string n) : name(n) {}
};

class Library {
private:
    vector<Book> books;
    vector<Borrower> borrowers;

public:
    void addBook(const string& title, const string& author, const string& isbn) {
        books.emplace_back(title, author, isbn);
        cout << "Book added: " << title << endl;
    }

    void searchBooks(const string& query) {
        cout << "Search results for '" << query << "':" << endl;
        bool found = false;
        for (const auto& book : books) {
            if (book.title.find(query) != string::npos || book.author.find(query) != string::npos || book.isbn == query) {
                cout << "Title: " << book.title << ", Author: " << book.author << ", ISBN: " << book.isbn
                     << ", Available: " << (book.available ? "Yes" : "No") << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No books found." << endl;
        }
    }

    void addBorrower(const string& name) {
        borrowers.emplace_back(name);
        cout << "Borrower added: " << name << endl;
    }

    void checkoutBook(const string& isbn, const string& borrowerName) {
        for (auto& book : books) {
            if (book.isbn == isbn && book.available) {
                for (auto& borrower : borrowers) {
                    if (borrower.name == borrowerName) {
                        borrower.borrowedBooks.push_back(&book);
                        book.available = false;
                        cout << borrowerName << " checked out: " << book.title << endl;
                        return;
                    }
                }
                cout << "Borrower not found." << endl;
                return;
            }
        }
        cout << "Book not available for checkout." << endl;
    }

    void returnBook(const string& isbn, const string& borrowerName) {
        for (auto& borrower : borrowers) {
            if (borrower.name == borrowerName) {
                for (auto it = borrower.borrowedBooks.begin(); it != borrower.borrowedBooks.end(); ++it) {
                    if ((*it)->isbn == isbn) {
                        (*it)->available = true;
                        borrower.borrowedBooks.erase(it);
                        cout << borrowerName << " returned: " << (*it)->title << endl;
                        return;
                    }
                }
            }
        }
        cout << "Transaction not found." << endl;
    }

    double calculateFine(int daysOverdue) {
        return daysOverdue * 0.50; // $0.50 per day
    }
};

int main() {
    Library library;
    int choice;

    do {
        cout << "\nLibrary Management System" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Search Books" << endl;
        cout << "3. Add Borrower" << endl;
        cout << "4. Checkout Book" << endl;
        cout << "5. Return Book" << endl;
        cout << "6. Calculate Fine" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";

        // Input validation for choice
        while (!(cin >> choice)) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number: ";
        }
        
        cin.ignore(); // To ignore the newline character after the choice input

        switch (choice) {
            case 1: {
                string title, author, isbn;
                cout << "Enter book title: ";
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                cout << "Enter book ISBN: ";
                getline(cin, isbn);
                library.addBook(title, author, isbn);
                break;
            }
            case 2: {
                string query;
                cout << "Enter search query (title/author/ISBN): ";
                getline(cin, query);
                library.searchBooks(query);
                break;
            }
            case 3: {
                string name;
                cout << "Enter borrower's name: ";
                getline(cin, name);
                library.addBorrower(name);
                break;
            }
            case 4: {
                string isbn, borrowerName;
                cout << "Enter book ISBN to checkout: ";
                getline(cin, isbn);
                cout << "Enter borrower's name: ";
                getline(cin, borrowerName);
                library.checkoutBook(isbn, borrowerName);
                break;
            }
            case 5: {
                string isbn, borrowerName;
                cout << "Enter book ISBN to return: ";
                getline(cin, isbn);
                cout << "Enter borrower's name: ";
                getline(cin, borrowerName);
                library.returnBook(isbn, borrowerName);
                break;
            }
            case 6: {
                int daysOverdue;
                cout << "Enter number of overdue days: ";
                
                // Input validation for daysOverdue
                while (!(cin >> daysOverdue)) {
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cout << "Invalid input. Please enter a number: ";
                }

                double fine = library.calculateFine(daysOverdue);
                cout << "Total fine: $" << fine << endl;
                break;
            }
            case 7:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}
