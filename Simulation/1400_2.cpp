#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define INF 987654321

using namespace std;
//BOJ 화물차 [1400](https://www.acmicpc.net/problem/1400)
//unsolved

int m, n;
char map[21][21];
typedef pair<int, int> pp;
int ans;
typedef struct Q
{
    int time, x, y;
};

typedef struct Signal
{
    char dir;
    int garo, sero;
};

Signal sign[10];

bool visited[21][21];
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

bool operator<(const Q &a, const Q &b)
{
    return a.time > b.time;
}
void bfs(int x, int y)
{
    memset(visited, 0, sizeof(visited));
    priority_queue<Q> q;
    q.push({0, x, y});

    while (!q.empty())
    {
        Q qq = q.top();
        q.pop();

        int time = qq.time;
        int xx = qq.x;
        int yy = qq.y;

        visited[xx][yy] = true;

        for (int j = 0; j < 4; j++)
        {
            int nx = xx + dx[j];
            int ny = yy + dy[j];

            if (nx < 0 || nx >= m || ny < 0 || ny >= n || visited[nx][ny] || map[nx][ny] == '.')
                continue;

            if (map[nx][ny] == 'B')
            {
                ans = time + 1;
                return;
            }
            if (map[nx][ny] == '#')
            {
                q.push({time + 1, nx, ny});
            }

            else
            {
                Signal now = sign[map[nx][ny] - '0'];
                int sum = now.garo + now.sero;

                if (now.dir == '-')
                {
                    if (time + 1 <= sum)
                    {
                        //한 사이클을 돌기 전이다.
                        if (time + 1 <= now.garo)
                        {
                            //가로방향으로 흐르고 있다.
                            if (j >= 2)
                                q.push({time + 1, nx, ny});
                            else
                                q.push({time + (now.garo - time) + 1, nx, ny});
                        }
                        else
                        {
                            //세로로 흐르고있다.
                            if (j >= 2)
                            {
                                //가로로 가고 싶을 때
                                q.push({time + (sum - time) + 1, nx, ny});
                            }
                            else
                                q.push({time + 1, nx, ny});
                        }
                    }
                    else if ((time + 1) % sum == 1)
                    {
                        //다음이 한 사이클째이다.
                        //가로로 먼저 흐를때
                        if (j >= 2)
                        {
                            q.push({time + 1, nx, ny});
                        }
                        else
                        {
                            q.push({time + now.garo + 1, nx, ny});
                        }
                    }
                    else
                    {
                        //시뮬레이션 계산
                        //가로 먼저
                        int mod = (time + 1) % sum;
                        if (mod <= now.garo)
                        {
                            //가로 방향으로 흐른다.
                            if (j >= 2)
                            {
                                q.push({time + 1, nx, ny});
                            }
                            else
                            {
                                q.push({time + (now.garo - mod + 1) + 1, nx, ny});
                            }
                        }
                        else
                        {
                            //세로방향으로 흐른다.
                            if (j >= 2)
                            {
                                q.push({time + (sum - mod + 1) + 1, nx, ny});
                            }
                            else
                                q.push({time + 1, nx, ny});
                        }
                    }
                }
                else
                {
                    //세로부터시작했음
                    if (time + 1 <= sum)
                    {
                        //한 사이클을 돌기 전이다.
                        if (time + 1 <= now.sero)
                        {
                            //가로방향으로 흐르고 있다.
                            if (j < 2)
                                q.push({time + 1, nx, ny});
                            else
                                q.push({time + (now.sero - time) + 1, nx, ny});
                        }
                        else
                        {
                            //세로로 흐르고있다.
                            if (j < 2)
                            {
                                //가로로 가고 싶을 때
                                q.push({time + (sum - time) + 1, nx, ny});
                            }
                            else
                                q.push({time + 1, nx, ny});
                        }
                    }
                    else if ((time + 1) % sum == 1)
                    {
                        //다음이 한 사이클째이다.
                        //가로로 먼저 흐를때
                        if (j < 2)
                        {
                            q.push({time + 1, nx, ny});
                        }
                        else
                        {
                            q.push({time + now.sero + 1, nx, ny});
                        }
                    }
                    else
                    {
                        //시뮬레이션 계산
                        //가로 먼저
                        int mod = (time + 1) % sum;
                        if (mod <= now.sero)
                        {
                            //가로 방향으로 흐른다.
                            if (j < 2)
                            {
                                q.push({time + 1, nx, ny});
                            }
                            else
                            {
                                q.push({time + (now.sero - mod + 1) + 1, nx, ny});
                            }
                        }
                        else
                        {
                            //세로방향으로 흐른다.
                            if (j < 2)
                            {
                                q.push({time + (sum - mod + 1) + 1, nx, ny});
                            }
                            else
                                q.push({time + 1, nx, ny});
                        }
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

    while (1)
    {

        cin >> m >> n;
        if (!m)
        {
            break;
        }

        int sx, sy;
        int maxx = -1;
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < n; k++)
            {
                cin >> map[j][k];
                if (map[j][k] == 'A')
                {
                    sx = j;
                    sy = k;
                }
                else if ('0' <= map[j][k] && map[j][k] <= '9')
                {
                    maxx = maxx > (map[j][k] - '0') ? maxx : (map[j][k] - '0');
                }
            }
        }

        char dir;
        int idx, garo, sero;

        if (maxx > -1)
        {
            for (int i = 0; i <= maxx; i++)
            {
                cin >> idx >> dir >> garo >> sero;
                sign[i] = {dir, garo, sero};
            }
        }

        ans = INF;
        bfs(sx, sy);

        if (ans == INF)
            cout << "impossible" << '\n';
        else
            cout << ans << '\n';
    }
    return 0;
}