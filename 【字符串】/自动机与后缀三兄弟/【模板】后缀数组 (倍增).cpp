#include<algorithm>
#include<cstring>
#include<cstdio>
#define Re register int
#define LL long long
using namespace std;
const int N=1e6+3;
inline void in(Re &x){
    int fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
struct Suffix_Array{
	int n,m,x[N],y[N],H[N],SA[N],cnt[N],rank[N],Height[N];char s[N];
	//Suf[i]: s[i,n]
	//len: 已经求出了长度为len的串的排名 
	//x[i]: Suf[i]的排名 (排序第一关键字) (上一次排序后得到的rank[i])
	//y[i]: 按第len个字符排出来的顺序(排序第二关键字) (第二关键字排名为i的数的位置)
	//H[i]: H[i]=Height[rank[i]] 即 LCP(Suf[i],Suf[SA[rank[i]-1]]) 
	//SA[i]: 排名为i的后缀第一个字符所在位置 
	//cnt[i]: 第一关键字排名为 i(1~i)的数有多少个 
	//rank[i]: Suf[i]的排名 
	//Height[i]: Height[i]=H[SA[i]] 即 LCP(Suf[SA[i]],Suf[SA[i-1]])
	inline void get_SA(){
		m=128;
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
			
			swap(x,y);
			x[SA[1]]=m=1;//把旧的x存进了y并清零x
			for(Re i=2;i<=n;++i)
				x[SA[i]]=(y[SA[i]]==y[SA[i-1]]&&y[SA[i]+len]==y[SA[i-1]+len])?m:++m;//注意这里的SA[i]+len和SA[i-1]+len有可能访问到n+1,所以上面的N最好稍开大一点,不要尝试卡这点小常数空间
			if(m==n)break;
		}
		for(Re i=1;i<=n;++i)printf("%d ",SA[i]);
	}
	inline void get_Height(){
		for(Re i=1;i<=n;++i)rank[SA[i]]=i;
		for(Re i=1,k=0;i<=n;++i){
			if(rank[i]==1)continue;
			if(k)--k;//H[i-1]-1<=H[i]
			Re j=SA[rank[i]-1];
			while(i+k<=n&&j+k<=n&&s[i+k]==s[j+k])++k;
			Height[rank[i]]=k;
		}
//		for(Re i=1;i<=n;++i)printf("%d ",Height[i]);
	}
}SA;
int main(){
//	freopen("123.txt","r",stdin);
	scanf("%s",SA.s+1),SA.n=strlen(SA.s+1);
	SA.get_SA(),SA.get_Height();
}
