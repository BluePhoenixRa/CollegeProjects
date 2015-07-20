
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <cctype>

using namespace std;

/***********************************************************
* List of commands (for user input), 
* and command keys (integer equivalence for internal use)
*************************************************************/
const string Command[]= 
		{"","HELP", "LOAD", "FIND", "ADD", 
		"REMOVE", "VIEW", "SAVE", "INFO", "EXIT"};
enum CommandKey {kNull,kHelp, kLoad, kFind, kAdd, 
		kRemove, kView, kSave, kInfo, kExit, kTotal};

/***********************************************************
* Message keys amd message(): used to communicate between functions
* display messages to users
*************************************************************/

enum mMessage {mNull, mHelp, mLoad, mFind, mAdd, 
		mRemove, mView, mSave, mInfo, mExit, mInvalid, 
		mLoaded, mLoadFailed, mFound, mNotFound, mAdded, 
		mExists, mUpdated, mNotAdded, mRemoved, 
		mNotRemoved,mEmpty, mSaved, mTotal};

void show_message(int msgnr);
void show_message(int msgnr, string s1);
void show_message(int msgnr, string s1, string s2);


/***********************************************************
* STRING CONVERSION and PARSING FUNCTIONS
* int2string()		: Converts int to string
* double2string()	: Converts double to string
* string2int		: Converts string to integer
* string2double		: Converts string to double
* to_upper()		: Converts string to uppercase
* to lower()		: Converts string to lower case
* parse_line()		: Seperates the first word from rest.
*************************************************************/
string int2string(const int& toConvert);
string double2string(const double& toConvert);
int string2int(const std::string& sToConvert);
double string2double(const std::string& sToConvert);
string to_upper(string sIn);
string to_lower(string sIn);
void parse_line(string sIn, string &sFirst, string &sNext);


// int2string()		: Converts int to string
string int2string(const int& toConvert)
{
     std::ostringstream stream;
     stream << toConvert;
     return stream.str();
}

// double2string()	: Converts double to string
string double2string(const double& toConvert)
{
     std::ostringstream stream;
     stream << toConvert;
     return stream.str();
}

// string2int		: Converts string to integer
int string2int(const std::string& sToConvert)
{
     std::istringstream stream (sToConvert);
     int number;
     stream >> number;
     return number;
}

// string2double		: Converts string to double
double string2double(const std::string& sToConvert)
{
     std::istringstream stream (sToConvert);
     double number;
     stream >> number;
     return number;
}

// to_upper()		: Converts string to uppercase
string to_upper(string sIn)
{
	for (int i=0; i<sIn.size();i++)
		sIn[i]= toupper(sIn[i]);
	return sIn;
}

// to lower()		: Converts string to lower case
string to_lower(string sIn)
{
	for (int i=0; i<sIn.size();i++)
		sIn[i]= tolower(sIn[i]);
	return sIn;
}


// parse_line()		: Seperates the first word from rest.
void parse_line(string sIn, string &sFirst, string &sNext)
{
	int sPos, mPos;
	sPos = 0; mPos=0;
	int sz = sIn.size();
	sFirst="";sNext="";
	
	if (sIn.find_first_of("\r\n",0)<sz)	// check for new lines
		sz = sz-1;
	if(sz==0)			// no segment to split
	{ 
		sFirst=""; 
		sNext=""; 
		return;	
	}
	while(sPos<sz)					  // find first alphabet.
	{
		if(isalpha(sIn[sPos]))
			break;
		sPos++;
	}
	
	if(sPos==sz)			// reached end of line: no alphabet found
	{ 
		sFirst=""; 
		sNext=""; 
		return;	
	}
	
	
	mPos=sPos;				// start from the first alphabet of the word
	while(mPos<sz)
	{
		if(!isalpha(sIn[mPos]))		// find end of word
			break;
		sFirst=sFirst+sIn[mPos];
		mPos++;
	}
	
	if(mPos<sz)				// remove space from beginning, if any
	{
	while(sIn[mPos]==' ')
		mPos++;
	}
	
	while(mPos<sz)			// copy rest of the string
	{
		sNext=sNext+sIn[mPos];
		mPos++;
	}
//	cout<< sPos<<"\t"<<mPos<<"\t"<<sFirst <<"\t"<<sNext <<".\n"; //test statement
}

//show_message()	: display message based on message# & parameters if any
void show_message(int msgnr)
{
	show_message(msgnr,"", "");
}

void show_message(int msgnr,string s1)
{
	show_message(msgnr, s1, "");
}

