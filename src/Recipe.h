#ifndef RECIPEH
#define RECIPEH

#include <vector>
#include <iostream>

using namespace std;

struct Ingredient
{
  string name;
  float quantity;
  string unit;
};

struct Recipe
{
  string name;
  int servings;
  vector<Ingredient> ingredient;
  vector<string> steps;
};

#endif
