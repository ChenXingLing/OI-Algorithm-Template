#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
int n,T,P,W,det;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline int mi(Re x,Re k){
	Re s=1;
	while(k){
		if(k&1)s=(LL)s*x%P;
		x=(LL)x*x%P,k>>=1;
	}
	return s;
}
struct CP{
	int x,y;CP(Re X=0,Re Y=0){x=X,y=Y;}
	inline CP operator*(const CP &O)const{return CP(((LL)x*O.x%P+(LL)y*O.y%P*W%P)%P,((LL)x*O.y%P+(LL)y*O.x%P)%P);}
	inline CP operator*=(const CP &O){return *this=*this*O;}
};
inline CP mi_(CP x,Re k){
	CP s=CP(1,0);
	while(k){
		if(k&1)s*=x;
		x*=x,k>>=1;
	}
	return s;
}
inline LL Sqrt(Re n){
    if(!n)return 0;Re x;
    while(1){
        x=rand()%P,W=((LL)x*x%P-n+P)%P;
        if(mi(W,(P-1)/2)==P-1)break;
    }
    return mi_(CP(x,1),(P+1)/2).x;
}
int main(){
//	freopen("123.txt","r",stdin);
	in(T);
	while(T--){
		in(n),in(P);
		if(mi(n,(P-1)/2)==P-1)puts("Hola!");//无解
	    else{
		    det=Sqrt(n);
		    if(det)printf("%d %d\n",min(det,P-det),max(det,P-det));//两解
		    else printf("%d\n",det);//单解
		}
	}
}
