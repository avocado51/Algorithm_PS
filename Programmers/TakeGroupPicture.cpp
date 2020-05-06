#include <string>
#include <vector>
#include <iostream>

using namespace std;
//Programmers 카카오 기출 단체사진찍기 https://programmers.co.kr/learn/courses/30/lessons/1835
//unsolved

//둘 사이의 최대 간격은 6
//6이 나오면 둘을 양 끝단에 놓고 확인한다.
//만약, 조건 중 동일한 사람 간 다른 조건을 가지고 있다면 0
typedef pair<int, int> pp;
pp dist[8][8]; //i번쩨 사람과 j번째 사람의 거리를 저장
char charac[8] = {'A', 'C', 'F', 'J', 'M', 'N', 'R', 'T'};
int answer = 0;
bool visited[8];
int res[8];
int abs(const int &a, const int &b)
{
    if (a > b)
        return a - b;
    return b - a;
}
bool check()
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = i + 1; j < 8; j++)
        {
            int f = dist[i][j].first;
            int s = dist[i][j].second;

            int d = j - i; // 둘 사이의 거리
            if (!f && !s)
                continue;
            //아무런 조건이 없는 관계
            //f와 s 의 사이에 존재해야 하낟.
            if (!(f <= d && d <= s))
                return false;
        }
    }
    return true;
}
void dfs(int idx, int cnt)
{
    if (cnt == 8)
    {
        if (check())
            answer++;
        //8명 다 고름
        return;
    }

    for (int i = 0; i < 8; i++)
    {
        //한 명씩놓을 때마다 검사를 하낟.
        if (!visited[i])
        {
            visited[i] = true;
            //지금 위치에
            res[cnt] = i;
            dfs(i + 1, cnt + 1);
            res[cnt] = 0;
            visited[i] = false;
        }
    }
}
// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, vector<string> data)
{

    for (int i = 0; i < data.size(); i++)
    {
        int a, b;
        for (int j = 0; j < 8; j++)
        {
            if (data[i][0] == charac[j])
                a = j;
            if (data[i][2] == charac[j])
                b = j;
        }

        char c = data[i][3];
        int d = (data[i][4] - '0');
    }

    dfs(0, 0); //8!조합을 구해서 안되는 애들만 제외시킨다.

    return answer;
}