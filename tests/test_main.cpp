#include "test_xmlparser.h"
#include <iostream>
#include <string>
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>

using namespace std;


int main()
{
    //STANDARD IOSTREAM SPEED UP
    ios_base::sync_with_stdio (false);

    //Run tests
    int count_errors = 0;
    int count_tests = 0;
    count_errors = simpleXML(count_tests);



    std::cout << count_errors << "/" << count_tests << " tests failed!" << '\n';

    return 0;
}