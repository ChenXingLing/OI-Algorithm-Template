#include<cstring>
#include<cstdio>
#define Re register int
const int N=1003;
int o,n,m,e,x,y,ans,pan[N],head[N],match[N];
struct QAQ{int to,next;}a[N*N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline int dfs(Re x){
	for(Re i=head[x],to;i;i=a[i].next)
		if(!pan[to=a[i].to]){
			pan[to]=1;
			if(!match[to]||dfs(match[to])){
				match[to]=x;return 1;
			}
		}
	return 0;
}
int main(){
	in(n),in(m),in(e);
	while(e--){
		in(x),in(y);
		if(x<=n&&y<=m)add(x,y);
	}
	for(Re i=1;i<=n;++i){
		memset(pan,0,sizeof(pan));
		ans+=dfs(i);
	}
	printf("%d",ans);
}
