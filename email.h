#ifndef EMAIL_H
#define EMAIL_H

#include <stdio.h>
#include <string.h>
#include <curl/include/curl/curl.h>


//Requires:
//Modifies: 
//Effects: 
static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp);

//Requires:
//Modifies: 
//Effects: 
void sendEmail();


#endif