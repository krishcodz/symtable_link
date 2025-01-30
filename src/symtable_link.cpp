#include "SymTable.h"
#include <cstdlib>

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

int mystrcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

SymTable_t SymTable_new(void)
{
    SymTable_t table = new SymTable();
    if (!table)
        return nullptr;
    table->root = nullptr;
    table->len = 0;
    return table;
}

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

int SymTable_getLength(SymTable_t oSymTable)
{
    return oSymTable ? oSymTable->len : 0;
}

int SymTable_put(SymTable_t oSymTable, const char *pcKey, const void *pvValue)
{
    if (!oSymTable || !pcKey)
        return 0;

    Node *current = oSymTable->root;
    while (current)
    {
        if (mystrcmp(current->key, pcKey) == 0)
            return 0;
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
