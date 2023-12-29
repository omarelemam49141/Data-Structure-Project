#include "CEllipse.h"
CEllipse::CEllipse(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	pointone = P1;
	pointtwo = P2;
}


void CEllipse::DrawMe(GUI* pGUI) const
{
	//Call Output::Draw Ellipse	
	pGUI->DrawEllipse(pointone, pointtwo, FigGfxInfo, Selected);
}

bool CEllipse::IsPointInside(int x, int y)
{
    // Calculate the normalized coordinates relative to the center
    double normalizedX = (x - (pointone.x + pointtwo.x) / 2.0) / ((pointtwo.x - pointone.x) / 2.0);
    double normalizedY = (y - (pointone.y + pointtwo.y) / 2.0) / ((pointtwo.y - pointone.y) / 2.0);

    // Check if the point satisfies the ellipse equation
    return (normalizedX * normalizedX + normalizedY * normalizedY) <= 1.0;
}

string CEllipse::GetInfo()
{
    return "First point: (" + to_string(pointone.x) + ", " + to_string(pointone.y) + ")" + 
        " - Second point: (" + to_string(pointtwo.x) + ", " + to_string(pointtwo.y) + ")";
}

//omar
void CEllipse::resizeMe(int factor)
{
    // Calculate the center of the ellipse
    double centerX = (pointone.x + pointtwo.x) / 2;
    double centerY = (pointone.y + pointtwo.y) / 2;

    // Resize the distance from the center to the second point by the factor
    double newRadiusX = factor * (pointtwo.x - centerX) / 2;
    double newRadiusY = factor * (pointtwo.y - centerY) / 2;

    // Update the coordinates of the second point
    pointtwo.x = centerX + newRadiusX;
    pointtwo.y = centerY + newRadiusY;

    //check if it exceeds the drawing area
}

//omar //does it excceds the drawing area

//omar return the details