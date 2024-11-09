#include <iostream>
#include <vector>
using namespace std;

void postorder(int *pre,int *in,int pref,int pree,int inf,int ine,vector<int>&result){
    if(pref>pree||inf>ine){
        return;
    }
    int root=pre[pref];
    int root_posin;
    for(root_posin=inf;root_posin<ine+1;root_posin++){
        if(in[root_posin]==root){
            break;
        }
    }
    int leftnum=root_posin-inf;
    int rightnum=ine-root_posin;
    
    postorder(pre,in,pref+1,pref+leftnum,inf,root_posin-1,result);
    postorder(pre,in,pref+1+leftnum,pref+leftnum+rightnum,root_posin+1,ine,result);
    result.push_back(root);
}

int main() {
    int n;
    cin >> n;
    
    int preorder[n],inorder[n];
    
    // 输入前序遍历和中序遍历
    for (int i = 0; i < n; ++i) {
        cin >> preorder[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> inorder[i];
    }
    
    // 存储后序遍历结果
    vector<int> result;
    
    // 调用后序遍历函数
    postorder(preorder, inorder, 0, n - 1, 0, n - 1, result);
    
    // 输出后序遍历序列
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << " ";
    }
    cout << endl;
    
    return 0;
}
