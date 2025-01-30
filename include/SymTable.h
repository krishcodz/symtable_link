#pragma once

struct Node;
struct SymTable
{
    struct Node *root;
    int len;
};

typedef struct SymTable *SymTable_t;

SymTable_t SymTable_new(void);