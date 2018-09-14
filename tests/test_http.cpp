#include "http.h"
#include <stdio.h>
#include <curl/curl.h>
#include <string>
#include <fstream>

using namespace std;


//Requires: two file names
//Modifies: nothing
//Effects: uses standard library implementation to compare
//			two files
bool compareFiles(const string& file1, const string& file2) 
{
	ifstream f1(file1, ifstream::binary|ifstream::ate);
	ifstream f2(file2, ifstream::binary|ifstream::ate);

	//file problem
	if (f1.fail() || f2.fail()) 
	  return false; 
	
	//size mismatch
	if (f1.tellg() != f2.tellg())
	  return false; 

	//seek back to beginning and use std::equal to compare contents
	f1.seekg(0, ifstream::beg);
	f2.seekg(0, ifstream::beg);
	return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
	                  std::istreambuf_iterator<char>(),
	                  std::istreambuf_iterator<char>(f2.rdbuf()));
}


//Requires: two file names
//Modifies: nothing
//Effects: tests http.cpp implementation
void test_http()
{
	cerr << "STARTING HTTP TESTING" << '\n';

	//Send GET request to webpage that doesn't change frequently
	string url = "http://home.mcom.com/home/welcome.html";

	sendGET(url.c_str(), false);

	string fileGrabbed = "../responses/GET_response.txt";
	string fileStatic = "../responses/examples/HTTP_test.html";

	bool failed = compareFiles(fileGrabbed, fileStatic);

	if (!failed)
	{
		cerr << "FILES ARE NOT THE SAME!" << '\n';
	}

	cerr << "PASSED: " << failed << "/1 TESTS" << '\n';
	cerr << '\n';
}

