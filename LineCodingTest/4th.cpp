#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

vector<vector<string>> solution(vector<vector<string>> snapshots, vector<vector<string>> transactions) {
    vector<vector<string>> answer;
    map<string, int> account;
    //키 : 계좌번호 값 : 금액 
    int n = snapshots.size();
    
    for (int i =0; i <n; i++ ) {
        account[snapshots[i][0]] += stoi(snapshots[i][1]);
    }
    
    //로그는 id로 구분되고 id가 같은 경우 같은 로그이기 때문에 한 번 만 처리하도록 한다. 
    vector<string> v;
    int m = transactions.size();
    for (int i = 0; i <m; i++ ) {
        //계좌가 추가될 수도 있다. 
        if (find(v.begin(), v.end(),transactions[i][0])!= v.end()) continue;
        v.push_back(transactions[i][0]);
        if (transactions[i][1] == "SAVE") {
            //계좌에 잔액을 플러스 
            if (account[transactions[i][2]] == 0) {
                account[transactions[i][2]] += stoi(transactions[i][3]);
            }
            else account[transactions[i][2]] += stoi(transactions[i][3]);
        }
        else {
            account[transactions[i][2]] -= stoi(transactions[i][3]);
        }
    }
    //계좌이름, 잔액을 배열로 반환 
    //계좌이름을 기준으로 오름차순
    map<string, int>::iterator it = account.begin();
    
    for (;it != account.end(); it++) {
        vector<string> tmp;
        tmp.push_back(it->first);
        tmp.push_back(to_string(it->second));
        answer.push_back(tmp);
    }
    
    
    return answer;
}