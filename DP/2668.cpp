//숫자고르기
#include <iostream>
#include <vector>

using namespace std;
//백준 숫자고르기 https://www.acmicpc.net/problem/2668
//unsolved

bool visited[101];
int ans = 0;
vector<int> v[101];
vector<int> res;
void dfs(int idx, int prev)
{
    for (int i = 0; i < v[idx].size(); i++)
    {
        //현재 수에 연결된 수를 모두 훓는다.
        //연결된 수가 없는 경우에는 뽑힐 수 없다.
        if (!visited[v[idx][i]] && v[idx][i] == prev)
        {
            visited[v[idx][i]] = true;
            res.push_back(v[idx][i]);
            ans = ans < res.size() ? res.size() : ans;
            dfs(v[idx][i], idx);
            res.pop_back();
            visited[v[idx][i]] = false;
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        int tmp;
        cin >> tmp;

        v[i].push_back(tmp);
    }
    //v[i].size()가 0이면 뽑히지 않는다.

    for (int i = 1; i <= n; i++)
    {
        if (!visited[i] && v[i].size() > 0)
        {
            visited[i] = true;

            res.push_back(i);
            dfs(v[i][0], i);
            cout << '\n';
            for (int j = 0; j < res.size(); j++)
                cout << res[j] << ' ';
            cout << '\n';
            res.pop_back();
            visited[i] = true;
        }
    }
    cout << ans << '\n';

    return 0;
}
