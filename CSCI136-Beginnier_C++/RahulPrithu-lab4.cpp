/*
Author: Rahul Prithu
File: RahulPrithu-lab4.cpp
*/

// Lab 4
// Input:	Asks the user to pick a temperature scale.
// Process:	After the user inputs the temperature he wants to convert, the program converts the temperature to 2 other scale values.
// Output:	Shows the user the temperature in all 3 (including the temperature input by the user) scales.

#include <iostream>
using namespace std;

double toFarhenheit(double toConvert, int scale);

double toCelsius(double toConvert, int scale);

double toKelvin(double toConvert, int scale);

int main()
{
	int theMenu = 0;
	float temper = 0;
	char goAgain = 'y';
	
	while (goAgain != 'n' && goAgain != 'N')
	{
		// The Menu
		cout << "\nWelcome to the Temperature Conversion System!\n";
		cout << "Please select the scale to start with:\n";
		cout << "1 - Fahrenheit\n";
		cout << "2 - Celsius\n";
		cout << "3 - Kelvin\n";
		cout << "Your choice: ";
		cin >> theMenu;
	
		if (theMenu <= 0 || theMenu > 3)
		{
			cout << "\nPlease enter a number between 1 to 3.\n";
			continue;
		}
		else if (theMenu == 1)				// Fahrenheit
			cout << "\nPlease enter the Fahrenheit temperature: ";
		
		else if (theMenu == 2)				// Celsius
			cout << "\nPlease enter the Celsius temperature: ";

		else if (theMenu == 3)				// Kelvin
			cout << "\nPlease enter the Kelvin temperature: ";
		
		cin >> temper;
		cout << "Fahrenheit: " << toFarhenheit(temper, theMenu) << " degrees\n";
		cout << "Celsius: " << toCelsius(temper, theMenu) << " degrees\n";
		cout << "Kelvin: " << toKelvin(temper, theMenu) << " degrees\n";

		// Go again or quit.

		cout << "\nWould you like another conversion?\n";
		cout << "Your answer [y/n]: ";
		cin >> goAgain;
		if ((goAgain == 'n') || (goAgain == 'N'))
			cout << "\nHave a great day!\n";
		else
			theMenu = 0;
	}

	return 0;
}


/*

Celsius to Kelvin		 	K = C + 273
Kelvin to Celsius			C = K - 273
Fahrenheit to Celsius		 C = (F - 32) x 5/9
Celsius to Fahrenheit		 F = (C x 9/5) + 32

*/


double toFarhenheit(double toConvert, int scale)
{
	double rValue = 0.0;
	
	if (scale == 1)				// Farhenheit							(No calculation required)
		rValue = toConvert;
	else if (scale == 2)		// Celsius to Fahrenheit		 		F = (C x 9/5) + 32
		rValue = (toConvert * 9/5) + 32;
	else if (scale == 3)		// Kelvin to Celsius to Farhenheit 		F =((K-273) * 9/5) + 32
		rValue = (toCelsius(toConvert,scale) * 9/5) + 32;
		// rValue = ((toConvert - 273) * 9/5) + 32;						Alternate calculation
		
	return rValue;
}

double toCelsius(double toConvert, int scale)
{
	double rValue = 0.0;
	
	if (scale == 1)				// Farhenheit to Celcius				C = (F - 32) x 5/9
		rValue = (toConvert - 32) * 5/9;
	else if (scale == 2)		// Celsius								(No calculation required)
		rValue = toConvert;
	else if (scale == 3)		// Kelvin to Celsius					C = K - 273
		rValue = (toConvert - 273);
		
	return rValue;
}

double toKelvin(double toConvert, int scale)
{
	double rValue = 0.0;

	if (scale == 1)				// Fahrenheit to Celsius to Kelvin		K = ((F - 32) x 5/9) +273
		rValue = toCelsius(toConvert,scale) + 273;
		// rValue = ((toConvert - 32) * 5/9) + 273;						Alternate calculation
	else if (scale == 2)		// Celsius to Kelvin					K = C + 273
		rValue = toConvert + 273;
	else if (scale == 3)		// Kelvin								(No calculation required)
		rValue = toConvert;
		
	return rValue;
}
