#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//BOJ 새로운게임2 [17837](https://www.acmicpc.net/problem/17837)

int n, k;
typedef pair<int, int> pp;

vector<pp> chase[15][15];
int map[15][15];
bool flag = false;

int dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};
pp pos[11];
void print()
{
    for (int i = 0; i <= n + 1; i++)
    {
        for (int j = 0; j <= n + 1; j++)
        {
            cout << map[i][j] << ' ';
        }
        cout << '\n';
    }
}
void bfs()
{
    //1번부터 k번까지 규칙에 따라 이동
    for (int i = 1; i <= k; i++)
    {
        //i번째 말이 있는 칸을 찾는다.
        int x = pos[i].first;
        int y = pos[i].second;

        vector<pp> v1 = chase[x][y];
        vector<pp> v2;
        //i번째 말을 기준으로 옮길 것들만
        int j = 0;
        for (; j < v1.size(); j++)
        {
            if (v1[j].first == i)
            {
                break;
            }
        }
        //j까지 자름
        if (j == 0)
        {
            v2 = v1;
            chase[x][y].clear();
        }
        else
        {
            v2.insert(v2.end(), v1.begin() + j, v1.end());
            chase[x][y].erase(chase[x][y].begin() + j, chase[x][y].end());
        }

        //이제 방향대로 움직인다.
        pp now = v2[0];

        int nx = x + dx[now.second];
        int ny = y + dy[now.second];

        if (map[nx][ny] == 2)
        {
            //파란색
            //방향 바꾸고 전진
            now.second = now.second < 2 ? 1 - now.second : 5 - now.second;
            nx = x + dx[now.second];
            ny = y + dy[now.second];

            if (map[nx][ny] == 2)
            {
                //방향만 바꾸고 원래 자리로
                v2[0] = pp(i, now.second);

                chase[x][y].insert(chase[x][y].end(), v2.begin(), v2.end());
                continue;
            }
        }
        if (map[nx][ny] == 0)
        {
            //흰색
            //그냥 쌓음

            v2[0] = pp(i, now.second);
            for (int k = 0; k < v2.size(); k++)
            {
                pos[v2[k].first] = {nx, ny};
            }
            vector<pp> tmp = chase[nx][ny];

            if (tmp.size() == 0)
            {
                chase[nx][ny] = v2;
            }
            else
            {
                chase[nx][ny].insert(chase[nx][ny].end(), v2.begin(), v2.end());
                if (chase[nx][ny].size() >= 4)
                {
                    flag = true;
                    return;
                }
            }
        }
        else if (map[nx][ny] == 1)
        {

            v2[0] = pp(i, now.second);
            reverse(v2.begin(), v2.end());

            for (int k = 0; k < v2.size(); k++)
            {
                pos[v2[k].first] = {nx, ny};
            }
            vector<pp> tmp = chase[nx][ny];
            if (tmp.size() == 0)
            {
                chase[nx][ny] = v2;
            }
            else
            {
                chase[nx][ny].insert(chase[nx][ny].end(), v2.begin(), v2.end());
                if (chase[nx][ny].size() >= 4)
                {
                    flag = true;
                    return;
                }
            }
        }
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;

    for (int i = 0; i <= n + 1; i++)
    {
        map[0][i] = map[i][0] = map[n + 1][i] = map[i][n + 1] = 2;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> map[i][j];
        }
    }

    int x, y, d;
    for (int i = 1; i <= k; i++)
    {
        cin >> x >> y >> d;
        d--;
        chase[x][y].push_back({i, d});
        pos[i] = pp(x, y);
    }
    // print();

    int turn = 0;
    while (1)
    {
        if (flag)
        {
            break;
        }
        ++turn;
        if (turn > 1000)
            break;
        bfs();
    }
    if (!flag)
        turn = -1;
    cout << turn << '\n';
    return 0;
}