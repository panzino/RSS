#ifndef PROGRAM_OPTIONS_H
#define PROGRAM_OPTIONS_H


#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <sstream>

//A struct to hold the values read in from settings
struct settings
{
public:

    std::string url; 
    std::string item;
    std::string ext;
    int price;

    //Requires: Nothing
    //Modifies: Nothing
    //Effects: default constructor
    settings(){}

   	//Requires: Nothing
    //Modifies: settings struct
    //Effects: constructor for settings struct
    settings(std::string& urlIn, std::string& itemIn, std::string& extIn, int priceIn)
    {
       url = urlIn;
       item = itemIn;
       ext = extIn;
       price = priceIn;
    }

};

//Requires: the map holding our settings from settings.txt
//Modifies: the map holding our settings
//Effects: opens settings.txt and reads data into it
void readSettings(std::vector<settings>& map);


#endif