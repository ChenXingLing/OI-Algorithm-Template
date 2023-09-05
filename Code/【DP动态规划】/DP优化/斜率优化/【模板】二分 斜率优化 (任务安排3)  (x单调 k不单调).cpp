#include<cstring>
#include<cstdio>
#define LL long long
#define Re register LL
const int N=3e5+5;
LL i,j,n,h=1,t=0,S,Q[N],ST[N],SF[N],dp[N];
//dp[p][i]=min(dp[p-1][j]+(ST[i]+S*p)*(SF[i]-SF[j]));
//dp[i]=dp[j]+ST[i]*(SF[i]-SF[j])+S*(SF[n]-SF[j]);
//(S+ST[i]) * SF[j] + (dp[i]-ST[i]*SF[i]-S*SF[i]) = (dp[j])
//    k     *   x   +              b              = y
//ti��С��0������ST[i]�ǵ�����ֻ�ɶ���
//fi�ɵ���0������SF[i](X)���ϸ�����������Ҫ����X(i)==X(j)����� 
inline LL min(Re a,Re b){return a<b?a:b;}
inline LL X(Re j){return SF[j];}
inline LL Y(Re j){return dp[j];}
inline long double slope(Re i,Re j){return X(j)==X(i)?(Y(j)>=Y(i)?1e18:-1e18):(long double)(Y(j)-Y(i))/(X(j)-X(i));}
//������Ҫ���ֲ��ң�����һЩ���ƣ������ﲻ������ͬһλ�õĵ�,����inf����-inf��Ӱ�����Ƿ�ɾ���ص㣬ƽʱ���ɲ��ܣ����ֱ���ע�ⷵ��ֵ 
inline LL sakura(Re k){
	if(h==t)return Q[h];
	Re l=h,r=t;
	while(l<r){
		Re mid=l+r>>1,i=Q[mid],j=Q[mid+1];
		if(slope(i,j)<k)l=mid+1;
//		if( (Y(j) - Y(i)) < k * (X(j) - X(i)) )l=mid+1;//ע����(j)-(i)��ΪQ[mid+1]>Q[mid]s��j>i��SF[j]>SF[i]��X(j)>X(i)�������(i)-(j)�Ļ��˹�ȥҪ��� 
		else r=mid;
	}
	return Q[l];
}
int main(){
    scanf("%lld%lld",&n,&S);
    for(i=1;i<=n;ST[i]+=ST[i-1],SF[i]+=SF[i-1],++i)scanf("%lld%lld",&ST[i],&SF[i]);
    Q[++t]=0;
	for(i=1;i<=n;++i){
		j=sakura(S+ST[i]);
        dp[i]=dp[j]+ST[i]*(SF[i]-SF[j])+S*(SF[n]-SF[j]);
        while(h<t&&slope(Q[t-1],Q[t])>=slope(Q[t-1],i))--t;//�˴�ȡ�Ⱥ����ó��֣������ȡ�Ȼ�WA
        Q[++t]=i;
	}
    printf("%lld",dp[n]);
}
