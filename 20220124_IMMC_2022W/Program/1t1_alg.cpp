#include<bits/stdc++.h>
#include<fstream>
#include<sstream>
#define M1 5
#define M2 6
#define M3 4 
#define C 100000 
#define PT 1000
#define P 100000
#define S 2
using namespace std;
int typ,old_purc[M1],purc[M2],prd[P][M3],yes_sell[S][P],label[C];//label 1:OnlyA 2:OnlyB 3:A&B 
double old_time,now_time,freq[C][S][PT],total_freq[S][PT],total_total_freq[S],rp_used[S][PT],rp_loss[S][PT],total_rp_loss[S],k1,k2;
char typ_name[PT];
void up_pctg(double a,double b){
	double rate=a/b*100;
	cout<<rate<<"%"<<endl;
}
int main(){
	cout<<"How many types of goods:";
	cin>>typ;
	cout<<"Please input the symbols of the "<<typ<<" types of goods."<<endl;
	for(int i=0;i<typ;i++)cin>>typ_name[i];
	cout<<"Please input the rate from(to) money to(from) RPs:";
	cin>>k1>>k2;
	
	
	
	int overlap[P]={0};//1A2B3AB
	double overlap_cnt=0,t=0;
	string line;
	ifstream fin("prd.csv");
	while(getline(fin,line)){
		istringstream sin(line);
		vector<string> data;
		string info;
		while(getline(sin,info,',')){
			data.push_back(info);
			if(info=="\n")break;
		}
		int tt=int(t);
		for(int i=0;i<M3;i++)prd[tt][i]=atoi(data[i].c_str());//id price typ_id shop(0A1B)
		
		yes_sell[prd[tt][3]][prd[tt][2]]=1;
		
		if(prd[tt][3]==0&&overlap[tt]==2)overlap[tt]=2;
		if(prd[tt][3]==1&&overlap[tt]==1)overlap[tt]=2;
		if(overlap[tt]==0)overlap[tt]=prd[tt][3]+1;
		
		t++;
	}
	for(int i=0;i<t;i++)
		if(overlap[i]==3)overlap_cnt++;
	double overlap_rate=overlap_cnt/t;
	fin.close();
	
	
	
	cout<<"Please input the time span of the old data:";
	cin>>old_time;
	ifstream finn("old.csv");
	while(getline(finn,line)){
		istringstream sin(line);
		vector<string> data;
		string info;
		while(getline(sin,info,',')){
			data.push_back(info);
			if(info=="\n")break;
		}
		for(int i=0;i<M1;i++)old_purc[i]=atoi(data[i].c_str());//id customer_id product_id amount shop(0A1B)
		
		freq[old_purc[1]][old_purc[4]][prd[old_purc[2]][2]]+=prd[old_purc[2]][1]*old_purc[3];//by customer&shop&product type
		total_freq[old_purc[4]][prd[old_purc[2]][2]]+=prd[old_purc[2]][1]*old_purc[3];
		total_total_freq[old_purc[4]]+=prd[old_purc[2]][1]*old_purc[3];
		
		if(old_purc[4]==0){
			if(label[old_purc[1]]==2||label[old_purc[1]]==3)label[old_purc[1]]=3;
			else label[old_purc[1]]=1;
		}
		if(old_purc[4]==1){
			if(label[old_purc[1]]==1||label[old_purc[1]]==3)label[old_purc[1]]=3;
			else label[old_purc[1]]=2;
		}
	}
	for(int i=0;i<C;i++){
		for(int j=0;j<PT;j++){
			freq[i][0][j]/=old_time;
			freq[i][1][j]/=old_time; 
		}
	}
	for(int i=0;i<PT;i++){
		total_freq[0][i]/=old_time;
		total_freq[1][i]/=old_time;
	}
	total_total_freq[0]/=old_time;
	total_total_freq[1]/=old_time;
	finn.close();
	
	
	
	cout<<"Please input the time span of the new data:";
	cin>>now_time;
	double sales[2]={0};
	double total_rp_used[2]={0},total_total_rp_used=0,total_sales=0;
	double bonus_A[PT]={0},bonus_B[PT]={0};//by product type
	double total_bonus_A=0,total_bonus_B=0;
	ifstream finnn("now.csv");
	while(getline(finnn,line)){
		istringstream sin(line);
		vector<string> data;
		string info;
		while(getline(sin,info,',')){
			data.push_back(info);
			if(info=="\n")break;
		}
		for(int i=0;i<M2;i++)purc[i]=atoi(data[i].c_str());//id customer_id product_id amount use_rp shop(0A1B)
		rp_used[purc[5]][prd[purc[2]][2]]+=purc[4];
		total_rp_used[purc[5]]+=purc[4];
		total_total_rp_used+=purc[4];
		sales[purc[5]]+=prd[purc[2]][1]*purc[3];
		total_sales+=sales[purc[5]];
		
		if(purc[5]==1){
			bonus_B[prd[purc[2]][2]]+=purc[3]*prd[purc[2]][1];
			total_bonus_B+=purc[3]*prd[purc[2]][1];
		}
		if(purc[5]==0){
			bonus_A[prd[purc[2]][2]]+=purc[3]*prd[purc[2]][1];
			total_bonus_A+=purc[3]*prd[purc[2]][1];
		}
	}
	for(int i=0;i<PT;i++){
		rp_loss[0][i]=rp_used[1][i]*k2;
		rp_loss[1][i]=rp_used[0][i]*k2;
	}
	total_rp_loss[0]+=total_rp_used[1]*k2;
	total_rp_loss[1]+=total_rp_used[0]*k2;
	double rp_given[2]={sales[0]*k1,sales[1]*k1};
	double rp_rate[2]={total_rp_used[1]/rp_given[0],total_rp_used[0]/rp_given[1]};
	double total_rp_given=total_sales*k1;
	double total_rp_rate=total_total_rp_used/total_rp_given;
	for(int i=0;i<C;i++){
		if(label[i]==3){
			total_bonus_A-=now_time*total_freq[0][i];
			total_bonus_B-=now_time*total_freq[1][i];
		}
	}
	finnn.close();
	
	
	
	cout<<"==============="<<endl;
	cout<<"Money to RP: "<<k1<<endl;
	cout<<"RP to Money: "<<k2<<endl;
	cout<<"The total RP usage rate: "<<total_rp_rate<<endl;
	cout<<"Overlap Rate: "<<overlap_rate<<endl; 
	cout<<"Merchant A benefit rise: ";
	up_pctg(total_bonus_A-total_rp_loss[0],now_time*total_total_freq[0]);
	cout<<"With each kind of product rising: "<<endl;
	for(int i=0;i<typ;i++){
		if(!yes_sell[0][i])continue;
		cout<<typ_name[i]<<": ";
		up_pctg(bonus_A[i]-rp_loss[0][i],now_time*total_freq[0][i]);
	}
	cout<<"Merchant B benefit rise: ";
	up_pctg(total_bonus_B-total_rp_loss[1],now_time*total_total_freq[1]);
	cout<<"With each kind of product rising: "<<endl;
	for(int i=0;i<typ;i++){
		if(!yes_sell[1][i])continue;
		cout<<typ_name[i]<<": ";
		up_pctg(bonus_B[i]-rp_loss[1][i],now_time*total_freq[1][i]);
	}
	cout<<"==============="<<endl;
	
	system("pause"); 
	return 0;
}
