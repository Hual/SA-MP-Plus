#pragma once

class CPoint2D
{
public:
	CPoint2D();
	CPoint2D(unsigned int long, unsigned long y);
	virtual ~CPoint2D();
	unsigned long& X();
	unsigned long& Y();

private:
	unsigned long m_x;
	unsigned long m_y;

};
