#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // 特殊情况：只有一个元素时，既是极小堆又是极大堆
    if (n == 1) {
        cout << "both" << endl;
        return 0;
    }

    int tp;
    if (a[0] < a[1] || (n > 2 && a[0] < a[2])) {
        tp = 1; // 假定为极小堆
    } else if (a[0] > a[1] || (n > 2 && a[0] > a[2])) {
        tp = 2; // 假定为极大堆
    } else {
        tp = 3; // 可能既是极小堆又是极大堆
    }

    for (int i = 0; i <= (n - 2) / 2; i++) {
        int l = 2 * i + 1;//左子节点
        int r = 2 * i + 2;//右子节点

        if (tp == 1) { // 假设是极小堆
            if ((l < n && a[i] > a[l]) || (r < n && a[i] > a[r])) {
                tp = 0; // 不满足极小堆，设置为不是堆
                break;
            }
        } else if (tp == 2) { // 假设是极大堆
            if ((l < n && a[i] < a[l]) || (r < n && a[i] < a[r])) {
                tp = 0; // 不满足极大堆，设置为不是堆
                break;
            }
        } else { // tp == 3，可能既是极小堆又是极大堆
            if ((l < n && a[i] > a[l]) || (r < n && a[i] > a[r])) {
                tp = 2; // 不满足极小堆，假设为极大堆
            } else if ((l < n && a[i] < a[l]) || (r < n && a[i] < a[r])) {
                tp = 1; // 不满足极大堆，假设为极小堆
            }
        }
    }

    // 根据最终的 tp 值输出结果
    string heap;
    switch (tp) {
        case 0:
            heap = "no";
            break;
        case 1:
            heap = "min heap";
            break;
        case 2:
            heap = "max heap";
            break;
        case 3:
            heap = "both";
            break;
        default:
            break;
    }

    cout << heap << endl;
    return 0;
}
