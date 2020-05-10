#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <functional>

using namespace std;

typedef long long ll;
vector<string> express;

vector<string> toPostExp(char op[])
{
    //우선순위에 맞게 후위표기식으로 바꾼다.
    vector<string> res;
    stack<string> st;
    for (int i = 0; i < express.size(); i++)
    {
        // 숫자인 경우
        if (i % 2 == 0)
            res.push_back(express[i]);
        else
        { // 연산자인 경우
            string one(1, op[0]);
            string two(1, op[1]);
            string three(1, op[2]);

            if (express[i] == one)
            { // 제일 높은 우선순위
                while (!st.empty() && (st.top() == one))
                {
                    res.push_back(st.top());
                    st.pop();
                }
                st.push(one);
            }
            else if (express[i] == two)
            {
                while (!st.empty() && (st.top() != three))
                {
                    res.push_back(st.top());
                    st.pop();
                }
                st.push(two);
            }
            else if (express[i] == three)
            {
                while (!st.empty())
                {
                    res.push_back(st.top());
                    st.pop();
                }
                st.push(three);
            }
        }
    }
    while (!st.empty())
    {
        res.push_back(st.top());
        st.pop();
    }

    return res; // 문자열 벡터를 반환
}

ll calc(vector<string> express)
{ // 후위표기 벡터를 계산
    stack<ll> st;

    for (int i = 0; i < express.size(); i++)
    {
        string tmp = express[i];
        if (tmp == "*" || tmp == "+" || tmp == "-")
        {
            ll last = st.top(); //후위연산식이니까 뒤에 연산할 거를 먼저 뽑는다.
            st.pop();
            ll first = st.top();
            st.pop();

            if (tmp == "*")
            {
                ll res = first * last;
                st.push(res);
            }

            else if (tmp == "+")
            {
                ll res = first + last;
                st.push(res);
            }
            else if (tmp == "-")
            {
                ll res = first - last;
                st.push(res);
            }
        }
        else
            st.push(stoi(tmp)); //연산자가 아니면 숫자를 넣어준다.
    }
    //결과를 반환한다.
    return abs(st.top());
}

long long solution(string expression)
{
    long long answer = 0;
    // 문자열을 숫자와 연산자 문자열로 구분하여 elements 벡터에 순차적으로 푸쉬
    int n = expression.size();
    ll MAXX = 0;

    char op[] = {'*', '+', '-'};
    int idx = 0;
    for (int i = 0; i < n; i++)
    {
        //한 자리 수 이상의 숫자들을 하나로 묶는다.
        if ('0' <= expression[i] && expression[i] <= '9')
            continue;
        else
        {
            //연산자가 나왔으니 앞을 자른다.
            string tmp = expression.substr(idx, i - idx);
            express.push_back(tmp);
            idx = i + 1;
            express.push_back(string(1, expression[i]));
        }
    }
    string tmp = expression.substr(idx, n - idx);
    express.push_back(tmp);

    do
    {
        vector<string> postExp = toPostExp(op);
        ll res = calc(postExp);
        MAXX = MAXX > res ? MAXX : res;
    } while (next_permutation(op, op + 3));

    answer = MAXX;
    return answer;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cout << solution("50*6-3*2") << '\n';
    return 0;
}