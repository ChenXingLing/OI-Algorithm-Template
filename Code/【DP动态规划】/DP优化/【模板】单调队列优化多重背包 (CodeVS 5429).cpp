#include<cstdio>
#define Re register int
const int N=7003,M=7003;
int n,h,t,V,mp,tmp,v[N],w[N],c[N],Q[N],K[N],dp[M];
inline void in(Re &x){
	Re fu=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=fu?-x:x;
}
inline int max(Re a,Re b){return a>b?a:b;}
inline int min(Re a,Re b){return a<b?a:b;}
int main(){
    in(n),in(V);
    for(Re i=1;i<=n;++i)in(v[i]),in(w[i]),in(c[i]);
    for(Re i=1;i<=n;++i)
    	for(Re r=0;r<v[i];++r){
    		h=1,t=0,mp=(V-r)/v[i];
    		for(Re p=0;p<=mp;++p){
    			tmp=dp[p*v[i]+r]-w[i]*p;
    			while(h<=t&&Q[t]<=tmp)--t;
    			Q[++t]=tmp,K[t]=p;
    			while(h<=t&&p-K[h]>min(c[i],V/v[i]))++h;
    			dp[p*v[i]+r]=max(dp[p*v[i]+r],Q[h]+p*w[i]);
			}
		}
    printf("%d",dp[V]);
}
