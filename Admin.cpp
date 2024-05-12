// Hotel Management and Reservation System
// Bilal Ahmad Khan
// Admin of the program

#include <iostream>
#include "Classes.h"

#define MAX_LINE_LENGTH 200
using namespace std;

void Admin()
{
    char pname[100];
    int RoomNo = 0;

    HotelMgnt hm;

    int choice;

    char uname[40];
    char passwd[40];
    int loginSuccessful = 0;

    while (!loginSuccessful)
    {
        cout << "\nEnter your username: ";
        cin >> uname;

        if (strcmp(uname, "exit") == 0)
        {
            cout << "Returning to the menu\n"
                 << endl;
            break;
        }

        cout << "Enter your password: ";
        cin >> passwd;

        if ((strcmp(uname, "Bilal") == 0) && (strcmp(passwd, "12345") == 0)) // Store the Username and Password for Admin Login
        {
            cout << "\nYou have logged in" << endl;
            loginSuccessful = 1;

            while (1)
            {
                cout << "\n1. Manage Rooms";
                cout << "\n2. Search Customer";
                cout << "\n3. Guest Summary Report";
                cout << "\n4. Exit";

                cout << "\nEnter your choice: ";
                cin >> choice;
                if (choice >= 1 && choice <= 4)
                {
                    if (choice == 1)
                    {
                        manageRooms();
                    }

                    else if (choice == 2)
                    {
                        cout << "Enter Customer Name: ";
                        cin >> pname;
                        hm.searchCustomer(pname);
                    }

                    else if (choice == 3)
                    {
                        hm.guestSummaryReport();
                    }
                    else if (choice == 4)
                    {
                        break;
                    }

                    else
                    {
                        cout << "Please select a correct choice\n"
                             << endl;
                    }
                }

                else
                {
                    cout << "Failed, please try again\n"
                         << endl;
                }
            }
        }
        else
        {
            cout << "\nInvalid Credidentials" << endl;
            cout << "Type exit to go back to main menu" << endl;
        }
    }
}
