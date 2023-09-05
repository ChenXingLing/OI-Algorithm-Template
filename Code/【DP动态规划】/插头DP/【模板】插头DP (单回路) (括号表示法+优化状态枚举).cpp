#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=14,M=1594323+3;
int n,m,o,V,edx,edy,Mi[N],A[N][N];LL ans,dp[2][M];char s[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
int st[2][M];
inline void add(Re s,LL v){
	if(!dp[o][s])st[o][++st[o][0]]=s;
	dp[o][s]+=v;
}
inline void CL(){
	for(Re i=1;i<=st[o][0];++i)dp[o][st[o][i]]=0;
	st[o][0]=0;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(m),Mi[0]=1;
	for(Re i=1;i<=m+1;++i)Mi[i]=Mi[i-1]*3;V=Mi[m+1]-1;
	for(Re i=1;i<=n;++i){
		scanf("%s",s+1);
		for(Re j=1;j<=m;++j)if(!(A[i][j]=(s[j]=='*')))edx=i,edy=j;
	}
//	printf("edx=%d, edy=%d\n",edx,edy);
	dp[o][st[o][++st[o][0]]=0]=1;
	for(Re i=1;i<=n;++i){
		o^=1,CL();
		for(Re I=1;I<=st[o^1][0];++I)if(st[o^1][I]*3<=V&&dp[o^1][st[o^1][I]])
			dp[o][st[o][++st[o][0]]=st[o^1][I]*3]=dp[o^1][st[o^1][I]];
		for(Re j=1;j<=m;++j){
			o^=1,CL();
			for(Re I=1;I<=st[o^1][0];++I)if(dp[o^1][st[o^1][I]]){
				Re s=st[o^1][I];LL v=dp[o^1][s];
				Re L=s/Mi[j-1]%3,U=s/Mi[j+1-1]%3;
				if(A[i][j]){if(!L&&!U)add(s,v);}
				else if(!L&&!U)add(s+Mi[j-1]+2*Mi[j+1-1],v);
				else if(!L&&U)add(s,v),add(s+U*Mi[j-1]-U*Mi[j+1-1],v);
				else if(L&&!U)add(s,v),add(s-L*Mi[j-1]+L*Mi[j+1-1],v);
				else if(L==1&&U==1){
					Re cnt=1;
					for(Re k=j+2;k<=m;++k){
						if(s/Mi[k-1]%3==1)++cnt;
						else if(s/Mi[k-1]%3==2)--cnt;
						if(!cnt){add(s-Mi[j-1]-Mi[j+1-1]-Mi[k-1],v);break;}//2±ä1
					}
				}
				else if(L==2&&U==2){
					Re cnt=1;
					for(Re k=j-1;k>=1;--k){
						if(s/Mi[k-1]%3==1)--cnt;
						else if(s/Mi[k-1]%3==2)++cnt;
						if(!cnt){add(s-2*Mi[j-1]-2*Mi[j+1-1]+Mi[k-1],v);break;}//1±ä2
					}
				}
				else if(L==2&&U==1)add(s-2*Mi[j-1]-Mi[j+1-1],v);
				else if(L==1&&U==2)if(i==edx&&j==edy&&!(s-Mi[j-1]-2*Mi[j+1-1]))ans+=v;
			}
		}
	}
	printf("%lld\n",ans);
}
