#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;
int arriveTime[2001];
void changeTimeUnit(vector<string> time)
{
    for (int i = 0; i < time.size(); i++)
    {
        string h = time[i].substr(0, 2);

        int hour = stoi(h);
        string m = time[i].substr(3, 2);

        int minute = stoi(m);

        arriveTime[i] = hour * 60 + minute;
    }
}
string solution(int n, int t, int m, vector<string> timetable)
{
    string answer = "";
    int size = timetable.size();
    int res = 0;
    //크루의 수가 셔틀버스 수용인원 *n보다 작다면 제일 마지막 셔틀버스를 탑승한다.
    //hour->minutes;
    changeTimeUnit(timetable);

    sort(arriveTime, arriveTime + size); //오름차순 정렬

    int start = 540; //09:00
    int idx = 0;
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        int full = m; //0이 될 때까지 태운다.
        for (int j = idx; j < size; j++)
        {
            if (arriveTime[j] <= start)
            {
                idx++; //태움
                full--;
                if (!full)
                    break; //이번 텀에 모두 태움
            }
        }
        if (i + 1 == n)
        {
            //마지막 버스일 때
            if (!full)
            {
                //만원 버스이면
                res = arriveTime[idx - 1] - 1; //가장 마지막 사람보다 1분 빠르게
            }
            else
            {
                res = start;
            }
        }
        start += t;
        if (start >= 60 * 24)
            break; //하루를 지나지 않는다.
    }

    //가장 마지막에 탄 사람을 빼내고 콘이 탄다.
    if (res / 60 < 10)
    {
        answer += "0";
        answer += to_string(res / 60);
    }
    else
    {
        answer += to_string(res / 60);
    }
    answer += ":";
    if (res % 60 == 0)
    {
        answer += "00";
    }
    else
    {
        if (res % 60 < 10)
        {
            answer += "0";
            answer += to_string(res % 60);
        }
        else
        {
            answer += to_string(res % 60);
        }
    }
    return answer;
}
