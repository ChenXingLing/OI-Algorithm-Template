#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define Re register int
using namespace std;
const int N=2e5+3;char opt[N];
int x,y,z,w,n,T,op,A[N],rk[N];
inline void in(int &x){
    Re fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
int pt[N<<1];
struct Segment_Tree{
	#define pl tr[p].lp
	#define pr tr[p].rp
	#define mid ((L+R)>>1)
	int O;queue<int>Q;
	struct QAQ{int S,lp,rp;}tr[N*200];
	inline int New(){//新建节点
		if(Q.empty())return ++O;
		Re tmp=Q.front();Q.pop();
		return tmp;
	}
	inline void del(Re &p){pl=pr=0,Q.push(p),p=0;}//回收垃圾(注意取地址符并初始化为1)
	inline void change(Re &p,Re L,Re R,Re w,Re v){
	    if(!p)p=New();tr[p].S+=v;
	    if(L==R){if(!tr[p].S)del(p);return;}
	    if(w<=mid)change(pl,L,mid,w,v);
	    else change(pr,mid+1,R,w,v);
	    if(!tr[p].S)del(p);
	}
	inline int ask(Re p,Re L,Re R,Re l,Re r){
		if(!p)return 0;
		if(l<=L&&R<=r)return tr[p].S;
		Re ans=0;
		if(l<=mid)ans+=ask(pl,L,mid,l,r);
		if(r>mid)ans+=ask(pr,mid+1,R,l,r);
		return ans;
	}
}TR;
inline int ask(Re L,Re R,Re l,Re r){
    Re ans=0;
    for(Re i=R;i;i-=i&-i)ans+=TR.ask(pt[i],1,n,l,r);
    for(Re i=L-1;i;i-=i&-i)ans-=TR.ask(pt[i],1,n,l,r);
    return ans;
}
inline void add(Re x,Re w,Re v){
    for(Re i=x;i<=n;i+=i&-i)TR.change(pt[i],1,n,w,v);
}
int main(){
//	freopen("123.txt","r",stdin);
    in(n),in(T);
	for(Re i=1;i<=n;++i)in(x),rk[x]=i;
	for(Re i=1;i<=n;++i)in(A[i]),A[i]=rk[A[i]],add(i,A[i],1);
    while(T--){
    	in(op),in(x),in(y);
    	if(op>1)add(x,A[x],-1),add(y,A[y],-1),swap(A[x],A[y]),add(x,A[x],1),add(y,A[y],1);
    	else in(z),in(w),printf("%d\n",ask(z,w,x,y));
	}
}
