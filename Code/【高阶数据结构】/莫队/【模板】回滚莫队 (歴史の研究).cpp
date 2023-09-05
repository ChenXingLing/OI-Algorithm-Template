#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3,M=1e5+3;
int n,m,T,BL,BLN,A[N],b[N],Li[325],Ri[325],cnt[N],cnt_[N],belong[N];LL Ans[M];
struct Query{
	int l,r,id;
	inline bool operator<(const Query &O)const{
		Re B1=belong[l],B2=belong[O.l];
		return B1!=B2?B1<B2:r<O.r;
	}
}Q[M];
inline void in(Re &x){
    Re fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(T),BL=sqrt(n)+1,BLN=n/BL+1;
	for(Re i=1;i<=BLN;++i){
		Li[i]=(i-1)*BL+1,Ri[i]=min(i*BL,n);
		for(Re j=Li[i];j<=Ri[i];++j)belong[j]=i;
	}
	for(Re i=1;i<=n;++i)in(A[i]),b[i]=A[i];
	sort(b+1,b+n+1),m=unique(b+1,b+n+1)-b-1;
	for(Re i=1;i<=n;++i)A[i]=lower_bound(b+1,b+m+1,A[i])-b;
	for(Re i=1;i<=T;++i)in(Q[i].l),in(Q[i].r),Q[i].id=i;
	sort(Q+1,Q+T+1);Re i=1;
	for(Re p=1;p<=BLN;++p){
		Re nowL=Ri[p]+1,nowR=Ri[p];LL ans=0;
		memset(cnt,0,sizeof(cnt));
		while(belong[Q[i].l]==p){
			Re L=Q[i].l,R=Q[i].r;
			if(belong[L]==belong[R]){
				LL tmp=0;
				for(Re j=L;j<=R;++j)cnt_[A[j]]=0;
				for(Re j=L;j<=R;++j)++cnt_[A[j]],tmp=max(tmp,(LL)b[A[j]]*cnt_[A[j]]);
				Ans[Q[i].id]=tmp;
			}
			else{
				while(nowR<R)cnt[A[++nowR]]++,ans=max(ans,(LL)b[A[nowR]]*cnt[A[nowR]]);
				LL tmp=ans;
				while(nowL>L)cnt[A[--nowL]]++,tmp=max(tmp,(LL)b[A[nowL]]*cnt[A[nowL]]);
				Ans[Q[i].id]=tmp;
				while(nowL<Ri[p]+1)--cnt[A[nowL++]];
			}
			++i;
		}
	}
	for(Re i=1;i<=T;++i)printf("%lld\n",Ans[i]);
}
