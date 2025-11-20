#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;

vector<vector<bool>> wordmatrix(1001, vector<bool>(1001, 0));

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

    string word1, word2, word3;
    while (getline(inputFile, word1) && getline(inputFile, word2) && getline(inputFile, word3))
    {   
        int l1 = word1.size();
        int l2 = word2.size();
        if (l1 + l2 != word3.size())
        {
            cout << "incongruous lengths\n";
            outputFile << "*** NOT A MERGE ***\n";    
            continue;
        }

        // initial cases
        wordmatrix[0][0] = true;
        for (int k = 1; k <= l1; k++)
        {
            if (word1[k - 1] == word3[k - 1] && wordmatrix[k - 1][0])
            {
                wordmatrix[k][0] = true;
            }
            else
            {
                wordmatrix[k][0] = false;
            }
        }
        for (int k = 1; k <= l2; k++)
        {
            if (word2[k - 1] == word3[k - 1] && wordmatrix[0][k - 1])
            {
                wordmatrix[0][k] = true;
            }
            else
            {
                wordmatrix[0][k] = false;
            }
        }

        for (int i = 1; i <= l1; i++)
        {
            for (int j = 1; j <= l2; j++)
            {
                if ((word1[i - 1] == word3[i + j - 1]) && wordmatrix[i - 1][j])
                {
                    wordmatrix[i][j] = true;
                }
                else if (word2[j - 1] == word3[i + j - 1] && wordmatrix[i][j - 1])
                {
                    wordmatrix[i][j] = true;
                }
                else
                {
                    wordmatrix[i][j] = false;
                }
            }
        }
        
        for (int i = 0; i <= l1; i++)
        {
            for (int j = 0; j <= l2; j++)
            {
                cout << wordmatrix[i][j] << " ";
            }
            cout << "\n";
        }

        // retrieve the word if possible
        if (wordmatrix[l1][l2])
        {
            string capitalword = "";
            int index1 = l1;
            int index2 = l2;
            transform(word1.begin(), word1.end(), word1.begin(), ::toupper);
            
            while (index1 != 0 || index2 != 0)
            {
                if ((index2 != 0) && wordmatrix[index1][index2 - 1])
                {
                    capitalword = word2[index2 - 1] + capitalword;
                    index2--;
                }
                else
                {
                    capitalword = word1[index1 - 1] + capitalword;
                    index1--;
                }
            }
            outputFile << capitalword << "\n";
        }
        else
        {
            cout << "last entry false\n";
            outputFile << "*** NOT A MERGE ***\n";
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
