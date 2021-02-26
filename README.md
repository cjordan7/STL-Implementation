
# STL-Implementation

This is an implementation of several containers of the STL (Standard Template
Library) library.

The namespace is `ostl` which stands for  *my Own STL*

## About the Project

My primary goal for this project was to gain a better understanding of the STL. My
second goal was to practice template programming. For developing the container
`Tuple`, I've used a lot of template concepts and tools, such as variadic templates,
parameter packs, unpacking and template specializations.

In this project, I implemented several containers of the STL, namely:

```
Vector
Queue
Deque
Set
List
Tuple
UnorderedMap
Stack
```

## The public API

Now let's talk about the functions that can be accessed through the public API.

### Vector (in vector.hpp)

Here's a list of implemented functions for the class `Vector`.

* `Vector()`
  
  Create a vector with size zero.

* `Vector(size_t size)`

    Create a vector with size `size`.

* `Vector(T ts[], size_t size)`

  Create a vector with a C-array, `size` is used to specify the size the array.

* `Vector(Vector<T>& t)`

  Create a vector to the new vector.

* `Vector<T>& operator=(const Vector<T>& rhs)`

    Assign a vector to the current one.

* `Vector<T>& operator=(Vector<T>&& vector)`

    Assign a vector to the current one.
* `Vector<T>& operator=(std::initializer_list<T> il)`

    Assign an initializer list to the current vector.
    
* `void reserve(size_t memorySize)`

    Reserve memory for the vector.

* `void resize(unsigned long long n)`
  
  Resize the vector.
  
* `void shrinkToFit()`

    Resize the vector memory size to be equal to the size of the vector.
    
* `T& at(unsigned long long i)`
  
  Access the element at index `i`. An exception is thrown if the index is out of
  bounds.

* `const T& at(unsigned long long i) const`
  
  Access the element at index `i`. An exception is thrown if the index is out of
  bounds.

* `T& front()`

    Return the first element of the vector.
    
* `const T& front() const`

    Return a constant to the first element of the vector.
    
* `T* data() noexcept`
  
  Return the data of the vector.
  
* `const T* data() const noexcept`
  
  Return the data of the vector.

* `void swap(Vector& vector)`

    Swap both vectors.
    
* `T& back()`

    Returns the last element of the vector.
    
* `const T& back() const`
  
  Returns a constant to the last element of the vector.


* `T& operator[](int i)`

  Access the element at index `i`. No exceptions are thrown if the index is out of
  bounds.

* `const T& operator[](int i) const`

  Access the element at index `i`. No exceptions are thrown if the index is out of
  bounds.
  
* `void pushBack(T&& t)`

    Add a `rvalue` to the vector.
* `void pushBack(const T& t)`

    Add a `rvalue` to the vector.

* `void popBack()`

    Delete an element of the vector.
* `bool empty()`

    Return wether the vector is empty.
    
* `unsigned long long size() const`
  
  Return the size of the vector.
  
* `unsigned long long capacity() const`

    Return the capacity of the vector.
    
* `Iterator insert(const Iterator position, const T& t)`

    Insert an element at the `position` specified by the `Iterator`.
    
* `Iterator begin()`

    Returns an iterator to the begin of the vector.
* `Iterator end()`

    Returns an iterator to the end of the vector.

* `Iterator erase(const Iterator position)`

    Delete the element specified by iterator.

* `Iterator erase(const Iterator first, const Iterator last)`

    Delete the elements between first and last.

* `void clear() noexcept`

    Reset the vector.

### Queue (in queue.hpp)

Here's a list of implemented functions for the class `Queue`.

* `Queue()`

    Create an empty queue.
    
* `Queue(Queue<T> const& queue)`

    Create a queue by copying it.
    
* `unsigned long long size() const`

    Returns the size of the queue.
    
* `bool empty() const`

    Check whether the queue is empty or not.
    
* `T& front()`

    Returns the "oldest" element inserted in the queue.
    
* `const T& front() const`

    Returns the "oldest" element inserted into the queue.
    
* `T& back()`

    Returns the "newest" element inserted into the queue.

* `const T& back() const`

    Returns the "newest" element inserted into the queue.
    
* `void push(const T& t)`

    Push a new element into the queue.

* `void push(T&& t)`

    Push a new element into the queue.
    
* `void pop()`

    Delete the "oldest" element of the queue.

* `void swap(Queue& queue) noexcept`

    Swap two queues.

### Deque (in deque.hpp)

Here's a list of implemented functions for the class `Deque`.

* `Deque()`

    Create an empty deque.
    
* `Deque(size_t size)`

    Create a deque with size `size`.
    
* `Deque(Deque<T> const& deque)`

    Copy a deque.
    
* `Deque<T>& operator=(const Deque& deque)`

    Assign a deque.

* `Deque<T>& operator=(Deque&& deque)`

    Assign a deque.
    
* `Deque<T>& operator=(std::initializer_list<T> il)`

    Assign an initializer list to a deque.
    
* `Iterator begin() noexcept`

    Return an iterator to the begining of the list.

* `const Iterator begin() const noexcept`

    Return an iterator to the begining of the list.
    
* `Iterator end() noexcept`

    Return an iterator to the en of the list.

* `const Iterator end() const noexcept`

    Return an iterator to the en of the list.
    
* `unsigned long long size() const noexcept`

    Return the size of the deque.

* `void resize(unsigned long long size)`

    Resize the deque.

* `T& at(unsigned long long i)`

    Get an the element at the index i of the deque. It sends an exception if it
    fails.

