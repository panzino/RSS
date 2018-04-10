#include "http.h"
#include "parser.h"
#include "readops.h"
#include <getopt.h>
#include <iostream>
#include <string>

using namespace std;


//Struct for getops_long
static struct option longopts[] = 
{
    {"help", no_argument, nullptr, 'h'},
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

    //2. GET RSS XML FILES
    //FROM: http


    //3. PARSE THE XML FILES
    //FROM: xmlparser'
    //TODO: write a quicker string parser for small files
    startParse(map, "responses/simple.xml");


    //4. IF REQUIRED- SEND EMAIL
    //FROM: sendemail

    return 0;
}