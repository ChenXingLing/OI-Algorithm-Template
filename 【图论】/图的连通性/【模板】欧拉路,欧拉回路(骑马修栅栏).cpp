#include<algorithm>
#include<cstdio>
#define Re register int
using namespace std;
const int N=1030;
int n,x,y,mi=2e9,st=2e9,as,du[N],ans[N],r[N][N];
inline void in(Re &x){
	Re fu=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=fu?-x:x;
}
inline void dfs(Re x){
	for(Re i=1;i<=500;++i)
		if(r[x][i]){
			--r[x][i],--r[i][x];
			dfs(i);
		}
	ans[++as]=x;
}
int main(){
	in(n);
	for(Re i=1;i<=n;++i)in(x),in(y),++r[x][y],++r[y][x],++du[x],++du[y],mi=min(mi,min(x,y));
	for(Re i=1;i<=500;++i)if(du[i]&1)st=min(st,i);
	if(st==2e9)st=mi;//没有奇数点，即为欧拉回路 
	dfs(st);
	for(Re i=as;i;--i)printf("%d\n",ans[i]);
}
