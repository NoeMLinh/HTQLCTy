#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int id;
	char name[50];
	char department[30];
	float salary;
} Employee;

#define MAX_EMPLOYEES 100

Employee employees[MAX_EMPLOYEES];
static int employeeCount = 0;

void addEmployee() {
	if (employeeCount >= MAX_EMPLOYEES) {
		printf("Employee list is full!\n");
		return;
	}
	Employee emp;
	printf("Enter ID: "); scanf_s("%d", &emp.id);
	printf("Enter Name: "); scanf(emp.name);
	printf("Enter Department: "); scanf(emp.department);
	printf("Enter Salary: "); scanf_s("%f", &emp.salary);
	employees[employeeCount++] = emp;
	printf("Employee added.\n");
}

void listEmployees() {
	if (employeeCount == 0) {
		printf("No employees to display.\n");
		return;
	}
	printf("\nEmployee List:\n");
	for (int i = 0; i < employeeCount; i++) {
		printf("ID: %d, Name: %s, Department: %s, Salary: %.2f\n",
			employees[i].id, employees[i].name, employees[i].department, employees[i].salary);
	}
}

void deleteEmployee(int id) {
	for (int i = 0; i < employeeCount; i++) {
		if (employees[i].id == id) {
			for (int j = i; j < employeeCount - 1; j++) {
				employees[j] = employees[j + 1];
			}
			employeeCount--;
			printf("Employee with ID %d deleted.\n", id);
			return;
		}
	}
	printf("Employee with ID %d not found.\n", id);
}

void updateEmployee(int id) {
	for (int i = 0; i < employeeCount; i++) {
		if (employees[i].id == id) {
			printf("Updating Employee ID %d:\n", id);
			printf("Enter new Name: "); scanf_s(" %[^\n]", employees[i].name);
			printf("Enter new Department: "); scanf_s(" %[^\n]", employees[i].department);
			printf("Enter new Salary: "); scanf_s("%f", &employees[i].salary);
			printf("Employee updated.\n");
			return;
		}
	}
	printf("Employee with ID %d not found.\n", id);
}

void searchEmployee(int id) {
	for (int i = 0; i < employeeCount; i++) {
		if (employees[i].id == id) {
			printf("Employee found: ID: %d, Name: %s, Department: %s, Salary: %.2f\n",
				employees[i].id, employees[i].name, employees[i].department, employees[i].salary);
			return;
		}
	}
	printf("Employee with ID %d not found.\n", id);
}

void sortEmployeesBySalary() {
	for (int i = 0; i < employeeCount - 1; i++) {
		for (int j = i + 1; j < employeeCount; j++) {
			if (employees[i].salary > employees[j].salary) {
				Employee temp = employees[i];
				employees[i] = employees[j];
				employees[j] = temp;
			}
		}
	}
	printf("Employees sorted by salary.\n");
}

void displayMenu() {
	printf("\nEmployee Management System\n");
	printf("1. Add Employee\n");
	printf("2. List Employees\n");
	printf("3. Delete Employee\n");
	printf("4. Update Employee\n");
	printf("5. Search Employee\n");
	printf("6. Sort Employees by Salary\n");
	printf("7. Exit\n");
}

void clearScreen() {
	// This is a simple way to clear the console on Windows
	system("cls");
}

void handleInput(int choice) {
	int id;
	switch (choice) {
	case 1:
		addEmployee();
		break;
	case 2:
		listEmployees();
		break;
	case 3:
		printf("Enter Employee ID to delete: ");
		scanf_s("%d", &id);
		deleteEmployee(id);
		break;
	case 4:
		printf("Enter Employee ID to update: ");
		scanf_s("%d", &id);
		updateEmployee(id);
		break;
	case 5:
		printf("Enter Employee ID to search: ");
		scanf_s("%d", &id);
		searchEmployee(id);
		break;
	case 6:
		sortEmployeesBySalary();
		break;
	case 7:
		exit(0);
	default:
		printf("Invalid choice. Please try again.\n");
	}
}