#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>  // For std::exit
#include <cstdio>   // For std::remove and std::rename

using namespace std;

// MARK: - Interface Functions Here

void intro() {
    cout << string(100, '\n');
    cout << "---------------------------------------------";
    cout << "---------------------------------------------";
    cout << "\t\t\t\t\t\t\t\t\t       \t";
    cout << "\t\t\t\t   Made By:Shreyash Joshi\t\t\t       ";
    cout << "\t\t\t\t\t\t\t\t\t       \t";
    cout << "---------------------------------------------";
    cout << "---------------------------------------------";
}

void head() {
    // Clear screen by printing multiple new lines
    cout << string(100, '\n');
    cout << "---------------------------------------------";
    cout << "---------------------------------------------";
    cout << "\t\t\t\t\t\t\t\t\t       \t";
    cout << "\t\t\t\t   Shreyash Group of Hotels\t\t\t       ";
    cout << "\t\t\t\t\t\t\t\t\t       \t";
    cout << "---------------------------------------------";
    cout << "---------------------------------------------";
}

void time() {
    int i = 0;
    cout << "    \n\n\n    Connecting to Server\n    Syncing Data";
    while (i < 10) {
        for (volatile long long j = 5; j > 4; j++) {
            if (j == 99999) {
                cout << ".";
                break;
            }
        }
        ++i;
    }
}

// MARK: - Hotel Class Here

class hotel {
private:
    int room_no;
    string name;
    string address;
    string phone;
    int days;
    float fare;

public:
    void main_menu();        // To display the main menu
    void add();             // To book a room
    void display();         // To display the customer record
    void rooms();           // To display allotted rooms
    void edit();            // To edit the customer record
    int check(int);         // To check room status
    void modify(int);       // To modify the record
    void delete_rec(int);   // To delete the record
};

void hotel::main_menu() {
    int choice = 0;
    while (choice != 5) {
        cout << string(100, '\n'); // Clear screen by printing multiple new lines
        head();
        cout << "\n\t\t\t\t*************";
        cout << "\n\t\t\t\t* MAIN MENU *";
        cout << "\n\t\t\t\t*************";
        cout << "\n\n\n\t\t\t1.Book A Room";
        cout << "\n\t\t\t2.Customer Record";
        cout << "\n\t\t\t3.Rooms Allotted";
        cout << "\n\t\t\t4.Edit Record";
        cout << "\n\t\t\t5.Exit";
        cout << "\n\n\t\t\tEnter Your Choice: ";
        cin >> choice;
        switch (choice) {
            case 1: add(); break;
            case 2: display(); break;
            case 3: rooms(); break;
            case 4: edit(); break;
            case 5: break;
            default: {
                cout << "\n\n\t\t\tWrong choice.....!!!";
                cout << "\n\t\t\tPress any key to continue....!!";
                cin.get(); // To consume any trailing newline character
                cin.get(); // Wait for user input
            }
        }
    }
}

void hotel::add() {
    cout << string(100, '\n'); // Clear screen by printing multiple new lines
    head();
    int r, flag;
    ofstream fout("Record.dat", ios::app | ios::binary);
    cout << "\n Enter Customer Details";
    cout << "\n ----------------------";
    cout << "\n\n Room no: ";
    cin >> r;
    flag = check(r);
    if (flag)
        cout << "\n Sorry..!!! Room is already booked";
    else {
        room_no = r;
        cin.ignore(); // To ignore leftover newline characters
        cout << " Name: ";
        getline(cin, name);
        cout << " Address: ";
        getline(cin, address);
        cout << " Phone No: ";
        getline(cin, phone);
        cout << " No of Days to Checkout: ";
        cin >> days;
        fare = days * 900; // 900 is currently set as the default price per day
        fout.write(reinterpret_cast<char*>(this), sizeof(hotel));
        cout << "\n Room is booked...!!!";
    }

    cout << "\n Press any key to continue.....!!";
    cin.get(); // To consume any trailing newline character
    cin.get(); // Wait for user input
    fout.close();
}

