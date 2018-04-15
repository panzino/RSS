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
	void startParse(std::vector<settings>& map, std::string fileName);

	//Requires: the top node
	//Modifies: nothing
	//Effects: traverses the RSS nodes
	void parseXML(rapidxml::xml_node<> *node);

	//Requires: the price of the item
	//Modifies: nothing
	//Effects: searches the parsed strings for the dollar value
	void regexPriceFind(std::string& str);
};



#endif