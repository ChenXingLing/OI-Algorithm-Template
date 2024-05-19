#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=3e5+5,logN=19;
int n;char s[N];
inline void in(Re &x){
    Re f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Suffix_Array{
	int m,x[N],y[N],SA[N],cnt[N],rank[N],Height[N];
	inline void get_SA(){
		m=129;
		for(Re i=1;i<=n;++i)++cnt[x[i]=s[i]];
		for(Re i=2;i<=m;++i)cnt[i]+=cnt[i-1];
		for(Re i=n;i>=1;--i)SA[cnt[x[i]]--]=i;
		for(Re len=1;len<=n;len<<=1){
			Re t=0;
			for(Re i=n-len+1;i<=n;++i)y[++t]=i;
			for(Re i=1;i<=n;++i)if(SA[i]>len)y[++t]=SA[i]-len;
			for(Re i=1;i<=m;++i)cnt[i]=0;
			for(Re i=1;i<=n;++i)++cnt[x[i]];
			for(Re i=2;i<=m;++i)cnt[i]+=cnt[i-1];
			for(Re i=n;i>=1;--i)SA[cnt[x[y[i]]]--]=y[i],y[i]=0;
			swap(x,y),x[SA[1]]=m=1;
			for(Re i=2;i<=n;++i)
				x[SA[i]]=(y[SA[i]]==y[SA[i-1]]&&y[SA[i]+len]==y[SA[i-1]+len])?m:++m;
			if(m>=n)break;
		}
	}
	inline void get_Height(){
		for(Re i=1;i<=n;++i)rank[SA[i]]=i;
		for(Re i=1,k=0;i<=n;++i){
			if(rank[i]==1)continue;
			if(k)--k;
			Re j=SA[rank[i]-1];
			while(i+k<=n&&j+k<=n&&s[i+k]==s[j+k])++k;
			Height[rank[i]]=k;
		}
//		for(Re i=1;i<=n;++i)printf("%d ",Height[i]);puts("");
	}
	int lg[N],dp[N][20];
	inline void get_ST(){
		lg[0]=-1;
		for(Re i=1;i<=n;++i)dp[i][0]=Height[i],lg[i]=lg[i>>1]+1;
		for(Re j=1;j<=logN;++j)
			for(Re i=1;i+(1<<j)-1<=n;++i)
				dp[i][j]=min(dp[i][j-1],dp[i+(1<<j-1)][j-1]);
	}
	inline int ask_min(Re l,Re r){
		Re m=lg[r-l+1];
		return min(dp[l][m],dp[r-(1<<m)+1][m]);
	}
	int r[N<<1];char a[N<<1];LL ans;
	inline void check(Re x,Re len){
//		printf("x=%d, len=%d\n",x,len);
		x=rank[x];Re L=x,R=x;
		if(Height[x]>=len){
			Re l=2,r=x;
			while(l<r){
				Re mid=l+r>>1;
				if(ask_min(mid,x)>=len)r=mid;
				else l=mid+1;
			}
			L=r-1;
		}
		if(Height[x+1]>=len){
			Re l=x+1,r=n;
			while(l<r){
				Re mid=l+r+1>>1;
				if(ask_min(x+1,mid)>=len)l=mid;
				else r=mid-1;
			}
			R=l;
		}
		ans=max(ans,(LL)len*(R-L+1));
	}
	inline void sakura(){
		get_SA(),get_Height(),get_ST();
		a[m=0]='$',a[++m]='|';
		for(Re i=1;i<=n;++i)a[++m]=s[i],a[++m]='|';
		for(Re i=1,R=0,mid=0;i<=m;++i){
			r[i]=i<=R?min(r[(mid<<1)-i],R-i+1):1;
			while(a[i-r[i]]==a[i+r[i]]){
				++r[i];
				if(i+r[i]-1>R)check((i>>1)-(r[i]>>1)+1,r[i]-!(i+r[i]&1));//如果i与r[i]奇偶性相同则长度为r[i]-1否则为r[i]
			}
			if(i+r[i]-1>R)mid=i,R=i+r[i]-1;
		}
//		for(Re i=1;i<=m;++i)printf("%d ",r[i]);puts("");
		printf("%lld\n",ans);
	}
}SA;
int main(){
//	freopen("123.txt","r",stdin);
//	freopen("my.txt","w",stdout);
	scanf("%s",s+1),n=strlen(s+1),SA.sakura();
}
