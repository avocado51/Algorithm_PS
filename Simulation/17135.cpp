#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
//BOJ 캐슬 디펜스 https://www.acmicpc.net/problem/17135
int map[17][17];
bool chk[16];
int n, m, d;
int ans = 0;

typedef pair<int, int> pp;
typedef pair<int, pp> ipp;

vector<pp> enemies;
int dx[3] = {0, -1, 0}, dy[3] = {-1, 0, 1};

int max(const int &a, const int &b)
{
    if (a > b)
        return a;
    return b;
}
void attackEnemy(int row, int col)
{
    if (map[row][col] == 2)
    {
        //이미 누가 죽임
        return;
    }
    if (map[row][col] == 1)
    {
        map[row][col] = 2;
        enemies.push_back(pp(row, col));
        return;
    }

    int visited[17][17];
    memset(visited, 0, sizeof(visited));

    //D거리 이하의 적을 죽일 수 있다.
    queue<ipp> q;
    q.push(ipp(1, pp(row, col)));

    while (!q.empty())
    {
        int dist = q.front().first;
        int x = q.front().second.first;
        int y = q.front().second.second;
        q.pop();

        if (dist >= d)
            continue;

        for (int i = 0; i < 3; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx <= 0 || ny <= 0 || ny > m || visited[nx][ny])
                continue;
            if (map[nx][ny] == 2)
                return;
            if (map[nx][ny] == 1)
            {
                enemies.push_back(pp(nx, ny));
                map[nx][ny] = 2;
                return;
            }
            visited[nx][ny] = true;
            q.push(ipp(dist + 1, pp(nx, ny)));
        }
    }
}
int attack()
{
    int ret = 0;
    int attacker[3] = {0, 0, 0};

    //총 n번 공격 가능
    int idx = 0;
    for (int i = 1; i <= m; i++)
    {
        if (chk[i])
        {
            attacker[idx++] = i;
        }
    }
    int x = n;
    while (x > 0)
    {
        enemies.clear();
        for (int i = 0; i < 3; i++)
        {
            attackEnemy(x, attacker[i]);
        }

        ret += enemies.size();
        for (pp e : enemies)
        {
            map[e.first][e.second] = 0;
        }
        x--;
    }

    return ret;
}
void dfs(int idx, int cnt)
{
    if (cnt == 3)
    {
        int c_map[17][17];
        memcpy(c_map, map, sizeof(map));

        ans = max(ans, attack());
        memcpy(map, c_map, sizeof(map));
        return;
    }

    for (int i = idx; i <= m; i++)
    {
        if (!chk[i])
        {
            chk[i] = true;
            dfs(i + 1, cnt + 1);
            chk[i] = false;
        }
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> d;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> map[i][j];
        }
    }

    //궁수의 위치를 지정
    dfs(1, 0);
    cout << ans << '\n';
    return 0;
}

/*
5 5 2
1 0 1 1 1
0 1 1 1 1
1 0 1 0 1
1 1 0 1 0
1 0 1 0 1
14

5 5 3
1 1 1 0 1
0 1 1 0 0
1 1 1 0 0
0 1 1 0 0
1 1 1 0 0

답 : 13

10 10 1
1 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 1

답 2

10 10 8
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0

ans : 30

2 7 2

0 0 1 0 1 0 1

1 0 1 0 1 0 0

답 5

3 3 4
1 1 1
1 1 1
1 1 1

답 9

3 3 4
0 0 0
0 0 0
0 0 0

답 0

15 15 10
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

답 0
*/