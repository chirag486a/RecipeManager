#include "input.h"

int GetInput(string &str)
{
  getline(cin, str);
  if (str.empty())
  {
    return 0;
  }
  return 1;
}

int GetInput(float &num)
{
  cin >> num;
  if (cin.fail())
  {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return -1;
  }
  return 1;
}

int GetInput(int &num)
{
  cin >> num;
  if (cin.fail())
  {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return -1;
  }
  return 1;
}