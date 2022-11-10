#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

class TreeNode{
    public:
        int leftPointer, rightPointer, parentPointer, mypointer;
        int keyValue;
        TreeNode(){}
        ~TreeNode(){}
};

void makeTree(int postA[], int length, TreeNode root[],int mypointer, int& h){
    root[mypointer].keyValue=postA[length-1];
    h++;
    cout<<"node="<<root[h].keyValue<<", its address="<<&root[h]<<endl;
    // cout<<endl<<"root= "<<root.keyValue<<"  ---->  ";
    if(length==1){
        // cout<<"I'm a leaf"<<endl;
        root[mypointer].leftPointer=-1;
        root[mypointer].rightPointer=-1;
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
            root[mypointer].rightPointer = h;
            root[h].parentPointer = mypointer;
            // cout<<"rightChildRoot.parentPointer"<<rightChildRoot.parentPointer<<endl;
            makeTree(rightTreeNodes, rightlength, root, h,h);
        }else{
            root[mypointer].rightPointer=-1;
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
            root[mypointer].leftPointer = h;
            root[h].parentPointer = mypointer;
            // cout<<"leftChildRoot.parentPointer="<<leftChildRoot.parentPointer<<endl;
            makeTree(leftTreeNodes, leftlength, root,h,h);
        }else{
            root[mypointer].leftPointer = -1;
            // cout<<"no left child"<<endl;
        }
    return;
}
void printPreorderTree(TreeNode root[], int mypointer, vector<int>& preT){
    cout<<root[mypointer].keyValue<<", ";
    preT.push_back(root[mypointer].keyValue);
    if(root[mypointer].leftPointer != -1) printPreorderTree(root,root[mypointer].leftPointer, preT);
    if(root[mypointer].rightPointer != -1)printPreorderTree(root,root[mypointer].rightPointer, preT);
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
    // int **preTree=NULL;
    // int **inorderTree=NULL;
    postTree = new int * [treeNum]; 
    // preTree = new int * [treeNum]; 
    // inorderTree = new int * [treeNum];
    TreeNode **binaryTreeRoot;
    binaryTreeRoot = new TreeNode * [treeNum];
    //TreeNode **bst_tree;
    //bst_tree = new TreeNode * [treeNum];

    int nodeNum[treeNum];
    for(int i=0; i<treeNum; i++){
        infile>>nodeNum[i];
        postTree[i] = new int[nodeNum[i]];
        binaryTreeRoot[i] = new TreeNode[nodeNum[i]];
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
        binaryTreeRoot[i][0].parentPointer=-1;
        binaryTreeRoot[i][0].mypointer=0;
        // cout<<endl<<"makeTree"<<i<<endl;
        int h = 0;
        makeTree(postTree[i], nodeNum[i], binaryTreeRoot[i],0, h);
    }

    for(int i=0; i<treeNum; i++){
        vector<int> preArr;
        cout<<i<<" preArr initialized"<<endl;
        printPreorderTree(binaryTreeRoot[i],0, preArr);
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