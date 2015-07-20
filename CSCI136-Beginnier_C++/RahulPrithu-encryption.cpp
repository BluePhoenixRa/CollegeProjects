/******************************************************************************
  Title          : RahulPrithu-lab11.cpp
  Author         : Rahul Prithu
  Created on     : December 5, 2011
  Description    : Message Encryption & Decryption 
  Purpose        : Lab 11
  Usage          : N/A
  Compile with	 : g++ -o RahulPrithu-lab11.cpp RahulPrithu-encryption.cpp
******************************************************************************/

#include <string>
#include "RahulPrithu-encryption.h"				// Include Header File
using namespace std;

/* Encryption::Encryption()
 * Default constructor
 */
Encryption::Encryption()
{
	key = "";
	message = "";
	for(int i = 0; i < 1024; i++)
	{
		ciphertext[i] = 0;
	}
}

/* Encryption::setKey
 * Preconditions: Key accessor. Takes in key from userKey, input by user.
 */
void Encryption::setKey(string userKey)
{
	key = userKey;
}

/* Encryption::setMsg
 * Preconditions: Message accessor. Tales in the message from setMsg, input by user.
 */
void Encryption::setMsg(string msgIn)
{
	message = msgIn;
}

/* Encryption::printCipher
 * Preconditions: Ciphered text is taken from the encrypt()
 * Postconditions: Prints the ciphered text
 */
void Encryption::printCipher()
{
	int i = 0;
	
	while(ciphertext[i] != 0)
	{
		cout << ciphertext[i] << " ";
		i++;
	}
}

/* Encryption::envrypt()
 * Preconditions: Message and key are taken from the user input.
 * Postconditions: The message from user input is encypted by adding the message with the key.
 */
void Encryption::encrypt()
{
	int i = 0, j = 0;

	while(message[i] != '\0')
	{
		ciphertext[i] = message[i] + key[j];
		i++;
		j++;
		
		if(key[j] == '\0')
			j = 0;
	}

}

/* Encryption::decrypt()
 * Preconditions: The message is encrypted with the encrypt(), the ciphered text is then
 * used to decrypt the message.
 * Postconditions: Ciphertext is subtracted from key and then returns the decrypted message.
 */
string Encryption::decrypt()
{
	char msgOut[1024];
	string strOut;
	int i = 0, j = 0;
	
	while(ciphertext[i] != 0)
	{
		msgOut[i] = ciphertext[i] - key[j];
		i++;
		j++;
		
		if(key[j] == '\0')
			j = 0;
	}
	msgOut[i] = '\0';
	strOut = msgOut;
	return strOut;
}
