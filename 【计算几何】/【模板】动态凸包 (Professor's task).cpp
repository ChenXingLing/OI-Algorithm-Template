#include<algorithm>
#include<cstdio>
#include<set>
#define LL long long
#define Vector Point
#define Re register int
#define IT set<Point>::iterator
using namespace std;
const int inf=2e9;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Point{
    LL x,y;Point(LL X=0,LL Y=0){x=X,y=Y;}
    inline void In(){Re X,Y;in(X),in(Y),x=X,y=Y;}
    inline bool operator<(const Point &O)const{return x!=O.x?x<O.x:y<O.y;}
}P;
inline LL Cro(Vector a,Vector b){return a.x*b.y-a.y*b.x;}
inline Vector operator-(Vector a,Vector b){return Vector(a.x-b.x,a.y-b.y);}
struct ConvexHull{
	int op;set<Point>s;
	inline int PIP(Point P){
		IT it=s.lower_bound(Point(P.x,-inf));//找到第一个横坐标大于P的点
		if(it==s.end())return 0;
		if(it->x==P.x)return (P.y-it->y)*op<=0;//比较纵坐标大小
		if(it==s.begin())return 0;
		IT j=it,k=it;--j;return Cro(P-*j,*k-*j)*op>=0;//看叉姬
	}
	inline int judge(IT it){
		IT j=it,k=it;
		if(j==s.begin())return 0;--j;
		if(++k==s.end())return 0;
		return Cro(*it-*j,*k-*j)*op>=0;//看叉姬
	}
	inline void insert(Point P){
		if(PIP(P))return;//如果点P已经在凸壳上或凸包里就不插入了
		IT tmp=s.lower_bound(Point(P.x,-inf));if(tmp!=s.end()&&tmp->x==P.x)s.erase(tmp);//特判横坐标相等的点要去掉
		s.insert(P);IT it=s.find(P),p=it;
		if(p!=s.begin()){--p;while(judge(p)){IT tmp=p--;s.erase(tmp);}}
		if((p=++it)!=s.end())while(judge(p)){IT tmp=p++;s.erase(tmp);}
	}
}up,down;
int x,y,T,op;
int main(){
//	freopen("123.txt","r",stdin);
	in(T),up.op=1,down.op=-1;
	while(T--){
		in(op),P.In();
		if(op<2)up.insert(P),down.insert(P);//插入点P
		else puts((up.PIP(P)&&down.PIP(P))?"YES":"NO");//判断点P是否在凸包内
	}
}
