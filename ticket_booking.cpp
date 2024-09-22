#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

// Train class representing train information
class Train {
public:
    string source;
    string destination;
    string travelTime;
    double cost;
    bool available;

    // Default constructor
    Train() : source(""), destination(""), travelTime(""), cost(0.0), available(false) {}

    // Parameterized constructor
    Train(string src, string dest, string time, double ticketCost, bool isAvailable)
        : source(src), destination(dest), travelTime(time), cost(ticketCost), available(isAvailable) {}
};

// Ticket class representing individual ticket
class Ticket {
public:
    int ticketID;
    string passengerName;
    string source;
    string destination;
    string travelTime;
    double cost;
    bool isBooked;

    Ticket(int id, string name, string src, string dest, string time, double ticketCost)
        : ticketID(id), passengerName(name), source(src), destination(dest), travelTime(time), cost(ticketCost), isBooked(true) {}

    void displayTicket() {
        cout << "Ticket ID: " << ticketID
             << "\nPassenger Name: " << passengerName
             << "\nSource: " << source
             << "\nDestination: " << destination
             << "\nTravel Time: " << travelTime
             << "\nCost: $" << cost
             << "\nStatus: " << (isBooked ? "Booked" : "Cancelled")
             << "\n";
    }
};

// Ticket Management System class
class TicketManagementSystem {
private:
    unordered_map<int, Ticket*> ticketDatabase;
    unordered_map<int, Train> trainDatabase;
    int ticketCounter;

public:
    TicketManagementSystem() : ticketCounter(1) {
        // Adding more sample trains to the database
        trainDatabase[1] = Train("CityA", "CityB", "10:00 AM", 50.0, true);
        trainDatabase[2] = Train("CityA", "CityC", "12:00 PM", 70.0, true);
        trainDatabase[3] = Train("CityB", "CityC", "02:00 PM", 65.0, false);
        trainDatabase[4] = Train("CityA", "CityD", "03:00 PM", 80.0, true);
        trainDatabase[5] = Train("CityC", "CityD", "04:30 PM", 55.0, true);
        trainDatabase[6] = Train("CityB", "CityE", "05:00 PM", 60.0, true);
        trainDatabase[7] = Train("CityD", "CityE", "06:15 PM", 75.0, true);
    }

    void displayAvailableTrains() {
        cout << "\nAvailable Trains:\n";
        for (const auto& pair : trainDatabase) {
            if (pair.second.available) {
                cout << "Source: " << pair.second.source
                     << ", Destination: " << pair.second.destination
                     << ", Travel Time: " << pair.second.travelTime
                     << ", Cost: $" << pair.second.cost << "\n";
            }
        }
    }

    // Book a new ticket
    void bookTicket() {
        displayAvailableTrains();

        string name, source, destination;
        cout << "Enter Passenger Name: ";
        cin.ignore(); // Clear the input buffer
        getline(cin, name);
        cout << "Enter Source: ";
        cin >> source;
        cout << "Enter Destination: ";
        cin >> destination;

        // Check for available trains
        bool trainFound = false;
        for (const auto& pair : trainDatabase) {
            if (pair.second.source == source && pair.second.destination == destination && pair.second.available) {
                trainFound = true;
                Ticket* newTicket = new Ticket(ticketCounter, name, source, destination, pair.second.travelTime, pair.second.cost);
                ticketDatabase[ticketCounter] = newTicket;

                cout << "\nTicket successfully booked!\n";
                newTicket->displayTicket();
                ticketCounter++;
                break;
            }
        }

        if (!trainFound) {
            cout << "\nNo available trains from " << source << " to " << destination << ".\n";
        }
    }

    // Cancel an existing ticket
    void cancelTicket() {
        if (ticketDatabase.empty()) {
            cout << "\nNo tickets booked yet.\n";
            return;
        }

        cout << "\nBooked Tickets:\n";
        for (const auto& pair : ticketDatabase) {
            pair.second->displayTicket();
        }

        int id;
        cout << "Enter Ticket ID to Cancel: ";
        cin >> id;

        if (ticketDatabase.find(id) != ticketDatabase.end() && ticketDatabase[id]->isBooked) {
            ticketDatabase[id]->isBooked = false;
            cout << "\nTicket ID " << id << " has been cancelled.\n";
            cout << "Source: " << ticketDatabase[id]->source
                 << "\nDestination: " << ticketDatabase[id]->destination
                 << "\nTravel Time: " << ticketDatabase[id]->travelTime
                 << "\nStatus: Cancelled\n";
        } else {
            cout << "\nTicket ID not found or already cancelled.\n";
        }
    }

    // View a ticket's details
    void viewTicket() {
        int id;
        cout << "Enter Ticket ID to View: ";
        cin >> id;

        if (ticketDatabase.find(id) != ticketDatabase.end()) {
            ticketDatabase[id]->displayTicket();
        } else {
            cout << "\nTicket ID not found.\n";
        }
    }

    // View all tickets
    void viewAllTickets() {
        if (ticketDatabase.empty()) {
            cout << "\nNo tickets booked yet.\n";
            return;
        }

        cout << "\nAll Tickets:\n";
        for (const auto& pair : ticketDatabase) {
            pair.second->displayTicket();
            cout << "--------------------------------\n";
        }
    }
};

// Main function to run the system
int main() {
    TicketManagementSystem tms;
    int choice;

    while (true) {
        cout << "\nTicket Management System\n";
        cout << "1. Book Ticket\n2. Cancel Ticket\n3. View Ticket\n4. View All Tickets\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                tms.bookTicket();
                break;
            case 2:
                tms.cancelTicket();
                break;
            case 3:
                tms.viewTicket();
                break;
            case 4:
                tms.viewAllTickets();
                break;
            case 5:
                cout << "Exiting the system. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    }
    return 0;
}
