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
  cout << "Adding..." << endl;
  Recipe r = Recipe();
  AskData(r);
  recipes.push_back(r);
  saveToFile(filename, recipes);
}
void ViewCMD()
{
  cout << "Viewing..." << endl;
  int size = AskRecipeNoToShow(recipes);
  if (size <= 0)
  {
    return;
  }
  ShowRecipe(recipes[size - 1]);
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
  cout << "Deleting..." << endl;
}
void ExitCMD()
{
  cout << "Exiting..." << endl;
}

int main()
{
  filename = "./build/data.txt";
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
