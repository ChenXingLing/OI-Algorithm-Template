#include<bits/stdc++.h>
#define itn int
#define mian main
using namespace std;
int len,a[30005],piu,op;
char s;
priority_queue<int,vector<int>, greater<int> >sak;
priority_queue<int,vector<int>,less<int> >b;
int main(){
    while(scanf("%c",&s)){
        if(s=='A'){
            while(s!='(') scanf("%c",&s);
            scanf("%d",&a[++len]);
            getchar();
            piu++;
        }
        if(s=='G'){
            getchar();
            getchar();
			while(op<piu){
            	op++;
           	 	b.push(a[op]);
           	 	sak.push(b.top());
            	b.pop();
        	}
        	printf("%d ",sak.top());
        	b.push(sak.top());
        	sak.pop();
        }
        getchar();
    } 
    return 0;
}
