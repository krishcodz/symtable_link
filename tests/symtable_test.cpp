#include <gtest/gtest.h>
#include "SymTable.h"
#include <iostream>
#include <cstring>

void sumValues(const char *pcKey, const void *pvValue, void *pvExtra)
{
    (*(int *)pvExtra) += (intptr_t)pvValue;
}

TEST(SymTableTest, Creation)
{
    SymTable_t table = SymTable_new();
    ASSERT_NE(table, nullptr);
    ASSERT_EQ(SymTable_getLength(table), 0);
    SymTable_free(table);
}

TEST(SymTableTest, EmptyTableOperations)
{
    SymTable_t table = SymTable_new();
    ASSERT_EQ(SymTable_get(table, "nonexistent"), nullptr);
    ASSERT_EQ(SymTable_remove(table, "nonexistent"), nullptr);
    ASSERT_EQ(SymTable_replace(table, "nonexistent", "value"), nullptr);
    ASSERT_EQ(SymTable_contains(table, "nonexistent"), 0);
    SymTable_free(table);
}

TEST(SymTableTest, Put)
{
    SymTable_t table = SymTable_new();
    ASSERT_EQ(SymTable_put(table, "key1", "value1"), 1);
    ASSERT_EQ(SymTable_put(table, "key1", "value2"), 0);
    ASSERT_EQ(SymTable_getLength(table), 1);
    ASSERT_STREQ((char *)SymTable_get(table, "key1"), "value1");
    SymTable_free(table);
}

TEST(SymTableTest, PutMultipleKeys)
{
    SymTable_t table = SymTable_new();
    ASSERT_EQ(SymTable_put(table, "key1", "value1"), 1);
    ASSERT_EQ(SymTable_put(table, "key2", "value2"), 1);
    ASSERT_EQ(SymTable_put(table, "key3", "value3"), 1);
    ASSERT_EQ(SymTable_getLength(table), 3);
    ASSERT_STREQ((char *)SymTable_get(table, "key2"), "value2");
    SymTable_free(table);
}

TEST(SymTableTest, Replace)
{
    SymTable_t table = SymTable_new();
    SymTable_put(table, "key1", "value1");
    void *oldValue = SymTable_replace(table, "key1", "newValue1");
    ASSERT_STREQ((char *)oldValue, "value1");
    ASSERT_STREQ((char *)SymTable_get(table, "key1"), "newValue1");
    SymTable_free(table);
}

TEST(SymTableTest, Contains)
{
    SymTable_t table = SymTable_new();
    SymTable_put(table, "key1", "value1");
    ASSERT_EQ(SymTable_contains(table, "key1"), 1);
    ASSERT_EQ(SymTable_contains(table, "key2"), 0);
    SymTable_free(table);
}

TEST(SymTableTest, Get)
{
    SymTable_t table = SymTable_new();
    SymTable_put(table, "key1", "value1");
    ASSERT_STREQ((char *)SymTable_get(table, "key1"), "value1");
    ASSERT_EQ(SymTable_get(table, "key2"), nullptr);
    SymTable_free(table);
}

TEST(SymTableTest, Remove)
{
    SymTable_t table = SymTable_new();
    SymTable_put(table, "key1", "value1");
    void *removedValue = SymTable_remove(table, "key1");
    ASSERT_STREQ((char *)removedValue, "value1");
    ASSERT_EQ(SymTable_contains(table, "key1"), 0);
    ASSERT_EQ(SymTable_getLength(table), 0);
    SymTable_free(table);
}

TEST(SymTableTest, RemoveNonExistent)
{
    SymTable_t table = SymTable_new();
    ASSERT_EQ(SymTable_remove(table, "key1"), nullptr);
    SymTable_free(table);
}

TEST(SymTableTest, Free)
{
    SymTable_t table = SymTable_new();
    SymTable_put(table, "key1", "value1");
    SymTable_put(table, "key2", "value2");
    SymTable_free(table);
}

TEST(SymTableTest, NullKeyHandling)
{
    SymTable_t table = SymTable_new();
    ASSERT_EQ(SymTable_put(table, nullptr, "value"), 0);
    ASSERT_EQ(SymTable_contains(table, nullptr), 0);
    ASSERT_EQ(SymTable_get(table, nullptr), nullptr);
    ASSERT_EQ(SymTable_remove(table, nullptr), nullptr);
    SymTable_free(table);
}

TEST(SymTableTest, NullValueHandling)
{
    SymTable_t table = SymTable_new();
    ASSERT_EQ(SymTable_put(table, "key1", nullptr), 1);
    ASSERT_EQ(SymTable_contains(table, "key1"), 1);
    ASSERT_EQ(SymTable_get(table, "key1"), nullptr);
    void *oldValue = SymTable_replace(table, "key1", "newValue");
    ASSERT_EQ(oldValue, nullptr);
    SymTable_free(table);
}

TEST(SymTableTest, Map)
{
    SymTable_t table = SymTable_new();
    ASSERT_NE(table, nullptr);

    SymTable_put(table, "key1", (void *)10);
    SymTable_put(table, "key2", (void *)20);
    SymTable_put(table, "key3", (void *)30);

    int sum = 0;
    SymTable_map(table, sumValues, &sum);

    ASSERT_EQ(sum, 60);

    SymTable_free(table);
}

TEST(SymTableTest, MapEmptyTable)
{
    SymTable_t table = SymTable_new();
    int count = 0;
    SymTable_map(table, sumValues, &count);
    ASSERT_EQ(count, 0);
    SymTable_free(table);
}

TEST(SymTableTest, MultipleOperations)
{
    SymTable_t table = SymTable_new();
    ASSERT_EQ(SymTable_put(table, "A", "1"), 1);
    ASSERT_EQ(SymTable_put(table, "B", "2"), 1);
    ASSERT_EQ(SymTable_put(table, "C", "3"), 1);
    ASSERT_EQ(SymTable_getLength(table), 3);

    ASSERT_EQ(SymTable_contains(table, "A"), 1);
    ASSERT_STREQ((char *)SymTable_get(table, "A"), "1");

    ASSERT_EQ(SymTable_remove(table, "B"), (void *)"2");
    ASSERT_EQ(SymTable_contains(table, "B"), 0);
    ASSERT_EQ(SymTable_getLength(table), 2);

    ASSERT_EQ(SymTable_replace(table, "C", "NewC"), (void *)"3");
    ASSERT_STREQ((char *)SymTable_get(table, "C"), "NewC");

    SymTable_free(table);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
