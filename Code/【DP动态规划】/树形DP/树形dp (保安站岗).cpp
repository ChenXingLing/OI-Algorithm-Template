#include<algorithm>
#include<cstring>
#include<cstdio>
#define R register int
using namespace std;
struct QAQ{int to,next;}a[1505]; 
int m,fa[1505],n,o,w[1505],dp[1505][3],head[1505];
inline void add(int x,int y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
  //dp[i][0] �Լ��������������������� 
 //dp[i][1] �Լ�������
//dp[i][2] �Լ��������������������� 
inline void dfs(int x){
    R i,to,dd=0xfffffff;
    dp[x][1]=w[x];dp[x][2]=0;dp[x][0]=0;
    for(i=head[x];i;i=a[i].next){
        dfs(to=a[i].to);
        dp[x][1]+=min(dp[to][2],dp[to][1]);
    //��x�Լ���������dp[x][1]��:���϶��� min(1.to�����׿���dp[to][2]; 2.to�Լ��ǿ���dp[to][1]) 
        dp[x][2]+=min(dp[to][0],dp[to][1]);
    //��x�����׿��أ�dp[x][2]�������϶��� min(1.to�����ӿ���dp[to][0]; 2.to�Լ��ǿ���dp[to][1])
        dp[x][0]+=min(dp[to][0],dp[to][1]);
    //��x�����ӿ��أ�dp[x][0]��:�ҵ������������軨����С�Ķ���dd�����������Ķ��� min(1.to�����ӿ���dp[to][0]; 2.to�Լ��ǿ���dp[to][1]) 
		dd=min(dd,dp[to][1]-min(dp[to][0],dp[to][1]));//ά����С�Ĳ�ֵ  
    }
    dp[x][0]+=dd;
}
int main(){
	memset(dp,127,sizeof(dp));
    scanf("%d",&n);
    R i,j,a,k,r;
    for(i=1;i<=n;i++){
        scanf("%d%d%d",&a,&k,&m);w[a]=k;
        for(j=1;j<=m;j++)scanf("%d",&r),fa[r]=1,add(a,r);
    }
    for(i=1;i<=n;i++)
        if(!fa[i]){
            dfs(i);
            printf("%d",min(dp[i][1],dp[i][0]));
            return 0;
        }
}
