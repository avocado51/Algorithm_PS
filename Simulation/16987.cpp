#include <iostream>
#include <vector>

using namespace std;

int n;
typedef pair<int, int> pp;
int s[9], w[9];
int ans = 0;
bool chk[9][9];
bool flag = false;
void calc()
{
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] <= 0)
            res++;
    }

    ans = max(ans, res);
}
void dfs(int cnt)
{
    if (cnt == n)
    {
        //총 n번만 칠수 있다.
        //가장 오른쪽 계란을 들 차례가 되면 끝나야 하기 때문에
        return;
    }

    bool flag = false;
    for (int i = 0; i < n; i++)
    {
        if (i != cnt && s[i] > 0 && s[cnt] > 0)
        {
            flag = true;
            s[cnt] = s[cnt] - w[i];
            s[i] = s[i] - w[cnt];
            calc();
            dfs(cnt + 1);
            s[cnt] = s[cnt] + w[i];
            s[i] = s[i] + w[cnt];
        }
    }
    if (!flag)
        dfs(cnt + 1);
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> s[i] >> w[i];
    }

    if (n == 1)
        cout << 0 << '\n';
    else
    {
        dfs(0);
        cout << ans << '\n';
    }
    return 0;
}