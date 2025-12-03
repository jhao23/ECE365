#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;

// Main matrix for dynamic programmign part
// (i, j) entry represents whether first i letters of first word and first j letters of second word can be
// combined to make string merge of first i+j letters of third word 
vector<vector<bool>> wordmatrix(1001, vector<bool>(1001, 0));

int main()
{
    // Input/ouput processing stuff
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
        // quick check for string length to rule out easy cases 
        if (l1 + l2 != word3.size())
        {
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

        // Fill in rest of entries with previous entries
        // Mostly checks if the new letter is the same as any of the last letters of the other two words
        // If so, check if the matching word (minus a letter) with the other word can make the previous portion
        // of the third word
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

        // retrieve the word if possible
        // basically traverses ones of matrix from bottom right to top left of the matrix
        // the direction of each step indicates which word the letter came from
        if (wordmatrix[l1][l2])
        {
            string capitalword = "";
            int index1 = l1;
            int index2 = l2;
            transform(word1.begin(), word1.end(), word1.begin(), ::toupper);
            
            while (index1 != 0 || index2 != 0)
            {
                // we check for the second word first because we want to prioritize putting those letters
                // as far back as possible
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
            outputFile << "*** NOT A MERGE ***\n";
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
