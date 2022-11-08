#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

class TreeNode{
    public:
        TreeNode *leftPointer=NULL;
        TreeNode *rightPointer=NULL;
        TreeNode *parentPointer=NULL;
        int keyValue;
        TreeNode(){}
};

void makeTree(int *postA, TreeNode *rootpointer){
    TreeNode root;
    int sizeOfPostA = sizeof(postA);
    root.keyValue=postA[sizeOfPostA-1];
    if(sizeOfPostA==1){
        return;
    }
    int k=sizeOfPostA-1;
        while(postA[k]>postA[sizeOfPostA-1]){
            k--;
        }
        int *rightTreeNodes, *leftTreeNodes;
        copy(postA+k+1,postA+sizeOfPostA-1,rightTreeNodes);
        copy(postA, postA+k, leftTreeNodes);
    makeTree(rightTreeNodes, root.rightPointer);
    makeTree(leftTreeNodes, root.leftPointer);
    *rootpointer = root;
}
void printPreorderTree(TreeNode root, vector<int>& preT){
    preT.push_back(root.keyValue);
    if(root.leftPointer!=NULL){
        printPreorderTree(*root.leftPointer, preT);
    }
    if(root.rightPointer!=NULL){
        printPreorderTree(*root.rightPointer, preT);
    }
    return;
}    

int main(int argc, char *argv[]){
    ifstream infile; 
    infile.open(argv[1]);
    ofstream outfile;
    outfile.open(argv[2]);

    // TODO: Please code here
    int treeNum=0;
    infile>>treeNum;
    int **postTree=NULL;
    int **preTree=NULL;
    int **inorderTree=NULL;
    postTree = new int * [treeNum]; 
    preTree = new int * [treeNum]; 
    inorderTree = new int * [treeNum];
    TreeNode *binaryTree[treeNum];
    //TreeNode **bst_tree;
    //bst_tree = new TreeNode * [treeNum];

    int nodeNum[treeNum];
    for(int i=0; i<treeNum; i++){
        infile>>nodeNum[i];
        postTree[i] = new int[nodeNum[i]];
        preTree[i] = new int[nodeNum[i]];
        inorderTree[i] = new int[nodeNum[i]];
        //bst_tree[i] = new TreeNode[nodeNum[i]];
        for(int j=0; j<nodeNum[i]; j++){
            infile>>postTree[i][j];
            inorderTree[i][j]=postTree[i][j];
        }
        sort(inorderTree[i],inorderTree[i]+nodeNum[i]);
    }
    for(int i=0; i<treeNum; i++){
        makeTree(postTree[i], binaryTree[i]);
        vector<int> preArr;
        printPreorderTree(*binaryTree[i], preArr);
        for(int j=0;j<preArr.size();j++)
        {
            outfile<<preArr[j]<<" ";
        }
        outfile<<endl;
    }
    infile.close();
    outfile.close();
}

// https://hackmd.io/@ndhu-programming-2021/BkZukG4jK