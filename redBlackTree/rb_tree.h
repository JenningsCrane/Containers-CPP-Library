#ifndef REDBLACKTHREE_RB_TREE_H_
#define REDBLACKTHREE_RB_TREE_H_

#include <cstdint>
#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>

#include "../vector/vector.h"
#include "node_struct.h"

namespace jen {

template <typename TreeTy>
class TreeConstIterator;

template <typename TreeTy>
class TreeIterator;

template <typename Key, typename T, bool IsMulti>
class RBtree {
 public:
  using tree_type = RBtree<Key, T, IsMulti>;
  using key_type = Key;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using node_type = Tree_Node<value_type>;
  using iterator = TreeIterator<tree_type>;
  using const_iterator = TreeConstIterator<tree_type>;

  RBtree() : root(nullptr) {}

  RBtree(const RBtree &other) { CopyTree(other); }

  RBtree(RBtree &&other) { MoveTree(std::move(other)); }

  ~RBtree() { clear_tree(root); }

  virtual const key_type &getValueKey(const_reference value) = 0;

  const_iterator begin() const { return iterator(GetMin(root)); }
  const_iterator rbegin() const { return iterator(GetMax(root)); }
  const_iterator end() const { return iterator(nullptr); }

  iterator begin() { return iterator(GetMin(root)); }
  iterator rbegin() { return iterator(GetMax(root)); }
  iterator end() { return iterator(nullptr); }
  node_type *getRoot() { return root; }

  std::pair<node_type *, bool> insertValue(const_reference value) {
    node_type *node = nullptr;
    bool isInserted = false;

    if (!IsMulti) {
      node = SearchNode(getValueKey(value));
    }

    if (node == nullptr) {
      node = new node_type(value);
      isInserted = insert(node);
    }

    return std::pair<node_type *, bool>(node, isInserted);
  }

  bool insert(node_type *node) {
    if (!root) {
      root = node;
      root->color = BLACK;
    } else {
      node_type *insertNode = root;
      node_type *nextNode = root;

      while (nextNode != nullptr) {
        if (getValueKey(node->value) < getValueKey(insertNode->value))
          nextNode = insertNode->left;
        else
          nextNode = insertNode->right;

        if (!IsMulti &&
            getValueKey(node->value) == getValueKey(insertNode->value))
          return false;

        if (nextNode != nullptr) {
          insertNode = nextNode;
        }
      }
      if (getValueKey(node->value) < getValueKey(insertNode->value))
        insertNode->left = node;
      else
        insertNode->right = node;
      node->parent = insertNode;
      insert_case1(node);

      while (root->parent != nullptr) {
        root = root->parent;
      }
    }

    size_ += 1;
    return true;
  }

  void insert_case1(node_type *node) {
    if (node->parent == nullptr)
      node->color = BLACK;
    else
      insert_case2(node);
  }

  void insert_case2(node_type *node) {
    if (node->parent->color == BLACK)
      return;
    else
      insert_case3(node);
  }

  void insert_case3(node_type *node) {
    node_type *uncleNode = node->uncle(), *grandpaNode;
    if ((uncleNode != nullptr) && (uncleNode->color == RED)) {
      node->parent->color = BLACK;
      uncleNode->color = BLACK;
      grandpaNode = node->grandparent();
      grandpaNode->color = RED;
      insert_case1(grandpaNode);
    } else {
      insert_case4(node);
    }
  }

  void insert_case4(node_type *node) {
    node_type *grandpaNode = node->grandparent();

    if ((node == node->parent->right) && (node->parent == grandpaNode->left)) {
      rotate_left(node->parent);
      node = node->left;
    } else if ((node == node->parent->left) &&
               (node->parent == grandpaNode->right)) {
      rotate_right(node->parent);
      node = node->right;
    }
    insert_case5(node);
  }

