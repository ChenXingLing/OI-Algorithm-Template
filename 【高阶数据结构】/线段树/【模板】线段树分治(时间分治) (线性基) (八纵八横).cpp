#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<bitset>
#include<stack>
#define LL long long
#define Re register int
#define Int bitset<M>
using namespace std;
const int N=550+5,M=1000+5;
int n,m,x,y,o,O,T,logN,X[N],Y[N],fa[N],last[N],head[N];Int z,Z[N],dis[N],Ans[M];char op[20];
struct QAQ{int to,next;Int w;}a[N<<1];
inline void add(Re x,Re y,Int z){a[++o].to=y,a[o].w=z,a[o].next=head[x],head[x]=o;}
inline int find(Re x){return x==fa[x]?x:fa[x]=find(fa[x]);}
inline int getlen(Int &x){Re n=1000;while(n>=1&&!x[n])--n;return n;}
inline void print(Int &x){for(Re i=getlen(x);i>=0;--i)putchar(x[i]+'0');puts("");}
inline void in(Int &x){cin>>x,logN=max(logN,getlen(x));}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Line_JI{
	Int p[M];bool pp[M];stack<int>Q;
	inline void insert(Int x){
		for(Re i=logN;i>=0;--i)
			if(x[i]){
				if(!pp[i]){Q.push(i),p[i]=x,pp[i]=1;break;}
				x^=p[i];
			}
	}
	inline Int ask(){
		Int ans;ans.reset();
		for(Re i=logN;i>=0;--i)if(pp[i]&&(!ans[i]))ans^=p[i];
		return ans;
	}
	inline void back(Re to){
		while(Q.size()>to)x=Q.top(),Q.pop(),p[x].reset(),pp[x]=0;
	}
}JI;
struct Segment_Tree{
	int o,head[M<<2];
	struct QAQ{int x,y,next;Int w;}a[(N+M)*10];
	inline void add(Re t,Re x,Re y,Int &z){a[++o].x=x,a[o].y=y,a[o].w=z,a[o].next=head[t],head[t]=o;}
	#define pl (p<<1)
	#define pr (p<<1|1)
	#define mid ((L+R)>>1)
	inline void change(Re p,Re L,Re R,Re l,Re r,Re x,Re y,Int &z){
		if(l<=L&&R<=r){add(p,x,y,z);return;}
		if(l<=mid)change(pl,L,mid,l,r,x,y,z);
		if(r>mid)change(pr,mid+1,R,l,r,x,y,z);
	}
	inline void dfs(Re p,Re L,Re R){
		Re tmp=JI.Q.size();
		for(Re i=head[p];i;i=a[i].next)JI.insert(dis[a[i].x]^dis[a[i].y]^a[i].w);
		if(L==R)Ans[L]=JI.ask();//这里还没调用back进行撤回,不能return啊!!!
		else dfs(pl,L,mid),dfs(pr,mid+1,R);
		JI.back(tmp);
	}
}TR;
inline void dfs(Re x,Re fa,Re w){
	dis[x]=dis[fa]^a[w].w;
	for(Re i=head[x];i;i=a[i].next)
		if(a[i].to!=fa)dfs(a[i].to,x,i);
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(m),in(T),++T;
	for(Re i=1;i<=n;++i)fa[i]=i;
	while(m--){
		in(x),in(y),in(z);
		if(find(x)!=find(y))add(x,y,z),add(y,x,z),fa[find(x)]=find(y);
		else TR.change(1,1,T,1,T,x,y,z);
	}
	for(Re i=2;i<=T;++i){
		scanf("%s",op);
		if(op[0]=='A')last[++O]=i,in(X[O]),in(Y[O]),in(Z[O]);
		else if(op[1]=='h'){
			in(x),in(z);
			TR.change(1,1,T,last[x],i-1,X[x],Y[x],Z[x]);
			last[x]=i,Z[x]=z;
		}
		else in(x),TR.change(1,1,T,last[x],i-1,X[x],Y[x],Z[x]),last[x]=0;
	}
	for(Re i=1;i<=O;++i)if(last[i])TR.change(1,1,T,last[i],T,X[i],Y[i],Z[i]);
	dfs(1,0,0),TR.dfs(1,1,T);
	for(Re i=1;i<=T;++i)print(Ans[i]);
}
