#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define MAXX 1501
using namespace std;
//SWEA 줄기세포배양 [5653](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRJ8EKe48DFAUo)

int n, m, k;
int map[MAXX][MAXX];
typedef struct Cell
{
    int x, y, life, age, time;
    bool enable;
};
vector<Cell> cells;
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};
int ans = 0;
bool checkRange(int x, int y)
{
    if (x < 0 || x >= MAXX || y < 0 || y >= MAXX || map[x][y] == 1)
        return false;
    return true;
}
void bfs()
{
    int times = 0;

    queue<Cell> q;
    for (Cell c : cells)
    {
        q.push(c);
    }

    while (k--)
    {
        int size = q.size();
        // cout << "First " << size << '\n';
        while (size--)
        {
            Cell now = q.front();
            q.pop();

            if (now.time == times)
            {
                if (!now.enable)
                {
                    //아직 활성화 전
                    now.time++;
                    now.age++;
                    if (now.age == now.life)
                    {
                        ///활성화
                        now.enable = true;
                    }

                    q.push(now);
                }
                else
                {
                    now.time++;
                    now.age++;
                    if (now.age != now.life * 2)
                    {
                        q.push(now);
                    }
                }
            }
            else
                q.push(now);
        }

        size = q.size();
        vector<Cell> generated;
        // cout << "second " << size << '\n';
        //번식
        while (size--)
        {
            Cell now = q.front();
            q.pop();

            if (now.enable)
            {
                // cout << "enable!! " << now.age << " " << now.life << '\n';
                int x = now.x;
                int y = now.y;

                for (int j = 0; j < 4; j++)
                {
                    int nx = x + dx[j];
                    int ny = y + dy[j];

                    if (checkRange(nx, ny))
                    {
                        if (map[nx][ny] == 0)
                        {
                            //처음 번식하는 셀
                            map[nx][ny] = 2;
                            generated.push_back({nx, ny, now.life, -1, times + 1, 0});
                        }
                        else if (map[nx][ny] == 2)
                        {
                            //다른 셀이 이미 있다.
                            int idx = 0;

                            for (Cell c : generated)
                            {
                                if (map[c.x][c.y] == 2)
                                {
                                    if (c.life < now.life)
                                    {
                                        //now가 대신한다.
                                        break;
                                    }
                                }
                                idx++;
                            }
                            if (idx <= generated.size() - 1)
                            {
                                generated.erase(cells.begin() + idx);
                                generated.push_back({nx, ny, now.life, -1, times + 1, 0});
                            }
                        }
                    }
                }
            }
            q.push(now);
        }

        //map[][] == 2인 것들을 다시 1로 만들어준다.
        for (Cell c : generated)
        {
            if (map[c.x][c.y] == 2)
            {
                map[c.x][c.y] = 1;
                q.push(c);
            }
        }
        // cout << "thrid " << q.size() << '\n';
        times++;
    }
    while (!q.empty())
    {
        if (q.front().age >= 0)
            ans++;
        q.pop();
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie();

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++)
    {
        cells.clear();
        memset(map, 0, sizeof(map));

        cin >> n >> m >> k;
        int life;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> life;
                if (life)
                {
                    int x = 750 + i;
                    int y = 750 + j;

                    cells.push_back({x, y, life, 0, 0, 0});
                    map[x][y] = 1; //exists cell
                }
            }
        }
        ans = 0;
        bfs();

        cout << "#" << tc << " " << ans << '\n';
    }
    return 0;
}