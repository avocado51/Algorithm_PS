#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;
//범준이의 제주도 여행 계획 [(1798)](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV4x9oyaCR8DFAUx&categoryId=AV4x9oyaCR8DFAUx&categoryType=CODE)
int n, m;
int ans;

typedef struct Pos
{
    int idx;
    char value;
    int time, conf;
    Pos(int i, int t, int c) : idx(i), time(t), conf(c){};
};
vector<Pos> pos;
int map[36][36];
bool visited[36];
int start;
void init()
{
    memset(map, 0, sizeof(map));
    memset(visited, 0, sizeof(visited));
    ans = 0;
    // hotel.clear();
    // play.clear();
    pos.clear();
}

void dfs(int now, int cnt, int time, int res)
{
    if (cnt == m)
    {
        //돌아가는 날짜가 됐음
        //만족도를 조사한다.
        ans = max(ans, res);
        return;
    }

    if (time > 9)
        return;

    for (int i = 0; i < n; i++)
    {
        if (i == start)
            continue;
        if (!visited[i])
        {
            //일단 아직 방문하지 않은 곳이어야 하고,
            //이 지점의 이동시간 + 노는 시간 + 호텔로 이동해야하는 것도 고려해야 한다.
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
        init();
        cin >> n >> m;

        for (int i = 0; i < n - 1; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                int tmp;
                cin >> tmp;
                map[i][j] = map[j][i] = tmp;
            }
        }

        for (int i = 0; i < n; i++)
        {
            char c;
            int time, conf;
            cin >> c;
            if (c == 'A' || c == 'H')
            {
                if (c == 'A')
                    start = i;
                else
                    pos.push_back(Pos(c, 0, 0));
            }
            else
            {
                cin >> time >> conf;
                pos.push_back(Pos(c, time, conf));
            }
        }
        //공항부터 시작해서 공항으로 돌아와야 한다.
        dfs(start, 1, 0, 0); //현재 위치, 현재 날짜, 이동시간
        cout << "#" << tc << " " << ans << '\n';
    }

    return 0;
}