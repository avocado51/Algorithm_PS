#include <string>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

int max(const int &a, const int &b) {
    if (a > b) return a;
    return b;
}
int solution(string answer, vector<string> sheet) {
    int ans = 0;
    int n = sheet.size();
    int maxx = 0;
    int idx1 = 0, idx2 = 0;
    for (int i = 0; i < n-1; i++) {
       //1번 답안과 2,3,4,5... 답안을 비교 (2와 1, 3과 1 을 다시 비교할 필요 없음)
        for (int j = i+1; j < n; j++) {
             int cnt = 0;
            for (int k = 0; k < answer.size(); k++) {
                if (answer[k] != sheet[i][k] && sheet[i][k] == sheet[j][k]) {
                    //의심문항의 수는 오답이면서 두 명의 답이 같은 경우이다. 
                    cnt++;
                }
            }
            //의심문항의 수를 구한다. -> 최다 의심문항의 수를 가진 두 명을 인덱스로 저장 
            if (cnt > maxx) {
                maxx = cnt;
                idx1 = i;
                idx2 = j;
            }
        }
    }
    //모두다 정답만 낸 경우에는 의심문항의 수가 없다. 
    if (!maxx) return 0;

    //idx1과 idx2사이의 가장 긴 연속된 의심 문항의 수를 구한다.

    bool flag =false;
    int seq = 0; //연속된 의심 문항의 수 
    int longCnt = 0;
    
    //연속된다=> 중간에 정답이 껴있거나 서로 답이 다르면 연속되지 않는다. 
    for (int i = 0; i < answer.size(); i++) {
        if (answer[i]!= sheet[idx1][i] && sheet[idx2][i] == sheet[idx1][i]){
            seq++;
        }
        else {
            longCnt = max(longCnt, seq);
            seq= 0;
        }
        
    }
    longCnt = max(longCnt, seq);

    ans = maxx +(int)pow(longCnt, 2);
    return ans;
}