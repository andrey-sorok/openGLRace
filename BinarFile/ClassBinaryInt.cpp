#include "ClassBinaryInt.h"

ClassBinaryInt::ClassBinaryInt():ClassBinaryFile()
{
}

void ClassBinaryInt::intFileOpen(string fPath, fileAccess access)
{
	fName = fPath;
	Open(fPath, access);

	int t = 0;
	typeSize = (int)getTypeSize(t);
	fSize /= typeSize;

	if (fSize > 0)
		numRecords = getIntRecords();	
}

void ClassBinaryInt::intFileClose()
{
	Close();
}

void ClassBinaryInt::intInsertWrite(int data, int pos)
{
	inoutWrite(data, pos);
}

void ClassBinaryInt::intOverWrite(int data)
{
	outWrite(data);
}

void ClassBinaryInt::intAppendWrite(int data)
{
	Append(data);
}

int ClassBinaryInt::intPositionRead(int pos)
{
	return posRed(pos);
}

vector<int> ClassBinaryInt::intAllRead()
{
	return allRead();
}


ClassBinaryInt::~ClassBinaryInt()
{
}

void ClassBinaryInt::outWrite(int data)
{
	int err = Error(1);
	if ((fileOpen == 1) && (err == 0))
		addDataOnWrite(data);
}

void ClassBinaryInt::inoutWrite(int data, int pos)
{
	int err = Error(2);
	if ((fileOpen == 1) && (err == 0))
	{
		pos = checkPos(pos);

		int i = pos;
		int cur = typeSize;
		while (i > 0)
		{
			f.seekg(cur, ios::beg);
			cur += typeSize;
			--i;
		}
		
		addDataOnWrite(data);

		f.seekg(0, ios::beg);
	}
}

void ClassBinaryInt::addDataOnWrite(int data)
{
	int size = sizeof(data);
	f.write((char *)&data, size);
	++numRecords;
	fSize += size;
	f.flush();

}

int ClassBinaryInt::checkPos(int pos)
{
	if (pos < 0)
		pos = 0;
	if (pos > numRecords)
		pos = numRecords;

	return pos;
}

void ClassBinaryInt::runFileToread(int pos)
{
	int cur = 0;
	int i = pos;
	while (i > 0)
	{
		f.seekg(cur, ios::beg);
		cur += typeSize;
		--i;
	}
}

int ClassBinaryInt::posRed(int pos)
{
	int err = Error(3);
	int rtn = 0;
	if ((fileOpen == 1) && (err == 0))
	{
		pos = checkPos(pos);
		runFileToread(pos);
		
		f.read((char *)&rtn, typeSize);
		f.seekg(0, ios::beg);
	}
	
	return rtn;
}

vector<int> ClassBinaryInt::allRead()
{
	vector<int> rtn;

	int err = Error(3);
	if ((fileOpen == 1) && (numRecords > 0) && (err == 0))
	{
		int i = fSize;
		int cur = 0;
		while (i > 0)
		{
			int n = 0;
			f.read((char *)&n, sizeof(int));
			
			cur += typeSize;
			f.seekg(cur, ios::beg);
			
			rtn.push_back(n);
			--i;
		}
	}
	f.seekg(0, ios::beg);

	return rtn;
}

void ClassBinaryInt::Append(int data)
{
	int err = Error(5);
	if ((fileOpen == 1) && (err == 0))
	{
		int pos = numRecords;
		f.seekg(pos*typeSize, ios::beg);
		addDataOnWrite(data);

		f.seekg(0, ios::beg);
	}
}

int ClassBinaryInt::getIntRecords()
{
	int i = fSize;
	int num = 0;
	while (i > 0)
	{
		f.seekg(typeSize, ios::beg);
		++num;
		--i;
	}

	f.seekg(0, ios::beg);

	return num;
}
