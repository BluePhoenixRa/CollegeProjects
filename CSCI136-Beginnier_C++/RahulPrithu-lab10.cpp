/*
Author: Rahul Prithu
File: RahulPrithu-lab10.cpp
*/

// Lab 10
// This program is an ATM account that keeps running until it is terminated.
// It records every account and transaction in arrays.
// Starting balance is always set to 0.

#include <iostream>
#include <string>
using namespace std;

/* class User
 * Precondition:	To define a username, pinnumber and balance, the information are
 *					passed using: set_user(). And Balance is passed using setBalance().
 *					Depositing or Withdrawing ammounts are passed to the balance
 *					using addBalance() and deductBalance()
 * Postcondition:	name() returns the Username
 *					pin() returns the Pin
 *					balance() returns the Balance
 */
class User
{
	public:
	void set_user(string s, int p);
	string name(){return username;};
	int pin(){return pinnumber;};
	double balance(){return bal;};
	void setBalance(double b);
	int addBalance(User &u, double depositAmount);
	int deductBalance(User &u, double withdrawAmount);
	
	private:
	string username;
	int pinnumber;
	double bal;
};

/* class ATM
 * Precondition:	All menu functions are included inside this class.
 *					All information in this class, except for the mainMenu()
 *					are private.
 *					A total of 100 users can be created: User accounts[100]
 *					addNewAcc() prints Registration form
 *					findUser() & validate() checks registration and login information
 *					loginMenu() prints Log In Menu
 *					logout() changes loginStatus to 0
 *					accountMenu() is printed if log in is successful
 *					withdrawMenu() asks the user how much money they want to withdraw
 *					depositMenu() asks the user how much money they want to deposit
 * Postcondition:	Prints menus when the appropriate menu() is called
 *					If Username is not taken, it registers the user
 *					Validates username and password when a log in is attempted
 *					Withdrawals/Deposits made here gets updated in class User
 */
class ATM
{
	public:
	void mainMenu();
	ATM();
	
	private:
	User accounts[100];
	int totalAccounts;
	User currentUser;	
	void addNewAcc();
	int loginStatus;
	int findUser(User &u);
	int validate(User &u);
	void loginMenu();
	int logout(){loginStatus = 0; return loginStatus;};
	void accountMenu();
	int withdrawMenu();
	int depositMenu();
};

///////////////////////////////////////////////////////////////////

/* void User::set_user()
 * Precondition: 	Sends User and Pin information to username, pinnumber.
 *					Sets balance to 0
 * Postcondition:	If Username is not taken, user is registered
 */
void User::set_user(string s, int p)
{
	username = s;
	pinnumber = p;
	bal = 0.0;
}

/* void User::setBalance()
 * Precondition:	Accepts Withdrawals/Deposits made to balance
 * Postcondition:	User's balane is updated
 */
void User::setBalance(double b)
{
	bal = b;
}

/* int User:addBalance()
 * Precondition:	Takes the deposit value from depositAmount
 * Postcondition:	Adds deposit amount to balance
 */
int User::addBalance(User &u, double depositAmount)
{
	if((username == u.name()) && (pinnumber == u.pin()))
	{
		bal += depositAmount;
		u.setBalance(bal);
		return 1;
	}
	else
		return 0;
	
}

/* int User::deductBalance()
 * Precondition:	Takes withdrawal value from withdrawAmount
 * Postcondition:	Subtracts withdrawal amount from balance
 *					If withdrawAmount is larger than current balance, returns -1
 *					returns -1, insufficient fund
 */
int User::deductBalance(User &u, double withdrawAmount)
{
	if((username == u.name()) && (pinnumber == u.pin()))
	{
		if(u.balance() >= withdrawAmount)
		{
			bal -= withdrawAmount;
			u.setBalance(bal);
			return 1;		// Withdrawal Successful
		}
		else
		{
			return -1;		// Insufficient Fund
		}
	}
	else
		return 0;

}

///////////////////////////////////////////////////////////////////

/* ATM::ATM()
 * Default constructor, sets totalAccounts to 0
 */
ATM::ATM()
{
	totalAccounts = 0;
}

/* void ATM::mainMenu()
 * Precondition:	Prints the Main Menu to the user, asks the user to enter a choice
 * Postcondition:	User is taken to the next menu
 */
void ATM::mainMenu()
{
	int menuChoice = 0;
	
	while(true)
	{
		cout << "ATM Main Menu\n";
		cout << "\t1. New Accout\n";
		cout << "\t2. Login\n";
		cout << "Your Choice: ";
		cin >> menuChoice;
		cout << "\n";
		
		if(menuChoice == 1)
		{
			addNewAcc();
		}
		else if(menuChoice == 2)
		{
			loginMenu();
		}
		else
			cout << "Enter a number between 1 and 2.\n";
		menuChoice = 0;
	}
	
}

