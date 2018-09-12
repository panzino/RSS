#ifndef XMLPARSER_H
#define XMLPARSER_H


#include "readops.h"
#include <string>
#include <vector>
#include <regex>

//Easier to just use a global variable with the recurssive function
class parse
{

private:
	std::vector<std::string> whitelist;
	int price;
	int foundPrice;

public:
	parse()
	{
		whitelist = {};
		price = 0;
		foundPrice = 0;
	}

	//Requires: nothing
	//Modifies: vector<string> 
	//Effects: creates list of places the item price is located
	//			at various merchants
	//We cannot use our trivial solution of just using a Regex
	//	because the $ symbol is rather common in HTML and leads
	//	to a lot of false positives
	void loadHTML();
	
	//Requires: the input file
	//Modifies: nothing
	//Effects: parses as a string
	bool startStringParse(const char* extension, int priceIn, bool verbose);
};


#endif