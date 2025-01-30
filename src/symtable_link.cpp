#include "SymTable.h"
#include <cstdlib>

// Node structure to store key-value pairs
struct Node
{
    const char *key;
    const void *value;
    Node *next;
};

// Symbol Table structure
struct SymTable
{
    struct Node *root;
    int len;
};

// Duplicates a string
char *mystrdup(const char *s)
{
    int len = 0;
    while (s[len] != '\0')
        len++;

    char *copy = (char *)malloc(len + 1);
    if (!copy)
        return nullptr;

    for (int i = 0; i <= len; i++)
        copy[i] = s[i];

    return copy;
}

// Compares two strings
int mystrcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

// Creates a new symbol table
SymTable_t SymTable_new(void)
{
    SymTable_t table = new SymTable();
    if (!table)
        return nullptr;
    table->root = nullptr;
    table->len = 0;
    return table;
}

// Frees the symbol table
void SymTable_free(SymTable_t oSymTable)
{
    if (!oSymTable)
        return;

    Node *current = oSymTable->root;
    while (current != nullptr)
    {
        Node *tmp = current;
        current = current->next;
        free((void *)tmp->key);
        delete (tmp);
    }

    delete (oSymTable);
}

// Returns the number of elements in the table
int SymTable_getLength(SymTable_t oSymTable)
{
    return oSymTable ? oSymTable->len : 0;
}

// Adds a new key-value pair
int SymTable_put(SymTable_t oSymTable, const char *pcKey, const void *pvValue)
{
    if (!oSymTable || !pcKey)
        return 0;

    Node *current = oSymTable->root;
    while (current)
    {
        if (mystrcmp(current->key, pcKey) == 0)
            return 0; // Key already exists
        current = current->next;
    }

    Node *newNode = new Node;
    if (!newNode)
        return 0;

    newNode->key = mystrdup(pcKey);
    if (!newNode->key)
    {
        delete newNode;
        return 0;
    }

    newNode->value = pvValue;
    newNode->next = oSymTable->root;
    oSymTable->root = newNode;

    oSymTable->len++;
    return 1;
}

// Replaces a value for an existing key
void *SymTable_replace(SymTable_t oSymTable, const char *pcKey, const void *pvValue)
{
    if (!oSymTable || !pcKey)
        return nullptr;

    Node *current = oSymTable->root;
    while (current)
    {
        if (mystrcmp(current->key, pcKey) == 0)
        {
            void *oldValue = (void *)current->value;
            current->value = pvValue;
            return oldValue;
        }
        current = current->next;
    }

    return nullptr;
}

// Checks if a key exists in the table
int SymTable_contains(SymTable_t oSymTable, const char *pcKey)
{
    if (!oSymTable || !pcKey)
        return 0;

    Node *current = oSymTable->root;
    while (current)
    {
        if (mystrcmp(current->key, pcKey) == 0)
            return 1;
        current = current->next;
    }

    return 0;
}

// Gets the value of a key
void *SymTable_get(SymTable_t oSymTable, const char *pcKey)
{
    if (!oSymTable || !pcKey)
        return nullptr;

    Node *current = oSymTable->root;
    while (current)
    {
        if (mystrcmp(current->key, pcKey) == 0)
            return (void *)current->value;
        current = current->next;
    }

    return nullptr;
}

// Removes a key-value pair
void *SymTable_remove(SymTable_t oSymTable, const char *pcKey)
{
    if (!oSymTable || !pcKey)
        return nullptr;

    Node *current = oSymTable->root;
    Node *prev = nullptr;

    while (current)
    {
        if (mystrcmp(current->key, pcKey) == 0)
        {
            void *oldValue = (void *)current->value;

            if (prev)
                prev->next = current->next;
            else
                oSymTable->root = current->next;

            free((void *)current->key);
            delete current;
            oSymTable->len--;
            return oldValue;
        }

        prev = current;
        current = current->next;
    }

    return nullptr;
}

// Applies a function to each key-value pair
void SymTable_map(SymTable_t oSymTable,
                  void (*pfApply)(const char *pcKey,
                                  const void *pvValue, void *pvExtra),
                  const void *pvExtra)
{
    if (!oSymTable || !pfApply)
        return;

    Node *current = oSymTable->root;

    while (current)
    {
        pfApply(current->key, current->value, (void *)pvExtra);
        current = current->next;
    }
}
