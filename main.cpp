#include "card.h"
#include "config.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <random>

void ignoreLine() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

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
    m_score += value;
    return value;
  }

  int score() const  {
    return m_score;
  }

  bool isBust() const  {
    return (m_score > Config::g_maximumScore);
  }
};

bool playerWantsToHit() {
  while (true) {
    std::cout << "(h) to hit or (s) to stand: ";
    char ch{};
    std::cin >> ch;
    switch (ch) {
      case 'h': return true;
      case 's': return false;
      default: ignoreLine();
    }
  }
}

bool playerTurn(Deck& deck, Player& player) {
  while (true) {
    if (player.isBust()) {
      return true;
    }else {
      if (playerWantsToHit()) {
        auto value = player.drawCard(deck);
        std::cout << "You were dealt a " << value << " and you have " << player.score() << '\n';
      }else {
        return false;
      }
    }
  }
}

bool dealerTurn(Deck& deck, Player dealer) {
  while (dealer.score() < Config::g_minimumDealerScore) {
    auto value = dealer.drawCard(deck);
    std::cout << "Dealer turned up a " << value << " and now have " << dealer.score() << '\n';
  }

  if (dealer.isBust()) {
    return true;
  }
  return false;
}

bool playerBlackjack(Deck& deck) {
  Player dealer{};
  dealer.drawCard(deck);
  std::cout << "The dealer is showing " << dealer.score() << '\n';

  Player player{};
  player.drawCard(deck);
  player.drawCard(deck);

  std::cout << "you have " << player.score() << '\n';

  if (playerTurn(deck, player)) {
    return false;
  }

  if (dealerTurn(deck, dealer)) {
    return true;
  }
  return (player.score() > dealer.score());
}

int main() {

  Deck deck{};
  deck.shuffle();

  if (playerBlackjack(deck))
  {
    std::cout << "you win \n";
  }else {
    std::cout << "you lose \n";
  }

  return 0;
}
