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
	int price;
	bool betterPrice;

public:
	//Requires: the map holding our settings from settings.txt
	//Modifies: the map holding our settings
	//Effects: parses XML setting
	bool startParse(const char* extension, int priceIn, bool verbose);

	//Requires: the top node
	//Modifies: nothing
	//Effects: traverses the RSS nodes
	void parseXML(rapidxml::xml_node<> *node, bool verbose);

	//Requires: nothing
	//Modifies: vector<string> 
	//Effects: creates list of places the item price is located
	//			at various merchants
	//We cannot use our trivial solution of just using a Regex
	//	because the $ symbol is rather common in HTML and leads
	//	to a lot of false positives
	//IF I really wanted to I could make the vector<string>
	//	a member of the class....
	std::vector<std::string> loadHTML();

	//Requires: the top node
	//Modifies: nothing
	//Effects: traverses the HTML that is converted to XML
	//			by fixer.cpp
	void parseHTML(std::vector<std::string>& whitelist, rapidxml::xml_node<> *node, bool verbose);

	//Requires: the price of the item
	//Modifies: nothing
	//Effects: searches the parsed strings for the dollar value
	void regexPriceFind(std::string& str);
};


#endif