#include "task.h"

void ShowRecipe(const Recipe &recipe)
{
  string tab = "  ";
  string space = " ";
  cout << "---" << endl;
  cout << "Recipe Name: " << recipe.name << endl;
  cout << "Servings: " << recipe.servings << endl;
  cout << endl;
  cout << "Ingredients: " << endl;
  for (const Ingredient &i : recipe.ingredient)
  {
    cout << tab << i.name << tab << i.quantity << space << i.unit << endl;
  }
  cout << endl;
  cout << "Procedures to prepare " << recipe.name << endl;
  size_t s = recipe.steps.size();
  for (size_t i = 0; i < s; i++)
  {
    cout << tab << "Step " << i + 1 << ": " << recipe.steps[i] << endl;
  }
  cout << "---" << endl;
}
