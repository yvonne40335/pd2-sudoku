#include<iostream>
#include<iomanip>
#include<cstdlib>
using namespace std;
int main(){
	int a,b,c,d,e,f,g,h,i;
	int arr[9];

	srand((unsigned) time(NULL));
	for(int i=0;i<9;i++){
		arr[i]=rand()%9+1;
		for(int j=0;j<i;j++){
			while(arr[i]==arr[j]){
				arr[i]=rand()%9+1;
				if(arr[i]!=arr[j])
					j=0;}}}
	a=arr[0],b=arr[1],c=arr[2],d=arr[3],e=arr[4],f=arr[5],g=arr[6],h=arr[7],i=arr[8];
	
	int init_map[12][12]={
		{e,g,d,b,c,a,-1,-1,-1,h,i,f},
		{b,c,f,h,i,d,-1,-1,-1,e,g,a},
		{h,i,a,e,g,f,-1,-1,-1,b,c,d},
		{-1,-1,-1,c,a,b,i,f,h,g,d,e},
		{-1,-1,-1,g,d,e,c,a,b,i,f,h},
		{-1,-1,-1,i,f,h,g,d,e,c,a,b},
		{f,h,i,a,b,c,d,e,g,-1,-1,-1},
		{a,b,c,d,e,g,f,h,i,-1,-1,-1},
		{d,e,g,f,h,i,a,b,c,-1,-1,-1},
		{g,d,e,-1,-1,-1,h,i,f,a,b,c},
		{i,f,h,-1,-1,-1,b,c,a,d,e,g},
		{c,a,b,-1,-1,-1,e,g,d,f,h,i}};
	
	for(int x=0;x<10;x++){
		int i=rand()%12;
		int j=rand()%12;
		if(init_map[i][j]!=-1)
			init_map[i][j]=0;
		else
			x=x-1;}

	int x=rand()%4*3;
	for(int i=0;i<12;i++){
		int y=i+x;
		if(y>11)
			y=y-12;
		for(int j=0;j<12;j++){
			cout<<setw(2)<<init_map[y][j];}
		cout<<endl;}
	
	return 0;}
