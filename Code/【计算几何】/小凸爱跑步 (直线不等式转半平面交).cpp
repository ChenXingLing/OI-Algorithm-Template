#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#define LD double
#define LL long long
#define Vector Point
#define Re register int
using namespace std;
const int N=1e5+3,inf=2e9;
const LD eps=1e-8;
inline int dcmp(LD a){return a<-eps?-1:(a>eps?1:0);}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Point{
    LD x,y;Point(LD X=0,LD Y=0){x=X,y=Y;}
    inline void in(){scanf("%lf%lf",&x,&y);}
};
inline LD Dot(Vector a,Vector b){return a.x*b.x+a.y*b.y;}
inline LD Cro(Vector a,Vector b){return a.x*b.y-a.y*b.x;}
inline Vector operator+(Vector a,Vector b){return Vector(a.x+b.x,a.y+b.y);}
inline Vector operator-(Vector a,Vector b){return Vector(a.x-b.x,a.y-b.y);}
inline Vector operator*(Vector a,LD b){return Vector(a.x*b,a.y*b);}
inline int judge(Point a,Point L,Point R){//≈–∂œAL «∑Ò‘⁄AR”“±ﬂ
    return dcmp(Cro(L-a,R-a))>0;
}
inline Point cross(Point a,Point b,Point c,Point d){
    Vector x=b-a,y=d-c,z=a-c;
    return a+x*(Cro(y,z)/Cro(x,y));
}
inline LD PolyArea(Point *P,Re n){
    LD ans=0;
    for(Re i=1;i<=n;++i)ans+=Cro(P[i],P[i<n?i+1:1]);
    return ans/2.0;
}
struct Line{
    Point a,b;LD k;Line(Point A=Point(0,0),Point B=Point(0,0)){a=A,b=B,k=atan2(b.y-a.y,b.x-a.x);}
    inline bool operator<(const Line &O)const{return dcmp(k-O.k)?dcmp(k-O.k)<0:judge(O.a,O.b,b);}
}Q[N<<1];
inline int judge(Point a,Line L){return dcmp(Cro(a-L.a,L.b-L.a))>0;}//≈–∂œµ„a «∑Ò‘⁄L”“±ﬂ
inline Point cross(Line L1,Line L2){return cross(L1.a,L1.b,L2.a,L2.b);}
inline int halfcut(Line *L,Re n,Point *P){
    sort(L+1,L+n+1);Re m=0;
    for(Re i=1;i<=n;++i)if(i==1||dcmp(L[i].k-L[i-1].k))L[++m]=L[i];
    Re h=1,t=0;
    for(Re i=1;i<=m;++i){
        while(h<t&&judge(cross(Q[t],Q[t-1]),L[i]))--t;
        while(h<t&&judge(cross(Q[h],Q[h+1]),L[i]))++h;
        Q[++t]=L[i];
    }
    while(h<t&&judge(cross(Q[t],Q[t-1]),Q[h]))--t;
    while(h<t&&judge(cross(Q[h],Q[h+1]),Q[t]))++h;
    m=0;
    for(Re i=h;i<=t;++i)P[++m]=cross(Q[i],Q[i<t?i+1:h]);
    return m;
}
int n,m;Point P[N],PP[N<<1];Line L[N<<1];
int main(){
//    freopen("123.txt","r",stdin);
    in(n);
    for(Re i=1;i<=n;++i)P[i].in();P[n+1]=P[1];
    for(Re i=2;i<=n;++i){
        Point tmp=P[1]-P[2]-P[i]+P[i+1];
        LD a=tmp.y,b=-tmp.x,c=Cro(P[1],P[2])-Cro(P[i],P[i+1]);//ax+by+c<=0
        if(!dcmp(a)&&!dcmp(b)){
            if(dcmp(c)<=0)continue;
            else{puts("0");return 0;}
        }
        if(!dcmp(a)){//by+c<=0
            if(b>0)L[++m]=Line(Point(1,-c/b),Point(0,-c/b));//y<=-c/b
            else L[++m]=Line(Point(0,-c/b),Point(1,-c/b));//y>=-c/b
        }
        else if(!dcmp(b)){//ax+c<=0
            if(a>0)L[++m]=Line(Point(-c/a,0),Point(-c/a,1));//x<=-c/a
            else L[++m]=Line(Point(-c/a,1),Point(-c/a,0));//x>=-c/a
        }
        else if(b>0)L[++m]=Line(Point(1,-a/b-c/b),Point(0,-c/b));//y<=-a/b*x-c/b
        else L[++m]=Line(Point(0,-c/b),Point(1,-a/b-c/b));//y>=-a/b*x-c/b
    }
    for(Re i=1;i<=n;++i)L[++m]=Line(P[i],P[i+1]);
    Re cnt=halfcut(L,m,PP);
    printf("%.4lf\n",PolyArea(PP,cnt)/PolyArea(P,n));
}
