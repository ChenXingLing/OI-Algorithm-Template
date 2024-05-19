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
int x,y,z,n,m,T,t,fu,cnt,tl,tr,a[N],b[N],pt[N],C[N],opt[N],ptl[20],ptr[20]; 
struct QAQ{int g,lp,rp;}tree[N*250];
struct O_O{int l,r,k;}Q[N];
struct T_T{int i,x;}c[N];
inline void in(Re &x){
    x=fu=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
inline int ask_kth(Re L,Re R,Re k){
    if(L==R)return b[R];
    Re tmp=0;
    F(i,1,tl)tmp-=tree[tree[ptl[i]].lp].g;
    F(i,1,tr)tmp+=tree[tree[ptr[i]].lp].g;
    if(tmp>=k){
    	F(i,1,tl)ptl[i]=tree[ptl[i]].lp;
    	F(i,1,tr)ptr[i]=tree[ptr[i]].lp;
    	return ask_kth(L,mid,k);
    }
    else{
    	F(i,1,tl)ptl[i]=tree[ptl[i]].rp;
    	F(i,1,tr)ptr[i]=tree[ptr[i]].rp;
    	return ask_kth(mid+1,R,k-tmp);
    }
}
inline int ask_kth_pre(Re L,Re R,Re k){
    tl=tr=0;
    for(Re i=L-1;i;i-=i&-i)ptl[++tl]=pt[i];
    for(Re i=R;i;i-=i&-i)ptr[++tr]=pt[i];
    return ask_kth(1,m,k);
}
inline void add(Re &p,Re L,Re R,Re w,Re v){
    if(!p)p=++cnt;tree[p].g+=v;
    if(L==R)return;
    if(w<=mid)add(pl,L,mid,w,v);
    else add(pr,mid+1,R,w,v);
}
inline void add_pre(Re x,Re v){
    Re w=lo(a[x]); 
    for(Re i=x;i<=n;i+=i&-i)add(pt[i],1,m,w,v);
}
inline int ask_level(Re p,Re L,Re R,Re x){
	if(L==R)return tree[p].g; 
	if(x<=mid)return ask_level(pl,L,mid,x);
	else return tree[pl].g+ask_level(pr,mid+1,R,x);
}
inline int ask_level_pre(Re L,Re R,Re w){
	Re ans=0;
    for(Re i=R;i;i-=i&-i)ans+=ask_level(pt[i],1,m,w);
    for(Re i=L-1;i;i-=i&-i)ans-=ask_level(pt[i],1,m,w);
    return ans;
}
int main(){
	in(n),in(T),m=n;
    F(i,1,n)in(a[i]),b[i]=a[i];
    F(i,1,T){
    	in(opt[i]);
    	if(opt[i]==3)in(c[i].i),in(c[i].x),b[++m]=c[i].x;
    	else{
    		in(Q[i].l),in(Q[i].r),in(Q[i].k);
    		if(opt[i]!=2)b[++m]=Q[i].k;
		}
    }
    sort(b+1,b+m+1),m=unique(b+1,b+m+1)-b-1;
    F(i,1,n)add_pre(i,1);
    F(i,1,T){
    	if(opt[i]==1)Q[i].k=lo(Q[i].k),printf("%d\n",ask_level_pre(Q[i].l,Q[i].r,Q[i].k-1)+1);
    	if(opt[i]==2)printf("%d\n",ask_kth_pre(Q[i].l,Q[i].r,Q[i].k));
		if(opt[i]==3)add_pre(c[i].i,-1),a[c[i].i]=c[i].x,add_pre(c[i].i,1);
		if(opt[i]==4){
			Re level=ask_level_pre(Q[i].l,Q[i].r,lo(Q[i].k)-1);
			if(!level)printf("%d\n",-inf);
			else printf("%d\n",ask_kth_pre(Q[i].l,Q[i].r,level));
		}
		if(opt[i]==5){
			Re level=ask_level_pre(Q[i].l,Q[i].r,lo(Q[i].k));
			if(level==Q[i].r-Q[i].l+1)printf("%d\n",inf);
			else printf("%d\n",ask_kth_pre(Q[i].l,Q[i].r,level+1));
		}
    }
}
