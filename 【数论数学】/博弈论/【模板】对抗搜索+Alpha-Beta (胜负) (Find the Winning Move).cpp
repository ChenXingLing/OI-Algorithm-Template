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
inline int check(Re op){//���op�Ƿ�ʤ��
	for(Re i=1;i<=n;++i){
		Re cnt1=0,cnt2=0;//�С���
		for(Re j=1;j<=n;++j)cnt1+=(A[i][j]==op),cnt2+=(A[j][i]==op);
		if(cnt1==4||cnt2==4)return 1;
	}
	Re cnt1=0,cnt2=0;//�Խ���
	for(Re i=1;i<=n;++i)cnt1+=(A[i][i]==op),cnt2+=(A[i][n-i+1]==op);
	if(cnt1==4||cnt2==4)return 1;
	return 0;
}
inline int findmin(Re alpha,Re op);//[op=0:���ֵĻغ�]
inline int findmax(Re beta,Re op);//[op=1:�ҵĻغ�]
inline int findmin(Re alpha,Re op){//���������Ҿ���С�������������䣩
	if(cnt==16)return 0;//����
	if(check(op^1))return inf;//�Ҵﵽ���������������ˣ���Ӯ��
	Re ans=inf;//׼��һ�����������ڶ�����˵��
	for(Re i=1;i<=n;++i)
		for(Re j=1;j<=n;++j)
			if(A[i][j]==-1){
				A[i][j]=op,++cnt;
				ans=min(ans,findmax(ans,op^1));//���ҵ��������ԣ����Ҿ�������ȡһ����С��
				A[i][j]=-1,--cnt;
				if(ans<=alpha)return ans;
				//�����ǰ���������С�Ѿ�����������alpha����������һ���findmax������������
				//��ô��������ȥ�Ļ�Ҳһ���������һ���findmax����������
			}
	return ans;
}
inline int findmax(Re beta,Re op){//���뾡������������Ӯ��
	if(cnt==16)return 0;//����
	if(check(op^1))return -inf;//�Ҵﵽ��С���������������ˣ����䣩
	Re ans=-inf;//׼��һ����������������˵��
	for(Re i=1;i<=n;++i)
		for(Re j=1;j<=n;++j)
			if(A[i][j]==-1){
				A[i][j]=op,++cnt;
				ans=max(ans,findmin(ans,op^1));//�ڶ��ֵ��������ԣ����Ҿ���С����ȡһ������
				A[i][j]=-1,--cnt;
				ansX=i,ansY=j;//����������ԣ���¼��һ��ѡ���λ��
				if(ans>=beta)return ans;
				//�����ǰ�����������Ѿ�����������beta����������һ���findmin�����������С��
				//��ô��������ȥ�Ļ�Ҳһ���������һ���findmin����������
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
		if(cnt<=4)puts("#####");//���������Ӳ���4��ʱ�ض��;�
		else if(findmax(inf,1)==inf)printf("(%d,%d)\n",ansX-1,ansY-1);//�Ҵﵽ�����Ӯ��
		else puts("#####");//�Ҵﵽ��С�����䣩
	}
}
