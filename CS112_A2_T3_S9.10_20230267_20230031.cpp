// File: CS112_A2_T3_S9.10_20230267_20230031.cpp

// Purpose: This is a simple fraction calculator.

// Author 1: Omar Mostafa Saad    - 20230267 - S9.10 - I did the part related to tokenizing string and getting input.
// Author 2: Ahmed Mohamed Ahmed  - 20230031 - S9.10 - he did the second part related to calculating the fractions.

// Sorry, but our team is from two because our third team member is ill.

#include <iostream>
#include <array>
#include <vector>
#include <sstream>
#include <cctype>

using namespace std;

// Define a struct to represent fractions
struct Fraction
{
    int numerator;   // Numerator of the fraction
    int denominator; // Denominator of the fraction
};

// Function to tokenize the input string based on spaces
vector<string> getTokens(string text); // Function prototype

// Function to parse a string token into a Fraction struct
Fraction parseFraction(const string &token); // Function prototype

// Functions for arithmetic operations on fractions
Fraction addFractions(const Fraction &a, const Fraction &b);      // Function prototype
Fraction subtractFractions(const Fraction &a, const Fraction &b); // Function prototype
Fraction multiplyFractions(const Fraction &a, const Fraction &b); // Function prototype
Fraction divideFractions(const Fraction &a, const Fraction &b);   // Function prototype

// Function to print a fraction in a readable format
void printFraction(const Fraction &result); // Function prototype

// Function to calculate the greatest common divisor of two integers (used for simplifying fractions)
int gcd(int a, int b); // Function prototype

// Function to simplify a fraction by dividing both numerator and denominator by their greatest common divisor
Fraction simplifyFraction(const Fraction &fraction); // Function prototype

// Function to check if a string is a valid fraction format
bool isValidFraction(const string &token); // Function prototype

int main()
{
    // Print header
    cout << "Welcome to the rational number calculator!\n"
         << "==========================================\n"
         << "Enter a fraction expression (e.g., '1/2 + 3' or '1 + 3/4'), or type 'exit' to quit:" << endl;

    // Program loop
    while (true)
    {
        cout << "> ";
        // Get input from the user
        string input;
        getline(cin, input);

        // Tokenize the input
        vector<string> tokens = getTokens(input);

        // if user entered nothing do nothing
        if (tokens.size() == 0)
        {
            continue;
        }
        // Check if the user wants to exit
        if (tokens.size() == 1 && tokens[0].compare("exit") == 0)
        {
            cout << "Good bye!" << endl;
            break;
        }
        // if the user entered just one valid number. just simplify it.
        if (tokens.size() == 1 && isValidFraction(tokens[0]))
        {
            Fraction fraction1 = parseFraction(tokens[0]);
            fraction1 = simplifyFraction(fraction1);
            printFraction(fraction1);
            continue;
        }

        // Check if the input is in the correct format.
        if (tokens.size() != 3 || !isValidFraction(tokens[0]) || !isValidFraction(tokens[2]) ||
            (tokens[1] != "+" && tokens[1] != "-" && tokens[1] != "*" && tokens[1] != "/"))
        {
            cerr << "Error! Invalid input. Please enter a valid fraction expression." << endl;
            continue;
        }

        // Parse fractions from tokens
        Fraction fraction1 = parseFraction(tokens[0]);
        Fraction fraction2 = parseFraction(tokens[2]);

        Fraction result;
        // Perform the operation based on the operator provided
        if (tokens[1] == "+")
        {
            result = addFractions(fraction1, fraction2);
        }
        else if (tokens[1] == "-")
        {
            result = subtractFractions(fraction1, fraction2);
        }
        else if (tokens[1] == "*")
        {
            result = multiplyFractions(fraction1, fraction2);
        }
        else if (tokens[1] == "/")
        {
            result = divideFractions(fraction1, fraction2);
        }

        // Print the result
        printFraction(result);
    }

    return 0;
}

// Function to tokenize the input string based on spaces
vector<string> getTokens(string text)
{
    vector<string> tokens;
    stringstream ss(text);
    string token;
    while (ss >> token)
    {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to parse a string token into a Fraction struct
Fraction parseFraction(const string &token)
{
    Fraction fraction;
    stringstream ss(token);
    char slash = '/';

    ss >> fraction.numerator;

    if (ss.peek() == slash)
    {
        ss.ignore();
        ss >> fraction.denominator;
    }
    else
    {
        fraction.denominator = 1; // Treat as integer or fraction with denominator 1
    }
    return fraction;
}

// Function to calculate the greatest common divisor of two integers
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to simplify a fraction by dividing both numerator and denominator by their greatest common divisor
Fraction simplifyFraction(const Fraction &fraction)
{
    int commonDivisor = gcd(fraction.numerator, fraction.denominator);
    Fraction simplifiedFraction;
    simplifiedFraction.numerator = fraction.numerator / commonDivisor;
    simplifiedFraction.denominator = fraction.denominator / commonDivisor;
    return simplifiedFraction;
}

// Function to add two fractions
Fraction addFractions(const Fraction &a, const Fraction &b)
{
    Fraction result;
    result.numerator = a.numerator * b.denominator + b.numerator * a.denominator;
    result.denominator = a.denominator * b.denominator;
    return simplifyFraction(result);
}

// Function to subtract one fraction from another
Fraction subtractFractions(const Fraction &a, const Fraction &b)
{
    Fraction result;
    result.numerator = a.numerator * b.denominator - b.numerator * a.denominator;
    result.denominator = a.denominator * b.denominator;
    return simplifyFraction(result);
}

// Function to multiply two fractions
Fraction multiplyFractions(const Fraction &a, const Fraction &b)
{
    Fraction result;
    result.numerator = a.numerator * b.numerator;
    result.denominator = a.denominator * b.denominator;
    return simplifyFraction(result);
}

// Function to divide one fraction by another
Fraction divideFractions(const Fraction &a, const Fraction &b)
{
    Fraction result;
    result.numerator = a.numerator * b.denominator;
    result.denominator = a.denominator * b.numerator;
    return simplifyFraction(result);
}

// Function to print a fraction in a readable format
void printFraction(const Fraction &result)
{
    if (result.denominator == 1)
    {
        cout << result.numerator << endl;
    }
    else
    {
        cout << result.numerator << "/" << result.denominator << endl;
    }
}

// Function to check if a string is a valid fraction format
bool isValidFraction(const string &token)
{
    stringstream ss(token);
    int numerator, denominator = 1;
    char slash = '/';

    if (ss >> numerator)
    {
        if (ss.peek() == slash)
        {
            ss.ignore();
            if (ss >> denominator && denominator != 0 && ss.eof())
            {
                return true;
            }
        }
        else if (ss.eof())
        {
            return true; // No denominator specified, treated as integer or fraction with denominator 1
        }
    }
    return false;
}
