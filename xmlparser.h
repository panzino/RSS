#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "readops.h"
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>
#include <string>
#include <vector>

//Requires: the map holding our settings from settings.txt
//Modifies: the map holding our settings
//Effects: parses XML setting
void startParse(std::vector<settings>& map, std::string fileName);







#endif