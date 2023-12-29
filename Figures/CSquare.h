#ifndef CSQUARE_H
#define CSQUARE_H

#include "CFigure.h"

class CSquare : public CFigure
{
private:
	Point TopLeftCorner;	
	int length;
public:
	CSquare(Point , int, GfxInfo FigureGfxInfo );
	virtual void DrawMe(GUI* pOut) const;
	//omar
	bool IsPointInside(int x, int y);
	//omar
	virtual string GetInfo();
	//omar
	virtual void resizeMe(int factor);
};

#endif