
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

    Swap both vectors
    
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

    Return the capacity of the vector
    
* `Iterator insert(const Iterator position, const T& t)`

    Insert an element at the `position` specified by the `Iterator`
    
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

### Deque (in deque.hpp)

Here's a list of implemented functions for the class `Deque`.

### Set (in set.hpp)

Here's a list of implemented functions for the class `Set`.

### List (in list.hpp)

Here's a list of implemented functions for the class `List`.

### Tuple (in tuple.hpp)

Here's a list of implemented functions for the class `Tuple`.

### UnorderedMap (in map.hpp)

Here's a list of implemented functions for the class `UnorderedMap`.

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

    Swap two stacks
