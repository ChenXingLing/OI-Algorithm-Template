#include<algorithm>
#include<cstdio>
#include<cmath>
#define LD double
#define Vector Point
#define Re register int
using namespace std;
const int N=1e4+3;
const LD eps=1e-8;
inline int dcmp(LD a){return a<-eps?-1:(a>eps?1:0);}
struct Point{LD x,y;Point(LD X=0,LD Y=0):x(X),y(Y){}}Poi[N],cp[N];
inline LD Dot(Vector a,Vector b){return a.x*b.x+a.y*b.y;}//���
inline LD Cro(Vector a,Vector b){return a.x*b.y-a.y*b.x;}//���
inline LD Len(Vector a){return sqrt(Dot(a,a));}//ģ��
inline LD Angle(Vector a,Vector b){return acos(Dot(a,b)/Len(a)/Len(b));}//�������н�
inline Vector Normal(Vector a){LD L=Len(a);return Vector(-a.y/L,a.x/L);}//��λ������(������ת90��)
inline Vector operator+(Vector a,Vector b){return Vector(a.x+b.x,a.y+b.y);}
inline Vector operator-(Vector a,Vector b){return Vector(a.x-b.x,a.y-b.y);}
inline Vector operator*(Vector a,LD b){return Vector(a.x*b,a.y*b);}
inline Vector operator/(Vector a,LD b){return Vector(a.x/b,a.y/b);}
inline bool cmp1(Vector a,Vector b){return a.x==b.x?a.y<b.y:a.x<b.x;};//����������
inline bool cmp2(Vector a,Vector b){//����������
	LD pan=Cro(a-Poi[0],b-Poi[0]);
	return pan>0||(pan==0&&Len(a-Poi[0])<Len(b-Poi[0]));
};
inline int ConvexHull(Point *P,Re n,Point *cp){
	sort(P+1,P+n+1,cmp1);
	Re t=0;
	for(Re i=1;i<=n;++i){//��͹�� 
		while(t>1&&dcmp(Cro(cp[t]-cp[t-1],P[i]-cp[t-1]))<=0)--t;
		cp[++t]=P[i];
	}
	Re St=t;
	for(Re i=n-1;i>=1;--i){//��͹�� 
		while(t>St&&dcmp(Cro(cp[t]-cp[t-1],P[i]-cp[t-1]))<=0)--t;
		cp[++t]=P[i];
	}
	return --t;//Ҫ��һ 
}
int n;LD ans;
int main(){
//	freopen("123.txt","r",stdin);
	scanf("%d",&n);
	for(Re i=1;i<=n;++i)scanf("%lf%lf",&Poi[i].x,&Poi[i].y);
	Re cnt=ConvexHull(Poi,n,cp);
	for(Re i=1;i<=cnt;++i)ans+=Len(cp[i<cnt?i+1:1]-cp[i]);
	printf("%.2lf\n",ans);
}
