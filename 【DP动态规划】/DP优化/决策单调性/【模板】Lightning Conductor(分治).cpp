#include<algorithm>
#include<cstdio>
#include<cmath>
#define Re register int
using namespace std;
const int N=5e5+3;
int i,j,n,h,t,a[N],Q[N],Poi[N];
double tmp,p[N],sqr[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void sakura(Re l,Re r,Re L,Re R){
	if(l>r)return;
	Re mid=l+r>>1,j0;double mx=0;
	for(Re j=L;j<=mid&&j<=R;++j)
//暴力找p[i]的最优决策点j0，而其决策点j必须满足j<=i，即此处的j<=mid 
		if((tmp=a[j]+sqr[mid-j])>mx)mx=tmp,j0=j;
	p[mid]=max(p[mid],mx);
	sakura(l,mid-1,L,j0),sakura(mid+1,r,j0,R);
}
int main(){
    in(n);
    for(Re i=1;i<=n;++i)in(a[i]),sqr[i]=sqrt(i);
    sakura(1,n,1,n);
    for(Re i=1;i<n-i+1;++i)swap(a[i],a[n-i+1]),swap(p[i],p[n-i+1]);
    sakura(1,n,1,n);
    for(Re i=n;i;--i)printf("%d\n",(int)ceil(p[i])-a[i]);
}
