//////////// PURPOSE //////////////////////
//FROM: libcurl example library
//This file is designed to send a HTTP 
//    GET request based on the URL that
//    is provided in settings.txt
//TODO: Rewrite the file using C++ syntax

#include "http.h"
#include "readops.h"
#include <stdio.h>
#include <curl/curl.h>
#include <string>
#include <cstring>


using namespace std;

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) 
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}


//const char*: required for C/C++ string compatability in cUrl
//Not exactly safe as this is a pointer to original string
//    so if original string dies...this dies too
void sendGET(const char* url, const char* extension, bool verbose)
{
    CURL *curl;
    FILE *fp;
    CURLcode res;

    //const char* url = set.url.c_str();
    char outfilename[FILENAME_MAX] = "../responses/output.";
    strcat (outfilename, extension);

    curl = curl_easy_init();
    if (curl) 
    {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

	//Verbose output for debugging
	if (verbose)
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

	//Send Message
        res = curl_easy_perform(curl);

	if (verbose)
	{
	    //Back to Verbose Mode
	    char *buf;
	    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, buf);

	    if (res != CURLE_OK)
	    {
	 	    fprintf(stderr, "curl_easy_perfor() failed: %s\n", curl_easy_strerror(res));
	  	    fprintf(stderr, buf);
	    }
	}

        //always cleanup
        curl_easy_cleanup(curl);
        fclose(fp);
    }

    return;
}
