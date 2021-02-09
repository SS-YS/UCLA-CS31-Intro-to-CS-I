#include <iostream>
#include <string>
using namespace std;

int main()
{
    // Gather input
    string cheeseType;
    double value;
    string importer;
    
    cout << "Cheese type: ";
    getline(cin, cheeseType);
    cout << "Value: ";
    cin >> value;
    cin.ignore(10000, '\n');
    cout << "Importer: ";
    getline(cin, importer);
    
    cout << "---" << endl;
    
    // Check for and output input errors
    if (cheeseType == "")
    {
        cout << "You must enter a cheese type" << endl;
        return 1;
    }
    if (value <= 0)
    {
        cout << "The value must be positive" << endl;
        return 1;
    }
    if (importer == "")
    {
        cout << "You must enter an importer" << endl;
        return 1;
    }
    
    // Calculate the import duty
    double duty = 0;
    
    if (value <= 1000) // value <= 1000
        duty += value * 0.011;
    
    else if (value <= 13000) // 1000 < value <= 13000
    {
        duty += 1000 * 0.011;
        if (cheeseType == "cheshire" || cheeseType == "stilton")
            duty += (value - 1000) * 0.014;
        else
            duty += (value - 1000) * 0.02;
    }
    
    else // 13000 < value
    {
        duty += 1000 * 0.011;
        if (cheeseType == "cheshire" || cheeseType == "stilton")
            duty += 12000 * 0.014;
        else
            duty += 12000 * 0.02;
        duty += (value - 13000) * 0.029;
    }
        
    // Output the import duty
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "The import duty for " << importer << " is $" << duty << endl;
}
