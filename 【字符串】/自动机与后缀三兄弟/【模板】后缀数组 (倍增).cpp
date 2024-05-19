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
	//len: �Ѿ�����˳���Ϊlen�Ĵ������� 
	//x[i]: Suf[i]������ (�����һ�ؼ���) (��һ�������õ���rank[i])
	//y[i]: ����len���ַ��ų�����˳��(����ڶ��ؼ���) (�ڶ��ؼ�������Ϊi������λ��)
	//H[i]: H[i]=Height[rank[i]] �� LCP(Suf[i],Suf[SA[rank[i]-1]]) 
	//SA[i]: ����Ϊi�ĺ�׺��һ���ַ�����λ�� 
	//cnt[i]: ��һ�ؼ�������Ϊ i(1~i)�����ж��ٸ� 
	//rank[i]: Suf[i]������ 
	//Height[i]: Height[i]=H[SA[i]] �� LCP(Suf[SA[i]],Suf[SA[i-1]])
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
			x[SA[1]]=m=1;//�Ѿɵ�x�����y������x
			for(Re i=2;i<=n;++i)
				x[SA[i]]=(y[SA[i]]==y[SA[i-1]]&&y[SA[i]+len]==y[SA[i-1]+len])?m:++m;//ע�������SA[i]+len��SA[i-1]+len�п��ܷ��ʵ�n+1,���������N����Կ���һ��,��Ҫ���Կ����С�����ռ�
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
