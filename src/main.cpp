#include <iostream>
#include <fstream>
#include <list>
#include <limits>
#include <sstream>
#include <vector>

using namespace std;

string filename = "./build/data.txt";
enum MainMenuUserInput
{
  ADD = 1,
  VIEW,
  EDIT,
  DELETE,
  FIND,
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
  vector<Ingredient> ingredients;
  vector<RecipeStep> recipeSteps;
};

vector<Recipe> recipes = {};

float numInputHandler()
{
  float userInput;
  cin >>
      userInput;
  // largest possible number of input to ignore || ignore when \n is found
  if (cin.fail() || userInput < 0)
  {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return -1;
  }
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  return userInput;
}

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
    cout << "5. Find Recipe" << endl;
    cout << "6. Exit Application" << endl;

    cout << "Choice: ";
    userInput = numInputHandler();
    if (userInput == -1)
    {
      continue;
    }

    if (userInput == ADD)
    {
      return ADD;
    }
    if (userInput == VIEW)
    {
      return VIEW;
    }
    if (userInput == EDIT)
    {
      return EDIT;
    }
    if (userInput == FIND)
    {
      return FIND;
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
int deserializer(string s)
{
  int totalRecipe = 0;
  const string delimeter = ",";
  const string NewLine = "\n";
  const string RecipeName = "Recipe: ";
  const string ServingsName = "Servings: ";
  const string IngredientsName = "Ingredients: ";
  const string StepsName = "Steps: ";
  const string RecipeDelimeter = "---";

  istringstream ss(s);
  string line = "";
  bool readingIngredients = false;
  bool readingSteps = false;

  Recipe currentRecipe;
  while (getline(ss, line))
  {

    if (line.substr(0, RecipeName.length()) == RecipeName)
    {
      currentRecipe = Recipe();
      currentRecipe.recipeName = line.substr(RecipeName.length());
    }
    else if (line.substr(0, ServingsName.length()) == ServingsName)
    {
      currentRecipe.servings = stof(line.substr(ServingsName.length()));
    }
    else if (line.substr(0, IngredientsName.length()) == IngredientsName)
    {
      readingIngredients = true;
      readingSteps = false;
    }
    else if (line.substr(0, StepsName.length()) == StepsName)
    {
      readingIngredients = false;
      readingSteps = true;
    }
    else if (readingIngredients == true)
    {
      size_t d1 = line.find(delimeter);
      size_t d2 = line.find(delimeter, d1 + 1);
      Ingredient i;
      i.name = line.substr(0, d1);
      i.quantity = stof(line.substr(d1 + 1, d2 - 1));
      i.unit = line.substr(d2 + 1);

      currentRecipe.ingredients.push_back(i);
    }
    else if (line == RecipeDelimeter)
    {
      recipes.push_back(currentRecipe);
      totalRecipe++;
    }
    else if (readingSteps == true)
    {
      currentRecipe.recipeSteps.push_back(line);
    }
  }
  return totalRecipe;
}

void saveToFile()
{
  ofstream outfile(filename, ios::out);
  if (!outfile)
  {
    cerr << "Error opening file for saving" << endl;
    return;
  }
  string s = serializer();
  outfile << s;
  outfile.close();
}
int loadFromFile()
{
  ifstream infile(filename, ios::in);
  if (!infile)
  {
    std::cerr << "Error loading from file" << endl;
    return -1;
  }
  string line;
  string NewLine = "\n";
  string data = "";
  while (getline(infile, line))
  {
    data += line + NewLine;
  }

  int totalRecipe = 0;
  totalRecipe = deserializer(data);
  return totalRecipe;
}

void DisplayRecipe(const Recipe &recipe)
{
  string tab = "  ";
  string space = " ";
  cout << "---" << endl;
  cout << "Recipe Name: " << recipe.recipeName << endl;
  cout << "Servings: " << recipe.servings << endl;
  cout << endl;
  cout << "Ingredients: " << endl;
  for (const Ingredient &i : recipe.ingredients)
  {
    cout << tab << i.name << tab << i.quantity << space << i.unit << endl;
  }
  cout << endl;
  cout << "Procedures to prepare " << recipe.recipeName << endl;
  size_t s = recipe.recipeSteps.size();
  for (size_t i = 0; i < s; i++)
  {
    cout << tab << "Step " << i + 1 << ": " << recipe.recipeSteps[i] << endl;
  }
  cout << "---" << endl;
}

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

    r.servings = numInputHandler();
    if (r.servings == -1)
    {
      cout << "Invalid serving (serving must be number greater than 0)" << endl;
      continue;
    }
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
      i.quantity = numInputHandler();
      if (i.quantity == -1)
      {
        cout << "Invalid quantity (quantity must be number greater than 0)" << endl;
      }
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
    r.ingredients.push_back(i);
    // r.ingredients.push_front(i);
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
    r.recipeSteps.push_back(recipeStep);
  }
  recipes.push_back(r);
  saveToFile();
};

