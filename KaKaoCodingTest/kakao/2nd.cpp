#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <stack>

using namespace std;

char op[] = {'+', '-', '*'};
vector<string> express;
typedef long long ll;

ll calc(vector<string> &res)
{
    stack<ll> st;

    for (int i = 0; i < res.size(); i++)
    {
        string now = res[i];

        if (now == "*" || now == "-" || now == "+")
        {
            ll second = st.top();
            st.pop();
            ll first = st.top();
            st.pop();

            if (now == "*")
            {
                st.push(first * second);
            }
            else if (now == "-")
            {
                st.push(first - second);
            }
            else if (now == "+")
            {
                st.push(first + second);
            }
        }
        else
        {
            st.push(stoi(now));
        }
    }
    return abs(st.top());
}
vector<string> toPostExp()
{
    vector<string> res;
    stack<string> st;
    for (int i = 0; i < express.size(); i++)
    {
        if (i % 2 == 0)
        {
            //숫자
            res.push_back(express[i]);
        }
        else
        {
            string one(1, op[0]); //가장 높은 우선순위
            string two(1, op[1]);
            string three(1, op[2]);

            if (express[i] == one)
            {
                //가장 우선순위가 높으니까 바로 처리 (연산할 숫자를 꺼내야 한다. )
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
            else
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
    return res;
}
long long solution(string expression)
{
    ll ans = 0;
    int idx = 0;
    for (int i = 0; i < expression.size(); i++)
    {
        if ('0' <= expression[i] && expression[i] <= '9')
        {
            continue;
        }
        else
        {
            //앞까지는 숫자
            string tmp = expression.substr(idx, i - idx);
            express.push_back(tmp);
            idx = i + 1;
            express.push_back(string(1, expression[i]));
        }
    }
    string tmp = expression.substr(idx, expression.size() - idx);
    express.push_back(tmp);
    ll res = 0;
    do
    {

        vector<string> post = toPostExp();
        //스택을 통한 계산을 하기 위해 후위식으로 바꿔준다.
        res = calc(post);
        ans = ans > res ? ans : res;

    } while (next_permutation(op, op + 3));
    
    return ans;
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cout << solution("100-200*300-500+20");
    return 0;
}