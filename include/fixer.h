#include <tidy.h>
#include <tidybuffio.h>
#include <stdio.h>
#include <errno.h>
#include <fstream>
#include <string>


//Requires: file extension of output file
//Modifies: output file from GET request
//Effects: fixes any formatting error in HTML or XML
//			from GET request
void fixFormatting(const char* extension, bool verbose);
