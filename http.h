#ifndef HTTP_H
#define HTTP_H


#include "readops.h"
#include <stdio.h>
#include <curl/include/curl/curl.h>
#include <string>


//Requires:
//Modifies: 
//Effects: 
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);

//Requires: the map holding our settings from settings.txt
//Modifies: the map holding our settings
//Effects: downloads .xml RSS feed from URLs in map
void sendGET(std::vector<settings>& map);



#endif