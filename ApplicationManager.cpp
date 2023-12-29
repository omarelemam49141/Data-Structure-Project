#include "ApplicationManager.h"
#include "Actions\ActionAddSquare.h"
#include "ActionAddEllipse.h"
#include "ActionAddHexagon.h"
#include "ActionChngDrawClr.h"
#include "ActionChngFillClr.h"
#include "ActionChngBGClr.h"
#include "ActionSelect.h"
#include "ActionChngFigureClr.h"
#include "ActionDelete.h"

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pGUI = new GUI;	
	
	FigCount = 0;
		
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
}

void ApplicationManager::Run()
{
	ActionType ActType;
	do
	{		
		//1- Read user action
		ActType = pGUI->MapInputToActionType();

		//2- Create the corresponding Action
		Action *pAct = CreateAction(ActType);
		
		//3- Execute the action
		ExecuteAction(pAct);

		//4- Update the interface
		UpdateInterface();	

	}while(ActType != EXIT);
	
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
//Creates an action
Action* ApplicationManager::CreateAction(ActionType ActType) 
{
	Action* newAct = NULL;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_SQUARE:
			newAct = new ActionAddSquare(this);
			break;
		case DRAW_ELPS:
			newAct = new ActionAddEllipse(this);
			break;
		case DRAW_HEX:
			newAct = new ActionAddHexagon(this);
			break;
		case CHNG_DRAW_CLR:
			newAct = new ActionChngDrawClr(this);
			break;
		case CHNG_FILL_CLR:
			newAct = new ActionChngFillClr(this);
			break;
		case CHNG_BK_CLR:
			newAct = new ActionChngBGClr(this);
			break;
		case DRAWING_AREA:
			newAct = new ActionSelect(this);
			break;
		case CHNG_FIG_CLR:
			newAct = new ActionChngFigureClr(this);
			break;
		case DEL:
			newAct = new ActionDelete(this);
			break;
		case EXIT:
			///create ExitAction here
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return NULL;
			break;
	}	
	return newAct;
}
//////////////////////////////////////////////////////////////////////
//Executes the created Action
void ApplicationManager::ExecuteAction(Action* &pAct) 
{	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount)
		FigList[FigCount++] = pFig;	
}
//Delete a figure from the list of figures
//Omar
void ApplicationManager::DeleteFigureAndRearrange(CFigure* pFig, int index)
{
	delete pFig;

	for (int i = index; i < FigCount - 1; i++)
	{
		FigList[i] = FigList[i + 1];
	}

	FigList[FigCount - 1] = NULL;
	FigCount--;
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL


	///Add your code here to search for a figure given a point x,y	
	//Omar
	for (int i = FigCount - 1; i >= 0; i--)
	{
		if (FigList[i]->IsPointInside(x,y))
			return FigList[i];
	}

	return NULL;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	for(int i=0; i<FigCount; i++)
		FigList[i]->DrawMe(pGUI);		//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
// 
// CFigure* currentFigure = NULL;
bool ApplicationManager::DeleteSelectedObjects()
{
	bool selected = false;
	int countDeleted = 0;
	for (int i = FigCount-1; i >= 0; i--)
	{
		if (FigList[i]->IsSelected())
		{
			DeleteFigureAndRearrange(FigList[i], i);
			pGUI->PrintMessage("Deleted successfully");
			countDeleted++;
		}
	}

	return countDeleted > 0;
}

//omar
//loop through the figures, if selected then multiplicate it by factor
//if no selected at all, then return false

CFigure* ApplicationManager::GetFigureByIndex(int index)
{
	return FigList[index];
}

int ApplicationManager::GetCount()
{
	return FigCount;
}

//Return a pointer to the interface
GUI *ApplicationManager::GetGUI() const
{	return pGUI; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pGUI;
	
}

