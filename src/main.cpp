#include "main.h"

vector<Recipe> recipes;
string filename;

MainMenuUserInput
DisplayMainMenu()
{
  while (true)
  {
    int userInput = 0;
    cout << "Welcome" << endl;
    cout << "1. Add Recipe" << endl;
    cout << "2. View Recipe" << endl;
    cout << "3. Edit Recipe" << endl;
    cout << "4. Delete Recipe" << endl;
    cout << "5. Find Recipe" << endl;
    cout << "6. Exit Application" << endl;

    cout << "Choice: ";
    int status = GetInput(userInput);

    if (status == -1)
    {
      cout << "Invalid Choice" << endl;
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
    if (userInput == SEARCH)
    {
      return SEARCH;
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

void AddCMD()
{
  while (true)
  {
    cout << "Adding..." << endl;
    Recipe r = Recipe();
    if (AskData(r) == 0)
    {
      return;
    }
    recipes.push_back(r);
    saveToFile(filename, recipes);
    cout << "Recipe added" << endl;
    cout << "Enter 0 to go back: ";
    string status = "";
    GetInput(status);
    if (status == "0")
    {
      return;
    }
  }
}
void ViewCMD()
{
  cout << "Viewing..." << endl;
  while (true)
  {
    int size = AskRecipeNoToShow(recipes);
    if (size <= 0)
    {
      return;
    }
    cout << endl;
    int servings = AskServingsNumber(recipes[size - 1]);
    if (servings == 0)
    {
      servings = recipes[size - 1].servings;
    }
    Recipe r = prepareRecipe(recipes[size - 1], servings);
    ShowRecipe(r);

    cout << endl;
    cout << "Enter 0 to go back: ";
    string status = "";
    GetInput(status);
    if (status == "0")
    {
      return;
    }
  }
}
void EditCMD()
{
  cout << "Editing..." << endl;
}
void SearchCMD()
{
  cout << "Searching..." << endl;
}
void DeleteCMD()
{
  while (true)
  {
    cout << "Deleting..." << endl;
    int recipeNumber = DeleteRecipe(recipes);
    if (recipeNumber == 0)
      return;
    if (recipeNumber >= 0)
    {
      saveToFile(filename, recipes);
      cout << "Enter 0 to go back: ";
      string status = "";
      GetInput(status);
      if (status == "0")
      {
        return;
      }
    }
  }
}
void ExitCMD()
{
  cout << "Exiting..." << endl;
}

int main()
{
  filename = "./build/data.txt";
  loadFromFile(filename, recipes);
  while (true)
  {
    MainMenuUserInput u = DisplayMainMenu();
    switch (u)
    {
    case ADD:
    {
      AddCMD();
      break;
    };
    case VIEW:
    {
      ViewCMD();
      break;
    }
    case EDIT:
    {
      EditCMD();
      break;
    }
    case SEARCH:
    {
      SearchCMD();
      break;
    }
    case DELETE:
    {
      DeleteCMD();
      break;
    }
    default:
      break;
    }
  }
  return 0;
}
