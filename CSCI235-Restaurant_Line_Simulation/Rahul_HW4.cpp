/******************************************************************************
Title			: Rahul_HW4.cpp
Author	    	: Rahul Prithu
Created on		: March 31, 2012
Description		: Main .cpp file for Assignment 4
Purpose			: Main .cpp file for Assignment 4
Usage			: ./<insert-name> <properties file>
Build with		: g++ -o <insert-name> Rahul_HW4.cpp Rahul_Restaurant.cpp Properties.cpp
Modifications	: 
*******************************************************************************/

#include "Rahul_Restaurant.hpp"
#include "properties.hpp"
using namespace std;


int main (int argc, char *argv[]) {
	int currTime = 0; 
	int firstHour = 7;			// Restaurant Opening Time
	int lastHour = 21 ;			// Restaurant Closing Time
	int customerPerMinute=0;	// Number of customers entering per minute
	int nCashiers=0;			// Number of Cashiers
	int nLines=0;				// Number of lines, single or cashiers.
	string s, sKey;
	int hr, mins;
	
	Restaurant R;
	
	Properties *prop;

	srand( time(NULL) );

	prop = Properties::getInstance();
	if (!prop->readPropertyFile(argv[1])){
		cout << "Failed to open the file!\n"; 
		return 0;
		}
	s = prop->getProperty("cashiers "); // Get number of cashiers
	nCashiers=atoi(s.c_str()); 
	if (nCashiers<=0){
		cout << "Unable to assign cashiers! \n"; 
		return 0;
		}

	s = prop->getProperty("lines "); // Get line type
	if (s==" single")
		nLines=1;
	else
		nLines = nCashiers;

	R.setCashiers(nCashiers);
	R.setLines(nLines);
		
		
	for (hr = firstHour; hr <=lastHour; hr++){
		sKey = "hour" + IntToStr(hr) + " ";
		s = prop->getProperty(sKey); // Get number of cashiers
		customerPerMinute=atoi(s.c_str());
		for (mins =0; mins<60; mins++){
			R.newCustomers(currTime, customerPerMinute);
			currTime++;
		}
	}

	cout << "Simulation Report:\n";
	cout << "--------------------------------- \n";
	cout << "Cashiers: " << nCashiers << "\n"; 
	cout << "Lines: " << nLines << "\n\n"; 

	cout<< "Status after adding the last customer:\n";
	cout<< "Current Time \t\t: "<< currTime << " mins \n";
	cout<< "Customers Entered \t: "<< R.getTotalEntered() << " \n";
	cout<< "Customers Served \t: "<< R.getTotalServed() << " \n";
	cout<< "Total Serving Time \t: "<< R.getTotalServeTime() << " mins \n";
	cout<< "Maximum Wait Time \t: "<< R.getMaxWait() << " mins \n";
	cout<< "Average Service Time \t: "<< R.getAvgServeTime() << " mins \n";
	cout<< "Average Waiting Time \t: "<< R.getAvgWait() << " mins \n\n";

	cout<< "Status after serving the last customer:\n";
	cout<< "Current Time \t\t: "<< R.clearQueues() << " mins \n";
	cout<< "Customers Entered \t: "<< R.getTotalEntered() << " \n";
	cout<< "Customers Served \t: "<< R.getTotalServed() << " \n";
	cout<< "Total Serving Time \t: "<< R.getTotalServeTime() << " mins \n";
	cout<< "Maximum Wait Time \t: "<< R.getMaxWait() << " mins \n";
	cout<< "Average Service Time \t: "<< R.getAvgServeTime() << " mins \n";
	cout<< "Average Waiting Time \t: "<< R.getAvgWait() << " mins \n\n";

	return 0;
}
