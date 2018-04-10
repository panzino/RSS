#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "readops.h"
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>
#include <string>
#include <vector>
#include <regex>


//Requires: the map holding our settings from settings.txt
//Modifies: the map holding our settings
//Effects: parses XML setting
void startParse(std::vector<settings>& map, std::string fileName);

//Requires: the top node
//Modifies: nothing
//Effects: traverses the RSS nodes
void parseXML(rapidxml::xml_node<> *node, int price);

//Requires: the price of the item
//Modifies: nothing
//Effects: searches the parsed strings for the dollar value
bool regexPriceFind(std::string str, int price);





#endif