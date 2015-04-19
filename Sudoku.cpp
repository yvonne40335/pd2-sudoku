#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<vector>
#include"Sudoku.h"

Sudoku::Sudoku(){
	i=0;
	map[144];
	mapsave[144];
	save[144];
	save1[144];
	savesite=0;
	savesite1=0;
	rowstart[144];
	colstart[144];
	squstart[144];
	rowadd[12];
	coladd[12];
	squadd[9];
}

void Sudoku::GiveQuestion(){	//出題function
	int a,b,c,d,e,f,g,h,i;
	int arr[9];
	for(int i=0;i<144;i++){
		map[i]=0;}
	srand((unsigned) time(NULL));	//利用亂數來產生數獨
	for(int i=0;i<9;i++){	//a~i代表不同的數字(1~9),其代表的數字是以亂數來決定
		arr[i]=rand()%9+1;
		for(int j=0;j<i;j++){
			while(arr[i]==arr[j]){
				arr[i]=rand()%9+1;
				if(arr[i]!=arr[j])
					j=0;}}}
	a=arr[0],b=arr[1],c=arr[2],d=arr[3],e=arr[4],f=arr[5],g=arr[6],h=arr[7],i=arr[8];
	
	int init_map[12][12]={	//將一個設定好的數獨棋盤填進陣列裡
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
	
	for(int x=0;x<20;x++){	//以亂數來決定哪格為空格(需解出答案的地方)
		int i=rand()%12;
		int j=rand()%12;
		if(init_map[i][j]!=-1)	//只能挖不是-1的地方,若為-1則跳過
			init_map[i][j]=0;
		else
			x=x-1;}

	int m=0;
	for(int i=0;i<12;i++){	
		for(int j=0;j<12;j++){
			map[m]=init_map[i][j];
			mapsave[m]=map[m];
			m++;}}
	
/*	init();
	if(isCorrect()==false || checkmore()==false){
		return GiveQuestion();}
	else{*/

	int x=rand()%4*3;
	for(int i=0;i<12;i++){	//讓每一橫列可以上下移動,做更多題目變化
		int y=i+x;
		if(y>11)
			y=y-12;
		for(int j=0;j<12;j++){
			cout<<init_map[y][j]<<" ";}
		cout<<endl;}
}

void Sudoku::ReadIn(){	//讀題目的function
	for(i=0;i<144;i++){
		cin>>map[i];
		mapsave[i]=map[i];}}

int Sudoku::Solve(){	//解題目的function
//	vector<int>map1(144);
//	vector<int>map2(144);
	init();	//呼叫為了產生"檢查有無重複數字時,用來運算的值"時所用的function
	if(isCorrect()==false){	
		cout<<'0'<<endl;	//無解時輸出0
		return 0;}
	if(checkmore()==false){
		cout<<'2'<<endl;	//多組解時輸出2
		return 0;}
	else
		cout<<'1'<<endl;	//有唯一解時輸出1

	for(int j=0;j<144;j++){	//印出解出來的答案
			cout<<map[j]<<" ";
			if(j%12==11)
				cout<<endl;}}
	

bool Sudoku::checkmore(){	//用來檢查是否為多組解的function
	vector<int>map1(144);	//存到vector裡,方便之後對照兩組解是否相同,若為相同,則是唯一解
	vector<int>map2(144);
	int site=getBlank(-1);	//從頭開始找挖空的位置
	do{
		map[site]++;	//將該位置的值從1開始測試
		if(map[site]>9){	//若該位置已測試到10都沒有答案,代表前一個位置填錯
			map[site]=0;	//將該位置歸零
			site=save[--savesite];}	//並找到上一個位置,去重新測試它的值
		else{
			if(checkset(site)==0){	//若該位置測試的值,在同一行,列,九宮格都沒有重複,則有可能為正確的值
				site=getBlank(site);}}	//去尋找下一個空格
		}while(site>=0 && site<144);

	for(int i=0;i<144;i++)	//將該組解存進map1,以供對照
		map1.at(i)=map[i];

	for(int i=0;i<144;i++){	//要進行第二次測試,因此拿出之前存入的題目,重新初始化陣列
		map[i]=mapsave[i];}

	site=getBlank1(-1);	//從最後面開始解
	do{
		map[site]--;
		if(map[site]<=0){
			map[site]=10;
			site=save1[--savesite1];}
		else{
			if(checkset(site)==0){
				site=getBlank1(site);}}
		}while(site>=0 && site<144);
	
	for(int j=0;j<144;j++){	//將該組解存進map2
		map2.at(j)=map[j];}

	if(map1!=map2){	//如果兩組相同則return true,不同則return false
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

bool Sudoku::isCorrect(){	//確認是否行,列,九宮格都沒有重複的數字
	for(int site=0;site<144;site++){
		if(map[site]!=-1 && map[site]!=0)
		{
			if(checkrow(site)!=0) return false;
			if(checkcol(site)!=0) return false;
			if(checksqu(site)!=0) return false;
		}
		else if(map[site]==-1)	//若為-1,則要同一個九宮格裡都是-1,才會有解
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

int Sudoku::init(){	//為對照數字所做的運算
	for(int i=0;i<144;i++){
		rowstart[i]=i/12*12;	//算列
		colstart[i]=i%12;	//算行
		squstart[i]=((i/12)/3)*36+((i%12)/3)*3;}	//算九宮格
	for(int i=0;i<12;i++){
		rowadd[i]=i;
		coladd[i]=i*12;}
	for(int i=0;i<9;i++){
		squadd[i]=(i/3)*12+i%3;}
	for(int i=9;i<12;i++){	//因為九宮格只需檢查九個,因此將後三個都設成0
		squadd[i]=0;}}

int Sudoku::getBlank(int site){	//找空格
	do{
		site++;
	}while(site<144 && map[site]!=0 );	//當找到0,則回傳該位置
	save[++savesite]=site;
	return(site);}

int Sudoku::getBlank1(int site){
	do{
		site++;
	}while(site>=0 && map[site]!=0 );
	map[site]=10;
	save1[++savesite1]=site;
	return(site);}

int Sudoku::checkset(int site){	//測試有沒有重複
	int p=0;
	p=checkrow(site);
	if(p!=0) return p;
	p=checkcol(site);
	if(p!=0) return p;
	p=checksqu(site);
	return p;}

int Sudoku::checkrow(int site){	//對同一列作測試,當發現有重複的,p會加一,p回傳只要不是1,代表有重複
	int p=0,site1;
	for(int i=0;i<12;i++){
		site1=rowstart[site]+rowadd[i];
		if(site!=site1 && map[site]==map[site1])
			p++;}
	return p;}

int Sudoku::checkcol(int site){	//對同一行做測試
	int p=0,site1;
	for(int i=0;i<12;i++){
		site1=colstart[site]+coladd[i];
		if(site!=site1 && map[site]==map[site1])
			p++;}
	return p;}

int Sudoku::checksqu(int site){	//對九宮格做測試
	int p=0,site1;
	for(int i=0;i<12;i++){
		site1=squstart[site]+squadd[i];
		if(site!=site1 && map[site]==map[site1])
			p++;}
	return p;}
