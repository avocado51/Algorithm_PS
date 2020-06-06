#include <iostream>
#include <vector>
#include <cstring>
#define INF 987654321
using namespace std;

//BOJ 감시 [15683](https://www.acmicpc.net/problem/15683)

int cctv_dir[6][4][4] = {
    {},
    {{0}, {1}, {2}, {3}},
    {{0, 2}, {1, 3}, {0, 2}, {1, 3}},
    {{0, 1}, {1, 2}, {2, 3}, {3, 0}},
    {{0, 1, 2}, {1, 2, 3}, {2, 3, 0}, {3, 0, 1}},
    {{0, 1, 2, 3}, {0, 1, 2, 3}, {0, 1, 2, 3}, {0, 1, 2, 3}}

};
int cctv_cnt[6] = {0, 1, 2, 2, 3, 4}; //한번에 탐색할 수 있는 방향의 횟수
int ans = INF;
int n, m;
int map[9][9];
bool visited[9][9];
typedef struct TV
{
    int x, y;
};
vector<TV> cctvs;

int dx[4] = {0, -1, 0, 1}, dy[4] = {1, 0, -1, 0};
//^ V < >
int emptyPlace = 0;

void print()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (map[i][j])
                cout << map[i][j];
            else if (visited[i][j])
            {
                cout << "#";
            }
            else
                cout << map[i][j];
        }
        cout << '\n';
    }
}
bool checkRange(int x, int y)
{
    if (x < 0 || x >= n || y < 0 || y >= m || map[x][y] == 6)
        return false;
    return true;
}
void dfs(int idx, int res)
{
    if (idx == cctvs.size())
    {
        ans = min(ans, res);
        return;
    }
    int x = cctvs[idx].x;
    int y = cctvs[idx].y;

    for (int j = 0; j < 4; j++)
    {
        int cnt = cctv_cnt[map[x][y]];
        int removed = res;
        bool chk[9][9];
        memcpy(chk, visited, sizeof(visited));

        for (int k = 0; k < cnt; k++)
        {
            int dir = cctv_dir[map[x][y]][j][k];
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            while (checkRange(nx, ny))
            {
                //이미 사각지대가 아님
                //사각지대의 시작
                // cout << x << " " << y << " " << nx << " " << ny << '\n';
                if (1 <= map[nx][ny] && map[nx][ny] <= 5)
                {
                    nx += dx[dir];
                    ny += dy[dir];
                }
                //cctv끼리는 통과할 수 있다.
                else if (!visited[nx][ny] && !map[nx][ny])
                {
                    removed--;
                    visited[nx][ny] = true;
                    nx += dx[dir];
                    ny += dy[dir];
                }
                else
                {
                    nx += dx[dir];
                    ny += dy[dir];
                }
            }
        }
        // cout << idx << '\n';
        // print();
        dfs(idx + 1, removed);
        memcpy(visited, chk, sizeof(visited));
        //보낸다.
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie();

    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
            if (1 <= map[i][j] && map[i][j] <= 5)
            {
                //cctv
                cctvs.push_back({i, j});
            }
            else if (!map[i][j])
                emptyPlace++;
        }
    }

    dfs(0, emptyPlace);
    cout << ans << '\n';
    return 0;
}