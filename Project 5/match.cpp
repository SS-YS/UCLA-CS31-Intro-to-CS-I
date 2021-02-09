#include <iostream>
#include <cassert>
#include <cctype>
#include <cstring>
using namespace std;

const int MAX_WORD_LENGTH = 20;
const int MAX_DOCUMENT_LENGTH = 250;

// Remove the match rule at pos n by moving all rules after it one place to the left.
// Decrement the number of match rules by one and return this value.
int removeRule(char wordin[][MAX_WORD_LENGTH+1], char wordout[][MAX_WORD_LENGTH+1], int n, int nRules)
{
    for (int i = n; i < nRules - 1; i++) // start at position n
    {
        // Move every rule one place to the left
        strcpy(wordin[i], wordin[i+1]);
        strcpy(wordout[i], wordout[i+1]);
    }
    nRules -= 1; // decrement the number of match rules
    return nRules;
}

/*
 Make the collection of match rules in clean form:
    Transform every upper case letter into its lower case equivalent.
    Remove every match rule for which any of the following holds:
        The win word is the empty string;
        The win and wout words are the same.
        A word contains a character that is not a letter;
    If a one-word rule has the same win as other rules, remove all such other rules.
    If a two-word rule has both the same win and wout as other two-word rules, remove all such other two-word rules.
 Return the number of match rules in the clean form of the collection.
*/
int cleanupRules(char wordin[][MAX_WORD_LENGTH+1], char wordout[][MAX_WORD_LENGTH+1], int nRules)
{
    if (nRules == 0)
        return 0;
    if (nRules < 0) // treat a negative nRules as if it were 0
        return 0;
    
    // Transform every upper case letter into its lower case equivalent.
    for (int i = 0; i < nRules; i++)
    {
        for (int j = 0; wordin[i][j] != '\0'; j++)
            wordin[i][j] = tolower(wordin[i][j]);
        for (int j = 0; wordout[i][j] != '\0'; j++)
            wordout[i][j] = tolower(wordout[i][j]);
    }
    
    for (int i = 0; i < nRules; i++) // traverse every match rule
    {
        bool shouldBeRemoved = false; // whether the current match rule should be removed
        
        if (strcmp(wordin[i], "") == 0) // the win word is the empty string
            shouldBeRemoved = true;
        else if (strcmp(wordin[i], wordout[i]) == 0) // the win and wout words are the same
            shouldBeRemoved = true;
        else
        {
            for (int j = 0; wordin[i][j] != '\0'; j++)
            {
                if (!isalpha(wordin[i][j])) // the win word contains a non-alphabetic character
                    shouldBeRemoved = true;
            }
            for (int j = 0; wordout[i][j] != '\0'; j++)
            {
                if (!isalpha(wordout[i][j])) // the wout word contains a non-alphabetic character
                    shouldBeRemoved = true;
            }
        }
        if (shouldBeRemoved)
        {
            nRules = removeRule(wordin, wordout, i, nRules); // remove the current match rule and decrement nRules
            i -= 1; // the next match rule to be examined has been moved one place to the left
        }
        
        else
        {
            for (int j = 0; j < nRules; j++) // traverse every other match rule
            {
                if (i == j)
                    continue;
                if (strcmp(wordout[i], "") == 0 && strcmp(wordin[i], wordin[j]) == 0) // the current one-word rule has the same win as another rule
                {
                    nRules = removeRule(wordin, wordout, j, nRules); // remove that another rule and decrement nRules
                    j -= 1; // the next match rule to be examined has been moved one place to the left
                    if (i > j)
                        i -= 1; // the current match rule has been moved one place to the left
                }
                if (strcmp(wordout[i], "") != 0 && strcmp(wordin[i], wordin[j]) == 0 && strcmp(wordout[i], wordout[j]) == 0) // the current two-word rule has both the same win and wout as another two-word rule
                {
                    nRules = removeRule(wordin, wordout, j, nRules); // remove that another two-word rule and decrement nRules
                    j -= 1; // the next match rule to be examined has been moved one place to the left
                    if (i > j)
                        i -= 1; // the current match rule has been moved one place to the left
                }
            }
        }
    }
    return nRules;
}

