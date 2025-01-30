#include <iostream>
#include <list>

using namespace std;

enum MainMenuUserInput
{
  ADD = 1,
  VIEW,
  EDIT,
  DELETE,
  EXIT
};
// Item-name, Item-quantity, Item-Unit
struct Ingredient
{
  string name;
  float quantity;
  string unit;
};

struct RecipeStep
{
  int stepNo;
  string stepTask;
};

struct Recipe
{
  string recipeName;
  float servings;
  list<Ingredient> ingredients;
  list<RecipeStep> recipeStep;
};

list<Recipe> Recipes = {};

MainMenuUserInput
DisplayMainMenu()
{
  while (true)
  {
    int userInput;
    cout << "Welcome" << endl;
    cout << "1. Add Recipe" << endl;
    cout << "2. View Recipe" << endl;
    cout << "3. Edit Recipe" << endl;
    cout << "4. Delete Recipe" << endl;
    cout << "5. Exit Application" << endl;
    cout << "Choice: ";
    cin >> userInput;
    cout << endl;

    if (userInput == ADD)
    {
      return ADD;
    }
    if (userInput == EDIT)
    {
      return EDIT;
    }
    if (userInput == VIEW)
    {
      return EDIT;
    }
    if (userInput == DELETE)
    {
      return DELETE;
    }
    if (userInput == EXIT)
    {
      return EXIT;
    }
    cout << endl
         << "Please input valid choice" << endl
         << endl;
  }
};

void CreateRecipe()
{
  Recipe r;
  cout << "Create new Recipe" << endl;
  cin >> r.recipeName;
}

int main()
{

  while (true)
  {
    MainMenuUserInput u = DisplayMainMenu();
    switch (u)
    {
    case ADD:
    {
      CreateRecipe();
      break;
    };
    default:
      break;
    }
  }

  return 0;
}