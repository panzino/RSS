#include "fixer.h"
#include <tidy.h>
#include <tidybuffio.h>
#include <stdio.h>
#include <errno.h>
#include <fstream>
#include <string>


void fixFormatting(const char* extension, bool verbose)
{
	char fullFileName[FILENAME_MAX] = "../responses/output.";
    strcat (fullFileName, extension);

	std::ifstream inputFile (fullFileName);
	std::string inputString;

	inputFile.seekg(0, std::ios::end);   
	inputString.reserve(inputFile.tellg());
	inputFile.seekg(0, std::ios::beg);

	inputString.assign((std::istreambuf_iterator<char>(inputFile)),
            	std::istreambuf_iterator<char>());


	const char* input = inputString.c_str();
	TidyBuffer output = {0};
	TidyBuffer errbuf = {0};
	int rc = -1;
	bool ok;

	//Open file stream
	FILE* ofile;
	ofile = fopen (fullFileName, "w");


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

    if (verbose)
    {
	  	if ( rc >= 0 )
	  	{
	    		if ( rc > 0 )
	      			printf("\nDiagnostics:\n\n%s", errbuf.bp );
	    			fprintf(ofile, "\nAnd here is the result:\n\n%s", output.bp );
	  	}
	  	else
	    		printf("A severe error (%d) occurred.\n", rc );
	}

  	tidyBufFree(&output );
  	tidyBufFree(&errbuf );
  	tidyRelease(tdoc );

  	//For future error handling implementation
  	//return rc;

  	return;
}