/*
 Return the score of the document, which is the number of rules in the given collection that the document matches.
 A document matches a one-word rule if the document contains the word win.
 A document matches a two-word rule if the document contains win and does not contain wout.
*/
int determineScore(const char document[], const char wordin[][MAX_WORD_LENGTH+1], const char wordout[][MAX_WORD_LENGTH+1], int nRules)
{
    if (nRules == 0)
        return 0;
    if (nRules < 0) // treat a negative nRules as if it were 0
        return 0;
    
    char newDocument[MAX_DOCUMENT_LENGTH/2][MAX_DOCUMENT_LENGTH+1] = {}; // store all the words in the correct form seperately
    int iNewDocument = 0;
    int iDocument = 0;
    while (document[iDocument] != '\0') // traverse every word in document
    {
        while (document[iDocument] == ' ')
            iDocument += 1; // skip space characters
        
        char curWord[MAX_DOCUMENT_LENGTH+1] = ""; // store the current word
        int iCurWOrd = 0;
        while (document[iDocument] != ' ' && document[iDocument] != '\0') // traverse every character that belongs to the current word
        {
            if (isalpha(document[iDocument]))
            {
                curWord[iCurWOrd] = tolower(document[iDocument]); // add the current character to the current word
                iCurWOrd += 1;
            }
            iDocument += 1;
        }
        
        if (strcmp(curWord, "") != 0) // the current word is not an empty string
        {
            strcpy(newDocument[iNewDocument], curWord);
            iNewDocument += 1;
        }
    }
    
    // Calculate score
    int score = 0;
    for (int i = 0; i < nRules; i++) // traverse every match rule
    {
        bool containWin = false;
        bool containWout = false;
        for (int j = 0; j < MAX_DOCUMENT_LENGTH/2; j++) // traverse every word in newDocument
        {
            if (strcmp(wordin[i], newDocument[j]) == 0) // newDocument contains the current win
                containWin = true;
            if (strcmp(wordout[i], newDocument[j]) == 0) // newDocument contains the current wout
                containWout = true;
        }
        if (strcmp(wordout[i], "") == 0 && containWin) // newDocument matches the current one-word rule
            score += 1;
        if (strcmp(wordout[i], "") != 0 && containWin && ! containWout) // newDocument matches the current two-word rule
            score += 1;
    }
    return score;
}

// Check if every rule in arrInCorrect, arrOutCorrect is in arrIn, arrOut
void matchRules(const char arrIn[][MAX_WORD_LENGTH+1], const char arrOut[][MAX_WORD_LENGTH+1], const char arrInCorrect[][MAX_WORD_LENGTH+1], const char arrOutCorrect[][MAX_WORD_LENGTH+1], int n)
{
    for (int i = 0; i < n; i++)
    {
        bool match = false;
        for (int j = 0; j < n; j++)
        {
            if (strcmp(arrInCorrect[i], arrIn[j]) == 0 && strcmp(arrOutCorrect[i], arrOut[j]) == 0)
                match = true;
        }
        assert(match);
    }
}

