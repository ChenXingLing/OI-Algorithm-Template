#include<algorithm>
#include<cstdio>
#include<cmath>
#define Re register int
using namespace std;
const int N=5e5+3;
int i,j,n,h,t,a[N],Q[N],Poi[N];
double p[N],sqr[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline double Y(Re i,Re j){return a[j]+sqr[i-j];}
inline int find_Poi(int j1,int j2){//找到两个直线的交点i 
    Re l=j2,r=n,mid,ans=n+1;//为了处理两个直线没有交点的情况，用一个变量记录答案
    while(l<=r){
        mid=l+r>>1;
        if(Y(mid,j1)<=Y(mid,j2))ans=mid,r=mid-1;
//当前这个位置i使得直线j1的纵坐标小于直线j2的纵坐标，说明这个点i在交点的右方，所以右边界要缩小
        else l=mid+1;
    }
    return ans;
}
inline void sakura(){
    h=1,t=0;
    for(i=1;i<=n;++i){//由于i本身也是一个决策点，所以要先入队再取答案择优
    	while(h<t&&Poi[t-1]>=find_Poi(Q[t],i))--t;//如果出现了上述可踢的情况，出队
    	Poi[t]=find_Poi(Q[t],i),Q[++t]=i;
    	while(h<t&&Poi[h]<=i)++h;
//找到第一个位置j使得直线Q[j]与直线Q[j+1]的交点大于i，
//那么直线Q[j]就是i前面在最上面的直线，即答案，自己画个图模拟一下就懂了
    	p[i]=max(p[i],Y(i,Q[h]));
    }
}
int main(){
    in(n);
    for(Re i=1;i<=n;++i)in(a[i]),sqr[i]=sqrt(i);
    sakura();
    for(Re i=1;i<n-i+1;++i)swap(a[i],a[n-i+1]),swap(p[i],p[n-i+1]);
    sakura();
    for(Re i=n;i;--i)printf("%d\n",(int)ceil(p[i])-a[i]);
}
