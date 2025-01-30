#include <iostream>
#include "SymTable.h"
using namespace std;

int main()
{
    SymTable_t symTable = SymTable_new();

    if (!symTable)
    {
        cout << "SymTable creation failed." << endl;
        return 1;
    }

    cout << "SymTable length: " << symTable->len << endl;

    delete symTable;
    return 0;
}
