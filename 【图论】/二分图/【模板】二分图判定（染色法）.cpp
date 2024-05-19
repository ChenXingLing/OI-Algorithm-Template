#include<algorithm>
#include<cstring>
#include<cstdio>
#define Re register int
using namespace std;
const int N=2003,M=1e6+3;
int n,m,x,y,h,t,o,T,O,Q[N],head[N],color[N];
struct QAQ{int to,next;}a[M<<1];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline int judge(){
	for(Re i=1;i<=n;++i)
		if(!color[i]){
			h=1,t=0,Q[++t]=i,color[i]=1;
			while(h<=t){
				Re x=Q[h++];
				for(Re j=head[x],to;j;j=a[j].next)
					if(!color[to=a[j].to])color[to]=3-color[x],Q[++t]=to;
					else if(color[to]==color[x])return 0;
			}
		}
	return 1;
}
int main(){
	in(T);
	while(T--){
		memset(color,0,sizeof(color));
		memset(head,0,sizeof(head));
		in(n),in(m),o=0;
		while(m--)in(x),in(y),add(x,y),add(y,x);
		printf("Scenario #%d:\n",++O);
		puts(judge()?"No suspicious bugs found!\n":"Suspicious bugs found!\n");
	}
}
