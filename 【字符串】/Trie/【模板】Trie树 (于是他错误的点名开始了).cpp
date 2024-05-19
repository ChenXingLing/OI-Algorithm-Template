#pragma once
#include<cstring>
#include<cstdio>
#define R register int
using namespace std;
const int SP=500003;
int trie[SP][26],pan[SP],ed[SP],re,t=1,n;
char ch[55];
inline void add(char ch[]){
    R a,i=0,p=1,m=strlen(ch);
    for(;i<m;i++){
        a=ch[i]-'a';
        if(!trie[p][a])trie[p][a]=++t;
        p=trie[p][a];
    }
    ed[p]=1;
}
inline int find(char ch[]){
    R re,i=0,p=1,m=strlen(ch);
    for(;i<m;i++){
        p=trie[p][ch[i]-'a'];
        if(!p)return 0;
    }
    re=ed[p];
    if(ed[p])ed[p]++;
    return re;
}
int main(){
    scanf("%d",&n);
    while(n--){scanf("%s",ch);add(ch);}
    scanf("%d",&n);
    while(n--){
        scanf("%s",ch);
        re=find(ch);
        if(!re)printf("WRONG\n");
        else if(re==1)printf("OK\n");
        else printf("REPEAT\n");
    }
}
