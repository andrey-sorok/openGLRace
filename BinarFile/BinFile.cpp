#include "BinFile.h"

#include "Rect2D.h"
#include "Triangle2D.h"
#include "Cycle.h"

#include <iostream>
#include <algorithm>
#include <string>
#include <memory>

#include <Windows.h>

bool CBinFile::Open(std::string fPath, fileAccess access)
{
	if (access == in)
		m_File.open(fPath, std::ios::in | std::ios::binary);
	else if (access == out)
		m_File.open(fPath, std::ios::out | std::ios::trunc | std::ios::binary);
	else
		m_File.open(fPath, std::ios::in | std::ios::out | std::ios::binary);

	if ( !m_File )
	{
		//Error(1);
		return 0;
	}
	else
		m_FileOpen = 1;

	m_fAccess = access;

	if (access == in)
	{
		m_File.seekp(0, std::ios::end);
		m_fSize = (int)m_File.tellg();
		m_File.seekp(0, std::ios::beg);
	}
	m_fName = fPath;

	return 1;
}

void CBinFile::Write(CFigureBase * pBase)
{
	if (pBase == nullptr)
		return;
	auto LmdWriteTypeColor = [&pBase](std::fstream & File)
	{
		EFigure fType = pBase->GetType();
		File.write((char*)&fType, sizeof(EFigure));

		CColor3D* color = pBase->GetColor();
		int size = sizeof(unsigned int);
		File.write((char *)&color->R, sizeof(size));
		File.write((char *)&color->G, sizeof(size));
		File.write((char *)&color->B, sizeof(size));

		return true;
	};

	EFigure fType = pBase->GetType();
	switch (fType)
	{
		case fPoint:
			break;

		case fLine:
			break;

		case fTriangle:
		{
			LmdWriteTypeColor(m_File);

			auto pTrian = dynamic_cast<CTriangle2D*>(pBase);
			TrianWrite(pTrian);
			break;
		}

		case fRectangle:
		{
			LmdWriteTypeColor(m_File);

			auto pRect = dynamic_cast<CRect2D*>(pBase);
			RectWrite(pRect);

			m_File.flush();
			break;
		}

		case fCycle:
		{
			LmdWriteTypeColor(m_File);
			auto pCycle = dynamic_cast<CCycle*>(pBase);

			CycleWrite(pCycle);

			m_File.flush();
			break;
		}

		case fCube:
			break;

		case fNone:
			break;

		default:
			break;
	}
	
}

std::shared_ptr<CFigureBase> CBinFile::Read()
{
	EFigure fType;
	int size = sizeof(EFigure);
	m_File.read((char *)&fType, sizeof(size));
	//m_File.seekg(size, std::ios::beg);

	auto LmdReadColor = [&fType](std::fstream & File)
	{
		CColor3D* color = new CColor3D(0, 0, 0);
		int size = sizeof(unsigned int);

		File.read((char *)&color->R, sizeof(size));
		File.read((char *)&color->G, sizeof(size));
		File.read((char *)&color->B, sizeof(size));

		return color;
	};

	switch (fType)
	{
		case fPoint:
			break;
	
		case fLine:
			break;
	
		case fTriangle:
		{
			CColor3D* color = LmdReadColor(m_File);

			auto pTrian = TrianRead();
			pTrian->SetColor(*color);
			
			return pTrian;
			break;
		}

		case fRectangle:
		{
			CColor3D* color = LmdReadColor(m_File);

			auto pRect = RectRead();
			pRect->SetColor(*color);
			
			return pRect;

			break;
		}

		case fCycle:
		{
			CColor3D* color = LmdReadColor(m_File);

			auto pCycle = CycleRead();
			pCycle->SetColor(*color);
			
			return pCycle;
			break;
		}

		case fCube:
			break;

		case fNone:
			break;
	
		default:
			break;
	}


	return nullptr;
}

std::vector<std::string> CBinFile::ReadFilesInDirectory(const std::string InPath, std::string InExtension)
{
	WIN32_FIND_DATA WFD;
	HANDLE hFind = FindFirstFile(InPath.c_str(), &WFD);

	std::vector<std::string> rtn;

	if (INVALID_HANDLE_VALUE != hFind)
	{
		while (FindNextFile(hFind, &WFD) != false)
		{
			std::string str = WFD.cFileName;
			///std::string str = std::to_string(wStrChar);

			auto f = str.find_first_of(".");
			if (str.substr(f + 1, str.length()) == InExtension.c_str())
			{
				auto f = InPath.find("*");
				rtn.push_back(InPath.substr(0, f) + str);
			}
		}

		FindClose(hFind);
	}

	return rtn;
}

std::shared_ptr<CRect2D> CBinFile::RectRead()
{
	int size = sizeof(float);
	CPoint2D* P1 = new CPoint2D(0, 0);
	CPoint2D* P3 = new CPoint2D(0, 0);

	m_File.read((char *)&P1->x, sizeof(size));
	m_File.read((char *)&P1->y, sizeof(size));

	m_File.read((char *)&P3->x, sizeof(size));
	m_File.read((char *)&P3->y, sizeof(size));

	auto pRect = std::make_shared<CRect2D>(*P1, *P3, CColor3D(0,0,0));
	return pRect;
}

