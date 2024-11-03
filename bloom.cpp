#include <bits/stdc++.h> // Includes all standard libraries
#include "bloom.hpp" // Includes the Bloom filter header file
#define ll long long // Defines ll as shorthand for long long data type
using namespace std; // Using the standard namespace

// Hash function 1: generates a unique hash for a string `s` based on an initial value
// Parameters:
// - `s`: the input string
// - `arrSize`: size of the Bloom filter bit array
int h1(string s, int arrSize)
{
    ll int hash = 8; // Initialize hash with a base value
    for (int i = 0; i < s.size(); i++) // Loop through each character in the string
    {
        hash = (hash * 37 + s[i]) % arrSize; // Update hash value using a multiplier and current character
    }
    return hash % arrSize; // Return the hash value within the bounds of the array size
}

// Hash function 2: a different hash function for variety, adds ASCII values of characters
int h2(string s, int arrSize)
{
    ll int hash = 0; // Initialize hash to zero
    for (int i = 0; i < s.size(); i++) // Loop through each character
    {
        hash = (hash + ((int)s[i])); // Add the ASCII value of each character to hash
        hash = hash % arrSize; // Keep hash within the bounds of array size
    }
    return hash; // Return the final hash value
}

// Hash function 3: combines powers of a prime number (17) with character ASCII values for uniqueness
int h3(string s, int arrSize)
{
    ll int hash = 1; // Initialize hash with 1
    for (int i = 0; i < s.size(); i++) // Loop through each character
    {
        hash = hash + pow(17, i) * s[i]; // Multiply character ASCII with powers of 17
        hash = hash % arrSize; // Keep hash within array bounds
    }
    return hash % arrSize; // Return final hash
}

// Hash function 4: uses another approach with a base multiplier for added variety
int h4(string s, int arrSize)
{
    ll int hash = 4; // Initialize hash with a base value
    int p = 8; // Base multiplier
    for (int i = 0; i < s.size(); i++) // Loop through each character
    {
        hash += hash * 8 + s[0] * pow(11, i); // Update hash using multipliers and powers of 11
        hash = hash % arrSize; // Keep within array bounds
    }
    return hash; // Return the final hash
}

// Function to check if a string is present in the Bloom filter
// Parameters:
// - `bit`: pointer to the bit array (Bloom filter representation)
// - `arr`: size of the bit array
// - `s`: string to check in the filter
int lookup(bool *bit, int arr, string s)
{
    ll int a = h1(s, arr); // Get the index from hash function 1
    ll int b = h2(s, arr); // Get the index from hash function 2
    ll int c = h3(s, arr); // Get the index from hash function 3
    ll int d = h4(s, arr); // Get the index from hash function 4

    // Check if all hashed indices are set to true; if any are false, string is not in Bloom filter
    if (!(bit[a] && bit[b] && bit[c] && bit[d]))
        return 0; // Return 0 if string is not in Bloom filter
    else
        return 1; // Return 1 if string is probably in Bloom filter
}

// Function to insert a string into the Bloom filter
// Parameters:
// - `bit`: pointer to the bit array (Bloom filter representation)
// - `Size`: size of the bit array
// - `s`: string to insert into the filter
int insert(bool *bit, int Size, string s)
{
    if (!(lookup(bit, Size, s))) // Check if string is not already in Bloom filter
    {
        int a = h1(s, Size); // Get index from hash function 1
        int b = h2(s, Size); // Get index from hash function 2
        int c = h3(s, Size); // Get index from hash function 3
        int d = h4(s, Size); // Get index from hash function 4

        // Set the corresponding bits in the Bloom filter for the string
        bit[a] = true;
        bit[b] = true;
        bit[c] = true;
        bit[d] = true;

        cout << s << " inserted" << endl; // Output insertion confirmation
        return 1; // Return 1 to indicate successful insertion
    }
    else
    {
        cout << s << " is probably already present" << endl; // Output that the string is likely already in Bloom filter
        return 0; // Return 0 if insertion was skipped because string is likely present
    }
}
