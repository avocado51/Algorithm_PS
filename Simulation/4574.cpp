#include <iostream>
#include <vector>

using namespace std;
//백준 스도미노쿠 https://www.acmicpc.net/problem/4574
//unsolved

typedef pair<int, int> pp;
typedef pair<pp, pp> pppp;

pppp points[9];
int map[9][9];
bool isThere[10];
vector<pp> pos;
bool appear[2][10][10];
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
void print()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << map[i][j] << ' ';
        }
        cout << '\n';
    }
}
bool checkTreeThree(int x, int y)
{
    int a, b;
    for (int k = 0; k < 9; k++)
    {
        if (points[k].first.first <= x && points[k].first.second <= y && x <= points[k].second.first && y <= points[k].second.second)
        {
            a = points[k].first.first;
            b = points[k].first.second;
            break;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (a + i == x && b + j == y)
                continue;
            if (map[a + i][b + j])
                if (map[a + i][b + j] == map[x][y])
                    return false;
        }
    }
    return true;
}
bool checkVert(int x, int y)
{
    for (int i = 0; i < 9; i++)
    {
        if (i == x)
            continue;
        if (map[i][y])
        {
            if (map[i][y] == map[x][y])
                return false;
        }
    }
    return true;
}
bool checkHori(int x, int y)
{
    for (int i = 0; i < 9; i++)
    {
        if (i == y)
            continue;
        if (map[x][i])
            if (map[x][i] == map[x][y])
                return false;
    }
    return true;
}
bool check(int idx)
{
    //조합 중복 없는지 확인 필요
    if (checkHori(pos[idx].first, pos[idx].second) && checkVert(pos[idx].first, pos[idx].second) && checkTreeThree(pos[idx].first, pos[idx].second))
    {
        for (int i = 0; i < 4; i++)
        {
            int nx = pos[idx].first + dx[i];
            int ny = pos[idx].second + dy[i];

            if (nx < 0 || nx >= 9 || ny < 0 || ny >= 9 || !map[nx][ny])
                continue;
        }
        return true;
    }
    return false;
}
bool dfs(int cnt)
{
    if (cnt > pos.size())
    {
        return true;
    }

    for (int k = 1; k <= 9; k++)
    {
        map[pos[cnt].first][pos[cnt].second] = k;
        if (check(cnt))
        {
            if (dfs(cnt + 1))
                return true;
        }
        map[pos[cnt].first][pos[cnt].second] = 0;
    }
    return false;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    points[0] = pppp(pp(0, 0), pp(2, 2));
    points[1] = pppp(pp(0, 3), pp(2, 5));
    points[2] = pppp(pp(0, 6), pp(2, 8));
    points[3] = pppp(pp(3, 0), pp(5, 2));
    points[4] = pppp(pp(3, 3), pp(5, 5));
    points[5] = pppp(pp(3, 6), pp(5, 8));
    points[6] = pppp(pp(6, 0), pp(8, 2));
    points[7] = pppp(pp(6, 3), pp(8, 5));
    points[8] = pppp(pp(6, 6), pp(8, 8));

    while (1)
    {
        int n;
        cin >> n;

        if (!n)
            break;

        memset(map, 0, sizeof(map));
        memset(appear, 0, sizeof(appear));
        pos.clear();

        for (int i = 0; i < n; i++)
        {
            int a, b;
            string pa, pb;
            cin >> a >> pa >> b >> pb;

            int x1 = pa[0] - 'A';
            int y1 = pa[1] - '0';

            map[x1][y1 - 1] = a;

            int x2 = pb[0] - 'A';
            int y2 = pb[1] - '0';

            map[x2][y2 - 1] = b;
            appear[abs(x1 - x2)][a][b] = appear[abs(x1 - x2)][b][a] = true;
        }
        // print();
        for (int i = 1; i <= 9; i++)
        {
            string pos;
            cin >> pos;
            int x = pos[0] - 'A';
            int y = pos[1] - '0';
            map[x][y - 1] = i;
        }
        // print();

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (!map[i][j])
                {
                    pos.push_back(pp(i, j));
                }
            }
        }
        dfs(0);
        cout << '\n';
        print();
        cout << '\n';
    }

    return 0;
}
