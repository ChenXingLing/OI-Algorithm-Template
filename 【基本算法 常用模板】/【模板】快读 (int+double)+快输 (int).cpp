#include<cstdio>
#define LD double
#define Re register int
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline void print(Re x){
	if(x<0)putchar('-'),x=-x;//注意-2^32会寄（具体见P4305） 
	if(x>9)print(x/10);putchar(x%10+'0');
}
inline LD LDin(){
	LD X=0,Y=1.0;int f=0;char c=getchar();
	while(c<'0'||c>'9')f|=c=='-',c=getchar(); 
	while(c>='0'&&c<='9')X=X*10+(c^48),c=getchar(); 
	if(c=='.'){c=getchar();while(c>='0'&&c<='9')X+=(Y/=10)*(c^48),c=getchar();}
	return f?-X:X;
}
int main(){}
