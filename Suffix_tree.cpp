#include "Suffix_tree.hpp"
#include<bits/stdc++.h>
#include <cstring>
#include <cstdlib>

// Global variables for Suffix Tree management
char* test;
SNode* root = nullptr;
SNode* lastNewNode = nullptr;
SNode* activeNode = nullptr;
int activeEdge = -1;
int activeLength = 0;
int remainingSuffixCount = 0;
int END = -1;
int* rootEnd = nullptr;
int* splitEnd = nullptr;
int size = -1;

// Function to create a new Suffix Tree node
SNode* newNode(int start, int* end)
{
    SNode* STSNode = new SNode();
    for (int i = 0; i < MAX; i++)
        STSNode->children[i] = nullptr;
    STSNode->suffixLink = root;
    STSNode->start = start;
    STSNode->end = end;
    STSNode->suffixIndex = -1;
    return STSNode;
}

// Function to calculate edge length between nodes
int edgeLength(SNode* a)
{
    if (a == root)
        return 0;
    return *(a->end) - a->start + 1;
}

// Function to perform a walk down the tree during extension
int walkDown(SNode* A)
{
    if (activeLength >= edgeLength(A))
    {
        activeNode = A;
        activeLength -= edgeLength(A);
        activeEdge += edgeLength(A);
        return 1;
    }
    return 0;
}

// Function to extend the suffix tree at a given position `pos`
void extendSuffixTree(int pos)
{
    END = pos;
    remainingSuffixCount++;
    lastNewNode = nullptr;

    while (remainingSuffixCount > 0)
    {
        if (activeLength == 0)
            activeEdge = pos;

        if (activeNode->children[test[activeEdge]] == nullptr)
        {
            activeNode->children[test[activeEdge]] = newNode(pos, &END);

            if (lastNewNode != nullptr)
            {
                lastNewNode->suffixLink = activeNode;
                lastNewNode = nullptr;
            }
        }
        else
        {
            SNode* next = activeNode->children[test[activeEdge]];
            if (walkDown(next))
                continue;

            if (test[next->start + activeLength] == test[pos])
            {
                if (lastNewNode != nullptr && activeNode != root)
                {
                    lastNewNode->suffixLink = activeNode;
                    lastNewNode = nullptr;
                }
                activeLength++;
                break;
            }

            splitEnd = new int(next->start + activeLength - 1);
            SNode* split = newNode(next->start, splitEnd);
            activeNode->children[test[activeEdge]] = split;

            split->children[test[pos]] = newNode(pos, &END);
            next->start += activeLength;
            split->children[test[next->start]] = next;

            if (lastNewNode != nullptr)
                lastNewNode->suffixLink = split;

            lastNewNode = split;
        }

        remainingSuffixCount--;
        if (activeNode == root && activeLength > 0)
        {
            activeLength--;
            activeEdge = pos - remainingSuffixCount + 1;
        }
        else if (activeNode != root)
        {
            activeNode = activeNode->suffixLink;
        }
    }
}

// Function to print characters from index `i` to `j`
void print(int i, int j)
{
    for (int k = i; k <= j; k++)
        std::cout << test[k];
}

// Function to set the suffix index for each leaf node
void setSuffixIndex(SNode* n, int labelHeight)
{
    if (n == nullptr)
        return;

    bool isLeaf = true;
    for (int i = 0; i < MAX; i++)
    {
        if (n->children[i] != nullptr)
        {
            isLeaf = false;
            setSuffixIndex(n->children[i], labelHeight + edgeLength(n->children[i]));
        }
    }
    if (isLeaf)
        n->suffixIndex = size - labelHeight;
}

// Function to free memory of the Suffix Tree nodes with post-order traversal
void freeSuffixTreeByPostOrder(SNode* n)
{
    if (n == nullptr)
        return;

    for (int i = 0; i < MAX; i++)
    {
        if (n->children[i] != nullptr)
            freeSuffixTreeByPostOrder(n->children[i]);
    }
    if (n->suffixIndex == -1)
        delete n->end;
    delete n;
}

// Function to build the Suffix Tree from a given text
void buildSuffixTree(char* text)
{
    test = text;
    size = strlen(test);
    rootEnd = new int(-1);
    root = newNode(-1, rootEnd);
    activeNode = root;

    for (int j = 0; j < size; j++)
        extendSuffixTree(j);

    int labelHeight = 0;
    setSuffixIndex(root, labelHeight);
}

// Function to return the root of the Suffix Tree
SNode* returnRoot()
{
    return root;
}
