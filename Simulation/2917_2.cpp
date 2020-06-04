#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define INF 987654321
using namespace std;
//BOJ 늑대사냥꾼 [2917](https://www.acmicpc.net/problem/2917)
//unsolved
//TEE

int n, m;
char map[502][502];
bool visited[502][502];
int distMap[502][502];

int sx, sy;
typedef pair<int, int> pp;
vector<pp> trees;
typedef struct Q
{
    int cnt, x, y;
};
int ans = INF;
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
queue<pp> q;
void print()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << distMap[i][j] << ' ';
        }
        cout << '\n';
    }
}
void bfs()
{

    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        int minn = INF;
        for (pp tree : trees)
        {
            int dist = abs(tree.first - x) + abs(tree.second - y);
            minn = min(dist, minn);
        }
        distMap[x][y] = minn;
    }
}
// void dfs(int x, int y, int minn)
// {
//     // cout << x << " " << y << " " << minn << '\n';
//     if (map[x][y] == 'J')
//     {
//         ans = min(ans, min(minn, distMap[x][y]));
//         return;
//     }

//     int maxx = 0;
//     for (int j = 0; j < 4; j++)
//     {
//         int nx = x + dx[j];
//         int ny = y + dy[j];

//         if (nx < 0 || nx >= n || ny < 0 || ny >= m || visited[nx][ny])
//             continue;

//         if (map[nx][ny] == '.')
//         {
//             int dist = distMap[nx][ny];
//             if (dist > maxx)
//             {
//                 maxx = dist;
//             }
//         }
//         else if (map[nx][ny] == 'J')
//         {
//             int dist = distMap[nx][ny];

//             dfs(nx, ny, min(minn, dist));
//         }
//         else if (map[nx][ny] == '+')
//         {
//             int dist = distMap[nx][ny];
//             if (dist > maxx)
//             {
//                 maxx = dist;
//             }
//         }
//     }
//     if (maxx)
//     {

//         for (int j = 0; j < 4; j++)
//         {
//             int nx = x + dx[j];
//             int ny = y + dy[j];

//             if (nx < 0 || nx >= n || ny < 0 || ny >= m || visited[nx][ny])
//                 continue;

//             if (distMap[nx][ny] == maxx)
//             {
//                 visited[nx][ny] = true;
//                 dfs(nx, ny, min(minn, maxx));
//                 visited[nx][ny] = false;
//             }
//         }
//     }
// }

bool check(int day)
{
    queue<pp> chkQ;
    chkQ.push({sx, sy});

    memset(visited, 0, sizeof(visited));

    visited[sx][sy] = true;

    int minn = distMap[sx][sy];
    while (!chkQ.empty())
    {
        int x = chkQ.front().first;
        int y = chkQ.front().second;
        chkQ.pop();

        // cout << x << " " << y << '\n';
        if (map[x][y] == 'J')
        {
            //arrive
            ans = min(ans, minn);
            return true;
        }
        minn = min(minn, distMap[x][y]);

        int maxDist = -1;
        for (int j = 0; j < 4; j++)
        {
            int nx = x + dx[j];
            int ny = y + dy[j];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m || visited[nx][ny])
                continue;

            if (distMap[nx][ny] <= day)
            {
                maxDist = max(maxDist, distMap[nx][ny]);
            }
        }
        if (maxDist >= 0)
        {
            for (int j = 0; j < 4; j++)
            {
                int nx = x + dx[j];
                int ny = y + dy[j];

                if (nx < 0 || nx >= n || ny < 0 || ny >= m || visited[nx][ny])
                    continue;

                if (distMap[nx][ny] == maxDist)
                {
                    visited[nx][ny] = true;
                    chkQ.push({nx, ny});
                }
            }
        }
    }
    return false;
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == 'V')
            {
                q.push({i, j});
                sx = i;
                sy = j;
            }
            else if (map[i][j] == '.' || map[i][j] == 'J')
            {
                q.push({i, j});
            }
            else if (map[i][j] == '+')
            {
                trees.push_back({i, j});
                distMap[i][j] = 0;
            }
        }
    }
    bfs();
    print();

    int left = 0, right = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            right = max(right, distMap[i][j]);
        }
    }

    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (check(mid))
        {
            // cout << "success " << mid << '\n';
            //mid 에 도착할 수 있느지 확인한다.
            right = mid - 1;
        }
        else
        {
            // cout << "fail" << '\n';
            left = mid + 1;
        }
    }

    cout << ans << '\n';
    return 0;
}