  void insert_case5(node_type *node) {
    node_type *grandpaNode = node->grandparent();
    node->parent->color = BLACK;
    grandpaNode->color = RED;
    if ((node == node->parent->left) && (node->parent == grandpaNode->left)) {
      rotate_right(grandpaNode);
    } else {
      rotate_left(grandpaNode);
    }
  }

  void erase(iterator node) {
    node_type *delNode = node.nodePtr;
    if (delNode != nullptr) {
      delNode = takeNode(delNode);
      delete delNode;
    }
  }

  node_type *SearchNode(key_type key) {
    node_type *node = root;
    if (!node) return nullptr;

    while (node != nullptr && key != getValueKey(node->value)) {
      if (key > getValueKey(node->value)) {
        node = node->right;
      } else if (key < getValueKey(node->value)) {
        node = node->left;
      }
    }
    return node;
  }

  node_type *takeNode(node_type *node) {
    if (node == nullptr) {
      return nullptr;
    }

    node_type *delNode = node;
    if (delNode->left != nullptr) {
      delNode = GetMax(delNode->left);
    } else if (delNode->right != nullptr) {
      delNode = GetMin(delNode->right);
    }

    if (delNode != node) {
      delNode->SwapNode(node);
      if (root == node) {
        root = delNode;
      }
      delNode = node;
    }

    if (delNode->color == BLACK) {
      node_type *child = delNode->left ? delNode->left : delNode->right;

      if (child == nullptr) {
        delete_case1(delNode);
      } else {
        child->parent = delNode->parent;

        if (delNode->parent->left == delNode) {
          delNode->parent->left = child;
        } else if (delNode->parent->right == delNode) {
          delNode->parent->right = child;
        }

        child->color = BLACK;
      }
    }

    if (delNode->parent != nullptr) {
      if (delNode->parent->left == delNode) {
        delNode->parent->left = nullptr;
      } else if (delNode->parent->right == delNode) {
        delNode->parent->right = nullptr;
      }
    }

    if (root == delNode) {
      root = nullptr;
    }

    size_ -= 1;

    return delNode;
  }

  void delete_case1(node_type *node) {
    if (node->parent != nullptr) delete_case2(node);
  }

  void delete_case2(node_type *node) {
    node_type *brotherNode = node->brother();
    if (brotherNode->color == RED) {
      node->parent->color = RED;
      brotherNode->color = BLACK;
      if (node == node->parent->left)
        rotate_left(node->parent);
      else
        rotate_right(node->parent);
    }
    delete_case3(node);
  }

  void delete_case3(node_type *node) {
    node_type *brotherNode = node->brother();
    if ((node->parent->color == BLACK) && (brotherNode->color == BLACK) &&
        (brotherNode->left == nullptr || brotherNode->left->color == BLACK) &&
        (brotherNode->right == nullptr || brotherNode->right->color == BLACK)) {
      brotherNode->color = RED;
      delete_case1(node->parent);
    } else
      delete_case4(node);
  }

  void delete_case4(node_type *node) {
    node_type *brotherNode = node->brother();
    if ((node->parent->color == RED) && (brotherNode->color == BLACK) &&
        (brotherNode->left == nullptr || brotherNode->left->color == BLACK) &&
        (brotherNode->right == nullptr || brotherNode->right->color == BLACK)) {
      brotherNode->color = RED;
      node->parent->color = BLACK;
    } else
      delete_case5(node);
  }

  void delete_case5(node_type *node) {
    node_type *brotherNode = node->brother();
    if (brotherNode->color == BLACK) {
      if ((node == node->parent->left) &&
          (brotherNode->right == nullptr ||
           brotherNode->right->color == BLACK) &&
          (brotherNode->left != nullptr && brotherNode->left->color == RED)) {
        brotherNode->color = RED;
        brotherNode->left->color = BLACK;
        rotate_right(brotherNode);
      } else if ((node == node->parent->right) &&
                 (brotherNode->left == nullptr ||
                  brotherNode->left->color == BLACK) &&
                 (brotherNode->right != nullptr &&
                  brotherNode->right->color == RED)) {
        brotherNode->color = RED;
        brotherNode->right->color = BLACK;
        rotate_left(brotherNode);
      }
    }
    delete_case6(node);
  }

