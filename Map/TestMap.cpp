#include "Employee.h"													// Defines class Employee
#include "Book.h"														// Defines class Book
#include "Map.h"														// Defines template Map<Key, Value>
#include <iostream>

typedef unsigned int ID; 												// Identification number of employee
typedef std::string Title;												// Title of book
typedef Map<ID, Employee> Database; 									// Database of employees
typedef Map<Title, Book> Library;										// Library of books

using namespace std;

void addEmployees(Database& database);
void modifyEmployees(Database& database);
void addBooks(Library& library);
void modifyBooks(Library& library);
void addDuplicateEmployee(Database& database);
void findMissingEmployee(Database& database);
void addDuplicateBook(Library& library);
void findMissingBook(Library& library);

int main() {
	Database database;
	addEmployees(database);

	Database newDatabase = database;									// Make a copy of database
	newDatabase.add(830505432, Employee("Ewa Nowak", "charwoman", 43));	// Add fourth employee
	modifyEmployees(newDatabase);

	cout << "Original database:" << endl << database << endl;
	cout << "Modified database:" << endl << newDatabase << endl;

	database = newDatabase;												// Update original database

	cout << "Database after the assignment:" << endl << database << endl;

	addDuplicateEmployee(database);
	cout << "Database after adding employee with existing ID:" << endl << database << endl;

	findMissingEmployee(database);

	Library library;
	addBooks(library);

	Library newLibrary = library;										// Make a copy of library
	newLibrary.add("Lalka", Book("Boleslaw Prus", "novel", 672, Book::Status::BOOKSHELF));	// Add fourth book

	modifyBooks(newLibrary);

	cout << "Original library:" << endl << library << endl;
	cout << "Modified library:" << endl << newLibrary << endl;

	library = newLibrary;												// Update original library

	cout << "Library after the assignment:" << endl << library << endl;

	addDuplicateBook(library);
	cout << "Library after adding book with existing title:" << endl << library << endl;

	findMissingBook(library);
}

void addEmployees(Database& database) {
	database.add(761028073, Employee("Jan Kowalski", "salesman", 28)); 	// Add first employee: name: Jan Kowalski, position: salseman, age: 28,
	database.add(510212881, Employee("Adam Nowak", "storekeeper", 54));	// Add second employee
	database.add(730505129, Employee("Anna Zaradna", "secretary", 32));	// Add third employee
}

void modifyEmployees(Database& database) {
	Employee* employeePtr;

	employeePtr = database.find(510212881);								// Find employee using its ID
	employeePtr->position = "salesman";									// Modify the position of employee
	
	employeePtr = database.find(761028073);								// Find employee using its ID
	employeePtr->age = 29;												// Modify the age of employee
}

void addBooks(Library& library) {
	library.add("Pan Tadeusz", Book("Adam Mickiewicz", "poem", 384, Book::Status::BOOKSHELF));		// Add first book: title: Pan Tadeusz, author: Adam Mickiewicz, category: poem, pages: 384, status: bookshelf
	library.add("Solaris", Book("Stanislaw Lem", "science fiction", 224, Book::Status::BORROWED));		// Add second book
	library.add("Ferdydurke", Book("Witold Gombrowicz", "novel", 296, Book::Status::BORROWED));		// Add third book
}

void modifyBooks(Library& library) {
	Book* bookPtr;

	bookPtr = library.find("Solaris");									// Find book using its title
	bookPtr->status = Book::Status::BOOKSHELF;							// The book has been returned

	bookPtr = library.find("Pan Tadeusz");								// Find book using its title
	bookPtr->status = Book::Status::BORROWED;							// The book has been borrowed
}

void addDuplicateEmployee(Database& database) {
	database.add(730505129, Employee("Anna Zaradna", "manager", 33));		// Add employee with already existing ID - data should be replaced
}

void findMissingEmployee(Database& database) {
	Employee* employeePtr;

	employeePtr = database.find(111111111);									// Find employee using ID which does not exist
	if (employeePtr == nullptr)
		cout << "Employee with ID 111111111 not found" << endl << endl;
	else
		cout << "Found employee: " << *employeePtr << endl << endl;
}

void addDuplicateBook(Library& library) {
	library.add("Solaris", Book("Stanislaw Lem", "science fiction", 224, Book::Status::BORROWED));		// Add book with already existing title - data should be replaced
}

void findMissingBook(Library& library) {
	Book* bookPtr;

	bookPtr = library.find("Quo Vadis");									// Find book using title which does not exist
	if (bookPtr == nullptr)
		cout << "Book \"Quo Vadis\" not found" << endl << endl;
	else
		cout << "Found book: " << *bookPtr << endl << endl;
}
