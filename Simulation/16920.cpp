#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
//BOJ 확장게임 https://www.acmicpc.net/problem/16920
//unsolved

int n, m, p;
char map[1001][1001];
char c_map[1001][1001];
bool visited[1001][1001];
int s[10];
typedef pair<int, int> pp;
typedef pair<int, pp> ipp;

vector<pp> newCastle[10];

int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};
queue<pp> q;
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
bool check()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (map[i][j] == '.')
                return false;
        }
    }
    return true;
}
void bfs()
{
    bool flag = true;
    while (flag)
    {
        flag = false;
        for (int i = 1; i <= 9; i++)
        {
            vector<pp> tmpCastle;

            for (pp pos : newCastle[i])
            {
                queue<ipp> q;
                q.push(ipp(0, pos));

                int ss = s[map[pos.first][pos.second] - '0'];
                // memset(visited, 0, sizeof(visited));
                while (!q.empty())
                {
                    int dist = q.front().first;
                    int x = q.front().second.first;
                    int y = q.front().second.second;
                    q.pop();

                    if (dist == ss)
                    {
                        //끝이다.
                        // tmpCastle.push_back(pp(x, y));
                        continue;
                    }

                    for (int d = 0; d < 4; d++)
                    {
                        int nx = x + dx[d];
                        int ny = y + dy[d];

                        if (nx < 0 || nx >= n || ny < 0 || ny >= m || map[nx][ny] == '.')
                            continue;

                        // visited[nx][ny] = true;

                        if (map[nx][ny] == '.')
                        {
                            map[nx][ny] = i + '0';
                            tmpCastle.push_back(pp(nx, ny));
                            q.push(ipp(dist + 1, pp(nx, ny)));
                        }
                    }
                }
            }

            if (tmpCastle.size() > 0)
                flag = true;
            newCastle[i] = tmpCastle; //성의 가장자리 좌표를 저장한 벡터로 대치한다.
        }
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> p;

    for (int i = 1; i <= p; i++)
    {
        cin >> s[i]; //확장할 수 있는 칸
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
            if ('1' <= map[i][j] && map[i][j] <= '9')
                newCastle[map[i][j] - '0'].push_back(pp(i, j));
        }
    }

    //s값에 따라 한 턴에 최대로 갈 수 있는 좌표를 미리 구해야 한다. s의 크기가 10억임
    bfs();
    vector<int> res(p + 1);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if ('1' <= map[i][j] && map[i][j] <= '9')
                res[map[i][j] - '0']++;
        }
    }

    for (int i = 1; i <= p; i++)
        cout << res[i] << ' ';
    cout << '\n';

    return 0;
}

/*
4 4 2
1000000000 1
1..1
#.##
....
...2

=> s의 크기가 크다 
*/