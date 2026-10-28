#include <iostream>
#include <fstream>
#include <cstdio>
#include <conio.h>
using namespace std;

class Employee
{
public:
    int id;
    char name[50];
    char department[50];
    char designation[50];
    float salary;

    void input()
    {
        cout << "Enter Employee ID: ";
        cin >> id;

        cout << "Enter Employee Name: ";
        cin.ignore();
        cin.getline(name, 50);

        cout << "Enter Department: ";
        cin.getline(department, 50);

        cout << "Enter Designation: ";
        cin.getline(designation, 50);

        cout << "Enter Salary: ";
        cin >> salary;
    }

    void display()
    {
        cout << "\nEmployee ID: " << id;
        cout << "\nName: " << name;
        cout << "\nDepartment: " << department;
        cout << "\nDesignation: " << designation;
        cout << "\nSalary: Rs. " << salary;
        cout << "\n-----------------------------\n";
    }
};

void addEmployee()
{
    Employee e;
    ofstream file("employees.dat", ios::binary | ios::app);

    if (!file)
    {
        cout << "Error opening file!\n";
        return;
    }

    e.input();
    file.write((char*)&e, sizeof(e));
    file.close();

    cout << "\nEmployee added successfully!\n";
}

void displayEmployees()
{
    Employee e;
    ifstream file("employees.dat", ios::binary);
    bool found = false;

    if (!file)
    {
        cout << "\nNo employee records found.\n";
        return;
    }

    while (file.read((char*)&e, sizeof(e)))
    {
        e.display();
        found = true;
    }

    if (!found)
        cout << "\nNo employee records found.\n";

    file.close();
}

void searchEmployee()
{
    Employee e;
    int searchID;
    bool found = false;

    cout << "Enter Employee ID to search: ";
    cin >> searchID;

    ifstream file("employees.dat", ios::binary);

    if (!file)
    {
        cout << "\nNo employee records found.\n";
        return;
    }

    while (file.read((char*)&e, sizeof(e)))
    {
        if (e.id == searchID)
        {
            e.display();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nEmployee not found!\n";

    file.close();
}

void updateEmployee()
{
    Employee e;
    int searchID;
    bool found = false;

    cout << "Enter Employee ID to update: ";
    cin >> searchID;

    ifstream file("employees.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    if (!file || !temp)
    {
        cout << "\nUnable to open file.\n";
        file.close();
        temp.close();
        remove("temp.dat");
        return;
    }

    while (file.read((char*)&e, sizeof(e)))
    {
        if (e.id == searchID)
        {
            cout << "\nEnter updated employee details:\n";
            e.input();
            found = true;
        }

        temp.write((char*)&e, sizeof(e));
    }

    file.close();
    temp.close();

    if (found)
    {
        remove("employees.dat");
        rename("temp.dat", "employees.dat");
        cout << "\nEmployee updated successfully!\n";
    }
    else
    {
        remove("temp.dat");
        cout << "\nEmployee not found!\n";
    }
}

void deleteEmployee()
{
    Employee e;
    int deleteID;
    bool found = false;

    cout << "Enter Employee ID to delete: ";
    cin >> deleteID;

    ifstream file("employees.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    if (!file || !temp)
    {
        cout << "\nUnable to open file.\n";
        file.close();
        temp.close();
        remove("temp.dat");
        return;
    }

    while (file.read((char*)&e, sizeof(e)))
    {
        if (e.id == deleteID)
        {
            found = true;
        }
        else
        {
            temp.write((char*)&e, sizeof(e));
        }
    }

    file.close();
    temp.close();

    if (found)
    {
        remove("employees.dat");
        rename("temp.dat", "employees.dat");
        cout << "\nEmployee deleted successfully!\n";
    }
    else
    {
        remove("temp.dat");
        cout << "\nEmployee not found!\n";
    }
}

int main()
{
    int choice;

    cout << "====================================\n";
    cout << "   EMPLOYEE MANAGEMENT SYSTEM\n";
    cout << "====================================\n";
    cout << "Developed by: Ajay Dhulgande\n";

    do
    {
        cout << "\n========== MAIN MENU ==========\n";
        cout << "1. Add Employee\n";
        cout << "2. Display All Employees\n";
        cout << "3. Search Employee\n";
        cout << "4. Update Employee\n";
        cout << "5. Delete Employee\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addEmployee();
                break;

            case 2:
                displayEmployees();
                break;

            case 3:
                searchEmployee();
                break;

            case 4:
                updateEmployee();
                break;

            case 5:
                deleteEmployee();
                break;

            case 6:
                cout << "\nThank you for using the system!\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 6);

    cout << "\nAjay Dhulgande";
    getch();
    return 0;
}