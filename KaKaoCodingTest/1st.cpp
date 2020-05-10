#include <string>
#include <vector>
#include <iostream>

using namespace std;

typedef pair<int, int> pp;

pp keypad[13];
string solution(vector<int> numbers, string hand)
{
    string answer = "";
    int x = 0, y = 0;
    for (int i = 1; i <= 12; i++)
    {
        if (y == 3)
        {
            x++;
            y = 0;
        }
        keypad[i] = pp(x, y++); //키패드를 좌표화
    }
    //11번째는 숫자 0으로 생각한다.

    // for (int i = 1; i <= 12; i++)
    // {
    //     cout << keypad[i].first << " " << keypad[i].second << '\n';
    // }
    //현재 왼손엄지의 위치
    pp left = pp(3, 0); //-> 숫자를 누르면 좌표를 변경한다.
    pp right = pp(3, 2);

    for (int i = 0; i < numbers.size(); i++)
    {
        int num = numbers[i];

        if (num == 1 || num == 4 || num == 7)
        {
            //왼손엄지가 누른다.
            answer += "L";
            left = keypad[num];
        }
        else if (num == 3 || num == 6 || num == 9)
        {
            //오른손 엄지가 누른다.
            answer += "R";
            right = keypad[num];
        }
        else
        {
            //더 가까운 엄지가 누른다.

            pp target;
            if (!num)
            {
                target = keypad[11];
            }
            else
            {
                target = keypad[num];
            }

            int distL = abs(left.first - target.first) + abs(left.second - target.second);

            int distR = abs(right.first - target.first) + abs(right.second - target.second);

            if (distL == distR)
            {
                //hand잡이가 한다.
                if (hand == "right")
                {
                    answer += "R";
                    right = target;
                }
                else
                {
                    answer += "L";
                    left = target;
                }
            }
            else if (distL > distR)
            {
                answer += "R";
                right = target;
            }
            else if (distL < distR)
            {
                answer += "L";
                left = target;
            }
        }
    }
    return answer;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<int> n = {1, 3, 4, 5, 8, 2, 1, 4, 5, 9, 5};
    string hand = "right";
    cout << solution(n, hand) << '\n';
    return 0;
}