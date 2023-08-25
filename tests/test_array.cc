#include <gtest/gtest.h>

#include <array>

#include "../containersplus.h"

TEST(array_test, constr1) {
  jen::array<int, 50> arr1;
  std::array<int, 50> arr2;
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr1.max_size(), arr2.max_size());
}

TEST(array_test, constr2) {
  jen::array<int, 11> arr1 = {11, 22, 33, 44, 55, 66, 77, 88, 99, 100, 111};
  std::array<int, 11> arr2 = {11, 22, 33, 44, 55, 66, 77, 88, 99, 100, 111};
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr1.max_size(), arr2.max_size());
  for (int i = 0; i < 11; i++) EXPECT_EQ(arr1.at(i), arr2.at(i));
}

TEST(array_test, constr3) {
  jen::array<int, 9> arr1 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  std::array<int, 9> arr2 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr1.max_size(), arr2.max_size());
  for (int i = 0; i < 9; i++) EXPECT_EQ(arr1.at(i), arr2.at(i));
}

TEST(array_test, constr5) {
  jen::array<int, 4> arr1 = {4, 6, 8, 10};
  std::array<int, 4> arr2 = {4, 6, 8, 10};
  auto arr11 = std::move(arr1);
  auto arr22 = std::move(arr2);
  auto it1 = arr11.begin();
  for (auto it2 = arr22.begin(); it2 != arr22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr11.size(), arr22.size());
}

TEST(array_test, constr6) {
  jen::array<int, 9> arr1 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  std::array<int, 9> arr2 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  auto arr11 = arr1;
  auto arr22 = arr2;
  auto it1 = arr11.begin();
  for (auto it2 = arr22.begin(); it2 != arr22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr11.size(), arr22.size());
}

TEST(array_test, constr7) {
  jen::array<int, 4> arr1 = {4, 6, 8, 10};
  std::array<int, 4> arr2 = {4, 6, 8, 10};
  jen::array<int, 4> arr11;
  std::array<int, 4> arr22;
  arr11 = std::move(arr1);
  arr22 = std::move(arr2);
  auto it1 = arr11.begin();
  for (auto it2 = arr22.begin(); it2 != arr22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr11.size(), arr22.size());
}

TEST(array_test, at1) {
  jen::array<int, 9> arr1 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  std::array<int, 9> arr2 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  for (int i = 0; i < 9; i++) EXPECT_EQ(arr1.at(i), arr2.at(i));
}

TEST(array_test, operator1) {
  jen::array<int, 9> arr1 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  std::array<int, 9> arr2 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  for (int i = 0; i < 9; i++) EXPECT_EQ(arr1[i], arr2[i]);
}

TEST(array_test, front1) {
  jen::array<int, 9> arr1 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  std::array<int, 9> arr2 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  EXPECT_EQ(arr1.front(), arr2.front());
}

TEST(array_test, back1) {
  jen::array<int, 9> arr1 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  std::array<int, 9> arr2 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  EXPECT_EQ(arr1.back(), arr2.back());
}

TEST(array_test, data1) {
  jen::array<int, 9> arr1 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  std::array<int, 9> arr2 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  EXPECT_EQ(*(arr1.data()), *(arr2.data()));
}

TEST(array_test, data2) { jen::array<int, 10> arr1; }

TEST(array_test, begin1) {
  jen::array<int, 9> arr1 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  std::array<int, 9> arr2 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  auto it1 = arr1.begin();
  auto it2 = arr2.begin();
  EXPECT_EQ(*it1, *it2);
}

TEST(array_test, end1) {
  jen::array<int, 9> arr1 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  std::array<int, 9> arr2 = {9, 8, 7, 6, 5, 4, 3, 2, 1};

  auto it1 = arr1.end();
  auto it2 = arr2.end();
  it1--, it2--;
  EXPECT_EQ(*it2, *it1);
}

TEST(array_test, empty1) {
  jen::array<int, 9> arr1 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  std::array<int, 9> arr2 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  EXPECT_EQ(arr1.empty(), arr2.empty());
}

TEST(array_test, empty2) {
  jen::array<int, 50> arr1;
  std::array<int, 50> arr2;
  EXPECT_EQ(arr1.empty(), arr2.empty());
}

TEST(array_test, size1) {
  jen::array<int, 99> arr1;
  std::array<int, 99> arr2;
  EXPECT_EQ(arr1.size(), arr2.size());
}

