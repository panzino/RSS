#include "parser.h"
#include <iostream>
#include <string>
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>
#include <fstream>

#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

using namespace rapidxml;


//Requires: nothing
//Modifies: nothing
//Effects: tests rapidxml parsing
short simpleXML()
{
    short count_errors = 0;

    rapidxml::file<> xmlfile("../responses/simple.xml");
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlfile.data());

    rapidxml::xml_node<> *node = doc.first_node(doc.first_node()->name());

    //TEST 1
    //Test name of first child node
    std::string first_node = doc.first_node()->name();
    if (first_node.compare("note"))
        std::cerr << "TEST 1 (simple): FAILED -> first node names do not match!" << '\n';
    else
        count_errors += 1;

    //TEST 2
    //Test attribute in last node
    rapidxml::xml_attribute<> *attr = node->first_attribute();
    first_node = attr->value();

    if (first_node.compare("Daniel"))
        std::cerr << "TEST 2 (simple): FAILED -> first node attributes do not match!" << '\n';
    else
        count_errors += 1;

    //Go to child node
    node = node->first_node(node->first_node()->name());

    //TEST 3
    //Test content in last node
    first_node = node->value();

    if (first_node.compare("Tove"))
        std::cerr << "TEST 3 (simple): FAILED -> first node values do not match!" << '\n';
    else
        count_errors += 1;



    return count_errors;
}


//Requires: nothing
//Modifies: nothing
//Effects: tests parser implmentation
short fileTest(std::string fileName, int priceIn, bool verbose, bool truth)
{


    //We are doing this throught the file system
    //  because it's quicker and the filesystem is
    //  designed to handle these tasks
    short success = 0;
    int source = open(fileName.c_str(), O_RDONLY, 0);
    int dest = open("../responses/output.xml", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    struct stat stat_source;
    fstat(source, &stat_source);
    sendfile(dest, source, 0, stat_source.st_size);
    close(source);
    close(dest);


    bool succeded = false;
    parse start = parse();
    succeded = start.startParse(priceIn, verbose);


    if (truth == succeded)
        success += 1; 
    else
        std::cerr << "Test '" << fileName << "' FAILED: WRONG PRICE DETECTION" << '\n';

    return success;
}


//Requires: nothing
//Modifies: nothing
//Effects: tests parser implmentation
void test_parser()
{
    std::cerr << "STARTING PARSER TESTING" << '\n';

    short passed = simpleXML();
    passed += fileTest("../responses/tidy.xml", 110, 0, 0);
    passed += fileTest("../responses/simple.xml", 100, 0, 0);

    std::cerr << "PASSED: " << passed << "/" << 5 << " TESTS" << '\n';
    std::cerr << '\n';
}






