#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

//BOJ 가스관 [2931](https://www.acmicpc.net/problem/2931)
//unsolved
char pipe[] = {'|', '-', '1', '2', '3', '4', '+'};
int r, c;
char map[26][26];
typedef pair<int, int> pp;

int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
int startD = -1;

typedef struct Q
{
    int x, y, dir;
};

int pipeline(char p, int dir)
{
    int ret = -1;

    if (p == '|')
    {
        if (dir == 0 || dir == 1)
            ret = dir; //가던 방향 그대로 간다.
    }
    else if (p == '-')
    {
        if (dir == 2 || dir == 3)
            ret = dir;
    }
    else if (p == '+')
        ret = dir;
    else if (p == '1')
    {
        if (dir == 0)
            ret = 3;
        else if (dir == 2)
            ret = 1;
    }
    else if (p == '2')
    {
        if (dir == 1)
            ret = 3;
        else if (dir == 2)
            ret = 0;
    }
    else if (p == '3')
    {
        if (dir == 3)
            ret = 0;
        else if (dir == 1)
            ret = 2;
    }
    else if (p == '4')
    {
        if (dir == 3)
            ret = 1;
        else if (dir == 0)
            ret = 2;
    }
    return ret;
}
bool checkRange(int x, int y)
{
    if (x < 0 || x >= r || y < 0 || y >= c)
        return false;
    return true;
}
pp bfs(int x, int y)
{
    queue<Q> q;
    q.push({x, y, startD});

    while (!q.empty())
    {
        Q qq = q.front();
        q.pop();

        int xx = qq.x;
        int yy = qq.y;
        int dir = qq.dir;

        //시작점이라면 이어진 곳으로 방향을 정해야 하고

        if (startD == -1 && map[xx][yy] == 'M')
        {
            int cnt = 0;
            Q tmp;
            for (int i = 0; i < 4; i++)
            {
                int nx = xx + dx[i];
                int ny = yy + dy[i];

                if (checkRange(nx, ny))
                {
                    if (map[nx][ny] == 'Z')
                        continue;
                    else if (map[nx][ny] != '.')
                    {
                        int dir = pipeline(map[nx][ny], i);
                        q.push({nx, ny, dir});
                        if (startD == -1)
                            startD = i;
                        break;
                    }
                }
            }
        }
        else
        {
            //아니라면 정해진 방향으로 이동한다.
            int nx = xx + dx[dir];
            int ny = yy + dy[dir];

            if (checkRange(nx, ny))
            {
                if (map[nx][ny] == '.')
                {
                    return {nx, ny};
                }
                else if (map[nx][ny] == 'Z')
                {
                    return {-1, -1};
                }
                else
                {
                    dir = pipeline(map[nx][ny], dir);

                    if (dir < 0)
                        return {nx, ny};
                    q.push({nx, ny, dir});
                }
            }
        }
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> r >> c;
    int x, y;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == 'M')
            {
                //시작점
                x = i;
                y = j;
            }
        }
    }

    pp spot = bfs(x, y);

    //pipe 7개 중에 맞는 걸 넣어본다.

    for (int j = 0; j < 7; j++)
    {
        map[spot.first][spot.second] = pipe[j];
        //M이 두 개의 파이프와 연결되는지 확인한다.

        pp chk = bfs(x, y); //다시 시작점부터 탐색

        //제대로 이어지는 지 확인
        if (chk == pp(-1, -1))
        {
            cout << spot.first + 1 << " " << spot.second + 1 << " " << pipe[j] << '\n';
            break;
        }
    }
    return 0;
}