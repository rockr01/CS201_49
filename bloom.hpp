#include <bits/stdc++.h> // Includes all standard libraries
using namespace std; // Using the standard namespace

#ifndef BLOOM_H // Start of include guard for BLOOM_H
#define BLOOM_H

// Hash function h1: takes a string and array size as input, returns an integer hash value
int h1(string s, int arrSize);

// Hash function h2: another hash function that takes a string and array size as input
int h2(string s, int arrSize);

// Hash function h3: another distinct hash function for the Bloom filter
int h3(string s, int arrSize);

// Hash function h4: fourth hash function for additional uniqueness in the Bloom filter
int h4(string s, int arrSize);

// Lookup function: checks if the given string `s` is likely in the Bloom filter
// Parameters:
// - `bit`: pointer to a bit array (boolean array) representing the Bloom filter
// - `arr`: size of the bit array
// - `s`: string to check in the Bloom filter
int lookup(bool *bit, int arr, string s);

// Insert function: inserts the given string `s` into the Bloom filter
// Parameters:
// - `bit`: pointer to a bit array (boolean array) representing the Bloom filter
// - `Size`: size of the bit array
// - `s`: string to insert into the Bloom filter
int insert(bool *bit, int Size, string s);

#endif // End of include guard for BLOOM_H


