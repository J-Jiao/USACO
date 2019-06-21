/*
 ID: joanna02
 TASK: beads
 LANG: C++
 */
#include <iostream>
#include <algorithm>
#include <math.h>
#include <unordered_map>
#include <vector>
#include <queue>
#include <cstring>
#include <stack>
#include <iterator>
#include <set>
#include <cstdio>
#include <fstream>
using namespace std;


//true - red; false - blue;
int n, decreaseby;
string s = "x";
vector<pair<char,int>>group;
vector<pair<int,int>>ins;

string addto(int x, char c){
    string a = "";
    for(int i = 0; i < x; i++){
        a += c;
    }
    return a;
}

bool issame(string x){
    for(int i = 1; i < x.size(); i++){
        if(x[i] != x[i-1])
            return 0;
    }
    return 1;
}

int main(){
    
    
    freopen("beads.in", "r", stdin);
    freopen("beads.out", "w", stdout);
    
    string tem;
    cin >> n >> tem;
    if(issame(tem)){
        cout << tem.size() << endl;
        return 0;
    }
    s+=tem;s+='x';
    for(int i = 1; i <= n; i++){
        if(s[i] == 'w'){
            int j = i;
            while(s[i+1]=='w'){
                i++;
            }
            if(s[j-1] == s[i+1] && s[j-1] != 'x'){
                s.erase(j,i-j+1);
                s.insert(j-1,addto(i-j+1,s[j-1]));
            }
        }
    }
    if(s[1] == s[n]){
        int i = 1;
        string sub;
        while(s[i] == s[i+1]){
            ++i;
        }
        sub = s.substr(1,i);
        s.erase(1,i);
        s.insert(n-i,sub);
    }
    for(int i = 1; i <= n; i++){
        group.push_back({s[i],1});
        ins.push_back({i,0});
        while(s[i] == s[i+1]){
            group.back().second++;
            i++;
        }
        ins.back().second = i;
    }
    if(group[0].first == 'w'){
        if(group[1].first == group.back().first){
            group.back().second+=group[1].second+group.front().second;
            group.erase(group.begin(),group.begin()+2);
            string sub = addto(ins[1].second,group.back().first);
            s.erase(1,ins[1].second);
            s.insert(n-sub.size(),sub);
            ins.back().second += (ins[1].second-ins[0].first+1);
            ins.erase(ins.begin(),ins.begin()+2);
            decreaseby = sub.size();
        }
        else{
            group.back().second += group.front().second;
            group[1].second += group[0].second;
            group.erase(group.begin());
            string sub = s.substr(1,ins[0].second);
            s.erase(1,ins[0].second);
            s.insert(n-sub.size(),sub);
            ins.back().second += (ins[0].second-ins[0].first+1);
            ins.erase(ins.begin());
            decreaseby = sub.size();
        }
    }
    else if(group.back().first == 'w'){
        if(group[group.size()-2].first == group.front().first){
            group[group.size()-2].second+=group[0].second+group.back().second;
            decreaseby = group.front().second;
            group.erase(group.begin());
            group.erase(group.end()-1);
            string sub = addto(ins[0].second+n-ins.back().first+1, group[group.size()-1].first);
            
            s.erase(1,ins[0].second);
            s.erase(ins.back().first-ins[0].second,ins.back().second-ins.back().first+1);
            s.insert(n-sub.size(),sub);
            ins[ins.size()-2].second += (ins[1].second-ins[0].first+1);
            ins.erase(ins.begin());
            ins.erase(ins.end()-1);
        }
        else{
            group.front().second += group.back().second;
            group[group.size()-2].second+=group.back().second;
            group.erase(group.end()-1);
            ins[ins.size()-2].second = ins.back().second;
            ins.erase(ins.end()-1);
        }
    }
    for(int i = 0; i < group.size(); i++){
        if(group[i].first == 'w'){
            group[i-1].second += group[i].second;
            group[i+1].second += group[i].second;
            group.erase(group.begin()+i);
            ins[i-1].second = ins[i].second;
            ins[i+1].first = ins[i].first;
            ins.erase(ins.begin()+i);
        }
    }
    int maximum = group.front().second + group.back().second;
    int ind = group.size()-1;
    for(int i = 0; i < group.size()-1; i++){
        if((ins[i+1].second - ins[i].first + 1)>=maximum){
            maximum = max(maximum,ins[i+1].second - ins[i].first + 1);
            ind = i;
        }
    }
    if(ind == group.size()-1){
        maximum = ins.front().second + (n-ins.back().first+1);
    }
    maximum = min(n,maximum);
    cout << maximum << endl;
    
    return 0;
}

