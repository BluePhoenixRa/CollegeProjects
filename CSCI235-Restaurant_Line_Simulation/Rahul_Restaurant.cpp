/******************************************************************************
Title			: Rahul_Restaurant.cpp
Author	    	: Rahul Prithu
Created on		: March 31, 2012
Description		: Contains class implementations  for Assignment 4
Purpose			: Class implementations (Resturant, Cashier, Customer, Queue) for Assignment 4
Usage			: Class declrations and implementations for Assignment 4
Build with		: N/A
Modifications	: 
*******************************************************************************/
#include "Rahul_Restaurant.hpp"
using namespace std;

/******************************************************************************
Class		    : Restaurant
Description		: Restaurant class declarations for Assignment 4
Purpose			: To create and manage a Restaurant object
*******************************************************************************/

/*
Restaurant::Restaurant()
Default Constructor
*/
Restaurant::Restaurant(){
	totalCustomersEntered=0;
	totalCustomersServed=0;
	customersInQueue=0;
	currentTime=0;
	totalWait=0;
	maxWait=0;
	totalServeTime=0;
	numberOfCashiers=0;
	numberOfLines =0;
}

/*
Restaurant::~Restaurant()
Destructor
*/
Restaurant::~Restaurant(){
}

/*
void Restaurant::setCashiers(int c)

Number of Cashiers is read and set from the property file supplied by the user.
*/
void Restaurant::setCashiers(int c){
if (c>0) {
	numberOfCashiers=c;
	for (int n =1; n <=numberOfCashiers; n++){
		cashier[n-1].setSkills(); 
		}
	}
else
	numberOfCashiers=0;
}

/*
void Restaurant::setLines(int n)

Number of cashier lines is read and set from the property file supplied by the user.
*/
void Restaurant::setLines(int n){
if(n==1)
	numberOfLines=1;			// single line
else if (n==numberOfCashiers)
	numberOfLines=n;			// cashier's line
else
	numberOfLines=0;			// inconsistent number of lines
}

/*
int Restaurant::newCustomers(int timeIn, int n)

newCustomer() adds the customer(s), sets the time, and assigns the customer(s) to a line (at random, if more than one line exists).
*/
int Restaurant::newCustomers(int timeIn, int n){ // Add Customers 
Customer newCustomer;
int lineNumber=0;
if (timeIn <currentTime)
	return -1;		// Time in past
while (currentTime < timeIn){
	updateService();
	currentTime++;
	}
for(int i=0;  i <n; i++){
	newCustomer.setTime(timeIn);
	if(numberOfLines==1)
		lineNumber=1;			// Single line
	else
		{
		lineNumber = rand()%numberOfLines +1; // Assign line at random
		}
	line[lineNumber-1].enqueue(newCustomer);
	totalCustomersEntered++;
	customersInQueue++;
	}
updateService();
currentTime++;
}

/*
void Restaurant::updateService()

updateService() checks if a cashier is available to serve the next customer.
If there are more than one lines for cashiers, and one of the cashier's line is empty, updateService moves a waiting customer from the adjacent line to the available cashier.
*/
void Restaurant::updateService(){
	int i=0, j=0, status=0, lineNumber=0, timeToServe=0, currentWaitTime=0;
	Customer customerToServe;
	for (i=0; i<numberOfCashiers && customersInQueue>0;i++){
		status = cashier[i].serveStatus(currentTime);
		if (status==0){ 		// Cashier is available to serve next customer
			if (numberOfLines==1) // Single line
				lineNumber=0;
			else if (!line[i].isEmpty()) // Get from current line
				lineNumber=i; 
			else // Invite customer from other lines
			{
				for (j =0; j<numberOfLines-1;j++){
					lineNumber=i+j;
					if(lineNumber>=numberOfLines)
						lineNumber=lineNumber-numberOfLines;
					if(!line[lineNumber].isEmpty())
						break;
					}
			}
			
			line[lineNumber].getFront(customerToServe);
 			line[lineNumber].dequeue(customerToServe);
			timeToServe = cashier[i].serveNew(currentTime, customerToServe.getTimeToFulfill());
			
			currentWaitTime = currentTime - customerToServe.getTimeIn(); 
			if(currentWaitTime > maxWait)
				maxWait = currentWaitTime ;
			totalWait+=currentWaitTime;
			totalCustomersServed++;
			totalServeTime+=timeToServe;
			customersInQueue--;
			currentWaitTime=0;
		}
	}
}

/*
int Restaurant::clearQueues()

This function completes serving all customers in the queue. No customer is added during this period.
*/
int Restaurant::clearQueues(){ // Serve all customers in queue
	while (customersInQueue!=0 ){
		updateService();
		currentTime++;
		}
	return currentTime++;
}

/******************************************************************************
Class		    : Cashier
Description		: Cashier class implementations for Assignment 4
Purpose			: To create and manage a Cashier object
*******************************************************************************/

