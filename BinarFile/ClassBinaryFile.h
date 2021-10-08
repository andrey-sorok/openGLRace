#pragma once

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

enum fileAccess { in, out, inout };

class ClassBinaryFile
{
public:
	ClassBinaryFile();

	void strFileOpen(string fPath, fileAccess access);
	void strFileClose();
	void strInsertWrite(string & data, int pos);
	void strOverWrite(string & data);
	void strAppendWrite(string & data);
	string strPositionRead(int pos);
	vector<string> strAllRead();

	~ClassBinaryFile();

private:
	void outWrite(string & data);
	void inoutWrite(string & data, int pos);
	
	string posRead(int pos);
	vector<string> allInRead();
	void Append(string & data);
	
	int getNumRecords();
	string getBuffer(char * buf, int size);

protected:
	enum filePos { beg, end, cur };
	fstream f;
	string fName;

	fileAccess fAccess;
	filePos fPos;

	bool fileOpen;

	int fSize;
	int numRecords;
	int typeSize;

	bool Open(string fPath, fileAccess access);

	template <typename T>
	long long getTypeSize(T t);

	void Close();
	int Error(int n);
	void outError(int n);

};

template<typename T>
inline long long ClassBinaryFile::getTypeSize(T t)
{
	return sizeof(t);
}
