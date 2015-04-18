#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<fstream>
#include<vector>
#include"Sudoku.h"

Sudoku::Sudoku(){
	i=0;
	map[144];
	mapsave[144];
	save[144];
	savesite=0;
	rowstart[144];
	colstart[144];
	squstart[144];
	rowadd[12];
	coladd[12];
	squadd[9];
}

void Sudoku::GiveQuestion(){
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
	
	for(int x=0;x<30;x++){
		int i=rand()%12;
		int j=rand()%12;
		if(init_map[i][j]!=-1)
			init_map[i][j]=0;
		else
			x=x-1;}

	int m=0;
	for(int i=0;i<12;i++){
		for(int j=0;j<12;j++){
			map[m]=init_map[i][j];
			mapsave[m]=map[m];
			m++;}}
	
	init();
	if(isCorrect()==false || checkmore()==false){
		return GiveQuestion();}

	int x=rand()%4*3;
	for(int i=0;i<12;i++){
		int y=i+x;
		if(y>11)
			y=y-12;
		for(int j=0;j<12;j++){
			cout<<setw(2)<<init_map[y][j];}
		cout<<endl;}
}

void Sudoku::ReadIn(){
	for(i=0;i<144;i++){
		cin>>map[i];
		mapsave[i]=map[i];}}

int Sudoku::Solve(){
//	vector<int>map1(144);
//	vector<int>map2(144);
	init();

	if(isCorrect()==false){
		cout<<"0"<<endl;
		return 0;}
	if(checkmore()==false){
		cout<<"2"<<endl;
		return 0;}
	else
		cout<<"1"<<endl;

	for(int j=0;j<144;j++){
			cout<<setw(2)<<map[j];
			if(j%12==11)
				cout<<endl;}}
	

bool Sudoku::checkmore(){
	vector<int>map1(144);
	vector<int>map2(144);
	int site=getBlank(-1);
	do{
		map[site]++;
		if(map[site]>9){
			map[site]=0;
			site=save[--savesite];}
		else{
			if(checkset(site)==0){
				site=getBlank(site);}}
		}while(site>=0 && site<144);

	for(int i=0;i<144;i++)
		map1.at(i)=map[i];

	for(int i=0;i<144;i++)
		map[i]=mapsave[i];

	site=getBlank1(144);
	do{
		map[site]++;
		if(map[site]>9){
			map[site]=0;
			site=save[--savesite];}
		else{
			if(checkset(site)==0){
				site=getBlank1(site);}}
		}while(site>=0 && site<144);
	
	for(int j=0;j<144;j++)
		map2.at(j)=map[j];

	if(map1!=map2){
		return false;}
	else 
		return true;

/*		cout<<"2"<<endl;
		return 0;}
	else
		cout<<"1"<<endl;

	for(int j=0;j<144;j++){
			cout<<setw(2)<<map1.at(j);
			if(j%12==11)
				cout<<endl;}*/}

bool Sudoku::isCorrect(){
	for(int site=0;site<144;site++){
		if(map[site]!=-1 && map[site]!=0)
		{
			if(checkrow(site)!=0) return false;
			if(checkcol(site)!=0) return false;
			if(checksqu(site)!=0) return false;
		}
		else if(map[site]==-1)
		{
			if(site==0 || site==3 || site==6 || site==9 || site==36 || site==39 || site==42 || site==45 || site==72 || site==75 || site==78 || site==81 || site==108 || site==111 || site==114 || site==117)
			{
				if(checksqu(site)!=8) return false;
			}
			else	
				if(checksqu(site)!=11) return false;
		}
	}
	return true;}

int Sudoku::init(){
	for(int i=0;i<144;i++){
		rowstart[i]=i/12*12;
		colstart[i]=i%12;
		squstart[i]=((i/12)/3)*36+((i%12)/3)*3;}
	for(int i=0;i<12;i++){
		rowadd[i]=i;
		coladd[i]=i*12;}
	for(int i=0;i<9;i++){
		squadd[i]=(i/3)*12+i%3;}
	for(int i=9;i<12;i++){
		squadd[i]=0;}}

int Sudoku::getBlank(int site){
	do{
		site++;
	}while(site<144 && map[site]!=0 );
	save[savesite]=site;
	return(site);}

int Sudoku::getBlank1(int site){
	do{
		site--;
	}while(site>=0 && map[site]!=0 );
	save[savesite++]=site;
	return(site);}

int Sudoku::checkset(int site){
	int p=0;
	p=checkrow(site);
	if(p!=0) return p;
	p=checkcol(site);
	if(p!=0) return p;
	p=checksqu(site);
	return p;}

int Sudoku::checkrow(int site){
	int p=0,site1;
	for(int i=0;i<12;i++){
		site1=rowstart[site]+rowadd[i];
		if(site!=site1 && map[site]==map[site1])
			p++;}
	return p;}

int Sudoku::checkcol(int site){
	int p=0,site1;
	for(int i=0;i<12;i++){
		site1=colstart[site]+coladd[i];
		if(site!=site1 && map[site]==map[site1])
			p++;}
	return p;}

int Sudoku::checksqu(int site){
	int p=0,site1;
	for(int i=0;i<12;i++){
		site1=squstart[site]+squadd[i];
		if(site!=site1 && map[site]==map[site1])
			p++;}
	return p;}
