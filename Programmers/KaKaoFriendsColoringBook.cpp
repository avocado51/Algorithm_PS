#include <vector>
#include <queue>
// #include <algorithm>
#include <cstring>
using namespace std;
int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};
//Programmers 카카오 기출 카카오 프렌즈 컬러링 북 https://programmers.co.kr/learn/courses/30/lessons/1829

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.

typedef pair<int, int> pp;

vector<int> solution(int m, int n, vector<vector<int>> map)
{

    bool visited[101][101] = {
        0,
    };
    int res1 = 0; //몇 개의 영역이 있는지
    int res2 = 0; //가장 큰 영역은 몇 칸으로 이루어져있는지

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (map[i][j] && !visited[i][j])
            {
                ++res1;
                queue<pp> q;
                q.push(pp(i, j));

                visited[i][j] = true;
                int color = map[i][j];
                int area = 1;

                while (!q.empty())
                {

                    int x = q.front().first;
                    int y = q.front().second;
                    q.pop();

                    for (int i = 0; i < 4; i++)
                    {
                        int nx = x + dx[i];
                        int ny = y + dy[i];
                        if (nx < 0 || nx >= m || ny < 0 || ny >= n)
                            continue;

                        if (color == map[nx][ny] && !visited[nx][ny])
                        {
                            visited[nx][ny] = true;
                            area++;
                            q.push(pp(nx, ny));
                        }
                    }
                }
                res2 = max(res2, area);
            }
        }
    }

    vector<int> answer(2);
    answer[0] = res1;
    answer[1] = res2;
    return answer;
}