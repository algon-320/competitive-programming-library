#pragma once

#include <bits/stdc++.h>
using namespace std;

// pairを見やすく出力する
template<class T,class U> ostream& operator << (ostream &os,const pair<T,U> &p) {
    os<<"\x1b[1m"<<"("<<p.first<<","<<p.second<<")"<<"\x1b[m";
    return os;
}

// dump(...)用
queue<string> argment_contents;
void set_args_con() {}
template<class First, class... Rest>
void set_args_con(const First& first, const Rest&... rest) {
    stringstream ss;
    ss << first;
    argment_contents.push(ss.str());
    set_args_con(rest...);
}
string gen_string(string s) {
    s += ',';
    string ret = "";
    int par = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '(' || s[i] == '<' || s[i] == '{') par++;
        else if (s[i] == ')' || s[i] == '>' || s[i] == '}') par--;
        if (par == 0 && s[i] == ',') {
            ret += "=" + argment_contents.front();
            argment_contents.pop();
            if (i != (int)s.size() - 1) {
                ret += ",";
            }
        } else {
            ret += s[i];
        }
    }
    return ret;
}
#ifdef dump
    #undef dump
#endif
#define dump(...) { set_args_con(__VA_ARGS__); cerr << "\x1b[1m" << gen_string(#__VA_ARGS__) << "\x1b[m" << endl; }

// 2次元vectorを出力する
template<class T>
void dump_vv(T vv, int k=-1, char fill='0', char sep=' ') {
    for(int i=0; i<(int)vv.size(); i++) {
        for(int j=0; j<(int)vv[0].size(); j++) {
            cerr<<"\x1b[1m";
            if(k!=-1) cerr<<setw(k)<<setfill(fill);
            cerr<<vv[i][j]<<sep<<"\x1b[m";
        }
        cerr<<endl;
    }
}


// 文字列に値を埋め込む
// {}の部分が引数の値で置き換えられる
string embed(const string &s) {
    return s;
}
template <typename Head, typename... Tail>
string embed(const string &s, const Head &val, const Tail&... tail) {
    string ret = "";
    bool par = false, embedded = false;
    string buf = "";
    for (auto& c : s) {
        if (embedded) {
            ret += c;
            continue;
        }

        if (!par && c == '{') {
            par = true;
            buf += c;
            continue;
        } else if (par && c == '}') {
            stringstream ss;
            ss << val;
            ret += ss.str();
            par = false;
            buf = "";
            embedded = true;
            continue;
        }
        
        if (!par) {
            ret += c;
        } else {
            buf += c;
        }
    }
    if (!buf.empty()) {
        ret += buf;
    }
    ret = embed(ret, std::move(tail)...);
    return ret;
}