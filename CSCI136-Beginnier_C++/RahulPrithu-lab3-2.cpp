/*
Author: Rahul Prithu
File: RahulPrithu-lab3.cpp
*/

// Lab 3
// Input: 	The program asks for selection from menu.
// Process: The program reads data from a text file.
//			It calculates the total, maxima and minima.
// 			It also searches for any user given number in the file.
// Output: 	Based on user selection, the program prints mean, maxima, minima or the search results.

#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	int iMenu = 0;				// Menu Choice.
	int lookFor;				// Search user input integer - Menu 4.
	int counter = 0;			// Counts number of entries in the text file.
	float total = 0.0;			// Sum of all numbers in text file.
	int number;					// Number read from the file.
	int found = 0;				// Number of items matched.
	
	while (iMenu !=5)
	{
		int mean, maxima, minima;
		
		// Menu
		cout << "\nMain Menu \n";
		cout << "Please enter the number for one of these options:\n";
		cout << "1 - Mean\n";
		cout << "2 - Maxima\n";
		cout << "3 - Minima\n";
		cout << "4 - Search\n";
		cout << "5 - Exit\n\n";
		
		cout << "Your choice: ";
		cin >> iMenu;
		
		if (iMenu == 5)										// Exit 1
			break;
		
		if (iMenu == 4)										// Get additional input.
		{
			cout << "Please enter a number: ";
			cin >> lookFor;
		}
		
		fstream file;										// File Handler.
		file.open ("numbers.txt");
		file >> number;										// Initialize (First line).
		counter++;
		total += number;
		maxima = number;
		minima = number;
		
		if (iMenu == 4)										// Check for search option.
		{
			if (lookFor == number)
				found++;
		}
		
		while (file.eof() == false)							// Rest of the file.
		{
			file >> number;
			counter++;										
			total += number;								
			if (maxima < number)							// Check for maximum value.
				maxima = number;
			if (minima > number)							// Check for minimum value.
				minima = number;
			if (iMenu == 4)
			{
				if (lookFor == number)
				found++;
			}
		}
		
		file.close();
		file.clear();
		
		if (iMenu == 1)										// Print average of all numbers.
		{
			cout << "Average of all numbers in the text file: ";
			cout << total / counter << "\n";
		}
		else if (iMenu == 2)								// Print largest number.
		{
			cout << "Largest number in the text file: ";
			cout << maxima << "\n";
		}
		else if (iMenu == 3)								// Print smallest number.
		{
			cout << "Smallest number in the text file: ";
			cout << minima << "\n";
		}
		else if (iMenu == 4)								// Search results.
			{
				if (found)
					cout << "We have found it " << found << " time(s)! Hooray!\n";
				else
					cout << "Sorry, we haven't found the number.\n";
			}
		else
			cout << "Enter a number between 1 and 5.\n\n";
	
	// Reset variables
	counter = 0;
	total = 0;
	found = 0;
	
	// Exit 2 - Asks the user if they want to choose another option from the menu or exit.
	char yesno;
	cout << "\nWould you like to choose another option? [y/n] ";
	cin >> yesno;
	if ((yesno == 'n') || (yesno == 'N'))
		iMenu = 5;
	else
		iMenu = 0;
	}
	
	cout << "Goodbye!\n";									// End
	return 0;
}
