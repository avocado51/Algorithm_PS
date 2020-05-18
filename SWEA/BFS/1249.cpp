#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <functional>
#define INF 987654321
using namespace std;

//SWEA 보급로 [1249](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV15QRX6APsCFAYD)

int map[101][101];
int dp[101][101];
bool visited[101][101][4];
int n;
int ans = INF;
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

typedef struct Q
{
    int cost, dir, x, y;
} Q;

bool operator<(const Q &a, const Q &b)
{
    return a.cost > b.cost;
}
void bfs()
{
    priority_queue<Q> q;
    q.push({0, 0, 0, 0});

    while (!q.empty())
    {
        Q qq = q.top();
        q.pop();

        int cost = qq.cost;
        int dir = qq.dir;
        int x = qq.x;
        int y = qq.y;

        if (x == n - 1 && y == n - 1)
        {
            ans = min(ans, cost);
            continue;
        }

        if (visited[x][y][dir])
            continue;
        visited[x][y][dir] = true;

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= n)
                continue;

            if (dp[x][y] != INF && dp[nx][ny] > dp[x][y] + map[nx][ny])
            {
                dp[nx][ny] = dp[x][y] + map[nx][ny];
                q.push({dp[nx][ny], i, nx, ny});
            }
        }
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++)
    {

        cin >> n;

        memset(visited, 0, sizeof(visited));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                char c;
                cin >> c;
                map[i][j] = c - '0';
                dp[i][j] = INF;
            }
        }
        ans = INF;
        dp[0][0] = 0;
        bfs();

        cout << "#" << tc << " " << ans << '\n';
    }

    return 0;
}