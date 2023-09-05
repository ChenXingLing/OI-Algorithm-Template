#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+5;
int n,x,y,T,op,A[N];
inline void in(Re &x){
	Re fu=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=fu?-x:x;
}
struct Leftist_Tree{
	int fa[N],pl[N],pr[N],dis[N];
	inline int merge(Re x,Re y){
		if(!x||!y)return x+y;
		if(A[x]>A[y]||(A[x]==A[y]&&x>y))swap(x,y);
		pr[x]=merge(pr[x],y);
		if(dis[pl[x]]<dis[pr[x]])swap(pl[x],pr[x]);
		dis[x]=dis[pr[x]]+1;
		if(pl[x])fa[pl[x]]=x;
		if(pr[x])fa[pr[x]]=x;
		return x;
	}
	inline int top(Re x){return fa[x]==x?x:fa[x]=top(fa[x]);}
	inline void pop(Re x){
		A[x]=-1,fa[pl[x]]=pl[x],fa[pr[x]]=pr[x];
		fa[x]=merge(pl[x],pr[x]),pl[x]=pr[x]=0;
	}
}T1;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T);
	for(Re i=1;i<=n;++i)in(A[i]),T1.fa[i]=i;
	while(T--){
		in(op),in(x);
		if(op&1){
			in(y);
			if(A[x]!=-1&&A[y]!=-1){
				x=T1.top(x),y=T1.top(y);
				if(x!=y)T1.merge(x,y);
			}
		}
		else if(A[x]==-1)puts("-1");
		else printf("%d\n",A[T1.top(x)]),T1.pop(T1.top(x));
	}
}
