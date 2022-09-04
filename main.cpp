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
  index_type m_indexCard{};

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
    m_indexCard = 0;
  }

  const Card& dealCard() { return m_deck[m_indexCard++]; }
};

class Player {
private:
  int m_score{};

public:
  int drawCard(Deck& card) {
    int value = card.dealCard().value();
    return m_score += value;
  }


  int score() const  {
    return m_score;
  }

  bool isBust() const  {
    return (m_score > Config::g_maximumScore);
  }
};

int main() {

  Deck deck{};

  deck.shuffle();
  deck.print();

  Player player{};
  Player dealer{};

  int playerCard { player.drawCard(deck) };
  std::cout << "The player drew a card with value " << playerCard << " and now has score " << player.score() << '\n';

  int dealerCard { dealer.drawCard(deck) };
  std::cout << "The dealer drew a card with value " << dealerCard << " and now has score " << dealer.score() << '\n';
  return 0;
}
