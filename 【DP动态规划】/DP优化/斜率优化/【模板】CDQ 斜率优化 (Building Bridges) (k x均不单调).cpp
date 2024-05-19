#include<algorithm>
#include<cstring>
#include<cstdio>
#define LD long double
#define LL long long
#define Re register int
#define S2(a) (1ll*(a)*(a))
using namespace std;
const LL N=1e5+3,inf=1e18;
int n,H[N],W[N],Q[N];LL S[N],dp[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
//dp[i]=min(dp[i],dp[j]+(H[i]-H[j])*(H[i]-H[j])+S[i-1]-S[j]);
//dp[i]=dp[j]-2*H[i]*H[j]+H[j]*H[j]+H[i]*H[i]+S[i-1]-S[j]
//(2*H[i]) * H[j] + (dp[i]-S[i-1]-H[i]*H[i]) = (dp[j]+H[j]*H[j]-S[j])
//   k     *  x   +            b             =          y
#define X(j) (a[j].x)
#define Y(j) (a[j].y)
struct QAQ{
	int k,x,id;LL y;
	inline bool operator<(const QAQ &O)const{return x!=O.x?x<O.x:y<O.y;}
}a[N],b[N];
inline bool cmp(QAQ A,QAQ B){return A.k<B.k;}
inline LD slope(Re i,Re j){return X(i)==X(j)?(Y(j)>Y(i)?inf:-inf):(LD)(Y(j)-Y(i))/(X(j)-X(i));}
inline void CDQ(Re L,Re R){
	if(L==R){Re j=a[L].id;a[L].y=dp[j]+(LL)H[j]*H[j]-S[j];return;}
	Re mid=L+R>>1,p1=L,p2=mid+1,h=1,t=0;
	for(Re i=L;i<=R;++i)a[i].id<=mid?b[p1++]=a[i]:b[p2++]=a[i];
	for(Re i=L;i<=R;++i)a[i]=b[i];
	CDQ(L,mid);
	for(Re i=L;i<=mid;++i){
		while(h<t&&slope(Q[t-1],Q[t])>=slope(Q[t-1],i))--t;
		Q[++t]=i;
	}
	for(Re i=mid+1,j,id;i<=R;++i){
		while(h<t&&slope(Q[h],Q[h+1])<=a[i].k)++h;
		if(h<=t)id=a[i].id,j=Q[h],dp[id]=min(dp[id],a[j].y-(LL)a[i].k*a[j].x+S[id-1]+(LL)H[id]*H[id]);
	}
	CDQ(mid+1,R);
	Re w=L-1;p1=L,p2=mid+1;
	while(p1<=mid&&p2<=R)b[++w]=a[p1]<a[p2]?a[p1++]:a[p2++];
	while(p1<=mid)b[++w]=a[p1++];while(p2<=R)b[++w]=a[p2++];
	for(Re i=L;i<=R;++i)a[i]=b[i];
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n);
	for(Re i=1;i<=n;++i)in(H[i]);
	for(Re i=1;i<=n;++i)in(W[i]);
	for(Re i=1;i<=n;++i)S[i]=S[i-1]+W[i],dp[i]=inf;
	for(Re i=1;i<=n;++i)a[i].k=(H[i]<<1),a[i].x=H[i],a[i].id=i;
	sort(a+1,a+n+1,cmp);
	dp[1]=0,CDQ(1,n);
	printf("%lld\n",dp[n]);
}
