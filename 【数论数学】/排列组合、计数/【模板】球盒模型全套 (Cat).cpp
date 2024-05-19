#include<cstdio>
#define LL long long
#define Re register LL
const int P=998244353,N=1e6+5;
LL T,a,b,f,opt,cnt,jc[N*2+5],dp[205][205],S[105][105];
inline void in(Re &x){
    x=f=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;
}
inline LL mi(Re x,Re k){
    Re ans=1;
    while(k){
        if(k&1)ans=(ans*x)%P;
        x=(x*x)%P;k>>=1;
    }
    return ans%P;
} 
inline LL niv(Re x){return mi(x,P-2);}
inline LL c(Re m,Re n){
    if(n<m)return 0;
    if(n<P)return jc[n]*niv(jc[m])%P*niv(jc[n-m])%P;
    return c(m/P,n/P)*c(m%P,n%P)%P;
}
inline void Stirling(){
    for(Re i=0;i<=100;++i)S[i][i]=1;
    for(Re i=1;i<=100;++i)
        for(Re j=1;j<=100;++j)
            S[i][j]=(S[i-1][j-1]+S[i-1][j]*j%P)%P;
}
inline void DP(){
    dp[0][0]=1;
    for(Re i=1;i<=200;++i)
        for(Re j=1;j<=i;++j)
            dp[i][j]=(dp[i-j][j]+dp[i-1][j-1])%P;
}
inline LL Catalan(Re n){return c(n,n<<1)*niv(n+1)%P;}
int main(){
//  freopen("cat.in","r",stdin);
//  freopen("cat.out","w",stdout);
    jc[0]=1;for(Re i=1;i<=N*2;i++)jc[i]=jc[i-1]*i%P;
    in(T);Stirling();DP();
    while(T--){
        in(opt),in(a),in(b);
        if(opt==1)printf("%lld\n",mi(b,a));
        else if(opt==2)printf("%lld\n",c(b-1,a-1));
        else if(opt==3)printf("%lld\n",c(b-1,a+b-1));
        else if(opt==4)printf("%lld\n",S[a][b]);
        else if(opt==5)printf("%lld\n",jc[b]*S[a][b]%P);
        else if(opt==6){
            Re ans=0;
            for(Re i=1;i<=b;++i)(ans+=S[a][i])%=P;
            printf("%lld\n",ans);
        }
        else if(opt==7)printf("%lld\n",dp[a+b][b]);
        else if(opt==8)printf("%lld\n",dp[a][b]);
        else if(opt==9)printf("%lld\n",Catalan(a));
    }
}
