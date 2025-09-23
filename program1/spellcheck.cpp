#include "hash.h"
#include <iostream>
#include <string>
#include <cctype>
#include <chrono>
#include <fstream>

std::string toLowerCase(std::string &input)
{
    // we effectively just reconstructed the word one character at a time
    std::string new_word;
    for (char c : input)
    {
        if (c >= 'A' && c <= 'Z')
        {
            // adding 32 to an uppercase character makes it lowercase
            new_word += char(c + 32);
        }
        else
        {
            new_word += char(c);
        }
    }
    return new_word;
}

bool charIsValid(char input)
{
    return (isalnum(input) || input == '-' || input == '\'');
}

bool hasDigits(std::string &input)
{
    for (char c : input)
    {
        if (c >= '0' && c <= '9')
        {
            return true;
        }
    }
    return false;
}

int main()
{
    // Loading the dictionary
    std::ifstream dict_file;
    std::string dict_name;

    std::cout << "Enter Name of Dictionary File: ";
    std::cin >> dict_name;

    const auto start1{std::chrono::steady_clock::now()};
    dict_file.open(dict_name);

    // Error checking for file names
    if (!dict_file.good())
    {
        std::cout << "Invalid Dictionary Name\n";
        dict_file.close();
        return 1;
    }

    std::string words;
    hashTable dictionary;

    // loading each word (we can assume the dictionary input is always valid)
    while (getline(dict_file, words))
    {
        if (words.size() > 20 || hasDigits(words))
        {
            // we can ignore when the word is too long or has digits
            continue;
        }
        else
        {
            // want lowercase inserts because we convert everything into lowercase
            dictionary.insert(toLowerCase(words));
        }
    }

    dict_file.close();
    const auto finish1{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_seconds1{finish1 - start1};
    std::cout << "Time to process dictionary (in seconds): " << elapsed_seconds1.count() << "\n";

    // Spellchecking part

    std::ifstream in_file;
    std::ofstream out_file;

    std::string in_name;
    std::string out_name;

    std::cout << "Enter Name of Input File: ";
    std::cin >> in_name;
    std::cout << "Enter Name of Output File: ";
    std::cin >> out_name;

    const auto start2{std::chrono::steady_clock::now()};

    in_file.open(in_name);
    out_file.open(out_name);
    // Error checking for file names
    if (!in_file.good())
    {
        std::cout << "Invalid Input Name\n";
        in_file.close();
        out_file.close();
        return 1;
    }
    

    int line_number = 1;
    std::string word;
    std::string line;

    while (getline(in_file, line))
    {
        line += '\n'; //getLine chops off the last newline character
        for (char character : line)
        {
            // we are adding characters on until an invalid character appears to make a word
            if (charIsValid(character))
            {
                word += tolower(character);
            }
            else
            {
                if (hasDigits(word))
                {
                    // ignore this case
                }
                else
                {
                    if (word.size() > 20)
                    {
                        // we only want the first 20 letters to be outputted
                        out_file << "Long word at line " << line_number << ", starts: " << word.substr(0, 20) << "\n";
                    }
                    else if (!dictionary.contains(word) && word != "")
                    {
                        out_file << "Unknown word at line " << line_number << ": " << word << "\n";
                    }
                }
                word.clear();
            }
        }
        line_number++;
    }

    in_file.close();
    out_file.close();
    
    const auto finish2{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_seconds2{finish2 - start2};
    std::cout << "Time to process document (in seconds): " << elapsed_seconds2.count() << "\n";

    return 0;
}
