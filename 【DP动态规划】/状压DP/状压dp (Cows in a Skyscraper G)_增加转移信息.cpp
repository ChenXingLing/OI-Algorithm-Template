#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1003,M=262144;
int n,K,V,A[N],g[M],f[M];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(K),V=(1<<n)-1;
	for(Re i=1;i<=n;++i)in(A[i]);
	memset(f,59,sizeof(f)),memset(g,59,sizeof(g));
	f[0]=1,g[0]=0;//g[j]��ʾѡ��j�����ŷ����У����һ��ʹ�õ���С���
	for(Re j=0;j<V;++j)
		for(Re i=1;i<=n;++i)if(!((j>>i-1)&1)){
			Re k=j|(1<<i-1);
			if(g[j]+A[i]<=K&&f[j]<=f[k]){//�������i�������������f[j]ת�ƹ�����f[k]���� 
				f[k]=f[j];
				if(f[j]<f[k])g[k]=g[j]+A[i];//����ϸ���ţ��Ͳ���f[j]�ķ��鷽��������A[i]�ӽ�f[j]�����һ���� 
				else g[k]=min(g[k],g[j]+A[i]);//���һ�����㣬��ѡ�����һ��ʹ�������С�ķ��� 
			}
			if(g[j]+A[i]>K&&f[j]+1<=f[k]){//�������i������ˣ���f[j]��һ���µ�ת�ƹ�����f[k]���� 
				f[k]=f[j]+1;
				if(f[j]+1<f[k])g[k]=A[i];
				else g[k]=min(g[k],A[i]);
			}
		}
	printf("%d\n",f[V]);
}
