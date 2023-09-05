//#pragma GCC optimize(3,"Ofast","inline")
//#pragma GCC optimize(2)
#include<algorithm>
#include<cstdio>
#define Re register int
#define pl tr[p].ps[0]
#define pr tr[p].ps[1]
#define pf tr[p].fa 
#define pv tr[p].v
using namespace std;
const int N=1e5+5,inf=2e9;
int T,a,b,n,o,root;
struct Splay{int v,fa,ps[2],cnt,size;}tr[N];
inline void in(Re &x){
    int fu=0;x=0;char c=getchar();
    while(c<'0'||c>'9')fu|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=fu?-x:x;
}
inline void pushup(Re p){if(!p)return;/*�������Ҫ���ж�return����������*/tr[p].size=tr[p].cnt+tr[pl].size+tr[pr].size;}
inline void connect(Re p,Re f,Re o){tr[tr[p].fa=f].ps[o]=p;}//��p��Ϊf��o���� 
inline int which(Re p){return tr[pf].ps[1]==p;}//��ѯp���ĸ����� 
inline void rotate(Re p){//Treap�ǰ�p�������������ǰ�p��������pf��ͷ��ȥ 
	Re y=pf,ys=which(p);//��y��x�ĸ���㡣��ys��x�������׵��ĸ����� 
	Re R=tr[y].fa,Rs=which(y);//��R��y�ĸ��ס���Rs��y�������׵��ĸ����� 
	Re B=tr[p].ps[ys^1];//p�Ķ�������pfͬ����ĵ�(��Ҫ��������y��) 
	connect(B,y,ys),connect(y,p,ys^1),connect(p,R,Rs);//���� 
	pushup(y),pushup(p);//p��������yͷ��ȥ����02����y���ٸ���p 
}
inline void Splay(Re p){//������ζ�һ��Ҫһ�������£�NOI�ľ޶������ݻῨ���� 
	for(Re fa;fa=pf;rotate(p))
		if(tr[fa].fa)rotate(which(p)==which(fa)?fa:p);
	root=p;
//���Կ������������ο�˫�� 
}
inline void New(Re x,Re fa){//��һ���µ�x���ӵ� fa���� 
	tr[++o].v=x,tr[o].fa=fa,tr[o].cnt=tr[o].size=1;
	if(fa)tr[fa].ps[tr[fa].v<x]=o;
}
inline void insert(Re x){
	if(!root){New(x,0);root=o;return;}//������ֱ�Ӽ򵥽��� 
	int p=root,fa=0;
	while(1){
		if(x==pv){++tr[p].cnt,pushup(p),pushup(fa),Splay(p);break;}//�����˸��� 
		fa=p,p=tr[p].ps[pv<x];//�������±��� 
		if(!p){New(x,fa),pushup(fa),Splay(o);break;}//����Ҷ�ӽڵ�λ�ã����벢������������ȥ 
	}
}
inline int ask_level(Re p,Re x){//��ѯ��x������ 
//printf("p: %d\n",p);exit(0);
	if(x==pv){Re ans=tr[pl].size+1;Splay(p);return ans;}//�ҵ��������
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
inline int ask_nex_p(Re p){p=pr;while(pl)p=pl;return p;}//�ӽڵ�p��ʼ��ѯ�Ｑ��λ�� 
inline int ask_pri_p(Re p){p=pl;while(pr)p=pr;return p;}//�ӽڵ�p��ʼ��ѯǰ����λ�� 
inline void del(Re x){
	ask_level(root,x);Re p=root;//�ҵ�����㲢����root 
	if(tr[p].cnt>1){--tr[p].cnt,--tr[p].size;return;}//�и���
	if(!pl&&!pr){root=0;return;}//û�ж��� 
	if(!pl||!pr){tr[root=pl+pr].fa=0;return;}//ֻ��һ������,ֱ�ӽ�����Ӹ�Ϊ�� 
	Splay(ask_pri_p(root));//������ǰ������ȥ��Ȼ�������Ҷ��Ӿ���ԭroot(��x) 
	tr[root].ps[1]=pr,tr[pr].fa=root;//ɾ��ԭroot(��x) 
	pushup(root);
}
int main(){
	in(T);
	while(T--){
		in(a),in(b);
		if(a==1)insert(b);
		if(a==2)del(b);
		if(a==3)printf("%d\n",ask_level(root,b));
		if(a==4)printf("%d\n",ask_v(root,b));
		if(a==5)insert(b),printf("%d\n",tr[ask_pri_p(root)].v),del(b);
		if(a==6)insert(b),printf("%d\n",tr[ask_nex_p(root)].v),del(b);
	}
}
