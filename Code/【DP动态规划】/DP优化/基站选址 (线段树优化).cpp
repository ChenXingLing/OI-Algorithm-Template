#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
#define LL long long
#define Re register int
using namespace std;
const LL N=2e4+3,inf=1e18;
int n,K,L[N],R[N],D[N],C[N],W[N],S[N];LL ans=inf,dp[N];vector<int>V[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline LL calc(Re j,Re i){
	LL ans=0;
	for(Re k=j+1;k<i;++k)if(L[k]>j&&R[k]<i)ans+=W[k];
	return ans;
}
struct Segment_Tree{
	#define pl (p<<1)
	#define pr (p<<1|1)
	#define mid ((L+R)>>1)
	LL tr[N<<2],add[N<<2];
	inline void updata(Re p,LL v){tr[p]+=v,add[p]+=v;}
	inline void pushdown(Re p){
		if(add[p])updata(pl,add[p]),updata(pr,add[p]),add[p]=0;
	}
	inline void build(Re p,Re L,Re R){
		add[p]=0;
		if(L==R){tr[p]=dp[L];return;}
		build(pl,L,mid),build(pr,mid+1,R);
		tr[p]=min(tr[pl],tr[pr]);
	}
	inline void change(Re p,Re L,Re R,Re l,Re r,Re v){
		if(l<=L&&R<=r){updata(p,v);return;}
		pushdown(p);
		if(l<=mid)change(pl,L,mid,l,r,v);
		if(r>mid)change(pr,mid+1,R,l,r,v);
		tr[p]=min(tr[pl],tr[pr]);
	}
	inline void change(Re p,Re L,Re R,Re x,Re v){
		if(L==R){tr[p]+=v;return;}
		pushdown(p);
		if(x<=mid)change(pl,L,mid,x,v);
		else change(pr,mid+1,R,x,v);
		tr[p]=min(tr[pl],tr[pr]);
	}
	inline LL ask(Re p,Re L,Re R,Re l,Re r){
		if(l<=L&&R<=r)return tr[p];
		LL ans=inf;pushdown(p);
		if(l<=mid)ans=min(ans,ask(pl,L,mid,l,r));
		if(r>mid)ans=min(ans,ask(pr,mid+1,R,l,r));
		return ans; 
	}
	#undef mid
}TR;
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(K);
	for(Re i=2;i<=n;++i)in(D[i]);
	for(Re i=1;i<=n;++i)in(C[i]);
	for(Re i=1;i<=n;++i){
		in(S[i]);
		Re l=1,r=i;
		while(l<r){
			Re mid=l+r>>1;
			if(D[mid]>=D[i]-S[i])r=mid;
			else l=mid+1;
		}
		L[i]=r;
		l=i,r=n;
		while(l<r){
			Re mid=l+r+1>>1;
			if(D[mid]<=D[i]+S[i])l=mid;
			else r=mid-1;
		}
		R[i]=l,V[R[i]].push_back(i);
	}
	for(Re i=1;i<=n;++i)in(W[i]);
	memset(dp,20,sizeof(dp));
	dp[0]=0,D[0]=-1e9,C[n+1]=0;
	for(Re k=1;k<=K;++k){
		TR.build(1,0,n);
		for(Re i=1;i<=n+1;++i){
			LL tmp=dp[i];
			dp[i]=min(dp[i],TR.ask(1,0,n,0,i-1)+C[i]);
			for(Re j=0,SZ=V[i].size();j<SZ;++j)TR.change(1,0,n,0,L[V[i][j]]-1,W[V[i][j]]);
			if(dp[i]!=tmp)TR.change(1,0,n,i,dp[i]-tmp);
		}
		ans=min(ans,dp[n+1]);
	}
	printf("%lld\n",ans);
}
