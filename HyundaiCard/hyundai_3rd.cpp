#include <string>
#include <vector>
#include <map>
using namespace std;

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