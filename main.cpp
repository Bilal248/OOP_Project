// Hotel Management and Reservation System
// Bilal Ahmad Khan and Naeem Khan
// Main of the program

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <limits>
#include "Admin.cpp"
#include "Logos.cpp"

#define maxx 100

using namespace std;

int main()
{
    ofstream outData;
    HotelMgnt hm;
    Room rm;
    Hotel *hotel;
    int opt, rno, person = 0;
    string city;
    hotelLogo();
    while (1)
    {
        Menu();
        users();

        string User;

        cout << "\n\nSelect a User:(1/2 or type exit to end the program!):";
        cin >> User;
        cin.ignore();

        if (User == "exit")
        {
            break;
        }

        if (User >= "1" && User <= "2")
        {
            int userinput = stoi(User);
            switch (userinput)
            {
            case 1:
                Admin();
                break;
            case 2:
                do
                {
                    cout << "Enter your city for reservation (islamabad,peshawar,lahore,karachi,quetta): ";
                    cin >> city;

                    if (city == "islamabad")
                    {
                        hotel = new MarriottIslamabad();
                        hotel->welcomeMessage();
                        break;
                    }
                    else if (city == "peshawar")
                    {
                        hotel = new MarriottPeshawar();
                        hotel->welcomeMessage();
                        break;
                    }

                    else if (city == "lahore")
                    {
                        hotel = new MarriottLahore();
                        hotel->welcomeMessage();
                        break;
                    }

                    else if (city == "karachi")
                    {
                        hotel = new MarriottKarachi();
                        hotel->welcomeMessage();
                        break;
                    }

                    else if (city == "quetta")
                    {
                        hotel = new MarriottQuetta();
                        hotel->welcomeMessage();
                        break;
                    }

                    else
                    {
                        cout << "Invalid city name. Please enter either 'islamabad' or 'peshawar'." << endl;
                    }
                } while (true);
                opt = 0;
                while (opt != 4)
                {
                    int customer = 0;
                    cout << "######## Hotel Management #########\n";
                    cout << "\n1. Available Rooms";
                    cout << "\n2. Check-In Room";
                    cout << "\n3. Check-Out Room";
                    cout << "\n4. Exit";

                    cout << "\n\nEnter Option: ";
                    cin >> opt;
                    cin.clear();
                    cin.ignore();
                    switch (opt)
                    {
                    case 1:
                        if (counter == 0)
                        {
                            cout << "\nRooms data is not available.\nPlease add the rooms first." << endl;
                        }
                        else
                        {
                            hm.getAvailRoom();
                        }
                        break;
                    case 2:
                        if (counter == 0)
                        {
                            cout << "\nRooms data is not available.\nPlease add the rooms first." << endl;
                        }
                        else
                        {
                            hm.checkIn();
                            person++;
                            customer++;
                        }
                        break;
                    case 3:
                        if (counter == 0)
                        {
                            cout << "\nRooms are not available.\nPlease add the rooms first." << endl;
                        }
                        else
                        {
                            cout << "Enter Room Number : ";
                            cin >> rno;
                            hm.checkOut(rno);
                        }
                        break;
                    case 4:
                        cout << "\nTHANK YOU! FOR VISITING OUR HOTEL\n";
                        break;
                    default:
                        cout << "\nPlease Enter correct option";
                        break;
                    }

                    if (person > 0)
                    {
                        float billAmount = 0;

                        string NaMe = rooms[counter - 1].cust.name;
                        string pHone = rooms[counter - 1].cust.phone;
                        int advance = rooms[counter - 1].cust.payment_advance;
                        int rNo = rooms[counter - 1].roomNumber;
                        int id = rooms[counter - 1].cust.booking_id;
                        string address = rooms[counter - 1].cust.address;
                        string from = rooms[counter - 1].cust.from_date;
                        string to = rooms[counter - 1].cust.to_date;

                        outData.open("Guests.csv", ios::app);
                        outData << endl;
                        // File Handling
                        outData << customer << "," << id << "," << NaMe << "," << pHone << "," << address << "," << rNo << "," << from << "," << to << "," << advance << "," << city << endl;

                        outData.close();
                        person = 0;
                    }
                }
            }
        }
        else
        {
            cout << "\nInvalid Input.Please choose 1 or 2. or type exit\n";
            cin.clear();
        }
    }

    return 0;
}
