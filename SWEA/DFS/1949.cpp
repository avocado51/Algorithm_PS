#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
//SWEA 등산로 조성

int n, k;
int ans;
bool visited[9][9];
int map[9][9];

int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, 1, -1};

void dfs(int x, int y, int prev, int res, bool flag)
{
    //prev는 현재의 가장 높은 봉우리를 저장한다.
    //flag는 일전에 깎은 적이 있는지 검사하는 변수이다.
    if (visited[x][y])
        return;

    visited[x][y] = true;
    if (res > ans)
        ans = res;

    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx < 0 || nx >= n || ny < 0 || ny >= n || visited[nx][ny])
            continue;

        if (!flag)
        {
            //아직 공사한 적이 없는 경우
            //"최대" k만큼이므로 k까지 깎을 수 있는 것이지 꼭 k만큼 깍을 필요는 없다.
            if (map[nx][ny] < map[x][y])
            {

                dfs(nx, ny, map[nx][ny], res + 1, flag);
            }
            else if (map[nx][ny] - k < map[x][y])
            {

                dfs(nx, ny, map[x][y] - 1, res + 1, true);
            }
        }
        else
        {
            //이전 봉우리의 높이가 k만큼 공사한 곳일수도 있기 때문에 map[x][y]가 아니라 prev를 대입한다.
            if (map[nx][ny] < prev)
            {
                //그냥 지나갈 수 있다.

                dfs(nx, ny, map[nx][ny], res + 1, flag);
            }
        }
    }
    visited[x][y] = false;
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++)
    {
        ans = 0;
        memset(visited, 0, sizeof(visited));

        cin >> n >> k;

        int maxx = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> map[i][j];
                maxx = maxx > map[i][j] ? maxx : map[i][j];
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (map[i][j] == maxx)
                {

                    dfs(i, j, map[i][j], 1, false);
                }
            }
        }
        cout << "#" << tc << " " << ans << '\n';
    }
    return 0;
}