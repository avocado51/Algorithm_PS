#include <string>
#include <vector>
#include <iostream>
using namespace std;
int days[12] ={31,28,31,30,31,30,31,31,30,31,30,31};
int res[366]; // 365 + 30 으로 잡아줘야 한다. 
/*
회원의 구매 등급은 30일간 유지된다. 
브론즈
실버
골드
플래티넘
다이아

구매 날짜와 구매한 금액의 리스트가 주어질 때, 브론즈, 실버, 골드, 플래티넘, 다이아 순으로 몇일동안 등급이 유지되는지를 저장해서 반환
*/
vector<int> solution(vector<string> purchase) {
    vector<int> answer(5);

    for (int i = 0; i < purchase.size(); i++) {
        int period = 0; //구매한 기간 (월, 일 합)
        
        //구매한 월   
        int month = stoi(purchase[i].substr(5,2));
        
        for (int j = 0; j < month-1; j++) {
            period += days[j]; //월에 맞는 날짜수를 더해준다. 
            
        }
        //구매한 일 
        period += stoi(purchase[i].substr(8,2));
        //금액 
        int money = stoi(purchase[i].substr(11,purchase[i].size()-1));

        for (int j = 0; j < 30; j++) {
            res[j+period] += money;
        }
    }
     for (int i = 0; i < 365; i++) {
        if (0 <= res[i] && res[i] < 10000)
            answer[0]++;
        else if (res[i] < 20000)
            answer[1]++;
        else if (res[i] < 50000)
            answer[2]++;
        else if (res[i] < 100000)
            answer[3]++;
        else if (res[i] >= 100000)
            answer[4]++;
    }
    
    return answer;
}