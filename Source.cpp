
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Resident {
    string surname;
    string initials;
    int roomNumber;
};

// Функція для створення файлу готелю
void createHotelFile(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {         
        file << "Sviatik Doe 101\n";
        file << "Chin Chong  102\n";
        file << "Mia Khalifa 103\n";
        file << "Adolf Sumey 104\n";
        file << "Yarouslav Imla 105\n";
        file << "David Johnson 201\n";
        file << "Emily Davis 202\n";
        file << "Adolf White 203\n";
        file << "Grace Adams 204\n";
        file << "Harry Wilson 205\n";
        file << "Ivy Clark 206\n";
        file << "Sviatik Dov 301\n";
        file << "Ivan Sem 302\n";
        file << "Mia Joo 303\n";
        file << "Bob Smith 304\n";
        file << "Charlie Brown 305\n";
        file.close();
    }
    else {
        cerr << "Error creating file: " << filename << endl;
    }
}

// Функція для пошуку мешканця за прізвищем
bool findResident(const string& filename, const string& surname, const string& searchInitials, Resident& foundResident) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }

    Resident resident;
    bool found = false;

    while (file >> resident.surname >> resident.initials >> resident.roomNumber) {
        if (resident.surname == surname && resident.initials == searchInitials) {
            if (!found) {
                foundResident = resident;
                found = true;
            }
            else {
                cout << "Multiple residents found with the same surname and initials." << endl;
                file.close();
                return false;
            }
        }
    }

    file.close();

    if (found) {
        return true;
    }
    else {
        cout << "Resident not found." << endl; // Якщо мешканця з таким прізвищем немає
        return false;
    }
}

void displayResidentInfo(const Resident& resident) { // функція яка виводить інформацію про мешканця на екран.
    cout << "Resident: " << resident.surname << " " << resident.initials << endl;
    cout << "Room Number: " << resident.roomNumber << endl;
}
void displayAllResidents(const string& filename) { // функція яка виводить інформацію про всіх мешканців готелю на екран.
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    Resident resident;
    while (file >> resident.surname >> resident.initials >> resident.roomNumber) {
        displayResidentInfo(resident);
        cout << "------------------------" << endl;
    }

    file.close();
}


void addResident(const string& filename, const Resident& newResident) { // функція яка додає нового мешканця до файлу готелю.
    ofstream file(filename, ios::app);

    if (file.is_open()) {
        file << newResident.surname << " " << newResident.initials << " " << newResident.roomNumber << "\n";
        file.close();
        cout << "Resident successfully added." << endl;
    }
    else {
        cerr << "Error opening file: " << filename << endl;
    }
}

void runMenu(const string& filename) {
    int choice;

    do {
        cout << "Menu:" << endl;
        cout << "1. Create Hotel File" << endl;
        cout << "2. Search for Resident" << endl;
        cout << "3. Display All Residents" << endl;
        cout << "4. Add Resident" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            createHotelFile(filename);
            break;

        case 2: {
            string searchSurname;
            cout << "Enter surname to search: ";
            cin >> searchSurname;

            string searchInitials;
            cout << "Enter initials to narrow down the search: ";
            cin >> searchInitials;

            Resident foundResident;
            if (findResident(filename, searchSurname, searchInitials, foundResident)) {
                displayResidentInfo(foundResident);
            }
        } break;

        case 3:
            displayAllResidents(filename);
            break;

        case 4: {
            Resident newResident;
            cout << "Enter new resident's surname: ";
            cin >> newResident.surname;
            cout << "Enter new resident's initials: ";
            cin >> newResident.initials;
            cout << "Enter new resident's room number: ";
            cin >> newResident.roomNumber;

            addResident(filename, newResident);
        } break;

        case 5:
            cout << "Exiting program." << endl;
            break;

        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
            break;
        }

    } while (choice != 5);
}

int main() {
    const string filename = "hotel.txt";
    runMenu(filename);

    return 0;
}