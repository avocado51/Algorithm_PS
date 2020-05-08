#include <string>
#include <vector>
#include<map>

using namespace std;
//Programmers 카카오 기출 [압축]
vector<int> solution(string msg) {
    vector<int> answer;
    int idx = 1;
    map<string, int> wordMap;
    
    //길이가 1인 단어를 넣는다. 
    for (int i = 0; i < 26; i++) {
        string x(1, 'A'+i);
        wordMap[x] = idx++;
    }
    
    int n = msg.size();
    for (int i = 0; i < n; ) {
        bool flag =false;
        string x(1, msg[i]);
        string w;
        map<string, int> ::iterator it;
        it = wordMap.find(x);
        int idx1 = it->second;
        int idx2 = 0;
        int endIdx = i;
        for (int j = i; j < n; j++) {
            //2. 현재 입력과 일치하는 가장 긴 문자열을 찾는다. 
            w += msg[j];
            if (wordMap.find(w) == wordMap.end()) 
            {
                wordMap[w] = idx++;
                break;
            }
            else {
                idx2 = wordMap[w];
                endIdx = j;
            }
        }
        if (!idx2) 
        {
            answer.push_back(idx1);
            i++;
        }
        else {
            answer.push_back(idx2);
            i = endIdx+1;
        }
        
    }
    
    return answer;
}