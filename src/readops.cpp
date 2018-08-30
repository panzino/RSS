//////////// PURPOSE //////////////////////
//This file is designed to parse the 
//    user configured settings contained
//    in settings.txt
//I will eventually get to optimizing this file...

#include "readops.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void readSettings(vector<settings>& map)
{	
	//init variables
	int loops;
	string temp;
	string url;
	string item;
	string ext;
	int price;

	ifstream settingsFile("../settings.txt");

	//find how many loops we need to perform
	settingsFile >> loops;

	//reserve memory before allocation
	map.reserve(loops);
	
	//pull data from settings.txt
	for (unsigned short i = 0; i < loops; ++i)
	{
		settingsFile >> temp >> temp >> temp;
		settingsFile >> url;
		settingsFile >> temp >> temp;
		settingsFile >> item;
		settingsFile >> temp >> temp;
		settingsFile >> ext;
		settingsFile >> temp >> temp;
		settingsFile >> price;

		map.emplace_back(settings(url, item, ext, price));
	}

	return;
}
