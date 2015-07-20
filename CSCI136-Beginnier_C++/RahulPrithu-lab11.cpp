/******************************************************************************
  Title          : RahulPrithu-lab11.cpp
  Author         : Rahul Prithu
  Created on     : December 5, 2011
  Description    : Message Encryption & Decryption 
  Purpose        : Lab 11
  Usage          : N/A
  Compile with	 : g++ -o RahulPrithu-lab11.cpp RahulPrithu-encryption.cpp
******************************************************************************/

#include <iostream>
#include <string>
#include "RahulPrithu-encryption.h"				// Include Header File
using namespace std;

int main()
{
	string firstName;							// User's First Name
	string uMessage;							// The Message
	Encryption userData;						// Encryption
	
	cout << "Enter First Name: ";
	getline(cin, firstName);					// Input User's First Name
	userData.setKey(firstName);
	cout << "Enter A Messege: ";
	getline(cin, uMessage);						// Enter The Message
	userData.setMsg(uMessage);
	cout << "\n\nOriginal Message: " << uMessage;	// Display Original Message
	
	userData.encrypt();							// Encrypt Message
	
	cout << "\nCipher Text: ";
	userData.printCipher();						// Print Chipered Text
	
	cout << "\nDecrypted Message: " << userData.decrypt() << "\n";	// Display Decrypted Message
	
	return 0;
}
