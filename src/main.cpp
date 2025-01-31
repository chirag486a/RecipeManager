#include <iostream>
#include <fstream>
#include <list>
#include <limits>

using namespace std;

string filename = "data";
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
typedef string RecipeStep;

struct Recipe
{
  string recipeName;
  float servings;
  list<Ingredient> ingredients;
  list<RecipeStep> recipeSteps;
};

list<Recipe> recipes = {};

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
    // largest possible number of input to ignore || ignore when n is found
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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

string serializer()
{
  string delimeter = ",";
  string d = "";
  string RecipeName = "Recipe: ";
  string ServingsName = "Servings: ";
  string NewLine = "\n";
  string IngredientsName = "Ingredients: ";
  string StepsName = "Steps: ";
  string RecipeDelimeter = "---";
  for (const auto &recipe : recipes)
  {
    d += RecipeName + recipe.recipeName + NewLine;
    d += ServingsName + to_string(recipe.servings) + NewLine;

    d += IngredientsName + NewLine;
    for (const auto &ingredient : recipe.ingredients)
    {
      d += ingredient.name + delimeter + to_string(ingredient.quantity) + delimeter + ingredient.unit + NewLine;
    };
    d += StepsName + NewLine;
    for (const auto &recipeStep : recipe.recipeSteps)
    {
      d += recipeStep + NewLine;
    }
    d += RecipeDelimeter + NewLine;
  }

  return d;
}
void deserializer(string data)
{
  string delimeter = ",";
  string RecipeName = "Recipe: ";
  string ServingsName = "Servings: ";
  string NewLine = "\n";
  string IngredientsName = "Ingredients: ";
  string StepsName = "Steps: ";
  string RecipeDelimeter = "---";

  string line = "";

  istringstream ss(data);
  
}

void saveToFile()
{
  ofstream outfile(filename, ios::binary);
  if (outfile)
  {
  std:
    cerr << "Error opening file for saving" << endl;
    return;
  }
  outfile << serializer();
  outfile.close();
}
// void loadFromFile()
// {
//   ifstream infile(filename, ios::binary);
//   if (!infile)
//   {
//     std::cerr << "Error loading from file" << endl;
//     return;
//   }
//   infile.read(reinterpret_cast<char *> recipes, )
// }

void CreateRecipe()
{
  Recipe r;
  int ExitRecipeCreate = 0;
  cout << "Create new Recipe" << endl;

  while (true)
  {
    cout << "Enter Recipe name: ";
    getline(cin, r.recipeName);
    if (r.recipeName.empty())
    {
      cout << "Recipe must not be empty" << endl;
      continue;
    }
    break;
  }
  while (true)
  {
    cout << "Enter number of servings: ";
    cin >> r.servings;

    if (cin.fail() || r.servings <= 0)
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid serving (serving must be number greater than 0)" << endl;
      continue;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    break;
  }
  while (true)
  {
    cout << "Enter Ingredients(Leave blank if finished)" << endl;
    // Item-name, Item-quantity, Item-Unit
    Ingredient i;
    cout << "Ingredient Name: ";
    getline(cin, i.name);
    if (i.name.empty())
    {
      if (r.ingredients.empty())
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
      cin >> i.quantity;
      if (cin.fail() || i.quantity <= 0)
      {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid quantity (quantity must be number greater than 0)" << endl;
        continue;
      }
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      break;
    }
    while (true)
    {
      cout << "Unit: ";
      getline(cin, i.unit);
      if (i.unit.empty())
      {
        cout << "Unit cannot be empty";
        continue;
      }
      break;
    };
    r.ingredients.push_front(i);
  };
  int stepCount = 0;
  cout
      << "Enter steps to prepare(Leaave blank if finished)" << r.recipeName << endl;
  while (true)
  {
    RecipeStep recipeStep;
    cout << "Step " << ++stepCount << ": ";
    getline(cin, recipeStep);
    if (recipeStep.empty() && r.recipeSteps.empty())
    {
      cout << "A Recipe must have atleast one step.";
      continue;
    }
    if (recipeStep.empty())
    {
      break;
    }
    r.recipeSteps.push_front(recipeStep);
  }
  recipes.push_front(r);
  string s = serializer();
  cout << s << endl;
};

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