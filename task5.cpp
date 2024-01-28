#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

int counter = 1;

class Book
{
public:
    string title;
    string author;
    string isbn;
    bool available;

    Book ()
    {
        available = true;
    }
};

class User
{
public:
    string name;
    int id;

    User ()
    {
        id = 0;
    }
};

class Transaction
{
public:
    Book * book;
    User * user;
    bool returned;

    Transaction (Book * b, User * u)
    {
        book = b;
        user = u;
        returned = false;
    }
};

class Library
{
    vector <Book> books;
    vector <User> users;
    vector <Transaction> transactions;

public:
    Library ()
    {
        
    }

    void addBook (string t, string a, string i)
    {
        Book book;
        book.title = t;
        book.author = a;
        book.isbn = i;

        books.push_back (book);
    }

    void addUser (string n)
    {
        User user;
        user.name = n;
        user.id = counter++;

        users.push_back (user);
    }

    void showBook ()
    {
        if (books.empty())
        {
            cout << "No books available in the library." << endl;
            return;
        }

        cout << setfill ('-') << setw (111) << "-" << setfill (' ') << endl;

        cout << "|" << setw (25) << "Title" 
             << setw (21) << "|" << setw (18) << "Author" 
             << setw (13) << "|" << setw (12) << "ISBN" 
             << setw (9) << "|" << setw (12) << "Available |" << endl;

        cout << setfill ('-') << setw (111) << "-" << setfill (' ') << endl;
        
        for (int i = 0 ; i < books.size () ; i++)
        {
            cout << "|" << setw (45) << left << books [i].title
                 << "|" << setw (30) << left << books [i].author
                 << "|" << setw (20) << left << books [i].isbn
                 << "|" << setw (11) << left << (books [i].available ? "Yes" : "No");
            
            cout << "|" << endl;
        }

        cout << setfill ('-') << setw (111) << "-" << setfill (' ') << endl;
    }

    void showUser ()
    {
        if (users.empty())
        {
            cout << "No User recorded." << endl;
            return;
        }

        cout << setfill ('-') << setw (50) << "-" << setfill (' ') << endl;

        cout << "|" << setw (8) << "ID"
             << setw (8) << "|" << setw (18) << "Name" << setw (15) << "|" << endl;

        cout << setfill ('-') << setw (50) << "-" << setfill (' ') << endl;
        
        for (int i = 0 ; i < users.size () ; i++)
        {
            cout << "|" << setw (15) << left << users [i].id
                 << "|" << setw (32) << left << users [i].name;
            
            cout << "|" << endl;
        }

        cout << setfill ('-') << setw (50) << "-" << setfill (' ') << endl;
    }

    void searchBook (string s)
    {
        if (books.empty())
        {
            cout << "No books available in the library." << endl;
            return;
        }

        int count = 0;
        for (int i = 0 ; i < books.size () ; i++)
        {
            if (books [i].title == s || books [i].author == s || books [i].isbn == s)
            {
                if (count == 0)
                {
                    count++;
                    cout << endl << endl << setfill ('-') << setw (111) << "-" << setfill (' ') << endl;

                    cout << "|" << setw (25) << "Title" 
                        << setw (21) << "|" << setw (18) << "Author" 
                        << setw (13) << "|" << setw (12) << "ISBN" << 
                        setw (9) << "|" << setw (12) << "Available |" << endl;
                    cout << setfill ('-') << setw (111) << "-" << setfill (' ') << endl;
                }

                cout << "|" << setw (45) << left << books [i].title
                    << "|" << setw (30) << left << books [i].author
                    << "|" << setw (20) << left << books [i].isbn
                    << "|" << setw (11) << left << (books [i].available ? "Yes" : "No");
                cout << "|" << endl;
            }
        }

        if (count != 0)
        {
            cout << setfill ('-') << setw (111) << "-" << setfill (' ') << endl;
            return;
        }

        cout << "Invalid book entered." << endl;
    }

    void checkoutBook (string s, string n)
    {
        if (books.empty())
        {
            cout << "No books available to checkout." << endl;
            return;
        }

        for (int i = 0 ; i < books.size () ; i++)
        {
            if (books [i].title == s || books [i].isbn == s)
            {
                if (books [i].available)
                {
                    addUser (n);
                    books [i].available = false;
                    Transaction t (&books [i], &users [users.size () - 1]);
                    transactions.push_back (t);
                    cout << "Book checked out successfully." << endl;
                    return;
                }

                cout << "Book is already checked out." << endl;
                return;
            }
        }

        cout << "Invalid Book entered." << endl;
    }

