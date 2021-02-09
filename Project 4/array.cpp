#include <iostream>
#include <string>
#include <cassert>
using namespace std;

// Append value to the end of each of the n elements of the array and return n.
int appendToAll(string a[], int n, string value)
{
    if (n < 0) // a valid n cannot be negative
        return -1;
    
    for (int i = 0; i <n ; i++)
        a[i] = a[i] + value; // append value to the current string
    
    return n;
}

// Return the smallest position of a string in the array that is equal to target,
// return -1 if no such string is found.
int lookup(const string a[], int n, string target)
{
    if (n < 0) // a valid n cannot be negative
        return -1;
    
    for (int i = 0; i < n; i++)
    {
        if (a[i] == target) // the current string is equal to target
            return i;
    }
    
    return -1; // target is not found in the arrary, return -1
}

// Return the smallest position of a string in the array that is >= every string in the array,
// return -1 if the array has no interesting elements.
int positionOfMax(const string a[], int n)
{
    if (n < 0) // a valid n cannot be negative
        return -1;
    if (n == 0) // the array has no interesting elements
        return -1;
        
    string maxStr = a[0];
    int maxStrInd = 0;
    for (int i = 0; i < n ; i++)
    {
        if (a[i] > maxStr) // the current string is > the previous maxStr
        {
            maxStr = a[i]; // store the current string as the maxStr
            maxStrInd = i; // store the index of the current string as the maxStrInd
        }
    }
    return maxStrInd;
}

// Eliminate the item at position pos by moving all elements after it one place to the left，
// put the eliminated item into the last position of the array,
// return the original position of that item.
int rotateLeft(string a[], int n, int pos)
{
    if (n < 0) // a valid n cannot be negative
        return - 1;
    if (pos < 0) // a valid pos cannot be negative
        return -1;
    if (n <= pos) // pos is past the last element of the array
        return -1;
    
    string targetItem = a[pos];
    for (int i = pos; i < n; i++) // start at position pos
    {
        if (i == n-1) // the last position of the array
            a[i] = targetItem; // put the eliminated item into the last position of the array
        else
            a[i] = a[i+1]; // move each element one place to the left
    }
    return pos;
}

// Return the number of sequences of one or more consecutive identical items in a.
int countRuns(const string a[], int n)
{
    if (n < 0) // a valid n cannot be negative
        return -1;
    
    int count = 0;
    string sequenceId;
    for (int i = 0; i < n; i++)
    {
        string curItem = a[i];
        
        if (i == 0) // initialize the variables
        {
            sequenceId = curItem;
            count += 1;
        }
        
        if (curItem != sequenceId) // curItem starts a new sequence
        {
            sequenceId = curItem; // store the current string as the sequenceId
            count += 1; // increment count
        }
    }
    return count;
}

// Reverse the order of the elements of the array and return n.
int flip(string a[], int n)
{
    if (n < 0) // a valid n cannot be negative
        return -1;
    
    for (int i = 0; i < n/2; i++) // swap elements up to the middle position
    {
        // Swap elements
        string temp = a[i];
        a[i] = a[n-1-i];
        a[n-1-i] = temp;
    }
    return n;
}

// Return the position of the first corresponding elements of a1 and a2 that are not equal,
// return min(n1, n2) if a1 and a2 are equal up to the point when one or both runs out.
int differ(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0) // a valid n1 and a valid n2 cannot be negative
        return -1;
    
    int i = 0;
    while (i < n1 && i < n2)
    {
        if (a1[i] != a2[i]) // at pos i, the corresponidng elements of a1 and a2 are not equal
            return i;
        i++;
    }
    
    // The arrays are equal up to the point when one or both runs out, return the smaller value between n1 and n2
    if (n1 < n2)
        return n1;
    else
        return n2;
}

