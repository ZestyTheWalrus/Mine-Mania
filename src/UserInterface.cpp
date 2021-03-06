#include "..\include\UserInterface.h"
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <functional>
#include <fstream>

using namespace std;

namespace game
{
	extern void Log(std::string txt);
}


UserInterface::UserInterface()
{
	isHidden_ = false;
	isPosVariablesSet_ = false;
	isSelectionAvailable_ = false;
	isSelectionActivated_ = false;
	isInIMode_ = false;
	isSlideUI_ = false;
	curSelected_ = 0;
	sectionAmount_ = 0;
}

UserInterface::UserInterface(unsigned int size_x, unsigned int size_y, unsigned int offset_x, unsigned int offset_y)
{
	isHidden_ = false;
	isPosVariablesSet_ = true;
	isSelectionAvailable_ = false;
	isSelectionActivated_ = false;
	isInIMode_ = false;
	isSlideUI_ = false;
	curSelected_ = 0;
	sectionAmount_ = 0;
	positionVars_.size_x = size_x;
	positionVars_.size_y = size_y;
	positionVars_.offset_x = offset_x;
	positionVars_.offset_y = offset_y;
	positionVars_.border_width = 0;
}


UserInterface::~UserInterface()
{
	iManager.isExit(true);
	if (iManage.joinable())
	{
		iManage.join();
	}
}

void UserInterface::isHidden(bool isHidden)
{
	isHidden_ = isHidden;
	if (isHidden == false)
	{
		reDrawAll();
	}
	else
	{
		hide();
	}
}

bool UserInterface::isHidden()
{
	return isHidden_;
}

void UserInterface::addSection(Section newSection)
{
	sectionAmount_++;

	newSection.setIndex(sectionAmount_);

	sections[sectionAmount_] = newSection;

	redraws.push_back(sectionAmount_);

	if (newSection.isSelectable())
	{
		if (isSelectionAvailable_ == false)
		{
			isSelectionAvailable_ = true;
			curSelected_ = sectionAmount_;
		}
	}
}

void UserInterface::addSection(string text)
{
	sectionAmount_++;
	
	Section newSection(sectionAmount_, text, false, true);

	sections[sectionAmount_] = newSection;

	redraws.push_back(sectionAmount_);
}

void UserInterface::addSection(string text, bool isSelectable)
{
	sectionAmount_++;

	Section newSection(sectionAmount_, text, isSelectable, false);

	sections[sectionAmount_] = newSection;

	redraws.push_back(sectionAmount_);

	if (newSection.isSelectable())
	{
		if (isSelectionAvailable_ == false)
		{
			isSelectionAvailable_ = true;
			curSelected_ = sectionAmount_;
		}
	}
}

void UserInterface::addSection(string text, bool isSelectable, bool isNumberHidden)
{
	sectionAmount_++;

	Section newSection(sectionAmount_, text, isSelectable, isNumberHidden);

	sections[sectionAmount_] = newSection;

	redraws.push_back(sectionAmount_);

	if (newSection.isSelectable())
	{
		if (isSelectionAvailable_ == false)
		{
			isSelectionAvailable_ = true;
			curSelected_ = sectionAmount_;
		}
	}
}

void UserInterface::addSlide(string text)
{
	slideSectionAdd_.push_back(text);
}

void UserInterface::push_back(Section newSection)
{
	sectionAmount_++;

	newSection.setIndex(sectionAmount_);

	sections[sectionAmount_] = newSection;

	redraws.push_back(sectionAmount_);

	if (newSection.isSelectable())
	{
		if (isSelectionAvailable_ == false)
		{
			isSelectionAvailable_ = true;
			curSelected_ = sectionAmount_;
		}
	}
}

void UserInterface::push_back(string text)
{
	sectionAmount_++;

	Section newSection(sectionAmount_, text, false, true);

	sections[sectionAmount_] = newSection;

	redraws.push_back(sectionAmount_);
}

void UserInterface::push_back(string text, bool isSelectable)
{
	sectionAmount_++;

	Section newSection(sectionAmount_, text, isSelectable, false);

	sections[sectionAmount_] = newSection;

	redraws.push_back(sectionAmount_);

	if (newSection.isSelectable())
	{
		if (isSelectionAvailable_ == false)
		{
			isSelectionAvailable_ = true;
			curSelected_ = sectionAmount_;
		}
	}
}

