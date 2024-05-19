#include<algorithm>
#include<cstring>
#include<cstdio>
#include<stack>
#include<map>
#define LL long long
#define Re register int
#define mp(x,y) make_pair(x,y)
using namespace std;
const int N=1e4+3,M=2e5+3;
int x,y,n,T,Ans[M];char ch[20];
map<pair<int,int>,int>last;
struct Query{int x,y,op;}Q[M];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Union{//冰茶姬
	struct BK{int x,y,sizex,sizey;BK(Re X=0,Re S1=0,Re Y=0,Re S2=0){x=X,y=Y,sizex=S1,sizey=S2;}};
	int fa[N],size[N];stack<BK>Q;
	inline int find(Re x){return fa[x]==x?x:find(fa[x]);}
	inline void merge(Re x,Re y){//按秩合并
		x=find(x),y=find(y);
		if(size[x]>size[y])swap(x,y);
		Q.push(BK(x,size[x],y,size[y]));
		fa[x]=y,size[y]+=size[x];
	}
	inline void back(Re to){//撤销操作
		while(Q.size()>to){
			BK a=Q.top();Q.pop();
			fa[a.x]=a.x,size[a.x]=a.sizex;
			fa[a.y]=a.y,size[a.y]=a.sizey;
		}
	}
}TF;
int o,head[M<<2];
struct QAQ{int x,y,next;}a[M*20];
inline void add(Re x,Re y1,Re y2){a[++o].x=y1,a[o].y=y2,a[o].next=head[x],head[x]=o;}
struct Segment_Tree{
	#define pl (p<<1)
	#define pr (p<<1|1)
	#define mid (L+R>>1)
	inline void change(Re p,Re L,Re R,Re l,Re r,Re x,Re y){
		if(l<=L&&R<=r){add(p,x,y);return;}
		if(l<=mid)change(pl,L,mid,l,r,x,y);
		if(r>mid)change(pr,mid+1,R,l,r,x,y);
	}
	inline void dfs(Re p,Re L,Re R){
		Re tmp=TF.Q.size();
		for(Re i=head[p];i;i=a[i].next)TF.merge(a[i].x,a[i].y);
		if(L==R){if(Q[L].op)Ans[L]=(TF.find(Q[L].x)==TF.find(Q[L].y));}
		else dfs(pl,L,mid),dfs(pr,mid+1,R);
		TF.back(tmp);//回退
	}
}T1;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T);
	for(Re i=1;i<=n;++i)TF.fa[i]=i,TF.size[i]=1;
	for(Re i=1;i<=T;++i){
		scanf("%s",ch),in(x),in(y);if(x>y)swap(x,y);
		if(ch[0]=='Q')Q[i].op=1,Q[i].x=x,Q[i].y=y;
		else if(ch[0]=='C')last[mp(x,y)]=i;
		else T1.change(1,1,T,last[mp(x,y)],i,x,y),last.erase(mp(x,y));
	}
	for(map<pair<int,int>,int>::iterator it=last.begin();it!=last.end();++it)
		T1.change(1,1,T,it->second,T,it->first.first,it->first.second);
	T1.dfs(1,1,T);
	for(Re i=1;i<=T;++i)if(Q[i].op)puts(Ans[i]?"Yes":"No");
}
