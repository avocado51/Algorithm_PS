#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef pair<string, int> pp;

map<string, int> tagMap;
bool compare(const pp &a, const pp &b) {
    if (a.second > b.second) return true;
    else if (a.second == b.second) {
        if (a.first < b.first) return true;
        else return false;
    }
    return false;
}
vector<string> solution(vector<vector<string>> data, vector<string> tags) {
    vector<string> answer;
    int n = data.size();
    for (int i = 0; i < n; i++) {
        for (int j = 1;  j< n; j++) {
            for (int k = 0; k < tags.size(); k++) {
                if (data[i][j] == tags[k]) {
                    if (tagMap[data[i][0]] == 0) {
                        tagMap[data[i][0]] = 1;
                    }
                    else tagMap[data[i][0]]++;
                }
            }
        }
    }
    
    //문서들을 배열로 반환한다. 
    map<string, int> :: iterator it = tagMap.begin();
    vector<pp> v;
    for (; it != tagMap.end(); it++) {
        v.push_back(pp(it->first, it->second));
    }
    
    sort(v.begin(), v.end(), compare);
    
    for (int i = 0; i < v.size(); i++) {
        if (i >= 10) break;
        answer.push_back(v[i].first);
    }
    
    return answer;
}