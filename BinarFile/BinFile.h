#ifndef __BINFILE_
#define __BINFILE_

#include "Types.h"
#include "FigureBase.h"

#include <vector>
#include <string>
#include <fstream>
#include <memory>

class CRect2D;
class CTriangle2D;
class CCycle;

class CBinFile
{
private:

	std::string m_fName;
	std::fstream m_File;

	int m_fSize;
	int m_NumCurs;

	fileAccess m_fAccess;

	bool m_FileOpen;

	bool Open(std::string fPath, fileAccess access);
	void Write(CFigureBase* pBase);
	std::shared_ptr<CFigureBase> Read();

	std::vector<std::string> ReadFilesInDirectory(const std::string InPath, std::string InExtension);

	std::shared_ptr<CRect2D> RectRead();
	std::shared_ptr<CTriangle2D> TrianRead();
	std::shared_ptr<CCycle> CycleRead();

	void RectWrite(CRect2D * InRect);
	void TrianWrite(CTriangle2D * InTrian);
	void CycleWrite(CCycle * InCycle);

public:
	CBinFile();
	~CBinFile();

	void CreateOutFile(std::string fPath, fileAccess access, int& InNumCars);
	void WriteFile(CFigureBase* pBase);
	
	std::vector<std::shared_ptr<CFigureBase>> ReadFile(std::string fPath);
	
	std::vector<std::string> ReadNamesFiles(std::string fPath);
	void CloseFile();

	int GetNumFiles(std::string InPath, std::string InExtension);
};

#endif //__BINFILE_