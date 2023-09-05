#include<bits/stdc++.h>
using namespace std;
int data[100100],n;
void mysort(int left, int right){
	int mid=data[(left+right)/2];
	int i=left,j=right;
	while(i<=j){
		while(data[i]<mid)i++;
		while(data[j]>mid)j--;
		if(i<=j)swap(data[i++],data[j--]);
	}
	if(j>left)mysort(left,j);
	if(i<right)mysort(i,right);
}
int main(){	
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&data[i]);
	mysort(1,n);
	for(int i=1;i<=n;i++)printf("%d ",data[i]);
}
