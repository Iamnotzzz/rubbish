#include<iostream>
#include<vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 插入节点到二叉搜索树
TreeNode* insertNode(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val)
        root->left = insertNode(root->left, val);
    else
        root->right = insertNode(root->right, val);
    return root;
}

// 中序遍历
void inorderTraversal(TreeNode* root, vector<int>& result) {
    if (!root) return;
    inorderTraversal(root->left, result);
    result.push_back(root->val);
    inorderTraversal(root->right, result);
}

// 先序遍历
void preorderTraversal(TreeNode* root, vector<int>& result) {
    if (!root) return;
    result.push_back(root->val);
    preorderTraversal(root->left, result);
    preorderTraversal(root->right, result);
}

int main() {
    int m;
    while (cin >> m && m != 0) {  // 读取数据直到遇到0
        vector<int> nums(m);
        for (int i = 0; i < m; ++i) {
            cin >> nums[i];
        }

        // 构建二叉搜索树
        TreeNode* root = nullptr;
        for (int val : nums) {
            root = insertNode(root, val);
        }

        // 获取中序遍历结果
        vector<int> inorderResult;
        inorderTraversal(root, inorderResult);
        
        // 获取先序遍历结果
        vector<int> preorderResult;
        preorderTraversal(root, preorderResult);

        // 输出中序遍历结果
        for (int i = 0; i < inorderResult.size(); ++i) {
            if (i > 0) cout << " ";
            cout << inorderResult[i];
        }
        cout << endl;

        // 输出先序遍历结果
        for (int i = 0; i < preorderResult.size(); ++i) {
            if (i > 0) cout << " ";
            cout << preorderResult[i];
        }
        cout << endl;
    }
    return 0;
}