TEST(array_test, size2) {
  jen::array<int, 11> arr1 = {11, 22, 33, 44, 55, 66, 77, 88, 99, 100, 111};
  std::array<int, 11> arr2 = {11, 22, 33, 44, 55, 66, 77, 88, 99, 100, 111};
  EXPECT_EQ(arr1.size(), arr2.size());
}

TEST(array_test, max_size1) {
  jen::array<int, 11> arr1 = {11, 22, 33, 44, 55, 66, 77, 88, 99, 100, 111};
  std::array<int, 11> arr2 = {11, 22, 33, 44, 55, 66, 77, 88, 99, 100, 111};
  EXPECT_EQ(arr1.max_size(), arr2.max_size());
}

TEST(array_test, max_size2) {
  jen::array<int, 11> arr1 = {11, 22, 33, 44, 55, 66, 77, 88, 99, 100, 111};
  std::array<int, 11> arr2 = {11, 22, 33, 44, 55, 66, 77, 88, 99, 100, 111};
  EXPECT_EQ(arr1.max_size(), arr2.max_size());
}

TEST(array_test, swap1) {
  jen::array<int, 11> arr1 = {11, 22, 33, 44, 55, 66, 77, 88, 99, 100, 111};
  std::array<int, 11> arr2 = {11, 22, 33, 44, 55, 66, 77, 88, 99, 100, 111};
  jen::array<int, 11> arr11;
  std::array<int, 11> arr22;
  arr1.swap(arr11);
  arr2.swap(arr22);
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr11.size(), arr22.size());
  auto it1 = arr11.begin();
  for (auto it2 = arr22.begin(); it2 != arr22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(array_test, swap2) {
  jen::array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  jen::array<int, 10> arr11 = {389, 3829, 111, 189, 11};
  std::array<int, 10> arr22 = {389, 3829, 111, 189, 11};
  arr1.swap(arr11);
  arr2.swap(arr22);
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr11.size(), arr22.size());
  auto it1 = arr11.begin();
  for (auto it2 = arr22.begin(); it2 != arr22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(array_test, swap3) {
  jen::array<int, 11> arr1 = {11, 22, 33, 44, 55, 66, 77, 88, 99, 100, 111};
  std::array<int, 11> arr2 = {11, 22, 33, 44, 55, 66, 77, 88, 99, 100, 111};
  jen::array<int, 11> arr11;
  std::array<int, 11> arr22;
  arr1.swap(arr11);
  arr2.swap(arr22);
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr11.size(), arr22.size());
  auto it1 = arr11.begin();
  for (auto it2 = arr22.begin(); it2 != arr22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(array_test, iter1) {
  jen::array<int, 11> arr1 = {11, 22, 33, 44, 55, 66, 77, 88, 99, 100, 111};
  std::array<int, 11> arr2 = {11, 22, 33, 44, 55, 66, 77, 88, 99, 100, 111};
  auto it1 = arr1.begin();
  auto it2 = arr2.begin();
  for (int i = 0; i < 4; i++) ++it1, ++it2;
  EXPECT_EQ(*it1, *it2);
}

TEST(array_test, iter2) {
  jen::array<int, 11> arr1 = {11, 22, 33, 44, 55, 66, 77, 88, 99, 100, 111};
  std::array<int, 11> arr2 = {11, 22, 33, 44, 55, 66, 77, 88, 99, 100, 111};
  auto it1 = arr1.end();
  auto it2 = arr2.end();
  for (int i = 0; i < 3; i++) --it1, --it2;
  EXPECT_EQ(*it1, *it2);
}

TEST(array_test, iter3) {
  jen::array<int, 11> arr1 = {11, 22, 33, 44, 55, 66, 77, 88, 99, 100, 111};
  auto it1 = arr1.end();
  auto it2 = arr1.end();
  EXPECT_EQ(it1 == it2, true);
}

TEST(array_test, iter4) {
  jen::array<int, 11> arr1 = {11, 22, 33, 44, 55, 66, 77, 88, 99, 100, 111};
  auto it1 = arr1.end();
  auto it2 = arr1.end();
  EXPECT_EQ(it1 != it2, false);
}

TEST(array_test, iter5) {
  jen::array<int, 11> arr1 = {11, 22, 33, 44, 55, 66, 77, 88, 99, 100, 111};
  auto it1 = arr1.end();
  auto it2 = arr1.end();
  ++it2;
  EXPECT_EQ(it1 == it2, false);
}
