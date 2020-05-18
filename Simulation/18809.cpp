#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define G 3
#define R 4

//BOJ 18809 Gaaaaaaaaaarden https://www.acmicpc.net/problem/18809

using namespace std;
int map[51][51];
int visited[51][51];
bool chk[11];
int n, m, g, r;
int ans = 0;
typedef pair<int, int> pp;
typedef struct Q
{
    int cnt, x, y;
} Q;
vector<pp> pos;

int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};


int spread()
{
    queue<Q> qR, qG;
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < pos.size(); i++)
    {
        if (map[pos[i].first][pos[i].second] == R)
        {
            qR.push({0, pos[i].first, pos[i].second});
        }
        else if (map[pos[i].first][pos[i].second] == G)
        {
            qG.push({0, pos[i].first, pos[i].second});
        }
        // cout << chk[i] << ' ';
    }
    // cout << '\n';

    int res = 0;
    while (!qR.empty() && !qG.empty())
    {
        int size = qG.size();
        while (size--)
        {
            Q q = qG.front();
            qG.pop();

            int cnt = q.cnt;
            int x = q.x;
            int y = q.y;

            if (map[x][y] == 7)
                continue;

            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                    continue;

                if (map[nx][ny] == 0 || map[nx][ny] == 7)
                    continue;

                if (map[nx][ny] == 1 || map[nx][ny] == 2)
                {
                    map[nx][ny] = G;
                    qG.push({cnt + 1, nx, ny});
                    visited[nx][ny] = cnt + 1;
                }
            }
        }

        size = qR.size();

        while (size--)
        {
            Q q = qR.front();
            qR.pop();

            int cnt = q.cnt;
            int x = q.x;
            int y = q.y;

            if (map[x][y] == 7)
                continue;
            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                    continue;

                if (map[nx][ny] == 0 || map[nx][ny] == 7)
                    continue;

                if (7 - map[nx][ny] == R)
                {
                    if (visited[nx][ny] == cnt + 1)
                    {
                        map[nx][ny] = 7;
                        res++;
                    }
                }

                if (map[nx][ny] == 1 || map[nx][ny] == 2)
                {
                    map[nx][ny] = R;
                    qR.push({cnt + 1, nx, ny});
                }
            }
        }
    }
    // cout << res << '\n';
    // print();

    return res;
}
void dfs(int cntR, int cntG, int idx)
{
    //배양액을 뿌릴 땅을 준비
    if (cntR + cntG == r + g)
    {
        //이제 퍼트린다.
        int c_map[51][51];
        memcpy(c_map, map, sizeof(map));
        ans = max(ans, spread());
        memcpy(map, c_map, sizeof(map));
        return;
    }

    for (int i = idx; i < pos.size(); i++)
    {
        if (chk[i])
            continue;

        chk[i] = true;
        if (cntR + 1 <= r)
        {
            map[pos[i].first][pos[i].second] = R;
            dfs(cntR + 1, cntG, i + 1);
        }
        if (cntG + 1 <= g)
        {
            map[pos[i].first][pos[i].second] = G;
            dfs(cntR, cntG + 1, i + 1);
        }
        map[pos[i].first][pos[i].second] = 2;
        chk[i] = false;
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> g >> r;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == 2)
                pos.push_back(pp(i, j));
        }
    }

    dfs(0, 0, 0);
    cout << ans << '\n';
    return 0;
}