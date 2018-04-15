#ifndef EMAIL_H
#define EMAIL_H


#include <stdio.h>
#include <string.h>
#include <curl/include/curl/curl.h>

//Requires:
//Modifies: 
//Effects: creates formated message to send via email
std::string formatMessage();

//Requires:
//Modifies: 
//Effects: 
static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp);

//Requires: vector of what items have a better price
//Modifies: nothing
//Effects: sends an email using SMTP settings through Gmail
void sendEmail(vector<bool> send);


#endif