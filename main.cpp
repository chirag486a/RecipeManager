#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <cctype>

using namespace std;

struct Ingredient
{
  string name;
  double quantity;
  string unit;
};

struct Recipe
{
  string name;
  int servings;
  vector<Ingredient> ingredients;
  vector<string> steps;
};

vector<Recipe> recipes;

// ... [loadRecipes() and saveRecipes() functions remain the same] ...

void saveRecipes()
{
  ofstream file("recipes.txt");
  for (auto &r : recipes)
  {
    file << r.name << "\n";
    file << r.servings << "\n";
    for (auto &ing : r.ingredients)
    {
      file << ing.name << "|" << ing.quantity << "|" << ing.unit << "\n";
    }
    file << "STEPS:\n";
    for (auto &step : r.steps)
    {
      file << step << "\n";
    }
    file << "====\n";
  }
  file.close();
}
void listRecipes()
{
  if (recipes.empty())
  {
    cout << "No recipes found.\n";
    return;
  }

  cout << "\nRecipes:\n";
  for (size_t i = 0; i < recipes.size(); i++)
  {
    cout << i + 1 << ". " << recipes[i].name << "\n";
  }
}

void displayRecipe(const Recipe &r, int servings = 0)
{
  if (servings == 0)
    servings = r.servings;
  double ratio = static_cast<double>(servings) / r.servings;

  cout << "\n--- " << r.name << " ---\n";
  cout << "Servings: " << servings << "\n\nIngredients:\n";
  for (auto &ing : r.ingredients)
  {
    cout << "- " << ing.name << ": " << ing.quantity * ratio << " " << ing.unit << "\n";
  }
  cout << "\nSteps:\n";
  for (size_t i = 0; i < r.steps.size(); i++)
  {
    cout << i + 1 << ". " << r.steps[i] << "\n";
  }
  cout << endl;
}
void loadRecipes()
{
  ifstream file("recipes.txt");
  if (!file.is_open())
    return;

  Recipe current;
  string line;
  while (getline(file, line))
  {
    if (line == "====")
    {
      recipes.push_back(current);
      current = Recipe{};
      continue;
    }

    if (current.name.empty())
    {
      current.name = line;
    }
    else if (current.servings == 0)
    {
      current.servings = stoi(line);
    }
    else if (line == "STEPS:")
    {
      while (getline(file, line) && line != "====")
      {
        if (!line.empty())
          current.steps.push_back(line);
      }
    }
    else
    {
      size_t pos1 = line.find('|');
      size_t pos2 = line.rfind('|');
      if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2)
      {
        Ingredient ing;
        ing.name = line.substr(0, pos1);
        ing.quantity = stod(line.substr(pos1 + 1, pos2 - pos1 - 1));
        ing.unit = line.substr(pos2 + 1);
        current.ingredients.push_back(ing);
      }
    }
  }
  file.close();
}
void addRecipe()
{
  Recipe r;
  cout << "Recipe name: ";
  getline(cin, r.name);

  cout << "Number of servings: ";
  while (!(cin >> r.servings) || r.servings < 1)
  {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input. Enter a positive number: ";
  }
  cin.ignore();

  cout << "Add ingredients (leave name empty to finish):\n";
  while (true)
  {
    Ingredient ing;
    cout << "Ingredient name: ";
    getline(cin, ing.name);
    if (ing.name.empty())
      break;

    cout << "Quantity: ";
    while (!(cin >> ing.quantity))
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input. Enter a number: ";
    }
    cin.ignore();

    cout << "Unit: ";
    getline(cin, ing.unit);

    r.ingredients.push_back(ing);
  }

  cout << "Add steps (leave empty to finish):\n";
  string step;
  int i = 1;
  while (true)
  {
    cout << "Step " << i++ << ": ";
    getline(cin, step);
    if (step.empty())
      break;
    r.steps.push_back(step);
  }

  recipes.push_back(r);
  cout << "Recipe added!\n";
}
void viewRecipe()
{
  listRecipes();
  if (recipes.empty())
    return;

  cout << "\nEnter recipe number: ";
  size_t choice;
  cin >> choice;
  cin.ignore();

  if (choice < 1 || choice > recipes.size())
  {
    cout << "Invalid selection.\n";
    return;
  }

  int servings = 0;
  cout << "Enter desired servings (0 to keep original): ";
  cin >> servings;
  cin.ignore();

  displayRecipe(recipes[choice - 1], (servings > 0) ? servings : recipes[choice - 1].servings);
}

