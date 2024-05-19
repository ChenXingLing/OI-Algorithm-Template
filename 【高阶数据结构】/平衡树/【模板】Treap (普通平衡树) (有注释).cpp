#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<algorithm> 
#include<cstdlib> 
#include<cstdio>
#include<ctime>
#define Re register int
#define pl tr[p].lp
#define pr tr[p].rp
#define pv tr[p].v
using namespace std;
const int N=1e5+5,inf=2e9;
int a,b,o,T,root;
inline void in(Re &x){
    int fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
struct Treap{int v,rd,lp,rp,cnt,size;}tr[N];//cntΪ�ýڵ㴦�����v�ĸ��� 
inline void pushup(Re p){tr[p].size=tr[p].cnt+tr[pl].size+tr[pr].size;}//���½ڵ�ռ���Ϣ 
inline void lturn(Re &p){//���� 
	Re q=pr;pr=tr[q].lp,tr[q].lp=p;//�ߵ����ӹ�ϵ 
	pushup(p),pushup(p=q);//��push(p)��push(q)��������������� 
//���ߣ�p=q�������p����������ȡ��ַ���������ö��������������൱��tr[?].lp����tr[?].rp 
}
inline void rturn(Re &p){//���� 
	Re q=pl;pl=tr[q].rp,tr[q].rp=p;//�ߵ����ӹ�ϵ 
	pushup(p),pushup(p=q);//��push(p)��push(q)��������������� 
}
inline void insert(Re &p,Re x){
	if(!p){tr[p=++o].v=x,tr[p].cnt=tr[p].size=1,tr[p].rd=rand();return;}
	++tr[p].size;
	if(x==pv)++tr[p].cnt;
	else if(x<pv){
		insert(pl,x);
		if(tr[pl].rd<tr[p].rd)rturn(p);//С���� 
	}
	else{
		insert(pr,x);
		if(tr[pr].rd<tr[p].rd)lturn(p);//С���� 
	}
}
inline void del(Re &p,Re x){
	if(!p)return;
    if(x<pv)--tr[p].size,del(pl,x);
	else if(x>pv)--tr[p].size,del(pr,x);
	else{
		if(tr[p].cnt>1)--tr[p].cnt,--tr[p].size;//���������ĸ�����ֹһ����ֱ�Ӽ�һ�����˳�
		else{//������Ҫɾ���ýڵ� 
			if(pl*pr==0)p=pl+pr;
//����һ������Ϊ�գ�ֱ��ָ��������յģ���ô����ʱ�Ϳ���ֱ�������ڵ�p���൱�ڴﵽ��ɾ��p��Ŀ��
//�����Ϊ�գ��൱�ڰ�p��ֵ����0 
//����Ļ����ȵ������������ӵĴ���Ȼ��p����һ�߲�����ɾ������ 
			else if(tr[pl].rd<tr[pr].rd)rturn(p),del(p,x);
			else lturn(p),del(p,x);
		}
	}
}
inline int ask_level(Re p,Re x){//��ѯ��x������(��֤����x)�� 
//	if(!p)return 0;//���û�ҵ������ 
	if(x==pv)return tr[pl].size+1;//�ҵ��������
	else return x<pv?ask_level(pl,x):tr[p].cnt+tr[pl].size+ask_level(pr,x);
}
inline int ask_v(Re p,Re x){//��ѯ����Ϊx���� 
//	if(!p)return 0;//���û�ҵ������
	if(x<=tr[pl].size)return ask_v(pl,x);
	else{
		Re tmp=tr[pl].size+tr[p].cnt;
		return x<=tmp?pv:ask_v(pr,x-tmp);
	}
}
inline int ask_pri(Re p,Re x){//��ѯx��ǰ�� 
	if(!p)return -inf;
	if(x<=pv)return ask_pri(pl,x);
	else return max(pv,ask_pri(pr,x));
}
inline int ask_nex(Re p,Re x){//��ѯx�ĺ�� 
	if(!p)return inf;
	if(x>=pv)return ask_nex(pr,x);
	else return min(pv,ask_nex(pl,x));
}
int main(){
	srand((int)time(NULL));
	in(T);
	while(T--){
		in(a),in(b);
		if(a==1)insert(root,b);
		if(a==2)del(root,b);
		if(a==3)printf("%d\n",ask_level(root,b));
		if(a==4)printf("%d\n",ask_v(root,b));
		if(a==5)printf("%d\n",ask_pri(root,b)); 
		if(a==6)printf("%d\n",ask_nex(root,b));
	}
}
