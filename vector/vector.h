#ifndef VECTOR_VECTOR_H_
#define VECTOR_VECTOR_H_

#include <initializer_list>

namespace jen {
template <typename T>
class vector {
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T* iterator;
  typedef const T* const_iterator;
  typedef std::size_t size_type;

 public:
  vector() {}
  vector(size_type n) { allocate_mem(n); }
  vector(std::initializer_list<value_type> const& items) noexcept
      : vector(static_cast<size_type>(items.size())) {
    int count = 0;
    for (auto element : items) {
      array[count] = element;
      ++count;
    }
  }
  vector(const vector& v) {
    allocate_mem(v.container_capacity);
    for (size_type i = 0; i < container_size; ++i) array[i] = v.array[i];
  }
  vector(vector&& v) noexcept {
    std::swap(container_size, v.container_size);
    std::swap(container_capacity, v.container_capacity);
    std::swap(array, v.array);
  }

  ~vector() { delete_mem(); }
  vector operator=(vector&& v) {
    if (this != &v) {
      delete_mem();
      std::swap(container_size, v.container_size);
      std::swap(container_capacity, v.container_capacity);
      std::swap(array, v.array);
    }
    return *this;
  }
  vector operator=(const vector& v) {
    if (this != &v) {
      delete_mem();
      allocate_mem(v.container_capacity);
      for (size_type i = 0; i < container_size; ++i) array[i] = v.array[i];
    }
    return *this;
  }

  reference at(size_type pos) {
    if (pos > container_size - 1)
      throw std::out_of_range("Выход за пределы вектора!");
    return array[pos];
  }
  reference operator[](size_type pos) noexcept { return array[pos]; }
  const_reference front() const noexcept { return array[0]; }
  const_reference back() const noexcept { return array[container_size - 1]; }
  T* data() noexcept { return array; }

  iterator begin() noexcept { return array; }
  iterator end() noexcept { return &array[container_size]; }

  bool empty() const noexcept {
    if (container_size == 0)
      return true;
    else
      return false;
  }
  size_type size() const noexcept { return container_size; }
  size_type max_size() {
    std::allocator<T> max;
    return static_cast<size_type>(max.max_size());
  }
  void reserve(size_type size) {
    if (size > max_size())
      throw std::out_of_range("Заданный буфер больше возможного размера!");
    if (size > container_capacity) {
      reserve_memory(size);
    }
  }
  size_type capacity() const noexcept { return container_capacity; }

  void shrink_to_fit() {
    if (container_size == 0) {
      delete_mem();
    } else {
      reserve_memory(container_size);
    }
  }

  void clear() noexcept { container_size = 0; }

  iterator insert(iterator pos, const_reference value) {
    std::ptrdiff_t offset = pos - array;

    reserve_memory();

    pos = array + offset;
    std::move(pos, array + container_size, pos + 1);
    *pos = value;

    container_size += 1;

    return pos;
  }
  void erase(iterator pos) {
    T* temp = allocateMemory(container_capacity);
    for (size_type i = 0, j = 0; i < container_size; ++i, ++j) {
      if (pos != &array[i]) {
        temp[j] = array[i];
      } else {
        j--;
      }
    }
    delete[] array;
    array = temp;
    container_size--;
  }
  void push_back(const_reference value) {
    reserve_memory();

    array[container_size] = value;
    container_size++;
  }

  void pop_back() noexcept {
    if (!empty()) container_size--;
  }

  void swap(vector& other) noexcept {
    std::swap(container_size, other.container_size);
    std::swap(container_capacity, other.container_capacity);
    std::swap(array, other.array);
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    std::ptrdiff_t offset = pos - array;

    iterator temp_pos = const_cast<iterator>(pos);

    for (const auto& arg : {std::forward<Args>(args)...}) {
      temp_pos = insert(temp_pos, arg);
      ++temp_pos;
    }
    return array + offset;
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    for (const auto& arg : {std::forward<Args>(args)...}) {
      push_back(arg);
    }
  }

 private:
  value_type* array = nullptr;
  size_type container_size = 0;  // размер массива (кол-во элементов в векторе)
  size_type container_capacity = 0;  // размер буффера

  void allocate_mem(size_type container_size) {
    array = allocateMemory(container_size);
    this->container_size = container_size;
    container_capacity = container_size;
  }
  void delete_mem() {
    if (array != nullptr) delete[] array;
    container_size = 0;
    container_capacity = 0;
    array = nullptr;
  }

  /// @brief Изменение размера буфера/размера вектора через временный массив
  /// @param size новый размер вектора
  void reserve_memory(size_type exactly = 0) {
    size_type start_capacity = container_capacity;

    if (exactly != 0) {
      container_capacity = exactly;
    } else if (container_capacity == 0) {
      container_capacity = 1;
    } else if (container_capacity == container_size) {
      container_capacity *= 2;
    }

    if (container_capacity != start_capacity) {
      T* array_rev = allocateMemory(container_capacity);
      for (size_type i = 0; i < container_size; ++i) array_rev[i] = array[i];
      delete[] array;
      array = array_rev;
    }
  }

  value_type* allocateMemory(size_type count_values) {
    int8_t* data = new int8_t[sizeof(value_type) * count_values];
    return reinterpret_cast<value_type*>(data);
  }
};
}  // namespace jen

#endif  // VECTOR_VECTOR_H_
