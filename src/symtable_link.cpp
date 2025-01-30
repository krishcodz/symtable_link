#include "SymTable.h"

SymTable_t SymTable_new(void)
{
    SymTable_t table = new SymTable;
    if (!table)
        return nullptr;
    table->root = nullptr;
    table->len = 0;
    return table;
}

void SymTable_free(SymTable_t oSymTable)
{
    delete (oSymTable);
}

int SymTable_getLength(SymTable_t oSymTable)
{
    return oSymTable->len;
}

int SymTable_put(SymTable_t oSymTable,
                 const char *pcKey,
                 const void *pvValue)
{

    if (oSymTable == nullptr)
        return 0;

    Node *newNode = new Node;
    newNode->key = pcKey;
    newNode->value = pvValue;
    newNode->next = nullptr;

    if (oSymTable->root == nullptr)
    {
        oSymTable->root = newNode;
        oSymTable->len++;
        return 1;
    }

    Node *current = oSymTable->root;
    while (current->next != nullptr)
    {
        current = current->next;
    }

    current->next = newNode;
    oSymTable->len++;
    return 1;
}

void *SymTable_replace(SymTable_t oSymTable,
                       const char *pcKey,
                       const void *pvValue)
{

    if (oSymTable == nullptr)
        return nullptr;

    Node *current = oSymTable->root;

    while (current != nullptr)
    {
        const char *s1 = current->key;
        const char *s2 = pcKey;

        while (*s1 && *s2 && (*s1 == *s2))
        {
            s1++;
            s2++;
        }

        if (*s1 == *s2)
        {
            void *oldValue = (void *)current->value;
            current->value = pvValue;
            return oldValue;
        }

        current = current->next;
    }

    return nullptr;
}
