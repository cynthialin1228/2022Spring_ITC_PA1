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
        TreeNode();
};
    

int main(int argc, char *argv[]){
    ifstream infile; 
    infile.open(argv[1]);
    ofstream outfile;
    outfile.open(argv[2]);

    // TODO: Please code here
    int treeNum=0;
    infile>>treeNum;
    int **postTree=NULL;
    int **inorderTree=NULL;
    postTree = new int * [treeNum]; 
    inorderTree = new int * [treeNum];
    TreeNode **bst_tree;
    bst_tree = new TreeNode * [treeNum];

    int nodeNum[treeNum];
    for(int i=0; i<treeNum; i++){
        infile>>nodeNum[i];
        postTree[i] = new int[nodeNum[i]];
        inorderTree[i] = new int[nodeNum[i]];
        bst_tree[i] = new TreeNode[nodeNum[i]];
        for(int j=0; j<nodeNum[i]; j++){
            infile>>postTree[i][j];
            inorderTree[i][j]=postTree[i][j];
        }
        sort(inorderTree[i],inorderTree[i]+nodeNum[i]);
    }

    for(int i=0; i<treeNum; i++){
        // for (int j=0; j<nodeNum[i]-2; j++){
        //     int key1=bst_tree[i][j].keyValue;
        //     int key2=bst_tree[i][j+1].keyValue;
        //     int key3=bst_tree[i][j+2].keyValue;
        //     // TreeNode *lefttree=NULL;
        //     if(key1<key2 && key2<key3){
        //         // bst_tree[i][j+1].parentPointer=bst_tree[i][j+2];
        //         // bst_tree[i][j+2].leftPointer=bst_tree[i][j+1];
        //         //key1 useless
        //     }else if (key1<key3 && key3<key2){
        //         bst_tree[i][j].parentPointer=bst_tree[i][j+2];
        //         bst_tree[i][j+2].leftPointer=bst_tree[i][j];
        //         bst_tree[i][j+2].rightPointer=bst_tree[i][j+1];
        //         bst_tree[i][j+1].parentPointer=bst_tree[i][j+2];
        //         *lefttree=bst_tree[i][j+2];
        //     }else if (key2<key1 && key1<key3){
        //         bst_tree[i][j].parentPointer=bst_tree[i][j+1];
        //         bst_tree[i][j+1].rightPointer=bst_tree[i][j];
        //         // if(*lefttree.keyValue<key2){
        //         //     *lefttree.parentPointer=bst_tree[i][j+1];
        //         //     bst_tree[i][j+1].leftPointer=*lefttree;
        //         //     *lefttree=bst_tree[i][j+1];
        //         // }
        //         //key3 useless
        //     }else if (key2<key3 && key3<key1){

        //     }else if (key3<key1 && key1<key2){
        //         bst_tree[i][j].parentPointer=bst_tree[i][j+1];
        //         bst_tree[i][j+1].leftPointer=bst_tree[i][j];
        //         bst_tree[i][j+1].parentPointer=bst_tree[i][j+2];
        //         bst_tree[i][j+2].rightPointer=bst_tree[i][j+1];

        //     }else if(key3<key2 && key2<key1){

        //     }
        // }
    }


    // for(int i=0; i<treeNum; i++){
    //     for (int j=0; j<nodeNum[i];j++){
    //         outfile<<postTree[i][j]<<" ";
    //     }outfile<<endl;
    // }
    infile.close();
    outfile.close();
}
// https://hackmd.io/@ndhu-programming-2021/BkZukG4jK