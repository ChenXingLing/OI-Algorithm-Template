#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#define LD double
#define LL long long
#define Re register int
using namespace std;
const int N=2097152+5;
const LD Pi=acos(-1);
int n,m,tr[N],Ans[N];char s1[N>>1],s2[N>>1];
inline void in(Re &x){
	Re fu=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=fu?-x:x;
}
struct CP{
	LD x,y;
	CP(LD X=0,LD Y=0){x=X,y=Y;}
	inline CP operator+(const CP &O)const{return CP(x+O.x,y+O.y);}
	inline CP operator-(const CP &O)const{return CP(x-O.x,y-O.y);}
	inline CP operator*(const CP &O)const{return CP(x*O.x-y*O.y,x*O.y+y*O.x);}
	inline CP operator*=(const CP &O){return *this=*this*O;}
}f[N],g[N];
inline void FFT(CP *f,Re n,Re op){
	for(Re i=0;i<n;++i)if(i<tr[i])swap(f[i],f[tr[i]]);
	for(Re p=2;p<=n;p<<=1){
		Re len=p>>1;
		CP w1(cos(2*Pi/p),sin(2*Pi/p));
		if(op)w1.y*=-1;
		for(Re st=0;st<n;st+=p){
			CP base(1,0);
			for(Re i=st;i<=st+len-1;++i){
				CP tmp=f[len+i]*base;
				f[len+i]=f[i]-tmp,f[i]=f[i]+tmp,base*=w1;
			}
		}
	}
}
int main(){
//	freopen("123.txt","r",stdin);
	scanf("%s%s",s1,s2),n=strlen(s1),m=strlen(s2);
	for(Re i=0;i<n;++i)f[i].x=s1[n-i-1]-'0';
	for(Re i=0;i<m;++i)g[i].x=s2[m-i-1]-'0';
	for(m+=n,n=1;n<=m;n<<=1);
	for(Re i=1;i<n;++i)tr[i]=(tr[i>>1]>>1)|((i&1)?n>>1:0);
	FFT(f,n,0),FFT(g,n,0);
	for(Re i=0;i<n;++i)f[i]*=g[i];
	FFT(f,n,1);
	for(Re i=0;i<=m;++i){
		Ans[i]+=(int)(f[i].x/n+0.5);
		if(Ans[i]>9)Ans[i+1]+=Ans[i]/10,Ans[i]%=10,m+=(i==m);
	}
	while(!Ans[m]&&m>=1)--m;
	for(Re i=m;i>=0;--i)printf("%d",Ans[i]);
}
