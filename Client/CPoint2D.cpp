#include <SAMP+/client/CPoint2D.h>

CPoint2D::CPoint2D()
{
	m_x = m_y = 0;
}

CPoint2D::CPoint2D(unsigned long x, unsigned long y)
{
	m_x = x;
	m_y = y;
}

CPoint2D::~CPoint2D() {}

unsigned long& CPoint2D::X()
{
	return m_x;
}

unsigned long& CPoint2D::Y()
{
	return m_y;
}
