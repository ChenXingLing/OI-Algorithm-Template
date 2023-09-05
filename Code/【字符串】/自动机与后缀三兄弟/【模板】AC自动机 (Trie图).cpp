#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define Re register int
#define LL long long
using namespace std;
const int N=2e5+3;
int n;char ch[N*10];
inline void in(Re &x){
    int fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
struct AC_Automaton{
	int O,edp[N],fail[N],tr[N][26];queue<int>Q;
	AC_Automaton(){O=1;}
	inline void insert(char ch[],Re id){
		Re p=1;
		for(Re i=1;ch[i];++i){
			Re a=ch[i]-'a';
			if(!tr[p][a])tr[p][a]=++O;
			p=tr[p][a];
		}
		edp[id]=p;
	}
	inline void get_fail(){
		for(Re i=0;i<26;++i)tr[0][i]=1;
		Q.push(1);
		while(!Q.empty()){
			Re x=Q.front();Q.pop();
			for(Re i=0;i<26;++i)
				if(tr[x][i])fail[tr[x][i]]=tr[fail[x]][i],Q.push(tr[x][i]);
				else tr[x][i]=tr[fail[x]][i];
		}
	}
	int ru[N],cnt[N];
	inline void sakura(char ch[]){
		for(Re i=1,p=1;ch[i];++i)p=tr[p][ch[i]-'a'],++cnt[p];
		for(Re i=2;i<=O;++i)++ru[fail[i]];
		for(Re i=1;i<=O;++i)if(!ru[i])Q.push(i);
		while(!Q.empty()){
			Re x=Q.front();Q.pop();
			cnt[fail[x]]+=cnt[x];
			if(!(--ru[fail[x]]))Q.push(fail[x]);
		}
		for(Re i=1;i<=n;++i)printf("%d\n",cnt[edp[i]]);
	}
}AC;
int main(){
//	freopen("123.txt","r",stdin);
	in(n);
	for(Re i=1;i<=n;++i)scanf("%s",ch+1),AC.insert(ch,i);
	AC.get_fail();
	scanf("%s",ch+1);AC.sakura(ch);
}
