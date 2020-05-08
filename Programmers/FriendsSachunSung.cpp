#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <iostream>

using namespace std;
// int dx[4] = {0, 0, -1, 1}, dy[4] = {0, 0, -1, 1};
typedef pair<int, int> pp;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
void print(int m, int n, vector<string> board)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << board[i][j] << ' ';
        }
        cout << '\n';
    }
}
bool goY(int sx, int sy, int ex, int ey, vector<string> board)
{
    int d = 1;
    if (sy == ey)
    {
        //x방향으로 이동 필요 없음
        return true;
    }
    else if (sy > ey)
    {
        d = -1;
    }
    while (1)
    {
        sy += d;
        if (board[sx][sy] != '.')
        {
            if (board[sx][sy] == board[ex][ey])
                return true;
            else
                return false;
        }
        else if (board[sx][sy] == '.' && sy == ey)
            return true; //go y 실행
    }
}
bool goX(int sx, int sy, int ex, int ey, vector<string> board)
{
    //갈 수 있으면 ok

    int d = 1;
    if (sx == ex)
    {
        //x방향으로 이동 필요 없음
        return true;
    }
    else if (sx > ex)
    {
        d = -1;
    }
    while (1)
    {
        sx += d;
        if (board[sx][sy] != '.')
        {
            if (board[sx][sy] == board[ex][ey])
                return true;
            else
                return false;
        }
        else if (board[sx][sy] == '.' && sx == ex)
            return true; //go y 실행
    }
}
string solution(int m, int n, vector<string> board)
{
    string answer = "";

    vector<pp> pos[26];

    // 타일의 좌표를 각각 저장
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] != '.' && board[i][j] != '*')
            {
                pos[board[i][j] - 'A'].push_back(pp(i, j));
            }
        }
    }

    while (1)
    {
        int flag = 0;
        for (int i = 0; i < 26; i++)
        {
            if (!pos[i].size())
                continue; //없는 타일

            flag = -1; //impossible

            if (goX(pos[i][0].first, pos[i][0].second, pos[i][1].first, pos[i][1].second, board) && goY(pos[i][1].first, pos[i][0].second, pos[i][1].first, pos[i][1].second, board))
            {
                //한 번 회전으로 갈 수 있다면
                answer.push_back(board[pos[i][0].first][pos[i][0].second]);
                board[pos[i][0].first][pos[i][0].second] = '.';
                board[pos[i][1].first][pos[i][1].second] = '.';
                pos[i].clear();
                flag = 1;
                break;
            }
            if (goX(pos[i][1].first, pos[i][1].second, pos[i][0].first, pos[i][0].second, board) && goY(pos[i][0].first, pos[i][1].second, pos[i][0].first, pos[i][0].second, board))
            {
                //한 번 회전으로 갈 수 있다면
                flag = 1;
                answer.push_back(board[pos[i][0].first][pos[i][0].second]);
                board[pos[i][0].first][pos[i][0].second] = '.';
                board[pos[i][1].first][pos[i][1].second] = '.';
                pos[i].clear();
                break;
            }
        }
        // cout << flag << '\n';
        // print(m, n, board);
        if (!flag)
            return answer;
        else if (flag == -1)
            return "IMPOSSIBLE";
    }
    return answer;
}

