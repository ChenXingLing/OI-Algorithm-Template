#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<cstdio>
const int N=1e7+3;
int i,j,n,cnt,pri[N>>1],pan[N],miu[N];
inline void get_miu(){
	pan[1]=1,miu[1]=1;
	for(i=2;i<=n;++i){
		if(!pan[i])pri[++cnt]=i,miu[i]=-1;
		for(j=1;j<=cnt&&i*pri[j]<=n;++j){
            pan[i*pri[j]]=1;
            if(i%pri[j])miu[i*pri[j]]=-miu[i];
            else{miu[i*pri[j]]=0;break;}
        }
	}
}
int main(){
	n=N;
	get_miu();
	for(i=1;i<=n;++i)printf("%d: %d\n",i,miu[i]);
}
