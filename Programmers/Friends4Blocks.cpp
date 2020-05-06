#include <string>
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;
//프로그래머스 카카오 기출 프렌즈 4블록 https://programmers.co.kr/learn/courses/30/lessons/17679

int w, h;
int map[31][31];
int answer = 0;
bool visited[31][31];
int dx[3] = {1, 0, 1}, dy[3] = {0, 1, 1};
bool flag = true;

bool check()
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (map[i][j])
                return false;
        }
    }
    return true;
}
void relocateBlocks()
{
    for (int i = 0; i < w; i++)
    {
        for (int j = h - 2; j >= 0; j--)
        {
            for (int k = j; k < h - 1; k++)
            {
                if (!map[k + 1][i])
                {
                    swap(map[k + 1][i], map[k][i]);
                }
            }
        }
    }
}
void removeBlocks()
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (visited[i][j])
            {
                answer++;
                map[i][j] = 0;
            }
        }
    }
}
void findBlocks()
{
    // v.clear();
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < h - 1; i++)
    {
        for (int j = 0; j < w - 1; j++)
        {
            if (map[i][j])
            {
                int now = map[i][j];
                int cnt = 1;

                for (int d = 0; d < 3; d++)
                {
                    int nx = i + dx[d];
                    int ny = j + dy[d];

                    if (nx >= h || ny < 0 || ny >= w)
                        continue;
                    if (now == map[nx][ny])
                    {
                        //4개까지만 허용
                        cnt++;
                    }
                }
                if (cnt == 4)
                {
                    //전부 visited 처리
                    visited[i][j] = true;
                    for (int d = 0; d < 3; d++)
                    {
                        int nx = i + dx[d];
                        int ny = j + dy[d];
                        visited[nx][ny] = true;
                        flag = false;
                    }
                }
            }
        }
    }

    //visited 처리된 블록 지우기
    removeBlocks();
    //끌어내리기
    relocateBlocks();
}
int solution(int m, int n, vector<string> board)
{
    h = m;
    w = n;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            map[i][j] = (board[i][j] - 'A') + 1;
        }
    }

    //전체적으로 탐색을 한다.
    // print();
    while (1)
    {
        flag = true;
        findBlocks();

        if (check() || flag)
            break; //더 이상 지워질 게 없는 경우
    }

    return answer;
}