void show_message(int msgnr,string s1, string s2)
{
	switch (msgnr)
	{
	case mNull	: 	cout<<s1<<s2<<"\n"; break;
	case mLoad	:	cout <<"Usage: LOAD filename.txt "<<"\n"; break; 
	case mFind	:	cout <<"Usage: FIND word "<<"\n"; break;
	case mAdd	:	cout <<"Usage: ADD word "<<"\n"; break;
	case mRemove:	cout <<"Usage: REMOVE word "<<"\n"; break;
	case mView	:	cout <<"INDEX \n--------------------- "<<"\n"; break;
	case mSave	:	cout <<"Usage: SAVE filename.txt "<<s1<<s2<<"\n"; break;
	case mExit	:	cout <<"THANK YOU."<<"\n"; break;
	case mLoaded: 	cout <<"File \""<<s1<<"\" read and index generated\n"; break;
	case mLoadFailed: cout <<"File \""<<s1<<"\" could not be read\n"; break;
	case mFound	:	cout <<"Word \""<<s1<<"\" appears on lines: "<<s2<<"\n"; break;
	case mExists:	cout <<"Word \""<<s1<<"\" exists in index "<<s2<<"\n"; break;
	case mNotFound:	cout <<"Word \""<<s1<<"\" does not appear in this file\n"; break;
	case mAdded	:	cout <<"Word \""<<s1<<"\" added to index\n"; break;
	case mNotAdded:	cout <<"Word \""<<s1<<"\" exists in index\n"; break;
	case mRemoved:	cout <<"Word \""<<s1<<"\" removed from index\n"; break;
	case mNotRemoved:	cout <<"Word \""<<s1<<"\" is not found in index\n"; break;
	case mSaved	:	cout <<"Index File \""<<s1<<"\" saved\n"; break;
	case mHelp	:	cout << "List of commands  :\n";
					cout << "-------------------\n";
					cout << "HELP \t\t  : Displays this list of commands.\n";
					cout << "LOAD filename.txt : Loads the specified file and creates index.\n";
					cout << "FIND word \t  : Finds the word in index.\n";
					cout << "ADD word \t  : Adds the given word to index.\n";
					cout << "REMOVE word \t  : Removes the word from index.\n";
					cout << "VIEW \t\t  : View index.\n";
					cout << "SAVE filename.txt : Saves index file.\n";
					cout << "INFO \t\t  : Prints file information.\n";
					cout << "EXIT \t\t  : Terminates the program.\n";
					break;
	case mInvalid:	cout <<"Invalid command: "<<s1<<" \n";
	default	:		cout << "Enter a valid command. Type HELP for list of commands.\n";
					break;
	}
}


/***********************************************************
* BINARY SEARCH TREE
* struct KeyWord	: Index word with location (line#s etc)
* BinarySearchTree	: Class containing following main functions
* insert(KeyWord)	: Adds new keywords, and updates existing keys 
* update(KeyWord)	: Updates the locations, if the word is already included
* remove (KeyWord)	: Remove a key word from the tree
* find(KeyWord)		: Finds a keyword and returns location by reference.
* list(ostream)		: Saves/displays the index.
* size()			: Returns number of nodes		
* clear()			: Clears all nodes
*************************************************************/

struct KeyWord
{
public:
	string word;
	string location;
};

class BinarySearchTree
{
    private:
        struct TreeNode
        {
           TreeNode* left;
           TreeNode* right;
           KeyWord data;
        };
        TreeNode* root;
		int nodeCount;
    
    public:
        BinarySearchTree()
        {
           root = NULL;
        }
       
        bool isEmpty() const { return root==NULL; }
        int insert(KeyWord);
        int remove(KeyWord);
		int update(KeyWord);
		int find(KeyWord&);
		void list(ostream &file);
		void list(ostream &file, TreeNode* t);
		int size();
		int size(TreeNode* t);
		void clear();
		void deleteNode(TreeNode*&);
};

/*******************************
* Binary Search Tree - Implementations
********************************/


int BinarySearchTree::size()
{
	nodeCount=0;
	if (root==NULL)
		return nodeCount;
	else
		return size(root);
}

int BinarySearchTree::size(TreeNode* t)
{
	if(t != NULL)
	{
		size (t->left);
		size (t->right);
		nodeCount++;
	}
return nodeCount;
}

void BinarySearchTree::clear()
{
	deleteNode(root);
	root=NULL;
}

void BinarySearchTree::deleteNode(TreeNode*& t)
{
	if(t != NULL)
	{
		deleteNode (t->left);
		deleteNode (t->right);
		delete t;
	}
}

