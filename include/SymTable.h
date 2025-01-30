#pragma once

struct Node
{
    const char *key;
    const void *value;
    Node *next;
};

struct SymTable
{
    struct Node *root;
    int len;
};

typedef struct SymTable *SymTable_t;

SymTable_t SymTable_new(void);

void SymTable_free(SymTable_t oSymTable);

int SymTable_getLength(SymTable_t oSymTable);

int SymTable_put(SymTable_t oSymTable,
                 const char *pcKey,
                 const void *pvValue);

void *SymTable_replace(SymTable_t oSymTable,
                       const char *pcKey,
                       const void *pvValue);