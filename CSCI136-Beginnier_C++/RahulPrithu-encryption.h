/******************************************************************************
  Title          : RahulPrithu-lab11.cpp
  Author         : Rahul Prithu
  Created on     : December 5, 2011
  Description    : Message Encryption & Decryption 
  Purpose        : Lab 11
  Usage          : N/A
  Compile with	 : g++ -o RahulPrithu-lab11.cpp RahulPrithu-encryption.cpp
******************************************************************************/

#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include <string>

/* class Encryption
 * Preconditions: The class has 3 private variables: string key, string message 
 * & int ciphertext.
 * setKey() & setMsg() are accessor functions for the strings key and message
 * Postconditions: User input is passed by the accessor functions.
 * encrypt() codes the message
 * decrypt() decodes the coded message
 */

class Encryption{
	public:
	
	Encryption();
	
	void setKey(string userKey);
	void setMsg(string msgIn);
	void printCipher();
	
	void encrypt();
	string decrypt();
	
	private:
	string key;
	string message;
	int ciphertext[1024];
};

#endif /* ENCRYPTION_H */
