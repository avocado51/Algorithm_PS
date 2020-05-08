#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

//Programmers 카카오 기출[압축]
int solution(int size, vector<string> cities)
{
    int answer = 0;
   
    vector<string> q;

    if (size == 0) {
        answer = cities.size() * 5;
        return answer;
    }
    for (int i = 0; i < cities.size(); i++)
    {
       transform(cities[i].begin(), cities[i].end(),cities[i].begin(), ::toupper);
        
        vector<string> :: iterator it = find(q.begin(), q.end(), cities[i]);
        
        if (it != q.end())
        {
            //큐안에 있으면 
            answer++;
            //맨 뒤로 보낸다. 
            q.erase(it);
            q.push_back(cities[i]);
        }
        else {
             //큐 안에 없음 
            answer += 5;
            if (q.size() < size)
            {
                q.push_back(cities[i]);
            }
            else
            {
                // 맨 앞의 요소를 제거하고 넣는다.
                q.erase(q.begin());
                q.push_back(cities[i]);
            }
        }
       
    }

    return answer;
}