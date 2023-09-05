#pragma comment(linker, "/STACK:102400000,102400000")
#include<cstdio>
#define Re register int
const int N=1e6+3;
#define LL long long
int n,m,x,y,o=1,h,t,st,cnt,In[N],cir[N],pan[N],head[N];LL ans,tmp,Q[N<<1],S[N<<1],dp[N<<1],dis[N];
struct QAQ{int w,to,next;}a[N<<1];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void add(Re x,Re y,Re z){a[++o].w=z,a[o].to=y,a[o].next=head[x],head[x]=o;}
inline LL max(LL a,LL b){return a>b?a:b;}
inline int find_circle(Re x,Re p){
	if(In[x]){st=x,cir[++cnt]=x,pan[x]=1;return 1;}
	In[x]=1;
	for(Re i=head[x];i;i=a[i].next)
		if(i!=(p^1)&&find_circle(a[i].to,i)){
			pan[x]=1;
			if(x==st){S[0]=S[1]-a[i].w;return 0;}
			cir[++cnt]=x,S[cnt]=S[cnt-1]+a[i].w;
			return 1;
		}
	return 0;
}
inline void Tree_dp(Re x){
	pan[x]=1;
	for(Re i=head[x],to;i;i=a[i].next)
		if(!pan[to=a[i].to]){
			Tree_dp(to);
			tmp=max(tmp,dis[x]+a[i].w+dis[to]);
			dis[x]=max(dis[x],dis[to]+a[i].w);
		}
}
inline LL pp(Re j){return dp[j]-S[j];}
inline LL sakura(Re root){
	S[0]=cnt=st=0;find_circle(root,0);
	LL ans1=0,ans2=0;tmp=0;
	for(Re i=1;i<=cnt;++i){
		tmp=0,Tree_dp(cir[i]),ans1=max(ans1,tmp);
		dp[i+cnt]=dp[i]=dis[cir[i]];
		S[i+cnt]=S[i+cnt-1]+S[i]-S[i-1];
	}
	h=1,t=0,Q[++t]=1;//ans=max(dp[i]+dp[j]+S[i]-S[j]) i-j+1<=cnt i-cnt+1<=j<i
	for(Re i=2;i<=(cnt<<1);++i){
		while(h<=t&&Q[h]<i-cnt+1)++h;
		if(h<=t)ans2=max(ans2,dp[i]+S[i]+pp(Q[h]));
		while(h<=t&&pp(Q[t])<=pp(i))--t;
		Q[++t]=i;
	}
	return max(ans1,ans2);
}
int main(){
	in(n);
	for(Re i=1;i<=n;++i)in(x),in(y),add(i,x,y),add(x,i,y);
	for(Re i=1;i<=n;++i)if(!pan[i])ans+=sakura(i);
	printf("%lld",ans);
}