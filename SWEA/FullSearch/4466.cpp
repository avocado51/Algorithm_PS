#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
//SWEA 최대 성적표 만들기 [4466](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWOUfCJ6qVMDFAWg&)

int n, k;
int score[101];
int ans = 0;

bool compare(const int &a, const int &b)
{
    return a > b;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++)
    {
        cin >> n >> k;
        //n개 중 k개를 고른다.
        for (int i = 0; i < n; i++)
            cin >> score[i];

        ans = 0;
        // dfs(0, 0, 0);
        sort(score, score + n, compare);

        for (int i = 0; i < k; i++)
        {
            ans += score[i];
        }
        cout << "#" << tc << " " << ans << '\n';
    }
    return 0;
}