void UserInterface::push_back(string text, bool isSelectable, bool isNumberHidden)
{
	sectionAmount_++;

	Section newSection(sectionAmount_, text, isSelectable, isNumberHidden);

	sections[sectionAmount_] = newSection;

	redraws.push_back(sectionAmount_);

	if (newSection.isSelectable())
	{
		if (isSelectionAvailable_ == false)
		{
			isSelectionAvailable_ = true;
			curSelected_ = sectionAmount_;
		}
	}
}

void UserInterface::push_isection(string text)
{
	sectionAmount_++;
	Section iSection;
	iSection.isISection(true);
	iSection.setText(text);
	iSection.setIndex(sectionAmount_);
	iSection.isSelectable(true);
	sections[sectionAmount_] = iSection;
	if (isSelectionAvailable_ == false)
	{
		isSelectionAvailable_ = true;
		curSelected_ = sectionAmount_;
	}

	redraws.push_back(sectionAmount_);
}

void UserInterface::push_isection(string text, int maxIText)
{
	sectionAmount_++;
	Section iSection;
	iSection.isISection(true);
	iSection.setIText(text);
	iSection.setMaxIText(maxIText);
	iSection.setIndex(sectionAmount_);
	iSection.isSelectable(true);
	sections[sectionAmount_] = iSection;
	if (isSelectionAvailable_ == false)
	{
		isSelectionAvailable_ = true;
		curSelected_ = sectionAmount_;
	}

	redraws.push_back(sectionAmount_);
}

void UserInterface::setPositionVariables(PositionVariables posV)
{
	positionVars_ = posV;

	isPosVariablesSet_ = true;
}

Section& UserInterface::getSectionRef(uint16_t sectionIndex)
{
	if (sections.count(sectionIndex))
	{
		return sections[sectionIndex];
	}
}

Section UserInterface::getSection(uint16_t sectionIndex)
{
	if (sections.count(sectionIndex))
	{
		return sections[sectionIndex];
	}
}

bool UserInterface::isSectionActivated()
{
	if (isSelectionActivated_ == true)
	{
		isSelectionActivated_ = false;
		return true;
	}
	return false;
}

int UserInterface::getActivatedSection()
{
	return (int)curSelected_;
}

void UserInterface::initializeSlideUI()
{
	isSlideUI_ = true;
}

void UserInterface::moveSelectionUp()
{
	redraws.push_back(curSelected_);
	if (isSelectionAvailable_ == false)
		return;

	curSelected_--;
	if (curSelected_ == 0)
		curSelected_ = sectionAmount_;

	while (sections[curSelected_].isSelectable() != true)
	{
		curSelected_--;
		if (curSelected_ == 0)
			curSelected_ = sectionAmount_;
	}
	redraws.push_back(curSelected_);
}

void UserInterface::moveSelectionDown()
{
	redraws.push_back(curSelected_);
	if (isSelectionAvailable_ == false)
		return;

	curSelected_++;
	if (curSelected_ > sectionAmount_)
		curSelected_ = 1;

	while (sections[curSelected_].isSelectable() != true)
	{
		curSelected_++;
		if (curSelected_ > sectionAmount_)
			curSelected_ = 1;
	}
	redraws.push_back(curSelected_);
}

void UserInterface::moveSlideDown()
{
	auto iter = SlideSections.rbegin();
	auto end = SlideSections.rend();
	bool deleteLast = false;
	uint16_t theDelete;
	for (; iter != end; iter++)
	{
		if (iter->first == positionVars_.size_y)
		{
			deleteLast = true;
			theDelete = iter->first;
		}
		else
		{
			SlideSections[iter->first + 1] = iter->second;
			SlideSections[iter->first] = "";
		}
	}
	if (deleteLast == true)
	{
		SlideSections.erase(theDelete);
	}
}

