/******************************************************************************
Title			: Rahul_Restaurant.cpp
Author	    	: Rahul Prithu
Created on		: March 31, 2012
Description		: Contains class declarations for Assignment 4
Purpose			: Class declarations (Resturant, Cashier, Customer, Queue) for Assignment 4
Usage			: Class declrations and implementations for Assignment 4
Build with		: N/A
Modifications	: 
*******************************************************************************/

#ifndef _Restaurant_h_
#define _Restaurant_h_

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define T Customer  // Use class Customer as Queue data type
#define MAX_SIZE 50 // Maximum number of cashiers & Queues

/******************************************************************************
Class		    : Customer
Description		: Customer class declarations for Assignment 4
Purpose			: To create and manage a Customer object
*******************************************************************************/

/*
class Customer

When a customer enters the restaurant, the entry time is recorded (to be used later to find the waiting time) and their order time is set at random between 2 to 5 minutes.
*/
class Customer{
public:
	Customer();
	Customer(int tIn); 
	~Customer();
	void setTime(int tIn);
	int getTimeIn();
	int getTimeToFulfill();
	
private:
	int timeIn;
	int timeToFulfill;
};


/******************************************************************************
Class		    : Queue
Description		: Queue class declarations for Assignment 4
Purpose			: To create and manage a Queue 
*******************************************************************************/

struct Node{
	T	data;
	Node *next;
	Node *prev;
};

class Queue{
public:
	Queue();
	~Queue();
	void enqueue(T newItem);
	void dequeue(T& queueFront);
	void getFront(T& queueFront);
	bool isEmpty();

private:
	Node *head;
	Node *tail;
	int size;
};


/******************************************************************************
Class		    : Cashier
Description		: Cashier class declarations for Assignment 4
Purpose			: To create and manage a Cashier object
*******************************************************************************/

/*
class Cashier

Defines the cashier(s) in the restaurant.
setSkills() set's the cashier's check out speed.
serveStatus() if a cashier is available at any point of time, the function returns 0. Otherwise it return's the time required to fulfill the current job.
serveNew() determines wether the cashier is busy or free to serve another customer. Return's -1 if busy.
*/

class Cashier{
public:
	Cashier();
	~Cashier();
	void setSkills();  		// Fast = -1, Average = 0, Slow = +1 
	int serveStatus(int t);	// Returns remaining time to fulfill current serve; '0' = not busy
	int serveNew(int startAt, int expectedTime);	// Returns -1 if the Cashier is busy, else return the time required to fulfill new order.
private:
	int skillFactor;   		// Fast = -1, Average = 0, Slow = +1 ... To be added to the checkout time 
	int totalServed;   		// Total number of customers served
	int totalTime;    		// Total time taken
	int timeStarted; 		// Time (in mins) when the current order is started
	int timeToFulfill; 		// Time (in mins) required to fulfill the current order
};



/******************************************************************************
Class		    : Restaurant
Description		: Restaurant class declarations for Assignment 4
Purpose			: To create and manage a Restaurant object
*******************************************************************************/

/*
class Restaurant

The number of cashiers and lines is set from the property file by setCashier() and setLines()
When a customer enters the restuarant, newCustomer() adds the customer, sets the time, and assigns the customer to a line.
updateService() checks if a cashier is available to serve the next customer.
If there is more than one line for cashiers, and one of the cashier's line is empty, updateService moves a waiting customer to the available cashier.
clearQueues() function completes serving all customers in the queue. No customer is added during this period.
*/
class Restaurant{
public:
	Restaurant();
	~Restaurant();
	void setCashiers(int c); // Setup  Cashiers
	void setLines(int n);   // Setup Customer Lines
	int newCustomers(int timeIn, int n); // Add Customers 
	int clearQueues();

	// Accessor Functions
	int getTotalEntered(){return totalCustomersEntered;};	// Returns total number of customers entered in the restaurant
	int getTotalServed(){return totalCustomersServed;};		// Returns total number of customers served at a point of time
	int getTotalWait(){return totalWait;};					// Returns total waiting time
	int getMaxWait(){return maxWait;}; 						// Returns maximum waiting time
	int getTotalServeTime(){return totalServeTime;};		// Returns total serving time
	float getAvgWait(){return static_cast<float> (totalWait)/totalCustomersServed;}; // Returns average waiting time
	float getAvgServeTime(){return  static_cast<float> (totalServeTime)/totalCustomersServed;}; // Returns average serving time

private:
	void updateService();  // Check cashiers available and serve customers
	int totalCustomersEntered;
	int totalCustomersServed;
	int currentTime;
	int totalWait;
	int maxWait;
	int totalServeTime;
	int numberOfCashiers;
	int numberOfLines;
	int cashiersAvailable;
	int customersInQueue;
	Cashier cashier[MAX_SIZE];
	Queue line[MAX_SIZE];
};

/*******************************/
// Function : IntToStr (int tmp)
// convert Integer to String
// A stand alone function used to convert
// integer to string 
/*******************************/

std::string IntToStr(int tmp); 

#endif 
