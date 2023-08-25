#ifndef MULTISET_MULTISET_H_
#define MULTISET_MULTISET_H_

#include "../redBlackTree/rb_tree.h"

namespace jen {

template <typename Key>
class multiset : public RBtree<Key, Key, true> {
 public:
  using key_type = Key;
  using value_type = Key;
  using tree_type = RBtree<Key, Key, true>;
  using node_type = typename tree_type::node_type;
  using size_type = size_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::const_iterator;

  multiset() : tree_type() {}

  multiset(std::initializer_list<value_type> const &items) {
    for (const_reference item : items) {
      node_type *node = new node_type(item);
      if (!tree_type::insert(node)) delete node;
    }
  }

  multiset(const multiset &ms) : tree_type(ms) {}

  multiset(multiset &&ms) : tree_type(std::move(ms)) {}

  ~multiset() {}

  multiset &operator=(multiset &ms) {
    tree_type::CopyTree(ms);
    return *this;
  }

  multiset &operator=(multiset &&ms) {
    tree_type::MoveTree(std::move(ms));
    return *this;
  }

  iterator begin() { return tree_type::begin(); }

  iterator rbegin() { return tree_type::rbegin(); }

  iterator end() { return tree_type::end(); }

  bool empty() { return tree_type::empty(); }

  size_type size() { return tree_type::size(); }

  size_type max_size() { return tree_type::max_size(); }

  void clear() { tree_type::clear(); }

  iterator insert(const value_type &value) {
    node_type *insertNode = new node_type(value);
    tree_type::insert(insertNode);

    return insertNode;
  }

  void erase(iterator pos) { tree_type::erase(pos); }

  void swap(multiset &other) { tree_type::swap(other); }

  void merge(multiset &other) { tree_type::merge(other); }

  size_type count(const key_type &key) {
    size_type keyCount = 0;
    std::pair<iterator, iterator> keyRange = equal_range(key);
    for (iterator &iter = keyRange.first; iter != keyRange.second; ++iter)
      ++keyCount;
    return keyCount;
  }

  iterator find(const key_type &key) {
    return iterator(tree_type::SearchNode(key));
  }

  bool contains(const key_type &key) { return tree_type::SearchNode(key); }

  std::pair<iterator, iterator> equal_range(const key_type &key) {
    node_type *moveNode = tree_type::getRoot();
    node_type *minNode = nullptr;
    node_type *maxNode = nullptr;

    while (moveNode != nullptr) {
      const key_type &nodeKey = getValueKey(moveNode->value);
      if (key > nodeKey) {
        moveNode = moveNode->right;
      } else {
        if (maxNode == nullptr && key < nodeKey) {
          maxNode = moveNode;
        }
        minNode = moveNode;
        moveNode = moveNode->left;
      }
    }
    if (maxNode == nullptr)
      moveNode = tree_type::getRoot();
    else
      moveNode = maxNode->left;
    while (moveNode != nullptr) {
      if (key < getValueKey(moveNode->value)) {
        maxNode = moveNode;
        moveNode = moveNode->left;
      } else {
        moveNode = moveNode->right;
      }
    }

    return std::pair<iterator, iterator>(iterator(minNode), iterator(maxNode));
  }

  iterator lower_bound(const key_type &key) { return equal_range(key).first; }

  iterator upper_bound(const key_type &key) { return equal_range(key).second; }

 private:
  const key_type &getValueKey(const_reference value) override { return value; }
};
}  // namespace jen

#endif  // MULTISET_MULTISET_H_
