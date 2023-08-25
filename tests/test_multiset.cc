#include <gtest/gtest.h>

#include <set>

#include "../containersplus.h"

TEST(Multiset, 1) {
  jen::multiset<double> v = {-7, 10, -55, 742, 92, -76, 38, 220, 11, 11, 210};
  std::multiset<double> vc = {-7, 10, -55, 742, 92, -76, 38, 220, 11, 11, 210};

  ASSERT_EQ(*v.begin(), *vc.begin());
  ASSERT_EQ(v.empty(), vc.empty());
  ASSERT_EQ(v.size(), vc.size());
}

TEST(Multiset, 2) {
  jen::multiset<double> v = {-7, 10, -55, 742, 92, -76, 38, 220, 11, 11, 210};
  std::multiset<double> vc = {-7, 10, -55, 742, 92, -76, 38, 220, 11, 11, 210};
  auto x = v.begin();
  auto y = vc.begin();

  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(Multiset, 3) {
  jen::multiset<double> v;
  std::multiset<double> vc;
  auto x = v.begin();
  auto y = vc.begin();
  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(Multiset, 4) {
  jen::multiset<double> v = {-7, 10, -55, 742, 92, -76, 38, 220, 11, 11, 210};
  std::multiset<double> vc = {-7, 10, -55, 742, 92, -76, 38, 220, 11, 11, 210};
  v.insert(15);
  vc.insert(15);
  v.erase(v.begin());
  vc.erase(vc.begin());
  auto x = v.begin();
  auto y = vc.begin();
  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(Multiset, 5) {
  jen::multiset<double> v = {-7, 10, -55, 742, 92, -76, 38, 220, 11, 11, 210};
  std::multiset<double> vc = {-7, 10, -55, 742, 92, -76, 38, 220, 11, 11, 210};
  jen::multiset<double> v1 = {10, 20, 30, 40, 50};
  std::multiset<double> vc1 = {10, 20, 30, 40, 50};
  v.swap(v1);
  vc.swap(vc1);

  auto x = v.begin();
  auto y = vc.begin();
  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(Multiset, 6) {
  jen::multiset<double> v = {-7, 10,  -55, 742, 92,  -76,
                             38, 220, 11,  11,  210, 20};
  jen::multiset<double> v1 = {10, 20, 30, 40, 50};
  jen::multiset<double> vc = {-7, 10,  -55, 742, 92, -76, 38, 220, 11,
                              11, 210, 20,  10,  20, 30,  40, 50};
  v.merge(v1);

  auto x = v.begin();
  auto y = vc.begin();
  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(Multiset, 7) {
  jen::multiset<double> v = {-7, 10,  -55, 742, 92,  -76,
                             38, 220, 11,  11,  210, 20};
  std::multiset<double> vc = {-7, 10,  -55, 742, 92,  -76,
                              38, 220, 11,  11,  210, 20};

  ASSERT_EQ(*v.find(20), *vc.find(20));
}

TEST(Multiset, 8) {
  jen::multiset<double> v = {-7, 10,  -55, 742, 92,  -76,
                             38, 220, 11,  11,  210, 20};

  ASSERT_EQ(v.contains(100), false);
}

TEST(Multiset, 9) {
  jen::multiset<double> v = {-7, 10,  -55, 742, 92,  -76,
                             38, 220, 11,  11,  210, 20};
  jen::multiset<double>::iterator x = v.lower_bound(10);
  --x;
  ASSERT_EQ(*x, -7);
}

TEST(Multiset, 10) {
  jen::multiset<double> v = {-7, 10,  -55, 742, 92,  -76,
                             38, 220, 11,  11,  210, 20};
  auto x = v.upper_bound(8);
  --x;
  ASSERT_EQ(*x, -7);
}

TEST(Multiset, 11) {
  jen::multiset<double> v = {-7, 10,  -55, 742, 92,  -76,
                             38, 220, 11,  11,  210, 20};
  auto x = v.equal_range(8);
  ASSERT_EQ(*x.first, 10);
  ASSERT_EQ(*x.second, 10);
}

// int main(int argc, char **argv) {
//   testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
