#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct Patient {
    int id;
    string name;
    int age;
    string gender;
    string disease;
};

// Function prototypes
void addPatient();
void displayAllPatients();
void searchPatient();
void updatePatient();

int main() {
    int choice;
    do {
        cout << "\n--- Hospital Management System ---\n";
        cout << "1. Add Patient\n";
        cout << "2. Display All Patients\n";
        cout << "3. Search Patient by ID\n";
        cout << "4. Update Patient Record\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addPatient(); break;
            case 2: displayAllPatients(); break;
            case 3: searchPatient(); break;
            case 4: updatePatient(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}

// Add patient
void addPatient() {
    Patient p;
    ofstream file("patients.txt", ios::app);

    cout << "\nEnter Patient ID: ";
    cin >> p.id;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, p.name);
    cout << "Enter Age: ";
    cin >> p.age;
    cin.ignore();
    cout << "Enter Gender: ";
    getline(cin, p.gender);
    cout << "Enter Disease: ";
    getline(cin, p.disease);

    file << p.id << "," << p.name << "," << p.age << "," << p.gender << "," << p.disease << endl;
    file.close();

    cout << "\nPatient record added successfully!\n";
}

// Display all patients
void displayAllPatients() {
    ifstream file("patients.txt");
    if (!file) {
        cout << "\nNo patient records found.\n";
        return;
    }

    cout << "\n--- Patient Records ---\n";
    cout << left << setw(10) << "ID" << setw(20) << "Name"
         << setw(10) << "Age" << setw(10) << "Gender"
         << setw(20) << "Disease" << endl;
    cout << string(70, '-') << endl;

    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line.empty()) continue;

        size_t pos = 0;
        string tokens[5];
        int i = 0;
        while ((pos = line.find(',')) != string::npos && i < 4) {
            tokens[i++] = line.substr(0, pos);
            line.erase(0, pos + 1);
        }
        tokens[i] = line;

        cout << left << setw(10) << tokens[0]
             << setw(20) << tokens[1]
             << setw(10) << tokens[2]
             << setw(10) << tokens[3]
             << setw(20) << tokens[4] << endl;

        found = true;
    }

    if (!found)
        cout << "No patient data available.\n";

    file.close();
}

// Search patient by ID
void searchPatient() {
    int id;
    cout << "\nEnter Patient ID to search: ";
    cin >> id;

    ifstream file("patients.txt");
    if (!file) {
        cout << "No patient records found.\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        size_t pos = line.find(',');
        int storedID = stoi(line.substr(0, pos));

        if (storedID == id) {
            cout << "\nPatient Record Found:\n" << line << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Patient with ID " << id << " not found.\n";

    file.close();
}

// Update patient record
void updatePatient() {
    int id;
    cout << "\nEnter Patient ID to update: ";
    cin >> id;
    cin.ignore();

    ifstream inFile("patients.txt");
    ofstream tempFile("temp.txt");

    string line;
    bool updated = false;

    while (getline(inFile, line)) {
        size_t pos = line.find(',');
        int storedID = stoi(line.substr(0, pos));

        if (storedID == id) {
            Patient p;
            cout << "\nEnter new details:\n";
            cout << "Name: "; getline(cin, p.name);
            cout << "Age: "; cin >> p.age; cin.ignore();
            cout << "Gender: "; getline(cin, p.gender);
            cout << "Disease: "; getline(cin, p.disease);
            p.id = id;

            tempFile << p.id << "," << p.name << "," << p.age << "," << p.gender << "," << p.disease << endl;
            updated = true;
        } else {
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (updated)
        cout << "Record updated successfully!\n";
    else
        cout << "Patient ID not found.\n";
}
