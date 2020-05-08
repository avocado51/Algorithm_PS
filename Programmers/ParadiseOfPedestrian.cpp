#include <vector>
#include <iostream>

using namespace std;

int MOD = 20170805;

int R[501][501], D[501][501];
// int map[501][501];
// int w , h;
// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
// int dx[2] = {1, 0}, dy[2] = {0,1};
// int dfs(int x, int y, int d) {
//      if (x >= h|| y>= w) return 0;
//     if (x == h-1 && y == w-1) {
//         return 1;
//     }
//     if (dp[x][y] != -1) return dp[x][y];

//     dp[x][y] = 0;
//     if (map[x][y] == 0) {
//         dp[x][y] +=dfs(x+1, y, 0);
//         dp[x][y] += dfs(x, y+1, 1);
//     }
//     else if (map[x][y] == 1) {
//         dp[x][y] = 0;
//         return 0;
//     }
//     else if (map[x][y] == 2) {
//         dp[x][y] += dfs(x+dx[d], y + dy[d], d);
//     }
//     //0은 자유롭게 통행
//     //1은 통행 금지
//     //2는 현재 방향 유지
//     return dp[x][y];
// }
int solution(int m, int n, vector<vector<int>> map)
{
    int answer = 0;

    //right, down을 나눠서 구한다.
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            R[i][j] =D[i][j] = 0;
        }
    }
    R[1][1] = D[1][1] = 1;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (map[i - 1][j - 1] == 0)
            {
                //어느방향이든 탐색 가능
                R[i][j] += (R[i][j - 1]%MOD + D[i - 1][j]%MOD)%MOD;
                D[i][j] += (R[i][j - 1]%MOD + D[i - 1][j]%MOD)%MOD;
            }
            else if(map[i-1][j-1] == 2) {
                R[i][j] = R[i][j-1]%MOD;
                D[i][j] = D[i-1][j]%MOD;
            }
        }
    }
    answer = (R[m][n-1]%MOD+ D[m-1][n]%MOD)%MOD;

    return answer;
}