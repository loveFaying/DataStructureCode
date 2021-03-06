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

class Solution_preOrder {

public:

    // Another Classic Non-Recursive algorithm for preorder traversal
    // Time Complexity: O(n), n is the node number in the tree
    // Space Complexity: O(h), h is the height of the tree
    vector<int> preorderTraversal(TreeNode* root) {

        vector<int> res;
        if(root == NULL)
            return res;

        stack<TreeNode*> stack;
        TreeNode* cur = root;
        while(cur != NULL || !stack.empty()){
            if(cur != NULL){
                res.push_back(cur->val);
                stack.push(cur);
                cur = cur->left;
            }
            else{
                cur = stack.top();
                stack.pop();
                cur = cur->right;
            }
        }
        return res;
    }

    // Another Classic Non-Recursive algorithm for preorder traversal
    // Time Complexity: O(n), n is the node number in the tree
    // Space Complexity: O(h), h is the height of the tree
    vector<int> preorderTraversal2(TreeNode* root) {

        vector<int> res;
        if(root == NULL)
            return res;

        stack<TreeNode*> stack;
        TreeNode* cur = root;
        while(cur != NULL || !stack.empty()){
            while(cur != NULL){
                res.push_back(cur->val);
                stack.push(cur);
                cur = cur->left;
            }

            cur = stack.top();
            stack.pop();
            cur = cur->right;
        }
        return res;
    }

    // Classic Non-Recursive algorithm for preorder traversal
    // Time Complexity: O(n), n is the node number in the tree
    // Space Complexity: O(h), h is the height of the tree
    vector<int> preorderTraversal3(TreeNode* root) {

        vector<int> res;
        if(root == NULL)
            return res;

        stack<TreeNode*> stack;
        stack.push(root);
        while(!stack.empty()){
            TreeNode* curNode = stack.top();
            stack.pop();
            res.push_back(curNode->val);

            if(curNode->right)
                stack.push(curNode->right);
            if(curNode->left)
                stack.push(curNode->left);
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
    vector<int> res = Solution_preOrder().preorderTraversal(root);
    print_vec(res);
    res = Solution_preOrder().preorderTraversal2(root);
    print_vec(res);
    res = Solution_preOrder().preorderTraversal3(root);
    print_vec(res);

    return 0;
}