// ... [listRecipes(), viewRecipe(), deleteRecipe() functions remain similar] ...

bool getYesNo(const string &prompt)
{
  while (true)
  {
    cout << prompt << " (y/n): ";
    char response;
    cin >> response;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    response = tolower(response);

    if (response == 'y')
      return true;
    if (response == 'n')
      return false;
    cout << "Invalid input. Please enter y or n.\n";
  }
}
void deleteRecipe()
{
  listRecipes();
  if (recipes.empty())
    return;

  cout << "Enter recipe number to delete: ";
  size_t choice;
  cin >> choice;
  cin.ignore();

  if (choice < 1 || choice > recipes.size())
  {
    cout << "Invalid selection.\n";
    return;
  }

  recipes.erase(recipes.begin() + (choice - 1));
  cout << "Recipe deleted.\n";
}

void editIngredients(Recipe &r)
{
  while (true)
  {
    cout << "\nCurrent ingredients:\n";
    for (size_t i = 0; i < r.ingredients.size(); i++)
    {
      cout << i + 1 << ". " << r.ingredients[i].name << " - "
           << r.ingredients[i].quantity << " " << r.ingredients[i].unit << "\n";
    }

    cout << "\nIngredient Options:\n"
         << "1. Add ingredient\n"
         << "2. Edit ingredient\n"
         << "3. Remove ingredient\n"
         << "4. Back to edit menu\n"
         << "Choice: ";

    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 4)
      return;

    switch (choice)
    {
    case 1:
    {
      Ingredient ing;
      cout << "Ingredient name: ";
      getline(cin, ing.name);
      cout << "Quantity: ";
      cin >> ing.quantity;
      cin.ignore();
      cout << "Unit: ";
      getline(cin, ing.unit);
      r.ingredients.push_back(ing);
      cout << "Ingredient added!\n";
      break;
    }
    case 2:
    {
      cout << "Enter ingredient number to edit: ";
      size_t num;
      cin >> num;
      cin.ignore();

      if (num < 1 || num > r.ingredients.size())
      {
        cout << "Invalid number!\n";
        break;
      }

      Ingredient &ing = r.ingredients[num - 1];
      cout << "Editing ingredient " << num << ":\n";
      cout << "New name [" << ing.name << "]: ";
      string name;
      getline(cin, name);
      if (!name.empty())
        ing.name = name;

      cout << "New quantity [" << ing.quantity << "]: ";
      string qty;
      getline(cin, qty);
      if (!qty.empty())
        ing.quantity = stod(qty);

      cout << "New unit [" << ing.unit << "]: ";
      string unit;
      getline(cin, unit);
      if (!unit.empty())
        ing.unit = unit;

      cout << "Ingredient updated!\n";
      break;
    }
    case 3:
    {
      cout << "Enter ingredient number to remove: ";
      size_t num;
      cin >> num;
      cin.ignore();

      if (num < 1 || num > r.ingredients.size())
      {
        cout << "Invalid number!\n";
        break;
      }

      r.ingredients.erase(r.ingredients.begin() + (num - 1));
      cout << "Ingredient removed!\n";
      break;
    }
    default:
      cout << "Invalid choice!\n";
    }

    if (choice >= 1 && choice <= 3)
    {
      if (!getYesNo("Modify another ingredient in this recipe?"))
        break;
    }
  }
}

