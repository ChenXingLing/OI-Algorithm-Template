#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
const int N=103,P=1e9+7;
int n;LL K;
template<typename T>inline void in(T &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Matrix{
	int a[N][N];
	Matrix(){memset(a,0,sizeof(a));}
	inline void read(){//读入
		for(Re i=1;i<=n;++i)
    		for(Re j=1;j<=n;++j)
    			in(a[i][j]);
	}
	inline void print(){//输出
		for(Re i=1;i<=n;puts(""),++i)
    		for(Re j=1;j<=n;++j)
    			printf("%d ",a[i][j]);
	}
	inline void Identity(){//单位矩阵 
		memset(a,0,sizeof(a));
		for(Re i=1;i<=n;++i)a[i][i]=1;
	}
	inline Matrix operator*(const Matrix &O)const{
		Matrix ans;
		for(Re i=1;i<=n;++i)
			for(Re j=1;j<=n;++j)
				for(Re k=1;k<=n;++k)
					(ans.a[i][j]+=(LL)a[i][k]*O.a[k][j]%P)%=P;
		return ans;
	}
	inline Matrix operator*=(Matrix &O){return *this=*this*O;}
}A;
inline Matrix mi(Matrix x,LL k){
	Matrix s;s.Identity();//初始化为0次方的单位矩阵
	while(k){
		if(k&1)s*=x;
		x*=x,k>>=1;
	}
	return s;
}
int main(){
	in(n),in(K),A.read(),mi(A,K).print();
}
