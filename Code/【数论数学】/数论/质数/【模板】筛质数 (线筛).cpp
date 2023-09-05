#include<cstdio>
#include<ctime>
const int N=1e6;
int cnt,i,j,pri[N/3];bool pan[N+1];
inline void get_pri(){
	pan[0]=pan[1]=1;
	for(i=2;i<=N;++i){
		if(!pan[i])pri[++cnt]=i;
		for(j=1;j<=cnt&&i*pri[j]<=N;++j){
			pan[i*pri[j]]=1;
			if(i%pri[j]==0)break;
		}
	}
}
int main(){
	get_pri();
	for(j=0,i=1;i<=cnt;++i)printf("%d ",pri[i]);
}