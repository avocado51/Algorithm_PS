#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

#define INF 987654321
using namespace std;
//BOJ 연구소3 https://www.acmicpc.net/problem/17142

int n, m, empCnt = 0;
int map[51][51];
bool picked[11];
bool visited[51][51];
int ans = INF;
typedef pair<int, int> pp;
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
vector<pp> virus;

int spreadVirus()
{
    //활성화 바이러스가 있는 칸은 -1로 표시한다.
    queue<pp> q;
    memset(visited, 0, sizeof(visited));
    int cnt = empCnt;

    for (int i = 0; i < virus.size(); i++)
    {
        if (picked[i])
        {
            map[virus[i].first][virus[i].second] = -1;
            q.push(virus[i]);
        }
    }

    int sec = 0;
    while (!q.empty())
    {
        int size = q.size();

        ++sec;

        while (size--)
        {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();

            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx < 0 || nx >= n || ny < 0 || ny >= n || map[nx][ny] == 1 || visited[nx][ny])
                    continue;

                visited[nx][ny] = true;

                if (!map[nx][ny])
                {
                    cnt--;
                    if (!cnt)
                        return sec;
                }

                map[nx][ny] = -1;
                q.push(pp(nx, ny));
            }
        }
    }
    return INF;
}
void dfs(int idx, int cnt)
{
    if (cnt == m)
    {
        int c_map[51][51];
        memcpy(c_map, map, sizeof(map));

        int res = spreadVirus();
        ans = min(ans, res);

        memcpy(map, c_map, sizeof(map));
        return;
    }

    for (int i = idx; i < virus.size(); i++)
    {
        if (!picked[i])
        {
            picked[i] = true;
            dfs(i + 1, cnt + 1);
            picked[i] = false;
        }
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == 2)
            {
                virus.push_back(pp(i, j));
            }
            else if (!map[i][j])
                empCnt++;
        }
    }
    if (!empCnt)
        ans = 0;
    else
    {
        dfs(0, 0);
        if (ans == INF)
            ans = -1;
    }
    cout << ans << '\n';
    return 0;
}