void editSteps(Recipe &r)
{
  while (true)
  {
    cout << "\nCurrent steps:\n";
    for (size_t i = 0; i < r.steps.size(); i++)
    {
      cout << i + 1 << ". " << r.steps[i] << "\n";
    }

    cout << "\nStep Options:\n"
         << "1. Add step\n"
         << "2. Edit step\n"
         << "3. Remove step\n"
         << "4. Back to edit menu\n"
         << "Choice: ";

    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 4)
      return;

    switch (choice)
    {
    case 1:
    {
      cout << "Enter new step: ";
      string step;
      getline(cin, step);
      r.steps.push_back(step);
      cout << "Step added!\n";
      break;
    }
    case 2:
    {
      cout << "Enter step number to edit: ";
      size_t num;
      cin >> num;
      cin.ignore();

      if (num < 1 || num > r.steps.size())
      {
        cout << "Invalid number!\n";
        break;
      }

      cout << "Current step: " << r.steps[num - 1] << "\n";
      cout << "New step text: ";
      string step;
      getline(cin, step);
      r.steps[num - 1] = step;
      cout << "Step updated!\n";
      break;
    }
    case 3:
    {
      cout << "Enter step number to remove: ";
      size_t num;
      cin >> num;
      cin.ignore();

      if (num < 1 || num > r.steps.size())
      {
        cout << "Invalid number!\n";
        break;
      }

      r.steps.erase(r.steps.begin() + (num - 1));
      cout << "Step removed!\n";
      break;
    }
    default:
      cout << "Invalid choice!\n";
    }

    if (choice >= 1 && choice <= 3)
    {
      if (!getYesNo("Modify another step in this recipe?"))
        break;
    }
  }
}

void editRecipe()
{
  listRecipes();
  if (recipes.empty())
    return;

  cout << "Enter recipe number to edit (0 to cancel): ";
  size_t choice;
  cin >> choice;
  cin.ignore();

  if (choice == 0)
    return;
  if (choice < 1 || choice > recipes.size())
  {
    cout << "Invalid selection.\n";
    return;
  }

  Recipe &r = recipes[choice - 1];

  while (true)
  {
    displayRecipe(r);
    cout << "\nEdit Options:\n"
         << "1. Edit name\n"
         << "2. Edit servings\n"
         << "3. Edit ingredients\n"
         << "4. Edit steps\n"
         << "5. Done editing\n"
         << "Choice: ";

    int option;
    cin >> option;
    cin.ignore();

    switch (option)
    {
    case 1:
    {
      cout << "Current name: " << r.name << "\n";
      cout << "New name: ";
      getline(cin, r.name);
      cout << "Name updated!\n";
      break;
    }
    case 2:
    {
      cout << "Current servings: " << r.servings << "\n";
      cout << "New servings: ";
      cin >> r.servings;
      cin.ignore();
      cout << "Servings updated!\n";
      break;
    }
    case 3:
      editIngredients(r);
      break;
    case 4:
      editSteps(r);
      break;
    case 5:
      cout << "Finished editing recipe.\n";
      return;
    default:
      cout << "Invalid option.\n";
    }

    if (option != 5 && !getYesNo("Make another edit to this recipe?"))
    {
      cout << "Finished editing recipe.\n";
      return;
    }
  }
}

// ... [rest of the functions (addRecipe, main menu, etc) remain similar] ...

int main()
{
  loadRecipes();

  while (true)
  {
    cout << "\nRecipe Manager\n"
         << "1. Add Recipe\n"
         << "2. View Recipes\n"
         << "3. Edit Recipe\n"
         << "4. Delete Recipe\n"
         << "5. Exit\n"
         << "Choice: ";

    int choice;
    cin >> choice;
    cin.ignore();

    switch (choice)
    {
    case 1:
      addRecipe();
      break;
    case 2:
      viewRecipe();
      break;
    case 3:
      editRecipe();
      break;
    case 4:
      deleteRecipe();
      break;
    case 5:
      saveRecipes();
      return 0;
    default:
      cout << "Invalid choice.\n";
    }
  }
}