#include "task.h"

#include <fstream>
#include <sstream>

int deserializer(const string s, vector<Recipe> &recipes)
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
      currentRecipe.name = line.substr(RecipeName.length());
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

      currentRecipe.ingredient.push_back(i);
    }
    else if (line == RecipeDelimeter)
    {
      recipes.push_back(currentRecipe);
      totalRecipe++;
    }
    else if (readingSteps == true)
    {
      currentRecipe.steps.push_back(line);
    }
  }
  return totalRecipe;
}
string serializer(const vector<Recipe> recipes)
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
    d += RecipeName + recipe.name + NewLine;
    d += ServingsName + to_string(recipe.servings) + NewLine;

    d += IngredientsName + NewLine;
    for (const auto &ingredient : recipe.ingredient)
    {
      d += ingredient.name + delimeter + to_string(ingredient.quantity) + delimeter + ingredient.unit + NewLine;
    };
    d += StepsName + NewLine;
    for (const auto &recipeStep : recipe.steps)
    {
      d += recipeStep + NewLine;
    }
    d += RecipeDelimeter + NewLine;
  }

  return d;
}

void saveToFile(const string filename, const vector<Recipe> &recipes)
{
  ofstream outfile(filename, ios::out);
  if (!outfile)
  {
    cerr << "Error opening file for saving" << endl;
    return;
  }
  string s = serializer(recipes);
  outfile << s;
  outfile.close();
}
int loadFromFile(const string filename, vector<Recipe> &recipes)
{
  ofstream outfile(filename);
  if (!outfile.is_open())
  {
    cerr << "Error: could not find file" << endl;
    return -1;
  }
  outfile.close();
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
  totalRecipe = deserializer(data, recipes);
  return totalRecipe;
}
