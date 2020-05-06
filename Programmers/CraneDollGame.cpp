#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

//Progrmmers 카카오 기출 크레인 인형 뽑기게임 https://programmers.co.kr/learn/courses/30/lessons/64061
int solution(vector<vector<int>> board, vector<int> moves)
{
    int answer = 0;

    //시뮬레이션
    //같은 숫자가 2개 쌓이면 없어짐
    stack<int> st;
    int size = board[0].size(); //인형이 없더라도 0으로 차있기 때문에 사이즈는 같음

    for (int i = 0; i < moves.size(); i++)
    {
        int idx = moves[i] - 1;
        int tmpS = 0;
        while (tmpS < size)
        {
            if (board[tmpS][idx])
                break;
            tmpS++;
        }
        if (tmpS == size)
            continue;
        cout << idx << " " << tmpS << " " << board[idx][tmpS] << '\n';
        if (st.empty())
        {
            st.push(board[tmpS][idx]);
        }
        else
        {
            if (st.top() == board[tmpS][idx])
            {
                answer += 2;
                st.pop();
            }
            else
                st.push(board[tmpS][idx]);
        }
        board[tmpS][idx] = 0;
    }

    return answer;
}