// Return the smallest beginning position of a subsequence of a1 that is exactly the same as a2,
// return -1 if no such subsequence is found.
int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0) // a valid n1 and a valid n2 cannot be negative
        return -1;
    if (n1 < n2) // if a2 is longer than a1, a1 cannot contain a2
        return -1;
    if (n2 == 0) // a sequence of 0 element is a subsequence of every sequence at pos 0
        return 0;
    
    for (int i = 0; i <= n1-n2; i++) // loop through each possible beginning position
    {
        // For each possible beginning position, loop through each element in a2
        for (int j = 0; j < n2; j++)
        {
            if (a1[i+j] != a2[j]) // the corresponding elements do not match
                break;
            if (j == n2-1) // all elements have been examined, this is a correct subsequence
                return i;
        }
    }
    return -1; // no such subsequence is found
}

// Return the smallest position in a1 of an element that is equal to any of the n2 elements in a2,
// return -1 if no element of a1 is equal to any element of a2.
int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0) // a valid n1 and a valid n2 cannot be negative
        return -1;
    
    for (int i = 0; i < n1; i++)
    {
        // For each element in a1, loop through each element in a2.
        for (int j = 0; j < n2; j++)
        {
            if (a1[i] == a2[j]) // the current a1 element is equal to an a2 element
                return i;
        }
    }
    return -1; // no element of a1 is equal to any element of a2
}

// Eliminate the item at position pos by moving all elements before it one place to the right，
// put the eliminated item into the first position of the array.
void rotateRight(string a[], int pos)
{
    string targetItem = a[pos];
    for (int i = pos; i >= 0; i--)
    {
        if (i == 0)
            a[i] = targetItem; // put the eliminated item into the first position of the array
        else
            a[i] = a[i-1]; // move each element one place to the right
    }
}

// Rearrange the array so that all elements that are < divider come before all other elements,
// and all elements that are > divider come after all other elements,
// then, return the position of the first element that is not < divider,
// return n if no such element is found.
int divide(string a[], int n, string divider)
{
    if (n < 0) // a valid n cannot be negative
        return -1;
    
    // Rearrange the array
    int curN = n;
    for (int i = 0; i < curN; i++)
    {
        if (a[i] < divider) // a[i] is < divider, thus it should come before all other elements
            rotateRight(a, i); // put a[i] into the first position of the array
        if (a[i] > divider) // a[i] is > divider, thus it should come after all other elements
        {
            rotateLeft(a, curN, i); // put a[i] into the last position of the array
            i -= 1; // all elements after i have been moved one place to the left, so should i be
            curN -= 1; // the last element was just put, no need to check it later
        }
    }
    
    // Return the position of the first element that is not < divider
    for (int i = 0; i < n; i++)
    {
        if (a[i] >= divider) // the current element is not < divider
            return i;
    }
    return n; // no such element is found
}

// Check if two arrays are identical
void matchArrays(string a[], string b[], int n)
{
    for (int i = 0; i < n; i++)
    {
        assert(a[i] == b[i]);
    }
}