int BinarySearchTree::insert(KeyWord kWord)
{
    TreeNode* t = new TreeNode;
    TreeNode* parent;
    t->data = kWord;
    t->left = NULL;
    t->right = NULL;
    parent = NULL;
    
    if(isEmpty()) root = t;
    else if (update(kWord)==mUpdated)
	{
		return mUpdated;
	}
	else
    {
        TreeNode* curr;
        curr = root;
        while(curr)
        {
            parent = curr;
            if(t->data.word > curr->data.word) curr = curr->right;
            else curr = curr->left;
        }

        if(t->data.word < parent->data.word)
           parent->left = t;
        else
           parent->right = t;
    }
	return mAdded;
}

int BinarySearchTree::find(KeyWord& kWord)
{
    bool found = false;
    if(isEmpty())
    {
        return mEmpty;
    }
    
    TreeNode* curr;
    TreeNode* parent;
    curr = root;
    
    while(curr != NULL)
    {
         if(curr->data.word == kWord.word)
         {
            found = true;
			kWord.location = curr->data.location;
			return mFound;
         }
         else
         {
             parent = curr;
             if(kWord.word > curr->data.word) curr = curr->right;
             else curr = curr->left;
         }
    }
    if(!found)
		 {
        return mNotFound;
    }
}

int BinarySearchTree::update(KeyWord kWord)
{
    bool found = false;
    if(isEmpty())
    {
        return mEmpty;
    }
    
    TreeNode* curr;
    TreeNode* parent;
    curr = root;
    
    while(curr != NULL)
    {
         if(curr->data.word == kWord.word)
         {
            found = true;
			if(string2int(curr->data.location)==0)	// 
				curr->data.location = kWord.location;
			else if (string2int(kWord.location)>0)
				curr->data.location = curr->data.location + ", "+kWord.location;
						
			return mUpdated;
         }
         else
         {
             parent = curr;
             if(kWord.word > curr->data.word) curr = curr->right;
             else curr = curr->left;
         }
    }
    if(!found)
	 {
        return mNotFound;
      }
}


int BinarySearchTree::remove(KeyWord kWord)
{
    bool found = false;
    if(isEmpty())
    {
        return mEmpty;
    }
    
    TreeNode* curr;
    TreeNode* parent;
    curr = root;
    
    while(curr != NULL)
    {
         if(curr->data.word == kWord.word)
         {
            found = true;
            break;
         }
         else
         {
             parent = curr;
             if(kWord.word > curr->data.word) curr = curr->right;
             else curr = curr->left;
         }
    }
    if(!found)
	 {
        return mNotFound;
     }


   if((curr->left == NULL && curr->right != NULL)|| (curr->left != NULL && curr->right == NULL))
    {
       if(curr->left == NULL && curr->right != NULL)	// Leaf, no child
       {
           if(parent->left == curr)
           {
             parent->left = curr->right;
             delete curr;
           }
           else
           {
             parent->right = curr->right;
             delete curr;
           }
       }
       else 								// Parent with Left child
       {
          if(parent->left == curr)
           {
             parent->left = curr->left;
             delete curr;
           }
           else
           {
             parent->right = curr->left;
             delete curr;
           }
       }
     return mRemoved;
    }
	if( curr->left == NULL && curr->right == NULL)
    {
        if(parent->left == curr) parent->left = NULL;
        else parent->right = NULL;
		 		 delete curr;
		 		 return mRemoved;
    }

    if (curr->left != NULL && curr->right != NULL)		// Parent with Left+Right child
    {
        TreeNode* chkr;
        chkr = curr->right;
        if((chkr->left == NULL) && (chkr->right == NULL))
        {
            curr = chkr;
            delete chkr;
            curr->right = NULL;
        }
        else 		
        {
            if((curr->right)->left != NULL)
            {
                TreeNode* lcurr;
                TreeNode* lcurrp;
                lcurrp = curr->right;
                lcurr = (curr->right)->left;
                while(lcurr->left != NULL)
                {
                   lcurrp = lcurr;
                   lcurr = lcurr->left;
                }
				curr->data = lcurr->data;
                delete lcurr;
                lcurrp->left = NULL;
           }
           else
           {
               TreeNode* tmp;
               tmp = curr->right;
               curr->data = tmp->data;
			   curr->right = tmp->right;
               delete tmp;
           }

        }
		 return mRemoved;
    }

}

void BinarySearchTree::list(ostream &file)
{
   list(file, root);
}

void BinarySearchTree::list(ostream &file, TreeNode* t)
{
    if(t != NULL)
    {
        if(t->left) list (file, t->left);
        file <<""<<t->data.word<<", "<<t->data.location<<"\n";
        if(t->right) list (file,t->right);
    }
    else return;
}


