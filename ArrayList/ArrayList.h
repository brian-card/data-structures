///////////////////////////////////////////////////////////////////////////////
///
/// @author            Brian Card
/// @date              02.19.2026
///
/// @file              ArrayList.h
///
/// @brief             Array-based implementation of a list in C.
///
/// @copyright
///                      Copyright (c) 2026 Brian Card
///
/// Permission is hereby granted, free of charge, to any person obtaining a
/// copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation
/// the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the
/// Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included
/// in all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
/// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
/// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
/// DEALINGS IN THE SOFTWARE.
///
///                                Brian Card
///                      https://github.com/brian-card
///
///////////////////////////////////////////////////////////////////////////////

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#ifdef __cplusplus
extern "C"
{
#endif

/// @struct ArrayList
///
/// @brief Base container for an array-based implementation of a list.
///
/// @var array Pointer to the dynamic memory for the array that holds the
///   elements of the list.
/// @var arraySize The number of elements that the array can hold.
/// @var listSize The number of elements currently in the array.
typedef struct ArrayList {
    int *array;
    int arraySize;
    int listSize;
} ArrayList;

/// @struct ALIter
///
/// @brief Implementation of an iterator for an ArrayList.
///
/// @var arrayList A pointer to the ArrayList currently being iterated over.
/// @var nextIndex The index of the next element in the ArrayList to return.
typedef struct ALIter {
    ArrayList *arrayList;
    int nextIndex;
} ALIter;

// Base ArrayList prototypes
ArrayList* arrayListCreate(void);
int arrayListInsert(ArrayList *arrayList, int value);
int arrayListSearch(ArrayList *arrayList, int value);
int arrayListRemove(ArrayList *arrayList, int value);
int arrayListPrint(ArrayList *arrayList);

// ArrayList iterator prototypes
ALIter* alIterCreate(ArrayList *arrayList);
ALIter* alIterNext(ALIter *alIter);
int alIterValue(ALIter *alIter);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ARRAY_LIST_H

