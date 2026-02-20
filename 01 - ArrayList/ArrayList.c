////////////////////////////////////////////////////////////////////////////////
//
//                       Copyright (c) 2026 Brian Card
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
//                                 Brian Card
//                       https://github.com/brian-card
//
////////////////////////////////////////////////////////////////////////////////

/// @file ArrayList.c
///
/// @brief Library implementation of the ArrayList.

// Standard C includes
#include <stdio.h>
#include <stdlib.h>

#include "ArrayList.h"

/// @def MIN_ARRAY_SIZE
///
/// @brief Minimum size we allow the array of the ArrayList to be
#define MIN_ARRAY_SIZE 4

/// @fn ArrayList* arrayListCreate(void)
///
/// @brief Allocate and initialize an ArrayList.
///
/// @return Returns a pointer to a allocated and initialized ArrayList on
/// success, NULL on failure.
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

/// @fn int arrayListInsert(ArrayList *arrayList, int value)
///
/// @brief Insert a new value at the end of an ArrayList.
///
/// @param arrayList A pointer to the ArrayList to append the value to.
/// @param value The value to append.
///
/// @return Returns 0 on success, -1 on failure.
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

/// @fn int arrayListSearch(ArrayList *arrayList, int value)
///
/// @brief Search an ArrayList for a given value.
///
/// @param arrayList A pointer to the ArrayList to search.
/// @param value The value to search for.
///
/// @return Returns the index of the value in the ArrayList's array if found, -1
/// if the value was not found in the list.
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

/// @fn int arrayListRemove(ArrayList *arrayList, int value)
///
/// @brief Remove a given value from an ArrayList.
///
/// @param arrayList A pointer to the ArrayList to remove a value from.
/// @param value The value to remove from the list.
///
/// @return Returns 0 if the value was successfully removed from the list, -1 if
/// the value was not in the list to start with.
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

/// @fn int arrayListPrint(ArrayList *arrayList)
///
/// @brief Print out all of the values in an ArrayList, with one value per line.
///
/// @param arrayList A pointer to the ArrayList to print the values from.
///
/// @return Returns 0 on success, -1 on failure.
int arrayListPrint(ArrayList *arrayList) {
    if (arrayList == NULL) {
        return -1;
    }

    printf("ArrayList contents:\n");
    for (ALIter *alIter = alIterCreate(arrayList);
        alIter != NULL;
        alIter = alIterNext(alIter)
    ) {
        printf("%d\n", alIterValue(alIter));
    }

    return 0;
}

/// @fn ALIter* alIterCreate(ArrayList *arrayList)
///
/// @brief Create an ArrayList iterator for an ArrayList.
///
/// @param arrayList A pointer to the ArrayList to create the iterator for.
///
/// @return Returns a pointer to an allocated and initialized ALIter on success,
/// NULL on failure.
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

/// @fn ALIter* alIterNext(ALIter *alIter)
///
/// @brief Prepare an ArrayList iterator for retrieving the next value.
///
/// @param alIter A pointer to the ALIter to prepare.
///
/// @return Returns a pointer to the prepared ALIter if there is another value
/// to retrieve, NULL if not.
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

/// @fn int alIterValue(ALIter *alIter)
///
/// @brief Retrieve the current value of the ArrayList iterator.
///
/// @param alIter A pointer to the AlIter to retrieve the value from.
///
/// @note It is assumed that the alIter parameter is non-NULL.  This function
/// does not check for that.  It is the responsibility of the caller to make
/// sure that the parameter is not NULL before calling this function.
///
/// @return Returns the current value of the ArrayList iterator.
int alIterValue(ALIter *alIter) {
    return alIter->arrayList->array[alIter->nextIndex];
}

