#include "Suffix_tree.hpp" // Include the suffix tree header
#include "PatternSearch.hpp" // Include the pattern search header
#include <iostream>
#include <vector>
#include<bits/stdc++.h>

using namespace std;

vector<int> results; // Vector to store results
int ind = 0; // Index for tracking results

// Function to traverse an edge in the suffix tree and compare it with a given string
int traverseEdge(const char *str, int idx, int start, int end, const char *text) {
    int k = 0; // Index for traversing the edge
    // Compare the edge with the string
    for (k = start; k <= end && str[idx] != '\0'; k++, idx++) {
        if (text[k] != str[idx])
            return -1; // Mismatch, return -1
    }
    if (str[idx] == '\0')
        return 1; // Exact match, return 1
    return 0; // Partial match, return 0
}



// Recursive function to count leaf nodes in the suffix tree
int doTraversalToCountLeaf(SNode *n) {
    if (n == nullptr)
        return 0; // Base case: null node

    // If it's a leaf node, store its suffix index
    if (n->suffixIndex > -1) {
        results.push_back(n->suffixIndex); // Store the suffix index in the results
        return 1; // Count this leaf
    }

    int count = 0; // Initialize leaf count
    // Traverse the children of the current node
    for (int i = 0; i < MAX; i++) {
        if (n->children[i] != nullptr) {
            count += doTraversalToCountLeaf(n->children[i]); // Accumulate leaf counts
        }
    }
    return count; // Return total count of leaf nodes
}

// Count the number of leaf nodes in the suffix tree
int countLeaf(SNode *n) {
    if (n == nullptr)
        return 0; // If the node is null, return 0
    return doTraversalToCountLeaf(n); // Call the helper function
}

// Recursive function to search for a string in the suffix tree
int doTraversal(SNode *n, const char *str, int idx, const char *text) {
    if (n == nullptr) {
        return -1; // No match, return -1
    }

    int res = -1; // Result variable
    if (n->start != -1) {
        // Compare the edge with the string
        res = traverseEdge(str, idx, n->start, *(n->end), text);
        if (res == -1)
            return -1; // Mismatch, return -1
        if (res == 1) {
            if (n->suffixIndex > -1) {
                cout << "\nOrder count: 1"; // Suffix found, print order count
                results.push_back(n->suffixIndex);
            } else {
                cout << "\nOrder count: " << countLeaf(n); // Count and print number of leaf nodes
            }
            return 1;
        }
    }

    // Move to the next index in the string
    idx += edgeLength(n);
    // Continue the search in the children
    if (n->children[str[idx]] != nullptr)
        return doTraversal(n->children[str[idx]], str, idx, text);
    else
        return -1; // No match
}

// Function to check for a substring in the suffix tree and store the results
void checkForSubString(const char *str, SNode *root, const char *text, int *pos) {
    results.clear(); // Clear previous results
    ind = 0; // Reset the index for results
    int res = doTraversal(root, str, 0, text); // Search for the substring

    results.push_back(-1); // Mark the end of the results
    if (res == 1) {
        ind = 0; // Reset the results index
    } else {
        cout << "\n" << str << " is NOT opted yet\n"; // String not found in the tree
    }
}
