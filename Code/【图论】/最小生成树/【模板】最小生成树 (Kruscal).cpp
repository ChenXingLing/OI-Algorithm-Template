#include<algorithm>
#include<cstdio>
#define Re register int
using namespace std;
const int N=5003,M=2e5+3;
int n,m,ans,fa[N];
struct QAQ{int x,y,w;inline bool operator<(const QAQ &O)const{return w<O.w;};}A[M];
inline void in(Re &x){
	Re fu=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=fu?-x:x;
}
inline int find(Re x){return x==fa[x]?x:fa[x]=find(fa[x]);}
int main(){
	in(n),in(m);
	for(Re i=1;i<=n;++i)fa[i]=i;
	for(Re i=1;i<=m;++i)in(A[i].x),in(A[i].y),in(A[i].w);
	sort(A+1,A+m+1);
	for(Re i=1,t=0;i<=m&&t<n-1;++i){
		Re x=find(A[i].x),y=find(A[i].y);
		if(x!=y)++t,ans+=A[i].w,fa[x]=y;
	}
	printf("%d",ans);
}