* `const T& at(unsigned long long i) const`

    Get an the element at the index i of the deque. It sends an exception if it
    fails.
    
* `bool empty() const noexcept`

    Returns whether the deque is empty.
    
* `void shrinkToFit()`

    Reduce the memory size to the actual size of the deque.
    
* `T& operator[](int i)`

    Get an the element at the index i of the deque.

* `const T& operator[](int i) const`

    Get an the element at the index i of the deque.

* `T& front()`

    Get the first element of the deque.
    
* `const T& front() const`

    Get the first element of the deque.
    
* `T& back()`

    Get the last element of the deque.

* `const T& back() const`

    Get the last element of the deque.
    
* `void pushBack(const T& t)`

    Add an element to the end of the deque.

* `void pushBack(T&& t)`

    Add an element to the end of the deque.
    
* `void pushFront(const T& t)`

    Add an element to the begining of the deque.
    
* `void pushFront(T&& t)`

    Add an element to the begining of the deque.
    
* `void popBack()`

    Delete the end element of the deque.
    
* `void popFront()`

    Delete the first element of the deque.
    
* `Iterator insert(const Iterator position, const T& t)`

    Add an element at `position`.
    
* `Iterator erase(const Iterator position)`

    Delete an element at `position`.

* `Iterator erase(const Iterator first, const Iterator last)`

    Delete elements between `first` and t `last`.
    
* `void swap(Deque& deque)`

    Swap deque with self.
    
* `void clear() noexcept`
  
  Clear the memory of the deque.


### Set (in set.hpp)

Here's a list of implemented functions for the class `Set`.

### List (in list.hpp)

Here's a list of implemented functions for the class `List`.

* `List()`

    Create an empty list.
    
* `List(List<T> const& List)`

    Copy a list.

* `Iterator begin()`

    Returns an iterator to the begining of the list.

* `Iterator end()`

    Returns an iterator to the end of the list.

* `const Iterator cbegin() const noexcept`

    Returns a constant iterator to the begining of the list.

* `const Iterator cend() const noexcept`

    Returns a constant iterator to the end of the list.

* `void pushFront(const T& t)`

    Push a new element to the list.

* `void pushFront(T&& t)`

    Push a new element to the list.

* `void pushFront(T data)`

    Push a new element to the list.
    
* `T& front()`

    Get the front element of the list.

* `const T& front() const`

    Get the front element of the list.

* `T& back()`

    Get the back element of the list.

* `const T& back() const`

    Get the back element of the list.

* `void pushBack(T data)`
  
  Add an element at the end of the list.

* `void popFront()`

    Delete an element at the begining of the list.
    
* `void popBack()`

    Delete an element at the end of the list.
    
* `unsigned long long size()`

    Returns the size of the list.

* `bool empty() const noexcept`

    Check if the list is empty. Or in other words, if the size is zero.


### Tuple (in tuple.hpp)

Here's a list of implemented functions for the class `Tuple`.

* `Tuple(Ts... ts)`

    Create a tuple.
    
    Example: `ostl::Tuple<int, std::string> tuple(42, "My Own STL")`

* `T& get`

    Get the element of a tuple

    Example to get "My Own STL" from the example above. Use: `ostl::get<1>(tuple)`

### UnorderedMap (in map.hpp)

Here's a list of implemented functions for the class `UnorderedMap`.

* `UnorderedMap()`

    Create an empty map.

* `UnorderedMap(std::initializer_list<ostl::Pair<K, V>> il)`

    Create a map with an initializer list.

* `UnorderedMap& operator=(const UnorderedMap& x)`

    Assign an initializer map to the map.

* `UnorderedMap& operator=(UnorderedMap&& x)`

    Assign an initializer map to the map.

* `UnorderedMap& operator=(std::initializer_list<ostl::Pair<K, V>> il)`

    Assign an initializer list to the map.

* `void clear() noexcept`

    Clear the content of the map.

* `const Iterator cbegin() const noexcept`

  Return an iterator to the begining of the map.

* `const Iterator cend() const noexcept`

  Return an iterator to the end of the map.

* `Iterator begin()`

  Return an iterator to the begining of the map.

* `const Iterator begin() const`
  
  Return an iterator to the begining of the map.

* `Iterator end()`

    Returns an iterator to the end of the map.

* `const Iterator end() const`

    Returns an iterator to the end of the map.

* `V& at(const K& key)`

    Get the value at the key.

* `Iterator erase(const Iterator position)`

    Delete the element at the iterator position.

* `V& operator[](const K& k)`

    Get the value at the key k.

* `V& operator[](K&& k)`

    Get the value at the key k.

* `const V& at(const K& key) const`

    Get the value at the key k.

* `bool empty() const`

    Returns wether the map is empty or not.

* `void remove(const K& key)`

    Remove the key k.

* `unsigned long long size`

    Return the size of the map.

### Stack (in stack.hpp)

Here's a list of implemented functions for the class `Stack`.

* `Stack()`

    Create an empty stack.
    
* `Stack(Stack<T> const& stack)`

    Copy a stack into the current one.

* `Stack(size_t size)`

    Create a stack of size `size`.
    
* `bool empty() const`

    Return wether the stack is empty or not.
    
* `void push(T& t)`

    Push an element onto the stack.

* `void push(const T& t)`

    Push an const element onto the stack.
    
* `T& top()`

    Get the top element of the stack.

* `const T& top() const`

    Get the top element of the stack.

* `void pop()`
  
  Pop the stack.
    
* `unsigned long long size() const`

    Get the size of the stack.
    
* `void swap(Stack& stack) noexcept`

    Swap two stacks.
