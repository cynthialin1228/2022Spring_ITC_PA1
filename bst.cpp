#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

class TreeNode{
    public:
        TreeNode *leftPointer;
        TreeNode *rightPointer;
        TreeNode *parentPointer;
        int keyValue;
        TreeNode(){}
        ~TreeNode(){}
};

void makeTree(int postA[], int length, TreeNode& root){
    root.keyValue=postA[length-1];
    cout<<"node="<<root.keyValue<<", its address="<<&root<<endl;
    // cout<<endl<<"root= "<<root.keyValue<<"  ---->  ";
    if(length==1){
        // cout<<"I'm a leaf"<<endl;
        root.leftPointer=NULL;
        root.rightPointer=NULL;
        return;
    }
    int k=length-2;
        while(postA[k]>postA[length-1]){
            k--;
            if(k==-1){
                break;
            }
        }
        if(k!=length-2){
            int rightTreeNodes[length-k-2], rightlength=length-k-2;
            // cout<<endl<<"rightT: ";
            for(int i=0; i<rightlength; i++){
                rightTreeNodes[i]=postA[k+1+i];
                // cout<<rightTreeNodes[i]<<", ";
            }
            // copy(postA+k+1,postA+length-2,rightTreeNodes);
            TreeNode rightChildRoot;
            root.rightPointer = &rightChildRoot;
            rightChildRoot.parentPointer = &root;
            // cout<<"rightChildRoot.parentPointer"<<rightChildRoot.parentPointer<<endl;
            makeTree(rightTreeNodes, rightlength, rightChildRoot);
        }else{
            root.rightPointer=NULL;
            // cout<<"no right child"<<endl;
        }

        if(k!=-1){
            int leftTreeNodes[k+1], leftlength=k+1;
            // cout<<endl<<"leftT: ";
            for(int i=0; i<leftlength; i++){
                leftTreeNodes[i]=postA[i];
                // cout<<leftTreeNodes[i]<<", ";
            }
            // copy(postA, postA+k, leftTreeNodes);
            TreeNode leftChildRoot;
            root.leftPointer = &leftChildRoot;
            leftChildRoot.parentPointer = &root;
            // cout<<"leftChildRoot.parentPointer="<<leftChildRoot.parentPointer<<endl;
            makeTree(leftTreeNodes, leftlength, leftChildRoot);
        }else{
            root.leftPointer = NULL;
            // cout<<"no left child"<<endl;
        }
    return;
}
void printPreorderTree(TreeNode& root){
        cout<<root.keyValue<<" ";
        cout<<&root<<"      ";
        cout<<root.leftPointer<<"   ";
        cout<<root.rightPointer<<"   "<<endl;

    // cout<<root.keyValue<<", ";
    // preT.push_back(root.keyValue);
    if(root.leftPointer != 0) printPreorderTree(*root.leftPointer);
    if(root.rightPointer != 0)printPreorderTree(*root.rightPointer);
    // preT.push_back(root.keyValue);
    // // cout<<root.keyValue<<endl;
    // if(root.leftPointer!=NULL){
    //     // cout<<"into leftchild"<<endl;
    //     printPreorderTree(*root.leftPointer, preT);
    //     // cout<<"out leftchild"<<endl;
    // }
    // if(root.rightPointer!=NULL){
    //     // cout<<"into rightchild"<<endl;
    //     printPreorderTree(*root.rightPointer, preT);
    // }
    // return;
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
    // int **preTree=NULL;
    // int **inorderTree=NULL;
    postTree = new int * [treeNum]; 
    // preTree = new int * [treeNum]; 
    // inorderTree = new int * [treeNum];
    TreeNode *binaryTreeRoot;
    binaryTreeRoot = new TreeNode [treeNum];
    //TreeNode **bst_tree;
    //bst_tree = new TreeNode * [treeNum];

    int nodeNum[treeNum];
    for(int i=0; i<treeNum; i++){
        infile>>nodeNum[i];
        postTree[i] = new int[nodeNum[i]];
        // preTree[i] = new int[nodeNum[i]];
        // inorderTree[i] = new int[nodeNum[i]];
        //bst_tree[i] = new TreeNode[nodeNum[i]];
        for(int j=0; j<nodeNum[i]; j++){
            infile>>postTree[i][j];
            // inorderTree[i][j]=postTree[i][j];
        }
        // sort(inorderTree[i],inorderTree[i]+nodeNum[i]);
    }


    for(int i=0; i<treeNum; i++){
        binaryTreeRoot[i].parentPointer=NULL;
        // cout<<endl<<"makeTree"<<i<<endl;
        makeTree(postTree[i], nodeNum[i], binaryTreeRoot[i]);
    }
    for(int i=0; i<treeNum; i++){
        cout<<"binaryTreeRoot"<<&binaryTreeRoot[i]<<endl;
        printPreorderTree(binaryTreeRoot[i]);
    }

    // for(int i=0; i<treeNum; i++){
    //     vector<int> preArr;
    //     cout<<i<<" preArr initialized"<<endl;
    //     printPreorderTree(binaryTreeRoot[i]);
    //     // preArr.push_back(binaryTreeRoot[i].keyValue);
    //     // printPreorderTree(binaryTreeRoot[i].leftPointer, preArr);
    //     // printPreorderTree(binaryTreeRoot[i].rightPointer, preArr);
    //     for(int j=0;j<preArr.size();j++)
    //     {
    //         outfile<<preArr[j]<<" ";
    //     }
    //     outfile<<endl;
    // }    
    infile.close();
    outfile.close();
}

// https://hackmd.io/@ndhu-programming-2021/BkZukG4jK