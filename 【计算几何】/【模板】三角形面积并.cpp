#pragma GCC optimize(3,"Ofast","inline")
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
const LD eps=1e-9;
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
struct Triangle{
	LD x,y,m,L,R,D,U;
	inline void in(){scanf("%lf%lf%lf",&x,&y,&m),L=x,R=x+m,D=y,U=y+m;}
}C[N],C_[N];
inline bool cmp(Triangle A,Triangle B){return A.m<B.m;}
inline LD F(Rd Y){
    if(vis[Y])return vis[Y];
    Re t=0;Rd ans=0;
    for(Re i=1;i<=n;++i)
        if(dcmp(Y-C[i].D)>=0&&dcmp(Y-C[i].U)<0){
			Rd tmp=C[i].U-Y;
			if(dcmp(tmp)>0)Seg[++t]=Segment(C[i].x,C[i].x+tmp);
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
inline int TIT(Triangle A,Triangle B){//判断三角形A是否在三角形B以内
	return A.L>=B.L&&A.R<=B.R&&A.D>=B.D&&A.U<=B.U&&dcmp(A.R-(B.x+B.U-A.y))<=0;
}
LD ans,YY[N<<1];
int main(){
//	freopen("456.txt","r",stdin);
    scanf("%d",&m);Re t=0;
    for(Re i=1;i<=m;++i)C_[i].in();
    sort(C_+1,C_+m+1,cmp),C[++n]=C_[m];//按半径大小排序
    for(Re i=m-1;i>=1;--i){
        Re flag=1;
        for(Re j=1;j<=n&&flag;++j)if(TIT(C_[i],C[j]))flag=0;
        if(flag)C[++n]=C_[i];
    }
    for(Re i=1;i<=n;++i)YY[++t]=C[i].D,YY[++t]=C[i].U;
	sort(YY+1,YY+t+1);
    for(Re i=2;i<=t;++i)//若干个小块分别处理
		if(dcmp(YY[i]-YY[i-1])>0){
			Rd D=YY[i-1],U=YY[i]-2*eps;
	        ans+=sakura(D,U,Simpson(D,U));
    	}
    printf("%.1lf",ans);
}
