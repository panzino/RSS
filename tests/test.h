#include "http.h"
#include "fixer.h"
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
short test_content (std::vector<settings>& read_test, std::vector<settings>& read_actual);
short test_length (std::vector<settings>& read_test, std::vector<settings>& read_actual);


//Requires: nothing
//Modifies: nothing
//Effects: tests parser implmentation
void test_parser();
short fileTest(std::string fileName, std::string masterName, int priceIn, bool verbose, bool truth);


//Requires: two file names
//Modifies: nothing
//Effects: tests http.cpp implementation
void test_http();
bool compareFiles(const std::string& file1, const std::string& file2);