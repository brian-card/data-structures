# Dynamic Memory in C

The lecture for this content is available on [YouTube](https://www.youtube.com/watch?v=fqvoLuhi7Gg).

- [Dynamic memory functions](#dynamic-memory-functions)
- [When to use malloc()](#when-to-use-malloc)
- [When to use free()](#when-to-use-free)
- [When to use calloc()](#when-to-use-calloc)
- [When to use realloc()](#when-to-use-realloc)
- [Always check for NULL!!!](#always-check-for-null)
- [Memory leaks](#memory-leaks)
- [Best practices](#best-practices)
- [Example function](#example-function)
- [Exercise](#exercise)

## Dynamic memory functions

There are four (4) dynamic memory functions in C:
- malloc(size): Basic memory allocation.  Returns a pointer to allocated memory on success, NULL on failure.  Allocated memory is *NOT* guaranteed to be cleared to zero.
- free(pointer): Releases memory previously allocated by one of the other memory functions.  There is nothing returned.
- calloc(number of elements, size of each element): Allocates memory and clears all of the bytes to 0.  Returns a pointer to allocated, cleared memory on success, NULL on failure.
- realloc(pointer, size): Changes the size of memory previously allocated with malloc or calloc.  Returns a pointer to allocated memory (which may be the same as or different from the one passed in) on success, NULL if the reallocation was unsuccessful.

## When to use malloc()

- "malloc" is short for "memory allocate"
- malloc() is the fastest of the functions that can allocate memory
  - It just finds the first thing that satisfies the size and returns it
- It's used when the user does not care about the contents of the returned memory
  - This means that the user will be initializing the memory and will *NOT* attempt to check any of the memory during initialization
- The parameter that's passed to malloc is the number of *bytes* you want allocated
  - This means that if you want something that is more than one byte in size, you'll have to use the right number
  - You can use C's "sizeof" operator to do this
  - For example:  `int *myInt = (int*) malloc(sizeof(int));`
- You can use malloc to create an array of things
  - For example, to declare an array of 42 ints:  `int *myInts = (int*) malloc(42 * sizeof(int));`

## When to use free()

- Use free when you're done with a piece of memory
- It doesn't matter which function allocated the memory or if it was reallocated
- Make sure you don't attempt to use a pointer once it's been freed
  - This will probably make your program crash
- Make sure you don't attempt to free a piece of memory that's already been freed
  - This will also probably make your program crash
- Always set your pointer to NULL after you free it
- It's recommended that you write "free(pointer); pointer = NULL;" on one line so that you don't accidentally forget to set it to NULL
- It is OK to free a NULL pointer (it just does nothing)
  - No need to check if a pointer is NULL before freeing it

## When to use calloc()

- "calloc" is short for "clear memory allocate"
- Use calloc when you need to guarantee that all the bytes in the memory you're using are set to zero or when you would be initializing it to zero anyway
  - This is important for some libraries
- Using calloc is usually slower than using malloc because of the extra work done to guarantee that all of the memory is zero
- Using calloc may be faster than setting it all to zero yourself because it may make use of special operating system functionality to do this
- The parameters to calloc are the number of elements and the size of each element
- Always set the number of elements to 1 and use the size you need as the second parameter
  - calloc has two parameters for historical reasons, but really only one is useful

## When to use realloc()

- "realloc" is short for "reallocate"
- Use realloc when you need to make a piece of memory larger
  - It can technically also be used to make a piece of memory smaller, but this should be avoided
- The parameters to realloc are the pointer to reallocate and the desired new size of the memory (*NOT* the number of bytes to be added)
- realloc may have to allocate a new block of memory to satisfy the request
  - If it does, it will copy over the contents of the old memory to the new memory
- realloc returns a pointer to the memory of the new size on success
- *NEVER* assign the return value to the same pointer you passed in
  - Use a separate variable for the return value (more on this next)

## Always check for NULL!!!

- Memory allocation (or reallocation) can fail
- If it does, then malloc, calloc, or realloc will return NULL
- *ALWAYS* check the return value to make sure it's not NULL before continuing and handle a failure gracefully
- If you don't check for NULL and memory allocation fails, your program will crash when it attempts to use the pointer
- As mentioned in the realloc slide *NEVER* assign the return value of realloc back to the same pointer you pass in
  - realloc does not do anything with the pointer you pass in if reallocation fails
  - If you reassign the pointer you pass in and realloc fails, your pointer will become NULL and you will lose the ability to free the memory
  - This is called a "memory leak"

## Memory leaks

- A memory leak happens when the pointer to allocated memory is lost before the memory at that address is freed
- This can happen, for example, if you forget to free the memory you locally allocated in a function before it exits
  - The pointer in the function will disappear when the function exits and you will have no knowledge of what it was and therefore will be unable to free it
- This can also happen if you assign the return value of a memory allocation function to a pointer that already held allocated memory
  - The pointer will hold the value of the new block of memory and the address of the old block of memory will be forever lost
- Over time, memory leaks cause programs to consume large amounts of RAM
- If it consumes enough memory, it will start interfering with the operation of other programs on the system
- At that point, the operating system will be forced to kill the program in order to make enough RAM available for other programs to run

## Best practices

- When you write a line of code that allocates memory, immediately write the line of code that will free it
- Put the logic of using the memory between the two lines
- This will help ensure that the memory you allocate is deallocated properly before your function exits
  - Exception:  If the purpose of your function is to create and initialize a block of memory that is being returned to the caller then it obviously doesn't make sense to free the memory you allocate before the function ends
- If your function has multiple return statements in it, make sure you free your memory before each one
- Free memory in the reverse order the pointers were allocated in
  - This helps write some error handling code such as the way errors are handled in the Linux kernel

## Example function

```C
void testRandomNumbers(void) {
    const int numNumbers = 65536;

    // Allocate an array numNumbers in length.
    // We want everything to start at 0, so use calloc.
    int *histogram = (int*) calloc(1, numNumbers * sizeof(int));

    for (int ii = 0; ii < 1000000; ii++) {
        histogram[rand() % numNumbers]++;
    }

    plotHistogram(histogram, numNumbers);

    free(histogram); histogram = NULL;
}
```

## Exercise

- Write a program that allocates an array of 26 characters
- Use a for loop to initialize the elements of the array to the letters 'a' through 'z'
  - Remember, characters are just numbers in C
  - So, if ii is between 0 and 25, you can write:  `myLetters[ii] = 'a' + ii;`
- Use a second for loop to print out the letters in the array
- Resize the array to hold the capital letters as well
- Use a for loop to initialize the second half of the array
  - You can write:  `myLetters[ii + NUM_LETTERS] = 'A' + ii;`
- Use another for loop to print out the full array
- Free the array and exit the program

[Table of Contents](.)
