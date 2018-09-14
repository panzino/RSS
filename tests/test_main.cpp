#include "http.h"
#include "parser.h"
#include "readops.h"
#include "fixer.h"
#include "test.h"
#include <iostream>

using namespace std;

int main()
{
    test_readops();
    test_parser();
    test_http();

    return 0;
}