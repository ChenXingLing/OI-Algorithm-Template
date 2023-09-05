#include<algorithm>
#include<cstring>
#include<cstdio>
#include<stack>
#include<map>
#define LL long long
#define Re register int
#define mp make_pair
using namespace std;
const int N=2e5+3,logN=30;
int x,y,n,m,T,op,X[N],Y[N],OP[N];LL Ans[N];map<pair<int,int>,int>last,z;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Union{//冰茶姬
	struct BK{int x,y,dx,dy,sx,sy;BK(Re X=0,Re d1=0,Re S1=0,Re Y=0,Re d2=0,Re S2=0){x=X,y=Y,sx=S1,sy=S2,dx=d1,dy=d2;}};
	int fa[N],dis[N],size[N];stack<BK>Q;
	inline int find(Re x){return fa[x]==x?x:find(fa[x]);}
	inline int Dis(Re x){return fa[x]==x?0:dis[x]^Dis(fa[x]);}
	inline void merge(Re x,Re y,Re w){//按秩合并
		if(size[x]>size[y])swap(x,y);
		Q.push(BK(x,dis[x],size[x],y,dis[y],size[y]));
		fa[x]=y,dis[x]=w,size[y]+=size[x];
	}
	inline void back(Re to){//撤销操作
		while(int(Q.size())>to){
			BK a=Q.top();Re x=a.x,y=a.y;Q.pop();
			fa[x]=x,dis[x]=a.dx,size[x]=a.sx;
			fa[y]=y,dis[y]=a.dy,size[y]=a.sy;
		}
	}
}TF;
struct Line_JI{
	int p[31];stack<int>Q;
	inline void insert(Re x){
		for(Re i=logN;i>=0;--i)
			if((x>>i)&1){
				if(!p[i]){p[i]=x,Q.push(i);break;}
				x^=p[i];
			}
	}
	inline int ask(Re x){for(Re i=logN;i>=0;--i)if(p[i])x=min(x,x^p[i]);return x;}
	inline void back(Re to){
		while(int(Q.size())>to)p[Q.top()]=0,Q.pop();
	}
}JI;
int o,head[N<<2];
struct QAQ{int x,y,w,next;}a[N*50];
inline void add(Re x,Re y1,Re y2,Re w){a[++o].w=w,a[o].x=y1,a[o].y=y2,a[o].next=head[x],head[x]=o;}
struct Segment_Tree{
	#define pl (p<<1)
	#define pr (p<<1|1)
	#define mid ((L+R)>>1)
	inline void change(Re p,Re L,Re R,Re l,Re r,Re x,Re y,Re v){
		if(l>r)return;
		if(l<=L&&R<=r){add(p,x,y,v);return;}
		if(l<=mid)change(pl,L,mid,l,r,x,y,v);
		if(r>mid)change(pr,mid+1,R,l,r,x,y,v);
	}
	inline void dfs(Re p,Re L,Re R){
		Re tmp1=TF.Q.size(),tmp2=JI.Q.size();
		for(Re i=head[p];i;i=a[i].next){
			Re x=TF.find(a[i].x),y=TF.find(a[i].y),w=TF.Dis(a[i].x)^TF.Dis(a[i].y)^a[i].w;
			if(x!=y)TF.merge(x,y,w);
			else JI.insert(w);
		}
		if(L==R){if(OP[L])Ans[L]=JI.ask(TF.Dis(X[L])^TF.Dis(Y[L]));}
		else dfs(pl,L,mid),dfs(pr,mid+1,R);
		TF.back(tmp1),JI.back(tmp2);//回退
	}
}T1;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(m);
	for(Re i=1;i<=n;++i)TF.fa[i]=i,TF.size[i]=1;
	for(Re i=1;i<=m;++i){
		in(x),in(y);if(x>y)swap(x,y);
		in(z[mp(x,y)]),last[mp(x,y)]=1;
	}
	in(T);
	for(Re i=1;i<=T;++i){
		in(op),in(x),in(y);if(x>y)swap(x,y);
		if(op<2)in(z[mp(x,y)]),last[mp(x,y)]=i;
		else if(op<3)T1.change(1,1,T,last[mp(x,y)],i-1,x,y,z[mp(x,y)]),last.erase(last.find(mp(x,y)));
		else OP[i]=1,X[i]=x,Y[i]=y;
	}
	for(map<pair<int,int>,int>::iterator it=last.begin();it!=last.end();++it)
		T1.change(1,1,T,it->second,T,it->first.first,it->first.second,z[it->first]);
	T1.dfs(1,1,T);
	for(Re i=1;i<=T;++i)if(OP[i])printf("%lld\n",Ans[i]);
}
