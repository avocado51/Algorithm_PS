#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
//SWEA 디저트 카페 https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5VwAr6APYDFAWu
int n;
int map[21][21];
int ans = -1;
bool visited[21][21];
int dx[4] = {1, 1, -1,-1}, dy[4] = {1,-1,-1,1};
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> map[i][j];
            }
        }
        //시작 지점은 (0,0~n-1, 0), (0~n-1,n-1), (n-1, 0~n-1)은 안된다.
        ans = -1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // dfs(i, j, 1);
            }
        }
        cout << "#" << tc << " " << ans << '\n';
    }
    return 0;
}