#ifndef TASKH
#define TASKH

#include <vector>
#include <iostream>
#include "../recipe.h"
#include "../input/input.h"
using namespace std;

int AskData(Recipe &r);
int AskRecipeNoToShow(const vector<Recipe> &recipes);
int AskServingsNumber(const Recipe &r);
Recipe prepareRecipe(const Recipe &recipe, int servings);
void ShowRecipe(const Recipe &r);
int DeleteRecipe(vector<Recipe> &recipes);
void saveToFile(const string filename, const vector<Recipe> &recipes);
int loadFromFile(const string filename, vector<Recipe> &recipes);
int AskEdit(Recipe &oldRecipe);

#endif