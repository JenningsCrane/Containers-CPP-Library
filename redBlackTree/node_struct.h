#ifndef REDBLACKTHREE_NODE_STRUCT_H_
#define REDBLACKTHREE_NODE_STRUCT_H_

namespace jen {

enum new_color { RED, BLACK };

template <typename T>
struct Tree_Node {
  using value_type = T;
  using Node = Tree_Node<value_type>;

  Node *parent, *left, *right;
  new_color color;
  value_type value;

  Tree_Node()
      : parent(nullptr),
        left(nullptr),
        right(nullptr),
        color(BLACK),
        value(0) {}

  Tree_Node(value_type value)
      : parent(nullptr),
        left(nullptr),
        right(nullptr),
        color(RED),
        value(value) {}

  Tree_Node(Tree_Node *node)
      : parent(nullptr),
        left(nullptr),
        right(nullptr),
        color(node->color),
        value(node->value) {}

  void ColorSwap(Node *other) noexcept {
    new_color tmp_color = this->color;
    this->color = other->color;
    other->color = tmp_color;
  }

  void SwapChild(Node *other) noexcept {
    if (this->parent != nullptr) {
      if (this == this->parent->left) this->parent->left = other;
      if (this == this->parent->right) this->parent->right = other;
    }
  }

  void SwapNode(Node *other) noexcept {
    this->SwapChild(other);
    other->SwapChild(this);

    Node *tmp = this->left;
    this->left = other->left;
    other->left = tmp;

    tmp = this->right;
    this->right = other->right;
    other->right = tmp;

    tmp = this->parent;
    this->parent = other->parent;
    other->parent = tmp;

    if (this->left != nullptr) this->left->parent = this;
    if (this->right != nullptr) this->right->parent = this;
    if (other->left != nullptr) other->left->parent = other;
    if (other->right != nullptr) other->right->parent = other;

    this->ColorSwap(other);
  }

  Node *grandparent() noexcept {
    if (this->parent != nullptr) {
      return this->parent->parent;
    }
    return nullptr;
  }

  Node *uncle() noexcept {
    Node *grandpa = this->grandparent();
    if (!grandpa) {
      return nullptr;
    } else if (grandpa->left == this->parent) {
      return grandpa->right;
    } else {
      return grandpa->left;
    }
  }

  Node *brother() noexcept {
    if (this == this->parent->left)
      return this->parent->right;
    else
      return this->parent->left;
  }
};
}  // namespace jen

#endif  // REDBLACKTHREE_NODE_STRUCT_H_
