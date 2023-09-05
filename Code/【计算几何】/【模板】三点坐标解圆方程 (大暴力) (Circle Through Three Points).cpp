#include<cstring>
#include<cstdio>
#include<cmath>
#define LD double
#define Re register LD
#define abs(x) (x<0?-x:x)
#define sakura(x) (x<0?'-':'+')
using namespace std;
struct Poi{LD x,y;inline void CL(){x=y=0;}}a1,a2,a3,xin;
struct Line{
	LD k,b;
	inline void CL(){k=b=0;}
	inline void calc(Poi a,Poi c){k=(a.y-c.y)/(a.x-c.x),b=a.y-k*a.x;}//已知两点坐标确定一条直线 
	inline void calc_(Poi a,Re K){k=K,b=a.y-k*a.x;}//已知一点坐标和k确定一条直线 
}L1,L2,L3,L4;
inline Poi Get_half(Poi a,Poi b){//求两点中点 
	Poi c;
	c.x=(a.x+b.x)/2.0,c.y=(a.y+b.y)/2.0;
	return c;
}
inline Poi Get_LPL(Line a,Line b){//求两直线交点 
	Poi c;
	c.x=(b.b-a.b)/(a.k-b.k),c.y=a.k*c.x+a.b;
	return c;
}
inline LD S(Re a){return a*a;}
inline LD Get_dis(Poi a,Poi b){//求两点距离 
	return sqrt(S(a.x-b.x)+S(a.y-b.y));
}
LD R;
int main(){
//	freopen("123.txt","r",stdin); 
	while(scanf("%lf%lf%lf%lf%lf%lf",&a1.x,&a1.y,&a2.x,&a2.y,&a3.x,&a3.y)!=EOF){
		xin.CL(),L1.CL(),L2.CL(),L3.CL(),L4.CL();
		L1.calc(a1,a2),L2.calc(a2,a3);//分别确定L1,L2 
		L3.calc_(Get_half(a1,a2),-1.0/L1.k);//求垂直平分L1的L3 
		L4.calc_(Get_half(a2,a3),-1.0/L2.k);//求垂直平分L2的L4
		xin=Get_LPL(L3,L4);//L3,L4的交点即为圆心 
		R=Get_dis(xin,a1);//求半径
//		printf("(x - %.3lf)^2 + (y - %.3lf)^2 = %.3lf^2\n",xin.x,xin.y,R);//标准式 
//		printf("x^2 + y^2 - %.3lfx + %.3lfy - %.3lf = 0\n",-2.0*xin.x,-2.0*xin.y,S(xin.x)+S(xin.y)-S(R));//二次函数式 
		Re a=-xin.x,b=-xin.y,c=R,d=-2.0*xin.x,e=-2.0*xin.y,f=S(xin.x)+S(xin.y)-S(R);
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
}
