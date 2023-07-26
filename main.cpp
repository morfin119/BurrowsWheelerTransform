#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// Function to perform the Burrows-Wheeler Transform (BWT) on a given string
// Parameters:
//   inputText: The input string to transform using BWT.
// Returns:
//   The last column of the BWT table, which represents the transformed string.
std::string burrowsWheelerTransform(std::string inputText)
{
    // Table of rotations of string
    std::vector<std::string> bwtTable;

    // String containing characters in the last column of the BWT table
    std::string lastColumn = "";

    // Add start and end of text markers to the input string
    inputText = '\002' + inputText + '\003';

    // Generate all rotations of the input string and store them in the bwtTable vector
    size_t text_size = inputText.length();
    for (size_t i = 0; i < text_size; i++)
    {
        std::string aux = inputText.substr(i, text_size) + inputText.substr(0, i);
        bwtTable.push_back(aux);
    }

    // Sort the table of rotations lexicographically
    std::sort(bwtTable.begin(), bwtTable.end());

    // Extract the last column of the sorted BWT table to obtain the transformed string
    size_t table_size = bwtTable.size();
    for (size_t i = 0; i < table_size; i++)
    {
        lastColumn += bwtTable[i].back();
    }

    // Return the transformed string (the last column of the BWT table)
    return lastColumn;
}

// Function to find the index of the first occurrence of a target character in the transformed text.
// Parameters:
//   transformedText: The transformed string obtained after the Burrows-Wheeler Transform.
//   targetCharacter: The character to search for in the transformed text.
// Returns:
//   The index of the first occurrence of the target character in the transformed text.
//   If the target character is not found, it returns std::string::npos, which is a constant value representing
//   the maximum possible size_t value.
size_t findFirstOccurrenceInBwt(const std::string &transformedText, const char &targetCharacter)
{
    // Loop through each character in the transformed text
    for (size_t i = 0; i < transformedText.size(); i++)
    {
        // Check if the current character matches the target character
        if (transformedText[i] == targetCharacter)
        {
            // If a match is found, return the index of the first occurrence
            return i;
        }
    }

    // If the target character is not found, return std::string::npos
    return std::string::npos;
}

// Function to count the occurrences of a target character in the transformed text up to a given index.
// Parameters:
//   transformedText: The transformed string obtained after the Burrows-Wheeler Transform.
//   targetCharacter: The character to count occurrences of in the transformed text.
//   endIndex: The index up to which occurrences of the target character will be counted.
// Returns:
//   The number of occurrences of the target character in the transformed text up to the specified index.
size_t countOccurrencesInBwt(const std::string &transformedText, const char &targetCharacter, size_t endIndex)
{
    // Initialize a counter to keep track of the occurrences
    size_t occurrenceCount = 0;

    // Loop through the characters in the transformed text up to the specified index
    for (size_t i = 0; i < endIndex; i++)
    {
        // Check if the current character matches the target character
        if (transformedText[i] == targetCharacter)
        {
            // If a match is found, increment the counter
            occurrenceCount++;
        }
    }

    // Return the final count of occurrences of the target character up to the specified index
    return occurrenceCount;
}

// Function to perform pattern matching against the transformed string (result of BWT)
// Parameters:
//   transformedText: The transformed string obtained after BWT.
//   pattern: The pattern to search for in the transformed string.
// Returns:
//   The number of occurrences of the pattern in the transformed string.
size_t findOccurrencesInBwt(const std::string &transformedText, std::string pattern)
{
    // Create a sorted copy of the transformedText for efficient searching
    std::string bwtFirstColumn = transformedText;
    std::sort(bwtFirstColumn.begin(), bwtFirstColumn.end());

    // Initialize the range for pattern search
    size_t topIndex = 0;
    size_t bottomIndex = transformedText.size() - 1;

    // Keep looping until topIndex is greater than bottomIndex
    while (topIndex <= bottomIndex)
    {
        // Check if pattern is empty, and if so, directly return the range length
        if (pattern.empty())
            return bottomIndex - topIndex + 1;

        // Get the last character of the pattern and remove it
        char symbol = pattern.back();
        pattern.pop_back();

        // Check if symbol exists in the current range [topIndex, bottomIndex]
        bool symbolFound = false;
        for (size_t j = topIndex; j <= bottomIndex; j++)
            if (transformedText[j] == symbol) {
                symbolFound = true;
                break;
            }

        // If the symbol is not found in the current range, return 0
        if (!symbolFound)
            return 0;

        // Update topIndex and bottomIndex based on the occurrences of the symbol
        topIndex = findFirstOccurrenceInBwt(bwtFirstColumn, symbol) +
                countOccurrencesInBwt(transformedText, symbol, topIndex);
        bottomIndex = findFirstOccurrenceInBwt(bwtFirstColumn, symbol) +
                countOccurrencesInBwt(transformedText, symbol, bottomIndex + 1) - 1;
    }

    // If the loop exits without returning, it means the pattern is not found.
    return 0;
}

int main(int argc, char **argv)
{
    // Display help message if no arguments are provided
    if (argc == 1)
    {
        std::cout << "Usage: " << argv[0] << " <text> [pattern]" << std::endl;
        std::cout << "This program performs the Burrows-Wheeler Transform (BWT) on the input text." << std::endl;
        std::cout << "If a pattern is provided, it searches for the pattern in the transformed text." << std::endl;
        return -1;
    }

    // User input for the input text as a string
    std::string inputText = std::string(argv[1]);

    // Perform Burrows-Wheeler Transform on the input text
    std::string transformedText = burrowsWheelerTransform(inputText);

    // If only one argument is provided, print the transformed text
    if (argc == 2)
    {
        std::cout << transformedText;
        return 0;
    }

    // User input for the pattern as a string
    std::string pattern = std::string(argv[2]);

    // Perform pattern matching against the transformed text
    std::cout << findOccurrencesInBwt(transformedText, pattern);

    return 0;
}