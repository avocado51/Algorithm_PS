#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define INF 1001
using namespace std;
//SWEA 줄기세포배양 [5653](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRJ8EKe48DFAUo)
int n, m, k;
int map[INF][INF];
//map[][] == 0 : 없음
//map[][] == 1 : 세포 하나 있음
//map[][] == 2 : 동시에 번식한 세포 있음
int ans;

typedef struct Cell
{
    int x, y, life, time, age;
    //life는 본래의 생명력 수치를 저장
    //time은 생성 후에 언제 활성화되는지를 저장
    //age : 활성화된 후에 지난 시간
    bool enable;
};

vector<Cell> cellMap;
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

void bfs()
{
    //세포 번식
    queue<Cell> q;

    for (Cell c : cellMap)
    {
        q.push(c);
    }
    vector<Cell> v;
    int times = 0;
    while (k--)
    {
        int size = q.size();
        while (size--)
        {

            Cell now = q.front();
            q.pop();

            int age = now.age;
            if (!now.enable)
            {
                //아직 활성화 되지 않았음

                if (age + 1 == now.life)
                {
                    now.enable = true;
                }
                q.push({now.x, now.y, now.life, now.time, age + 1, now.enable});
            }
            else
            {
                //죽은 세포 없앰
                if (age + 1 != 2 * now.life)
                {
                    q.push({now.x, now.y, now.life, now.time, age + 1, now.enable});
                }
            }
        }

        cout << "first " << q.size() << '\n';
        size = q.size();
        v.clear();
        while (size--)
        {
            //번식
            Cell now = q.front();
            q.pop();

            int x = now.x;
            int y = now.y;

            if (now.enable)
            {
                for (int j = 0; j < 4; j++)
                {
                    int nx = x + dx[j];
                    int ny = y + dy[j];

                    if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                        continue;

                    if (!map[nx][ny])
                    {
                        //번식 가능
                        map[nx][ny] = 2;
                        v.push_back({nx, ny, now.life, now.life + times, 0, 0});
                    }
                    else if (map[nx][ny] == 2)
                    {
                        //같은 곳에 잇는 세포보다 생명력이 커야 한다.
                        for (int i = 0; i < v.size(); i++)
                        {
                            if (v[i].x == nx && v[i].y == ny)
                            {
                                if (v[i].life < now.life)
                                {
                                    v.erase(v.begin() + i);
                                    v.push_back({nx, ny, now.life, now.life + times, 0, 0});
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            q.push(now);
        }
        cout << "v size " << v.size() << '\n';
        for (int j = 0; j < v.size(); j++)
        {
            q.push(v[j]);
            map[v[j].x][v[j].y] = 1;
        }
        cout << "second " << q.size() << '\n';
        ++times;
    }

    while (!q.empty())
    {
        ans++;
        q.pop();
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++)
    {
        memset(map, 0, sizeof(map));
        cellMap.clear();
        cin >> n >> m >> k;

        int x;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> x; //세포의 생명력
                if (x)
                {
                    int posx = 500 + i;
                    int posy = 500 + j;
                    cellMap.push_back({posx, posy, x, x, 0, 0});
                    map[posx][posy] = 1; //세포가 살아있음을 저장
                }
            }
        }
        ans = 0;
        bfs();

        cout << "#" << tc << " " << ans << '\n';
    }

    return 0;
}