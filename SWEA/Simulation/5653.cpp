#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define INF 1001
using namespace std;
//SWEA 줄기세포배양 [5653](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRJ8EKe48DFAUo)
int n, m, k;
int map[INF][INF];
//map[][] == 0 : 없음 
//map[][] == 1 : 세포 하나 있음 
//map[][] == 2 : 동시에 번식한 세포 있음 

typedef struct Cell
{
    int x, y, life, time, age;
    //life는 본래의 생명력 수치를 저장
    //time은 생성 후에 언제 활성화되는지를 저장
    //age : 활성화된 후에 지난 시간
    bool enable;
};
typedef pair<int, Cell> ic;
vector<Cell> cellMap;
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

bool compare(const ic &a, const ic &b) {
    return a.second.life > b.second.life;
}
void bfs()
{
    queue<Cell> q;
    for (int i = 0; i < cellMap.size(); i++)
    {
        q.push(cellMap[i]);
    }

    int times = 0;
    while (k--)
    {
        //시간에 따라
        ++times;
        int size = q.size();
        while (size--)
        {
            //세포의 개수만큼
            //시간이 되면 번식한다.
            Cell now = q.front();
            q.pop();

            if (now.time == times)
            {
                //활성화된다.
                //생성부터 2*x-1시간 후에 죽는다??
                now.enable = true;
                now.age += 1;
            }

            if (now.age == 2 * now.life)
            {
                //죽음
                map[now.x][now.y]--;
                continue;
            }
        }

        size = q.size();
        while (size--)
        {
            //enable ==true 인 것들의 번식
            Cell now = q.front();
            q.pop();

            if (now.enable)
            {
                for (int i = 0; i < 4; i++)
                {
                    int nx = now.x + dx[i];
                    int ny = now.y + dy[i];

                    if (nx < 0 || nx >= INF || ny < 0 || ny >= INF)
                        continue;
                    //이미 다른 세포가 있으면 추가 번식 안함
                    //동시에 번식을 하게 되면 더 생명력이 높은 친구가 살아남는다.
                    

                }
            }
        }
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

        bfs();
        cout << "#" << tc << " " << '\n';
    }

    return 0;
}