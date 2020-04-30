#include <string>
#include <vector>
#include <map>
using namespace std;
/*
이미 가입된 회원들의 아이디와 사용자가 원하는 아이디가 주어진다. 
사용자가 원하는 아이디가 아이디 목록에 없다면 그 아이디를 사용하고, 
만약 없다면 해당 조건에 따라 유효한 아이디를 만든다. 
1. 아이디는 문자열 / 문자열 + 숫자로 이루어져있다. 
2. 숫자는 null 일 수 있다. -> null일 때는 숫자를 1부터 붙여가면서 유효한 아이디임을 검사한다.
3. 숫자가 null이 아닌 경우 -> 숫자 + 1 을 붙여가면서 유효한 아이디임을 검사한다.
*/
string solution(vector<string> registered_list, string new_id) {
    string answer = "";
    map<string, int> idMap;
    
    for (int i =0; i < registered_list.size(); i++ ) {
        idMap[registered_list[i]] = 1;
    }
    
    if (idMap.count(new_id) == 0) return new_id;
    
    string n, s;
    bool chk = false;
    
    for (int i = 0; i < new_id.size(); i++) {
        if ('0' <= new_id[i] && new_id[i] <= '9') {
            chk = true;
            n += new_id[i];
        }
        else s += new_id[i];
    }
    
    if (chk) {
        //숫자가 있으면 
        int tmp = stoi(n);
        for (int i = tmp+1;; i++) {
            //숫자에 1을 더한 값 
            if (idMap.count(s+to_string(i)) == 0) {
                answer = s + to_string(i);
                break;
            }
        }
    }
    else {
        //숫자가 없으면 
        for (int i = 1;; i++) {
            if (idMap.count(s+to_string(i)) == 0) {
                answer += s+to_string(i);
                break;
            }
        }
    }
    return answer;
}