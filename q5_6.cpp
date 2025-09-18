#include <iostream>
#include <vector>
#include <list>
#include <fstream>
using namespace std;


/*
让我们用简单的图来演示：顶点{1,2,3,4,5}，边{(1,2), (3,4), (4,5)}
初始状态：
C: [_, 1, 2, 3, 4, 5]
L[1]: [1]  L[2]: [2]  L[3]: [3]  L[4]: [4]  L[5]: [5]
处理边(1,2)：
C[1]=1, C[2]=2, 不相等，需要合并
old_component=1, new_component=2

步骤1：更新C[1]=2
C: [_, 2, 2, 3, 4, 5]

步骤2：L[2].splice(end, L[1])
L[1]: []  L[2]: [1,2]  L[3]: [3]  L[4]: [4]  L[5]: [5]
处理边(3,4)：
C[3]=3, C[4]=4, 不相等，需要合并
old_component=3, new_component=4

更新后：
C: [_, 2, 2, 4, 4, 5]
L[1]: []  L[2]: [1,2]  L[3]: []  L[4]: [3,4]  L[5]: [5]
处理边(4,5)：
C[4]=4, C[5]=5, 不相等，需要合并
old_component=4, new_component=5

更新后：
C: [_, 2, 2, 5, 5, 5]
L[1]: []  L[2]: [1,2]  L[3]: []  L[4]: []  L[5]: [3,4,5]
最终结果：
连通分量1：L[2] = [1,2]
连通分量2：L[5] = [3,4,5]
*/



int main() {
    ifstream file("graph2.txt");
    
    int n; // 顶点数
    file >> n;
    
    // 1. 创建vector<list<int>> L，大小为顶点数+1（因为顶点从1开始编号）
    vector<list<int>> L(n + 1);
    
    // 2. 初始化：对于i = 1...n，将i插入L[i]
    for (int i = 1; i <= n; i++) {
        L[i].push_back(i);
    }
    
    // 3. 创建vector<int> C，C[i]表示顶点i属于哪个连通分量
    vector<int> C(n + 1);
    for (int i = 1; i <= n; i++) {
        C[i] = i;
    }
    
    // 4. 处理每条边
    int a, b;
    while (file >> a >> b) {
        // 如果C[a] == C[b]，则不做任何操作（已经在同一连通分量中）
        if (C[a] != C[b]) {
            // 合并连通分量：将L[C[a]]中的所有元素移到L[C[b]]
            int old_component = C[a];
            int new_component = C[b];
            
            // 对于L[C[a]]中的所有顶点x，设置C[x] = C[b]
            for (int x : L[old_component]) {
                C[x] = new_component;
            }
            
            // 将L[C[a]]追加到L[C[b]]，然后清空L[C[a]]
            L[new_component].splice(L[new_component].end(), L[old_component]);
        }
    }
    
    file.close();
    
    // 5. 统计连通分量数量并输出
    int component_count = 0;
    cout << "components:" << endl;
    
    for (int i = 1; i <= n; i++) {
        if (!L[i].empty()) {
            component_count++;
            cout << i << ": ";
            
            // 输出该连通分量中的所有顶点
            bool first = true;
            for (int vertex : L[i]) {
                if (!first) cout << ", ";
                cout << vertex;
                first = false;
            }
            cout << endl;
        }
    }
    
    cout << "Total components: " << component_count << endl;
    
    system("pause");
    return 0;
}

// 如果需要更高效的版本（方案3：保存C[a]的值），可以使用以下代码：
/*
int main() {
    ifstream file("graph2.txt");
    
    int n;
    file >> n;
    
    vector<list<int>> L(n + 1);
    vector<int> C(n + 1);
    
    // 初始化
    for (int i = 1; i <= n; i++) {
        L[i].push_back(i);
        C[i] = i;
    }
    
    int a, b;
    while (file >> a >> b) {
        if (C[a] != C[b]) {
            // 保存C[a]的值，避免在循环中被修改
            int saved_component_a = C[a];
            int component_b = C[b];
            
            // 先执行step 2：更新C值
            for (int x : L[saved_component_a]) {
                C[x] = component_b;
            }
            
            // 再执行step 3：合并列表并清空
            L[component_b].splice(L[component_b].end(), L[saved_component_a]);
        }
    }
    
    file.close();
    
    // 输出结果
    cout << "components:" << endl;
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (!L[i].empty()) {
            count++;
            cout << i << ": ";
            bool first = true;
            for (int v : L[i]) {
                if (!first) cout << ", ";
                cout << v;
                first = false;
            }
            cout << endl;
        }
    }
    
    return 0;
}
*/