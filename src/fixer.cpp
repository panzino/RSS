#include "fixer.h"
#include <tidy.h>
#include <tidybuffio.h>
#include <stdio.h>
#include <errno.h>
#include <fstream>
#include <string>
#include <iostream>

void fixFormatting(const char* extension, bool verbose)
{
	//I decided to use fstream because I might as well use the C++ methods
	//std::ifstream inputFile ("../responses/GET_Response.xml");
	std::ifstream inputFile ("../responses/GET_Response.xml");
	std::string inputString;

	inputFile.seekg(0, std::ios::end);   
	inputString.reserve(inputFile.tellg());
	inputFile.seekg(0, std::ios::beg);

	//Read input data from input file
	inputString.assign((std::istreambuf_iterator<char>(inputFile)),
            	std::istreambuf_iterator<char>());


	const char* input = inputString.c_str();
	TidyBuffer output = {0};
	TidyBuffer errbuf = {0};
	int rc = -1;
	bool ok;

	std::ofstream outFile("../responses/output.xml");

	//Init doc
	TidyDoc tdoc = tidyCreate();
	
	//Conver to XML
	ok = tidyOptSetBool(tdoc, TidyXmlOut, yes);

	//Error handling
	if (ok)
		rc = tidySetErrorBuffer(tdoc, &errbuf);
	if (rc >= 0)
		rc = tidyParseString(tdoc, input);
	if (rc >= 0)
		rc = tidyCleanAndRepair(tdoc);
	if (rc >= 0)
   	 	rc = tidyRunDiagnostics(tdoc);
  	if ( rc > 1 )                           
    		rc = ( tidyOptSetBool(tdoc, TidyForceOutput, yes) ? rc : -1 );
  	if ( rc >= 0 )
    		rc = tidySaveBuffer(tdoc, &output);


  	if ( rc >= 0 )
  	{
		if (verbose)
		{
			printf("\nDiagnostics:\n\n%s", errbuf.bp );
		}

		outFile.write((char*)output.bp, output.size);
  	}   
  	else
		if (verbose)
		{
			printf("A severe error (%d) occurred.\n", rc );
		}

  	tidyBufFree(&output );
  	tidyBufFree(&errbuf );
  	tidyRelease(tdoc );


  	//Close file
  	inputFile.close();
  	outFile.close();

  	//For future error handling implementation
  	//return rc;

  	return;
}