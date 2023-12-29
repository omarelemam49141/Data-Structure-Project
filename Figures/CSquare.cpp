#include "CSquare.h"

CSquare::CSquare(Point P1, int len, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	length = len;
}
	

void CSquare::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawSquare(TopLeftCorner, length, FigGfxInfo, Selected);
}

//omar
bool CSquare::IsPointInside(int x, int y)
{
	// Check if the point is within the bounds of the square
	return (x >= TopLeftCorner.x && x <= TopLeftCorner.x + length &&
		y >= TopLeftCorner.y && y <= TopLeftCorner.y + length);
}

//omar return the details
string CSquare::GetInfo()
{
	return "First point: (" + to_string(TopLeftCorner.x) + ", " + to_string(TopLeftCorner.y) + ")" + " - side length is: " + to_string(length);
}

//omar resize
void CSquare::resizeMe(int factor)
{
	length *= factor;
}