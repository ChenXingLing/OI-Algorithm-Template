#include<algorithm>
#include<cstdio>
#include<queue>
#define Re register int
using namespace std;
const int N=5003,M=1e5+3,inf=1e9;
int n,m,x,y,z,o,pan[N],head[N],dis[N][2];
struct QAQ{int w,to,next;}a[M<<1];queue<int>Q;
inline void add(Re x,Re y,Re z){a[++o].w=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    Re fu=0;x=0;char ch=getchar();
    while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x=fu?-x:x;
}
inline void SPFA(Re st){
	for(Re i=1;i<=n;++i)dis[i][0]=dis[i][1]=inf;
	Q.push(st),dis[st][0]=0,pan[st]=1;
	while(!Q.empty()){
		Re x=Q.front();Q.pop();pan[x]=0;
		for(Re i=head[x],to;i;i=a[i].next){
//从x节点出去有两个信息：最短dis[x][0]+a[i].w和次短dis[x][1]+a[i].w，分别拿这两个东西去更新dis[to]的最短和次短 
			if(dis[to=a[i].to][0]>dis[x][0]+a[i].w){//x最短+w 优于to最短 
				dis[to][1]=dis[to][0];//先把to的最短传给次短
				dis[to][0]=dis[x][0]+a[i].w;
				if(!pan[to])pan[to]=1,Q.push(to);
			}
			if(dis[to][0]<dis[x][0]+a[i].w&&dis[to][1]>dis[x][0]+a[i].w){//x最短+w 劣于to最短，但优于to次短
			//（注意这里不能紧接着上面那个if写一个else。因为当dis[to][0]==dis[x][0]+a[i].w时是不能更新to次短的，否则to的最短和次短就一样长了） 
				dis[to][1]=dis[x][0]+a[i].w;
				if(!pan[to])pan[to]=1,Q.push(to);
			}
			if(dis[to][1]>dis[x][1]+a[i].w){//x次短+w 优于to次短（x次短+w 是不可能更新to最短的，因为前面已经有一个更优秀的"x最短+w"了） 
				dis[to][1]=dis[x][1]+a[i].w;
				if(!pan[to])pan[to]=1,Q.push(to);
			}
		}
	}
}
int main(){
    in(n),in(m);
    while(m--)in(x),in(y),in(z),add(x,y,z),add(y,x,z);
    SPFA(1);
    printf("%d\n",dis[n][1]);
}