void hotel::display() {
    cout << string(100, '\n'); // Clear screen by printing multiple new lines
    head();
    ifstream fin("Record.dat", ios::in | ios::binary);
    int r, flag = 0;
    cout << "\n Enter room no: ";
    cin >> r;
    while (fin.read(reinterpret_cast<char*>(this), sizeof(hotel))) {
        if (room_no == r) {
            cout << string(100, '\n'); // Clear screen by printing multiple new lines
            head();
            cout << "\n Customer Details";
            cout << "\n ----------------";
            cout << "\n\n Room no: " << room_no;
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone no: " << phone;
            cout << "\n Days: " << days;
            cout << "\n Total Fare: " << fare;
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        cout << "\n Sorry Room no. not found or vacant....!!";
    cout << "\n\n Press any key to continue....!!";
    cin.get(); // To consume any trailing newline character
    cin.get(); // Wait for user input
    fin.close();
}

void hotel::rooms() {
    cout << string(100, '\n'); // Clear screen by printing multiple new lines
    head();
    ifstream fin("Record.dat", ios::in | ios::binary);
    cout << "\n\t\t\t    List Of Rooms Allotted";
    cout << "\n\t\t\t    ----------------------";
    while (fin.read(reinterpret_cast<char*>(this), sizeof(hotel))) {
        cout << "\n Room no: " << room_no << "\n Name: " << name;
        cout << "\n Address: " << address << "\n Phone: " << phone;
        cout << "\n Days: " << days << "\n Total: " << fare;
        cout << "\n**********************************";
    }
    cout << "\n\n\n\t\t\tPress any key to continue.....!!";
    cin.get(); // To consume any trailing newline character
    cin.get(); // Wait for user input
    fin.close();
}

void hotel::edit() {
    cout << string(100, '\n'); // Clear screen by printing multiple new lines
    head();
    int choice, r;
    cout << "\n EDIT MENU";
    cout << "\n ---------";
    cout << "\n\n 1.Modify Customer Record";
    cout << "\n 2.Delete Customer Record";
    cout << "\n Enter your choice: ";
    cin >> choice;

    cout << string(100, '\n'); // Clear screen by printing multiple new lines
    head();
    cout << "\n Enter room no: ";
    cin >> r;
    switch (choice) {
        case 1: modify(r); break;
        case 2: delete_rec(r); break;
        default: cout << "\n Wrong Choice.....!!";
    }
    cout << "\n Press any key to continue....!!!";
    cin.get(); // To consume any trailing newline character
    cin.get(); // Wait for user input
}

int hotel::check(int r) {
    int flag = 0;
    ifstream fin("Record.dat", ios::in | ios::binary);
    while (fin.read(reinterpret_cast<char*>(this), sizeof(hotel))) {
        if (room_no == r) {
            flag = 1;
            break;
        }
    }

    fin.close();
    return flag;
}

void hotel::modify(int r) {
    cout << string(100, '\n'); // Clear screen by printing multiple new lines
    head();
    long pos;
    int flag = 0;
    fstream file("Record.dat", ios::in | ios::out | ios::binary);
    while (file.read(reinterpret_cast<char*>(this), sizeof(hotel))) {
        pos = file.tellg();
        if (room_no == r) {
            cout << "\n Enter New Details";
            cout << "\n -----------------";
            cin.ignore(); // To ignore leftover newline characters
            cout << " Name: ";
            getline(cin, name);
            cout << " Address: ";
            getline(cin, address);
            cout << " Phone no: ";
            getline(cin, phone);
            cout << " Days: ";
            cin >> days;
            fare = days * 900;
            file.seekp(pos);
            file.write(reinterpret_cast<char*>(this), sizeof(hotel));
            cout << "\n Record is modified....!!";
            flag = 1;
            break;
        }
    }

    if (flag == 0)
        cout << "\n Sorry Room no. not found or vacant...!!";
    file.close();
}

void hotel::delete_rec(int r) {
    cout << string(100, '\n'); // Clear screen by printing multiple new lines
    head();
    int flag = 0;
    char ch;
    ifstream fin("Record.dat", ios::in | ios::binary);
    ofstream fout("temp.dat", ios::out | ios::binary);
    while (fin.read(reinterpret_cast<char*>(this), sizeof(hotel))) {
        if (room_no == r) {
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone No: " << phone;
            cout << "\n Days: " << days;
            cout << "\n Total Fare: " << fare;
            cout << "\n\n Do you want to delete this record(y/n): ";
            cin >> ch;
            if (ch == 'n')
                fout.write(reinterpret_cast<char*>(this), sizeof(hotel));
            flag = 1;
            break;
        } else {
            fout.write(reinterpret_cast<char*>(this), sizeof(hotel));
        }
    }

    fin.close();
    fout.close();
    if (flag == 0)
        cout << "\n Sorry room no. not found or vacant...!!";
    else {
        remove("Record.dat");
        rename("temp.dat", "Record.dat");
    }
}

// MARK: - Main() Function Here

int main() {
    // No equivalent for textbackground and textcolor in modern C++
    hotel h;
    cout << string(100, '\n'); // Clear screen by printing multiple new lines
    intro();
    time();
    cout << "\n\n\n\t\t\tPress any key to continue....!!";

    cin.get(); // To consume any trailing newline character
    cin.get(); // Wait for user input
    cout << string(100, '\n'); // Clear screen by printing multiple new lines
    head();
    string id, pass;
    cout << "\n\n\t\t\t\tusername => ";
    cin >> id;
    cout << "\n\t\t\t\tpassword => ";
    cin >> pass;
    cout << "\n\n\t";
    time();
    cout << "\t";
    if (id == "shreyash" && pass == "123456")
        cout << "\n\n\t\t\t  !!!Login Successful!!!";
    else {
        cout << "\n\n\t\t\t!!!INVALID CREDENTIALS!!!";
        cin.get(); // To consume any trailing newline character
        cin.get(); // Wait for user input
        exit(-1);
    }
    cout << string(100, '\n'); // Clear screen by printing multiple new lines
    h.main_menu();
    cin.get(); // To consume any trailing newline character
    cin.get(); // Wait for user input

    return 0;
}
