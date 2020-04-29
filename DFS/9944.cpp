#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define INF 987654321
using namespace std;

int n, m;
char map[31][31];
bool visited[31][31];
vector<int> dirs[31][31];
//갈 수 있는 방향들만 저장해놓는다.
int cnts[31][31][4];
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
typedef pair<int, int> pp;
typedef pair<pp, pp> pppp;

typedef struct Q
{
    int cnt, dir, x, y;

    Q(int c, int d, int _x, int _y) : cnt(c), dir(d), x(_x), y(_y){};
};

int ans = INF;
void print()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << map[i][j] << ' ';
        }
        cout << '\n';
    }
}
bool checkRange(int x, int y)
{
    if (x < 0 || x >= n || y < 0 || y >= m || map[x][y] == '*')
        return false;
    return true;
}
bool check()
{
    //모두 방문했는지 확인
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (map[i][j] == '.')
            {
                if (!visited[i][j])
                    return false;
            }
        }
    }
    return true;
}
void bfs(int sx, int sy)
{
    queue<Q> q;
    for (int dir : dirs[sx][sy])
    {
        q.push(Q(0, dir, sx, sy));
    }
    memset(visited, 0, sizeof(visited));

    visited[sx][sy] = true;

    while (!q.empty())
    {
        int size = q.size();

        while (size--)
        {
            Q now = q.front();
            q.pop();

            int x = now.x;
            int y = now.y;
            int cnt = now.cnt;
            int dir = now.dir;

            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if (cnts[nx][ny][dir] || visited[nx][ny]) {
                //코너 좌표라면
                
            }
        }
    }
}
// void bfs(int sx, int sy, int d)
// {
//     queue<pppp> q;
//     q.push(pppp(pp(1, d), pp(sx, sy))); //좌표 방향

//     memset(visited, 0, sizeof(visited));

//     visited[sx][sy] = true;

//     while (!q.empty())
//     {

//         int x = q.front().second.first;
//         int y = q.front().second.second;
//         int dir = q.front().first.second;
//         int cnt = q.front().first.first;

//         q.pop();

//         int nx = x;
//         int ny = y;

//         while (nx + dx[dir] >= 0 && nx + dx[dir] < n && ny + dy[dir] >= 0 && ny + dy[dir] < m && map[nx + dx[dir]][ny + dy[dir]] == '.' && !visited[nx + dx[dir]][ny + dy[dir]])
//         {
//             nx += dx[dir];
//             ny += dy[dir];
//             visited[nx][ny] = true;
//         }

//         if (check())
//             ans = min(ans, cnt);
//         else
//         {
//             //갈 수 있는 방향을 정해서 가야한다.
//             for (int i = 0; i < 4; i++)
//             {
//                 if (i == d)
//                     continue;
//                 int nnx = nx + dx[i];
//                 int nny = ny + dy[i];
//                 if (nnx < 0 || nnx >= n || nny < 0 || nny >= m || map[nnx][nny] == '*' || visited[nnx][nny])
//                     continue;

//                 q.push(pppp(pp(cnt + 1, i), pp(nnx, nny)));
//             }
//         }
//     }
// }
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string input;
    int tc = 0;

    ++tc;
    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (map[i][j] == '.')
            {
                //갈 수 있는 방향들과
                //만약 어떤 방향으로 들어왔을 때 내가 방향전환이 되어야하는 좌표라면 그 수를 저장한다.
                for (int d = 0; d < 4; d++)
                {
                    int nx = i + dx[d];
                    int ny = j + dy[d];

                    if (checkRange(nx, ny))
                    {
                        dirs[i][j].push_back(d); //아니라면 갈 수 있는 방향으로 저장해놓는다.
                    }
                    else
                    {
                        cnts[i][j][d]++; //이 방향으로들어오면 cnt++;
                    }
                }
            }
        }
    }
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < m; j++)
    //     {
    //         for (int d = 0; d < 4; d++)
    //         {
    //             cout << cnts[i][j][d] << ' ';
    //         }
    //         cout << '\n';
    //     }
    //     cout << '\n';
    // }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i == 0 || j == 0 || i == n || j == m)
            {
                if (map[i][j] == '.')
                    bfs(i, j);
            }
        }
    }
    cout << "Case " << tc << ": " << ans << '\n';

    return 0;
}