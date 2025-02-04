#ifndef MAINH
#define MAINH

#include <iostream>
#include <vector>

#include "./recipe.h"
#include "./input/input.h"
#include "./tasks/task.h"

using namespace std;

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