# Containers C++

Implementation of the containers.h library.

Iterator `iter` has the following operations:

- `*iter`: gets the element pointed to by the iterator;

- `++iter`: moves the iterator forward to the next element

- `--iter`: moves the iterator backwards to the previous element;

- `iter1 == iter2`: two iterators are equal if they point to the same element

- `iter1 != iter2`: two iterators are not equal if they point to different elements

### Part 1.

You need to implement the `containers.h` library classes (specifications are given in the relevant material sections, see **"Main containers"**). \
List of classes: `list`, `map`, `queue`, `set`, `stack`, `vector`.
- Make it as a header file `containers.h` which includes different header files with implementations of the specified containers (`list.h`, `map.h` and etc.) 
- Provide a Makefile for testing the library (with targets clean, test)
- The classical implementation of containers should be considered as a basis, but the final choice of implementations remains free. Except for the list - it should be implemented via the list structure rather than the array

### Part 2.

List of classes to be implemented additionally: `array`, `multiset`.
- Make it as a header file `containersplus.h` which includes different header files with implementations of the specified containers (`array.h`, `multiset.h`) 
- Provide a Makefile for testing the library (with targets clean, test)
- The classical implementation of containers should be considered as a basis, but the final choice of the algorithm remains free.

### Part 3. Bonus.

| Modifiers      | Definition                                      | Containers |
|----------------|-------------------------------------------------| -------------------------------------------|
| `iterator insert_many(const_iterator pos, Args&&... args)`          | inserts new elements into the container directly before `pos`  | List, Vector |
| `void insert_many_back(Args&&... args)`          | appends new elements to the end of the container  | List, Vector, Queue |
| `void insert_many_front(Args&&... args)`          | appends new elements to the top of the container  | List, Stack |
| `vector<std::pair<iterator,bool>> insert_many(Args&&... args)`          | inserts new elements into the container  | Map, Set, Multiset |

Note: the arguments are the already created elements of the appropriate container that should be inserted into this container.

*Tip 1*: notice that each of these methods uses an Args&&... args - Parameter pack construct. This construct allows a variable number of parameters to be passed to a function or method. So, when calling a method defined as `iterator insert_many(const_iterator pos, Args&&... args)`, you can write either `insert_many(pos, arg1, arg2)` or `insert_many(pos, arg1, arg2, arg3)`.

*Tip 2*: remember to test methods for different cases, including boundary ones.

💡 [Tap here](https://forms.yandex.ru/cloud/64181a7dc09c02252de7a4f3/) **to leave your feedback on the project**. Pedago Team really tries to make your educational experience better.
