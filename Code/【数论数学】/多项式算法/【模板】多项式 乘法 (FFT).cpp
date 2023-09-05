#include<algorithm>
#include<cstdio>
#include<cmath>
#define LD double
#define LL long long
#define Re register int
using namespace std;
const int N=2097152+3;
const LD Pi=acos(-1);
int n,m,tr[N];
inline void in(Re &x){
	Re fu=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=fu?-x:x;
}
struct CP{
	LD x,y;CP(LD X=0,LD Y=0){x=X,y=Y;}
	inline CP operator+(const CP &O)const{return CP(x+O.x,y+O.y);}
	inline CP operator-(const CP &O)const{return CP(x-O.x,y-O.y);}
	inline CP operator*(const CP &O)const{return CP(x*O.x-y*O.y,x*O.y+y*O.x);}//(ac-bd,bc+ad)
	inline CP operator/(const CP &O)const{
		LD tmp=O.x*O.x+O.y*O.y;//tmp=c^2+d^2
		return CP((x*O.x+y*O.y)/tmp,(y*O.x-x*O.y)/tmp);//( (ac+bd)/tmp,(bc-ad)/tmp )
	}
	inline CP operator*=(const CP &O){return *this=*this*O;}
}f[N],g[N];
inline void FFT(CP *f,Re n,Re op){//op=0:DFT, op=1:IDFT
	for(Re i=0;i<n;++i)if(i<tr[i])swap(f[i],f[tr[i]]);
	for(Re p=2;p<=n;p<<=1){
		Re len=p>>1;CP w1(cos(2*Pi/p),sin(2*Pi/p));
		if(op)w1.y*=-1;
		for(Re st=0;st<n;st+=p){
			CP base(1,0);
			for(Re i=st;i<=st+len-1;++i){
				CP tmp=base*f[len+i];
				f[len+i]=f[i]-tmp,f[i]=f[i]+tmp,base*=w1;
			}
		}
	}
}
inline void times(CP *f,Re n,CP *g,Re m){
	for(m+=n,n=1;n<=m;n<<=1);
	for(Re i=1;i<n;++i)tr[i]=(tr[i>>1]>>1)|((i&1)?n>>1:0);
	FFT(f,n,0),FFT(g,n,0);
	for(Re i=0;i<n;++i)f[i]*=g[i];
	FFT(f,n,1);
	for(Re i=0;i<=m;++i)f[i].x/=n;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(n),in(m);
	for(Re i=0;i<=n;++i)scanf("%lf",&f[i].x);
	for(Re i=0;i<=m;++i)scanf("%lf",&g[i].x);
	times(f,n,g,m);
	for(Re i=0;i<=n+m;++i)printf("%d ",(int)(f[i].x+0.5));
}
