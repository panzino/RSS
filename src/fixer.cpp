//This file is only needed for an XML parser
//The trivial string parser can work without this

#include "fixer.h"
#include <tidy.h>
#include <tidybuffio.h>
#include <stdio.h>
#include <errno.h>
#include <fstream>
#include <string>
#include <iostream>

void fixFormatting(bool verbose)
{
	
	//I decided to use fstream because I might as well use the C++ methods
	const char* input = "../responses/GET_Response.txt";
	const char* output = "../responses/output.xml";

	if (verbose)
	{
		TidyBuffer errbuf = {0};
		short rc = -1;
		bool ok;

		//Init doc
		TidyDoc tdoc = tidyCreate();
		
		//Conver to XML
		ok = tidyOptSetBool(tdoc, TidyXhtmlOut, yes);
		ok = tidyOptSetBool(tdoc, TidyForceOutput, yes);

		//Error handling
		//Parse and Clean File
		if (ok)
			rc = tidySetErrorBuffer(tdoc, &errbuf);
		if (rc >= 0)
			rc = tidyParseFile(tdoc, input);
		if (rc >= 0)
			rc = tidyCleanAndRepair(tdoc);
		if (rc >= 0)
	   	 	rc = tidyRunDiagnostics(tdoc);
	  	if ( rc > 1 )                           
	    	rc = ( tidyOptSetBool(tdoc, TidyForceOutput, yes) ? rc : -1);
	  	if ( rc >= 0 )
	    	rc = tidySaveFile(tdoc, output);

	    if (rc >= 0)
	    	printf("\nDiagnostics:\n\n%s", errbuf.bp);
	    else
	    	printf("A severe error (%d) occurred.\n", rc);

	  	tidyBufFree(&errbuf);
	  	tidyRelease(tdoc);

	}

	else
	{
		TidyBuffer errbuf = {0};
		short rc = -1;
		bool ok;

		//Init doc
		TidyDoc tdoc = tidyCreate();
		
		//Conver to XML
		ok = tidyOptSetBool(tdoc, TidyXhtmlOut, yes);

		//Error handling
		//Parse and Clean File
		if (ok)
			rc = tidySetErrorBuffer(tdoc, &errbuf);
		if (rc >= 0)
			rc = tidyParseFile(tdoc, input);
		if (rc >= 0)
			rc = tidyCleanAndRepair(tdoc);
	  	if ( rc > 1 )                           
	    	rc = ( tidyOptSetBool(tdoc, TidyForceOutput, yes) ? rc : -1);
	  	if ( rc >= 0 )
	    	rc = tidySaveFile(tdoc, output);

	  	tidyBufFree(&errbuf);
	  	tidyRelease(tdoc);
	}

  	return;
}