void UserInterface::update()
{
	if (isPosVariablesSet_ == false)
		return;
	if (isSlideUI_ == false)
	{
		for (auto& iter : sections)
		{
			if (iter.second.redraw() == true)
				redraws.push_back(iter.second.getIndex());
		}
		if (redraws.empty() == false)
		{
			for (auto& iter : redraws)
			{
				draw(iter);
			}
			redraws.clear();
		}

		if (isSelectionAvailable_)
		{
			if (inputCoolDown.Update() == true)
			{
				if (isInIMode_ == false)
				{
					if (GetAsyncKeyState('W'))
					{
						moveSelectionUp();
						inputCoolDown.StartNewTimer(0.175);
						return;
					}
					if (GetAsyncKeyState('S'))
					{
						moveSelectionDown();
						inputCoolDown.StartNewTimer(0.175);
						return;
					}
					if (GetAsyncKeyState(VK_RETURN))
					{
						if (sections[curSelected_].isISection() == true)
						{
							isInIMode_ = true;
							iManager.clear();
							iManager.isExit(false);
							FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
							redraws.push_back(curSelected_);
						}
						else
						{
							isSelectionActivated_ = true;
						}
						inputCoolDown.StartNewTimer(0.175);
						return;
					}
				}
				else
				{
					if (GetAsyncKeyState(VK_RETURN))
					{
						isInIMode_ = false;
						iManager.clear();
						iManager.isExit(true);
						draw(curSelected_);
						Sleep(250);
						if (iManage.joinable())
						{
							iManage.join();
						}
						FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
						isSelectionActivated_ = true;
						return;
					}
					if (GetAsyncKeyState(VK_ESCAPE))
					{
						hide();
						isInIMode_ = false;
						iManager.clear();
						iManager.isExit(true);
						draw(curSelected_);
						Sleep(250);
						if (iManage.joinable())
						{
							iManage.join();
						}
						FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
						isSelectionActivated_ = true;
						return;
					}
					iManager.start();
					while (iManager.inputAvailable())
					{
						char key = iManager.getInput();
						string skey;
						skey.push_back(key);
						sections[curSelected_].addIText(skey);
					}
					if (GetAsyncKeyState(VK_BACK))
					{
						sections[curSelected_].removeIText();
						inputCoolDown.StartNewTimer(0.100);
					}
				}
			}
		}
	}
	else
	{
		if (inputCoolDown.Update() == true)
		{
			if (SlideSections.empty() == false)
			{
				moveSlideDown();
				inputCoolDown.StartNewTimer(0.100);
			}
			if (slideSectionAdd_.empty() == false)
			{
				SlideSections[0] = slideSectionAdd_.front();
				slideSectionAdd_.pop_front();
			}
			for (auto& iter : SlideSections)
			{
				slideDraw(iter.first, iter.second);
			}
		}
	}
}

void UserInterface::reset()
{
	sections.clear();
	curSelected_ = 0;
	isSelectionActivated_ = false;
	isSelectionAvailable_ = false;
	isHidden_ = false;
	isPosVariablesSet_ = false;
	inputCoolDown.StartNewTimer(0.0001);
	sectionAmount_ = 0;
	positionVars_.size_x = 0;
	positionVars_.size_y = 0;
	positionVars_.offset_x = 0;
	positionVars_.offset_y = 0;
}

void UserInterface::draw(uint16_t index)
{
	if (sections.count(index))
	{
		unsigned int offset_y = positionVars_.offset_y + (positionVars_.border_width * 2);
		offset_y += index - 1;
		SetCursorPosition(positionVars_.offset_x+positionVars_.border_width, offset_y);
		if (curSelected_ == index)
		{
			if (sections[index].isISection() == true)
			{
				if (isInIMode_ == true)
				{
					cout << sections[index]() + "_" + "       ";
				}
				else
				{
					cout << sections[index]() + " <-" + "          ";
				}
			}
			else
			{
				cout << sections[index]() + " <-" + "       ";
			}
		}
		else
		{
			cout << sections[index]() << "          ";
		}
	}
}

extern void setCursorPos(int x, int y);

void UserInterface::slideDraw(uint16_t index, string text)
{

	setCursorPos(positionVars_.offset_x, index);
	cout << text << "               ";
}

void UserInterface::slideClear(uint16_t index)
{
	setCursorPos(positionVars_.offset_x, index);
	cout << "          ";
}

void UserInterface::reDrawAll()
{
	for (auto& iter: sections)
	{
		redraws.push_back(iter.second.getIndex());
	}
}

void UserInterface::SetCursorPosition(int x, int y)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(h, pos);
}

