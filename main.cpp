#include "card.h"
#include "config.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <random>

class Deck {
public:
  using array_type = std::array<Card, 52>;
  using index_type = array_type::size_type;

private:
  array_type m_deck{};

public:
  Deck() {
    index_type index{};
    for (index_type suit{}; suit < Card::max_suits; ++suit) {
      for (index_type rank{}; rank < Card::max_ranks; ++rank) {
        m_deck[index] = {static_cast<Card::Rank>(rank),
                         static_cast<Card::Suit>(suit)};
        ++index;
      }
    }
  }

  void print() const {
    for(const auto& card: m_deck) {
      card.print();
      std::cout << ' ';
    }
    std::cout << '\n';
  }

  void shuffle() {
    std::mt19937 mt{static_cast<std::mt19937::result_type>(std::time(nullptr))};
    std::shuffle(m_deck.begin(), m_deck.end(), mt);
  }
};

int main() {

  Deck deck{};
  deck.print();
  deck.shuffle();
  deck.print();

  return 0;
}
