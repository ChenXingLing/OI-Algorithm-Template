#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#define LD double
#define LL long long
#define Vector Point
#define Re register int
using namespace std;
const int N=1e5+3,inf=1e8;
const LD eps=1e-8;
inline int dcmp(LD a){return a<-eps?-1:(a>eps?1:0);}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Point{
	LD x,y;LD k;Point(LD X=0,LD Y=0){x=X,y=Y;}
	inline void in(){scanf("%lf%lf",&x,&y);}
	inline void print(Re op=0){printf("(%.2lf %.2lf) ",x,y);if(op)puts("");}
};
inline LD Dot(Vector a,Vector b){return a.x*b.x+a.y*b.y;}
inline LD Cro(Vector a,Vector b){return a.x*b.y-a.y*b.x;}
inline LD Len(Vector a){return sqrt(Dot(a,a));}
inline Vector operator+(Vector a,Vector b){return Vector(a.x+b.x,a.y+b.y);}
inline Vector operator-(Vector a,Vector b){return Vector(a.x-b.x,a.y-b.y);}
inline Vector operator*(Vector a,LD b){return Vector(a.x*b,a.y*b);}
inline bool cmp1(Vector a,Vector b){return a.x==b.x?a.y<b.y:a.x<b.x;};//按坐标排序
inline int ConvexHull(Point *P,Re n,Point *cp){//【Graham扫描法】求凸包
    sort(P+1,P+n+1,cmp1);
    Re t=0;
    for(Re i=1;i<=n;++i){//下凸包
        while(t>1&&dcmp(Cro(cp[t]-cp[t-1],P[i]-cp[t-1]))<=0)--t;
        cp[++t]=P[i];
    }
    Re St=t;
    for(Re i=n-1;i>=1;--i){//上凸包
        while(t>St&&dcmp(Cro(cp[t]-cp[t-1],P[i]-cp[t-1]))<=0)--t;
        cp[++t]=P[i];
    }
    return --t;//要减一
}
inline int judge(Point a,Point L,Point R){//判断AL是否在AR右边
	return dcmp(Cro(L-a,R-a))>0;
}
inline int PIL(Point a,Point b,Point p){//判断点P是否在线段AB上
	return !dcmp(Cro(p-a,b-a))&&dcmp(Cro(p-a,p-b))<0;
}
inline int PIP(Point *P,Re n,Point a){
	if(judge(P[1],a,P[2])||judge(P[1],P[n],a))return 0;
	if(PIL(P[1],P[2],a)||PIL(P[1],P[n],a))return 1;
	Re l=2,r=n-1;
	while(l<r){
		Re mid=l+r+1>>1;
		if(judge(P[1],P[mid],a))l=mid;
		else r=mid-1;
	}
	if(judge(P[l],a,P[l+1]))return 0;
	if(PIL(P[l],P[l+1],a))return 1;
	return 1;
}
Vector V1[N],V2[N];
inline int Mincowski(Point *P1,Re n,Point *P2,Re m,Vector *V){//【闵可夫斯基和】求两个凸包{P1},{P2}的向量集合{V}={P1+P2}构成的凸包
	for(Re i=1;i<=n;++i)V1[i]=P1[i<n?i+1:1]-P1[i];
	for(Re i=1;i<=m;++i)V2[i]=P2[i<m?i+1:1]-P2[i];
	Re t=0,i=1,j=1;V[++t]=P1[1]+P2[1];
	while(i<=n&&j<=m)++t,V[t]=V[t-1]+(dcmp(Cro(V1[i],V2[j]))>0?V1[i++]:V2[j++]);
	while(i<=n)++t,V[t]=V[t-1]+V1[i++];
	while(j<=m)++t,V[t]=V[t-1]+V2[j++];
	return t;
}
int n,m,T;Point v,P1[N],P2[N],cp1[N],cp2[N];Vector V[N<<1];
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(m),in(T);
	for(Re i=1;i<=n;++i)P1[i].in();
	for(Re i=1;i<=m;++i)P2[i].in(),P2[i].x=-P2[i].x,P2[i].y=-P2[i].y;
	Re cnt1=ConvexHull(P1,n,cp1),cnt2=ConvexHull(P2,m,cp2);
	Re cnt=Mincowski(cp1,cnt1,cp2,cnt2,V); 
	while(T--)v.in(),printf("%d\n",PIP(V,cnt,v));
}
