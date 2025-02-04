#include "task.h"

int DeleteRecipe(vector<Recipe> &recipes)
{
  int size = AskRecipeNoToShow(recipes);
  if (size <= 0)
  {
    return 0;
  }
  recipes.erase(recipes.begin() + size - 1);
  cout << "Recipe deleted" << endl;
  return size;
}