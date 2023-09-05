//#pragma GCC optimize(3,"Ofast","inline")
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<map>
#define LD double
#define LL long long
#define Re register int
#define Rd register LD
#define Vector Point
using namespace std;
const int N=2003;
const LD eps=1e-13;
int n,m;map<LD,LD>vis;
inline int dcmp(Rd a){return a<-eps?-1:(a>eps?1:0);}
struct Point{
    LD x,y;Point(LD X=0,LD Y=0){x=X,y=Y;}
    inline void in(){scanf("%lf%lf",&x,&y);}
};
struct Segment{
    LD L,R;Segment(LD l=0,LD r=0){L=l,R=r;}
    inline bool operator<(Segment O)const{return L!=O.L?L<O.L:R<O.R;}
}Seg[N];
struct Circle{
    LD x,y,r,L,R,D,U;
    inline void in(){scanf("%lf%lf%lf",&x,&y,&r),L=x-r,R=x+r,D=y-r,U=y+r;}
    inline bool operator<(Circle B)const{return D<B.D;}
}C[N],C_[N];
inline bool cmp(Circle A,Circle B){return A.r<B.r;}
inline LD dis(Circle A,Circle B){return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));}
inline LD SS(Rd x){return x*x;}
inline LD F(Rd Y){
    if(vis[Y])return vis[Y];
    Re t=0;Rd ans=0;
    for(Re i=1;i<=n;++i)
        if(dcmp(Y-C[i].D)>0&&dcmp(Y-C[i].U)<0){
            Rd tmp=sqrt(SS(C[i].r)-SS(C[i].y-Y));
            if(dcmp(tmp)>0)Seg[++t]=Segment(C[i].x-tmp,C[i].x+tmp);
        }
    if(!t)return 0.0;
    sort(Seg+1,Seg+t+1);
    for(Re i=1,j;i<=t;i=j+1){
        Rd L=Seg[i].L,R=Seg[i].R;j=i;
        while(j<t&&Seg[j+1].L<=R)++j,R=max(R,Seg[j].R);
        ans+=R-L;
    }
    return vis[Y]=ans;
}
inline LD Simpson(Rd L,Rd R){return (R-L)*(F(L)+4.0*F((L+R)*0.5)+F(R))/6.0;}
inline LD sakura(Rd L,Rd R,Rd now){
    Rd mid=(L+R)*0.5,FL=Simpson(L,mid),FR=Simpson(mid,R);
    if(!dcmp(now-FL-FR))return now;
    return sakura(L,mid,FL)+sakura(mid,R,FR);
}
LD ans;
int main(){
//    freopen("789.txt","r",stdin);
    scanf("%d",&m);
    for(Re i=1;i<=m;++i)C_[i].in();
    sort(C_+1,C_+m+1,cmp),C[++n]=C_[m];//按半径大小排序
    for(Re i=m-1;i>=1;--i){
        Re flag=1;
        for(Re j=1;j<=n&&flag;++j)
			if(dcmp(C_[i].r-C[j].r+dis(C_[i],C[j]))<=0)flag=0;//小r+大r <= dis，则说明小圆被包含了
        if(flag)C[++n]=C_[i];
    }
    sort(C+1,C+n+1);
    for(Re i=1,j;i<=n;i=j+1){//每个联通块单独处理
        Rd D=C[i].D,U=C[i].U;j=i;
        while(j<n&&C[j+1].D<=U)++j,U=max(U,C[j].U);
        ans+=sakura(D,U,Simpson(D,U));
    }
    printf("%.3lf",ans);
}