int main() {
    // Test cleanupRules()
    char aIn[3][MAX_WORD_LENGTH+1] = { "furious", "boy", "sports" };
    char aOut[3][MAX_WORD_LENGTH+1] = { "", "emily", "family" };
    assert(cleanupRules(aIn, aOut, -5) == 0); // nRules is negative
    assert(cleanupRules(aIn, aOut, 0) == 0); // nRules is zero
    assert(cleanupRules(aIn, aOut, 3) == 3); // wordin and wordout already in clean form
    matchRules(aIn, aOut, aIn, aOut, 3);
    char bIn[3][MAX_WORD_LENGTH+1] = { "furious*", "boy", "sports" };
    char bOut[3][MAX_WORD_LENGTH+1] = { "", "emily", " family" };
    assert(cleanupRules(bIn, bOut, 3) == 1); // two words contain a non-alphabetic character
    char bInCorrect[1][MAX_WORD_LENGTH+1] = { "boy" };
    char bOutCorrect[1][MAX_WORD_LENGTH+1] = { "emily" };
    matchRules(bIn, bOut, bInCorrect, bOutCorrect, 1);
    char cIn[3][MAX_WORD_LENGTH+1] = { "furious*", "", "sports" };
    char cOut[3][MAX_WORD_LENGTH+1] = { "", "emily", "family" };
    assert(cleanupRules(cIn, cOut, 3) == 1); // a win word is the empty string
    char cInCorrect[1][MAX_WORD_LENGTH+1] = { "sports" };
    char cOutCorrect[1][MAX_WORD_LENGTH+1] = { "family" };
    matchRules(cIn, cOut, cInCorrect, cOutCorrect, 1);
    char dIn[3][MAX_WORD_LENGTH+1] = { "furious", "", "sports" };
    char dOut[3][MAX_WORD_LENGTH+1] = { "", "emily", "sports" };
    assert(cleanupRules(dIn, dOut, 3) == 1); // a match rule has the same win and wout words
    char dInCorrect[1][MAX_WORD_LENGTH+1] = { "furious" };
    char dOutCorrect[1][MAX_WORD_LENGTH+1] = { "" };
    matchRules(dIn, dOut, dInCorrect, dOutCorrect, 1);
    char eIn[3][MAX_WORD_LENGTH+1] = { "furious*", "", "sports" };
    char eOut[3][MAX_WORD_LENGTH+1] = { "", "emily", "family" };
    assert(cleanupRules(eIn, eOut, 2) == 0); // only the first two match rules should be examined
    char fIn[4][MAX_WORD_LENGTH+1] = { "the", "that", "the", "CS" };
    char fOut[4][MAX_WORD_LENGTH+1] = { "warriors", "take", "", "31" };
    assert(cleanupRules(fIn, fOut, 4) == 2); // a one-word rule has the same win as another two-word rule
    char fInCorrect[2][MAX_WORD_LENGTH+1] = { "that", "the" };
    char fOutCorrect[2][MAX_WORD_LENGTH+1] = { "take", "" };
    matchRules(fIn, fOut, fInCorrect, fOutCorrect, 2);
    char gIn[4][MAX_WORD_LENGTH+1] = { "the", "that", "the", "CS" };
    char gOut[4][MAX_WORD_LENGTH+1] = { "", "take", "", "31" };
    assert(cleanupRules(gIn, gOut, 4) == 2); // a one-word rule has the same win as another one-word rule
    char gInCorrect[2][MAX_WORD_LENGTH+1] = { "that", "the" };
    char gOutCorrect[2][MAX_WORD_LENGTH+1] = { "take", "" };
    matchRules(gIn, gOut, gInCorrect, gOutCorrect, 2);
    char hIn[5][MAX_WORD_LENGTH+1] = { "the", "that", "the", "that", "cs" };
    char hOut[5][MAX_WORD_LENGTH+1] = { "warriors", "take", "", "take", "31" };
    assert(cleanupRules(hIn, hOut, 5) == 2); // a two-word rule has both the same win and wout as another two-word rule
    char hInCorrect[2][MAX_WORD_LENGTH+1] = { "the", "that" };
    char hOutCorrect[2][MAX_WORD_LENGTH+1] = { "", "take" };
    matchRules(hIn, hOut, hInCorrect, hOutCorrect, 2);
    char iIn[5][MAX_WORD_LENGTH+1] = { "tHe", "That", "tHE", "tHat", "CS" };
    char iOut[5][MAX_WORD_LENGTH+1] = { "wArrIors", "take", "", "TakE", "31" };
    assert(cleanupRules(iIn, iOut, 5) == 2); // match rules contain upper case letters
    char iInCorrect[2][MAX_WORD_LENGTH+1] = { "the", "that" };
    char iOutCorrect[2][MAX_WORD_LENGTH+1] = { "", "take" };
    matchRules(iIn, iOut, iInCorrect, iOutCorrect, 2);
    char jIn[12][MAX_WORD_LENGTH+1] = { "dog", "(mike)", "family", "charm", "confused", "charm", "ties", "", "charm", "CouPle", "refuse", "COUple" };
    char jOut[12][MAX_WORD_LENGTH+1] = { "walking", "older", "last", "project", "confused", "", "family", "frightened", "", "LovEs", "", "loves" };
    assert(cleanupRules(jIn, jOut, 12) == 6); // test for correctness
    char jInCorrect[6][MAX_WORD_LENGTH+1] = { "ties", "dog", "family", "refuse", "couple", "charm" };
    char jOutCorrect[6][MAX_WORD_LENGTH+1] = { "family", "walking", "last", "", "loves", "" };
    matchRules(jIn, jOut, jInCorrect, jOutCorrect, 6);
    char kIn[10][MAX_WORD_LENGTH+1] = { "dog", "(mike)", "family", "charm", "confused", "charm", "ties", "", "charm", "CouPle" };
    char kOut[10][MAX_WORD_LENGTH+1] = { "walking", "older", "last", "project", "confused", "", "family", "frightened", "", "LovEs" };
    assert(cleanupRules(kIn, kOut, 9) == 4); // test for correctness
    char kInCorrect[6][MAX_WORD_LENGTH+1] = { "ties", "dog", "family", "charm" };
    char kOutCorrect[6][MAX_WORD_LENGTH+1] = { "family", "walking", "last", "" };
    matchRules(kIn, kOut, kInCorrect, kOutCorrect, 4);
    char lIn[10][MAX_WORD_LENGTH+1] = { "abcdefghijklmnopqrst", "(mike)", "family", "charm", "confused", "charm", "ties", "", "charm", "CouPle" };
    char lOut[10][MAX_WORD_LENGTH+1] = { "walking", "older", "last", "project", "confused", "", "family", "frightened", "", "LovEs" };
    assert(cleanupRules(lIn, lOut, 9) == 4); // MAX_WORD_LENGTH reached
    char lInCorrect[6][MAX_WORD_LENGTH+1] = { "ties", "abcdefghijklmnopqrst", "family", "charm" };
    char lOutCorrect[6][MAX_WORD_LENGTH+1] = { "family", "walking", "last", "" };
    matchRules(lIn, lOut, lInCorrect, lOutCorrect, 4);

    // Test determineScore()
    char mDocument[MAX_DOCUMENT_LENGTH+1] = "Some of NBA's best players include Lebron James from LA Lakers, Kevin Durant from Brooklyn Nets, James Harden from Houston Rockets, Giannis Antetokounmpo from Milwaukee Bucks, and Russell Westbrook from UCLA.";
    char mWin[4][MAX_WORD_LENGTH+1] = { "nba", "james", "ucl", "bucks" };
    char mWout[4][MAX_WORD_LENGTH+1] = { "", "", "",   "" };
    assert(determineScore(mDocument, mWin, mWout, -5) == 0); // nRules is negative
    assert(determineScore(mDocument, mWin, mWout, 0) == 0); // nRules is zero
    assert(determineScore(mDocument, mWin, mWout, 4) == 2); // matches two one-word rules
    char nWin[4][MAX_WORD_LENGTH+1] = { "nbas", "james", "ucla", "bucks" };
    char nWout[4][MAX_WORD_LENGTH+1] = { "jordan", "harden", "la", "championship" };
    assert(determineScore(mDocument, nWin, nWout, 4) == 2); // matches two two-word rules
    char oWin[6][MAX_WORD_LENGTH+1] = { "nbas", "james", "ucla", "bucks", "westbrook", "west" };
    char oWout[6][MAX_WORD_LENGTH+1] = { "", "harden", "la", "htown", "", "wood" };
    assert(determineScore(mDocument, oWin, oWout, 6) == 3); // matches two one-word rules and one two-word rules
    assert(determineScore(mDocument, oWin, oWout, 4) == 2); // only the first four rules should be examined
    char pDocument[MAX_DOCUMENT_LENGTH+1] = "So13290-me of NBA'^%s best pla<>yers include Le';bron James from LA La~ke1rs, Kevin Durant from Br000ooklyn Nets, Jam=es Ha!r!@den from Ho???uston Rock***ets, Gian--nis Antet(okounmpo f)rom Milwaukee Bucks, a(-nd Russell West+brook from UCLA:).";
    assert(determineScore(pDocument, oWin, oWout, 6) == 3); // document is filled with non-alphabetic characters that should be ignored
    char qDocument[MAX_DOCUMENT_LENGTH+1] = "So13290-me of  NBA'^%s best pla<>yers include   Le'bron James from LA Lakers, Kevin Durant from Br000ooklyn Nets, James Harden    from Ho???uston Rock***ets, Gian--nis Antet(okounmpo    f)rom Milwaukee Bucks,    a(-nd Russell West+brook from UCLA:).";
    assert(determineScore(qDocument, oWin, oWout, 6) == 3); // more than one space character between words
    char rDocument[MAX_DOCUMENT_LENGTH+1] = "";
    assert(determineScore(rDocument, oWin, oWout, 6) == 0); // document is an empty string
    char sDocument[MAX_DOCUMENT_LENGTH+1] = ")&)*) (*)(!*)81 8298019809**81929090 0~ ";
    assert(determineScore(sDocument, oWin, oWout, 6) == 0); // document has only non-alphabetic characters
    char tWin[4][MAX_WORD_LENGTH+1] = { "ratio", "team", "unsuccessful", "tea" };
    char tWout[4][MAX_WORD_LENGTH+1] = { "meaningful", "", "tea", "" };
    char tDocument[MAX_DOCUMENT_LENGTH+1] = "Successful teams are all alike; every unsuccessful team is unsuccessful in its own way.";
    assert(determineScore(tDocument, tWin, tWout, 4) == 2); // test for correctness
    char uDocument[MAX_DOCUMENT_LENGTH+1] = "Successful teas are all alike; every unsuccessful tea is unsuccessful in its own way.";
    assert(determineScore(uDocument, tWin, tWout, 4) == 1); // test for correctness
    char vDocument[MAX_DOCUMENT_LENGTH+1] = "Successful teas are all alike; every unsuccessful tea is unsuccessful in its own way.";
    assert(determineScore(vDocument, tWin, tWout, 2) == 0); // test for correctness
    char wDocument[MAX_DOCUMENT_LENGTH+1] = "A cup of tea!  A tea! My kingdom for a cup of tea!";
    assert(determineScore(wDocument, tWin, tWout, 4) == 1); // test for correctness
    char xDocument[MAX_DOCUMENT_LENGTH+1] = "tea:sugar ratio means nothing.";
    assert(determineScore(xDocument, tWin, tWout, 4) == 1); // test for correctness
    char yDocument[MAX_DOCUMENT_LENGTH+1] = "****  **** 2020";
    assert(determineScore(yDocument, tWin, tWout, 4) == 0); // test for correctness
    char zDocument[MAX_DOCUMENT_LENGTH+1] = "a b c d e f g h i j k l m n o p q r s t u v w x y z a b c d e f g h i j k l m n o p q r s t u v w x y z a b c d e f g h i j k l m n o p q r s t u v w x y z a b c d e f g h i j k l m n o p q r s t u v w x y z a b c d e f g h i j k l m n o p q r s t u ";
    char zWin[8][MAX_WORD_LENGTH+1] = { "a", "cd", "e", "o", "x", "z", "opq", "n" };
    char zWout[8][MAX_WORD_LENGTH+1] = { "p", "", "", "ab", "ii", "", "", "" };
    assert(determineScore(zDocument, zWin, zWout, 8) == 5); // MAX_DOCUMENT_LENGTH reached

    cout << "All tests succeeded." << endl;
}