  void delete_case6(node_type *node) {
    node_type *brotherNode = node->brother();
    brotherNode->color = node->parent->color;
    node->parent->color = BLACK;
    if (node == node->parent->left) {
      brotherNode->right->color = BLACK;
      rotate_left(node->parent);
    } else {
      brotherNode->left->color = BLACK;
      rotate_right(node->parent);
    }
  }

  void rotate_left(node_type *node) {
    node_type *pivot = node->right;
    pivot->parent = node->parent;
    if (node->parent != nullptr) {
      if (node->parent->left == node)
        node->parent->left = pivot;
      else
        node->parent->right = pivot;
    }
    node->right = pivot->left;
    if (pivot->left != nullptr) pivot->left->parent = node;
    node->parent = pivot;
    pivot->left = node;
    if (pivot->parent == nullptr) root = pivot;
  }

  void rotate_right(node_type *node) {
    node_type *pivot = node->left;
    pivot->parent = node->parent;
    if (node->parent != nullptr) {
      if (node->parent->left == node)
        node->parent->left = pivot;
      else
        node->parent->right = pivot;
    }
    node->left = pivot->right;
    if (pivot->right != nullptr) pivot->right->parent = node;
    node->parent = pivot;
    pivot->right = node;
    if (pivot->parent == nullptr) root = pivot;
  }

  static node_type *GetMax(node_type *node) {
    if (node == nullptr) return nullptr;
    while (node->right != nullptr) {
      node = node->right;
    }
    return node;
  }

  static node_type *GetMin(node_type *node) {
    if (node == nullptr) return nullptr;
    while (node->left != nullptr) {
      node = node->left;
    }
    return node;
  }

  void CopyChilds(node_type *newNode, node_type *oldNode) {
    if (oldNode->left != nullptr) {
      node_type *leftNode = new node_type(oldNode->left);
      newNode->left = leftNode;
      leftNode->parent = newNode;
      CopyChilds(leftNode, oldNode->left);
    }

    if (oldNode->right != nullptr) {
      node_type *rightNode = new node_type(oldNode->right);
      newNode->right = rightNode;
      rightNode->parent = newNode;
      CopyChilds(rightNode, oldNode->right);
    }
  }

  void CopyTree(const RBtree &m) {
    if (this->root != m.root) {
      clear_tree(this->root);

      if (m.root != nullptr) {
        this->root = new node_type(m.root);
        CopyChilds(this->root, m.root);
      }

      this->size_ = m.size_;
    }
  }

  void MoveTree(RBtree &&m) {
    clear_tree(root);
    root = m.root;
    size_ = m.size_;

    m.root = nullptr;
    m.size_ = 0;
  }

  void clear_tree(node_type *node) {
    if (!node) return;
    clear_tree(node->left);
    clear_tree(node->right);
    delete node;
    node = nullptr;
    size_ = 0;
  }

  bool empty() { return root == nullptr; }

  size_type size() { return size_; }

  size_type max_size() { return (PTRDIFF_MAX / sizeof(node_type)); }

  void swap(tree_type &other) {
    node_type *tmp = root;
    root = other.root;
    other.root = tmp;

    size_type tmpSize = size_;
    size_ = other.size_;
    other.size_ = tmpSize;
  }

  void merge(tree_type &other) {
    if (other.root != nullptr) {
      node_type *takingNode = nullptr;
      node_type *current_node = nullptr;
      for (const_iterator tmp_iter = other.begin(); tmp_iter != other.end();) {
        takingNode = (tmp_iter++).nodePtr;
        current_node = other.takeNode(takingNode);

        current_node->left = nullptr;
        current_node->right = nullptr;
        current_node->color = RED;
        current_node->parent = nullptr;

        if (!insert(current_node)) {
          other.insert(current_node);
        }
      }
    }
  }

