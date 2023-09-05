#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
#define LL long long
#define Re register int
using namespace std;
const int N=1003,M=503;
int n,m,x,y,T,Q_o,tmp,ans1,cut[N];LL ans2;
std::vector<int>dcc[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline int max(Re a,Re b){return a>b?a:b;}
struct Tarjan{
	int o,t,dfn_o,Q[N],dfn[N],low[N],head[N];
	struct QAQ{int to,next;}a[M<<1];
	inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
	inline void CL(){
		memset(head,0,sizeof(head));
		memset(low,0,sizeof(low));
		memset(dfn,0,sizeof(dfn));
		memset(cut,0,sizeof(cut));
		dfn_o=t=o=0;
	}
	inline void tarjan(Re x,Re rt){
		Re son=0;Q[++t]=x,dfn[x]=low[x]=++dfn_o;
		for(Re i=head[x],to;i;i=a[i].next)
			if(!dfn[to=a[i].to]){
				tarjan(to,rt),++son;
				low[x]=min(low[x],low[to]);
				if(low[to]>=dfn[x]){
					if(x!=rt)cut[x]=1;
					else cut[x]|=son>1;
					++Q_o;
					while(1){
						dcc[Q_o].push_back(Q[t]);
						if(to==Q[t--])break;
					}
					dcc[Q_o].push_back(x);
				}
			}
			else low[x]=min(low[x],dfn[to]);
	}
	inline void SuoPoint(){for(Re i=1;i<=n;++i)if(!dfn[i])tarjan(i,i);}
}T1;
int main(){
    while(scanf("%d",&m)&&m){
	    for(Re i=1;i<=Q_o;++i)dcc[i].clear();
	    T1.CL(),Q_o=ans1=n=0,ans2=1;
	    while(m--)in(x),in(y),T1.add(x,y),T1.add(y,x),n=max(n,max(x,y));
	    T1.SuoPoint();
	    for(Re i=1;i<=Q_o;++i){
	    	tmp=0,n=dcc[i].size();
	    	for(Re j=0;j<n;++j)tmp+=cut[dcc[i][j]];
	    	if(!tmp)ans1+=2,ans2*=(n-1)*n/2;
	    	else if(tmp<2)ans1+=1,ans2*=(n-1);
	    }
	    printf("Case %d: %d %lld\n",++T,ans1,ans2);
    }
}
