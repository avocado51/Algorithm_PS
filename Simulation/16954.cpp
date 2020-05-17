#include <iostream>
#include <vector>
#include <queue>

/*
BOJ 16954 움직이는 미로 탈출
https://www.acmicpc.net/problem/16954
*/
using namespace std;

char map[8][8][8];

bool flag = false;
typedef pair<int, int> pp;
typedef pair<int, pp> ipp;

bool visited[8][8][8];

int dx[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1}, dy[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

void print()
{

    cout << '\n';
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << map[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}
void down(int x)
{
    //현재 벽을 내린다.
    for (int j = 7; j > 0; j--)
    {
        for (int i = 0; i < 8; i++)
        {
            map[j][i] = map[j - 1][i];
            map[j - 1][i] = '.';
        }
    }
    for (int i = 0; i < 8; i++)
    {
        map[0][i] = '.';
    }
}
bool check(int x)
{
    for (int i = 0; i <= x; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (map[i][j] == '#')
                return false;
        }
    }
    return true;
}

void bfs()
{
    //현재 벽인 지역과 다음에 벽이 될 수 있는 지점빼고 전부 큐에 넣는다.
    queue<ipp> q;
    q.push({0, {7, 0}});

    while (!q.empty())
    {
        int x = q.front().second.first;
        int y = q.front().second.second;
        int cnt = q.front().first;
        q.pop();

        if (check(x))
        {
            flag = true;
            return;
        }

        for (int i = 0; i < 9; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx >= 8 || ny < 0 || ny >= 8)
                continue;
            if (map[nx][ny] == '#' || (nx - 1 >= 0 && map[nx - 1][ny] == '#'))
                continue;

            q.push({cnt+1,{nx, ny}});
        }
        down(x);
        // print();
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cin >> map[i][j];
        }
    }

    bfs();
    if (flag)
        cout << 1 << '\n';
    else
        cout << 0 << '\n';
    return 0;
}