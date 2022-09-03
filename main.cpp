#include "card.h"
#include "config.h"
#include <cassert>
#include <iostream>

int main() {

  Card card{Card::rank_queen, Card::diamonds};
  card.print();
  std::cout << " has value " << card.value() << '\n';

  return 0;
}
