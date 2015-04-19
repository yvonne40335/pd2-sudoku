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
	int Solve();
	bool isCorrect();
	bool checkmore();
	int init();
	int getBlank(int site);
	int getBlank1(int site);
	int checkset(int site);
	int checkrow(int site);
	int checkcol(int site);
	int checksqu(int site);
private:
	int i;
	int map[144];
	int mapsave[144];
	int save[144];
	int save1[144];
	int savesite;
	int savesite1;
	int rowstart[144];
	int colstart[144];
	int squstart[144];
	int rowadd[12];
	int coladd[12];
	int squadd[12];
};
