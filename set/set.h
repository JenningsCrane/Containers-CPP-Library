#ifndef SET_SET_H_
#define SET_SET_H_

#include <initializer_list>
#include <limits>
#include <utility>

#include "../redBlackTree/rb_tree.h"

namespace jen {

template <typename Key>
class set : public RBtree<Key, Key, false> {
 public:
  using key_type = Key;
  using value_type = Key;
  using tree_type = RBtree<Key, Key, false>;
  using node_type = typename tree_type::node_type;
  using size_type = size_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::const_iterator;

  set() : tree_type() {}

  set(std::initializer_list<value_type> const &items) {
    for (const_reference item : items) {
      node_type *node = new node_type(item);
      if (!tree_type::insert(node)) delete node;
    }
  }

  set(const set &s) : tree_type(s) {}

  set(set &&s) : tree_type(std::move(s)) {}

  ~set() {}

  set &operator=(set &s) {
    tree_type::CopyTree(s);
    return *this;
  }

  set &operator=(set &&s) {
    tree_type::MoveTree(std::move(s));
    return *this;
  }

  iterator begin() { return tree_type::begin(); }

  iterator rbegin() { return tree_type::rbegin(); }

  iterator end() { return tree_type::end(); }

  bool empty() { return tree_type::empty(); }

  size_type size() { return tree_type::size(); }

  size_type max_size() { return tree_type::max_size(); }

  void clear() { tree_type::clear(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    node_type *insertNode = tree_type::SearchNode(value);
    bool isInserted = false;

    if (insertNode == nullptr) {
      insertNode = new node_type(value);
      isInserted = tree_type::insert(insertNode);
    }

    return std::pair<iterator, bool>(insertNode, isInserted);
  }

  void erase(iterator pos) { tree_type::erase(pos); }

  void swap(set &other) { tree_type::swap(other); }

  void merge(set &other) { tree_type::merge(other); }

  iterator find(const key_type &key) {
    return iterator(tree_type::SearchNode(key));
  }

  bool contains(const key_type &key) { return tree_type::SearchNode(key); }

 private:
  const key_type &getValueKey(const_reference value) override { return value; }
};
}  // namespace jen

#endif  // SET_SET_H_
