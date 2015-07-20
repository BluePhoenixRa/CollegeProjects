/******************************************************************************
Title			: Prithu_main.cpp
Author	    	: Rahul Prithu
Created on   	: May 10, 2012
Description   	: 
				  
				  
Purpose       	: Assignment 6
Usage          	: 
Build with     	: g++ -o < > Prithu-HW-6.cpp 
Modifications  	:
*******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "Prithu-HW-6.hpp"

using namespace std;

/************************************************************
 * int get_command(string &commandIn, string &paramIn);
 * Takes user-input and splits into the command and parameters.
 *
 ************************************************************/

int get_command(string &commandIn, string &paramIn);	

int get_command(string &commandIn, string &paramIn)
{
	int iCommand=0;
	string txtIn;
	cout <<"\nCommand: ";
	getline(cin,txtIn);
	parse_line(txtIn, commandIn, paramIn);
	commandIn=to_upper(commandIn);
	while(iCommand<kTotal)
	{	
		if(commandIn==Command[iCommand])
			break;
		iCommand++;
	}
	return iCommand;
}

	

/************************************************************
 * int main()
 * Main function. Receives the commands, validates the command,
 * and executes functions as defined. The program accepts following commands:
 * "Help, Load, Find, Add, Remove, View, Save, Info, Exit."
 * The commands are 'not' case sensitive.
 ************************************************************/

int main()
{
	BinarySearchTree Index;
	int iCommand, rValue;
	string sCommand, sParameter;
	string oneLine, firstWord,secondWord;
	KeyWord kWord;	
	string sourceFileName=""; int linenumber=0;
	ifstream sourceFile;
	ofstream indexFile;

	while(true)
	{
		iCommand= get_command(sCommand, sParameter);
		switch(iCommand)
		{
		case kLoad	: if(sParameter==""){show_message(mLoad); break;}
					  sourceFile.open(sParameter.c_str());
					  if(sourceFile.fail())
						{show_message(mLoadFailed,sParameter);break;}
					  Index.clear();	
					  sourceFileName=sParameter;
					  linenumber =0;	
					  while(getline(sourceFile, oneLine))
					  {
						linenumber++;
						while(oneLine.size()-1)
						{ 
						  parse_line(oneLine,firstWord, secondWord);
						  if(firstWord!="")
							{
								kWord.word = to_lower(firstWord); 
								kWord.location=int2string(linenumber);
								Index.insert(kWord);
								oneLine = secondWord;
							}
						  else break;	
						} 
					  }
					sourceFile.close();
					show_message(mLoaded,sourceFileName);
					break;	
		case kAdd	: if(sParameter==""){show_message(mAdd); break;}
					  kWord.word=to_lower(sParameter); kWord.location="";
					  rValue=Index.insert(kWord); 
					  if (rValue==mAdded)
						show_message(mAdded,kWord.word);
					  else if(rValue==mUpdated || rValue==mExists)
						show_message(mExists,kWord.word);
					  break;
		case kFind	: if(sParameter==""){show_message(mFind); break;}
					  kWord.word=to_lower(sParameter); kWord.location="";
					  rValue=Index.find(kWord);
					  if (rValue==mFound)
						show_message(mFound,kWord.word,kWord.location);
					  else if(rValue==mNotFound)
						show_message(mNotFound,kWord.word);
					  break;
		case kRemove: if(sParameter==""){show_message(mRemove); break;} 
					  kWord.word=to_lower(sParameter); kWord.location="";
					  rValue=Index.remove(kWord);
					  if (rValue==mRemoved)
						show_message(mRemoved,kWord.word,kWord.location);
					  else if(rValue==mNotFound)
						show_message(mNotFound,kWord.word);
					  break;
		case kView	: show_message(mView);
					  Index.list(cout);
					  break;
		case kInfo	: cout <<"File Information : \n-----------------------\n";
					  cout <<"File Name \t: "<<sourceFileName<<"\n";
					  cout <<"Lines \t\t: "<<linenumber<<"\n";
					  cout <<"Index size\t: "<<Index.size()<<"\n";
						break;
		case kSave	: if(sParameter==""){show_message(mSave); break;}
						indexFile.open(sParameter.c_str());
						Index.list(indexFile);
						indexFile.close();
						show_message(mSaved,sParameter);
						break;
		case kHelp	: show_message(mHelp); break;
		case kExit	: show_message(mExit); return 0;
		default		: show_message(mInvalid, sCommand, sParameter); break;
		}
	}
	return 0;
}
	

