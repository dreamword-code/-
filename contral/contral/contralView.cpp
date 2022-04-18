
// contralView.cpp: CcontralView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "contral.h"
#endif

#include "contralDoc.h"
#include "contralView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CcontralView

IMPLEMENT_DYNCREATE(CcontralView, CView)

BEGIN_MESSAGE_MAP(CcontralView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CcontralView 构造/析构

CcontralView::CcontralView() noexcept
{
	// TODO: 在此处添加构造代码

}

CcontralView::~CcontralView()
{
}

BOOL CcontralView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CcontralView 绘图

void CcontralView::OnDraw(CDC* /*pDC*/)
{
	CcontralDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CcontralView 打印

BOOL CcontralView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CcontralView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CcontralView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CcontralView 诊断

#ifdef _DEBUG
void CcontralView::AssertValid() const
{
	CView::AssertValid();
}

void CcontralView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CcontralDoc* CcontralView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CcontralDoc)));
	return (CcontralDoc*)m_pDocument;
}
#endif //_DEBUG


// CcontralView 消息处理程序
