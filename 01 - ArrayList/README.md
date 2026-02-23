# Lists

The lecture for this content is available on [YouTube](https://www.youtube.com/watch?v=aAGfUqERxuA).

- [Properties of a list](#properties-of-a-list)
- [List implementations](#list-implementations)

[Array Lists](#array-lists)
- [Array List definition](#array-list-definition)
- [Array List initialization](#array-list-initialization)
- [Array List insertion](#array-list-insertion)
- [Array List search](#array-list-search)
- [Array List remove](#array-list-remove)
- [Array List Iterator](#array-list-iterator)
- [Array List Iterator initialization](#array-list-iterator-initialization)
- [Array List Iterator iterating](#array-list-iterator-iterating)
- [Array List Iterator value](#array-list-iterator-value)
- [Iterating over an Array List](#iterating-over-an-array-list)
- [Example usage](#example-usage)
- [Exercise 1](#exercise-1)
- [Exercise 2](#exercise-2)
- [Exercise 3](#exercise-3)
- [Extra Credit](#extra-credit)

## Properties of a list

- The usual insertion use case for a list is adding items to the back
  - This should be an O(1) operation
  - This maintains insertion order
- The usual access pattern of a list is starting from the beginning and accessing each element from start to finish
  - This requires use of a list iterator
- Finding an item in a list requires starting from the beginning and traversing it until the desired value is found or the end of the list is reached (meaning the item is not in the list)
  - This means that searching a list is an O(n) operation
- Deleting an item from a list requires first finding it, so it's expected to be an O(n) operation
- Not all lists support changing an existing value in a list
  - For those that do, the existing value has to be found first, so modifying a value is expected to be an O(n) operation

## List implementations

- There are two (2) basic kinds of list implementations:
  - Array lists
  - Linked lists
- Array lists potentially take up more memory but they're simpler to implement
  - They don't have as many dynamic memory operations
- Linked lists are memory efficient but require more memory allocations and deallocations and more pointer manipulations
- Both meet all the basic qualifications of a list from an outside perspective

We will talk about array lists in this lesson

# Array Lists

## Array List definition

- The main container for an array list only needs to contain the list of elements, the size of the array, and the number of elements currently in the array

Example:
```C
typedef struct ArrayList {
    int *array;
    int arraySize;
    int listSize;
} ArrayList;
```

## Array List initialization

- The array of an array list should always be large enough to hold at least one more item than it currently does
- It's recommended to choose a starting size that's useful for the expected minimum case

Example:
```C
#define MIN_ARRAY_SIZE 4
ArrayList* arrayListCreate(void) {
    ArrayList *arrayList = (ArrayList*) malloc(sizeof(ArrayList));
    if (arrayList == NULL) {
        return NULL;
    }

    arrayList->array = (int*) malloc(MIN_ARRAY_SIZE * sizeof(int));
    if (arrayList->array == NULL) {
        free(arrayList); arrayList = NULL;
        return NULL;
    }

    arrayList->arraySize = MIN_ARRAY_SIZE;
    arrayList->listSize = 0;

    return arrayList;
}
```

## Array List insertion

- Inserting to the back of an array list just sets the last value in the array
- However, the insertion function also has to make sure that there will be enough space in the array for the next insertion before it exits

Example:
```C
int arrayListInsert(ArrayList *arrayList, int value) {
    if (arrayList == NULL) {
        return -1;
    } else if (arrayList->listSize == arrayList->arraySize) {
        // Array is full.  This means the previous attempt
        // to extend the array failed.  Nothing we can do.
        return -1;
    }

    arrayList->array[arrayList->listSize] = value;
    arrayList->listSize++;

    if (arrayList->listSize == arrayList->arraySize) {
        // Double the size of the array
        int newArraySize = arrayList->arraySize * 2;
        void *check = realloc(arrayList->array, newArraySize * sizeof(int));
        if (check == NULL) {
            // Out of memory.
            return -1;
        }

        arrayList->array = (int*) check;
        arrayList->arraySize = newArraySize;
    }

    return 0;
}
```

## Array List search

- Searching a list requires starting at the beginning and examining each element until the desired value is found
- The result of a search should be an address of some kind

Example:
```C
int arrayListSearch(ArrayList *arrayList, int value) {
    if (arrayList == NULL) {
        // Cannot search
        return -1;
    }

    for (int ii = 0; ii < arrayList->listSize; ii++) {
        if (arrayList->array[ii] == value) {
            return ii;
        }
    }

    // value not found
    return -1;
}
```

## Array List remove

- Removing a value requires first finding the value
- If found, the data from that point onward has to be shifted down

Example:
```C
int arrayListRemove(ArrayList *arrayList, int value) {
    int foundIndex = arrayListSearch(arrayList, value);
    if (foundIndex < 0) {
        // Value not in list
        return -1;
    }

    for (int ii = foundIndex; ii < (arrayList->listSize - 1); ii++) {
        arrayList->array[ii] = arrayList->array[ii + 1];
    }
    arrayList->listSize--;

    return 0;
}
```

## Array List Iterator

- An iterator for an Array List holds a pointer to the Array List and the index of the next value to return

Example:
```C
typedef struct ALIter {
    ArrayList *arrayList;
    int nextIndex;
} ALIter;
```

## Array List Iterator initialization

- If the Array List is non-empty, then initialization will return a pointer to a new Array List iterator
- If the Array List is empty, then initialization will return NULL

Example:
```C
ALIter* alIterCreate(ArrayList *arrayList) {
    if ((arrayList == NULL) || (arrayList->listSize == 0)) {
        return NULL;
    }

    ALIter *alIter = (ALIter*) malloc(sizeof(ALIter));
    if (alIter == NULL) {
        return NULL;
    }

    alIter->arrayList = arrayList;
    alIter->nextIndex = 0;

    return alIter;
}
```

## Array List Iterator iterating

- Getting the next value of an iterator should increment the next index
- If the next index is less than the list size then the function should return the Array List Iterator pointer
- If the next index is equal to the list size then the function should free the memory and return NULL

Example:
```C
ALIter* alIterNext(ALIter *alIter) {
    if (alIter == NULL) {
        return NULL;
    }

    alIter->nextIndex++;
    if (alIter->nextIndex == alIter->arrayList->listSize) {
        free(alIter); alIter = NULL;
        return NULL;
    }

    return alIter;
}
```

## Array List Iterator value

- Getting the value of an iterator should just be a matter of getting the value of the next index in the Array List
- The function should not need to check for a NULL Array List Iterator because this should be handled as the stop condition outside of the function

Example:
```C
int alIterValue(ALIter *alIter) {
    return alIter->arrayList->array[alIter->nextIndex];
}
```

## Iterating over an Array List

- The usual way of iterating over an Array List is with a for loop

Example:
```C
int arrayListPrint(ArrayList *arrayList) {
    if (arrayList == NULL) {
        return -1;
    }

    printf("ArrayList contents:\n")
    for (ALIter *alIter = alIterCreate(arrayList);
        alIter != NULL;
        alIter = alIterNext(alIter)
    ) {
        printf("%d\n", alIterValue(alIter));
    }

    return 0;
}
```

## Example usage

```C
#include "ArrayList.h"

int main(void) {
    ArrayList *arrayList = arrayListCreate();

    arrayListInsert(arrayList, 1);
    arrayListInsert(arrayList, 2);
    arrayListInsert(arrayList, 3);
    arrayListInsert(arrayList, 4);
    arrayListInsert(arrayList, 5);
    arrayListInsert(arrayList, 6);
    arrayListInsert(arrayList, 7);
    arrayListPrint(arrayList);

    arrayListRemove(arrayList, 4);
    arrayListPrint(arrayList);

    return 0;
}
```

## Exercise 1

- There is currently a bug with insert/remove in that if a value is inserted twice and then removed, only the first instance will be removed
- Modify arrayListInsert to check to see if the value is already in the list first and return an error if so

## Exercise 2

- There is currently no way to release the memory held by an ArrayList
  - This is very bad practice
- Create an arrayListDestroy function that takes a pointer to an ArrayList, frees all of its memory, and returns NULL
  - This should be the inverse of the arrayListCreate function
- Modify the main function so that it properly releases the memory of the ArrayList before returning

## Exercise 3

- Write an "arrayListGet" function that takes a pointer to an ArrayList and a desired index within the list to get
- Make it return a pointer to the element in the list if there are enough items in the list
  - Getting a pointer for an element in a list is written:  `&array[index]`
- Make it return NULL if the index specified is beyond the end of the list

## Extra Credit

- The ArrayList in this lesson holds int values
- Copy it to "ArrayListString" and change it to hold C string values
- For this, your internal array will be an array of char* pointers
  - You'll need to allocate memory for each string in the array
  - You'll need to use the strlen function and the strcpy function to make a copy of the values that are inserted into the list
  - Remember to account for the NULL byte at the end of the string when computing the size of a string!!
- You'll need to use the strcmp function to compare string values when searching
- Use the "%s" formatter with printf to print out the values in the arrayListPrint function

[Table of Contents](.)
