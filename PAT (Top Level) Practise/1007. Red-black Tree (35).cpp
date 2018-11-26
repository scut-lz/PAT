//dp 求有n个区间节点的红黑树的个数
//dp[i][j][k] 表示i个节点(不算叶子节点)的红黑树子树 
//黑树高（路径上黑色节点个数且不算叶子节点）为j 根节点颜色为k的个数
#include<bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
const int N = 505;
const int BLK = 0, RED = 1;
int dp[N][N][2];
using ll = long long;

int main() {
    int n;
    scanf("%d",&n);
    dp[1][1][BLK] = dp[1][0][RED] = dp[0][0][BLK] = 1;
    for(int i = 2; i <= n; i++) {
        for(int j = log2(i+1)/2; j <= log2(i+1)+1; j++) {
            for(int il = 0; il < i/2; il++) {
                dp[i][j][RED] = (ll(dp[i][j][RED]) + 1ll*dp[il][j][BLK]*dp[i-il-1][j][BLK]*2) % mod;
                dp[i][j][BLK] = (ll(dp[i][j][BLK]) + 
                        1ll*(dp[il][j-1][BLK] + dp[il][j-1][RED]) * 
                        (dp[i-il-1][j-1][BLK] + dp[i-il-1][j-1][RED])*2) % mod;
            }
            if(i & 1) {
                int il = i / 2;
                dp[i][j][RED] = (ll(dp[i][j][RED]) + 1ll*dp[il][j][BLK]*dp[i-il-1][j][BLK]) % mod;
                dp[i][j][BLK] = (ll(dp[i][j][BLK]) + 
                        1ll*(dp[il][j-1][BLK] + dp[il][j-1][RED]) * 
                        (dp[i-il-1][j-1][BLK] + dp[i-il-1][j-1][RED])) % mod;
            }
        }
    }
    int res = 0;
    for(int i = 1; i <= n; i++) res = (res + dp[n][i][BLK]) % mod;
    printf("%d\n",res);
    return 0;
}
