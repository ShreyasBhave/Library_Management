#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

class Book {
private:
    string title, author, isbn;
    int year;
    bool available;

public:
    Book(string t, string a, string i, int y, bool av = true)
        : title(t), author(a), isbn(i), year(y), available(av) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return isbn; }
    int getYear() const { return year; }
    bool isAvailable() const { return available; }

    void setAvailability(bool av) { available = av; }

    string toFileString() const {
        return isbn + "|" + title + "|" + author + "|" + to_string(year) + "|" + (available ? "1" : "0");
    }

    static Book fromFileString(const string &line) {
        size_t pos = 0;
        vector<string> parts;
        string s = line;
        while ((pos = s.find('|')) != string::npos) {
            parts.push_back(s.substr(0, pos));
            s.erase(0, pos + 1);
        }
        parts.push_back(s);
        return Book(parts[1], parts[2], parts[0], stoi(parts[3]), parts[4] == "1");
    }
};

class Library {
private:
    vector<Book> books;

    void saveBooks() {
        ofstream file("books.txt");
        for (auto &b : books) file << b.toFileString() << "\n";
    }

public:
    Library() { loadBooks(); }

    void loadBooks() {
        books.clear();
        ifstream file("books.txt");
        string line;
        while (getline(file, line)) {
            if (!line.empty()) books.push_back(Book::fromFileString(line));
        }
    }

    void displayBooks() {
        cout << "\nAvailable Books:\n";
        for (auto &b : books) {
            cout << "Title: " << b.getTitle() << "\nAuthor: " << b.getAuthor()
                 << "\nISBN: " << b.getISBN() << "\nYear: " << b.getYear()
                 << "\nStatus: " << (b.isAvailable() ? "Available" : "Borrowed") << "\n---\n";
        }
    }

    void addBook(const Book &b) {
        books.push_back(b);
        saveBooks();
        cout << "Book added successfully.\n";
    }

    void removeBook(const string &isbn) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getISBN() == isbn) {
                books.erase(books.begin() + i);
                saveBooks();
                cout << "Book removed.\n";
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void updateBook(const string &isbn, string newTitle, string newAuthor, int newYear) {
        for (auto &b : books) {
            if (b.getISBN() == isbn) {
                b = Book(newTitle, newAuthor, isbn, newYear, b.isAvailable());
                saveBooks();
                cout << "Book updated.\n";
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void searchBook(string keyword) {
        bool found = false;
        for (auto &b : books) {
            if (b.getTitle() == keyword || b.getAuthor() == keyword || b.getISBN() == keyword) {
                cout << "Found: " << b.getTitle() << " | " << b.getAuthor()
                     << " | " << b.getISBN() << " | "
                     << (b.isAvailable() ? "Available" : "Borrowed") << "\n";
                found = true;
            }
        }
        if (!found) cout << "No matching book found.\n";
    }

    void borrowBook(const string &isbn, const string &user) {
        for (auto &b : books) {
            if (b.getISBN() == isbn) {
                if (!b.isAvailable()) { cout << "Book already borrowed.\n"; return; }
                b.setAvailability(false);
                saveBooks();

                ofstream log("borrow_history.txt", ios::app);
                time_t now = time(0);
                log << user << " borrowed " << b.getTitle() << " (ISBN: " << isbn << ") on " << ctime(&now);
                log.close();

                cout << "Book borrowed successfully.\n";
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void returnBook(const string &isbn) {
        for (auto &b : books) {
            if (b.getISBN() == isbn) {
                if (b.isAvailable()) { cout << "This book was not borrowed.\n"; return; }
                b.setAvailability(true);
                saveBooks();
                cout << "Book returned successfully.\n";
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void viewBorrowHistory() {
        ifstream log("borrow_history.txt");
        if (!log.is_open()) { cout << "No history found.\n"; return; }
        string line;
        cout << "\nBorrow History:\n";
        while (getline(log, line)) cout << line << "\n";
        log.close();
    }
};

int main() {
    Library lib;

    while (true) {
        cout << "\n1. User Mode\n2. Admin Mode\n3. Exit\nChoice: ";
        int mode; cin >> mode;

        if (mode == 1) {
            while (true) {
                cout << "\n--- User Menu ---\n";
                cout << "1. View Books\n2. Search Book\n3. Borrow Book\n4. Return Book\n5. Back\nChoice: ";
                int ch; cin >> ch;

                if (ch == 1) lib.displayBooks();
                else if (ch == 2) { string key; cout << "Enter Title/Author/ISBN: "; cin >> key; lib.searchBook(key); }
                else if (ch == 3) { string isbn, user; cout << "Enter ISBN: "; cin >> isbn; cout << "Enter Your Name: "; cin >> user; lib.borrowBook(isbn, user); }
                else if (ch == 4) { string isbn; cout << "Enter ISBN: "; cin >> isbn; lib.returnBook(isbn); }
                else if (ch == 5) break;
            }
        }
        else if (mode == 2) {
            string pass; cout << "Enter Admin Password: "; cin >> pass;
            if (pass != "admin123") { cout << "Wrong password.\n"; continue; }

            while (true) {
                cout << "\n--- Admin Menu ---\n";
                cout << "1. Add Book\n2. Remove Book\n3. Update Book\n4. View Borrow History\n5. Back\nChoice: ";
                int ch; cin >> ch;

                if (ch == 1) {
                    string t, a, i; int y;
                    cout << "Enter Title Author ISBN Year: ";
                    cin >> t >> a >> i >> y;
                    lib.addBook(Book(t, a, i, y));
                }
                else if (ch == 2) { string i; cout << "Enter ISBN: "; cin >> i; lib.removeBook(i); }
                else if (ch == 3) {
                    string i,t,a; int y;
                    cout << "Enter ISBN NewTitle NewAuthor NewYear: ";
                    cin >> i >> t >> a >> y;
                    lib.updateBook(i,t,a,y);
                }
                else if (ch == 4) lib.viewBorrowHistory();
                else if (ch == 5) break;
            }
        }
        else if (mode == 3) break;
    }
}