/* void ATM::addNewAcc()
 * Precondition:	Register Menu is printed out
 *					User is asked to inter Username and Pin
 * Postcondition:	If Username is available, User's account is registered
 */
void ATM::addNewAcc()
{
	string s;
	int p = 0;
	
	cout << "Register Menu\n";
	cout << "Please enter your username: ";
	cin >> s;
	cout << "Please enter your pin: ";
	cin >> p;
	cout << "\n";
	
	currentUser.set_user(s, p);
	if(!findUser(currentUser))
	{
		accounts[totalAccounts].set_user(s, p);
		totalAccounts++;
		cout << "Thanks! Your account has been created!\n\n";
	}
	else
		cout << "Username already exists. Pick a different username.\n\n";
}

/* void ATM::loginMenu()
 * Precondition:	Asks the user for their credentials
 *					Calls validate() to validate the Username and Pin
 * Postcondition:	If Username and Pin matches, user is taken to the Account Menu
 *					If Username and Pin does not match, error message is printed
 *					Asks the user to input credentials again
 */
void ATM::loginMenu()
{
	string s;
	int p = 0;
	
	cout << "Login Menu\n";
	cout << "Please enter your username: ";
	cin >> s;
	cout << "Please enter your pin: ";
	cin >> p;
	cout << "\n";
	
	currentUser.set_user(s, p);
	if(validate(currentUser))
	{
		cout << "Authentication successful! Welcome back!\n";
		accountMenu();
	}
	else
		cout << "Authentication failed.\n";
}

/* int ATM::findUser()
 * Precondition:	This function searches for the Username
 * Postcondition:	Return's 1 if Username matches
 *					Return's 0 if User not found
 */
int ATM::findUser(User &u)
{
	int i = 0;
	
	while(i < totalAccounts)
	{
		if((accounts[i].name() == u.name()))
		{
			return 1;
		}
		i++;
	}

	return 0;
}

/* int ATM::validate()
 * Precondition:	This function checks the Username and Pin entered by the User
 * Postcondition:	Return's 1 if Username & Pin matches
 *					Return's 0 if Username/Pin doesn't match
 */
int ATM::validate(User &u)
{
	int i = 0;
	
	while(i < totalAccounts)
	{
		if((accounts[i].name() == u.name()) && (accounts[i].pin() == u.pin()))
		{
			u.setBalance(accounts[i].balance());
			return 1;
		}
		i++;
	}
	cout << "Wrong Username/Pin. Try again.\n\n";
	return 0;
}

/* int ATM::accountMenu()
 * Precondition:	If login is successful, the Account Menu is printed out
 * Postcondition:	The balance is affected depending on what the User does 
 *					after logging in to their ATM
 */
void ATM::accountMenu()
{
	int choice = 0;
	double amount = 0.0;
	
	while(choice != 4)
	{
	cout << "\nAccount Menu\n";
	cout << "Please select an option from the list below:\n";
	cout << "\t1. Withdraw\n";
	cout << "\t2. Deposit\n";
	cout << "\t3. See Balance\n";
	cout << "\t4. Exit\n";
	cout << "Your choice: ";
	cin >> choice;
	cout << "\n";
	
	switch(choice)
	{
		case 1:
			cout << "Withdraw Menu\n";
			cout << "How much money would you like withdraw?\n";
			cout << "Your withdrawal: ";
			cin >> amount;
			for(int i = 0, j = 0; i < totalAccounts; i++)
			{
				j = accounts[i].deductBalance(currentUser, amount);
				
				if(j == -1)
				{
					cout << "\nInsufficient Funds.\n";
					break;
				}
				else if(j == 1)
				{
					cout << "\nThanks! Your money has been withdrawn!\n";
					break;
				}
			}
			break;
		case 2:
			cout << "Deposit Menu\n";
			cout << "How much money would you like to deposit?\n";
			cout << "Your deposit: ";
			cin >> amount;
			for(int i = 0, j = 0; i < totalAccounts; i++)
			{
				j = accounts[i].addBalance(currentUser, amount);
				
				if(j == 1)
				{
					cout << "\nThanks! The deposit has been applied to your account!\n";
					break;
				}
			}
			break;
		case 3:
			cout << "\nYour balance is: ";
			cout << currentUser.balance();
			cout << "\n";
			break;
		default:
			break;
	}
	}
}

int main()
{
	ATM myATM;
	
	myATM.mainMenu();
	
	return 0;
}
