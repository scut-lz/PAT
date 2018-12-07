1004 To Buy or Not to Buy - Hard Version （35 point(s)）
Eva would like to make a string of beads with her favorite colors so she went to a small shop to buy some beads. 
There were many colorful strings of beads.
However the owner of the shop would only sell the strings in whole pieces.
Hence in some cases Eva might have to buy several strings to get all the beads she needs.
With a hundred strings in the shop, 
Eva needs your help to tell her whether or not she can get all the beads she needs with the least number of extra beads she has to pay for.

For the sake of simplicity,
let's use the characters in the ranges [0-9], [a-z], and [A-Z] to represent the colors. 
In sample 1, buying the 2nd and the last two strings is the best way since there are only 3 extra beads. 
In sample 2, buying all the three strings won't help since there are three R beads missing.

Input Specification:
Each input file contains one test case. 
Each case first gives in a line the string that Eva wants. 
Then a positive integer N (≤100) is given in the next line, followed by N lines of strings that belong to the shop. 
All the strings contain no more than 1000 beads.

Output Specification:
For each test case, print your answer in one line. 
If the answer is Yes, then also output the least number of extra beads Eva has to buy; 
or if the answer is No, then also output the number of beads missing from all the strings.
There must be exactly 1 space between the answer and the number.

Sample Input 1:
RYg5
8
gY5Ybf
8R5
12346789
gRg8h
5Y37
pRgYgbR52
8Y
8g
Sample Output 1:
Yes 3
Sample Input 2:
YrRR8RRrY
3
ppRGrrYB225
8ppGrrB25
Zd6KrY
Sample Output 2:
No 3

#include <bits/stdc++.h>
using namespace std;

// 1. 压缩字符串为一个62维度向量
// 2. 深搜+回溯
// 3. 剪枝（1. 是否已经超过最优解 2. 所有加在一个是否满足要求 3. 试求一个解，缩小搜索深度）
const int maxn = 62;

int getPos(char ch) {
    if ('0' <= ch && ch <= '9') return ch - '0';
    else if ('a' <= ch && ch <= 'z') return ch -'a' + 10;
    else if ('A' <= ch && ch <= 'Z') return ch -'A' + 36;
}

vector<int> computeColorVec(string bead) { // 压缩字符串为一个62维度向量 0-9a-zA-Z
    vector<int> vec(maxn, 0);
    for (auto &c : bead)
        vec[getPos(c)]++;
    return vec;
}

void dfs(
    unordered_map<int, vector<vector<int>>> &G,
    vector<vector<bool>> &isUsed,
    vector<int> missing,
    int extra_cnt,
    int &extra_ans) {

    int pos = -1;
    for (int i = 0; i < maxn; i++) {
        if (missing[i] > 0) {
            pos = i;
            break;
        }
    }
    if (extra_cnt >= extra_ans) return; // 如果当前答案没有存的答案更优秀，剪枝掉
    if (pos == -1) { // 找到一个可行解
        extra_ans = min(extra_ans, extra_cnt);
        return;
    }

    for (int i = 0; i < G[pos].size(); i++) {

        if (isUsed[pos][i]) continue; // G[pos][i]的bead已经在搜索中用过了，就跳过

        vector<int> missing_copy(missing);
        int extra_cnt_copy = extra_cnt;
        for (int j = 0; j < maxn; j++) { // 更新missing
            int v = missing[j] - G[pos][i][j];
            if (v <= 0) {
                missing[j] = 0;
                extra_cnt += -v;
            } else missing[j] = v;
        }

        isUsed[pos][i] = true;
        dfs(G, isUsed, missing, extra_cnt, extra_ans); // 进行下一层搜索
        // 回溯变量
        extra_cnt = extra_cnt_copy;
        missing = vector<int>(missing_copy);
        isUsed[pos][i] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    int n, extra_ans = INT_MAX;
    string eva_wants, bead;
    unordered_map<int, vector<vector<int>>> G;
    cin >> eva_wants >> n;
    auto eva_wants_vec = computeColorVec(eva_wants);
    vector<int> all(maxn, 0);
    for (int i = 0; i < n; i++) {
        cin >> bead;
        auto vec = computeColorVec(bead);
        vector<bool> isPushBack(maxn, false);

        bool ok = true;
        int diff = 0;
        for (int i = 0; i < maxn; i++) { // 如果有一个bead可以满足答案，缩小extra_ans的范围，可以剪枝，
            if (eva_wants_vec[i] > vec[i]) {
                ok = false;
                break;
            } else diff += vec[i] - eva_wants_vec[i];
        }
        if (ok) extra_ans = min(extra_ans, diff);

        for (auto &c : bead) {
            all[getPos(c)]++;
            if (!isPushBack[getPos(c)])
                G[getPos(c)].push_back(vec);
            isPushBack[getPos(c)] = true;
        }
    }
    int missing_ans = 0;
    for (int i = 0; i < maxn; i++) { // 如果所有bead都没法满足，就没必要继续搜索
        int v = all[i] - eva_wants_vec[i];
        if (v < 0) missing_ans += -v;
    }

    if (missing_ans != 0) cout << "No " << missing_ans << endl;
    else {
        vector<vector<bool>> isUsed(maxn, vector<bool>(101, false));
        dfs(G, isUsed, eva_wants_vec, 0, extra_ans);
        cout << "Yes " << extra_ans << endl;
    }
    return 0;
}