int deleteRecipe(size_t index)
{
  if (index < recipes.size())
  {
    recipes.erase(recipes.begin() + index);
    return 1;
  }
  return -1;
}

void DeleteRecipeCMD()
{
  cout << endl;
  for (size_t i = 0; i < recipes.size(); i++)
  {
    cout << i + 1 << ": " << recipes[i].recipeName << endl;
  }
  int deleteRecipeNumber = 0;
  while (true)
  {
    cout << "Enter Recipes number to Delete(0 to exit): ";
    deleteRecipeNumber = numInputHandler();
    if (deleteRecipeNumber == -1)
    {
      cout << "Invalid input or negative number" << endl;
      continue;
    }

    if (deleteRecipeNumber == 0)
      return;
    if (deleteRecipe(deleteRecipeNumber - 1) == -1)
    {
      cout << endl
           << "Invalid recipe number" << endl;
      continue;
    }
    saveToFile();
    cout << endl;
    cout << "Recipe Delete successfully " << endl;
    cout << "Press ENTER to back Main." << endl;
    cout << "Enter d to DELETE Again." << endl;
    string c;
    getline(cin, c);
    if (c == "d")
    {
      DeleteRecipeCMD();
    }
    if (c.empty())
    {
      break;
    }
    break;
  }
}

Recipe generateRecipeForServings(const Recipe r, int newServings)
{
  if (newServings == 0)
  {
    return r;
  }

  Recipe newRecipe = Recipe();
  newRecipe.recipeName = r.recipeName;
  newRecipe.servings = newServings;
  Ingredient newIngredient;
  for (const auto &ing : r.ingredients)
  {
    newIngredient = Ingredient();
    newIngredient.name = ing.name;
    newIngredient.quantity = (ing.quantity / r.servings) * newServings;
    newIngredient.unit = ing.unit;
    newRecipe.ingredients.push_back(newIngredient);
  }
  for (const auto &step : r.recipeSteps)
  {
    newRecipe.recipeSteps.push_back(step);
  }
  return newRecipe;
}

void DisplayRecipeCMD()
{
  cout << "Enter Recipes number to view: " << endl;
  for (size_t i = 0; i < recipes.size(); i++)
  {
    cout << i + 1 << ": " << recipes[i].recipeName << endl;
  }

  int recipeNumber;
  while (true)
  {
    cout << "Recipe number: (0 to exit)";
    recipeNumber = numInputHandler();

    if (recipeNumber == -1)
    {
      cout << "Either recipe doesnot exist or invalid input.";
      continue;
    }
    if (recipeNumber == 0)
      break;
  }

  if (recipeNumber == 0)
  {
    return;
  }
  int servingsNumber = 0;
  while (true)
  {
    cout << "No of servings(0 for default): ";
    servingsNumber = numInputHandler();
    if (servingsNumber == -1)
    {
      cout << "Invalid Servings";
      continue;
    }
    break;
  }

  Recipe generateNewRecipe = generateRecipeForServings(recipes[recipeNumber - 1], servingsNumber);
  DisplayRecipe(generateNewRecipe);
}
void EditRecipeCMD()
{
  cout << "Editing..." << endl;
  return;
}
void FindRecipeCMD()
{
  cout << "Finding..." << endl;
  return;
}

int main()
{

  loadFromFile();
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
    case VIEW:
    {
      DisplayRecipeCMD();
      break;
    }
    case EDIT:
    {
      EditRecipeCMD();
      break;
    }
    case FIND:
    {
      FindRecipeCMD();
      break;
    }
    case DELETE:
    {
      DeleteRecipeCMD();
    }
    default:
      break;
    }
  }
  return 0;
}