#include<iostream>
#include<map>
#include<algorithm>
#include<vector>
using namespace std;
const int SIZE = 105;
int mat[SIZE][SIZE];  /*图矩阵*/
int dp[SIZE],P[SIZE];
int mx,N,M,a,b,ans_sum;
int stack[SIZE][SIZE];
map<int, int> IDCache;
vector<int> ICache,path,ans,list;
int ID(int x) {
    if (IDCache.count(x)) return IDCache[x];
    ICache.push_back(x);
    return IDCache[x] = ICache.size() - 1;
}
void dfs(int NN, int num, int step) {
    if (num == 0) {
        if (step > mx) {
            mx = step;
            ans = path;
            ans_sum = 0;
            for (int i = 0; i < path.size(); ++i)
                ans_sum += P[path[i]];
        }
        else if (step == mx) {
            int sum = 0;
            for (int i = 0; i < path.size(); ++i)
                sum += P[path[i]];
            if (sum < ans_sum)
                ans = path, ans_sum = sum;
        }
        return;
    }
    for (int i = 0; i<num; i++) {
        int k = stack[step][i];
        if (step + NN - k < mx) return;
        if (step + dp[k] < mx) return;
        int cnt = 0;
        for (int j = i + 1; j < num; j++) {
            int k2 = stack[step][j];
            if (mat[k][k2]) {
                stack[step + 1][cnt++] = k2;
            }
        }
        path.push_back(k);
        dfs(NN, cnt, step + 1);
        path.pop_back();
    }
}

void run(int NN) {
    mx = 0;
    for (int i = NN - 1; i >= 0; i--) {
        int sz = 0;
        for (int j = i + 1; j<NN; j++)
            if (mat[i][j]) stack[1][sz++] = j;
        path.push_back(i);
        dfs(NN, sz, 1);
        path.pop_back();
        dp[i] = mx;
    }
}
int main() {
    cin >> N >> M;
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < M; ++j)
            if(i!=j) mat[i][j] = 1;
    for (int i = 0; i < N; ++i)
        cin >> a >> b,list.push_back(a),list.push_back(b);
    for (int i = 0; i < M; ++i)
        cin >> a >> b, P[ID(a)] = b;
    for (int i = 0; i < N; ++i) {
        a = list.back(), list.pop_back(), b = list.back(), list.pop_back();
        if (IDCache.count(a) && IDCache.count(b))
            mat[ID(a)][ID(b)] = mat[ID(b)][ID(a)] = 0;
    }
    run(M);
    for (int i = 0; i < ans.size(); ++i)
        path.push_back(ICache[ans[i]]);
    sort(path.begin(), path.end());
    printf("%d\n", mx);
    for (int i = 0; i < path.size(); ++i)
        if (i != path.size() - 1) printf("%03d ", path[i]);
        else printf("%03d\n%d\n", path[i], ans_sum);
}
