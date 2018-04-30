#include <gtest/gtest.h>
#include <list>
#include "../src/stringmap.h"

TEST(stringmap_test, test_construct) {
    stringmap<int> m1,m2;
    stringmap<int> m3(m1);
    stringmap<stringmap<string> > m4;
}

TEST(stringmap_test, test_define) {
    stringmap<int> m1;
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

TEST(stringmap_test, test_compare) {
    stringmap<int> m1,m2;
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

TEST(stringmap_test, test_erase) {
    stringmap<int> m1;
    EXPECT_TRUE(m1.empty());
    m1["hello"] = 123;
    EXPECT_TRUE(m1.count("hello"));
    m1.erase("hello");
    EXPECT_FALSE(m1.count("hello"));
    EXPECT_FALSE(m1.count("he"));
    m1["hello"] = 1;
    m1["he"] = 3;
    EXPECT_TRUE(m1.count("hello"));
    EXPECT_TRUE(m1.count("he"));
    m1.erase("he");
    EXPECT_TRUE(m1.count("hello"));
    EXPECT_FALSE(m1.empty());
    m1.erase("hello");
    EXPECT_FALSE(m1.count("hello"));
    EXPECT_TRUE(m1.empty());
}

TEST(stringmap_test, test_clear) {
    stringmap<int> m1;
    m1["hello"] = 1;
    m1["he"] = 3;
    EXPECT_TRUE(m1.count("hello"));
    EXPECT_TRUE(m1.count("he"));
    EXPECT_FALSE(m1.empty());
    m1.clear();
    EXPECT_FALSE(m1.count("hello"));
    EXPECT_FALSE(m1.count("he"));
    EXPECT_TRUE(m1.empty());
}

TEST(stringmap_test, test_iterator) {
    stringmap<int> m1;

    m1["world"] = 2;
    m1["aaaa"] = 0;
    m1["hello"] = 1;
    /**
     * m1:  .-a-a-a-a[0]
     *      |-h-e-l-l-o[1]
     *      \-w-o-r-l-d[2]
     */
    std::list<int> l1, l2 = {0,1,2};
    for (auto p : m1)
        l1.push_back(p.second);
    EXPECT_EQ(l1,l2);


    m1["aaaab"] = 12;
    m1["aaaba"] = 24;
    m1["aabba"] = 48;

    /**
     * m1:  .-a-a-a-a[0]-b[12]
     *      |    | \b-a[24]
     *      |    \b-b-a[48]
     *      |-h-e-l-l-o[1]
     *      \-w-o-r-l-d[2]
     */

    std::list<int> l3, l4 = {0,12,24,48,1,2};
    for (auto p : m1)
        l3.push_back(p.second);
    EXPECT_EQ(l3,l4);


    std::list<int> l5;
    auto it2 = m1.end();
    --it2;
    for (it2 ; it2 != m1.begin(); --it2){
        int e = it2->second;
        l5.push_back(e);
    }
    l5.push_back(m1.begin()->second);
    l5.reverse();
    EXPECT_EQ(l4,l5);

    EXPECT_EQ(m1.erase("aaaa"), 1);

    /**
     * m1:  .-a-a-a-a-b[12]
     *      |    | \b-a[24]
     *      |    \b-b-a[48]
     *      |-h-e-l-l-o[1]
     *      \-w-o-r-l-d[2]
     */

    auto it = m1.find("aaaab");
    it = m1.erase(it);

    /**
     * m1:  .-a-a-a-b-a[24]
     *      |    \b-b-a[48]
     *      |-h-e-l-l-o[1]
     *      \-w-o-r-l-d[2]
     */

    EXPECT_EQ(it->first, "aaaba");
    EXPECT_EQ(it->second, 24);

    it = m1.find("aabba");
    it = m1.erase(it);

    /**
     * m1:  .-a-a-a-b-a[24]
     *      |-h-e-l-l-o[1]
     *      \-w-o-r-l-d[2]
     */
    EXPECT_EQ(it, m1.find("hello"));

    EXPECT_EQ(m1.erase(m1.find("world")), m1.end());

    /**
     * m1:  .-a-a-a-b-a[24]
     *      \-h-e-l-l-o[1]
     */

    std::list<int> l6, l7 = {24,1};
    for (auto p : m1)
        l6.push_back(p.second);
    EXPECT_EQ(l6,l7);
}

