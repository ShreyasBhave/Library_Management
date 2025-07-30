# Library Management System (C++ OOP Project)

Overview
This project is a C++ Object-Oriented Programming (OOP) based Library Management System.
It allows users to search, borrow, and return books, while admins can manage the library inventory and view borrow history.
The project uses file handling to store book details and borrow logs for persistent data.

Features
User Mode
View all available books

Search books by title, author, or ISBN

Borrow books (updates availability status)

Return borrowed books

Admin Mode
Password-protected access (default password: admin123)

Add new books to the library

Remove books from the library

Update book details (title, author, year)

View complete borrow history

File Handling
The program automatically creates and manages two files:

books.txt – Stores all book details including title, author, ISBN, year, and availability

borrow_history.txt – Stores borrow logs with user name and timestamp

Both files are created in the same directory where the program is executed.

How to Compile and Run
Compilation
bash
Copy
Edit
g++ library.cpp -o library
Execution
bash
Copy
Edit
./library
Usage
Main Menu
markdown
Copy
Edit
1. User Mode
2. Admin Mode
3. Exit
User Menu
markdown
Copy
Edit
1. View Books
2. Search Book
3. Borrow Book
4. Return Book
5. Back
Admin Menu
markdown
Copy
Edit
1. Add Book
2. Remove Book
3. Update Book
4. View Borrow History
5. Back
Default Admin Password
nginx
Copy
Edit
admin123
Example Borrow History (borrow_history.txt)
nginx
Copy
Edit
John borrowed TheGreatGatsby (ISBN: 9780743273565) on Wed Jul 30 23:05:20 2025
Technologies Used
Language: C++

Concepts: Classes, Objects, Encapsulation, File Handling, OOP Principl
