#include <iostream>
#include <vector>
#include <set>

using namespace std;
//격자판의 숫자 이어 붙이기 [(2819)](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV7I5fgqEogDFAXB&categoryId=AV7I5fgqEogDFAXB&categoryType=CODE)

int matrix[4][4];
set<string> resSet;
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

void dfs(int x, int y, int cnt, string res)
{
    if (cnt == 7)
    {
        resSet.insert(res);
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4)
            continue;

        dfs(nx, ny, cnt + 1, res + to_string(matrix[nx][ny]));
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
        resSet.clear();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                cin >> matrix[i][j];
            }
        }
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                string s(1, matrix[i][j]);

                dfs(i, j, 1, s);
            }
        }

        // set<string>::iterator it;
        // for (it = resSet.begin(); it != resSet.end(); it++)
        // {
        //     cout << *it << '\n';
        // }
        cout << "#" << tc << " " << resSet.size() << '\n';
    }
    return 0;
}