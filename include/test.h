#include "http.h"
#include "parser.h"
#include "readops.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <stdio.h>
#include <curl/curl.h>


//Requires: nothing
//Modifies: nothing
//Effects: tests readops.cpp implementation
void test_readops();
short test_content (vector<settings>& read_test, vector<settings>& read_actual);
short test_length (vector<settings>& read_test, vector<settings>& read_actual);


//Requires: nothing
//Modifies: nothing
//Effects: tests parser implmentation
void test_parser()
short simpleXML()


//Requires: two file names
//Modifies: nothing
//Effects: tests http.cpp implementation
void test_http()
bool compareFiles(const string& file1, const string& file2) 