#include "Cell.hpp"
#include "../../Standart/CellInterface.hpp"

HouseCell::HouseCell()
  :  Building     (static_cast<size_t>(ReservedTypes::HOUSE), 0),
     tick_count   (0),
     cur_citizens (kAppearIncome.population)
{
  srand(time(nullptr));
}

Resources HouseCell::getAppearIncome() const
{
  return kAppearIncome;
}

Resources HouseCell::getTickIncome()
{
  if (cur_citizens == 0) return kTickIncome;

  Resources tick_income = kTickIncome;
  printf("TICK Plugin: %u %d\n", cur_citizens, tick_count);
  if (tick_count == kBirthTicks)
  {
    int rand_coeff = rand() % kRandomCoeff;
    printf("TICK PLUGIN SUCCESS: %d\n", rand_coeff);
    if (rand_coeff == 0)
    {
      tick_income.population      = -1;
      tick_income.free_population = -1;
      cur_citizens--;
    }
    else
    {
      tick_income.population      = 1;
      tick_income.free_population = 1;
      cur_citizens++;
    }

    tick_count = 0;
  }
  else
  {
    tick_count++;
  }
  std::cout << tick_income << '\n';
  return tick_income;
}

Resources HouseCell::getDestroyIncome() const
{
  Resources destroy_res  = kDestroyIncome;

  destroy_res.population      = -1 * cur_citizens;
  destroy_res.free_population = -1 * cur_citizens;
  printf("KILL: %ld\n", destroy_res.population);

  return destroy_res;
}

Bitmask HouseCell::getBuildMask() const
{
  return kBuildMask;
}
