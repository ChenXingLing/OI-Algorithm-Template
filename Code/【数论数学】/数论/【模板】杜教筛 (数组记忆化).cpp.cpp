#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#define Re register int
#define LL long long
using namespace std;
const int N23=1664511+3,N13=1303,N=2147483647;
int x,T,cnt,pan[N23],pri[N23],phi[N23],miu[N23];
int TO,vis1[N13],vis2[N13],Smiu[N23],Smiu_[N13];
LL Sphi[N23],Sphi_[N13];
inline void in(Re &x){
	Re fu=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=fu?-x:x;
}
inline void get_(Re N){
	miu[1]=phi[1]=pan[1]=1;
	for(Re i=2;i<=N;++i){
		if(!pan[i])pri[++cnt]=i,miu[i]=-1,phi[i]=i-1;
		for(Re j=1;j<=cnt&&pri[j]<=N/i;++j){
			pan[i*pri[j]]=1;
			if(i%pri[j])miu[i*pri[j]]=-miu[i],phi[i*pri[j]]=phi[i]*phi[pri[j]];
			else{miu[i*pri[j]]=0,phi[i*pri[j]]=phi[i]*pri[j];break;}
		}
	}
	for(Re i=1;i<=N;++i)Smiu[i]=Smiu[i-1]+miu[i],Sphi[i]=Sphi[i-1]+phi[i];
}
inline LL get_Sphi(Re n){
	if(n<=TO)return Sphi[n];
	Re nn=N/n;
	if(vis1[nn])return Sphi_[nn];
	LL ans=(LL)n*(n+1)>>1;
	for(Re l=2,r;l<=n;l=r+1){
		r=n/(n/l);
		ans-=(LL)(r-l+1)*get_Sphi(n/l);
	}
	vis1[nn]=1;
	return Sphi_[nn]=ans;
}
inline int get_Smiu(Re n){
	if(n<=TO)return Smiu[n];
	Re nn=N/n;
	if(vis2[nn])return Smiu_[nn];
	Re ans=1;
	for(Re l=2,r;l<=n;l=r+1){
		r=n/(n/l);
		ans-=(r-l+1)*get_Smiu(n/l);
	}
	vis2[nn]=1;
	return Smiu_[nn]=ans;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(T),get_(TO=N23-3);
	while(T--){
		in(x),printf("%lld %d\n",get_Sphi(x),get_Smiu(x));
		memset(vis1,0,sizeof(vis1));//注意对于每次询问的n，n/i都不同 
		memset(vis2,0,sizeof(vis2));//所以要清空 
	}
}