std::shared_ptr<CTriangle2D> CBinFile::TrianRead()
{
	int size = sizeof(float);

	CPoint2D* P1 = new CPoint2D(0, 0);
	CPoint2D* P2 = new CPoint2D(0, 0);
	CPoint2D* P3 = new CPoint2D(0, 0);

	m_File.read((char *)&P1->x, sizeof(size));
	m_File.read((char *)&P1->y, sizeof(size));

	m_File.read((char *)&P2->x, sizeof(size));
	m_File.read((char *)&P2->y, sizeof(size));

	m_File.read((char *)&P3->x, sizeof(size));
	m_File.read((char *)&P3->y, sizeof(size));

	auto pTrian = std::make_shared<CTriangle2D>(*P1, *P2, *P3, CColor3D(0,0,0));
	return pTrian;
}

std::shared_ptr<CCycle> CBinFile::CycleRead()
{
	CPoint2D* center = new CPoint2D(0, 0);
	double radius = 0.00;

	int size = sizeof(float);
	m_File.read((char *)&center->x, sizeof(size));
	m_File.flush();
	m_File.read((char *)&center->y, sizeof(size));
	m_File.flush();

	m_File.read((char *)&radius, sizeof(double));
	m_File.flush();

	auto pCycle = std::make_shared<CCycle>(*center, radius, CColor3D(0, 0, 0));
	return pCycle;
}

void CBinFile::RectWrite(CRect2D * InRect)
{
	std::list<CPoint2D*> lPoints = InRect->GetPoints();
	
	int size = sizeof(float);
	CPoint2D* P1 = lPoints.front();
	lPoints.pop_front();
	lPoints.pop_front();
	CPoint2D* P3 = lPoints.front();

	m_File.write((char *)&P1->x, sizeof(size));
	m_File.flush();
	m_File.write((char *)&P1->y, sizeof(size));
	m_File.flush();

	m_File.write((char *)&P3->x, sizeof(size));
	m_File.flush();
	m_File.write((char *)&P3->y, sizeof(size));
	m_File.flush();
}

void CBinFile::TrianWrite(CTriangle2D * InTrian)
{
	std::list<CPoint2D*> lPoints = InTrian->GetPoints();

	int size = sizeof(float);
	CPoint2D* P1 = lPoints.front();
	lPoints.pop_front();
	CPoint2D* P2 = lPoints.front();
	lPoints.pop_front();
	CPoint2D* P3 = lPoints.front();
	lPoints.pop_front();

	m_File.write((char *)&P1->x, sizeof(size));
	m_File.flush();
	m_File.write((char *)&P1->y, sizeof(size));
	m_File.flush();

	m_File.write((char *)&P2->x, sizeof(size));
	m_File.flush();
	m_File.write((char *)&P2->y, sizeof(size));
	m_File.flush();

	m_File.write((char *)&P3->x, sizeof(size));
	m_File.flush();
	m_File.write((char *)&P3->y, sizeof(size));
	m_File.flush();
}

void CBinFile::CycleWrite(CCycle * InCycle)
{
	CPoint2D center = InCycle->GetCenter();
	CPoint2D* pCenter = new CPoint2D(center.x, center.y);

	double radius = InCycle->GetRadius();
	
	int size = sizeof(float);
	m_File.write((char *)&pCenter->x, sizeof(size));
	m_File.write((char *)&pCenter->y, sizeof(size));

	m_File.write((char *)&radius, sizeof(double));
}

CBinFile::CBinFile(): m_fSize(0), m_FileOpen(false)
{
}

CBinFile::~CBinFile()
{
}

void CBinFile::CreateOutFile(std::string fPath, fileAccess access, int& InNumCars)
{
	InNumCars++;
	TCHAR buffer[MAX_PATH];
	GetCurrentDirectory(sizeof(buffer), buffer);
	std::string Path = buffer;

	auto last = Path.find_last_of("\\", Path.length());

	Path = Path.substr(0, last + 1);
	m_fName = Path + fPath + "\\" + std::to_string(InNumCars) + ".race";
	Open(m_fName, access);
}

void CBinFile::WriteFile(CFigureBase * pBase)
{
	Write(pBase);
}

std::vector<std::shared_ptr<CFigureBase>> CBinFile::ReadFile(std::string fPath)
{
	m_fName = fPath;
	Open(m_fName, in);
	
	std::vector<std::shared_ptr<CFigureBase>> pRtnFigure;

	if (m_FileOpen == 1)
	{
		do
		{
			auto pFigure = Read();
			if(pFigure.get() != nullptr)
				pRtnFigure.emplace_back(pFigure);
		} while (!m_File.eof());
	}
	return pRtnFigure;
}

std::vector<std::string> CBinFile::ReadNamesFiles(std::string fPath)
{
	TCHAR buffer[MAX_PATH];
	GetCurrentDirectory(sizeof(buffer), buffer);
	std::string Path = buffer;

	auto last = Path.find_last_of("\\", Path.length());

	Path = Path.substr(0, last + 1);

	Path = Path + fPath + "\\*";
	std::string Ext = "race";
	std::vector<std::string> rtn = ReadFilesInDirectory(Path, Ext);

	return rtn;
}

void CBinFile::CloseFile()
{
	m_File.close();
	m_fName = "";
	m_FileOpen = 0;

	m_fSize = 0;
}

int CBinFile::GetNumFiles(std::string InPath, std::string InExtension)
{
	TCHAR buffer[MAX_PATH];
	GetCurrentDirectory(sizeof(buffer), buffer);
	std::string Path = buffer;

	auto last = Path.find_last_of("\\", Path.length());

	Path = Path.substr(0, last + 1);

	Path = Path + InPath + "\\*";
	std::vector<std::string> rtn = ReadFilesInDirectory(Path, InExtension);

	return rtn.size();
}
