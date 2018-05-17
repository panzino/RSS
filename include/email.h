#ifndef EMAIL_H
#define EMAIL_H


#include "readops.h"
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <curl/curl.h>

//Requires:
//Modifies: 
//Effects: creates formated message to send via email
std::vector<const char*> formatMessage(std::vector<settings>& map, std::vector<short> send);

//Requires:
//Modifies: 
//Effects: 
static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp);

//Requires: vector of what items have a better price
//Modifies: nothing
//Effects: sends an email using SMTP settings through Gmail
void sendEmail(std::vector<settings>& map, std::vector<short> send, bool verbose);


//This struct is a method of preserving data
//    passed in during the call of sendEmail
//    when the function callback is initiated
//I have to use this structure because libcurl
//    is written in C code and must use a pointer
//This is C++ I'm using a vector not an array
struct variables
{

public:
    std::vector<const char*> message;
    unsigned short linesRead;

    //Requires: Nothing
    //Modifies: variables struct
    //Effects: constructor for creating variables struct
    variables(std::vector<settings>& mapIn, std::vector<short> sendIn)
    {
        message = formatMessage(mapIn, sendIn);
        linesRead = 0;
    }
};


#endif
