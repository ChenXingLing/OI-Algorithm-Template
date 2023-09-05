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
const int N=1e5+5,inf=2e9;
int a,b,o,T,root;
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
inline void del(Re &p,Re x){
	if(!p)return;
    if(x<pv)--tr[p].size,del(pl,x);
	else if(x>pv)--tr[p].size,del(pr,x);
	else{
		if(tr[p].cnt>1)--tr[p].cnt,--tr[p].size;
		else{
			if(pl*pr==0)p=pl+pr;
			else if(tr[pl].rd<tr[pr].rd)rturn(p),del(p,x);
			else lturn(p),del(p,x);
		}
	}
}
inline int ask_level(Re p,Re x){ 
	if(x==pv)return tr[pl].size+1;
	else return x<pv?ask_level(pl,x):tr[p].cnt+tr[pl].size+ask_level(pr,x);
}
inline int ask_v(Re p,Re x){
	if(x<=tr[pl].size)return ask_v(pl,x);
	else{
		Re tmp=tr[pl].size+tr[p].cnt;
		return x<=tmp?pv:ask_v(pr,x-tmp);
	}
}
inline int ask_pri(Re p,Re x){
	if(!p)return -inf;
	if(x<=pv)return ask_pri(pl,x);
	else return max(pv,ask_pri(pr,x));
}
inline int ask_nex(Re p,Re x){
	if(!p)return inf;
	if(x>=pv)return ask_nex(pr,x);
	else return min(pv,ask_nex(pl,x));
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return ;
}
int main(){
	srand((int)time(NULL));
	in(T);
	while(T--){
		in(a),in(b);
		if(a==1)insert(root,b);
		if(a==2)del(root,b);
		if(a==3)write(ask_level(root,b)),puts("");
		if(a==4)write(ask_v(root,b)),puts("");
		if(a==5)write(ask_pri(root,b)),puts(""); 
		if(a==6)write(ask_nex(root,b)),puts("");
	}
}