void UserInterface::hide()
{
	for (auto& iter : sections)
	{
		unsigned int offset_y = positionVars_.offset_y + (positionVars_.border_width * 2);
		offset_y += iter.second.getIndex() - 1;
		SetCursorPosition(positionVars_.offset_x + positionVars_.border_width, offset_y);
		string text = iter.second();
		if (iter.second.getIndex() == curSelected_)
			text += " <-    ";
		cout << createClearLine(text.length());
	}
}

void UserInterface::log(string text)
{
	fstream file("Logs\\Log.txt", ios::app);

	file << text << endl;

	file.close();
}

string UserInterface::createClearLine(int x)
{
	string text;
	for (int i = 0; i < x; i++)
	{
		text += " ";
	}
	return text;
}


/* Section */
/////////////////////////////////////////////////////
Section::Section()
{
	index_ = 0;
	varIndex_ = 0;
	text_ = "";
	isSelectable_ = false;
	isNumberHidden_ = true;
	isHidden_ = false;
	isISection_ = false;
	redraw_ = false;
	maxIText_ = 20;
}

Section::Section(uint16_t index, string text)
{
	index_ = index;
	text_ = text;
	varIndex_ = 0;
	isSelectable_ = false;
	isNumberHidden_ = true;
	isHidden_ = false;
	redraw_ = false;
	isISection_ = false;
	maxIText_ = 20;
}

Section::Section(uint16_t index, string text, bool isSelectable)
{
	index_ = index;
	text_ = text;
	varIndex_ = 0;
	isSelectable_ = isSelectable;
	isNumberHidden_ = true;
	isHidden_ = false;
	redraw_ = false;
	isISection_ = false;
	maxIText_ = 20;
}

Section::Section(uint16_t index, string text, bool isSelectable, bool isNumberHidden)
{
	index_ = index;
	text_ = text;
	varIndex_ = 0;
	isSelectable_ = isSelectable;
	isNumberHidden_ = isNumberHidden;
	isHidden_ = false;
	redraw_ = false;
	isISection_ = false;
	maxIText_ = 20;
}

uint16_t Section::getIndex()
{
	return index_;
}

void Section::isSelectable(bool isSelectable)
{
	isSelectable_ = isSelectable;
}

void Section::isNumberHidden(bool isHidden)
{
	isNumberHidden_ = isHidden;
}

void Section::isHidden(bool isHidden)
{
	isHidden_ = isHidden;
}

void Section::setText(string text)
{
	text_ = text;
}

void Section::setIndex(uint16_t index)
{
	index_ = index;
}

void Section::setMaxIText(int length)
{
	maxIText_ = length;
}

void Section::addVar(int var)
{
	varIndex_++;

	Variable newVar(var);

	variables[varIndex_] = newVar;

	redraw_ = true;

	return;
}

void Section::addVar(double var)
{
	varIndex_++;

	Variable newVar(var);

	variables[varIndex_] = newVar;

	redraw_ = true;

	return;
}

void Section::addVar(string var)
{
	varIndex_++;

	Variable newVar(var);

	variables[varIndex_] = newVar;
	
	redraw_ = true;

	return;
}

void Section::addIText(string iText)
{
	iText_ += iText;
	/*if (iText_.length() > maxIText_)
	{
		iText_ = iText_.substr(0, maxIText_);
	}*/
	redraw_ = true;
}

void Section::removeIText()
{
	if (iText_.empty()==false)
	{
		iText_.pop_back();
		redraw_ = true;
	}
}

void Section::push_backVar(int var)
{
	varIndex_++;

	Variable newVar(var);

	variables[varIndex_] = newVar;

	redraw_ = true;

	return;
}

void Section::push_backVar(double var)
{
	varIndex_++;

	Variable newVar(var);

	variables[varIndex_] = newVar;

	redraw_ = true;

	return;
}

void Section::push_backVar(string var)
{
	varIndex_++;

	Variable newVar(var);

	variables[varIndex_] = newVar;

	redraw_ = true;

	return;
}

void Section::setVar(uint16_t varIndex, int var)
{
	if (variables.count(varIndex))
	{
		if (variables[varIndex].getInt() == var)
		{
			return;
		}
		else
		{
			variables[varIndex].setVar(var);
			redraw_ = true;
		}
	}
}

void Section::setVar(uint16_t varIndex, double var)
{
	if (variables.count(varIndex))
	{
		if (variables[varIndex].getDou() == var)
		{
			return;
		}
		else
		{
			variables[varIndex].setVar(var);
			redraw_ = true;
		}
	}
}

