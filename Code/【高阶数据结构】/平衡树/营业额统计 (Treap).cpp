#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<algorithm> 
#include<cstdlib> 
#include<cstdio>
#include<ctime>
#define Re register int
#define pl tr[p].lp
#define pr tr[p].rp
#define pv tr[p].v
using namespace std;
const int N=32780,inf=2e9;
int a,o,T,ans,root;
inline void in(Re &x){
    int fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
struct Treap{int v,rd,lp,rp,cnt,size;}tr[N];
inline void pushup(Re p){tr[p].size=tr[p].cnt+tr[pl].size+tr[pr].size;}
inline void lturn(Re &p){
	Re q=pr;pr=tr[q].lp,tr[q].lp=p;
	pushup(p),pushup(p=q);
}
inline void rturn(Re &p){
	Re q=pl;pl=tr[q].rp,tr[q].rp=p;
	pushup(p),pushup(p=q);
}
inline void insert(Re &p,Re x){
	if(!p){tr[p=++o].v=x,tr[p].cnt=tr[p].size=1,tr[p].rd=rand();return;}
	++tr[p].size;
	if(x==pv)++tr[p].cnt;
	else if(x<pv){
		insert(pl,x);
		if(tr[pl].rd<tr[p].rd)rturn(p);
	}
	else{
		insert(pr,x);
		if(tr[pr].rd<tr[p].rd)lturn(p);
	}
}
inline int ask_pri(Re p,Re x){
	if(!p)return -inf;
	if(x==pv)return x;
	else if(x<pv)return ask_pri(pl,x);
	else return max(pv,ask_pri(pr,x));
}
inline int ask_nex(Re p,Re x){
	if(!p)return inf;
	if(x==pv)return x;
	else if(x>pv)return ask_nex(pr,x);
	else return min(pv,ask_nex(pl,x));
}
int main(){
	srand((int)time(NULL));
	in(T);--T;in(a);ans=a;insert(root,a);
	while(T--){
		in(a);
		ans+=min(abs(a-ask_pri(root,a)),abs(a-ask_nex(root,a)));
		insert(root,a);
	}
	printf("%d",ans);
}
