// Hotel Management and Reservation System
// Naeem Khan
// Classes and Functions of the program

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <limits>

#define maxx 100

using namespace std;

int counter = 0;

ofstream outData2;

class Hotel
{
public:
    virtual void welcomeMessage() = 0;

    virtual ~Hotel()
    {
    }
};

// Derived class for Marriott Islamabad
class MarriottIslamabad : public Hotel
{
public:
    void welcomeMessage()
    {
        cout << "Welcome to Marriott Islamabad !" << endl;
    }
};

// Derived class for Marriott Peshawar
class MarriottPeshawar : public Hotel
{
public:
    void welcomeMessage()
    {
        cout << "Welcome to Marriott Peshawar !" << endl;
    }
};

class MarriottLahore : public Hotel
{
public:
    void welcomeMessage()
    {
        cout << "Welcome to Marriott Lahore !" << endl;
    }
};

class MarriottKarachi : public Hotel
{
public:
    void welcomeMessage()
    {
        cout << "Welcome to Marriott Karachi !" << endl;
    }
};

class MarriottQuetta : public Hotel
{
public:
    void welcomeMessage()
    {
        cout << "Welcome to Marriott Quetta !" << endl;
    }
};

// Class Customer
class Customer
{
public:
    char pname[100];

    char name[100];
    char address[100];
    char phone[12];
    char from_date[20];
    char to_date[20];
    float payment_advance;
    int booking_id;
    int days;
    float billAmount;
};

// Class Room
class Room
{
public:
    char type;
    char stype;
    char ac;
    int roomNumber;
    int rent;
    int status;
    Customer cust;

    int getAdvance()
    {
        return cust.payment_advance;
    }
    int getRent()
    {
        return rent;
    }
    Room addRoom(int);
    void searchRoom(int);
    void deleteRoom(int);
    void displayRoom(Room);

    int operator[](Room other)
    {
        int ReNt = rent * cust.days;
        return ReNt - other.cust.payment_advance;
    }
};

// Global Declarations
class Room rooms[maxx];

Room Room::addRoom(int rno)
{
    int RoomNo = 0;
    Room room;
    room.roomNumber = rno;

    cout << "\nType AC/Non-AC (A/N) : ";
    cin >> room.ac;
    while (cin.fail() || (room.ac != 'A' && room.ac != 'N'))
    {
        cout << "Invalid input. Please enter either 'A' for AC or 'N' for Non-AC: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> room.ac;
    }

    cout << "\nType S for Comfort / N for No Comfort (S/N) : ";
    cin >> room.type;
    while (cin.fail() || (room.type != 'S' && room.type != 'N'))
    {
        cout << "Invalid input. Please enter either 'S' for Comfort or 'N' for Non-Comfort: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> room.type;
    }

    cout << "\nType Size (Big/Small)(B/S) : ";
    cin >> room.stype;
    while (cin.fail() || (room.stype != 'B' && room.stype != 'S'))
    {
        cout << "Invalid input. Please enter either 'B' for Big or 'S' for Small: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> room.stype;
    }

    cout << "\nDaily Rent : ";
    cin >> room.rent;
    while (cin.fail() || room.rent <= 0)
    {
        cout << "Invalid input. Please enter a positive integer for rent: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> room.rent;
    }
    room.status = 0;

    cout << "\n Room Added Successfully!";

    RoomNo++;

    if (RoomNo > 0)
    {
        outData2.open("Hotel Rooms Data.csv", ios::app);

        outData2 << room.roomNumber << ","
                 << room.ac << ","
                 << room.type << ","
                 << room.stype << ","
                 << room.rent << endl;

        // Close file
        outData2.close();
        RoomNo = 0;
    }

    return room;
}

void Room::searchRoom(int rno)
{
    int i, found = 0;
    for (i = 0; i < counter; i++)
    {
        if (rooms[i].roomNumber == rno)
        {
            found = 1;
            break;
        }
    }
    if (found == 1)
    {
        cout << "Room Details\n";
        if (rooms[i].status == 1)
        {
            cout << "\nRoom is Reserved";
        }
        else
        {
            cout << "\nRoom is available";
        }
        displayRoom(rooms[i]);
    }
    else
    {
        cout << "\nRoom not found";
    }
}

void Room::displayRoom(Room tempRoom)
{
    cout << "\nRoom Number: \t" << tempRoom.roomNumber;
    cout << "\nType AC/Non-AC (A/N) " << tempRoom.ac;
    cout << "\nType Comfort (S/N) " << tempRoom.type;
    cout << "\nType Size (B/S) " << tempRoom.stype;
    cout << "\nRent: " << tempRoom.rent;
}

// Class Hotel Management
class HotelMgnt : protected Room
{
public:
    int getRent()
    {
        return rent;
    }
    void checkIn();
    void getAvailRoom();
    void searchCustomer(char *);
    void checkOut(int);
    void guestSummaryReport();
};

void HotelMgnt::guestSummaryReport()
{
    if (counter == 0)
    {
        cout << "\n No Guest in Hotel !!" << endl;
    }
    else
    {
    }

    for (int i = 0; i < counter; i++)
    {
        if (rooms[i].status == 1)
        {
            cout << "Customer First Name : " << rooms[i].cust.name << endl;
            cout << "Room Number : " << rooms[i].roomNumber << endl;
            cout << "Address (only city) : " << rooms[i].cust.address << endl;
            cout << "Phone : " << rooms[i].cust.phone << endl;
            cout << "---------------------------------------" << endl;
        }
    }
}

