#ifndef PATTERN_SEARCH_HPP
#define PATTERN_SEARCH_HPP

#include "Suffix_tree.hpp" // Include the suffix tree header

// Define maximum characters for child nodes
#define MAX 256

// Function declarations
int traverseEdge(const char *str, int idx, int start, int end, const char *text);
int doTraversalToCountLeaf(SNode *n);
int countLeaf(SNode *n);
int doTraversal(SNode *n, const char *str, int idx, const char *text);
void checkForSubString(const char *str, SNode *root, const char *text, int *pos);

#endif // PATTERN_SEARCH_HPP
