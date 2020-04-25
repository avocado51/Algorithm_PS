#include <iostream>
#include <vector>
#include <queue>
#define INF 300001
using namespace std;

int r, c;
int map[501][501];
int ball[501][501];
int dir[501][501];
bool visited[501][501];

int dx[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1}, dy[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

typedef pair<int, int> pp;

void bfs()
{
    queue<pp> q;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (dir[i][j] == 4)
                continue;
            q.push(pp(i, j));
        }
    }

    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if (dir[x][y] == 4 || ball[x][y] == 0)
            continue;

        int cnt = ball[x][y];
        ball[x][y] = 0;

        int nx = x + dx[dir[x][y]];
        int ny = y + dy[dir[x][y]];

        ball[nx][ny] += cnt;
        q.push(pp(nx, ny));
    }
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cout << ball[i][j] << ' ';
        }
        cout << '\n';
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> r >> c;

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> map[i][j];
            ball[i][j] = 1;
        }
    }

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            int minn = map[i][j];
            int idx = 4;
            for (int d = 0; d < 9; d++)
            {
                int nx = i + dx[d];
                int ny = j + dy[d];

                if (nx < 0 || nx >= r || ny < 0 || ny >= c)
                    continue;

                if (minn > map[nx][ny])
                {
                    minn = map[nx][ny];
                    idx = d;
                }
            }

            dir[i][j] = idx;
        }
    }

    bfs();
    return 0;
}