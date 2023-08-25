#ifndef ARRAY_ARRAY_H_
#define ARRAY_ARRAY_H_

#include <cstring>

namespace jen {
template <typename T, size_t N>
class array {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 public:
  array() {
    set_array_null();
    size_array = N;
  }
  array(std::initializer_list<value_type> const &items) {
    if (items.size() > N)
      throw std::out_of_range("Значений больше, чем размер массива!");
    size_array = N;
    int count = 0;
    for (auto &element : items) {
      static_array[count] = element;
      ++count;
    }
  }
  array(const array &a) {
    size_array = a.size_array;
    for (size_type i = 0; i < N; ++i) static_array[i] = a.static_array[i];
  }
  array(array &&a) noexcept {
    set_array_null();
    std::swap(static_array, a.static_array);
    std::swap(size_array, a.size_array);
  }
  ~array() noexcept { set_array_null(); }
  array operator=(array &&a) noexcept {
    if (this != &a) {
      set_array_null();
      std::swap(static_array, a.static_array);
      std::swap(size_array, a.size_array);
    }
    return *this;
  }
  array operator=(const array &a) noexcept {
    if (this != &a) {
      size_array = a.size_array;
      for (size_type i = 0; i < N; ++i) static_array[i] = a.static_array[i];
    }
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= N) {
      throw std::out_of_range("Выход за пределы массива!");
    }
    return static_array[pos];
  }
  reference operator[](size_type pos) noexcept { return static_array[pos]; }

  const_reference front() const noexcept { return static_array[0]; }
  const_reference back() const noexcept { return static_array[N - 1]; }

  iterator data() noexcept { return static_array; }
  const_iterator data() const noexcept { return static_array; }

  iterator begin() noexcept { return &static_array[0]; }
  const_iterator begin() const noexcept { return &static_array[0]; }
  iterator end() noexcept { return &static_array[N]; }
  const_iterator end() const noexcept { return &static_array[N]; }

  bool empty() const noexcept {
    if (N == 0)
      return true;
    else
      return false;
  }
  size_type size() const noexcept { return N; }
  size_type max_size() const noexcept { return N; }

  void swap(array &other) {
    if (size_array != other.size_array)
      throw std::out_of_range("Массивы не равны");
    std::swap(static_array, other.static_array);
  }
  void fill(const_reference value) noexcept {
    for (int i = 0; i < size_array; ++i) static_array[i] = value;
  }

 private:
  size_type size_array;
  value_type static_array[N];

  void set_array_null() noexcept {
    for (size_type i = 0; i < N; ++i) static_array[i] = 0;
    size_array = 0;
  }
};
}  // namespace jen

#endif  // ARRAY_ARRAY_H_
