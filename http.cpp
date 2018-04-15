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

void sendGET(vector<settings>& map)
{
    CURL *curl;
    FILE *fp;
    CURLcode res;

    //Required for C/C++ string compatability
    const char *url = "https://www.newegg.com/Product/RSS.aspx?Submit=Property&N=100007609%20600006178%20600213067%20600564396%20600006157&IsNodeId=1&ShowDeactivatedMark=False";

    //DELETE
    cout << map[0].url << endl;

    char outfilename[FILENAME_MAX] = "responses/output2.xml";
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
