#include<cstdio>
const int N=1e6+10;
int cnt,a,n=N-10,T,phi[N],pan[N],pri[N/3];
inline void get_phi(){
	phi[1]=1;
    for(int i=2;i<=n;i++)if(!phi[i]){
    	for(int j=i;j<=n;j+=i){
            if(!phi[j])phi[j]=j;
            phi[j]=phi[j]/i*(i-1);
        }
    }
}
int main(){
	get_phi();
	for(int i=1;i<=n;++i)printf("%d: %d\n",i,phi[i]);
}
