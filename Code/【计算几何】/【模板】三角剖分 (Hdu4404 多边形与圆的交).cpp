#include<algorithm>
#include<cstdio>
#include<cmath>
#define LD double
#define LL long long
#define Vector Point
#define Re register int
using namespace std;
const int N=1e5+3;
const LD eps=1e-8,Pi=acos(-1.0);
inline int dcmp(LD a){return a<-eps?-1:(a>eps?1:0);}
inline LD Abs(LD a){return a*dcmp(a);}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline LD LDin(){
    LD X=0,Y=1.0;int f=0;char c=getchar();
    while(c<'0'||c>'9'){f|=c=='-';c=getchar();} 
    while(c>='0'&&c<='9')X=X*10+(c^48),c=getchar(); 
    if(c=='.'){c=getchar();while(c>='0'&&c<='9')X+=(Y/=10)*(c^48),c=getchar();}
    return f?-X:X;
}
struct Point{
    LD x,y;Point(LD X=0,LD Y=0){x=X,y=Y;}
    inline void in(){x=LDin(),y=LDin();}
    inline bool operator<(const Point &O)const{return x!=O.x?x<O.x:y<O.y;}
};
inline LD Dot(Vector a,Vector b){return a.x*b.x+a.y*b.y;}
inline LD Cro(Vector a,Vector b){return a.x*b.y-a.y*b.x;}
inline LD Len(Vector a){return sqrt(Dot(a,a));}
inline LD Angle(Vector a,Vector b){return acos(Dot(a,b)/Len(a)/Len(b));}
inline Vector operator-(Vector a,Vector b){return Vector(a.x-b.x,a.y-b.y);}
inline Vector operator+(Vector a,Vector b){return Vector(a.x+b.x,a.y+b.y);}
inline Vector operator*(Vector a,LD b){return Vector(a.x*b,a.y*b);}
inline bool operator==(Vector a,Vector b){return !dcmp(a.x-b.x)&&!dcmp(a.y-b.y);}
inline Point turn_P(Point a,LD theta){
    LD x=a.x*cos(theta)+a.y*sin(theta);
    LD y=-a.x*sin(theta)+a.y*cos(theta);
    return Point(x,y);
}
inline Point cross_LL(Point a,Point b,Point c,Point d){
    Vector x=b-a,y=d-c,z=a-c;
    return a+x*(Cro(y,z)/Cro(x,y));
}
inline LD dis_PL(Point p,Point a,Point b){
    if(a==b)return Len(p-a);
    Vector x=p-a,y=p-b,z=b-a;
    if(dcmp(Dot(x,z))<0)return Len(x);
    if(dcmp(Dot(y,z))>0)return Len(y);
    return Abs(Cro(x,z)/Len(z));
}
inline Point FootPoint(Point p,Point a,Point b){
    Vector x=p-a,y=p-b,z=b-a;
    LD len1=Dot(x,z)/Len(z),len2=-1.0*Dot(y,z)/Len(z);
    return a+z*(len1/(len1+len2));
}
inline LD calc(Point A,Point B,Point O,LD R){
    if((A==O)||(B==O))return 0;
    Re op=(dcmp(Cro(A-O,B-O))>0)?1:-1;LD ans=0;
    Vector x=A-O,y=B-O;
    Re flag1=(int)(dcmp(Len(x)-R)>0),flag2=(int)(dcmp(Len(y)-R)>0);
    if(!flag1&&!flag2)ans=Abs(Cro(A-O,B-O))/2.0;
    else if(flag1&&flag2){
        if(dcmp(dis_PL(O,A,B)-R)>=0)ans=R*R*Angle(x,y)/2.0;
        else{
            if(dcmp(Cro(A-O,B-O))>0)swap(A,B);
            Point F=FootPoint(O,A,B);LD lenx=Len(F-O),len=sqrt(R*R-lenx*lenx);
            Vector z=turn_P(F-O,Pi/2.0)*(len/lenx);Point B_=F+z,A_=F-z;
            ans=R*R*(Angle(A-O,A_-O)+Angle(B-O,B_-O))/2.0+Cro(B_-O,A_-O)/2.0;
        }
    }
    else{
        if(flag1)swap(A,B);
        Point F=FootPoint(O,A,B);LD lenx=Len(F-O),len=sqrt(R*R-lenx*lenx);
        Vector z=turn_P(F-O,Pi/2.0)*(len/lenx);Point C=(dcmp(Cro(A-O,B-O))>0)?(F-z):(F+z);
        ans=Abs(Cro(A-O,C-O))/2.0+R*R*Angle(C-O,B-O)/2.0;
    }
    return ans*op;
}
Point V,P[N];LD h,t,g,v0,ans,theta;int n;Point O;LD R;
int main(){
//    freopen("123.txt","r",stdin);
    while(~scanf("%lf",&O.x)){
        O.y=LDin(),v0=LDin(),theta=LDin(),t=LDin(),g=LDin(),R=LDin();
        if(!dcmp(O.x)&&!dcmp(O.y)&&!dcmp(v0)&&!dcmp(theta)&&!dcmp(t)&&!dcmp(g)&&!dcmp(R))break;
        theta=theta/180.0*Pi,O.x+=t*v0*cos(theta),O.y+=t*v0*sin(theta)-0.5*g*t*t,ans=0;
//        printf("O=(%.2lf,%.2lf), R=%d\n",O.x,O.y,R);
        in(n);for(Re i=1;i<=n;++i)P[i].in();
        for(Re i=1;i<=n;++i)ans+=calc(P[i],P[i<n?i+1:1],O,R);
        if(!dcmp(ans))puts("0.00");
        else printf("%.2lf\n",Abs(ans));
    }
}
