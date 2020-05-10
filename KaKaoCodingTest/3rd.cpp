#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#define INF 987654321

using namespace std;

vector<int> solution(vector<string> gems)
{
    vector<int> answer;

    int MAXX = INF;

    unordered_map<string, int> gemMap;
    unordered_map<string, int> visited;

    for (int i = 0; i < gems.size(); i++)
        gemMap[gems[i]] = 1;

    int size = gemMap.size();

    deque<string> q;

    int left = 1, right = 1;
    int startIdx = 0, endIdx = 0;
    for (int i = 0; i < gems.size(); i++)
    {
        q.push_back(gems[i]);
        right++;

        //보석 없으면 넣는다. 
        if (visited.find(gems[i]) == visited.end())
            visited[gems[i]] = 1;
        else
            visited[gems[i]]++;

        //모든 보석이 다 들어있다면 
        //left를 늘려가면서 슬라이딩 윈도우
        while (visited.size() == gemMap.size())
        {
            string now = q.front();
            q.pop_front();

            if (visited[now] == 1)
                visited.erase(visited.find(now));
            else
                visited[now]--;

            if (visited.size() < gemMap.size())
            {
                q.push_front(now);
                visited[now] = 1;
                left = right - q.size();
                break;
            }
        }

        if (visited.size() == gemMap.size() && MAXX > q.size())
        {
            startIdx = left;
            endIdx = right - 1;
            MAXX = q.size();
            right = i + 2;
        }
    }
    answer.push_back(startIdx);
    answer.push_back(endIdx);
    return answer;
}