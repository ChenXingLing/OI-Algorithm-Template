//#pragma GCC optimize(3,"Ofast","inline")
//#pragma GCC optimize(2)
#include<algorithm>
#include<cstdio>
#define Re register int
using std::sort;
const int N=1e5+5,K=2e5+5;
int n,m,k,C[K],ans[N];
struct QAQ{int a,b,c,cnt,ans;}a[N],Q[N];//cnt为副本，ans为严格小于它的点的数量
inline void in(Re &x){
    int fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
inline bool cmp1(QAQ p,QAQ o){return p.a!=o.a?p.a<o.a:(p.b!=o.b?p.b<o.b:p.c<o.c);}
inline bool cmp2(QAQ p,QAQ o){return p.b<o.b;}
inline void add(Re x,Re v){while(x<=k)C[x]+=v,x+=x&-x;}
inline int ask(Re x){
	Re ans=0;
	while(x)ans+=C[x],x-=x&-x;
	return ans;
}
inline void CDQ(Re L,Re R){
	if(L==R)return;
	Re mid=L+R>>1;
	CDQ(L,mid),CDQ(mid+1,R);
	sort(Q+L,Q+mid+1,cmp2),sort(Q+mid+1,Q+R+1,cmp2);
	Re j=L;
	for(Re i=mid+1;i<=R;++i){
		while(j<=mid&&Q[j].b<=Q[i].b)add(Q[j].c,Q[j].cnt),++j;
		Q[i].ans+=ask(Q[i].c);
	}
	for(Re i=L;i<j;++i)add(Q[i].c,-Q[i].cnt);//这里是小于j而不是mid 
}
int main(){
	in(n),in(k);
	for(Re i=1;i<=n;++i)in(a[i].a),in(a[i].b),in(a[i].c);
	sort(a+1,a+n+1,cmp1);
	for(Re i=1;i<=n;++i){
		if(i>2&&a[i].a==a[i-1].a&&a[i].b==a[i-1].b&&a[i].c==a[i-1].c)++Q[m].cnt;
		else Q[++m]=a[i],Q[m].cnt=1;
	}
	CDQ(1,m);
	for(Re i=1;i<=m;++i)ans[Q[i].ans+Q[i].cnt-1]+=Q[i].cnt;
	for(Re i=0;i<n;++i)printf("%d\n",ans[i]);
}
