#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

int main()
{
    ifstream inputFile;
    ofstream outputFile;

    string inputName, outputName;

    cout << "Input File: ";
    cin >> inputName;
    inputFile.open(inputName);

    cout << "Output File: ";
    cin >> outputName;
    outputFile.open(outputName);

    string word1, word2, word3, line;
    while (getline(inputFile, line))
    {
        issstream ss(line);
        ss >> word1 >> word2 >> word3;
        
        if (word1.size() + word2.size() != word3.size())
        {
            outputFile << "*** NOT A MERGE ***\n";    
            continue;
        }

        
        // Dynamic programming stuff here
    }
    inputFile.close();
    outputFile.close();

    return 0;
}
