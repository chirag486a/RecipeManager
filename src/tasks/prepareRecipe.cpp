#include "task.h"

Recipe prepareRecipe(const Recipe &recipe, int servings)
{
  Recipe r = Recipe();
  r.name = recipe.name;
  r.servings = servings;
  for (const auto &ingredient : recipe.ingredient)
  {
    Ingredient i = Ingredient();
    i.name = ingredient.name;
    i.quantity = ingredient.quantity * servings / recipe.servings;
    i.unit = ingredient.unit;
    r.ingredient.push_back(i);
  }
  for (const auto &step : recipe.steps)
  {
    r.steps.push_back(step);
  }
  return r;
}