#include<cstdio>
#define LL long long
#define Re register int
int a,b,P;
inline int cf_flow(Re a,Re k){//分治 龟速乘
	if(!k)return 0;
	Re x=1,y=cf_flow(a,k>>1);
	x=(LL)y+y%P;
	if(k&1)x=(LL)x+a%P;
	return x%P;
}
inline int cf(Re a,Re b){//按进制分 龟速乘 
	Re x=0;
	while(b){
		if(b&1)x=(x+a)%P;
		a=a*2%P,b>>=1;
	}
	return x%P;
}
inline int mi_slow(Re a,Re k){//分治 快速幂 
	if(!k)return 1%P;
	Re x=1,y=mi_slow(a,k>>1);
	x=(LL)y*y%P;
	if(k&1)x=(LL)x*a%P;
	return x%P;
}
inline int mi(Re x,Re k){//按进制分 快速幂 
	Re s=1;
    while(k){
    	if(k&1)s=(LL)s*x%P;
    	x=(LL)x*x%P,k>>=1;
    }
    return s%P;
}
int main(){}
