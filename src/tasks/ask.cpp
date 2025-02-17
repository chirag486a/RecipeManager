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

    if (status == -1)
    {
      cout << "Invalid serving." << endl;
      continue;
    }
    break;
  }
}

int AskIngredientName(string &str)
{
  cout << "Ingredient Name: ";
  GetInput(str);
  if (str.empty())
  {
    return 0;
  }
  return 1;
}
int AskIngredientQuantity(float &num)
{
  cout << "Ingredient Quantity: ";
  int status = GetInput(num);
  if (status == -1 || num < 0)
    return 0;
  return 1;
};
int AskIngredientUnit(string &str)
{
  cout << "Unit: ";
  GetInput(str);
  if (str.empty())
  {
    return 0;
  }
  return 1;
}

void AskIngredients(vector<Ingredient> &ingredients)
{

  while (true)
  {
    Ingredient i = Ingredient();
    cout << "Enter Ingredients(Leave blank if finished)" << endl;
    int status = AskIngredientName(i.name);
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
      int status = AskIngredientQuantity(i.quantity);
      if (status == 0 || i.quantity == 0)
      {
        cout << "Invalid quantity" << endl;
        continue;
      }
      break;
    }
    while (true)
    {
      int status = AskIngredientUnit(i.unit);
      if (status == 0)
      {
        cout << "Invalid unit" << endl;
        continue;
      }
      break;
    };
    ingredients.push_back(i);
  };
}

