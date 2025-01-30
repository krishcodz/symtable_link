#pragma once

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

int SymTable_contains(SymTable_t oSymTable,
                      const char *pcKey);

void *SymTable_get(SymTable_t oSymTable, const char *pcKey);

void *SymTable_remove(SymTable_t oSymTable,
                      const char *pcKey);

void SymTable_map(SymTable_t oSymTable,
                  void (*pfApply)(const char *pcKey,
                                  const void *pvValue, void *pvExtra),
                  const void *pvExtra);