#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define LD long double
#define Re register int
using namespace std;
const LL N=1e5+3,inf=1e18;
const LD eps=1e-20;
inline int dcmp(LD a){return a<-eps?-1:(a>eps?1:0);}
int n,h,t,Q[N];LD S,A[N],B[N],Ra[N],f[N],dp[N];
inline void in(Re &x){
    int dp=0;x=0;char c=getchar();
    while(c<'0'||c>'9')dp|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=dp?-x:x;
}
inline void in(LD &X){
	X=0;LD Y=1.0;int dp=0;char c=getchar();
	while(c<'0'||c>'9')dp|=c=='-',c=getchar(); 
	while(c>='0'&&c<='9')X=X*10+(c^48),c=getchar(); 
	if(c=='.'){c=getchar();while(c>='0'&&c<='9')X+=(Y/=10)*(c^48),c=getchar();}
	X=dp?-X:X;
}
//dp[i]=max((B[i]/A[i])*f[j]+Ra[j]*f[j]),f[i]=dp[i]/(A[i]*Ra[i]+B[i])
//(B[i]/A[i])*f[j]+(-dp[i])=(-Ra[j]*f[j])
//     k     * x  +   b    =     y
#define X(i) (a[i].x)
#define Y(i) (a[i].y)
struct QAQ{
	LD k,x,y;int id;
	inline bool operator<(const QAQ &O)const{return dcmp(x-O.x)?x<O.x:y<O.y;}
}a[N],b[N];
inline bool cmp(QAQ A,QAQ B){return dcmp(A.k-B.k)<0;}
inline LD slope(Re i,Re j){return X(i)==X(j)?(Y(j)>Y(i)?inf:-inf):(Y(j)-Y(i))/(X(j)-X(i));}
inline void CDQ(Re L,Re R){
	if(L==R){
		Re j=a[L].id;
//		printf("getdp(%d), dp=%.3Lf\n",j,dp[j]);
		if(j>1)dp[j]=max(dp[j-1],A[j]*dp[j]),f[j]=dp[j]/(A[j]*Ra[j]+B[j]);
		a[L].x=f[j],a[L].y=-Ra[j]*f[j];
//		printf("k=%.3Lf, x=%.3Lf, y=%.3Lf\n",a[L].k,a[L].x,a[L].y);
		return;
	}
	Re mid=(L+R)>>1,p1=L,p2=mid+1,h=1,t=0;
	for(Re i=L;i<=R;++i)a[i].id<=mid?b[p1++]=a[i]:b[p2++]=a[i];
	for(Re i=L;i<=R;++i)a[i]=b[i];
	CDQ(L,mid);
	for(Re i=L;i<=mid;++i){
		while(h<t&&slope(Q[t-1],Q[t])>=slope(Q[t-1],i))--t;
		Q[++t]=i;
	}
	for(Re i=mid+1,j,id;i<=R;++i){
		while(h<t&&slope(Q[h],Q[h+1])<=a[i].k)++h;
		if(h<=t)id=a[i].id,j=Q[h],dp[id]=max(dp[id],-(a[j].y-a[i].k*a[j].x));
	}
	CDQ(mid+1,R);Re p=L-1;p1=L,p2=mid+1;
	while(p1<=mid&&p2<=R)b[++p]=a[p1]<a[p2]?a[p1++]:a[p2++];
	while(p1<=mid)b[++p]=a[p1++];while(p2<=R)b[++p]=a[p2++];
	for(Re i=L;i<=R;++i)a[i]=b[i];
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(S);
	for(Re i=1;i<=n;++i)in(A[i]),in(B[i]),in(Ra[i]),dp[i]=-inf;
	for(Re i=1;i<=n;++i)a[i].k=B[i]/A[i],a[i].id=i;
	f[1]=(dp[1]=S)/(A[1]*Ra[1]+B[1]);
//	for(Re i=2;i<=n;++i){
//		for(Re j=1;j<i;++j)dp[i]=max(dp[i],f[j]*Ra[j]+f[j]*B[i]/A[i]);
//		dp[i]=max(dp[i-1],A[i]*dp[i]),f[i]=dp[i]/(A[i]*Ra[i]+B[i]);
//	}
	sort(a+1,a+n+1,cmp),CDQ(1,n);
	printf("%.3Lf",dp[n]);
}
