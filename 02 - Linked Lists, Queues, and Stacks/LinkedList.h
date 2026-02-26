///////////////////////////////////////////////////////////////////////////////
///
/// @author            Brian Card
/// @date              02.25.2026
///
/// @file              LinkedList.h
///
/// @brief             Linked list implementation in C.
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

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#ifdef __cplusplus
extern "C"
{
#endif

/// @struct ListNode
///
/// @brief Individual node component of a linked list.
///
/// @param next Pointer to the next ListNode in the list.
/// @param prev Pointer to the previous ListNode in the list.
/// @param value Pointer to the value that is at this node.
typedef struct ListNode {
    struct ListNode *next;
    struct ListNode *prev;
    void *value;
} ListNode;

/// @struct LinkedList
///
/// @brief Base container for a linked list.
///
/// @param compare Function pointer to the function that will compare two values
///   in the list.
/// @param head Pointer to the first ListNode in the list.
/// @param tail Pointer to the last ListNode in the list.
/// @param size Number of elements in the list.
typedef struct LinkedList {
    int (*compare)(const void*, const void*);
    ListNode *head;
    ListNode *tail;
    int size;
} LinkedList;

// Base LinkedList prototypes
LinkedList* linkedListCreate(int (*compare)(const void*, const void*));
int linkedListInsertFront(LinkedList *linkedList, void *value, int size);
int linkedListInsertBack(LinkedList *linkedList, void *value, int size);
ListNode* linkedListSearch(LinkedList *linkedList, const void *value);
int linkedListRemoveValue(LinkedList *linkedList, const void *value);
void* linkedListPeekFront(LinkedList *linkedList);
void* linkedListPeekBack(LinkedList *linkedList);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LINKED_LIST_H