/*
Cashier::Cashier()

Default Constructor
*/
Cashier::Cashier(){
	skillFactor=0;
	totalServed=0;
	totalTime=0;
	timeStarted=0;
	timeToFulfill=0;
	}
	
/*
Cashier::~Cashier()

Deconstructor
*/
Cashier::~Cashier(){
}

/*
void Cashier::setSkills()

Set's the cashier's check out speed. Each cashier has a 10% probability of being fast, a 10% probability of being slow and an 80% probability of being average.
*/
void Cashier::setSkills(){
int skillLevel=0; 
skillLevel = rand()%100 +1;
if(skillLevel <=10)			// Slow cashier
	skillFactor = +1;
else if(skillLevel > 90)	// Fast cashier
	skillFactor = -1;
else						// Average cashier
	skillFactor = 0;
}

/*
int Cashier::serveNew(int startAt, int expectedTime)

The function determines wether the cashier is busy or free to serve another customer. Return's -1 if busy.
*/
int Cashier::serveNew(int startAt, int expectedTime){
if(startAt <timeStarted+timeToFulfill) // Job can not be started
	return -1;
else				// Accept Order
	{
	timeStarted = startAt;
	timeToFulfill = expectedTime + skillFactor;
	totalServed++;
	totalTime+=timeToFulfill;
	return timeToFulfill;
	}
}

/*
int Cashier::serveStatus(int t)

Return's the status of the cashiers.
If the cashier is not busy and ready to accept the next customer, it will return 0.
If the cashier is attending to a customer, it'll return the time to fulfill current order.
It will return -1, if the time is in past or the status is unknown.
*/
int Cashier::serveStatus(int t){
if(timeStarted+timeToFulfill <=t)
	return 0;					// Cashier is not busy
else if(timeStarted> t)
	return -1; 					// Time in past, status unknown
else
	return (timeStarted+timeToFulfill - t); // Time to fulfill current order
}


/******************************************************************************
Class		    : Customer
Description		: Customer class implementations for Assignment 4
Purpose			: To create and manage a Customer object
*******************************************************************************/

/*
Customer::Customer()

Default Constructor
*/
Customer::Customer(){
	timeIn=0;
	timeToFulfill=0;
}

/*
Customer::~Customer()

Desturctor
*/
Customer::~Customer(){
}

/*
Customer::Customer(int tIn)

Copy Constructor
*/
Customer::Customer(int tIn){
	timeIn=tIn;
	timeToFulfill = rand()%4 +2;
}

/*
void Customer::setTime(int tIn){

Stores the time when the customer entered and the time it may take (determined at random) to fulfill the order. 
*/
void Customer::setTime(int tIn){
	timeIn=tIn;
	timeToFulfill = rand()%4 +2;
}

/*
int Customer::getTimeIn()

Returns when the customer entered into the restaurant
Used to calculate waiting time

*/
int Customer::getTimeIn(){
	return timeIn;
}

/*
int Customer::getTimeToFulfill()

Returns the expected time to fulfill the customer's order
The time is determined at random when the object is created

*/
int Customer::getTimeToFulfill(){
	return timeToFulfill;
}


/******************************************************************************
Class		    : Queue
Description		: Queue class implementations for Assignment 4
Purpose			: To create and manage a Queue 
*******************************************************************************/



/*
Queue::Queue():head(NULL), tail(NULL)

Default Constructor

*/
Queue::Queue():head(NULL), tail(NULL){
size =0;
}

/*
Queue::~Queue()

Destructor

*/
Queue::~Queue(){
	T tmp;
	while(!isEmpty())
		dequeue(tmp);
}

/*
void Queue::enqueue(T newItem)

Adds new item at the end of the queue
*/
void Queue::enqueue(T newItem){
	Node *newPtr = new Node;
	newPtr -> data = newItem;
	if(size==0) {
		head = newPtr;
		}
	else
		{
		tail->next = newPtr;
		newPtr -> next = NULL;
		}
	tail = newPtr;

	size++;
}

/*
void Queue::dequeue(T& queueFront)

Provides the first object data from the queue and removes it
*/
void Queue::dequeue(T& queueFront){
	Node *temp = head;
	if(size>0){
		queueFront = head -> data;
		if(head == tail){
			head = NULL;
			tail = NULL;
			}
		else
			head = temp -> next;
	T tailItem;
	tailItem=queueFront;
	size--;
	delete temp;
	}
	
}

/*
void Queue::getFront(T& queueFront){

Provides the first object data from the queue without removing it
*/
void Queue::getFront(T& queueFront){
	if(!isEmpty())
		queueFront = head -> data;
}

bool Queue::isEmpty(){
	return bool(tail == NULL);
}


/**********************************************
Function : IntToStr (int tmp)

Convert Integer to String
A stand alone function used to convert integer to string 
***********************************************/

std::string IntToStr(int tmp)
{
    std::ostringstream out;
    out << tmp;
    return out.str();
}