void HotelMgnt::checkIn()
{
    int i, found = 0, rno;

    cout << "\nEnter Room number : ";
    cin >> rno;

    for (i = 0; i < counter; i++)
    {
        if (rooms[i].roomNumber == rno)
        {
            found = 1;
            break;
        }
    }
    if (found == 1)
    {
        if (rooms[i].status == 1)
        {
            cout << "\nRoom is already Booked";
            return;
        }

        cout << "\nEnter booking id: ";
        cin >> rooms[i].cust.booking_id;
        while (cin.fail())
        {
            cout << "Invalid input. Please enter an integer for booking id: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> rooms[i].cust.booking_id;
        }

        cout << "\nEnter Customer Name (First Name): ";
        cin >> rooms[i].cust.name;

        cout << "\nEnter Address (only city): ";
        cin >> rooms[i].cust.address;

        cout << "\nEnter Phone: ";
        cin >> rooms[i].cust.phone;

        cout << "\nEnter From Date: ";
        cin >> rooms[i].cust.from_date;

        cout << "\nEnter to Date: ";
        cin >> rooms[i].cust.to_date;

        cout << "\nEnter Advance Payment: ";
        cin >> rooms[i].cust.payment_advance;
        while (cin.fail())
        {
            cout << "Invalid input. Please enter a float for advance payment: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> rooms[i].cust.payment_advance;
        }

        rooms[i].status = 1;

        cout << "\n Customer Checked-in Successfully.." << endl;
    }
}

void HotelMgnt::getAvailRoom()
{
    int found = 0;
    for (int i = 0; i < counter; i++)
    {
        if (rooms[i].status == 0)
        {
            displayRoom(rooms[i]);
            cout << "\n\nPress enter for next room" << endl;
            found = 1;
        }
    }
    if (found == 0)
    {
        cout << "\nAll rooms are reserved" << endl;
    }
}

void HotelMgnt::searchCustomer(char *pname)
{
    int found = 0;
    for (int i = 0; i < counter; i++)
    {
        if (rooms[i].status == 1 && strcmp(rooms[i].cust.name, pname) == 0)
        {
            cout << "\nCustomer Name: " << rooms[i].cust.name;
            cout << "\nRoom Number: " << rooms[i].roomNumber;
            cout << "\n\nPress enter for next record\n";
            found = 1;
        }
    }
    if (found == 0)
    {
        cout << "\nPerson not found.\n";
    }
}

void HotelMgnt::checkOut(int roomNum)
{
    int found = 0;

    for (int i = 0; i < counter; i++)
    {
        if (rooms[i].status == 1 && rooms[i].roomNumber == roomNum)
        {
            found = 1;
            cout << "\nEnter Number of Days:\t";
            cin >> cust.days;
            while (cin.fail() || cust.days <= 0)
            {
                cout << "Invalid input. Please enter a positive integer for number of days: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> cust.days;
            }

            cust.billAmount = cust.days * rooms[i].rent;

            cout << "\n\t######## CheckOut Details ########\n";
            cout << "\nCustomer Name : " << rooms[i].cust.name;
            cout << "\nRoom Number : " << rooms[i].roomNumber;
            cout << "\nAddress : " << rooms[i].cust.address;
            cout << "\nPhone : " << rooms[i].cust.phone;
            cout << "\nTotal Amount Due : " << cust.billAmount << " /";
            cout << "\nAdvance Paid: " << rooms[i].cust.payment_advance << " /";
            cout << "\n*** Total Payable: " << cust.billAmount - rooms[i].cust.payment_advance << "/ only" << endl;
            ;

            rooms[i].status = 0;
            break;
        }
    }

    if (found == 0)
    {
        cout << "Room not found or not checked-in.\n";
    }
}

// Function to manage rooms
void manageRooms()
{
    Room room;
    int opt, rno, i, flag = 0;
    do
    {
        cout << "\n### Manage Rooms ###";
        cout << "\n1. Add Room";
        cout << "\n2. Search Room";
        cout << "\n3. Back to Main Menu";
        cout << "\n\nEnter Option: ";
        cin >> opt;
        cin.clear();
        cin.ignore();

        switch (opt)
        {
        case 1:
            cout << "\nEnter Room Number: ";
            cin >> rno;
            while (cin.fail())
            {
                cout << "Invalid input. Please enter an integer for room number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> rno;
            }
            for (i = 0; i < counter; i++)
            {
                if (rooms[i].roomNumber == rno)
                {
                    flag = 1;
                }
            }
            if (flag == 1)
            {
                cout << "\nRoom Number is Present.\nPlease enter unique Number";
                flag = 0;
            }
            else
            {
                rooms[counter] = room.addRoom(rno);
                counter++;
            }
            break;
        case 2:
            cout << "\nEnter room number: ";
            cin >> rno;
            while (cin.fail())
            {
                cout << "Invalid input. Please enter an integer for room number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> rno;
            }

            cin.clear();
            cin.ignore();
            room.searchRoom(rno);
            break;
        case 3:
            break;
        default:
            cout << "\nPlease Enter correct option";
            break;
        }
    } while (opt != 3);
}
