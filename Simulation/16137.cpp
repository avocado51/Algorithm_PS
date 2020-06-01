#include <iostream>
#include <vector>
#include <queue>

using namespace std;
//BOJ 견우와 직녀 [16137](https://www.acmicpc.net/problem/16137)

int n, m;
int map[11][11];
typedef struct Q
{
    int time, x, y;
    bool prev, built;
};
bool visited[11][11][2];
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
int cdx[4][2] = {{0, 2}, {0, 3}, {1, 2}, {1, 3}};
int ans = 987654321;

bool operator<(const Q &q1, const Q &q2)
{
    return q1.time > q2.time;
}
void bfs()
{
    priority_queue<Q> q;
    q.push({0, 0, 0, 0, 0});

    visited[0][0][0] = 1;

    while (!q.empty())
    {
        Q qq = q.top();
        q.pop();

        int x = qq.x;
        int y = qq.y;
        int time = qq.time;
        bool prev = qq.prev;
        bool built = qq.built;

        if (x == n - 1 && y == n - 1)
        {
            ans = min(ans, time);
            continue;
        }

        bool flag = false;
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= n || visited[nx][ny][built])
                continue;

            if (map[nx][ny] == 1)
            {
                // flag = true;
                visited[nx][ny][built] = 1;
                q.push({time + 1, nx, ny, false, built});
            }

            else if (!prev)
            {
                if (map[nx][ny] == 0)
                {
                    if (built)
                        continue;
                    if (((time + 1) % m) == 0)
                    {
                        visited[nx][ny][true] = 1;
                        q.push({time + 1, nx, ny, true, true});
                    }
                    else
                    {
                        visited[nx][ny][true] = 1;
                        int tmp = m;
                        while (tmp <= time)
                        {
                            tmp += m;
                        }
                        q.push({tmp, nx, ny, true, true});
                    }
                }
                else if (map[nx][ny] >= 2)
                {
                    //주기가 맞으면 ok
                    if (((time + 1) % map[nx][ny]) == 0)
                    {
                        // flag = true;
                        visited[nx][ny][built] = 1;
                        q.push({time + 1, nx, ny, true, built});
                    }
                    else
                    {
                        // flag = true;
                        visited[nx][ny][built] = 1;
                        int tmp = map[nx][ny];
                        while (tmp <= time)
                        {
                            tmp += map[nx][ny];
                        }
                        q.push({tmp, nx, ny, true, built});
                    }
                }
            }
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
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!map[i][j])
            {
                for (int k = 0; k < 4; k++)
                {
                    int cnt = 0;
                    for (int d = 0; d < 2; d++)
                    {
                        int nx = i + dx[cdx[k][d]];
                        int ny = j + dy[cdx[k][d]];
                        if (nx < 0 || nx >= n || ny < 0 || ny >= n)
                            continue;
                        if (map[nx][ny] <= 0)
                            cnt++;
                    }
                    if (cnt == 2)
                    {
                        map[i][j] = -1;
                        break;
                    }
                }
            }
        }
    }
    bfs(); //전이 절벽인지 아닌지 확인

    cout << ans << '\n';
    return 0;
}
/*
8 2 

1 1 1 1 0 1 1 1 

1 1 0 1 0 1 0 1 

0 0 0 1 1 1 0 1 

0 0 0 0 0 0 0 1 

0 0 0 0 0 1 0 1 

0 0 0 0 0 1 1 1 

0 0 0 0 0 0 0 10 

0 0 0 0 0 0 1 1

ans = 20

3 3 

1 1 1 

1 1 1 

1 1 1 

Answer = 4; 

5 5 

1 2 1 2 1 

1 2 1 2 1 

1 2 1 2 1 

1 2 1 2 1 

1 2 1 2 1 

Answer = 8; 



4 3 

1 1 100 100 

1 1 100 100 

0 0 1 1 

1 0 1 1 

Answer = 103 

(* 데이터 입력 범위를 벗어나지만 넣어놨습니다.)  

4 3 

1 1 20 20 

1 1 20 20 

0 0 1 1 

1 0 1 1 

 Answer = 23; 


 만드신 분 : sangdo913 



5 10 

1 1 2 3 1 

1 1 0 0 1 

13 0 0 0 1 

1 1 1 1 1 

1 1 1 1 1 

 Answer = 15;

 2 2

1 0

0 1
ans = 3

*/