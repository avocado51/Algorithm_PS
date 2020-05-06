import os
import sys


from collections import defaultdict

class Trie:

    def __init__(self):
        self.root = {} # chr|visited

    def insert(self, s):
        cur = self.root
        while s:
            if s[0] not in cur: cur[s[0]] = [ {} , 0 ]
            cur[s[0]][1] += 1
            cur = cur[s[0]][0]
            s = s[1:]

    def find(self, s)->int:
        cur = self.root; pre_v = 0
        while s:
            if s[0] == '?': return pre_v
            else:
                if s[0] not in cur: return 0
                pre_v = cur[s[0]][1]; cur = cur[s[0]][0]
            s = s[1:]

        return pre_v

def solution(words, queries):
    prefix_dict = defaultdict(Trie)
    suffix_dict = defaultdict(Trie)
    len_dict = defaultdict(int)
    result = []

    for word in words:
        prefix_dict[len(word)].insert(word)
        suffix_dict[len(word)].insert(word[::-1])
        len_dict[len(word)] += 1

    for q in queries:
        if q[0] == '?' and q[-1] == '?':
            result.append(len_dict[len(q)])
        elif q[-1] == '?': #preffix_query
            result.append( prefix_dict[len(q)].find(q))
        elif q[0] == '?': #suffix_query
            result.append( suffix_dict[len(q)].find(q[::-1]) )
        else:
            print("IMPOSSIBLE", q)

    return result