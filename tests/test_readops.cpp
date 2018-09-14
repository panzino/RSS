#include "readops.h"
#include "email.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//TEST 1
//Check if the vectors are the same size
short test_length (vector<settings>& read_test, vector<settings>& read_actual)
{
    if (read_test.size() != read_actual.size())
    {
    	cerr << "TEST 1: FAILED -> Vector lengths are not the same size" << '\n';
    	cerr << "				further tests will be skipped" << '\n';
    	cerr << '\n';
    	return 0;
    }

    return 1;
}

//TESTS 2-4
//Check if the vectors have the same content
//I could functionalize the comparisons here...but that'd hurt readability
//	and performance isn't essential for the testing suite
short test_content (vector<settings>& read_test, vector<settings>& read_actual)
{
	short count_errors = 0;

	for (short i = 0; i < read_test.size(); ++i)
	{
		cerr << "TESTING CONTENT OF ELEMENT: " << i << '\n';

		//TEST 2
		//Compare the url parameters
		if (read_test[i].url.compare(read_actual[i].url) != 0)
			cerr << "	TEST " << i << ".2: FAILED -> url parameters are not the same for element " << i << '\n';
		else
			count_errors += 1;

		//TEST 3
		//Compare the item parameters
		if (read_test[i].item.compare(read_actual[i].item) != 0)
			cerr << "	TEST " << i << ".3: FAILED -> item parameters are not the same for element " << i << '\n';
		else
			count_errors += 1;

		//TEST 4
		//Compare the price parameters
		if (read_test[i].price != read_actual[i].price)
			cerr << "	TEST " << i << ".4: FAILED -> price parameters are not the same for element " << i << '\n';
		else
			count_errors += 1;
	}

	return count_errors;
}


//Requires: nothing
//Modifies: nothing
//Effects: tests readops.cpp implementation
void test_readops()
{
	cerr << "STARTING READOPS TESTING" << '\n';

	vector<settings> read_test;

	string url = "https://www.amazon.com/s?url=search-alias%3Daps&field-keywords=light+bulbs";
	string item = "light_bulbs";
    int price = 20;

    read_test.emplace_back(settings(url, item, price));

    url = "https://www.newegg.com/Product/RSS.aspx?Submit=Property&N=100007609%20600006178%20600213067%20600564396%20600006157&IsNodeId=1&ShowDeactivatedMark=False";
    item = "1600";
    price = 100;

    read_test.emplace_back(settings(url,item,price));

    vector<settings> read_actual;
    readSettings(read_actual);

    //Counter for errors
    short counter = 0;

    counter += test_length(read_test, read_actual);

    if (counter == 0)
    	return;

    counter += test_content(read_test, read_actual);

    cerr << "PASSED: " << counter << "/" << read_test.size()*3 + 1 << " TESTS" << '\n';
    cerr << '\n';
}