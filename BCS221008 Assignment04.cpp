#include <iostream>
#include <string>

using namespace std;

// Base Class: Item (Abstract)
class Item {
protected:
    int itemID;
    string title;
    bool availability;

public:
    Item(int id, string t) : itemID(id), title(t), availability(true) {}

    virtual void getItemDetails() const = 0;
    virtual bool checkAvailability() const {
        return availability;
    }
    virtual void checkOut() {
        if (availability) {
            availability = false;
            cout << title << " has been checked out." << endl;
        } else {
            cout << title << " is currently unavailable." << endl;
        }
    }
    virtual void checkIn() {
        availability = true;
        cout << title << " has been checked in." << endl;
    }
};

// Derived Class: Book
class Book : public Item {
private:
    string author;
    string ISBN;

public:
    Book(int id, string t, string a, string isbn) : Item(id, t), author(a), ISBN(isbn) {}

    void getItemDetails() const override {
        cout << "Book ID: " << itemID << "\nTitle: " << title << "\nAuthor: " << author << "\nISBN: " << ISBN << "\nAvailability: " << (availability ? "Available" : "Checked Out") << endl;
    }
};

// Derived Class: Journal
class Journal : public Item {
private:
    string publisher;
    int issueNumber;

public:
    Journal(int id, string t, string p, int issue) : Item(id, t), publisher(p), issueNumber(issue) {}

    void getItemDetails() const override {
        cout << "Journal ID: " << itemID << "\nTitle: " << title << "\nPublisher: " << publisher << "\nIssue Number: " << issueNumber << "\nAvailability: " << (availability ? "Available" : "Checked Out") << endl;
    }
};

// Class: Member
class Member {
private:
    int memberID;
    string name;
    string contactInfo;
    int loanLimit;
    int currentLoans;

public:
    Member(int id, string n, string contact, int limit) : memberID(id), name(n), contactInfo(contact), loanLimit(limit), currentLoans(0) {}

    void borrowItem(Item &item) {
        if (currentLoans < loanLimit && item.checkAvailability()) {
            item.checkOut();
            currentLoans++;
        } else if (currentLoans >= loanLimit) {
            cout << name << " has reached the loan limit!" << endl;
        } else {
            cout << "Item is not available for borrowing." << endl;
        }
    }

    void returnItem(Item &item) {
        item.checkIn();
        currentLoans--;
    }
};

// Class: Loan
class Loan {
private:
    int loanID;
    Item &item;
    Member &member;
    int dueDays;
    int returnDays;

public:
    Loan(int id, Item &i, Member &m, int due) : loanID(id), item(i), member(m), dueDays(due), returnDays(-1) {}

    void returnItem(int daysLate) {
        returnDays = daysLate;
        member.returnItem(item);
        calculateFine();
    }

    void calculateFine() {
        if (returnDays > dueDays) {
            int fine = (returnDays - dueDays) * 5; // Simple fine calculation: 5 units per day overdue
            cout << "Fine for overdue: " << fine << " units." << endl;
        } else {
            cout << "No fine. Item returned on time." << endl;
        }
    }
};

// Main Function
int main() {
    // Create some books and journals
    Book b1(101, "C++ Programming", "Bjarne Stroustrup", "1234567890");
    Journal j1(201, "Science Journal", "Nature", 55);

    // Create a member
    Member m1(1, "John Doe", "john@example.com", 2);

    // Borrow and return items
    m1.borrowItem(b1);
    m1.borrowItem(j1);
    m1.returnItem(b1);

    // Loan handling
    Loan l1(1, j1, m1, 7); // Due in 7 days
    l1.returnItem(10); // Returned after 10 days

    return 0;
}
