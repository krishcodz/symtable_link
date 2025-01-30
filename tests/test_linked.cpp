#include <gtest/gtest.h>
#include "SymTable.h"

TEST(SymTableTest, Creation)
{
    SymTable_t table = SymTable_new();
    ASSERT_NE(table, nullptr);
    ASSERT_EQ(SymTable_getLength(table), 0);
    SymTable_free(table);
}

TEST(SymTableTest, Put)
{
    SymTable_t table = SymTable_new();
    ASSERT_NE(table, nullptr);
    ASSERT_EQ(SymTable_put(table, "key1", "value1"), 1);
    ASSERT_EQ(SymTable_put(table, "key1", "value2"), 0);
    ASSERT_EQ(SymTable_getLength(table), 1);
    SymTable_free(table);
}

TEST(SymTableTest, Replace)
{
    SymTable_t table = SymTable_new();
    ASSERT_NE(table, nullptr);
    SymTable_put(table, "key1", "value1");
    void *oldValue = SymTable_replace(table, "key1", "newValue1");
    ASSERT_STREQ((char *)oldValue, "value1");
    ASSERT_STREQ((char *)SymTable_get(table, "key1"), "newValue1");
    SymTable_free(table);
}

TEST(SymTableTest, Contains)
{
    SymTable_t table = SymTable_new();
    ASSERT_NE(table, nullptr);
    SymTable_put(table, "key1", "value1");
    ASSERT_EQ(SymTable_contains(table, "key1"), 1);
    ASSERT_EQ(SymTable_contains(table, "key2"), 0);
    SymTable_free(table);
}

TEST(SymTableTest, Get)
{
    SymTable_t table = SymTable_new();
    ASSERT_NE(table, nullptr);
    SymTable_put(table, "key1", "value1");
    ASSERT_STREQ((char *)SymTable_get(table, "key1"), "value1");
    ASSERT_EQ(SymTable_get(table, "key2"), nullptr);
    SymTable_free(table);
}

TEST(SymTableTest, Remove)
{
    SymTable_t table = SymTable_new();
    ASSERT_NE(table, nullptr);
    SymTable_put(table, "key1", "value1");
    void *removedValue = SymTable_remove(table, "key1");
    ASSERT_STREQ((char *)removedValue, "value1");
    ASSERT_EQ(SymTable_contains(table, "key1"), 0);
    ASSERT_EQ(SymTable_getLength(table), 0);
    SymTable_free(table);
}

TEST(SymTableTest, Free)
{
    SymTable_t table = SymTable_new();
    ASSERT_NE(table, nullptr);
    SymTable_put(table, "key1", "value1");
    SymTable_put(table, "key2", "value2");
    SymTable_free(table);
}
