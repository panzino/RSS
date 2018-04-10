//I will eventually get to optimizing this file...
//  because it is crap

#include "readops.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


void readSettings(vector<settings>& map)
{	
	//init variables
	int loops;
	string temp;
	string url;
	string item;
	int price;

	ifstream settingsFile("settings.txt");

	settingsFile >> temp; 
	loops = temp[1] - 48;

	//Background stuff...
	map.reserve(loops);
	
	//pull data from settings.txt
	for (int i = 0; i < loops; ++i)
	{
		settingsFile >> temp >> temp >> temp;
		settingsFile >> url;
		settingsFile >> temp >> temp;
		settingsFile >> item;
		settingsFile >> temp >> temp;
		settingsFile >> price;

		map.emplace_back(settings(url,item,price));
	}

	return;
}