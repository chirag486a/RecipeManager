#ifndef MAINH
#define MAINH

#include <iostream>

#include "Recipe.h"
#include "input/input.h"

using namespace std;

string filename = "data.txt";

enum MainMenuUserInput
{
  ADD = 1,
  VIEW,
  EDIT,
  DELETE,
  SEARCH,
  EXIT
};

void AddCMD();
void ViewCMD();
void EditCMD();
void SearchCMD();
void DeleteCMD();
void ExitCMD();

#endif