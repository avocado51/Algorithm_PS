#include <string>
#include <vector>
#include <iostream>

using namespace std;
//Programmers 카카오 기출 단체사진찍기 https://programmers.co.kr/learn/courses/30/lessons/1835

//둘 사이의 최대 간격은 6
//6이 나오면 둘을 양 끝단에 놓고 확인한다.
//만약, 조건 중 동일한 사람 간 다른 조건을 가지고 있다면 0

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, vector<string> data)
{
    int answer = 0;
    char charac[8] = {'A', 'C', 'F', 'J', 'M', 'N', 'R', 'T'};

    do
    {
        bool flag = true;

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
            int dist = (data[i][4] - '0') + 1;

            if (c == '=')
            {
                if (dist != abs(a - b))
                {
                    flag = false;
                    break;
                }
            }
            else if (c == '>')
            {
                if (dist >= abs(a - b))
                {
                    flag = false;
                    break;
                }
            }
            else if (c == '<')
            {
                if (dist <= abs(a - b))
                {
                    flag = false;
                    break;
                }
            }
        }
        if (flag)
            answer++;
    } while (next_permutation(charac, charac + 8));

    return answer;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n = 2;
    string s1 = "N~F=0";
    string s2 = "R~T>2";
    vector<string> v;
    v.push_back(s1);
    v.push_back(s2);
    cout << solution(n, v) << '\n';
    return 0;
}