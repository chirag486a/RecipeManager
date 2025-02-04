#include "task.h"

void AskRecipeName(string &str)
{
  cout << "Enter Recipe name(leave blank to exit): ";
  GetInput(str);
};

void AskServings(int &num)
{
  while (true)
  {
    cout << "Enter number of servings: ";

    int status = GetInput(num);

    if (status == -1 || status == 0)
    {
      cout << "Invalid serving (serving must be number greater than 0)" << endl;
      continue;
    }
    break;
  }
}

void AskIngredients(vector<Ingredient> &ingredients)
{

  while (true)
  {
    Ingredient i = Ingredient();
    cout << "Enter Ingredients(Leave blank if finished)" << endl;
    cout << "Ingredient Name: ";
    int status = GetInput(i.name);
    if (status == 0)
    {
      if (ingredients.empty())
      {
        cout << endl
             << "A recipe must have atleast one ingredient" << endl
             << endl;
        continue;
      }
      break;
    }
    while (true)
    {
      cout << "Ingredient Quantity: ";
      int status = GetInput(i.quantity);
      if (status == -1)
      {
        cout << "Invalid quantity (quantity must be number greater than 0)" << endl;
        continue;
      }
      break;
    }
    while (true)
    {
      cout << "Unit: ";
      int status = GetInput(i.unit);
      if (status == 0)
      {
        cout << "Unit cannot be empty";
        continue;
      }
      break;
    };
    ingredients.push_back(i);
  };
}

void AskSteps(vector<string> &steps, const string recipeName)
{

  int stepCount = 0;
  cout
      << "Enter steps to prepare(Leaave blank if finished)" << recipeName << endl;
  while (true)
  {
    string step = "";
    cout << "Step " << ++stepCount << ": ";

    int status = GetInput(step);

    if (status == 0 && steps.empty())
    {
      cout << "A Recipe must have atleast one step.";
      continue;
    }
    if (status == 0)
    {
      break;
    }
    steps.push_back(step);
  }
}

int AskData(Recipe &r)
{
  cout << "Create new Recipe" << endl;

  AskRecipeName(r.name);
  if (r.name.empty())
  {
    return 0;
  }
  AskServings(r.servings);
  AskIngredients(r.ingredient);
  AskSteps(r.steps, r.name);
  return 1;
}

int AskRecipeNoToShow(const vector<Recipe> &recipes)
{
  int recipeNumber = 0;
  while (true)
  {
    int i = 0;
    if (recipes.size() == 0)
    {
      cout << endl;
      cout << "No recipe found" << endl;
      cout << endl;
      return 0;
    }
    cout << "Recipe Names" << endl;

    for (const Recipe &recipe : recipes)
    {
      cout << ++i << ". " << recipe.name << endl;
    }
    cout << "Recipe number(0 to exit): ";
    int status = GetInput(recipeNumber);
    if (recipeNumber == 0)
      return 0;
    if (status == -1)
    {
      cout << "Invalid input" << endl;
      continue;
    }
    if (recipeNumber < 0 || recipeNumber > recipes.size())
    {
      cout << "Choice must be positive number from given list" << endl;
      continue;
    }
    break;
  }
  return recipeNumber;
}
