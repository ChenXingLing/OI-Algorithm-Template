#include<algorithm>
#include<cstring>
#include<cstdio>
#define Re register int
const int N=2e6+3,M=2e6+3;
int n,m,mm,p1,p2,x1,x2,Q_o,X[M],Y[M],ip[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Kosaraju{
	int o,ndfn_o,nQ[N],pan[N],head[N];
	struct QAQ{int x,to,next;}a[M];
	inline void add(Re x,Re y){a[++o].x=x,a[o].to=y,a[o].next=head[x],head[x]=o;}
	inline void dfs1(Re x){
		pan[x]=1;
		for(Re i=head[x];i;i=a[i].next)if(!pan[a[i].to])dfs1(a[i].to);
		nQ[++ndfn_o]=x;
	}
	inline void dfs2(Re x){
		ip[x]=Q_o;
		for(Re i=head[x];i;i=a[i].next)if(!ip[a[i].to])dfs2(a[i].to);
	}
	inline void kosaraju(){
		for(Re i=1;i<=m;++i)add(X[i],Y[i]);
		for(Re i=1;i<=2*n;++i)if(!pan[i])dfs1(i);//ÅÜÄædfsÐò
		memset(head,0,sizeof(head));
		memset(pan,0,sizeof(pan));
		memset(a,0,sizeof(a));o=0;
		for(Re i=1;i<=m;++i)add(Y[i],X[i]);//½¨·´Í¼
		for(Re i=ndfn_o;i;--i)if(!ip[nQ[i]])++Q_o,dfs2(nQ[i]);//Ëõµã
	}
}T1;
int main(){
	in(n),in(mm);
	while(mm--)in(p1),in(x1),in(p2),in(x2),X[++m]=p1+(x1^1)*n,Y[m]=p2+x2*n,X[++m]=p2+(x2^1)*n,Y[m]=p1+x1*n;
	T1.kosaraju();
	for(Re i=1;i<=n;++i)if(ip[i]==ip[i+n])return !printf("IMPOSSIBLE");
	puts("POSSIBLE");
	for(Re i=1;i<=n;++i)printf("%d ",ip[i]<ip[i+n]);
}
