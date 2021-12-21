#include "pch.h"
#include "../Task2_new/HashMap.h"
#include <string>

using namespace std;
//#include "HashMap.h"

TEST(Functions, SizeTest) {
	HashMap<int, std::string> map;
	EXPECT_EQ(map.size(), 0);
	map.insert(make_pair(1, "size_test"));
	EXPECT_EQ(map.size(), 1);
}

TEST(Functions, OperatorEqualTest) {
	HashMap<int, std::string> map;
	for (int i = 0; i < 10; i++) {
		map.insert(make_pair(i, "AAAA "));
	}
	EXPECT_EQ(map.size(), 10);
	HashMap<int,std::string> map2;
	map2 = map;
	EXPECT_EQ(map2.size(), 10);
}

TEST(Functions, OperatorBracketsTest)
{
	HashMap<int, std::string> map;
	for (int i = 0; i < 10; i++) {
		map.insert(make_pair(i, "AAA"));
	}
	EXPECT_EQ(map[0], "AAA");
	map[0] = "BBB";
	EXPECT_EQ(map[0], "BBB");
}

TEST(Functions, SwapTest)
{
	HashMap<int, char> map;
	map.insert(make_pair(1, 'a'));
	HashMap<int, char> map2;
	map2.insert(make_pair(1, 'a'));
	map2.insert(make_pair(3, 'a'));

	map.swap(map2);
	EXPECT_EQ(map.size(), 2);
	EXPECT_EQ(map2.size(), 1);
}

TEST(Functions, EmptyTest)
{
	HashMap<int, char> map;
	bool empty_ = map.empty();
	EXPECT_EQ(empty_, true);
	map.insert(make_pair(1, 'a'));
	empty_ = map.empty();
	EXPECT_EQ(empty_, false);
}

TEST(Functions, ClearTest)
{
	HashMap<int, char> map2;
	map2.insert(make_pair(1, 'a'));
	map2.insert(make_pair(3, 'a'));
	map2.clear();
	bool empty_ = map2.empty();
	EXPECT_EQ(empty_, true);
}



