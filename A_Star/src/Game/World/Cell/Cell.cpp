
#include "Cell.h"

#include "../../../../../lib/gplib.h"

Cell* Cell::m_pGoal;
Cell::Cell(Vector2D Center, double Size, int Type)
	:
	m_vCenter(Center),
	m_dSize(Size),
	m_iType(Type),
	m_FrameColor({ /*255*/0,255,255,255 })
{

}

Cell::~Cell()
{

}

void Cell::Update()
{
	switch (m_iType)
	{
	case Cell::normal:
		Disable_Fill();
		break;
	case Cell::wall:
		Enable_Fill();
		m_FillColor = { 255,166,91,35 };
		break;
	case Cell::route:
		Enable_Fill();
		m_FillColor = { 255,77,110,250 };
		break;
	case Cell::goal:
		m_FillColor = { 255,255,0,0 };
		Enable_Fill();
		break;
	}
}

void Cell::Render()
{
	gplib::graph::Draw_BoxCenter(static_cast<float>(m_vCenter.x), static_cast<float>(m_vCenter.y), static_cast<float>(m_dSize), static_cast<float>(m_dSize), 0.1f, ARGB(m_FillColor.m_iAlpha, m_FillColor.m_iRed, m_FillColor.m_iGreen, m_FillColor.m_iBlue), ARGB(m_FrameColor.m_iAlpha, m_FrameColor.m_iRed, m_FrameColor.m_iGreen, m_FrameColor.m_iBlue), 1, m_bFill);
}