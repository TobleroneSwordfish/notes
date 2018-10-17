//file for testing the list API
#include "list.h"
#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"

list *fromString(const char *string)
{
    list *output = newList();
    int currentPos = -1; //set to -1 literally just because I hate warnings
    int len = strlen(string);
    for (int i = len - 1; i >= 0; i--)
    {
        if (string[i] != '|')
        {
            insertAfter(output, string[i] - '0');
        }
        else
        {
            currentPos = i;
        }
    }
    for (int i = 0; i < currentPos; i++)
    {
        forward(output);
    }
    return output;
}

char *toString(list *input)
{
    int length = 0;
    int currentPosition = 0;
    while (!atStart(input))
    {
        backward(input);
        currentPosition++;
    }
    while (!atEnd(input))
    {
        forward(input);
        length++;
    }
    char *output = malloc(length * sizeof(char));
    start(input);
    if (length != 0)
    {
        for (int i = 0; i < length + 1; i++)
        {
            if (i == currentPosition)
            {
                output[i] = '|';
                i++;
            }
            output[i] = getAfter(input) + '0';
            if (i == currentPosition - 1)
            {
                output[i + 1] = '|';
                i++;
            }
            forward(input);
        }
    }
    else
    {
        output = "|";
    }
    start(input);
    for (int i = 0; i < currentPosition; i++)
    {
        forward(input);
    }
    return output;
}

bool compare(list* l, char* s)
{
    return strcmp(toString(l), s) == 0;
}

void testNew()
{
    list *test = newList();
    assert(compare(test, "|"));
    free(test);
}

void testGet()
{
    list *test = fromString("12|3");
    assert(getBefore(test) == 2 && getAfter(test) == 3);
    free(test);
}

void testInsertBefore()
{
    list *test = fromString("1234|");
    insertBefore(test, 5);
    assert(compare(test, "12345|"));
    free(test);
}

void testInsertAfter()
{
    list *test = fromString("12|34");
    insertAfter(test, 5);
    assert(compare(test, "12|534"));
    free(test);
}

void testStartEnd()
{
    list *test = fromString("123|456");
    end(test);
    assert(compare(test, "123456|"));
    start(test);
    assert(compare(test, "|123456"));
    free(test);
}

void testAtStartAtEnd()
{
    list *test = fromString("|12345");
    assert(atStart(test));
    end(test);
    assert(atEnd(test));
    free(test);
}

void testForwardBackward()
{
    list *test = fromString("1|23");
    forward(test);
    assert(compare(test, "12|3"));
    backward(test);
    backward(test);
    assert(compare(test, "|123"));
    free(test);
}

void testSet()
{
    list *test = fromString("1|23");
    setBefore(test, 9);
    assert(compare(test, "9|23"));
    setAfter(test, 7);
    assert(compare(test, "9|73"));
    free(test);
}

void testDelete()
{
    list *test = fromString("12|3");
    deleteBefore(test);
    assert(compare(test, "1|3"));
    deleteAfter(test);
    assert(compare(test, "1|"));
    free(test);
}

void scenarioOne()
{
    printf("running scenario one\n");
    list *test = newList();
    printf("list created\n");
    insertBefore(test, 42);
    printf("42 inserted before\n");
    item fourtyTwo = getBefore(test);
    assert(fourtyTwo == 42);
    printf("42 found before\n");
    backward(test);
    printf("list position moved backward\n");
    assert(getAfter(test) == 42);
    printf("42 found after\n");
    insertAfter(test, 21);
    printf("21 inserted after\n");
    assert(getAfter(test) == 21);
    printf("21 found after\n");
    forward(test);
    printf("list position moved forward\n");
    assert(getBefore(test) == 21);
    printf("21 found before\n");
    assert(getAfter(test) == 42);
    printf("42 found after\n");
    start(test);
    printf("reset list position to start\n");
    deleteAfter(test);
    printf("deleted after\n");
    assert(getAfter(test) == 42);
    printf("42 found after\n");
    forward(test);
    printf("list position moved forward\n");
    deleteBefore(test);
    printf("deleted before\n");
    assert(atStart(test) && atEnd(test));
    printf("list is both at start and end, ergo list is empty\n");

}

void scenarioTwo()
{
    printf("\nrunning scenario two\n");
    list *test = newList();
    insertBefore(test, 1);
    insertBefore(test, 2);
    insertBefore(test, 3);
    printf("inserted 1, 2, 3 into the list ");
    assert(atEnd(test));
    printf("putting current position at end\n");
    printf("Running through the list backwards: \n");
    while (!atStart(test))
    {
        backward(test);
        printf("%d\n", getAfter(test));
    }
    printf("and forwards again: \n");
    while (!atEnd(test))
    {
        forward(test);
        printf("%d\n", getBefore(test));
    }
}

//Alongside the standard function tests, I've set up a couple of test scenarios that run through step by step, constantly asserting to test everything

int main(int n, char *args[])
{
    printf("Test module running\n");
    testNew();
    testInsertBefore();
    testInsertAfter();
    testStartEnd();
    testAtStartAtEnd();
    testForwardBackward();
    testGet();
    testSet();
    testDelete();
    scenarioOne();
    scenarioTwo();
    printf("Tests complete, excellent work Tenno\n");
}
