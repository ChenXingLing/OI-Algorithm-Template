#include<algorithm>
#include<cstdio>
#define Re register int
using namespace std;
const int N=103,inf=1e8;
int n,m,x,y,z,ans,Ans[N],a[N][N],g[N][N],dis[N][N];
inline void in(Re &x){
	Re fu=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=fu?-x:x;
}
inline void get(Re i,Re j){
	Re k=g[i][j];if(!k)return;
	get(i,k),Ans[++Ans[0]]=k,get(k,j);
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(m);
	for(Re i=1;i<=n;++i)
		for(Re j=1;j<=n;++j)
			dis[i][j]=a[i][j]=inf;//用a记录边（邻接矩阵），dis记录路径
	for(Re i=1;i<=n;++i)dis[i][i]=a[i][i]=0;
	while(m--)in(x),in(y),in(z),dis[x][y]=dis[y][x]=a[x][y]=a[y][x]=min(a[x][y],z);
	ans=inf;
	for(Re k=1;k<=n;++k){
		for(Re i=1;i<k;++i)//注意这里要求i,j,k三点互不相同。至于i,j大于k的情况，枚举与否不影响答案（只是会被重复计算）
			for(Re j=i+1,tmp;j<k;++j)	
				if((tmp=dis[i][j]+a[j][k]+a[k][i])<ans){
					ans=tmp,Ans[0]=0;
					Ans[++Ans[0]]=i;
					get(i,j);
					Ans[++Ans[0]]=j;
					Ans[++Ans[0]]=k;
				}
		for(Re i=1;i<=n;++i)
			for(Re j=1,tmp;j<=n;++j)
				if((tmp=dis[i][k]+dis[k][j])<dis[i][j])	
					dis[i][j]=tmp,g[i][j]=k;//用g记录下决策点
	}
	if(ans==inf)puts("No solution.");
	else for(Re i=1;i<=Ans[0];++i)printf("%d ",Ans[i]); 
}
