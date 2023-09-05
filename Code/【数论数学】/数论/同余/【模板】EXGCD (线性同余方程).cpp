#include<cstdio>
#define Re register int
int a,b,x,y;
inline void exgcd(Re a,Re b,Re &x,Re &y){
	if(!b){x=1,y=0;return;}
	exgcd(b,a%b,x,y);Re x0=x,y0=y;
	x=y0,y=x0-a/b*y0;return;
}
int main(){
    scanf("%d%d",&a,&b),exgcd(a,b,x,y);
	printf("%d\n",(x%b+b)%b);
}
