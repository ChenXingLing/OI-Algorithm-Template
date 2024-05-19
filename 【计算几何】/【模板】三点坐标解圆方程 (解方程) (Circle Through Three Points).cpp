#include<cstdio>
#include<cmath>
#define LD double
#define LL long long
#define Re register int
#define S(a) ((a)*(a))
using namespace std;
struct Point{LD x,y;Point(LD X=0,LD Y=0){x=X,y=Y;}};
struct Circle{Point O;LD r;Circle(Point P,LD R=0){O=P,r=R;}};
inline Circle getcircle(Point A,Point B,Point C){
	LD x1=A.x,y1=A.y,x2=B.x,y2=B.y,x3=C.x,y3=C.y;
	LD D=((S(x2)+S(y2)-S(x3)-S(y3))*(y1-y2)-(S(x1)+S(y1)-S(x2)-S(y2))*(y2-y3))/((x1-x2)*(y2-y3)-(x2-x3)*(y1-y2));
	LD E=(S(x1)+S(y1)-S(x2)-S(y2)+D*(x1-x2))/(y2-y1);
	LD F=-(S(x1)+S(y1)+D*x1+E*y1);
//	printf("(%.3lf,%.3lf), D=%.3lf E=%.3lf F=%.3lf\n",D/2.0,E/2.0,D,E,F);
	return Circle(Point(-D/2.0,-E/2.0),sqrt((S(D)+S(E)-4.0*F)/4.0));
}
#define abs(x) (x<0?-x:x)
#define sakura(x) (x<0?'-':'+')
inline void print(Point O,LD r){//UVAµÄ¹íÐóÊä³ö
	LD a=-O.x,b=-O.y,c=r,d=-2.0*O.x,e=-2.0*O.y,f=S(O.x)+S(O.y)-S(r);
	if(a!=0)printf("(x %c %.3lf)^2 ",sakura(a),abs(a));
    else printf("x^2 ");
    if(b!=0)printf("+ (y %c %.3lf)^2 ",sakura(b),abs(b));
    else printf("+ y^2 ");
    printf("= %.3lf^2\n",c);
    printf("x^2 + y^2");
    if(d!=0)printf(" %c %.3lf%c",sakura(d),abs(d),'x');
    if(e!=0)printf(" %c %.3lf%c",sakura(e),abs(e),'y');
    if(f!=0)printf(" %c %.3lf%c",sakura(f),abs(f),' ');
    printf("= 0\n\n");
}
int main(){
//	freopen("123.txt","r",stdin);
	LD a,b,c,d,e,f;
	while(scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&e,&f)!=EOF){
		Circle C=getcircle(Point(a,b),Point(c,d),Point(e,f));print(C.O,C.r);
	}
}
