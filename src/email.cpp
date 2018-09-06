/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
//Modified from above source


#include "email.h"
#include "readops.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <iostream>
#include <string>
#include <vector>


//This creates a vector<string> because payload_source calls
//     is called multiple times and reads in the payload
//     specifications line by line
//     and a string is much easier to use than a char*[]
//WARNING: because of cUrl you cannot convert strings to c strings
 //    it is not possible and will cause undefined behavior due to 
 //    cUrl memory allocation
std::vector<const char*> formatMessage(std::vector<settings>& map, std::vector<short>& send)
{
    std::vector<const char*> message;
    message.reserve(10);
    message.emplace_back("Date: Mon, 16 April 2018 14:52:29 +1100\r\n");
    message.emplace_back("To:" TO ">\r\n");
    message.emplace_back("From:" FROM " (Mail Bot)\r\n");
    message.emplace_back("Cc:" CC " (Placeholder)\r\n");
    message.emplace_back("Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efd@rssmailbot@gmail.com>\r\n");
    message.emplace_back("Subject: Price Alert!\r\n");
    //empty line to divide headers from body, see RFC5322
    message.emplace_back("\r\n");


    //Now we add our items w/ price alerts to the message body
    //Remember that we must use pointers here because c_str points
    //    to the original string's array...so once that string
    //    goes out of scope the c_str will point to random bits
    //&map[i].item finds the memory address of string 'item' in 
    //    our struct map
    //* - dereferences this memory address to provide the actual
    //    memory address where this data is stored and not a copy
    //    that will be destroyed once this function is over
    for (unsigned short i = 0; i < send.size(); ++i)
    {
        if (send[i])
        {
            message.emplace_back("Item:\r\n");
            message.emplace_back((*(&map[i].item)).c_str());
            message.emplace_back("\r\n");

            message.emplace_back("Url:\r\n");
            message.emplace_back((*(&map[i].url)).c_str());
            message.emplace_back("\r\n");
        }
    }

    //Null pointer terminator is needed for libcurl compatibility
    //    libcurl looks for this null pointer to know when to stop
    //    reading in the message
    message.push_back(NULL);

    return message;
}


//This function is called multiple times by curl...
//    therefore 
static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
    struct variables *variablesList = (struct variables *)userp;
    const char *data;

    //Error checking
    if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) 
    {
        return 0;
    }

    //Might have to change the struct to hold map and send....
    data = variablesList->message[variablesList->linesRead];

    if(data) 
    {
        size_t len = strlen(data);
        memcpy(ptr, data, len);
        variablesList->linesRead++;
        return len;
    }

    return 0;
}


void sendEmail(std::vector<settings>& map, std::vector<short>& send, bool verbose)
{
    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = NULL;

    //Initialize our variables
    struct variables variablesList = variables(map, send);

    curl = curl_easy_init();
    if(curl) 
    {

      // Set username and password 
      curl_easy_setopt(curl, CURLOPT_USERNAME, FROM);
      curl_easy_setopt(curl, CURLOPT_PASSWORD, getenv("RSSPass"));

      // This is the URL for your mailserver
      curl_easy_setopt(curl, CURLOPT_URL, "smtp.googlemail.com:587");

      //Start TLS
      curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);

      /* If you want to connect to a site who isn't using a certificate that is
       * signed by one of the certs in the CA bundle you have, you can skip the
       * verification of the server's certificate. This makes the connection
       * A LOT LESS SECURE.
       *
       * If you have a CA cert for the server stored someplace else than in the
       * default bundle, then the CURLOPT_CAPATH option might come handy for
       * you. */
#ifdef SKIP_PEER_VERIFICATION
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

      /* If the site you're connecting to uses a different host name that what
       * they have mentioned in their server certificate's commonName (or
       * subjectAltName) fields, libcurl will refuse to connect. You can skip
       * this check, but this will make the connection less secure. */
#ifdef SKIP_HOSTNAME_VERIFICATION
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

    /* Note that this option isn't strictly required, omitting it will result
       * in libcurl sending the MAIL FROM command with empty sender data. All
       * autoresponses should have an empty reverse-path, and should be directed
       * to the address in the reverse-path which triggered them. Otherwise,
       * they could cause an endless loop. See RFC 5321 Section 4.5.5 for more
       * details.
       */
      curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM);

      /* Add two recipients, in this particular case they correspond to the
       * To: and Cc: addressees in the header, but they could be any kind of
       * recipient. */
      recipients = curl_slist_append(recipients, TO);
      recipients = curl_slist_append(recipients, CC);
      curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

      /* We're using a callback function to specify the payload (the headers and
       * body of the message). You could just use the CURLOPT_READDATA option to
       * specify a FILE pointer to read from. */
      curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
      curl_easy_setopt(curl, CURLOPT_READDATA, &variablesList);
      curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

      /* Since the traffic will be encrypted, it is very useful to turn on debug
       * information within libcurl to see what is happening during the
       * transfer */
      if (verbose)
          curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

      /* Send the message */
      res = curl_easy_perform(curl);

      if (verbose)
      {
          char *buf;
          curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, buf);

          /* Check for errors */
          if(res != CURLE_OK)
          {
              fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
              fprintf(stderr, buf);
          }
      }
      /* Free the list of recipients */
      curl_slist_free_all(recipients);

      /* Always cleanup */
      curl_easy_cleanup(curl);

    }

    return;
}
