#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

class TreeNode{
    public:
        int leftPointer, rightPointer, parentPointer, mypointer, nodeHeight;
        int keyValue;
        TreeNode(){}
        ~TreeNode(){}
};

void makeTree(int postA[], int length, TreeNode root[],int mypointer, int& h){
    root[mypointer].keyValue=postA[length-1];
    h++;
    if(length==1){
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
            for(int i=0; i<rightlength; i++){
                rightTreeNodes[i]=postA[k+1+i];
            }
            root[mypointer].rightPointer = h;
            root[h].parentPointer = mypointer;
			root[h].nodeHeight = root[mypointer].nodeHeight+1;
            makeTree(rightTreeNodes, rightlength, root, h,h);
        }else{
            root[mypointer].rightPointer=-1;
        }

        if(k!=-1){
            int leftTreeNodes[k+1], leftlength=k+1;
            for(int i=0; i<leftlength; i++){
                leftTreeNodes[i]=postA[i];
            }
            root[mypointer].leftPointer = h;
            root[h].parentPointer = mypointer;
			root[h].nodeHeight = root[mypointer].nodeHeight+1;
            makeTree(leftTreeNodes, leftlength, root,h,h);
        }else{
            root[mypointer].leftPointer = -1;
        }
    return;
}
void printPreorderTree(TreeNode root[], int mypointer, vector<int>& preT){
    preT.push_back(root[mypointer].keyValue);
    if(root[mypointer].leftPointer != -1){
    	printPreorderTree(root,root[mypointer].leftPointer, preT);
	} 
    if(root[mypointer].rightPointer != -1){
    	printPreorderTree(root,root[mypointer].rightPointer, preT);
	} 
    return;
}    
int getHeight(TreeNode root[], int length){
	int maxHeight=0;
	for(int i=0; i<length; i++){
		if(root[i].nodeHeight>maxHeight){
			maxHeight = root[i].nodeHeight;
		}
	}
	return maxHeight;
}
void getMaxValues(TreeNode root[],int length, int maxValues[]){
	for(int i=0; i<length; i++){
		if(root[i].keyValue>maxValues[root[i].nodeHeight-1]){
			maxValues[root[i].nodeHeight-1] = root[i].keyValue;
		}
	}
}

int main(int argc, char *argv[]){
    ifstream infile; 
    infile.open(argv[1]);
    ofstream outfile;
    outfile.open(argv[2]);

    int treeNum=0;
    infile>>treeNum;
    int **postTree=NULL;
    postTree = new int * [treeNum]; 
    TreeNode **binaryTreeRoot;
    binaryTreeRoot = new TreeNode * [treeNum];

    int nodeNum[treeNum];
    for(int i=0; i<treeNum; i++){
        infile>>nodeNum[i];
        postTree[i] = new int[nodeNum[i]];
        binaryTreeRoot[i] = new TreeNode[nodeNum[i]];
        for(int j=0; j<nodeNum[i]; j++){
            infile>>postTree[i][j];
        }
    }

    for(int i=0; i<treeNum; i++){
        binaryTreeRoot[i][0].parentPointer=-1;
        binaryTreeRoot[i][0].mypointer=0;
		binaryTreeRoot[i][0].nodeHeight=1;
        int h = 0;
        makeTree(postTree[i], nodeNum[i], binaryTreeRoot[i],0, h);
    }

    for(int i=0; i<treeNum; i++){
        vector<int> preArr;
        printPreorderTree(binaryTreeRoot[i],0, preArr);
        for(int j=0;j<preArr.size();j++)
        {
            outfile<<preArr[j]<<" ";
        }
        outfile<<endl;
    	int height = getHeight(binaryTreeRoot[i],nodeNum[i]);
        outfile<<height<<endl;
        int maxValues[height];
        for(int j=0; j<height; j++){
        	maxValues[j]=-1000;
		}
        getMaxValues(binaryTreeRoot[i],nodeNum[i], maxValues);
        for(int j=0; j<height; j++){
        	outfile<<maxValues[j]<<" "<<endl;
		}
    }    
    
    infile.close();
    outfile.close();
}

// https://hackmd.io/@ndhu-programming-2021/BkZukG4jK
