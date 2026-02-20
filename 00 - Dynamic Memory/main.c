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

#include <stdio.h>
#include <stdlib.h>

#define NUM_LETTERS 26
int main(void) {
    char *myLetters = (char*) malloc(NUM_LETTERS * sizeof(char));
    if (myLetters == NULL) {
        printf("Error:  Could not allocate memory for myLetters!\n");
        return 1;
    }

    for (int ii = 0; ii < NUM_LETTERS; ii++) {
        myLetters[ii] = 'a' + ii;
    }

    for (int ii = 0; ii < NUM_LETTERS; ii++) {
        printf("myLetters[%d] = %c\n", ii, myLetters[ii]);
    }

    void *check = realloc(myLetters, (NUM_LETTERS * 2) * sizeof(char));
    if (check == NULL) {
        printf("Error:  Could not reallocate memory for myLetters!\n");
        free(myLetters); myLetters = NULL;
        return 1;
    }
    myLetters = (char*) check;

    for (int ii = 0; ii < NUM_LETTERS; ii++) {
        myLetters[ii + NUM_LETTERS] = 'A' + ii;
    }

    for (int ii = 0; ii < (NUM_LETTERS * 2); ii++) {
        printf("myLetters[%d] = %c\n", ii, myLetters[ii]);
    }

    free(myLetters); myLetters = NULL;

    return 0;
}