    void returnBook (string s)
    {
        if (books.empty())
        {
            cout << "No books available to return." << endl;
            return;
        }

        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].title == s || books[i].isbn == s)
            {
                if (!books[i].available)
                {
                    for (int j = 0; j < transactions.size(); j++)
                    {
                        if (transactions[j].book == &books[i] && !transactions[j].returned)
                        {
                            transactions[j].returned = true;
                            books[i].available = true;
                            cout << "Book returned successfully." << endl;
                            return;
                        }
                    }
                }
                
                cout << "This book was not checked out." << endl;
                return;
            }
        }

        cout << "Invalid Book entered." << endl;
    }
};

void exit ()
{
    system ("cls");
    cout << endl << endl << endl;
    cout << setw (100) << right << "==============================================================" << endl;
    cout << setw (100) << right << "                     Thank You for using.                     " << endl;
    cout << setw (100) << right << "                        See You Again.                        " << endl;
    cout << setw (100) << right << "==============================================================" << endl;
    cout << endl << endl << endl;
}

void back (int & ch)
{
    cout << endl << endl;
    cout << setw(100) << right << "==============================================================" << endl;
    cout << setw(100) << right << "       Press corresponding number for specific operation      " << endl;
    cout << setw(100) << right << "==============================================================" << endl;
    cout << setw(100) << right << "                                                              " << endl;
    cout << setw(100) << right << "                          1. Go Back                          " << endl;
    cout << setw(100) << right << "                          0. Exit                             " << endl;
    cout << setw(100) << right << "==============================================================" << endl;
    cout << setw(100) << right << "                                                              " << endl;
    cout << setw(75) << right << "                       Enter number: ";
    cin >> ch;

    if (ch == 0)
        exit ();
}

void LMS ()
{
    Library library;

    ifstream file ("books.csv");
    string line;
    string title;
    string author;
    string isbn;

    while (getline (file, line))
    {
        stringstream part (line);

        getline (part, title, ',');
        getline (part, author, ',');
        getline (part, isbn, ',');

        if (title != "Title")
        {
            library.addBook (title, author, isbn);
        }
    }

    int choice;

    do
    {
        system("cls");
        cout << setw(100) << "==============================================================" << endl;
        cout << setw(100) << "             Welcome to Library Management System             " << endl;
        cout << setw(100) << "       Press corresponding number for specific operation      " << endl;
        cout << setw(100) << "==============================================================" << endl;
        cout << setw(100) << "                                                              " << endl;
        cout << setw(100) << "                      1. All Books                            " << endl;
        cout << setw(100) << "                      2. All Users                            " << endl;
        cout << setw(100) << "                      3. Search any Book                      " << endl;
        cout << setw(100) << "                      4. Checkout Book                        " << endl;
        cout << setw(100) << "                      5. Return Book                          " << endl;
        cout << setw(100) << "                      0. Exit                                 " << endl;
        cout << setw(100) << "                                                              " << endl;
        cout << setw(100) << "==============================================================" << endl;
        cout << setw(100) << "                                                              " << endl;
        cout << setw(75) << "                       Enter number: ";
        cin >> choice;

        bool flag = false;
        switch (choice)
        {
            case 1:
            {
                system ("cls");
                library.showBook ();
                flag = true;
                break;
            }

            case 2:
            {
                system ("cls");
                library.showUser ();
                flag = true;
                break;
            }

            case 3:
            {
                system ("cls");
                string enter;

                cin.ignore ();
                cout << "Enter Title/Author/ISBN of the book to search: ";
                getline (cin, enter);

                library.searchBook (enter);
                flag = true;
                break;
            }

            case 4:
            {
                system ("cls");
                string enter;
                string name;

                cin.ignore ();
                cout << "Enter Title/ISBN of the book to checkout: ";
                getline (cin, enter);
                cout << "Enter your name: ";
                getline (cin, name);

                library.checkoutBook (enter, name);
                flag = true;
                break;
            }

            case 5:
            {
                system ("cls");
                string enter;

                cin.ignore ();
                cout << "Enter Title/ISBN of the book to return: ";
                getline (cin, enter);

                library.returnBook (enter);
                flag = true;
                break;
            }

            case 0:
            {
                exit ();
                break;
            }

            default:
            {
                break;
            }
        }

        if (flag)
        {
            flag = false;
            back (choice);
        }

    } while (choice != 0);
}

int main ()
{
    LMS ();

    return 0;
}