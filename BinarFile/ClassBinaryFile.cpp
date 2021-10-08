#include "ClassBinaryFile.h"

ClassBinaryFile::ClassBinaryFile():fSize(0), numRecords(0), typeSize(0)
{
}

void ClassBinaryFile::strFileOpen(string fPath, fileAccess access)
{
	fName = fPath;
	Open(fName, access);
	
	if (fSize > 0)
		numRecords = getNumRecords();

	string s = "";
	typeSize = (int)getTypeSize(s);
}

void ClassBinaryFile::strFileClose()
{
	Close();
}

void ClassBinaryFile::strInsertWrite(string & data, int pos)
{
	inoutWrite(data, pos);
}

void ClassBinaryFile::strOverWrite(string & data)
{
	outWrite(data);
}

void ClassBinaryFile::strAppendWrite(string & data)
{
	Append(data);
}

string ClassBinaryFile::strPositionRead(int pos)
{
	return posRead(pos);
}

vector<string> ClassBinaryFile::strAllRead()
{
	return allInRead();
}


ClassBinaryFile::~ClassBinaryFile()
{
}
//out
void ClassBinaryFile::outWrite(string & data)
{
	int err = Error(1);
	if (err == 0)
	{
		int size = (int)data.size();
		fSize += size + 4;
		f.write((char *)&size, sizeof(size));
		f.write((char *)data.c_str(), size);
		++numRecords;
		f.flush();
	}
}
//inout
void ClassBinaryFile::inoutWrite(string & data, int pos)
{
	int err = Error(2);
	if ((fileOpen == 1) && (err == 0))
	{
		if (pos < 0)
			pos = 0;
		if (pos > numRecords)
		{
			pos = numRecords;
			++numRecords;
		}

		int cur = 0;
		while (pos > 0)
		{
			int size = 0;
			f.read((char *)&size, sizeof(size));
			cur += size + 4;
			f.seekg(cur, ios::beg);
			--pos;
		}

		int size = (int)data.size();
		f.write((char *)&size, sizeof(size));
		f.write((char *)data.c_str(), size);


		f.seekg(0, ios::beg);
		f.flush();
	}
}

string ClassBinaryFile::posRead(int pos)
{
	string rtn = "";
	
	int err = Error(3);

	if ((fileOpen == 1) && (err == 0))
	{
		if (pos < 0 || pos > numRecords)
		{
			Error(4);
			return rtn;
		}

		int cur = 0;
		while (pos != 0)
		{
			int size = 0;
			f.read((char *)&size, sizeof(size));
			cur += size + 4;
			f.seekg(cur, ios::beg);
			--pos;
		}
		int size = 0;
		f.read((char *)&size, sizeof(size));
		char * buf = new char[size];
		f.read((char *)buf, size);
		f.seekg(0, ios::beg);

		rtn = getBuffer(buf, size);
	}

	return rtn.c_str();
}

vector<string> ClassBinaryFile::allInRead()
{
	vector<string> rtn;

	int err = Error(4);
	numRecords = getNumRecords();
	if ((fileOpen == 1) && (numRecords > 0) && (err == 0))
	{

		int cur = 0;
		int i = numRecords;
		while (i != 0)
		{
			int size = 0;
			f.read((char *)&size, sizeof(size));
			char * buf = new char[size];
			f.read((char *)buf, size);

			rtn.push_back(getBuffer(buf, size));
			cur += size + 4;
			f.seekg(cur, ios::beg);

			--i;
		}
		f.seekg(0, ios::beg);
	}

	return rtn;
}

void ClassBinaryFile::Append(string & data)
{
	
	int err = Error(5);
	if ((fileOpen == 1) && (err == 0))
	{
		int cur = 0;
		int i = numRecords;
		while (i != 0)
		{
			int size = 0;
			f.read((char *)&size, sizeof(size));
			cur += size + 4;
			f.seekg(cur, ios::beg);
			--i;
		}

		int size = (int)data.size();
		fSize += size + 4;
		f.write((char *)&size, sizeof(size));
		f.write((char *)data.c_str(), size);
		++numRecords;
		f.seekg(0, ios::beg);
		f.flush();
	}
}

int ClassBinaryFile::getNumRecords()
{
	int err = Error(4);

	int curRecords = 0;
	if ((fileOpen == 1) && err == 0)
	{
		int cur = 0;
		while (cur != fSize)
		{
			int size = 0;
			f.read((char *)&size, sizeof(size));
			cur += size + 4;
			++curRecords;
			f.seekg(cur, ios::beg);
		}

		f.seekg(0, ios::beg);
	}
	return curRecords;
}

string ClassBinaryFile::getBuffer(char * buf, int size)
{
	string rtn = "";

	for (int i = 0; i < size; ++i)
		rtn += buf[i];

	return rtn;

}

bool ClassBinaryFile::Open(string fPath, fileAccess access)
{
	if (access == in)
		f.open(fPath, ios::in | ios::binary);
	else if (access == out)
		f.open(fPath, ios::out | ios::trunc | ios::binary);
	else
		f.open(fPath, ios::in | ios::out | ios::binary);
		
	if (!f)
	{
		Error(1);
		return 0;
	}
	else
		fileOpen = 1;

	fAccess = access;

	f.seekp(0, ios::end);
	fSize = (int)f.tellg();
	f.seekp(0, ios::beg);
	
	fName = fPath;

	return 1;
}

void ClassBinaryFile::Close()
{
	f.close();
	fName = "";
	fileOpen = 0;

	fSize = 0;
	numRecords = 0;
	typeSize = 0;
}

int ClassBinaryFile::Error(int n)
{
	switch (n)
	{
		//out
		case 1:
		{
			if (fAccess == in || fAccess == inout)
			{
				outError(5);
				return 1;
			}
			break;
		}
		case 2:
		{
			//inout
			if (fAccess == in)
			{
				outError(3);
				return 1;
			}	
			break;
		}
		case 3:
		{
			//in
			if (fAccess == out)
			{
				outError(2);
				return 1;
			}
			break;
		}
		case 4:
		{
			if (fAccess == out)
			{
				Error(2);
				return 1;
			}
			break;
		}
		case 5:
		{
			if ((fAccess == in) || (fAccess == out))
			{
				outError(5);
				return 1;
			}
			break;
		}
	}
	return 0;
}

void ClassBinaryFile::outError(int n)
{
	switch (n)
	{

		case 1:
		{
			cout << "File not open" << endl;
			break;
		}
		case 2:
		{
			//out
			cout << "Access only Write command" << endl;
			break;
		}
		case 3:
		{
			//in
			cout << "Access only Read command" << endl;
			break;
		}
	case 4:
	{
		cout << "Not correction position for read" << endl;
		break;
	}
	case 5:
	{
		cout << "Commant does not match of access type" << endl;
		break;
	}
	}

}
