#pragma once
#include "ClassBinaryFile.h"

class ClassBinaryInt:protected ClassBinaryFile
{
public:

	ClassBinaryInt();

	void intFileOpen(string fPath, fileAccess access);
	void intFileClose();

	void intInsertWrite(int data, int pos);
	void intOverWrite(int data);
	void intAppendWrite(int data);
	int intPositionRead(int pos);
	vector<int> intAllRead();

	~ClassBinaryInt();

private:
	void outWrite(int data);
	void inoutWrite(int data, int pos);
	
	void addDataOnWrite(int data);
	int checkPos(int pos);
	void runFileToread(int pos);

	int posRed(int pos);
	vector<int> allRead();
	void Append(int data);

	int getIntRecords();

};