int main()
{
    // Test appendToAll()
    string a[8] = { "martha", "mark", "lindsey", "sara", "spark", "ava", "mike", "" };
    assert(appendToAll(a, -2, "!") == -1); // n is negative
    assert(appendToAll(a, 0, "!") == 0); // n is 0, should return 0 and leave the array unchanged
    string a1[8] = { "martha", "mark", "lindsey", "sara", "spark", "ava", "mike", "" };
    matchArrays(a, a1, 8);
    assert(appendToAll(a, 8, "!") == 8); // test for correctness
    string a2[8] = { "martha!", "mark!", "lindsey!", "sara!", "spark!", "ava!", "mike!", "!" };
    matchArrays(a, a2, 8);
    assert(appendToAll(a, 4, "?") == 4); // only the first 4 elements should be changed
    string a3[8] = { "martha!?", "mark!?", "lindsey!?", "sara!?", "spark!", "ava!", "mike!", "!" };
    matchArrays(a, a3, 8);
    cout << "Tests for appendToAll() succeeded." << endl;

    // Test lookup()
    string b[9] = { " ", "martha", "mark", "lindsey", "sara", "spark", "ava", "mike", "" };
    assert(lookup(b, -2, "mark") == -1); // n is negative
    assert(lookup(b, 0, "mark") == -1); // n is 0, should return -1
    assert(lookup(b, 9, "mark") == 2); // test for correctness
    assert(lookup(b, 9, "") == 8); // test for correctness
    b[7] = "";
    assert(lookup(b, 9, "") == 7); // more than one target string in the array, should return the smallest position
    assert(lookup(b, 9, "!") == -1); // no match
    assert(lookup(b, 4, "sara") == -1); // only the first 4 elements should be checked
    cout << "Tests for lookup() succeeded." << endl;
    
    // Test positionOfMax()
    string c[9] = { " ", "martha", "mark", "lindsey", "sara", "ava", "spark", "mike", "" };
    assert(positionOfMax(c, -2) == -1); // n is negative
    assert(positionOfMax(c, 0) == -1); // n is 0, should return -1
    assert(positionOfMax(c, 9) == 6); // test for correctness
    c[5] = "spark";
    assert(positionOfMax(c, 9) == 5); // more than one max string, should return the smallest position
    assert(positionOfMax(c, 5) == 4); // only the first 5 elements should be checked
    assert(positionOfMax(c, 2) == 1); // only the first 2 elements should be checked
    cout << "Tests for positionOfMax() succeeded." << endl;

    // Test rotateLeft()
    string d[8] = { "martha", "mark", "lindsey", "sara", "spark", "ava", "mike", "" };
    assert(rotateLeft(d, -2, 2) == -1); // n is negative
    assert(rotateLeft(d, 8, -2) == -1); // pos is negative
    assert(rotateLeft(d, 3, 6) == -1); // pos >= n
    assert(rotateLeft(d, 0, 0) == -1); // pos >= n
    assert(rotateLeft(d, 8, 2) == 2); // test for correctness
    string d1[8] = { "martha", "mark", "sara", "spark", "ava", "mike", "", "lindsey" };
    matchArrays(d, d1, 8);
    assert(rotateLeft(d, 6, 4) == 4); // only the first 6 elements should be changed
    string d2[8] = { "martha", "mark", "sara", "spark", "mike", "ava", "", "lindsey" };
    matchArrays(d, d2, 8);
    cout << "Tests for rotateLeft() succeeded." << endl;
    
    // Test countRuns()
    string e[10] = { "today", "today", "tomorrow", "", "", "", " ", "cs", "31", "31" };
    assert(countRuns(e, -2) == -1); // n is negative
    assert(countRuns(e, 0) == 0); // n is 0, should return 0
    assert(countRuns(e, 10) == 6); // test for correctness
    assert(countRuns(e, 8) == 5); // only the first 8 elements should be checked
    assert(countRuns(e, 1) == 1); // only the first element should be checked
    cout << "Tests for countRuns() succeeded." << endl;
    
    // Test flip()
    string f[9] = { " ", "martha", "mark", "lindsey", "sara", "spark", "ava", "mike", "" };
    assert(flip(f, -2) == -1); // n is negative
    assert(flip(f, 0) == 0); // n is 0, should return 0 and leave the array unchanged
    string f1[9] = { " ", "martha", "mark", "lindsey", "sara", "spark", "ava", "mike", "" };
    matchArrays(f, f1, 9);
    assert(flip(f, 9) == 9); // test for correctness
    string f2[9] = { "", "mike", "ava", "spark", "sara", "lindsey", "mark", "martha", " " };
    matchArrays(f, f2, 9);
    assert(flip(f, 5) == 5); // only the first 5 elements should be changed
    string f3[9] = { "sara", "spark", "ava", "mike", "", "lindsey", "mark", "martha", " " };
    matchArrays(f, f3, 9);
    assert(flip(f, 1) == 1); // only the first element should be changed
    string f4[9] = { "sara", "spark", "ava", "mike", "", "lindsey", "mark", "martha", " " };
    matchArrays(f, f4, 9);
    cout << "Tests for flip() succeeded." << endl;
        
    // Test differ()
    string g1[7] = { "martha", "mark", "lindsey", "joe", "susan", "", "kamala" };
    string g2[4] = { "martha", "mark", "lindsey", "sara" };
    assert(differ(g1, -2, g2, 4) == -1); // n1 is negative
    assert(differ(g1, 7, g2, -2) == -1); // n2 is negative
    assert(differ(g1, 0, g2, 4) == 0); // n1 is 0, should return 0
    assert(differ(g1, 7, g2, 0) == 0); // n2 is 0, should return 0
    assert(differ(g1, 7, g2, 4) == 3); // test for correctness
    assert(differ(g1, 2, g2, 3) == 2); // arrays are equal until g1 runs out
    assert(differ(g1, 1, g2, 1) == 1); // arrays are equal until both run out
    cout << "Tests for differ() succeeded." << endl;

    // Test subsequence()
    string h[10] = { "today", "today", "tomorrow", "", "", "", " ", "cs", "31", "31" };
    string h1[2] = { "today", "tomorrow" };
    assert(subsequence(h, -2, h1, 2) == -1); // n1 is negative
    assert(subsequence(h, 10, h1, -2) == -1); // n2 is negative
    assert(subsequence(h, 0, h1, 2) == -1); // n1 is 0, should return -1
    assert(subsequence(h, 10, h1, 20) == -1); // n2 is 0, should return -1
    assert(subsequence(h, 10, h1, 2) == 1); // test for correctness
    string h2[2] = { "", "" };
    assert(subsequence(h, 10, h2, 2) == 3); // more than one subsequence, should return the smallest position
    assert(subsequence(h, 4, h2, 2) == -1); // only the first 4 elements should be checked
    string h3[2] = { " ", "" };
    assert(subsequence(h, 10, h3, 2) == -1); // no match
    assert(subsequence(h, 10, h3, 1) == 6); // {" "} is the subsequence
    cout << "Tests for subsequence() succeeded." << endl;
    
    // Test lookupAny()
    string i[10] = { "today", "today", "tomorrow", "", "", "", " ", "cs", "31", "31" };
    string i1[3] = { "Monday", "CS", "today" };
    assert(lookupAny(i1, -2, i, 10) == -1); // n1 is negative
    assert(lookupAny(i1, 3, i, -2) == -1); // n2 is negative
    assert(lookupAny(i1, 0, i, 10) == -1); // n1 is 0, should return -1
    assert(lookupAny(i1, 3, i, 0) == -1); // n2 is 0, should return -1
    assert(lookupAny(i1, 3, i, 10) == 2); // test for correctness
    assert(lookupAny(i1, 2, i, 10) == -1); // only the first 2 elements in i1 should be checked, there is no match
    i1[1] = "cs";
    assert(lookupAny(i1, 3, i, 10) == 1); // both "cs" and "today" can match, should return the smallest position
    assert(lookupAny(i1, 3, i, 7) == 2); // only the first 7 elements in i should be checked
    string i2[3] = { "Monday", "Cs", "Today" };
    assert(lookupAny(i2, 3, i, 10) == -1); // no match
    cout << "Tests for lookupAny() succeeded." << endl;
    
    // Test divide()
    string j[10] = { "ae", "b", "c", "aa", "e", "a", "ab", "ac", "d", "az" };
    assert(divide(j, -2, "af") == -1); // n is negative
    assert(divide(j, 0, "af") == 0); // n is 0, should return 0
    assert(divide(j, 10, "af") == 5); // test for correctness
    assert(divide(j, 10, "b") == 6); // test for correctness
    assert(divide(j, 10, "f") == 10); // no element >= divider
    string j1[10] = { "ae", "b", "c", "aa", "e", "a", "ab", "ac", "d", "az" };
    assert(divide(j1, 4, "ca") == 4); // only the first 4 elements should be changed and checked, there is no element >= divider
    cout << "Tests for divide() succeeded." << endl;
    
    cout << "All tests succeeded." << endl;
}
