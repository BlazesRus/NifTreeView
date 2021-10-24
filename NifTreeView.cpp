// ***********************************************************************
// Code Created by James Michael Armstrong (https://github.com/BlazesRus)
// Latest Code Release at https://github.com/BlazesRus/NifTreeView under Boost Software License 1.0 
// (MainProject this is submodule to at https://github.com/BlazesRus/BlazesRusSharedCode)
// Other Required submodule at https://github.com/BlazesRus/MFCApp
// ***********************************************************************
#include "AppPch.h"
#include "NifTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// NifTreeView
IMPLEMENT_DYNCREATE(NifTreeView, MFCView)

BEGIN_MESSAGE_MAP(NifTreeView, MFCView)
#ifndef BlazesMFCApp_DisablePrinter
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, &MFCView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &MFCView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &MFCView::OnFilePrintPreview)
#endif
END_MESSAGE_MAP()

// NifTreeView construction/destruction

NifTreeView::NifTreeView() noexcept
{

}

BOOL NifTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs
    return MFCView::PreCreateWindow(cs);
}

#pragma region File Loading And Saving
bool NifTreeView::LoadDataFromFile(std::string FilePath)
{
    Reset();
    char LineChar;
    std::string LineString="";
    std::ifstream inFile;
    inFile.open(FilePath);
    if (!inFile)
    {
        return false;
    }
    while (inFile >> LineChar)
    {
        if (LineChar != '\n')
        {
            ContentList.Add(LineString); LineString.clear();
        }
        else
            LineString += LineChar;
    }
    if (!LineString.empty())
        ContentList.Add(LineString);
    return true;
}

void NifTreeView::SaveDataToFile(std::string FilePath)
{
    if (FilePath.back() == '/' || FilePath.back() == '\\') { FilePath += "TextFile.txt"; }
    //size_t StringLength;
    //char StringChar;
    //std::string LineString;
    //std::fstream LoadedFileStream;
    ////Fix for non-existing file
    //CreateFileIfDoesntExist(FilePath);
    //LoadedFileStream.open(FilePath.c_str(), std::fstream::out | std::fstream::trunc);
    //if (LoadedFileStream.is_open())
    //{
    //	if (LoadedFileStream.good())
    //	{//Saving to file now
    //		//for (ContentList::iterator ArgElement = ContentList.begin(), EndElement = ContentList.end(); ArgElement != EndElement; ++ArgElement)
    //		//{
    //		//	LoadedFileStream << ArgElement << "\n";
    //		//}
    //	}
    //	else
    //	{
    //		if (LoadedFileStream.bad()) { std::cout << "Failed Read/Write operation Error!\n"; }
    //		else if (LoadedFileStream.fail()) { std::cout << "Failed format based Error!\n"; }
    //		else if (LoadedFileStream.bad()) { std::cout << "Failed Read/Write operation Error!\n"; }
    //		else if (LoadedFileStream.eof()) {/*Send debug message of reaching end of file?*/ }
    //	}
    //	LoadedFileStream.close();
    //}
    //else
    //{
    //	std::cout << "Failed to open " << FilePath << ".\n";
    //}
    ContentList.SaveDataToFileV3(FilePath, true);
}
#pragma endregion File Loading And Saving

// NifTreeView drawing

void NifTreeView::OnDraw(CDC* /*pDC*/)
{
    MFCDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // TODO: add draw code for native data here
}

#pragma region Printer Features
#ifndef BlazesMFCApp_DisablePrinter
// NifTreeView printing
BOOL NifTreeView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default preparation
    return DoPreparePrinting(pInfo);
}

void NifTreeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void NifTreeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}
#endif
#pragma endregion Printer Features

#pragma region NifTreeView diagnostics
#ifdef _DEBUG
void NifTreeView::AssertValid() const
{
    MFCView::AssertValid();
}

void NifTreeView::Dump(CDumpContext& dc) const
{
    MFCView::Dump(dc);
}

MFCDoc* NifTreeView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(MFCDoc)));
    return (MFCDoc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion NifTreeView diagnostics

// NifTreeView message handlers
