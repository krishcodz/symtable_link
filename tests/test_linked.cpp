#include <gtest/gtest.h>
#include "SymTable.h"

TEST(SymTableTest, Creation)
{
    SymTable_t table = SymTable_new();
    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->len, 0);
}
