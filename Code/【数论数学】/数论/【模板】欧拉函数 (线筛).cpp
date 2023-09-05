#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<cstdio>
const int N=1e6;
int cnt,i,j,pan[N+1],pri[N/3],phi[N+1];
inline void get_phi(int N){
    pan[1]=1,phi[1]=1;
    for(int i=2;i<=N;++i){
        if(!pan[i])pri[++cnt]=i,phi[i]=i-1;
        for(int j=1;j<=cnt&&pri[j]<=N/i;++j){
            pan[i*pri[j]]=1;
            if(i%pri[j])phi[i*pri[j]]=phi[i]*(pri[j]-1);
            else{phi[i*pri[j]]=phi[i]*pri[j];break;}
        }
    }
}
int main(){
	get_phi(N);
	for(i=1;i<=N;++i)printf("%d: %d\n",i,phi[i]);
}
