#ifndef QUEUE_QUEUE_H_
#define QUEUE_QUEUE_H_

#include "../list/list.h"

namespace jen {

template <typename T, typename list = jen::list<T>>
class queue {
 public:
  using value_type = typename list::value_type;
  using reference = typename list::reference;
  using const_reference = typename list::const_reference;
  using size_type = typename list::size_type;

 protected:
  list list_obj;

 public:
  queue() : list_obj() {}
  queue(std::initializer_list<value_type> const &items) : list_obj(items) {}
  queue(const queue &q) : list_obj(q.list_obj) {}
  queue(queue &&q) : list_obj(std::move(q.list_obj)) {}
  ~queue() {}
  queue operator=(queue &&q) {
    list_obj.swap(q.list_obj);
    return *this;
  }

  const_reference front() { return list_obj.front(); }
  const_reference back() { return list_obj.back(); }
  bool empty() { return list_obj.empty(); }
  size_type size() { return list_obj.size(); }
  void push(const_reference value) { list_obj.push_back(value); }
  void pop() { list_obj.pop_front(); }
  void swap(queue &other) { list_obj.swap(other.list_obj); }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    for (const auto &arg : {std::forward<Args>(args)...}) {
      list_obj.push_back(arg);
    }
  }
  const_reference getFront() { return list_obj.front(); }
};

}  // namespace jen

#endif  // QUEUE_QUEUE_H_
