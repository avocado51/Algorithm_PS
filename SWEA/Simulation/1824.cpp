#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
//SWEA 1824. 혁진이의 프로그램 검증
//https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV4yLUiKDUoDFAUx&categoryId=AV4yLUiKDUoDFAUx&categoryType=CODE

int r, c;
char map[21][21];
bool visited[21][21][4][16];

int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

int buf = 0;
bool flag = false;
void dfs(int x, int y, int dir)
{

    if (map[x][y] == '@')
    {
        flag = true;
        return;
    }
    else if (map[x][y] == '^' || (map[x][y] == '|' && buf))
        dir = 0;
    else if (map[x][y] == 'v' || (map[x][y] == '|' && !buf))
        dir = 1;
    else if (map[x][y] == '<' || (map[x][y] == '_' && buf))
        dir = 2;
    else if (map[x][y] == '>' || (map[x][y] == '_' && !buf))
        dir = 3;
    else if ('0' <= map[x][y] && map[x][y] <= '9')
        buf = (map[x][y] - '0');
    else if (map[x][y] == '+')
        buf = buf == 15 ? 0 : buf + 1;
    else if (map[x][y] == '-')
        buf = buf == 0 ? 15 : buf - 1;

    if (visited[x][y][dir][buf])
        return;

    visited[x][y][dir][buf] = true;

    if (map[x][y] == '?')
    {
        for (int i = 0; i < 4; i++)
        {
            int nx = (x + dx[i] + r) % r;
            int ny = (y + dy[i] + c) % c;

            dfs(nx, ny, i);
        }
    }
    else
    {
        int nx = (x + dx[dir] + r) % r;
        int ny = (y + dy[dir] + c) % c;

        dfs(nx, ny, dir);
    }
}
void init()
{
    memset(map, 0, sizeof(map));
    memset(visited, 0, sizeof(visited));
    flag = false;
    buf = 0;
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++)
    {

        cin >> r >> c;

        init();

        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                cin >> map[i][j];
            }
        }

        //처음 이동방향은 오른쪽
        dfs(0, 0, 3);
        cout << "#" << tc << " ";
        if (flag)
            cout << "YES" << '\n';
        else
            cout << "NO" << '\n';
    }
    return 0;
}