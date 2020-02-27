#include "animal.hh"

#include <iostream>

int main(int argc, char* argv[]) {
  std::ostream& out = std::cout;
  Cat fluffy("fluffy"), simba("simba");
  Dog fido("fido"), rufus("rufus");
  Cow bossy("bossy"), bessie("bessie");
  const Dog *dogs[] = {&fido, &rufus};
  const Cow *cows[] = {&bessie, &bossy};
  const Cat *cats[] = {&fluffy, &simba};

  for (auto dogx : dogs) {
    out << dogx->name << " eats " << dogx->eats() << std::endl;
  }
  for (auto cowx : cows) {
    out << cowx->name << " eats " << cowx->eats() << std::endl;
  }
  for (auto catx : cats) {
    out << catx->name << " eats " << catx->eats() << std::endl;
  }
}
