#include "http.h"
#include "parser.h"
#include "readops.h"
#include "test.h"
#include <iostream>

using namespace std;

int main()
{
    //STANDARD IOSTREAM SPEED UP
    ios_base::sync_with_stdio (false);

    test_readops();
    test_parser();
    test_http();

    return 0;
}