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
int calc(int x, int y, int time, int j)
{

    //방향이 맞으면 가고 아니면 기다림
    Signal now = sign[map[x][y] - '0'];
    int sum = now.garo + now.sero;

    if (time < sum)
    {
        if (now.dir == '-')
        {
            if (time < now.garo)
            {
                //가로 방향으로 신호등이 켜짐
                //가로방향으로가고 있으면 계속 갈 수 있다.
                if (j >= 2)
                {
                    return time + 1;
                }
                else
                {
                    //기다렸다가 간다.
                    return time + (now.garo - time) + 1;
                }
            }
            else
            {
                //세로방향으로 신호등이 켜짐
                if (j < 2)
                {
                    return time + 1;
                }
                else
                {
                    return time + (sum - time) + 1;
                }
            }
        }
        else
        {
            //세로-> 가로-> 세로-> 가로
            if (time < now.sero)
            {
                if (j < 2)
                {
                    return time + 1;
                }
                else
                {
                    return time + (now.sero - time) + 1;
                }
            }
            else
            {
                //가로 방향으로 바뀜
                if (j >= 2)
                {
                    return time + 1;
                }
                else
                {
                    return time + (sum - time) + 1;
                }
            }
        }
    }
    else if ((time) % sum == 0)
    {
        //사이클을 딱 돌았음
        //방향만 확인
        if (now.dir == '-')
        {
            if (j < 2)
            {
                //기다림
                return time + now.garo;
            }
            else
            {
                return time + 1;
            }
        }
        else
        {
            if (j < 2)
            {
                return time + 1;
            }
            else
            {
                return time + now.sero;
            }
        }
    }
    else
    {
        //이제 계산 시작
        int sum = now.garo + now.sero;
        int mod = (time) % sum;
        if (now.dir == '-')
        {
            if (mod <= now.garo)
            {
                //가로 방향으로 켜져있음
                if (j >= 2)
                {
                    return time + 1;
                }
                else
                {
                    return time + (now.garo - mod) + 1;
                }
            }
            else
            {
                //세로 방향으로 켜져있다.
                if (j < 2)
                {
                    return time + 1;
                }
                else
                {
                    return time + (sum - mod) + 1;
                }
            }
        }
        else
        {
            //세로방향부터 시작
            if (mod <= now.sero)
            {
                if (j < 2)
                {
                    return time + 1;
                }
                else
                {
                    return time + (now.sero - mod) + 1;
                }
            }
            else
            {
                //가로방향으로 흐르고 있음
                if (j < 2)
                {
                    return time + (sum - mod) + 1;
                }
                else
                {
                    return time + 1;
                }
            }
        }
    }
}
void bfs(int sx, int sy)
{
    priority_queue<Q> q;
    memset(visited, 0, sizeof(visited));

    q.push({0, sx, sy});
    visited[sx][sy] = true;

    while (!q.empty())
    {
        Q qq = q.top();
        q.pop();

        int x = qq.x;
        int y = qq.y;
        int time = qq.time;

        visited[x][y] = true;

        // cout << x << " " << y << " " << map[x][y] << " " << time << '\n';

        for (int j = 0; j < 4; j++)
        {
            int nx = x + dx[j];
            int ny = y + dy[j];

            if (nx < 0 || nx >= m || ny < 0 || ny >= n || visited[nx][ny] || map[nx][ny] == '.')
                continue;

            if (map[nx][ny] == 'B')
            {
                ans = time + 1;
                return;
            }

            else if (map[nx][ny] == '#')
            {
                q.push({time + 1, nx, ny});
            }

            else if ('0' <= map[nx][ny] && map[nx][ny] <= '9')
            {
                //다른 방향으로 꺽을 수 있다.
                q.push({calc(nx, ny, time, j), nx, ny});
            }
        }
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<string> res;

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