#include "readops.h"
#include "http.h"
#include "parser.h"
#include "email.h"
#include <getopt.h>
#include <iostream>
#include <string>

using namespace std;


//Struct for getops_long
static struct option longopts[] = 
{
    {"help", no_argument, nullptr, 'h'},
    {"verbose", no_argument, nullptr, 'v'},
    {nullptr, 0, nullptr, 0}
};


int main(int argc, char *argv[])
{
    //STANDARD IOSTREAM SPEED UP
    ios_base::sync_with_stdio (false);

    ///////////////////////////////////////
    ////////START GETOPS /////////////////
    /////////////////////////////////////
    int index = 0;
    bool verbose = false;
    char c;

    //I'm keeping getops because I might one day decide to utilize it more
    //    it'll make my life easier eventually
    while ((c = getopt_long (argc, argv, "hq", longopts, &index)) != -1)
    {
        switch (c)
        {
            case 'h':   //Print a help message 
                        cout << "This program is designed to parse";
                        cout << " RSS feeds. And alert the user ";
                        cout << "when items are at a pre-set price point" << '\n';
                        cout << "Options are:" << '\n';
                        cout << "-r / --run: Run the program" << '\n';
                        cout << "-h / --help: Describe program and options" << '\n';
                        return 0;
            case 'v':   //Set verbose to true
                        verbose = true;
        }
    }
    /////////////////////////////////////
    //////////////END GETOPS ///////////
    ////////////////////////////////////

    //Now we run the program

    //1. GET SETTINGS
    //FROM: readops and settings.txt
    //TODO: Rewrite the settings importation code to work with Boost.program_options
    //TODO: OR rewrite the code so it's prettier
    vector<settings> map;
    readSettings(map);

    //Cache our responses so we only send one email
    //Execute tracks if we need to send an email
    //Send tracks which items we need to send an email for
    bool execute = false;
    vector<bool> send;
    send.reserve(map.size());

    for (unsigned short i = 0; i < map.size(); ++i)
    {
        //2. GET RSS XML FILES
        //FROM: http
        //TODO: Refactor code from C to C++
        sendGET(map[i]);

        //3. PARSE THE XML FILES
        //FROM: xmlparser'
        //TODO: write a quicker string parser for small files
        parse start = parse();
        send[i] = start.startParse(map[i].price, verbose);

        execute += send[i];
    }

        //4. IF REQUIRED- SEND EMAIL
        //FROM: sendemail
        //TODO: Refactor code from C to C++
        if (execute)
            sendEmail(send);
    

    return 0;
}