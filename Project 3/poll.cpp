#include <iostream>
#include <cassert>
#include <string>
#include <cctype>
using namespace std;

// Return true if stateCode is a valid state code, or
// false otherwise.
bool isValidStateCode(string stateCode)
{
    for (int i=0; i<stateCode.size(); i++)
    {
        stateCode.at(i) = toupper(stateCode.at(i)); // convert each character to uppercase
    }
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
        "KY.LA.ME.MD.MA.MI.MN.MO.MS.MT.NE.NV.NH.NJ.NM.NY.NC."
        "ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

// Return true if pollData is a valid poll data string, or
// false otherwise.
bool isSyntacticallyCorrect(string pollData)
{
    int pos = 0;
    while (pos < pollData.size())
    {
        // A state forecast = one or two digits + a state code + a party code
        
        // Test the "one or two digits" part
        if (!isdigit(pollData.at(pos)))  return false;
        pos += 1;
        if (pos >= pollData.size())  return false;
        if (isdigit(pollData.at(pos)))   pos += 1;
        
        // Test the "a state code" part
        if (pos+1 >= pollData.size())  return false;
        if (!isValidStateCode(pollData.substr(pos, 2)))  return false;
        pos += 2;
        
        // Test the "a party code" part
        if (pos >= pollData.size())  return false;
        if (!isalpha(pollData.at(pos)))  return false;
        pos += 1; // proceed to the next state forecast
    }
    return true;
}

// Return 1 if pollData is not a valid poll data string;
// return 2 if party is not a letter;
// return 3 if pollData is valid but it contains state forecast(s) that predicts 0 vote;
// if none of the above occurs, set voteTally to the correct number and return 0.
int tallyVotes(string pollData, char party, int& voteTally)
{
    if (!isSyntacticallyCorrect(pollData))  return 1;
    if (!isalpha(party))  return 2;
    
    // Calculate the number of votes
    int votes = 0;
    int pos = 0;
    while (pos < pollData.size())
    {
        // A state forecast = one or two digits + a state code + a party code
        
        // Calculate the votes of the current state forecast
        int curVote = 0;
        int firstDigit = pollData.at(pos) - '0'; // convert char to int
        if (!isdigit(pollData.at(pos+1))) // there is only one digit
        {
            curVote = firstDigit;
            pos += 1;
        }
        else // there are two digits
        {
            int secondDigit = pollData.at(pos+1) - '0'; // convert char to int
            curVote = firstDigit * 10 + secondDigit;
            pos += 2;
        }
        
        // If the current state forecast predicts 0 vote, return 3.
        if (curVote == 0)  return 3;
        
        pos += 2; // proceed to the party code
        if (toupper(pollData.at(pos)) == toupper(party)) // the current votes belong to the party we want to calculate
        {
            votes += curVote;
        }
        pos += 1; // proceed to the next state forecast
    }
    voteTally = votes; // set voteTally to the number of votes we calculated
    return 0;
}

int main()
{
    // Test if isSyntacticallyCorrect() is implemented correctly
    assert(isSyntacticallyCorrect(""));
    assert(isSyntacticallyCorrect("38tXr55CaD"));
    assert(isSyntacticallyCorrect("38TXR55CAD6Msr29nYd06UTL"));
    
    assert(!isSyntacticallyCorrect("tXr55CaD")); // no digit in front of "tXr"
    assert(!isSyntacticallyCorrect("111tXr55CaD")); // more than two digits in front of "tXr"
    
    assert(!isSyntacticallyCorrect("38r55D")); // no state code
    assert(!isSyntacticallyCorrect("38mXr55CaD")); // "mX" is not a state code
    assert(!isSyntacticallyCorrect("38tXTxr55CaD")); // "38tXTxr" has two state codes
    
    assert(!isSyntacticallyCorrect("38tX55Ca")); // no party code
    assert(!isSyntacticallyCorrect("38tXr55Ca$")); // "$" is not a party code
    assert(!isSyntacticallyCorrect("38tXr55CaDd")); // "55CaDd" has two party codes
    
    assert(!isSyntacticallyCorrect("38tXrA55CaD")); // an extra "A" between "38tXr" and "55CaD"
    assert(!isSyntacticallyCorrect("38t Xr55CaD")); // an extra " " after "38t"
    assert(!isSyntacticallyCorrect("38tXr55CaD0")); // an extra "0" at the end

    // Test if tallyVotes() is implemented correctly
    int votes;
    votes = -999;
    assert(tallyVotes("38TXR55CAD6Msr29nYd06UTL", 'd', votes) == 0  &&  votes == 84);
    votes = -888;
    assert(tallyVotes("38TXR55CAD6Msr29nYd06UTL", 'R', votes) == 0  &&  votes == 44);
    votes = -777;
    assert(tallyVotes("38TXR55CAD6Msr29nYd06UTL", 'l', votes) == 0  &&  votes == 6);
    
    votes = -666;
    assert(tallyVotes("111tXr55CaD", 'd', votes) == 1 && votes == -666); // invalid poll data string
    votes = -555;
    assert(tallyVotes("38tXr55Ca$", 'r', votes) == 1 && votes == -555); // invalid poll data string
    votes = -444;
    assert(tallyVotes("38TXR55CAD", '%', votes) == 2  &&  votes == -444); // invalid party
    votes = -333;
    assert(tallyVotes("38TXR55CAD", ' ', votes) == 2  &&  votes == -333); // invalid party
    votes = -222;
    assert(tallyVotes("38TXR55CAD6Msr29nYd0UTL", 'd', votes) == 3  &&  votes == -222); // "00UTL" predicts 0 vote
    votes = -111;
    assert(tallyVotes("0CAD38TXR", 'r', votes) == 3  &&  votes == -111); // "0CAD" predicts 0 vote

    cout << "All tests passed!" << endl;
}
