//////////// PURPOSE //////////////////////
//This file is designed to parse the 
//    xml file from the RSS feed
//    to see if any items have a better price


//Version 3.0: Insitituted vector<string> to loop through results
//Version 4.0: Implemented trivial string file parsing & disabled XML/HTML parsing
//Version 5.0: Removed XML/HTML parsing - only better for very large files


#include "parser.h"
#include "readops.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>


void parse::loadHTML()
{
	//Get list of possible places price might be located in the HTML document
	std::ifstream inputFile ("../http_search_list.txt");
	std::string helper = "";

	while (inputFile >> helper)
	{
		inputFile >> helper;
		whitelist.emplace_back(helper);
	}

	inputFile.close();

	return;
}


bool parse::startStringParse(const char* extension, int priceIn, bool verbose)
{
	price = priceIn;

	//Open file
	std::ifstream inputFile ("../responses/output.xml");

	//Declare Variables
	std::string reader = "";
	std::string converter = "";
	std::smatch matchPrice;
	bool present = false;

	//Loop through file
	while (inputFile >> reader)
	{
		for (short i = 0; i < whitelist.size(); ++i)
		{
			if (reader.find(whitelist[i]) != std::string::npos)
			{
				present = std::regex_search(reader, matchPrice, std::regex("\\$\\d+"));

				//If no number is present we don't need to compare the number
				if (present == false)
					continue;

				//Convert match to number
				converter = matchPrice.str();
				converter.erase(0,1);
				foundPrice = atoi(converter.c_str());

				if (foundPrice < price)
				{
					if (verbose)
						std::cout << "Found better price of: " << foundPrice << '\n';

					inputFile.close();

					return true;
				}
			}
		}
	}

	inputFile.close();

	return false;
}