void Section::setVar(uint16_t varIndex, string var)
{
	if (variables.count(varIndex))
	{
		if (variables[varIndex].getStr() == var)
		{
			return;
		}
		else
		{
			variables[varIndex].setVar(var);
			redraw_ = true;
		}
	}
}

void Section::setIVar(string text)
{
	iText_ = text;
	if (iText_.length() > maxIText_)
	{
		iText_ = iText_.substr(0, maxIText_);
	}
	redraw_ = true;
}

void Section::setIText(string text)
{
	text_ = text;
	redraw_ = true;
}

void Section::isISection(bool isI)
{
	isISection_ = isI;
	if (isI)
	{
		maxIText_ = 20;
	}
	redraw_ = true;
}

int Section::getVarI(uint16_t varIndex)
{
	if (variables.count(varIndex))
	{
		return variables[varIndex].getInt();
	}
	return 0;
}

double Section::getVarD(uint16_t varIndex)
{
	if (variables.count(varIndex))
	{
		return variables[varIndex].getDou();
	}
	return 0.0;
}

string Section::getVarS(uint16_t varIndex)
{
	if (variables.count(varIndex))
	{
		return variables[varIndex].getStr();
	}
	return "ERROR:VARDOESNOTEXIST";
}

string Section::getIVar()
{
	if (isISection_)
	{
		return iText_;
	}
	else
	{
		return "ERROR:NOTISECTION";
	}
}

string Section::operator()()
{
	stringstream text;
	if (isHidden_ == true)
		return "               ";
	if (isISection_ == false)
	{
		if (isNumberHidden_ == false)
		{
			text << index_ << ".";
		}
		text << text_;
		if (variables.empty() == false)
		{
			for (auto &iter : variables)
			{
				text << " <";
				switch (iter.second.getVarIndex())
				{
				case 1: text << iter.second.getInt();
				case 2: text << iter.second.getDou();
				case 3: text << iter.second.getStr();
				}
				text << ">";
			}
		}
	}
	else
	{
		text << text_ << " " << iText_;
	}
	return text.str();
}

bool Section::isHidden()
{
	return isHidden_;
}

bool Section::isSelectable()
{
	return isSelectable_;
}

bool Section::isISection()
{
	return isISection_;
}

bool Section::redraw()
{
	if (redraw_ == true)
	{
		redraw_ = false;
		return true;
	}
	return false;
}

void Section::log(string text)
{
	fstream file("Logs\\Log.txt", ios::app);

	file << text << endl;
}

bool Section::isNumberHidden()
{
	return isNumberHidden_;
}
/////////////////////////////////////////////////////


/* Variable */
/////////////////////////////////////////////////////
Variable::Variable()
{
	iVar_ = 0;
	dVar_ = 0.0;
	sVar_ = "";
	isValid_ = true;
}

Variable::Variable(int var)
{
	iVar_ = var;
	dVar_ = 0.0;
	sVar_ = "";
	isValid_ = true;
	varIndex_ = 1;
}

Variable::Variable(double var)
{
	iVar_ = 0;
	dVar_ = var;
	sVar_ = "";
	isValid_ = true;
	varIndex_ = 2;
}

Variable::Variable(string var)
{
	iVar_ = 0;
	dVar_ = 0.0;
	sVar_ = var;
	isValid_ = true;
	varIndex_ = 3;
}

void Variable::setVar(int var)
{
	iVar_ = var;
	varIndex_ = 1;
}

void Variable::setVar(double var)
{
	sVar_ = var;
	varIndex_ = 2;
}

void Variable::setVar(string var)
{
	sVar_ = var;
	varIndex_ = 3;
}

int Variable::getVarIndex()
{
	return varIndex_;
}

int Variable::getInt()
{
	return iVar_;
}

double Variable::getDou()
{
	return dVar_;
}

string Variable::getStr()
{
	return sVar_;
}

void Variable::isValid(bool isValid)
{
	isValid_ = isValid;
}

bool Variable::isValid()
{
	return isValid_;
}

void Variable::operator()(int var)
{
	iVar_ = var;
}

void Variable::operator()(double var)
{
	dVar_ = var;
}

void Variable::operator()(string var)
{
	sVar_ = var;
}
/////////////////////////////////////////////////////