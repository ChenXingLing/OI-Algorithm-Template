#include<cstring>
#include<cstdio>
#define R register int
using namespace std;
const int SP=500003;
int trie[SP][26],pan[SP],ed[SP],re,t=1,n,m;char ch[55];
inline void add(char ch[]){
    R a,i=0,p=1,l=strlen(ch);
    for(;i<l;i++){
        a=ch[i]-'a';
        if(!trie[p][a])trie[p][a]=++t;
        p=trie[p][a];
    }
    ++ed[p];
}
inline int find(char ch[]){
    R i=0,p=1,ans=0,l=strlen(ch);
    for(;i<l;i++){
        p=trie[p][ch[i]-'a'];
        ans+=ed[p];
        if(!p)return ans;
    }
    return ans;
}
int main(){
    scanf("%d%d",&n,&m);
    while(n--){scanf("%s",ch);add(ch);}
    while(m--){scanf("%s",ch);printf("%d\n",find(ch));}
}
