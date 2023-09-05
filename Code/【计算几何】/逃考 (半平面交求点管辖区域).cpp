#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<queue>
#define LD double
#define LL long long
#define Vector Point
#define Re register int
using namespace std;
const int N=610;
const LD eps=1e-8,Pi=acos(-1);
inline int dcmp(LD a){return a<-eps?-1:(a>eps?1:0);}
struct Point{
	LD x,y;Point(LD X=0,LD Y=0){x=X,y=Y;}
	inline void in(){scanf("%lf%lf",&x,&y);}
	inline void print(){printf("%.2lf %.2lf\n",x,y);}
}P[N];
inline LD Dot(Vector a,Vector b){return a.x*b.x+a.y*b.y;}
inline LD Cro(Vector a,Vector b){return a.x*b.y-a.y*b.x;}
inline LD Len(Vector a){return Dot(a,a);}
inline Vector operator+(Vector a,Vector b){return Vector(a.x+b.x,a.y+b.y);}
inline Vector operator-(Vector a,Vector b){return Vector(a.x-b.x,a.y-b.y);}
inline Vector operator*(Vector a,LD x){return Vector(a.x*x,a.y*x);}
inline Point cross(Point a,Point b,Point c,Point d){
	Vector x=b-a,y=d-c,z=a-c;
	return a+x*(Cro(y,z)/Cro(x,y));
}
inline int judge(Point a,Point L,Point R){//判断AL是否在AR的右边
	return dcmp(Cro(L-a,R-a))>0;
}
struct Line{
	Point a,b;LD k;int id;Line(Point A=Point(0,0),Point B=Point(0,0)){id=0,a=A,b=B,k=atan2(b.y-a.y,b.x-a.x);}
	inline bool operator<(const Line &O)const{return dcmp(k-O.k)?dcmp(k-O.k)<0:judge(O.a,O.b,b);}
}Q[N];
inline Point cross(Line L1,Line L2){return cross(L1.a,L1.b,L2.a,L2.b);}
inline int judge(Line L,Point a){return dcmp(Cro(a-L.a,L.b-L.a))>0;}//判断点A是否在直线L右边
inline void halfcut(Line *L,Re &n){
	sort(L+1,L+n+1);Re m=n;n=0;
	for(Re i=1;i<=m;++i)if(i==1||dcmp(L[i].k-L[i-1].k))L[++n]=L[i];
	Re h=1,t=0;
	for(Re i=1;i<=n;++i){
		while(h<t&&judge(L[i],cross(Q[t],Q[t-1])))--t;
		while(h<t&&judge(L[i],cross(Q[h],Q[h+1])))++h;
		Q[++t]=L[i];
	}
	while(h<t&&judge(Q[h],cross(Q[t],Q[t-1])))--t;
	while(h<t&&judge(Q[t],cross(Q[h],Q[h+1])))++h;
	n=0;
	for(Re i=h;i<=t;++i)L[++n]=Q[i];
}
inline Point turnP(Point a,LD theta){//将点A/向量A顺时针旋转theta弧度
	LD x=a.x*cos(theta)+a.y*sin(theta);
	LD y=a.y*cos(theta)-a.x*sin(theta);
	return Point(x,y);
}
inline Line get_midL(Point a,Point b){//获取线段AB的中垂线(A在其左边)
	Point M=a+((b-a)*0.5);
	return Line(M,M+turnP(a-b,Pi/2.0));
}
int n,m,T,st,ed;Point a,b,c,d,x0,A[N];Line L[N];
struct Dijkstra{
	int o,dis[N],pan[N],head[N];
	struct QAQ{int w,to,next;}a[N*N];
	inline void add(Re x,Re y,Re z){a[++o].w=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
	struct QWQ{int x,d;inline bool operator<(const QWQ &O)const{return d>O.d;}};
	priority_queue<QWQ>Q;
	inline void CL(){memset(head,0,sizeof(head)),o=0;}
	inline int dijkstra(Re st,Re ed){
		for(Re i=0;i<=n;++i)dis[i]=2e9,pan[i]=0;
		Q.push((QWQ){st,dis[st]=1});
		while(!Q.empty()){
			Re x=Q.top().x;Q.pop();
			if(pan[x])continue;
			pan[x]=1;
			for(Re i=head[x],to;i;i=a[i].next)
				if(dis[to=a[i].to]>dis[x]+a[i].w)
					Q.push((QWQ){to,dis[to]=dis[x]+a[i].w});
		}
		return dis[ed];
	}
}T1;
int main(){
//	freopen("456.txt","r",stdin);
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n),c.in(),x0.in(),T1.CL();
		if(!n){puts("0");continue;}
		a=Point(0,0),b=Point(c.x,0),d=Point(0,c.y);
		for(Re i=1;i<=n;++i){
			A[i].in();
			if(A[i].x>c.x||A[i].y>c.y){--i,--n;continue;}
			if(dcmp(Len(A[i]-x0)-Len(A[st]-x0))<0)st=i;
		}
//		printf("st=%d\n",st);
		for(Re i=1;i<=n;++i){
			Re m=0;
			for(Re j=1;j<=n;++j)
				if(i!=j)L[++m]=get_midL(A[i],A[j]),L[m].id=j;
			L[++m]=Line(a,b),L[++m]=Line(b,c),L[++m]=Line(c,d),L[++m]=Line(d,a);
			halfcut(L,m);
			for(Re j=1;j<=m;++j)T1.add(i,L[j].id,L[j].id>0);
		}
		printf("%d\n",T1.dijkstra(st,ed));
	}
}
