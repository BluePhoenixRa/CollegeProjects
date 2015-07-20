/*
Author: Rahul Prithu
File: RahulPrithu-lab5.cpp
*/

// Lab 5
// This program computes 3 mathematical statistics: Mean, Variance and Standard Deviation.
// The program reads data from a text file, named "numbers.txt"
// It calculates the sum of all the numbers in the text file, then computes the mean, variance and standard deviation

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

void showMenu();											// Main Menu prototype

void ProcessChoice(int uChoice);							// Process User Choice prototype

void ComputeStat(char *fileName, double &xMean, double &xVar, double &xStddev);	// Compute Statistics prototype

int main()
{
	int iMenu = 0;
	char goAgain = 'y';

	while ((goAgain != 'n') && (goAgain != 'N'))
	{
	showMenu();												// Calls the "showMenu" function and displays the menu.
	cin >> iMenu;											// User Choice Input

	if ((iMenu <= 0) || (iMenu > 3))
		cout << "\n\nInvalid input. (The number must be between 1 and 3)\n";
	else
		ProcessChoice(iMenu);

	cout << "Would you like to continue? [y/n]: ";			// Continue or Exit
	cin >> goAgain;
	}
	
	cout << "\nThank you.\n";								// Exit Message
	
	return 0;
}

void showMenu()												// Display's the Main Menu
{	
	cout << "\nMain Menu\n";
	cout << "Please enter the number for one of these options:\n";
	cout << "1 - Mean\n";
	cout << "2 - Variance\n";
	cout << "3 - Standard Deviation\n";
	cout << "Your choice: ";
}

/*
Precondition: Passes the integer value picked by the user in the Menu.
Postcondition: Depending on user's Menu choice, it calls the compute functuion and displays the answer. It does not return any value.
*/

void ProcessChoice(int uChoice)								// Process User Choice
{
	double Mean = 0, Var = 0, stdDev = 0;
	
	char *dataFile = "numbers.txt";							// Directs the program to the 
	
	ComputeStat(dataFile, Mean, Var, stdDev);
	
	if (uChoice == 1)										// Process user menu choice
		cout << "\nMean: " << Mean << "\n\n";
	else if (uChoice == 2)
		cout << "\nVariance: " << Var << "\n\n";
	else
		cout << "\nStandard Deviation: " << stdDev << "\n\n";
}

/*
Precondition: Pass file name with 3 variable references.
Postcondition: Comuptes Mean, Variance and Standard Deviation, but does not return a value.
*/

void ComputeStat(char *fileName, double &xMean, double &xVar, double &xStddev)			// Compute Statistics
{
	int n = 0;
	double sum = 0, x = 0;
	double sumSq = 0;
	
	ifstream file;										// File Handler.
	file.open (fileName);
	
	while (!file.eof())
	{
		file >> x;
		n++;										
		sum += x;
	}
		
	file.close();
	file.clear();
	
	xMean = sum/n;										// Calculates Mean
	
	//////////////////////////////////////////////////////
	
	file.open (fileName);
	
	while (!file.eof())
	{
		file >> x;
		sumSq = sumSq + (x - xMean) *  (x - xMean);
	}
		
	file.close();
	file.clear();
	
	xVar = sumSq/n;										// Calculates Variance
	
	//////////////////////////////////////////////////////
	
	xStddev = sqrt(xVar);								// Calculates Standard Deviation
}
