// allow for the program to use certain modules
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <list>

using namespace std;

// Class blueprint for to do list
class TodoItem {

// Attributes of the class defined, List Number, Task name and its state of completion
private:
	int id; 
	string description;
	bool completed;

// initilising body for the class (values upon init)
// 
// Sourced Code //
public:
	TodoItem() : id(0), description(""), completed(false) {}
	~TodoItem() = default;
// Sourced Code //
// 
	// Function to create new to do item
	bool create(string new_description, int new_id) {
		// generates a random integer between 1 and 100
		id = new_id;
		description = new_description;
		return true;
	}

	// getter methods
	int getId() { return id; }
		string getDescription() { return description; }
	bool isCompleted() { return completed; }

	// Method to set completed value to true (done) or false (not done)
	void setCompleted(bool val) { completed = val; }

};

// Function to validate user
bool CheckLoggedState()
{
	// Declaration of variable and input of user details 
	string username, password, uncompare, pwcompare;
	cout << "Enter Username: "; cin >> username;
	cout << "Enter Password: "; cin >> password;

	// reading text file of the user to authenticate code
	ifstream read("d:\\" + username + ".txt");
	getline(read, uncompare);
	getline(read, pwcompare);

	// if both username and password match, return true else false
	if (uncompare == username && pwcompare == password)
	{
		return true;
	}
	else 
	{
		return false;
	}

}

// Track the current user using the system
string Profile(bool state)
{
	// re enter username for for verification
	string username, non;

	non = "Nothing";

	cout << "Confirm Your Username: ";
	cin >> username;


	// if true allow username to be passed through and displyed
	if (state = true)
	{
		return username;
	}
	else
	{
		return non;
	}

}


// Function to allow for user to sign up or Log In
string Authorisation()
{	
	// variable instantiation
	string user;
	int choice;
	string username, password;

	cout << "1: Sign Up\n2: Log In\nYour Choice: "; cin >> choice; // Allow for user to choice option to Sign Up or Log In

	// If statement for if choice 1 is picked
	if (choice == 1) 
	{
		// initialise variable

		// Allow for user input

		cout << "Enter a username: "; cin >> username;
		cout << "Entera password: "; cin >> password;

		// Store User details into external file
		ofstream file;
		file.open("d:\\" + username + ".txt");
		file << username << endl << password;
		file.close();

	}

	// Else if choice one is not picked, 2 possible outcomes
	else
	{	
		// Choice 2, To Log In
		if (choice == 2) {
			bool status = CheckLoggedState(); // Call function, store contents in variable status

			// Error handling, prompting the user to renter if details incorrect. Looping it for multiple tries
			
			if (status == false) {
				while (status == false) {
					cout << "Enter Details Again!" << endl; // alert the use of the error
					status = CheckLoggedState(); // function called in the loop
					cout << status << endl;

				}
			}

			// If the correct details have been provided, if statement to check if loop above has been broken (meaning correct details given)
			if (status == true) {

				user = Profile(true);
				cout << "Succesful login!" << endl;
				
			}
		}

		// Error handling, if neither 1 or 2 is chosen, then the user will be requested to re-enter choice
		else {
			cout << "Please choose a valid choice! (1 or 2)" << endl;
			Authorisation();
		}

	}

	return user;
}

char user_input() {
	// Main Display
	char input_option;
	cout << "Add a task [a]" << endl;
	cout << "Check off a task [c]" << endl;
	cout << "quit [q]" << endl;

	cout << "choice: ";

	// Allow the user to input their choice
	cin >> input_option;

	return input_option;
}

// Main Prpgram for the Task Manager Check List Program, all code is run here
int main()
{
	string username = Authorisation(); // Allow the user to Authorise before starting program
	
	// Variable for user to enter for a specific task
	char input_option;
	int input_id;
	string input_description;
	int input_new_id{};

	list<TodoItem> todoItems; // create list for items
	list<TodoItem>::iterator it; //iterator to allow looping through list

	srand(time(NULL));

	todoItems.clear();

	// infinite loop, to continuesly run the application
	while (1) {
		system("cls");
		cout << "LifeChecker" << endl; // display title name
		cout << "\n" << endl;

		// Sourced Code //
		// 
		// Iterating through the list
		for (it = todoItems.begin(); it != todoItems.end(); it++) {

			string completed = it->isCompleted() ? "done" : "not done"; // Check if list is completed or not

			cout << it->getId() << " | " << it->getDescription() << " | "
				<< completed << endl; // getter methods of task class, displaying its contents
		}
		// Sourced Code //
		// 
		// Prompt the user to add a task if no task has been added (if list of task is empty)
		if (todoItems.empty()) {
			cout << "Add your first Task!" << endl; cout << username; cout << endl;
		}

		cout << endl << endl;

		// Main Display
		input_option = user_input();

		//quit if the user presses q, breaks the loop and ends the program
		if (input_option == 'q') {
			cout << "Application closed" << std::endl;
			break;
		}

		// Add a new task, instantiatiing an object of task item
		else if (input_option == 'a') {

			// Customisation of to do headings
			cout << "Add a new description: ";
			cin.clear();
			cin.ignore();
			getline(cin, input_description);
			cout << "Add a new id: ";
			cin >> input_new_id; 

			// Adding task decsription to file
			ofstream file;
			file.open("d:\\" + username + ".txt", ios::app);
			file << input_new_id << endl << input_description << endl;
			file.close();

			TodoItem newItem; // new item in the list
			newItem.create(input_description,input_new_id); // instantiating
			todoItems.push_back(newItem);

		}

		// To check the list
		else if (input_option == 'c') {
			cout << "Enter id to mark completed: ";
			cin >> input_id;

			// Sourced Code //
			//
			// Iterating through loop
			for (it = todoItems.begin(); it != todoItems.end(); it++) {

				// if the input id is a valid id held in the list, the box will be ticked
				if (input_id == it->getId()) {
					it->setCompleted(true);
					break;
				}
			}
			// Sourced Code //
		}

		else {
			cout << "Enter a valid Choice! " << endl;
			system("pause");
		}

	}

	return 0;
}