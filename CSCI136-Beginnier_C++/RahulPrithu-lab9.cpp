/*
Author: Rahul Prithu
File: RahulPrithu-lab9.cpp
*/

// Lab 9
// The program allows the user to Register and/or Log in to their acounts and edit their profile.
// 

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct UserInfo													// User Info Structure
{
	string Username;
	string Password;
	string firstName;
	string lastName;
	int Phone;
	string email;

};

int mainMenu();													// Main Menu prototype

int loginMenu(UserInfo &userProfile);							// Log-In Menu prototype

void viewProfile(UserInfo &userProfile);						// View Profile prototype

void editProfile(UserInfo &userProfile);						// Edit Profile prototype

void updateProfile(UserInfo &userProfile);						// Update Profile prototype

void getUserRegistration(UserInfo &userProfile);				// Get User Registration prototype

void addUserProfile(UserInfo &userProfile);						// Add User Profile prototype

int findUser(string name, UserInfo &userProfile);				// Find User prototype

const int MAX = 1000;											// Max number of User Registrations

int main()
{
	int LogOn = 0;
	int menuChoice = 0;
	UserInfo User;
	
	while(menuChoice != 3)
	{
		menuChoice = mainMenu();
		if(menuChoice == 1)
		{
			LogOn = loginMenu(User);
				if(LogOn == 1)
				{		
					int userOption = 0;
						
						while(userOption != 3)
						{
							cout << "Welcome " << User.Username << ".\n";
							cout << "Please select an option:\n";
							cout << "\t1 - View Profile\n";
							cout << "\t2 - Edit Profile\n";
							cout << "\t3 - Log Out\n";
							cout << "Your Choice: ";
							cin >> userOption;
							cout << "\n";
							
							if(userOption == 1)
								viewProfile(User);
							else if(userOption == 2)
								editProfile(User);
							else if(userOption == 3)
								break;
							else
								cout << "Please enter a number between 1 - 3\n\n";
						};
				}
		}
		
		if(menuChoice == 2)
		{
			getUserRegistration(User);
		}
	}
	
	cout << "\nThank you.\n";
	
	return 0;
}

/* Main Menu
 * This function prints the main menu to the user
 * It asks the user to pick an option form the Main Menu
 * It prints an error if the user picks a number out of the range of the menu
 * It then return's the user's choice
 */
int mainMenu()
{
	int userChoice = 0;
	
	// while(!(userChoice > 0 && userChoice <= 3))        //     >-------AND---<     <----OR--->
	while(userChoice < 1 || userChoice > 3)
	{
	cout << "Main Menu\n";
	cout << "Welcome to the System\n";
	cout << "Please select an option from the menu below:\n";
	cout << "\t1 - Login\n";
	cout << "\t2 - Register\n";
	cout << "\t3 - Exit\n";
	cout << "Your Choice: ";
	cin >> userChoice;
	
		if(userChoice > 3)
		{
			cout << "\nPlease enter a number between 1 - 3.\n\n";
		}
	}

	return userChoice;
}

/* Log In Menu
 * If the user pick's "1" from the Main Menu, the Log In Menu is displayed
 * This function asks the user to input their username and password
 * It output's error if the username and password don't match
 */
int loginMenu(UserInfo &userProfile)
{
	int status = 0;
	string uname;
	string pwd;
	
	cout << "\nEnter your Username and Password:\n";
	cout << "Username: ";
	cin >> uname;
	cout << "Password: ";
	cin >> pwd;
	cout << "\n";
	
	status = findUser(uname, userProfile);
	
		if(status == 1 && pwd == userProfile.Password)
			return 1;
		else
		{
			cout << "Username/Password does not match.\n\n";
			return 0;
		}
}

/* View Profile
 * Prints out the current user's proile page
 * Password is hidden with *
 */
void viewProfile(UserInfo &userProfile)
{
	cout << "\nUser Account:\n";
	cout << "\nUsername: " << userProfile.Username;
	cout << "\nPassword: " << "********";
	cout << "\nFirst Name: " << userProfile.firstName;
	cout << "\nLast Name: " << userProfile.lastName;
	cout << "\nPhone Number: " << userProfile.Phone;
	cout << "\nE-mail Address: " << userProfile.email;
	cout << "\n\n";
}

/* Edit Profile
 * Prints out another sub-menu 
 * Asks's the user which part of his profile the user would like to use
 * After the user is done editing that part of the profile, it shows the sub-menu again for further editing
 */
