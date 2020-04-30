#include <string>
#include <vector>
#include <set>
using namespace std;

set<string> s;
set<string>::iterator it;
bool check(string target, string dir)
{
    for (int i = 0; i < target.size(); i++)
    {
        if (target[i] != dir[i])
            return false;
    }
    return true;
}
void cp(string from, string to)
{
    vector<string> v;
    for (int i = 0; i < from.size(); i++)
    {
        string tmp = "";
        int j = i;
        for (j = i; j < from.size() && from[j] != '/'; j++)
        {
            tmp += from[j];
        }
        v.push_back(tmp);
        i = j;
    }

    for (it = s.begin(); it != s.end(); it++)
    {
        if (to == "/")
        {
            if (check(from, *it))
            {
                string cnt = *it;
                string tmp = "";

                //마지막 제외
                int i = from.size() - v[v.size() - 1].size();
                for (; i < cnt.size(); i++)
                {
                    tmp += cnt[i];
                }
                string res = to + tmp;
                s.insert(res);
            }
        }
        else
        {
            if (check(from, *it))
            {
                string cnt = *it;
                string tmp = "";

                //마지막 제외
                int i = from.size() - v[v.size() - 1].size();
                for (; i < cnt.size(); i++)
                {
                    tmp += cnt[i];
                }
                string res = to + "/" + tmp;
                s.insert(res);
            }
        }
    }
}
void mkdir(string dir)
{
    s.insert(dir);
}

void rm(string dir)
{
    if (dir == "/")
    {
        s.clear();
    }

    for (auto iter = s.begin(); iter != s.end(); iter++)
    {
        if (check(dir, *iter))
        {
            s.erase(*iter);
            *iter--;
        }
    }
}

vector<string> solution(vector<string> directory, vector<string> command)
{
    vector<string> answer;

    for (int i = 0; i < directory.size(); i++)
    {
        s.insert(directory[i]);
    }

    for (int i = 0; i < command.size(); i++)
    {
        string cnt = "";
        string commandFrom = "";
        string commandTo = "";

        int j = 0;
        for (; command[i][j] != ' '; j++)
        {
            cnt += command[i][j];
        }

        j++;
        for (; j < command[i].size() && command[i][j] != ' '; j++)
        {
            if (command[i][j] != ' ')
                commandFrom += command[i][j];
        }

        j++;
        for (; j < command[i].size(); j++)
        {
            if (command[i][j] != ' ')
                commandTo += command[i][j];
        }

        if (cnt == "mkdir")
        {
            mkdir(commandFrom);
        }
        else if (cnt == "cp")
        {
            cp(commandFrom, commandTo);
        }
        else
        {
            rm(commandFrom);
        }
    }

    for (it = s.begin(); it != s.end(); it++)
    {
        answer.push_back(*it);
    }

    return answer;
}
