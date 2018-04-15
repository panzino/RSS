//////////// PURPOSE //////////////////////
//FROM: libcurl example library
//This file is designed to send a HTTP 
//    GET request based on the URL that
//    is provided in settings.txt
//TODO: Rewrite the file using C++ syntax

#include "http.h"
#include "readops.h"
#include <stdio.h>
#include <curl/include/curl/curl.h>
#include <string>


using namespace std;

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) 
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void sendGET(settings& set)
{
    CURL *curl;
    FILE *fp;
    CURLcode res;

    //Required for C/C++ string compatability in cUrl
    //Not exactly safe as this is a pointer to original string
    //    so if original string dies...this dies too
    const char* url = set.url.c_str();

    char outfilename[FILENAME_MAX] = "responses/output.xml";
    curl = curl_easy_init();
    if (curl) 
    {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);

        //always cleanup
        curl_easy_cleanup(curl);
        fclose(fp);
    }

    return;
}
