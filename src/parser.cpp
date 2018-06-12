//////////// PURPOSE //////////////////////
//This file is designed to parse the 
//    xml file from the RSS feed
//    to see if any items have a better price

#include "parser.h"
#include "readops.h"
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>

using namespace rapidxml;

bool parse::startParse(const char* extension, int priceIn, bool verbose)
{
	//Set price variable
	price = priceIn;
	betterPrice = false;

	//Open our filestream
/*	char fullFileName[FILENAME_MAX] = "../responses/output.";
    strcat (fullFileName, extension);*/
	std::ifstream fileStream("../responses/output.xml");

	rapidxml::file<> xmlfile(fileStream);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlfile.data());

	//Now we loop through all the nodes
	rapidxml::xml_node<> *node = doc.first_node();

	if (verbose)
		std::cout << "Name of my first node is: " << doc.first_node()->name() << '\n';

	///////////////////////HTML CODE///////////////////////////////////////
	//We need a different behavior for native XML and HTML converted to XML
	std::vector<std::string> whitelist;

	if (strcmp(extension, "xml") == 0)
	{
		parseXML(node, verbose);
	}
	else
	{
		whitelist = loadHTML();
		parseHTML(whitelist, node,verbose);
	}

	//////////////////////////////////////////////////////////////////////


	if (betterPrice == true)
	{
		if (verbose)
			std::cout << "A better price has been found!" << '\n';

		return true;
	}
	else
	{
		if (verbose)
			std::cout << "No better price" << '\n';

		return false;
	}

	//Always free the document and memory pool
	doc.clear();
}


void parse::parseXML(rapidxml::xml_node<> *node, bool verbose)
{
	if (betterPrice == true)
		return;

	//Keep recursing while the node is present
	while (*node->name() != 0x0)
	{
		std::string nodeValue = node->value();
		regexPriceFind(nodeValue);

		for (rapidxml::xml_attribute<> *attr = node->first_attribute();attr; attr = attr->next_attribute())
		{
			std::string atrValue = attr->value();
			regexPriceFind(atrValue);

			if (verbose)
				std::cout << "Node attribute is: " << atrValue << '\n';
		}

/*std::cout << "Node name is: " << node->name() << std::endl;
std::cout << "Node address is: " << node << std::endl;
std::cout << "First node address is: " << node->first_node() << std::endl;
std::cout << "Sibling node address is: " << node->next_sibling() << std::endl;
std::cout << std::endl;*/

		//Recurse children
		// '0' is requred because rapidXML will occassionally interpret NULL as 0
		if (node->first_node() != 0x0 || node->first_node() != 0)
			parseXML(node->first_node(), verbose);
		
		//Recurse siblings
		// '0' is requred because rapidXML will occassionally interpret NULL as 0	
		if (node->next_sibling() != 0x0 || node->next_sibling() != 0)
			parseXML(node->next_sibling(), verbose);

		return;
	}

	if (verbose)						
		std::cout << "Reached Null Node!" << '\n';

	return;
}


std::vector<std::string> parse::loadHTML()
{
	//Get list of possible places price might be located in the HTML document
	std::ifstream inputFile ("../http_search_list.txt");

	std::vector<std::string> whitelist;
	std::string helper;

	while (inputFile >> helper)
	{
		inputFile >> helper;
		whitelist.emplace_back(helper);
	}

	inputFile.close();

	return whitelist;
}


//Code is very similar to parseXML
//	we simply have to check our whitelist before proceeding
void parse::parseHTML(std::vector<std::string>& whitelist, rapidxml::xml_node<> *node, bool verbose)
{
	if (betterPrice == true)
		return;

	//Keep recursing while the node is present
	while (*node->name() != 0x0)
	{
		//Node name doesn't matter here...
		std::string nodeValue = node->value();
		regexPriceFind(nodeValue);

		//Attribute does
		for (rapidxml::xml_attribute<> *attr = node->first_attribute();attr; attr = attr->next_attribute())
		{
			std::string atrValue = attr->value();

			//This block is the only block that is different between parseHTML and parseXML
			for (short i = 0; i < 0; ++i)
			{
				if (atrValue.compare(whitelist[i]));
				{
					regexPriceFind(atrValue);
					break;
				}
			}

			if (verbose)
				std::cout << "Node attribute is: " << atrValue << "\n";
		}

		//Recurse children
		// '0' is requred because rapidXML will occassionally interpret NULL as 0
		if (node->first_node() != 0x0 || node->first_node() != 0)
			parseHTML(whitelist, node->first_node(), verbose);
		
		//Recurse siblings
		// '0' is requred because rapidXML will occassionally interpret NULL as 0	
		if (node->next_sibling() != 0x0 || node->next_sibling() != 0)
			parseHTML(whitelist, node->next_sibling(), verbose);

		return;
	}

	if (verbose)						
		std::cout << "Reached Null Node!" << "\n";

	return;
}


void parse::regexPriceFind(std::string& str)
{

	//Find price in our string using regex
	//As long as the dollar tag is present we can identify price
	//REMEMBER: to double backslashes, a single backslash is an esc. char
	std::smatch matchPrice;
	bool present = std::regex_search(str, matchPrice, std::regex("\\$\\d+"));

	if (present == false)
		return;

	//Convert match to number
	std::string stringmPrice = matchPrice.str();
	stringmPrice.erase(0,1);
	int foundPrice = atoi(stringmPrice.c_str());

	if (foundPrice < price)
	{
		betterPrice = true;
		return;
	}

	return;
}