void editProfile(UserInfo &userProfile)
{
	int editOption = 0;
	
	while(editOption != 6)
	{
		cout << "Which part of your profile would you like to change?\n";
		cout << "\t1 - Password\n";
		cout << "\t2 - First Name\n";
		cout << "\t3 - Last Name\n";
		cout << "\t4 - Phone Number\n";
		cout << "\t5 - Hunter Email\n";
		cout << "\t6 - Return to Profile Menu\n";
		cout << "Your Choice: ";
		cin >> editOption;
		cout << "\n";
	
		switch(editOption)
		{
			case 1:
					cout << "Enter New Password: "; cin >> userProfile.Password;
					updateProfile(userProfile);
					break;
			case 2:
					cout << "Enter First Name: "; cin >> userProfile.firstName;
					updateProfile(userProfile);
					break;		
			case 3:
					cout << "Enter Last Name: "; cin >> userProfile.lastName;
					updateProfile(userProfile);
					break;		
			case 4:
					cout << "Enter Phone Number: "; cin >> userProfile.Phone;
					updateProfile(userProfile);
					break;
			case 5:
					cout << "Enter E-mail ID: "; cin >> userProfile.email;
					updateProfile(userProfile);
					break;
			default:
					break;
		}
	}
	
}

/* Update Profile
 * Updates the "users.txt" with the edited information
 */
void updateProfile(UserInfo &userProfile)
{
	UserInfo allUsers[MAX];
	int nUsers = 0;
	
	fstream file;
	file.open("users.txt");
	while(!file.eof())
	{
		file >> allUsers[nUsers].Username;
		file >> allUsers[nUsers].Password;
		file >> allUsers[nUsers].firstName;
		file >> allUsers[nUsers].lastName;
		file >> allUsers[nUsers].Phone;
		file >> allUsers[nUsers].email;
		
		if(allUsers[nUsers].Username == userProfile.Username)
		{
			allUsers[nUsers].Password = userProfile.Password;
			allUsers[nUsers].firstName = userProfile.firstName;
			allUsers[nUsers].lastName = userProfile.lastName;
			allUsers[nUsers].Phone = userProfile.Phone;
			allUsers[nUsers].email = userProfile.email;
		}
		nUsers++;
	}
	
	file.close();
	file.clear();	

	file.open("users.txt");
	for(int n = 0; n < nUsers; n++)
	{
		if(allUsers[n].Username != "")
		{
		file << allUsers[n].Username << "\n";
		file << allUsers[n].Password << "\n";
		file << allUsers[n].firstName << "\n";
		file << allUsers[n].lastName << "\n";
		file << allUsers[n].Phone << "\n";
		file << allUsers[n].email << "\n";
		}
	}
	
	file.close();
	file.clear();	
}

/* Get User Registration
 * Asks the user to input username, password, first name, last name, phone number and e-mail address
 * If the username provided by the user is already taken, output error
 */
void getUserRegistration(UserInfo &userProfile)
{
	cout << "\nUser Registration:\n";
	cout << "Username: "; 	cin >> userProfile.Username;
	if(findUser(userProfile.Username, userProfile))
	{
		cout << "\n\nThis username is taken. Choose another.\n\n";
	}
	else
	{
	cout << "Password: ";	cin >> userProfile.Password;
	cout << "First Name: ";	cin >> userProfile.firstName;
	cout << "Last Name: ";	cin >> userProfile.lastName;
	cout << "Phone Number: "; 	cin >> userProfile.Phone;
	cout << "E-mail Address: "; 	cin >> userProfile.email;
	cout << "\n";
	
	addUserProfile(userProfile);
	cout << "Registration successfully completed.\n\n";
	}
}

/* Add User Profile
 * Adds the user's information to the "users.txt" file
 */
void addUserProfile(UserInfo &userProfile)
{
	ofstream file;
	file.open ("users.txt", ios::app);
	file << userProfile.Username << "\n";
	file << userProfile.Password << "\n";
	file << userProfile.firstName << "\n";
	file << userProfile.lastName << "\n";
	file << userProfile.Phone << "\n";
	file << userProfile.email << "\n";

	file.close();
	file.clear();	

}

/* Find User
 * Find's the profiles from "users.txt" for verification purposes
 * Return's foundName = 1 if User found
 */
int findUser(string name, UserInfo &userProfile)
{
	int foundName = 0;
	UserInfo aUser;
	
	ifstream file;
	file.open ("users.txt");
	while(!file.eof())
	{
		file >> aUser.Username;
		file >> aUser.Password;
		file >> aUser.firstName;
		file >> aUser.lastName;
		file >> aUser.Phone;
		file >> aUser.email;
		
		if(name == aUser.Username)
		{
			foundName = 1;
			break;
		}
	}
	
	if(foundName == 1)
	{
		userProfile.Username = aUser.Username;
		userProfile.Password = aUser.Password;
		userProfile.firstName = aUser.firstName;
		userProfile.lastName = aUser.lastName;
		userProfile.Phone = aUser.Phone;
		userProfile.email = aUser.email;
	}
	
	file.close();
	file.clear();	

	return foundName;
}
