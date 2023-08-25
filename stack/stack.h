#ifndef STACK_STACK_H_
#define STACK_STACK_H_

#include "../list/list.h"

namespace jen {

template <typename T, typename list = jen::list<T>>
class stack {
 public:
  using value_type = typename list::value_type;
  using reference = typename list::reference;
  using const_reference = typename list::const_reference;
  using size_type = typename list::size_type;

 protected:
  list list_obj;

 public:
  stack() : list_obj() {}
  stack(std::initializer_list<value_type> const &items) : list_obj(items) {}
  stack(const stack &q) : list_obj(q.list_obj){};
  stack(stack &&q) : list_obj(std::move(q.list_obj)){};
  ~stack(){};
  stack operator=(stack &&q) {
    list_obj.swap(q.list_obj);
    return *this;
  };

  const_reference top() { return list_obj.back(); }
  bool empty() { return list_obj.empty(); };
  size_type size() { return list_obj.size(); };
  void push(const_reference value) { list_obj.push_back(value); };
  void pop() { list_obj.pop_back(); };
  void swap(stack &other) { list_obj.swap(other.list_obj); };
  const_reference getFront() { return list_obj.front(); }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    typename list::iterator temp_pos = list_obj.begin();
    for (const auto &arg : {std::forward<Args>(args)...}) {
      list_obj.insert(temp_pos, arg);
      ++temp_pos;
    }
  }
};

}  // namespace jen

#endif  // STACK_STACK_H_
