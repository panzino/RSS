#include "parser.h"
#include "fixer.h"
#include <iostream>
#include <string>
#include <rapidxml.hpp>
#include <fstream>

#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>



//Requires: nothing
//Modifies: nothing
//Effects: tests parser implmentation
short fileTest(std::string fileName, std::string masterName, int priceIn, bool verbose, bool truth)
{

    //This copies the input file to GET_Response
    //This way we don't have to change the source code
    //We are doing this throught the file system
    //  because it's quicker and the filesystem is
    //  designed to handle these tasks
    short success = 0;
    int source = open(fileName.c_str(), O_RDONLY, 0644);
    int dest = open("../responses/GET_Response.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    struct stat stat_source;
    fstat(source, &stat_source);
    int error = sendfile(dest, source, 0, stat_source.st_size);
    if (error == -1)
    {
        std::cerr << "FILE TRANSFER ERROR! ABORTING FURTHER TESTS!" << '\n';
        return 0;
    }
    close(source);
    close(dest);

    //Run Tidy on the example code
    fixFormatting(false);

    //First we need to redirect cout and clean the file
    std::ofstream out("parseOut.txt", std::ofstream::trunc);
    std::streambuf *coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());

    //Now we compare the output
    bool succeded = false;
    parse start = parse();
    start.loadHTML();
    succeded = start.startStringParse(priceIn, true);

    //Redirect cout to terminal
    std::cout.flush();
    std::cout.rdbuf(coutbuf);
    out.close();

    //Compare output from 'startStringParse'
    std::ifstream response("parseOut.txt");
    std::string stringResponse = "";
    std::getline(response, stringResponse);
    response.close();

    //Get response we expect
    std::ifstream master(masterName);
    std::string stringMaster = "";
    std::getline(master, stringMaster);
    master.close();

    if (stringMaster.compare(stringResponse) != 0)
    {
        std::cerr << "TEST '" << fileName << "' FAILED: WRONG PRICE DETECTION" << '\n';
        std::cerr << "      OUTPUT: " << stringResponse << '\n';
        return 0;
    }

    if (truth == succeded)
        success += 1; 
    else
        std::cerr << "TEST '" << fileName << "' FAILED: WRONG RESPONSE" << '\n';

    return success;
}


//Requires: nothing
//Modifies: nothing
//Effects: tests parser implmentation
void test_parser()
{
    std::cerr << "STARTING PARSER TESTING" << '\n';

    //Run simple test
    short passed = 0;

    //Run parsing test
    passed += fileTest("../responses/examples/ebay_example.html", "../responses/test_responses/ebay_response.txt", 25, 0, 1);
    passed += fileTest("../responses/examples/walmart_example.html", "../responses/test_responses/walmart_response.txt", 38, 0, 1);
    passed += fileTest("../responses/examples/rockauto_example.html", "../responses/test_responses/rockauto_response.txt", 13, 0, 1);
    passed += fileTest("../responses/examples/amazon_example.html", "../responses/test_responses/amazon_response.txt", 6, 0, 1);

    std::cerr << "PASSED: " << passed << "/" << 4 << " TESTS" << '\n';
    std::cerr << '\n';
}






