#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<string>
#include<map>
#include<queue>
#include<vector>
using namespace std;
#define ll long long int
#define INF 0x3f3f3f3f
#define Irish_Moonshine main
const int maxn = 1e6 + 10;
char str[maxn];
ll dp[maxn][3];
int Irish_Moonshine()
{
    scanf("%s", str);
    int len = strlen(str);
    for (int i = 0; i <= len; i++) dp[i][0] = 1;
    dp[0][1] = 1;
    for (int i = 1; i < len; i++){
        dp[i][1] = dp[i - 1][0] + dp[i - 1][1];
        if (str[i] == str[i - 1]) dp[i][1]--;

    }
    dp[1][2] = 1;
    for (int i = 2; i < len; i++){
        dp[i][2] = dp[i - 1][1] + dp[i - 1][2];
        if (str[i] == str[i - 1]) dp[i][2] -= dp[i - 2][1];
        else if (str[i] == str[i - 2]) dp[i][2]--;
    }
    ll ans = dp[len - 1][0] + dp[len - 1][1] + dp[len - 1][2];
    printf("%lld\n", ans);
    return 0;
}
