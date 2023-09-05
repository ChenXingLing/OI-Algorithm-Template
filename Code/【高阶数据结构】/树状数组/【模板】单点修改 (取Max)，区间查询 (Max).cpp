#include<cstdio>
#define Re register int
const int N=2e5+3;
int n,l,r,T,A[N],C[N];char op;
inline void in(Re &x){
    Re f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;
}
inline int max(Re a,Re b){return a>b?a:b;}
struct BIT{
    int C[N];
    inline void add(Re x,Re v){while(x<=n)C[x]=max(C[x],v),x+=x&-x;}
    inline int ask(Re l,Re r){
        Re ans=0;
        while(l<=r){
            while(r-(r&-r)>=l)ans=max(ans,C[r]),r-=r&-r;
            ans=max(ans,A[r--]);
        }
        return ans;
    }
}TR;
int main(){
    in(n),in(T);
    for(Re i=1;i<=n;i++)in(A[i]),TR.add(i,A[i]);
    while(T--){
    	scanf(" %c",&op),in(l),in(r);
    	if(op=='Q')printf("%d\n",TR.ask(l,r));
    	else A[l]=max(r,A[l]),TR.add(l,r);
	}
}
