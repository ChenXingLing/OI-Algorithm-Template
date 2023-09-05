#include<algorithm>
#include<cstdio>
#include<cmath>
#define LD double
#define LL long long
#define Vector Point
#define Re register int
#define S(a) ((a)*(a))
using namespace std;
const int N=1e6+3;
const LD eps=1e-8;
inline int dcmp(LD a){return a<-eps?-1:(a>eps?1:0);}//处理精度
int n;
struct Point{
    LD x,y;Point(LD X=0,LD Y=0){x=X,y=Y;}
    inline void in(){scanf("%lf%lf",&x,&y);}
}P[N];
inline LD Dot(Vector a,Vector b){return a.x*b.x+a.y*b.y;}//【点积】
inline LD Len(Vector a){return sqrt(Dot(a,a));}//【模长】
inline Vector operator+(Vector a,Vector b){return Vector(a.x+b.x,a.y+b.y);}
inline Vector operator-(Vector a,Vector b){return Vector(a.x-b.x,a.y-b.y);}
inline Vector operator*(Vector a,LD b){return Vector(a.x*b,a.y*b);}
struct Circle{Point O;LD r;Circle(Point P,LD R=0){O=P,r=R;}};
inline Circle getcircle(Point A,Point B,Point C){//【三点确定一圆】
	LD x1=A.x,y1=A.y,x2=B.x,y2=B.y,x3=C.x,y3=C.y;
	LD D=((S(x2)+S(y2)-S(x3)-S(y3))*(y1-y2)-(S(x1)+S(y1)-S(x2)-S(y2))*(y2-y3))/((x1-x2)*(y2-y3)-(x2-x3)*(y1-y2));
	LD E=(S(x1)+S(y1)-S(x2)-S(y2)+D*(x1-x2))/(y2-y1);
	LD F=-(S(x1)+S(y1)+D*x1+E*y1);
	return Circle(Point(-D/2.0,-E/2.0),sqrt((S(D)+S(E)-4.0*F)/4.0));
}
inline int PIC(Circle &C,Point a){return dcmp(Len(a-C.O)-C.r)<=0;}//判断点A是否在圆C内
inline void Random(){for(Re i=1;i<=n;++i)swap(P[i],P[rand()%n+1]);}
int main(){
//	freopen("123.txt","r",stdin);
	scanf("%d",&n);
	for(Re i=1;i<=n;++i)P[i].in();
//	random_shuffle(P+1,P+n+1);
	Random();Circle C=Circle(P[1],0);
	for(Re i=2;i<=n;++i)
		if(!PIC(C,P[i])){
			C=Circle(P[i],0);
			for(Re j=1;j<i;++j)
				if(!PIC(C,P[j])){
					C.O=(P[i]+P[j])*0.5,C.r=Len(P[j]-C.O);
					for(Re k=1;k<j;++k)if(!PIC(C,P[k]))C=getcircle(P[i],P[j],P[k]);
				}
		}
	printf("%.2lf %.2lf %.2lf\n",C.O.x,C.O.y,C.r);
}
