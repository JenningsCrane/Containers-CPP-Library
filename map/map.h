#ifndef MAP_MAP_H_
#define MAP_MAP_H_

#include <initializer_list>
#include <limits>
#include <utility>

#include "../redBlackTree/rb_tree.h"

namespace jen {

template <typename Key, typename T>
class map : public RBtree<Key, std::pair<const Key, T>, false> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using tree_type = RBtree<Key, std::pair<const Key, T>, false>;
  using node_type = typename tree_type::node_type;
  using value_type = std::pair<const key_type, mapped_type>;
  using size_type = size_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::const_iterator;

  map() : tree_type() {}

  map(std::initializer_list<value_type> const &items) {
    for (const_reference item : items) {
      node_type *node = new node_type(item);
      if (!tree_type::insert(node)) delete node;
    }
  }

  map(const map &m) : tree_type(m) {}

  map(map &&m) : tree_type(std::move(m)) {}

  ~map() {}

  iterator begin() { return tree_type::begin(); }

  iterator end() { return tree_type::end(); }
  iterator rbegin() { return tree_type::rbegin(); }
  bool empty() { return tree_type::empty(); }

  size_type size() { return tree_type::size(); }

  size_type max_size() { return tree_type::max_size(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    node_type *insertNode = tree_type::SearchNode(value.first);
    bool isInserted = false;

    if (insertNode == nullptr) {
      insertNode = new node_type(value);
      isInserted = tree_type::insert(insertNode);
    }

    return std::pair<iterator, bool>(insertNode, isInserted);
  }

  std::pair<iterator, bool> insert(const key_type &key,
                                   const mapped_type &obj) {
    node_type *insertNode = tree_type::SearchNode(key);
    bool isInserted = false;

    if (insertNode == nullptr) {
      insertNode = new node_type(
          std::pair<const key_type &, const mapped_type &>(key, obj));
      isInserted = tree_type::insert(insertNode);
    }
    return std::pair<iterator, bool>(insertNode, isInserted);
  }

  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const T &obj) {
    node_type *insertNode = tree_type::SearchNode(key);
    bool isInserted = false;

    if (insertNode == nullptr) {
      insertNode = new node_type(
          std::pair<const key_type &, const mapped_type &>(key, obj));
      isInserted = tree_type::insert(insertNode);
    } else
      insertNode->value.second = obj;
    return std::pair<iterator, bool>(insertNode, isInserted);
  }

  void erase(iterator pos) { tree_type::erase(pos); }

  void swap(map &other) { tree_type::swap(other); }

  void merge(map &other) { tree_type::merge(other); };

  void clear() { tree_type::clear(); }

  bool contains(const key_type &key) { return tree_type::SearchNode(key); }

  map &operator=(map &m) {
    tree_type::CopyTree(m);
    return *this;
  }

  map &operator=(map &&m) {
    tree_type::MoveTree(std::move(m));
    return *this;
  }

  mapped_type &at(const key_type &key) {
    node_type *node = tree_type::SearchNode(key);
    if (node == nullptr) throw std::out_of_range("Node does not exists");
    return node->value.second;
  }

  mapped_type &operator[](const key_type &key) {
    node_type *node = tree_type::SearchNode(key);
    if (node == nullptr) {
      node = new node_type(value_type(key, mapped_type()));
      tree_type::insert(node);
    }
    return node->value.second;
  }

  const key_type &getValueKey(const_reference value) override {
    return value.first;
  }
};
}  // namespace jen

#endif  // MAP_MAP_H_
