#ifndef LIST_LIST_H_
#define LIST_LIST_H_

#include <cstddef>
#include <cstdint>
#include <initializer_list>

namespace jen {

template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  list() : size_(0), head_(nullptr), tail_(nullptr), end_(nullptr) {
    value_type value = value_type{};
    end_ = new Node(value);
    end_->next_ = end_;
    end_->prev_ = end_;
  }

  list(size_type n) : list() {
    for (size_type i = 0; i < n; i++) {
      push_back(value_type{});
    }
  }

  list(std::initializer_list<value_type> const &items) : list() {
    for (const value_type &itm : items) {
      push_back(itm);
    }
  }

  list(const list &l) : list() {
    for (iterator i = l.begin(); i != l.end(); i++) {
      push_back(*i);
    }
  }

  list(list &&l) : list() { swap(l); }
  ~list() {
    clear();
    delete end_;
  }

  list &operator=(const list &l) {
    if (*this != l) {
      clear();
      size_ = l.size_;
      for (iterator i = l.begin(); i != l.end(); i++) {
        push_back(*i);
      }
    }
    return *this;
  }

  list &operator=(list &&l) noexcept {
    if (*this != l) {
      clear();
      swap(l);
    }
    return *this;
  }

  list &operator=(std::initializer_list<value_type> const &items) {
    clear();
    for (const value_type &itm : items) {
      push_back(itm);
    }
    return *this;
  }

  const_reference front() const noexcept { return end_->next_->data_; }

  const_reference back() const noexcept { return end_->prev_->data_; }

