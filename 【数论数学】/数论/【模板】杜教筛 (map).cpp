#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<map>
#define Re register int
#define LL long long
using namespace std;
const int N23=1664511+3,N=2147483647;
int x,T,cnt,pan[N23],pri[N23],phi[N23],miu[N23];
int TO,Smiu[N23];LL Sphi[N23];
map<int,int>Smiu_;map<int,LL>Sphi_;
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
	if(Sphi_[n])return Sphi_[n];
	LL ans=(LL)n*(n+1)>>1;
	for(Re l=2,r;l<=n;l=r+1){
		r=n/(n/l);
		ans-=(LL)(r-l+1)*get_Sphi(n/l);
	}
	return Sphi_[n]=ans;
}
inline int get_Smiu(Re n){
	if(n<=TO)return Smiu[n];
	if(Smiu_[n])return Smiu_[n];
	Re ans=1;
	for(Re l=2,r;l<=n;l=r+1){
		r=n/(n/l);
		ans-=(r-l+1)*get_Smiu(n/l);
	}
	return Smiu_[n]=ans;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(T),get_(TO=N23-3);
	while(T--)in(x),printf("%lld %d\n",get_Sphi(x),get_Smiu(x));
}
