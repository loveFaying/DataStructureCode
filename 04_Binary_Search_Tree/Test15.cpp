#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

using namespace std;

/// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {

public:

    // PreOrder Morris Traversal
    // Time Complexity: O(n), n is the node number in the tree
    // Space Complexity: O(1)
    vector<int> preorderTraversal(TreeNode* root) {

        vector<int> res;
        if(root == NULL)
            return res;

        TreeNode* cur = root;
        while(cur != NULL){
            if(cur->left == NULL){
                res.push_back(cur->val);
                cur = cur->right;
            }
            else{
                TreeNode* prev = cur->left;
                while(prev->right != NULL && prev->right != cur)
                    prev = prev->right;

                if(prev->right == NULL){
                    res.push_back(cur->val);
                    prev->right = cur;
                    cur = cur->left;
                }
                else{
                    prev->right = NULL;
                    cur = cur->right;
                }
            }
        }

        return res;
    }

    // InOrder Morris Traversal
    // Time Complexity: O(n), n is the node number in the tree
    // Space Complexity: O(1)
    vector<int> inorderTraversal(TreeNode* root) {

        vector<int> res;
        if( root == NULL )
            return res;

        TreeNode* cur = root;
        while(cur != NULL){

            if(cur->left == NULL){
                res.push_back(cur->val);
                cur = cur->right;
            }
            else{
                TreeNode* prev = cur->left;
                while(prev->right != NULL && prev->right != cur)
                    prev = prev->right;

                if(prev->right == NULL){
                    prev->right = cur;
                    cur = cur->left;
                }
                else{
                    prev->right = NULL;
                    res.push_back(cur->val);
                    cur = cur->right;
                }
            }
        }

        return res;
    }
};

void print_vec(const vector<int>& vec){
    for(int e: vec)
        cout << e << " ";
    cout << endl;
}

int main() {

    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);
    print_vec(Solution().inorderTraversal(root));
    print_vec(Solution().preorderTraversal(root));
    return 0;
}
