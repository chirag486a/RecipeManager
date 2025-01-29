#include <iostream>

using namespace std;

enum UserInput
{
  ADD,
  VIEW,
  EDIT,
  DELETE,
  EXIT
};

UserInput DisplayMainMenu()
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

int main()
{

  while (true)
  {
    UserInput u = DisplayMainMenu();
  }

  return 0;
}