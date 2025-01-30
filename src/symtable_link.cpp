#include "SymTable.h"

struct Node
{
    char *key;
    void *value;
    Node *next;
};

SymTable_t SymTable_new(void)
{
    SymTable_t table = new SymTable;
    if (!table)
        return nullptr;
    table->root = nullptr;
    table->len = 0;
    return table;
}