  bool empty() const noexcept { return size_ == 0; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept { return PTRDIFF_MAX / sizeof(Node); }

  void clear() {
    while (!empty()) {
      pop_back();
    }
  }
  void push_back(const_reference value) { insert(end(), value); }
  void pop_back() { erase(--end()); }
  void push_front(const_reference value) { insert(begin(), value); }

  void pop_front() { erase(begin()); }
  void swap(list &other) noexcept {
    if (*this != other) {
      std::swap(size_, other.size_);
      std::swap(head_, other.head_);
      std::swap(tail_, other.tail_);
      std::swap(end_, other.end_);
    }
  }

 private:
  void forgotList() noexcept {
    head_ = nullptr;
    tail_ = nullptr;
    end_->next_ = end_;
    end_->prev_ = end_;
    size_ = 0;
  }

  class Node {
   public:
    Node(const value_type &data)
        : data_(data), next_(nullptr), prev_(nullptr) {}
    value_type data_;
    Node *next_;
    Node *prev_;
  };

  size_type size_ = 0;
  Node *head_;
  Node *tail_;
  Node *end_;

 public:
  template <typename value_type>
  class ListIterator {
   public:
    ListIterator() : itr_(nullptr) {}

    ListIterator(Node *new_node) : itr_(new_node) {}

    Node *itr_;

    const_reference operator*() { return itr_->data_; }

    ListIterator &operator++() noexcept {
      itr_ = itr_->next_;
      return *this;
    }

    ListIterator operator++(int) {
      iterator resIter = iterator(itr_);
      itr_ = itr_->next_;
      return resIter;
    }

    ListIterator &operator--() noexcept {
      itr_ = itr_->prev_;
      return *this;
    }

    ListIterator operator--(int) {
      iterator resIter = iterator(itr_);
      itr_ = itr_->prev_;
      return resIter;
    }

    bool operator==(ListIterator other_itr) noexcept {
      return itr_ == other_itr.itr_;
    }
    bool operator!=(ListIterator other_itr) noexcept {
      return itr_ != other_itr.itr_;
    }
  };

  template <typename value_type>
  class ListConstIterator : public ListIterator<T> {
   public:
    ListConstIterator() = default;
    ListConstIterator(ListIterator<T> other) : ListIterator<T>(other) {}
  };

  using const_iterator = ListConstIterator<T>;
  using iterator = ListIterator<T>;

  iterator begin() const noexcept {
    const_iterator tmp;
    if (head_) {
      tmp.itr_ = head_;
    } else {
      tmp.itr_ = end_;
    }
    return tmp;
  }

  iterator end() const { return const_iterator(end_); }

  /// @brief вставка ноды вместо ноды pos, смещая её вправо
  /// @param pos куда вставляем
  /// @param node что вставлем
  /// @return итератор на вставленную ноду
  iterator insertNode(iterator pos, Node *node) {
    node->prev_ = pos.itr_->prev_;
    node->next_ = pos.itr_;

    node->prev_->next_ = node;
    node->next_->prev_ = node;

    head_ = end_->next_;
    tail_ = end_->prev_;
    ++size_;

    return iterator(node);
  }

  iterator insert(iterator pos, const_reference value) {
    Node *new_node = new Node(value);
    return insertNode(pos, new_node);
  }

  void erase(iterator pos) {
    if (pos.itr_ != end_ || size_ == 1) {
      pos.itr_->prev_->next_ = pos.itr_->next_;
      pos.itr_->next_->prev_ = pos.itr_->prev_;
      --size_;
      delete pos.itr_;
      head_ = end_->next_;
      tail_ = end_->prev_;
    }
  }

  void merge(list &other) {
    if (other.empty() || *this == other) {
      return;
    }

    list<value_type> mergedList;

    iterator iter1 = begin();
    iterator iter2 = other.begin();

    // сравниваем два листа для создания своего
    while (iter1 != end() && iter2 != other.end()) {
      if (*iter1 <= *iter2) {
        iterator insertIter = iter1++;
        mergedList.insertNode(mergedList.end(), insertIter.itr_);
      } else {
        iterator insertIter = iter2++;
        mergedList.insertNode(mergedList.end(), insertIter.itr_);
      }
    }

    // если один лист закончился, а второй нет, дополняем
    while (iter1 != end()) {
      iterator insertIter = iter1++;
      mergedList.insertNode(mergedList.end(), insertIter.itr_);
    }

    while (iter2 != other.end()) {
      iterator insertIter = iter2++;
      mergedList.insertNode(mergedList.end(), insertIter.itr_);
    }

    forgotList();
    other.forgotList();

    swap(mergedList);
  }

  void splice(const_iterator pos, list &other) {
    iterator tmp_begin = other.begin(), tmp_end = --other.end();

    tmp_begin.itr_->prev_ = pos.itr_->prev_;
    tmp_end.itr_->next_ = pos.itr_;
    tmp_begin.itr_->prev_->next_ = tmp_begin.itr_;
    tmp_end.itr_->next_->prev_ = tmp_end.itr_;

    size_ += other.size_;
    head_ = end_->next_;
    tail_ = end_->prev_;

    other.end_->next_ = other.end_;
    other.end_->prev_ = other.end_;
    other.size_ = 0;
    other.head_ = nullptr;
    other.tail_ = nullptr;
  }

  void reverse() {
    iterator itr_1 = begin();
    while (itr_1.itr_ != end_) {
      std::swap(itr_1.itr_->next_, itr_1.itr_->prev_);
      --itr_1;
    }
    std::swap(end_->next_, end_->prev_);
    std::swap(head_, tail_);
  }

  void unique() {
    iterator tmp = begin();
    while (tmp.itr_->next_ != end_) {
      iterator checkIter = tmp++;
      if (*checkIter == checkIter.itr_->next_->data_) {
        erase(checkIter);
      }
    }
    head_ = end_->next_;
    tail_ = end_->prev_;
  }

  void sort() { quicksort(begin(), --end()); }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    iterator temp_pos = pos;

    for (const auto &arg : {std::forward<Args>(args)...}) {
      insert(temp_pos, arg);
      ++temp_pos;
    }
    return temp_pos;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    for (const auto &arg : {std::forward<Args>(args)...}) {
      push_back(arg);
    }
  }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    iterator temp_pos = begin();
    for (const auto &arg : {std::forward<Args>(args)...}) {
      insert(temp_pos, arg);
      ++temp_pos;
    }
  }

 private:
  bool operator==(list &l) { return (head_ == l.head_ && tail_ == l.tail_); };
  bool operator!=(list &l) { return !(head_ == l.head_ && tail_ == l.tail_); };

  iterator enumeration(iterator l, iterator r) noexcept {
    value_type pivot = *r;

    while (r.itr_ != l.itr_->prev_) {
      while (*l < pivot) {
        ++l;
      }
      while (*r > pivot) {
        --r;
      }
      if (r.itr_ != l.itr_->prev_ && l != r) {
        std::swap(l.itr_->data_, r.itr_->data_);
        ++l;
        --r;
      } else {
        return l;
      }
    }
    return l;
  }

  void quicksort(iterator l, iterator r) {
    if (l.itr_ == r.itr_ || r.itr_ == end_ || l.itr_ == end_ ||
        l.itr_ == tail_) {
      return;
    }
    iterator a = enumeration(l, r);
    quicksort(l, --a);
    quicksort(++a, r);
  }
};

}  // namespace jen

#endif  // LIST_LIST_H_
