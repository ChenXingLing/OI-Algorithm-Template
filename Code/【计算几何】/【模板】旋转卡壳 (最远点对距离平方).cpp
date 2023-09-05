#include<algorithm>
#include<cstdio>
#include<cmath>
#define LD double
#define LL long long
#define Vector Point
#define Rd register LD
#define Re register int
using namespace std;
const int N=50003;
const LD eps=1e-8;
inline int dcmp(Rd a){return a<-eps?-1:(a>eps?1:0);}
struct Point{
    LD x,y;Point(LD X=0,LD Y=0){x=X,y=Y;}
    inline void in(){scanf("%lf%lf",&x,&y);}
}cp[N],Poi[N];
inline LD Dot(Vector a,Vector b){return a.x*b.x+a.y*b.y;}
inline LD Cro(Vector a,Vector b){return a.x*b.y-a.y*b.x;}
inline LD Len(Vector a){return Dot(a,a);}//题意求距离平方，这里不需要加sqrt了 
inline Vector operator-(Point a,Point b){return Vector(a.x-b.x,a.y-b.y);}
inline bool cmp(Point a,Point b){return a.x!=b.x?a.x<b.x:a.y<b.y;}
inline int ConvexHull(Point *P,Re n,Point *cp){
	sort(P+1,P+n+1,cmp);
	Re t=0;
	for(Re i=1;i<=n;++i){
		while(t>1&&dcmp(Cro(cp[t]-cp[t-1],P[i]-cp[t-1]))<=0)--t;
		cp[++t]=P[i];
	}
	Re St=t;
	for(Re i=n-1;i>=1;--i){
		while(t>St&&dcmp(Cro(cp[t]-cp[t-1],P[i]-cp[t-1]))<=0)--t;
		cp[++t]=P[i];
	}
	return --t;
}
int n;
int main(){
//	freopen("123.txt","r",stdin);
	scanf("%d",&n);
	for(Re i=1;i<=n;++i)Poi[i].in();
	Re cnt=ConvexHull(Poi,n,cp);
	Rd Ans=Len(cp[2]-cp[1]);
	for(Re i=1,j=3;i<=cnt;++i){
		while(dcmp(Cro(cp[i+1]-cp[i],cp[j]-cp[i])-Cro(cp[i+1]-cp[i],cp[j+1]-cp[i]))<0)j=j<cnt?j+1:1;//注意是<0，如果写<=0的话可能会被两个点的数据卡掉
		Ans=max(Ans,max(Len(cp[j]-cp[i]),Len(cp[j]-cp[i+1])));//求最远距离
	}
	printf("%lld\n",(LL)(Ans+0.5));
}
