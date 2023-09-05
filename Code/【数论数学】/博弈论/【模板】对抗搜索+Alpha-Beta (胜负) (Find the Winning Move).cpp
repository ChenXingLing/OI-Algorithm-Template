#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=6,inf=2e9;
int n=4,cnt,ansX,ansY,A[N][N];char op[5],s[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline int check(Re op){//检查op是否胜利
	for(Re i=1;i<=n;++i){
		Re cnt1=0,cnt2=0;//行、列
		for(Re j=1;j<=n;++j)cnt1+=(A[i][j]==op),cnt2+=(A[j][i]==op);
		if(cnt1==4||cnt2==4)return 1;
	}
	Re cnt1=0,cnt2=0;//对角线
	for(Re i=1;i<=n;++i)cnt1+=(A[i][i]==op),cnt2+=(A[i][n-i+1]==op);
	if(cnt1==4||cnt2==4)return 1;
	return 0;
}
inline int findmin(Re alpha,Re op);//[op=0:对手的回合]
inline int findmax(Re beta,Re op);//[op=1:我的回合]
inline int findmin(Re alpha,Re op){//对手想让我尽量小（对手想让我输）
	if(cnt==16)return 0;//和棋
	if(check(op^1))return inf;//我达到最大分数（我连成了，我赢）
	Re ans=inf;//准备一个最坏情况（对于对手来说）
	for(Re i=1;i<=n;++i)
		for(Re j=1;j<=n;++j)
			if(A[i][j]==-1){
				A[i][j]=op,++cnt;
				ans=min(ans,findmax(ans,op^1));//在我的完美策略（让我尽量大）中取一个最小的
				A[i][j]=-1,--cnt;
				if(ans<=alpha)return ans;
				//如果当前算出来的最小已经超过了下限alpha（超过了上一层的findmax中已算出的最大）
				//那么继续做下去的话也一定不会对上一层的findmax产生贡献了
			}
	return ans;
}
inline int findmax(Re beta,Re op){//我想尽量大（我想让我赢）
	if(cnt==16)return 0;//和棋
	if(check(op^1))return -inf;//我达到最小分数（对手连成了，我输）
	Re ans=-inf;//准备一个最坏情况（对于我来说）
	for(Re i=1;i<=n;++i)
		for(Re j=1;j<=n;++j)
			if(A[i][j]==-1){
				A[i][j]=op,++cnt;
				ans=max(ans,findmin(ans,op^1));//在对手的完美策略（让我尽量小）中取一个最大的
				A[i][j]=-1,--cnt;
				ansX=i,ansY=j;//本题的特殊性：记录第一步选择的位置
				if(ans>=beta)return ans;
				//如果当前算出来的最大已经超过了上限beta（超过了上一层的findmin中已算出的最小）
				//那么继续做下去的话也一定不会对上一层的findmin产生贡献了
			}
	return ans;
}
int main(){
//	freopen("123.txt","r",stdin);
	while(~scanf("%s",op)&&op[0]!='$'){
		cnt=0;
		for(Re i=1;i<=n;++i){
			scanf("%s",s+1);
			for(Re j=1;j<=n;++j)
				if(s[j]=='.')A[i][j]=-1,++cnt;
				else A[i][j]=(s[j]=='x');
		}
		if(cnt<=4)puts("#####");//当已有棋子不足4个时必定和局
		else if(findmax(inf,1)==inf)printf("(%d,%d)\n",ansX-1,ansY-1);//我达到最大（我赢）
		else puts("#####");//我达到最小（我输）
	}
}
