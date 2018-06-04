#ifndef HTTP_H
#define HTTP_H


#include "readops.h"
#include <stdio.h>
#include <curl/curl.h>
#include <string>

//Requires:
//Modifies: the file pointed to
//Effects: writes the data from the request to a file
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);

//Requires: the settings from one item in settings.txt
//Modifies: output.xml
//Effects: downloads .xml RSS feed from URLs in settings variable
//TODO: rewrite this code to work w/ XML and HTML
void sendGET(const char* url, const char* extension, bool verbose);


#endif
