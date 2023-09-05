#include<algorithm>
#include<cstdio>
using namespace std;
int x,a,b,c,d,T,n,i,j,t,f[1010],v[100010],w[100010];
int main(){
	scanf("%d:%d%d:%d%d",&a,&b,&c,&d,&n);
	T=c*60+d-a*60-b;
	for(i=1;i<=n;i++){
		scanf("%d%d%d",&a,&b,&c);
		if(!c){
			for(j=a;j<=T;j++)
				f[j]=max(f[j],f[j-a]+b);
			continue;
		}
		int p=1;
		while(c>=p){v[++t]=p*a,w[t]=p*b,c-=p,p<<=1;}
		v[++t]=c*a,w[t]=c*b;
	}
	for(i=1;i<=t;i++)
		for(j=T;j>=v[i];j--)
			f[j]=max(f[j],f[j-v[i]]+w[i]);
	printf("%d",f[T]);
	return 0;
}
