#ifndef CELLIPSE_H
#define CELLIPSE_H
#endif

#include "figures/CFigure.h"

class CEllipse : public CFigure
{
private:
	Point pointone;
	Point pointtwo;
public:
	CEllipse(Point, Point, GfxInfo FigureGfxInfo);
	virtual void DrawMe(GUI* pOut) const;
	//omar
	bool IsPointInside(int x, int y);
	virtual string GetInfo();
	virtual void resizeMe(int factor);
};
