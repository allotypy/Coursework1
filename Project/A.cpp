#include <bits/stdc++.h>

const int N = 10000;
int n;
int a[N];

// 10000人 Top-10
void solve0() {
    // 读入文件
    freopen("A0.txt", "r", stdin);
    freopen("ans0.txt", "w", stdout);

    // 从文件读入数据
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    // 调用nth_element，O(N)使得前10大的数排在数组a的前10个位置上
    std::nth_element(a, a + 10, a + N, std::greater<>());
    std::cout << "First 10:\n";
    for (int i = 0; i < 10; i++) {
        std::cout << a[i] << " \n"[i == 9];
    }

    // 关闭重定向
    fclose(stdin);
    fclose(stdout);
}

// 在10^9个数中找前1000大
void solve1() {
    freopen("ans1.txt", "w", stdout);

    std::mt19937_64 rng(time(0));
    const int MOD = 1e9;

    n = 1e9;
    std::priority_queue<int, std::vector<int>, std::greater<>> q;
    for (int i = 0; i < n; i++) {
        int x = rng() % MOD;
        q.push(x);
        // 堆大小大于1000，删去堆内最小的元素
        if (q.size() > 1000) {
            q.pop();
        }
    }

    std::cout << "First 1000:\n";
    while (q.size()) {
        if (q.size() == 1)
            std::cout << q.top() << '\n';
        else
            std::cout << q.top() << ' ';
        q.pop();
    }
    std::cout << '\n';

    // 关闭重定向
    fclose(stdout);
}

signed main() {
    //10^4
    solve0();
    //10^9
    solve1();
    return 0;
}