#include<bits/stdc++.h>
using namespace std;
#ifndef BK_TREE_H
#define BK_TREE_H
#define BMAX 100 
#define TOL 2   
#define LEN 10  

typedef struct BK_Tree_Node
{
    string word;
    int rating;
    int next[2 * LEN];
} BkNode;
BkNode createNode(string s , int rate);
int editDistance(string s1, string s2);
void addNode(BkNode &rootNode, BkNode &currentNode);
vector<string> getSimilarWords(BkNode &rootNode, string s , int minRating);
BkNode* ReturnBNode();
#endif


