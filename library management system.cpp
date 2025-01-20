#include <iostream>
#include <string>
#include <ctime>

using namespace std;

const int MAX_BOOKS = 100;
const int MAX_BORROWERS = 50;

struct Book {
    string title;
    string author;
    string ISBN;
    bool isCheckedOut;
};

struct Borrower {
    string name;
    string borrowedBookISBN;
    time_t borrowDate;  // Store the date when the book was borrowed
};

// Array to store books and borrowers
Book books[MAX_BOOKS];
Borrower borrowers[MAX_BORROWERS];

// Function to initialize books
void initializeBooks() {
    for (int i = 0; i < MAX_BOOKS; i++) {
        books[i].isCheckedOut = false;
    }
}

// Function to add a book
void addBook(string title, string author, string ISBN) {
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (books[i].ISBN == "") {  // Find an empty slot for the book
            books[i].title = title;
            books[i].author = author;
            books[i].ISBN = ISBN;
            books[i].isCheckedOut = false;
            cout << "Book added successfully!\n";
            return;
        }
    }
    cout << "Library is full, cannot add more books.\n";
}

// Function to search for books by title, author, or ISBN
void searchBook() {
    string query;
    cout << "Enter title, author, or ISBN to search: ";
    cin.ignore();
    getline(cin, query);

    bool found = false;
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (books[i].title == query || books[i].author == query || books[i].ISBN == query) {
            cout << "Book found: " << books[i].title << " by " << books[i].author << ", ISBN: " << books[i].ISBN << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No book found matching the search criteria.\n";
    }
}

// Function to check out a book to a borrower
void checkoutBook() {
    string ISBN, borrowerName;
    cout << "Enter ISBN of the book to check out: ";
    cin >> ISBN;
    cin.ignore();
    cout << "Enter borrower name: ";
    getline(cin, borrowerName);

    // Find the book in the library
    bool bookFound = false;
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (books[i].ISBN == ISBN && !books[i].isCheckedOut) {
            books[i].isCheckedOut = true;
            // Store borrower details
            for (int j = 0; j < MAX_BORROWERS; j++) {
                if (borrowers[j].name == "") {  // Empty slot for borrower
                    borrowers[j].name = borrowerName;
                    borrowers[j].borrowedBookISBN = ISBN;
                    borrowers[j].borrowDate = time(0);  // Store current time as borrow date
                    cout << "Book checked out successfully!\n";
                    bookFound = true;
                    return;
                }
            }
            cout << "No space for new borrowers.\n";
            bookFound = true;
            break;
        }
    }

    if (!bookFound) {
        cout << "Book not available or already checked out.\n";
    }
}

// Function to calculate fine for overdue books
void calculateFine() {
    string ISBN;
    cout << "Enter ISBN of the book to calculate fine: ";
    cin >> ISBN;

    // Find the borrower who has the book
    bool found = false;
    for (int i = 0; i < MAX_BORROWERS; i++) {
        if (borrowers[i].borrowedBookISBN == ISBN) {
            time_t currentTime = time(0);
            double difference = difftime(currentTime, borrowers[i].borrowDate);
            double overdueDays = difference / (60 * 60 * 24);  // Convert seconds to days

            if (overdueDays > 14) {  // Fine applies after 14 days
                double fine = (overdueDays - 14) * 0.5;  // Fine: $0.5 per day
                cout << "Overdue! Fine: $" << fine << endl;
            } else {
                cout << "No fine, book returned on time.\n";
            }
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No borrower found with this book.\n";
    }
}

// Function to return a book
void returnBook() {
    string ISBN;
    cout << "Enter ISBN of the book to return: ";
    cin >> ISBN;

    // Find the borrowed book and mark it as returned
    bool found = false;
    for (int i = 0; i < MAX_BORROWERS; i++) {
        if (borrowers[i].borrowedBookISBN == ISBN) {
            // Mark the book as returned
            for (int j = 0; j < MAX_BOOKS; j++) {
                if (books[j].ISBN == ISBN) {
                    books[j].isCheckedOut = false;
                    break;
                }
            }

            // Clear borrower record
            borrowers[i].name = "";
            borrowers[i].borrowedBookISBN = "";
            borrowers[i].borrowDate = 0;
            cout << "Book returned successfully!\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "This book is not checked out.\n";
    }
}

int main() {
    int choice;
    initializeBooks();

    while (true) {
        cout << "\nLibrary Management System Menu:\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book\n";
        cout << "3. Checkout Book\n";
        cout << "4. Return Book\n";
        cout << "5. Calculate Fine\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                {
                    string title, author, ISBN;
                    cout << "Enter book title: ";
                    cin.ignore();
                    getline(cin, title);
                    cout << "Enter book author: ";
                    getline(cin, author);
                    cout << "Enter book ISBN: ";
                    getline(cin, ISBN);
                    addBook(title, author, ISBN);
                }
                break;
            case 2:
                searchBook();
                break;
            case 3:
                checkoutBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                calculateFine();
                break;
            case 6:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice, try again.\n";
        }
    }

    return 0;
}

