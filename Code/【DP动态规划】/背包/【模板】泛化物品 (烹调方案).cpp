// luogu-judger-enable-o2
#include<algorithm>
#include<cstring>
#include<cstdio>
#define lg long long
lg ans,T,n,i,j,f[100010];
struct QAQ{lg a,b,v;}Q[55];
inline bool cmp(const QAQ &a,const QAQ &b){return a.v*b.b<b.v*a.b;}
int main(){
	scanf("%lld%lld",&T,&n);
	for(i=1;i<=n;i++)scanf("%lld",&Q[i].a);
	for(i=1;i<=n;i++)scanf("%lld",&Q[i].b);
	for(i=1;i<=n;i++)scanf("%lld",&Q[i].v);
	std::sort(Q+1,Q+n+1,cmp);
	for(i=1;i<=n;i++)
		for(j=T;j>=Q[i].v;j--)
			f[j]=std::max(f[j],f[j-Q[i].v]+Q[i].a-j*Q[i].b);
	for(i=0;i<=T;i++)ans=std::max(ans,f[i]);
	printf("%lld",ans);
	return 0;
}
