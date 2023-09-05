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
inline int find_Poi(int j1,int j2){//�ҵ�����ֱ�ߵĽ���i 
    Re l=j2,r=n,mid,ans=n+1;//Ϊ�˴�������ֱ��û�н�����������һ��������¼��
    while(l<=r){
        mid=l+r>>1;
        if(Y(mid,j1)<=Y(mid,j2))ans=mid,r=mid-1;
//��ǰ���λ��iʹ��ֱ��j1��������С��ֱ��j2�������꣬˵�������i�ڽ�����ҷ��������ұ߽�Ҫ��С
        else l=mid+1;
    }
    return ans;
}
inline void sakura(){
    h=1,t=0;
    for(i=1;i<=n;++i){//����i����Ҳ��һ�����ߵ㣬����Ҫ�������ȡ������
    	while(h<t&&Poi[t-1]>=find_Poi(Q[t],i))--t;//����������������ߵ����������
    	Poi[t]=find_Poi(Q[t],i),Q[++t]=i;
    	while(h<t&&Poi[h]<=i)++h;
//�ҵ���һ��λ��jʹ��ֱ��Q[j]��ֱ��Q[j+1]�Ľ������i��
//��ôֱ��Q[j]����iǰ�����������ֱ�ߣ����𰸣��Լ�����ͼģ��һ�¾Ͷ���
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