  void clear_all(node_type *node) {
    if (node->left != nullptr) clear_all(node->left);

    if (node->right != nullptr) clear_all(node->right);

    delete node;
  }

  void clear() {
    if (root != nullptr) {
      clear_all(root);
      root = nullptr;
      size_ = 0;
    }
  }

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::initializer_list<value_type> items = {args...};

    vector<std::pair<iterator, bool>> resultVec;

    for (const_reference item : items) {
      std::pair<node_type *, bool> insertRes = tree_type::insertValue(item);
      resultVec.push_back(std::pair<iterator, bool>(iterator(insertRes.first),
                                                    insertRes.second));
    }

    return resultVec;
  }

 private:
  node_type *root = nullptr;
  size_type size_ = 0;
};

template <typename TreeTy>
class TreeConstIterator {
 public:
  using tree_type = TreeTy;
  using node_type = typename TreeTy::node_type;
  using value_type = typename TreeTy::value_type;
  using const_reference = const value_type &;

  template <typename Key, typename T, bool IsMulti>
  friend class RBtree;

  TreeConstIterator(node_type *node) : nodePtr(node) {}
  TreeConstIterator(TreeIterator<tree_type> &iter) : nodePtr(iter.nodePtr) {}

  const_reference operator*() const {
    if (nodePtr != nullptr) {
      return nodePtr->value;
    } else {
      static value_type zero = value_type{};
      return zero;
    }
  }

  TreeConstIterator &operator++() {
    if (nodePtr != nullptr) {
      if (nodePtr->right == nullptr) {
        node_type *parentNode = nullptr;
        while ((parentNode = nodePtr->parent) != nullptr &&
               nodePtr == parentNode->right) {
          nodePtr = parentNode;
        }
        nodePtr = parentNode;

      } else {
        nodePtr = tree_type::GetMin(nodePtr->right);
      }
    }

    return *this;
  }

  TreeConstIterator &operator--() {
    if (nodePtr != nullptr) {
      if (nodePtr->left == nullptr) {
        node_type *parentNode = nullptr;
        while ((parentNode = nodePtr->parent) != nullptr &&
               nodePtr == parentNode->left) {
          nodePtr = parentNode;
        }
        nodePtr = parentNode;

      } else {
        nodePtr = tree_type::GetMax(nodePtr->left);
      }
    }

    return *this;
  }

  TreeConstIterator operator++(int) {
    TreeConstIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  TreeConstIterator operator--(int) {
    TreeConstIterator tmp = *this;
    --(*this);
    return tmp;
  }
  bool operator==(const TreeConstIterator &other) const {
    return nodePtr == other.nodePtr;
  }
  bool operator!=(const TreeConstIterator &other) const {
    return nodePtr != other.nodePtr;
  }

  node_type *getNodePtr() { return nodePtr; }

 protected:
  node_type *nodePtr;
};

template <typename TreeTy>
class TreeIterator : public TreeConstIterator<TreeTy> {
 public:
  using tree_type = TreeConstIterator<TreeTy>;
  using node_type = typename TreeTy::node_type;
  using value_type = typename TreeTy::value_type;
  using reference = value_type &;

  template <typename Key, typename T, bool IsMulti>
  friend class RBtree;

  TreeIterator(node_type *node) : tree_type(node) {}

  reference operator*() const {
    return const_cast<reference>(tree_type::operator*());
  }

  TreeIterator &operator++() {
    tree_type::operator++();
    return *this;
  }

  TreeIterator &operator--() {
    tree_type::operator--();
    return *this;
  }

  TreeIterator operator++(int) {
    tree_type::operator++();
    return *this;
  }

  TreeIterator operator--(int) {
    tree_type::operator--();
    return *this;
  }
  bool operator==(const TreeIterator &other) const {
    return tree_type::operator==(other);
  }
  bool operator!=(const TreeIterator &other) const {
    return tree_type::operator!=(other);
  }
};

}  // namespace jen

#endif  // REDBLACKTHREE_RB_TREE_H_
