#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")
#include<algorithm>
#include<cstring>
#include<cstdio>
#define mid (L+R>>1)
#define Re register int
#define pl tree[p].lp
#define pr tree[p].rp
#define F(i,a,b) for(Re i=a;i<=b;++i)
#define lo(o) lower_bound(b+1,b+m+1,o)-b
using namespace std;
const int N=1e5+3,inf=2147483647;
int m,T,t,fu,cnt,root,a[N],b[N],Q[N],opt[N]; 
struct QAQ{int g,lp,rp;}tree[N<<1];
inline void in(Re &x){
    x=fu=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
inline int ask_kth(Re p,Re L,Re R,Re k){
	if(L==R)return b[R];
    Re tmp=tree[pl].g;
    if(tmp>=k)return ask_kth(pl,L,mid,k);
    else return ask_kth(pr,mid+1,R,k-tmp);
}
inline void add(Re &p,Re L,Re R,Re w,Re v){
    if(!p)p=++cnt;tree[p].g+=v;
    if(L==R)return;
    if(w<=mid)add(pl,L,mid,w,v);
    else add(pr,mid+1,R,w,v);
}
inline int ask_level(Re p,Re L,Re R,Re x){
	if(!x)return 0;//注意这个地方特判一下，因为有可能会查询第0大，直接返回 
	if(L==R)return tree[p].g;
	if(x<=mid)return ask_level(pl,L,mid,x);
	else return tree[pl].g+ask_level(pr,mid+1,R,x);
}
int main(){
	in(T); 
    F(i,1,T){
    	in(opt[i]),in(Q[i]);
    	if(opt[i]!=4)b[++m]=Q[i];
    }
    sort(b+1,b+m+1),m=unique(b+1,b+m+1)-b-1;
    F(i,1,T){
    	if(opt[i]==1)add(root,1,m,lo(Q[i]),1);
    	if(opt[i]==2)add(root,1,m,lo(Q[i]),-1);
		if(opt[i]==3)printf("%d\n",ask_level(root,1,m,lo(Q[i])-1)+1);
		if(opt[i]==4)printf("%d\n",ask_kth(root,1,m,Q[i]));
		if(opt[i]==5){
			Re level=ask_level(root,1,m,lo(Q[i])-1);
			printf("%d\n",ask_kth(root,1,m,level));
		}
		if(opt[i]==6){
			Re level=ask_level(root,1,m,lo(Q[i]));
			printf("%d\n",ask_kth(root,1,m,level+1));
		}
    }
}
