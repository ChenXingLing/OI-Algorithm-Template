#include<algorithm>
#include<cstring>
#include<cstdio>
#define LD double
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3,M=5e4;
int n,x,T;LD b[N],k[N];char s[20];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline LD y(Re id,Re x){return k[id]*x+b[id];}
struct Segment_Tree{
	#define pl (p<<1)
	#define pr (p<<1|1)
	#define mid ((L+R)>>1)
	int tr[N<<2];
	inline void change(Re p,Re L,Re R,Re id){
		if(y(id,L)>y(tr[p],L)&&y(id,R)>y(tr[p],R)){tr[p]=id;return;}
		if(y(id,L)<=y(tr[p],L)&&y(id,R)<=y(tr[p],R))return;
//		if(L==R){if(y(id,L)>y(tr[p],L))tr[p]=id;return;}
		if(k[tr[p]]<k[id]){
			if(y(id,mid+1)>y(tr[p],mid+1))change(pl,L,mid,tr[p]),tr[p]=id;
			else change(pr,mid+1,R,id);
		}
		else{
			if(y(id,mid)>y(tr[p],mid))change(pr,mid+1,R,tr[p]),tr[p]=id;
			else change(pl,L,mid,id);
		}
	}
	inline LD ask(Re p,Re L,Re R,Re x){
		if(L==R)return y(tr[p],x);
		LD ans=y(tr[p],x);
		if(x<=mid)return max(ans,ask(pl,L,mid,x));
		else return max(ans,ask(pr,mid+1,R,x));
	}
}TR;
int main(){
//	freopen("123.txt","r",stdin);
	in(T);
	while(T--){
		scanf("%s",s);
        if(s[0]=='P')++n,scanf("%lf%lf",&b[n],&k[n]),TR.change(1,1,M,n);
        else in(x),printf("%d\n",(int)(TR.ask(1,1,M,x-1)/100));
	}
}
