#include <gtest/gtest.h>
#include <list>
#include "../src/string_map.h"

TEST(string_map_test, test_construct) {
    string_map<int> m1,m2;
    string_map<int> m3(m1);
    string_map<string_map<string> > m4;
}

TEST(string_map_test, test_define) {
    string_map<int> m1;
    EXPECT_EQ(m1.size(),0);
    EXPECT_TRUE(m1.empty());
    m1.insert(pair<string, int>("hello", 1));
    EXPECT_EQ(m1.size(),1);
    EXPECT_FALSE(m1.empty());
    m1.insert(pair<string, int>("world", 5));
    auto falsy = m1.insert(pair<string, int>("world", 7));
    EXPECT_EQ(m1.at("hello"),1);
    EXPECT_EQ(m1.at("world"),5);
    EXPECT_EQ(falsy.second,false);
    EXPECT_TRUE(m1.count("hello"));
    EXPECT_TRUE(m1.count("world"));
    EXPECT_FALSE(m1.count("he"));
    EXPECT_FALSE(m1.count("worldwide"));
    m1.at("world") = 3;
    EXPECT_EQ(m1.at("world"),3);
    m1["world"] = 4;
    EXPECT_EQ(m1.at("world"),4);
    m1["goodbye"] = 7;
    EXPECT_EQ(m1.at("goodbye"),7);
}

TEST(string_map_test, test_compare) {
    string_map<int> m1,m2;
    EXPECT_TRUE(m1==m2);
    m1["hello"] = 123;
    m1["world"] = 456;
    EXPECT_FALSE(m1==m2);
    m2["hello"] = 123;
    m2["world"] = 456;
    EXPECT_TRUE(m1==m2);
    m2["world"] = 45;
    EXPECT_FALSE(m1==m2);
}

