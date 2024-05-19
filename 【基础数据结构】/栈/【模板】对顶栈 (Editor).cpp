#include<algorithm>
#include<iostream>
#include<cstdio>
using namespace std;
const int N=1e6+5;
int m,x,tl,tr,L[N],R[N],f[N],s[N];char a;
int main(){
    while(scanf("%d",&m)!=EOF){
        s[0]=0;f[0]=-0xfffffff;tl=tr=0;
        while(m--){
            cin>>a;
            if(a=='I'){
                scanf("%d",&x);
                L[++tl]=x;
                f[tl]=max(f[tl-1],s[tl]=s[tl-1]+x);
            }
            else if(a=='R'){
                if(tr){
                    x=L[++tl]=R[tr--];
                    f[tl]=max(f[tl-1],s[tl]=s[tl-1]+x);
                }
            }
            else if(a=='Q')scanf("%d",&x),printf("%d\n",f[x]);
            else if(a=='L'){if(tl)R[++tr]=L[tl--];}
            else if(tl)tl--;
        }
    }
}
