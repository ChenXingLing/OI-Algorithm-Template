#include<algorithm>
#include<cstring>
#include<cstdio>
#define Re register int
using namespace std;
const int N=5e5+5;
char s[N];
inline void in(Re &x){
    Re f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Palindromic_Automaton{
	int O,last,siz[N],cnt[N],len[N],fail[N],trans[N][26];
	Palindromic_Automaton(){O=1,len[1]=-1,fail[0]=fail[1]=last=1;}
	//0:偶数串的根节点
	//1:奇数串的根节点
	//siz[x]:状态x出现的次数
	//cnt[x]:状态x所代表的回文串的回文后缀个数
	inline int find(Re p,Re id){while(s[id-1-len[p]]!=s[id])p=fail[p];return p;}
	inline void insert(Re ch,Re id){
		Re cur=find(last,id),now=trans[cur][ch];
		if(!now){
			now=++O,len[now]=len[cur]+2;
			fail[now]=trans[find(fail[cur],id)][ch];
			cnt[now]=cnt[fail[now]]+1;
			trans[cur][ch]=now;
		}
		++siz[now],last=now;
	}
	inline void sakura(){
		for(Re i=O;i>=2;--i)siz[fail[i]]+=siz[i];
	}
}PAM;
int main(){
//	freopen("123.txt","r",stdin);
	scanf("%s",s+1);
	for(Re i=1,k=0;s[i];++i){
		s[i]=(s[i]-'a'+k)%26+'a';
		PAM.insert(s[i]-'a',i);
		printf("%d ",k=PAM.cnt[PAM.last]);
	}
}
