# Data Structures in C

The lecture for this content is available on [YouTube](https://www.youtube.com/watch?v=Oys_x5qaXog).

- [Prerequisites](#prerequisites)
- [Why C?](#why-c)
- [What is a data structure?](#what-is-a-data-structure)
- [Why would you need something else?](#why-would-you-need-something-else)
- [Evaluating data structures](#evaluating-data-structures)
- [Data ordering](#data-ordering)
- [Iterating](#iterating)

## Prerequisites

_ This course assumes that you've had an introduction to programming class or similar
_ This course assumes basic familiarity with C
_ Use of dynamic memory is required in this course
_ There will be a review of how to use dynamic memory in C in a separate lesson

## Why C?

- C is the "Latin" of many modern programming languages
 - C++, Objective-C, C#, Java, JavaScript, Go, Rust, Swift, and Kotlin are all descendendants of C's syntax
- The core of all major operating systems is written in C
 - All versions of Unix (including macOS and its derivatives), Windows, Linux, and Android (a Linux derivative) all have a C foundation
- C is often the first high-level language available on new processors
 - Many embedded processors only support C
- While not a 1:1 translation in all circumstances, having a good foundation of data structures in C will help you in many places in Software Engineering

## What is a data structure?

- A data structure is a way to store more than one element of related data
- Some examples include:
 - A list of groceries
 - The name and grades for all students in a class
 - The deposits and withdrawals from a bank account in a month
- The simplest data structure is an array
 - In C, this can be a static array declared as a variable or a dynamic array created and destroyed with dynamic memory functions
 - In an array, all elements are simply addressed by their index

## Why would you need something else?

- There are multiple cases when a simple array may not be sufficient
- One is when you don't know how many things you need to represent up-front
 - Arrays are difficult and slow to resize
- Another is when you need to lookup a value by something other than an index
 - For example, you want to find the address of the person named, "Jane Doe"
 - Doing this with only arrays would require keeping track of multiple arrays, which is inconvenient and error prone
- Another is when you need to find something quickly
 - In a normal array, you have to start from the beginning and examine each element until you find what you're looking for
 - In real-world situations, this is often too slow
 - Data structures allow for organizing data for faster lookup

## Evaluating data structures

- Data structures are evaluated by the time complexity of their operations
 - Basic operations are get, set, add, and delete
- We say that the time complexity of an operation is of a certain "Order" of "n" where n is the number of elements it holds
- We express this as "O(X)" where X is the value in relation to n
 - For example, searching an unsorted array is "O(n)" because the number of comparisons scales directly with the number of elements in the array
 - However, adding an element to an unsorted array is "O(1)" or "constant time" because it only requires setting the next value of the array after the current last value in it
 - Deleting a value from an array is "O(n)" because it requires copying a number of elements from the deleted index to the end of the array and that number scales directly with the number of elements in the array
 - Assuming you know the index you want to modify, setting the value of an existing element of an array is "O(1)" because you don't have to do any modification of the data structure

## Data ordering

- Different data structures order internal data differently
 - Some maintain the order things are added in
 - Some maintain the data in sorted order
 - Some maintain the data in semi-random order
- This means that there is no one data structure that is best for all cases
- How the program is going to use the data affects the choice of the data structure to use

## Iterating

- In addition to getting an arbitrary element from a data structure, all data structures support traversing them from the beginning to the end
- This is usually accomplished by an "iterator" that is dedicated to the data structure type
- Incrementing the iterator prepares it to provide the next value in the data structure
 - The increment function destroys the iterator and returns NULL once there are no more elements to provide
- Accessing the value of the iterator provides the current value it references within the data structure

[Table of Contents](.)
