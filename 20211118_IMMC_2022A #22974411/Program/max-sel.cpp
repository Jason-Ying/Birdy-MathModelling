#include<bits/stdc++.h>
using namespace std;
int a[10];
string str;
int main(){
	freopen("lamppost-8-modi.in","r",stdin);
	freopen("lp-sel-8.out","w",stdout);
	for(int i=1;i<=53316;i++){
		memset(a,0,sizeof(a));
		for(int j=1;j<=8;j++){
			cin>>a[j];
		}
		cin>>str;
//		cout<<"str: "<<str<<endl;
		if(str=="1"){
			for(int j=1;j<=8;j++){
				cout<<a[j]<<" ";
			}
			cout<<endl;
		}
		getchar();
//		cout<<"str: "<<str<<endl;
	}
	return 0;
}
