#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=103,M=177147+3,P=20110520;
int n,m,o,V,Mi[N],A[N][N],A_[N][N],dp[2][M];char s[N];//0:û�в�ͷ 1:��û�չ��Ĳ�ͷ 2:�Ѿ��չ��Ĳ�ͷ
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void mo(Re &x){if(x>P)x-=P;}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(m);
	for(Re i=1;i<=n;++i){
		scanf("%s",s+1);
		for(Re j=1;j<=m;++j)A[i][j]=(s[j]=='*');
	}
	if(n<m){
		for(Re i=1;i<=n;++i)
			for(Re j=1;j<=m;++j)
				A_[j][i]=A[i][j];
		swap(n,m);
		for(Re i=1;i<=n;++i)
			for(Re j=1;j<=m;++j)
				A[i][j]=A_[i][j];
	}
	Mi[0]=1;for(Re i=1;i<=m+1;++i)Mi[i]=Mi[i-1]*3;
	V=Mi[m+1]-1,dp[o][0]=1;
	for(Re i=1;i<=n;++i){
		o^=1;
		for(Re s=0;s<=V;++s)dp[o][s]=s%3?0:dp[o^1][s/3];
		for(Re j=1;j<=m;++j){
			o^=1;
			for(Re s=0;s<=V;++s)dp[o][s]=0;
			for(Re s=0;s<=V;++s)if(dp[o^1][s]){
				Re L=s/Mi[j-1]%3,U=s/Mi[j+1-1]%3,ML=Mi[j-1],MU=Mi[j+1-1];
				if(A[i][j]){//�˴����ܷŲ�ͷ
					if(!L&&!U)mo(dp[o][s]+=dp[o^1][s]);
				}
				else{//�˴����ԷŲ�ͷ
					if(L==0&&U==0){
						mo(dp[o][s+ML]+=dp[o^1][s]);//��1
						mo(dp[o][s+MU]+=dp[o^1][s]);//��1
						mo(dp[o][s+2*ML+2*MU]+=dp[o^1][s]);//���¹�
					}
					if(L==0&&U==1){
						mo(dp[o][s+MU]+=dp[o^1][s]);//���Ϲգ�ԭ����1���2
						mo(dp[o][s+ML-MU]+=dp[o^1][s]);//��1
					}
					if(L==0&&U==2){
						mo(dp[o][s+2*ML-2*MU]+=dp[o^1][s]);//��2
						mo(dp[o][s-2*MU]+=dp[o^1][s]);//����һ������ֹ
					}
					if(L==1&&U==0){
						mo(dp[o][s+ML]+=dp[o^1][s]);//���¹գ�ԭ����1���2
						mo(dp[o][s-ML+MU]+=dp[o^1][s]);//��1
					}
					if(L==1&&U==1)mo(dp[o][s-ML-MU]+=dp[o^1][s]);//���Ϲգ�ԭ����1��Ϊ0
					if(L==1&&U==2);//�޷�����
					if(L==2&&U==0){
						mo(dp[o][s-2*ML+2*MU]+=dp[o^1][s]);//��2
						mo(dp[o][s-2*ML]+=dp[o^1][s]);//����һ������ֹ
					}
					if(L==2&&U==1);//�޷�����
					if(L==2&&U==2);//�޷�����
				}
			}
		}
	}
	printf("%d\n",dp[o][0]);
}