void AskSteps(vector<string> &steps, const string recipeName)
{

  cout
      << "Enter steps to prepare(Leaave blank if finished)" << recipeName << endl;
  while (true)
  {
    string step = "";
    cout << "Step " << steps.size() + 1 << ": ";

    int status = GetInput(step);

    if (status == 0 && steps.empty())
    {
      cout << "A Recipe must have atleast one step." << endl;
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
  while (true)
  {
    AskServings(r.servings);
    if (r.servings == 0)
    {
      cout << "Invalid servings" << endl;
      continue;
    }
    break;
  }

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

int AskServingsNumber(const Recipe &r)
{
  int servings = 0;
  cout << "Enter number of servings(" << r.servings << " is default): ";
  int status = GetInput(servings);
  if (status == -1)
  {
    cout << "Invalid input" << endl;
    return -1;
  }
  return servings;
}

int AskEditCMD()
{
  while (true)
  {

    int cmd = 0;
    cout << "1. Add" << endl;
    cout << "2. Edit" << endl;
    cout << "3. Delete" << endl;

    cout << "Enter command(0 to exit): ";
    int status = GetInput(cmd);
    if (status == -1 || cmd < 0 || cmd > 3)
    {
      cout << "Invalid input" << endl;
      continue;
    }
    return cmd;
  }
}
int AskIngredientNumber(const vector<Ingredient> &ingredients)
{
  while (true)
  {

    int i = 0;
    cout << "Ingredients" << endl;
    for (const Ingredient &ingredient : ingredients)
    {
      cout << ++i << ". " << ingredient.name << endl;
    }
    cout << "Enter ingredient number(0 to exit): ";
    int num = 0;
    int status = GetInput(num);
    if (status == -1)
    {
      cout << "Invalid input" << endl;
      continue;
    }
    if (num == 0)
    {
      return 0;
    }
    if (num < 0 || i > ingredients.size())
    {
      cout << "Choice must be positive number from given list" << endl;
      continue;
    }
    return num;
  }
}
void AskDeleteIngredient(vector<Ingredient> &ingredients)
{
  while (true)
  {
    int i = AskIngredientNumber(ingredients);
    if (i == 0)
    {
      break;
    }
    ingredients.erase(ingredients.begin() + i - 1);
  }
}

int AskEdit(Recipe &oldRecipe)
{
  cout << "Leave Empty if no change(Recipe name: " << oldRecipe.name << ")" << endl;
  string tempIngredientName = "";
  AskRecipeName(tempIngredientName);
  if (!tempIngredientName.empty())
  {
    oldRecipe.name = tempIngredientName;
  }
  cout << "Leave 0 if no change(Servings: " << oldRecipe.servings << ")" << endl;

  int tempServings = 0;
  AskServings(tempServings);

  if (!(tempServings == 0))
  {
    oldRecipe.servings = tempServings;
  }

  while (true)
  {

    cout << "Editing Ingredient" << endl;
    int cmd = AskEditCMD();

    if (cmd == 0)
    {
      break;
    }

    if (cmd == 1)
    {
      AskIngredients(oldRecipe.ingredient);
      cout << "Ingredient added" << endl;
      cout << "Enter 0 to exit adding ingerdient: ";
      string redo = "";
      GetInput(redo);
      if (redo == "0")
      {
        return 1;
      }
    }

    if (cmd == 2)
    {
      while (true)
      {
        int i = AskIngredientNumber(oldRecipe.ingredient);
        if (i == 0)
        {
          break;
        }
        Ingredient &ingredient = oldRecipe.ingredient[i - 1];
        cout << "Leave Empty if no change(Ingredient Name: " << oldRecipe.ingredient[i - 1].name << ")" << endl;
        ingredient.name = "";
        ingredient.quantity = 0;
        ingredient.unit = "";
        AskIngredientName(ingredient.name);
        if (!(ingredient.name.empty()))
        {
          oldRecipe.ingredient[i - 1].name = ingredient.name;
        }
        cout << "Leave 0 if no change(Ingredient Quantity: " << oldRecipe.ingredient[i - 1].quantity << ")" << endl;
        AskIngredientQuantity(ingredient.quantity);
        if (!(ingredient.quantity == 0))
        {
          oldRecipe.ingredient[i - 1].quantity = ingredient.quantity;
        }
        cout << "Leave Empty if no change(Unit: " << oldRecipe.ingredient[i - 1].unit << ")" << endl;
        AskIngredientUnit(ingredient.unit);
        if (!(ingredient.unit.empty()))
        {
          oldRecipe.ingredient[i - 1].unit = ingredient.unit;
        }
        cout << "Ingredient updated" << endl;
        cout << "Enter 0 to exit editing ingredient: ";
        string redo = "";
        GetInput(redo);
        if (redo == "0")
        {
          break;
        }
      }
    }
    if (cmd == 3)
    {
      while (true)
      {
        AskDeleteIngredient(oldRecipe.ingredient);
        cout << "Ingredient deleted" << endl;
        string redo = "";
        cout << "Enter 0 to exit deleting ingredient: ";
        GetInput(redo);
        if (redo == "0")
        {
          break;
        }
      }
    }
  }
  while (true)
  {
    int cmd = 0;

    cout << "Editing Steps" << endl;
    cmd = AskEditCMD();
    if (cmd == 0)
    {
      break;
    }
    if (cmd == 1)
    {
      AskSteps(oldRecipe.steps, oldRecipe.name);
      cout << "Step added" << endl;
      cout << "Enter 0 to exit adding step: ";
      string redo = "";
      GetInput(redo);
      if (redo == "0")
      {
        return 1;
      }
    }
    if (cmd == 2)
    {
      while (true)
      {
        cout << "Editing " << oldRecipe.name << " recipe steps.";
        int i = 0;
        for (const string &step : oldRecipe.steps)
        {
          cout << "Step " << ++i << "." << step << endl;
        }
        cout << "Enter step number to edit(0 to exit): ";
        int num = 0;
        int status = GetInput(num);
        if (status == -1)
        {
          cout << "Invalid input" << endl;
          continue;
        }
        if (num == 0)
        {
          break;
        }
        cout << "Step " << num << ".";
        string tempStep = "";
        status = 0;
        status = GetInput(tempStep);
        if (status == 0)
        {
          continue;
        }
        oldRecipe.steps[num - 1] = tempStep;
      }
    }
    if (cmd == 3)
    {
      cout << "Deleting " << oldRecipe.name << " recipe steps." << endl;
      int i = 0;
      for (const string &step : oldRecipe.steps)
      {
        cout << "Step " << ++i << "." << step << endl;
      }
      cout << "Enter step number to delete(0 to exit): ";
      int num = 0;
      int status = GetInput(num);
      if (status == -1)
      {
        cout << "Invalid input" << endl;
        continue;
      }
      if (num == 0)
      {
        break;
      }
      if (oldRecipe.steps.size() <= 1)
      {
        cout << "Recipe must have at atleast one steps" << endl;
        continue;
      }
      oldRecipe.steps.erase(oldRecipe.steps.begin() + (num - 1));
    }
  }

  return 1;
}

string toLowercase(const std::string &str)
{
  string lowerStr = str;
  transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
  return lowerStr;
}

bool caseInsensitiveContains(const std::string &mainStr, const std::string &queryStr)
{
  std::string lowerMainStr = toLowercase(mainStr);
  std::string lowerQueryStr = toLowercase(queryStr);

  return lowerMainStr.find(lowerQueryStr) != std::string::npos;
}

void AskSearch(vector<Recipe> &recipes, vector<size_t> &indexes)
{
  while (true)
  {
    cout << "Search Recipe by" << endl;
    cout << "1. Recipe name" << endl;
    cout << "2. Ingredient Name" << endl;

    int cmd = 0;
    cout << "How would you like to search recipe?(0 to exit) : ";
    int status = GetInput(cmd);
    if (status < 0)
    {
      cout << "Invalid Input" << endl;
      continue;
    }
    if (cmd == 0)
    {
      break;
    }
    // Search By name
    if (cmd == 1)
    {
      cout << "Enter Recipe name to search (empty to exit): ";
      string queryName = "";
      GetInput(queryName);
      if (queryName.empty())
      {
        break;
      }
      indexes.clear();
      for (size_t i = 0; i < recipes.size(); i++)
      {
        if (caseInsensitiveContains(recipes[i].name, queryName))
        {
          indexes.push_back(i);
        };
      }
      break;
    }
    // Search by ingredient
    if (cmd == 2)
    {
      cout << "Enter Ingredient name to search (empty to exit): ";
      string queryName = "";
      GetInput(queryName);
      if (queryName.empty())
      {
        break;
      }
      indexes.clear();
      for (size_t j = 0; j < recipes.size(); j++)
      {
        for (const Ingredient &i : recipes[j].ingredient)
        {
          if (caseInsensitiveContains(i.name, queryName))
          {
            indexes.push_back(j);
            break;
          };
        }
      }
      break;
    }
  }

  return;
}