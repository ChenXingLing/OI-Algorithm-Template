#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define Re register int
#define LL long long
using namespace std;
const int N=524288+3,P=998244353,G=3;
int n,m,ans,invG,a[N],b[N],f[N],g[N],tr[N],PA[N];char A[N],B[N];
inline void in(Re &x){
    int fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
inline int mi(Re x,Re k){
	Re s=1;
	while(k){
		if(k&1)s=(LL)s*x%P;
		x=(LL)x*x%P,k>>=1;
	}
	return s;
}
inline int inv(Re x){return mi(x,P-2);}
inline void NTT(Re *f,Re n,Re op){
	for(Re i=0;i<n;++i)if(i<tr[i])swap(f[i],f[tr[i]]);
	for(Re p=2;p<=n;p<<=1){
		Re len=p>>1,w1=mi(op?invG:G,(P-1)/p);
		for(Re st=0;st<n;st+=p)
			for(Re j=st,base=1;j<=st+len-1;++j){
				Re tmp=(LL)base*f[j+len]%P;
				f[j+len]=(f[j]-tmp+P)%P,(f[j]+=tmp)%=P;
				base=(LL)base*w1%P;
			}
	}
}
inline void sakura(Re *f,Re n,Re *g,Re m){
	for(m=n+1,n=1;n<=m;n<<=1);Re invn=inv(n);//循环卷积优化
	for(Re i=1;i<n;++i)tr[i]=(tr[i>>1]>>1)|((i&1)?n>>1:0);
	NTT(f,n,0),NTT(g,n,0);
	for(Re i=0;i<n;++i)f[i]=(LL)f[i]*g[i]%P;
	NTT(f,n,1);
	for(Re i=0;i<=m;++i)f[i]=(LL)f[i]*invn%P;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(m),in(n),scanf("%s%s",B+1,A+1),invG=inv(G);
	for(Re i=1;i<=n/2;++i)swap(A[i],A[n-i+1]);
	for(Re i=1;i<=n;++i)a[i]=(A[i]=='*'?0:A[i]-'a'+1);
	for(Re i=1;i<=m;++i)b[i]=(B[i]=='*'?0:B[i]-'a'+1);
	for(Re i=1;i<=n;++i)f[i]=(LL)a[i]*a[i]%P*a[i]%P;
	for(Re i=1;i<=m;++i)g[i]=b[i];
	sakura(f,n,g,m);
	for(Re i=m;i<=n;++i)(PA[n-i+1]+=f[i+1])%=P;
	memset(f,0,sizeof(f)),memset(g,0,sizeof(g));
	for(Re i=1;i<=n;++i)f[i]=a[i];
	for(Re i=1;i<=m;++i)g[i]=(LL)b[i]*b[i]%P*b[i]%P;
	sakura(f,n,g,m);
	for(Re i=m;i<=n;++i)(PA[n-i+1]+=f[i+1])%=P;
	memset(f,0,sizeof(f)),memset(g,0,sizeof(g));
	for(Re i=1;i<=n;++i)f[i]=(LL)a[i]*a[i]%P;
	for(Re i=1;i<=m;++i)g[i]=(LL)b[i]*b[i]%P;
	sakura(f,n,g,m);
	for(Re i=m;i<=n;++i)(PA[n-i+1]+=P-2*f[i+1]%P)%=P;
	Re ans=0;
	for(Re i=1;i<=n-m+1;++i)ans+=(PA[i]==0);
	printf("%d\n",ans);
	for(Re i=1;i<=n-m+1;++i)if(PA[i]==0)printf("%d ",i);
}
