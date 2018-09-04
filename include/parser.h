#ifndef XMLPARSER_H
#define XMLPARSER_H


#include "readops.h"
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>
#include <string>
#include <vector>
#include <regex>

//Easier to just use a global variable with the recurssive function
class parse
{

private:
	std::vector<std::string> whitelist;
	std::vector<std::string> value;
	std::string helper;
	int price;
	int foundPrice;
	bool betterPrice;
	bool present;

	//Requires: the top node
	//Modifies: nothing
	//Effects: traverses the RSS nodes
	void parseXML(rapidxml::xml_node<> *node, bool verbose);

	//Requires: the price of the item
	//Modifies: nothing
	//Effects: searches the parsed strings for the dollar value
	bool regexPriceFind();

public:
	parse()
	{
		whitelist = {};
		value = {};
		helper = "";
		price = 0;
		betterPrice = false;
		present = false;
	}

	//Requires: nothing
	//Modifies: vector<string> 
	//Effects: creates list of places the item price is located
	//			at various merchants
	//We cannot use our trivial solution of just using a Regex
	//	because the $ symbol is rather common in HTML and leads
	//	to a lot of false positives
	void loadHTML();
	
	//Requires: the map holding our settings from settings.txt
	//Modifies: the map holding our settings
	//Effects: parses XML setting
	bool startParse(const char* extension, int priceIn, bool verbose);
};


#endif