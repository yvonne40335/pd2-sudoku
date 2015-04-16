#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<fstream>
#include<vector>
using namespace std;
class Sudoku{
public:
	Sudoku();
	void GiveQuestion();
	void ReadIn();
	void Solve();
	int init();
	int getBlank(int site);
	int checkset(int site);
	int check(int site,int start,int *add);
	int push(int site);
	int back();
//	bool
//	bool
private:
	int i;
	int map[144];
	int save[144];
	int savesite;
	int rowstart[144];
	int colstart[144];
	int squstart[144];
	int rowadd[12];
	int coladd[12];
	int squadd[12];
};
