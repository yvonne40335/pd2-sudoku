#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<fstream>
#include<vector>
#include"Sudoku.h"
//using namespace std;
Sudoku::Sudoku(){
	i=0;
	map[144];
	save[144];
	savesite=0;
	rowstart[144];
	colstart[144];
	squstart[144];
	rowadd[12];
	coladd[12];
	squadd[12];
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
}

void Sudoku::ReadIn(){
	int num;
	ifstream fin("question.txt",ios::in);
	if(!fin)
		cerr<<"Failed opening"<<endl;
	while(!fin.eof()){
		fin>>num;
		map[i]=num;
		i++;}
	fin.close();}

/*bool Sudoku::checkUnity(int arr[]){
	int arr_unity[12];
	for(int i=0;i<12;i++)
		arr_unity[i]=0;
	for(int i=0;i<12;i++)
		++arr_unity[arr[i]-1];
	for(int i=0;i<12;i++)
		if(arr_unity[i]!=1)
			return false;
	return true;}*/

/*bool Sudoku::isCorrect(){
	bool check_result;
	int check_arr[12];
	int location;
	for(int i=0;i<144;i+=12){
		for(int j=0;j<12;j++)
			check_arr[j]=map[i+j];
		check_result=checkUnity(check_arr);
		if(check_result==false)
			return false;}
	for(int i=0;i<12;i++){
		for(int j=0;j<12;j++)
			check_arr[j]=map[i+12*j];
		check_result=checkUnity(check_arr);
		if(check_result==false)
			return false;}
	for(int i=0;i<16;i++){
		for(int j=0;j<9;j++0){
			location=36*(i/3)+3*(i%4)+12*(j/3)+(j%3);
			check_arr[i]=map[location];}
		check_result=checkUnity(check_arr);
		if(check_result==false)
			return false;}
	return true;}*/

void Sudoku::Solve(){
	init();
	int site=getBlank(-1);
	do{
		map[site]++;
		cout<<map[site]<<endl;
		if(map[site]>9){
			map[site]=0;
			site=back();}
		else{
			if(checkset(site)==0){
				push(site);
				site=getBlank(site);}}
		}while(site>=0 && site<144);

	for(int i=0;i<144;i++){
		cout<<setw(2)<<map[i];
		if(i%12==11)
			cout<<endl;}}

int Sudoku::init(){
	for(int i=0;i<144;i++){
		rowstart[i]=i/12*12;
		colstart[i]=i%12;
		squstart[i]=((i/12)/3)*36+((i%12)/3)*3;}
	for(int i=0;i<12;i++){
		rowadd[i]=i;
		coladd[i]=i*12;
		squadd[i]=(i/3)*12+i%3;}}

int Sudoku::getBlank(int site){
	do{
		site++;
	}while(site<144 && map[site]!=0 );
	return(site);
}

int Sudoku::checkset(int site){
	int p=0;
	if(!p) 
		p=check(site,rowstart[site],rowadd);
	if(!p) 
		p=check(site,colstart[site],coladd);
	if(!p) 
		p=check(site,squstart[site],squadd);
	return(p);}

int Sudoku::check(int site,int start,int *add){
	int site1,p=0;
	for(int i=0;i<12;i++){
		site1=start+add[i];
		if(site!=site1 && map[site]==map[site1])
			p++;}
	return(p);}

int Sudoku::push(int site){
	save[savesite++]=site;}

int Sudoku::back(){
	if(savesite<=0)
		return(-1);
	else
		return(save[--savesite]);}

/*int main(){
	GiveQuestion();
	ReadIn();
	Solve();
	return 0;}*/
