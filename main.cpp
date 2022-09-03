#include <cassert>
#include <iostream>

namespace Config {
  constexpr int g_maximumScore{21};
  constexpr int g_minimumDealerScore{17};
}

class Card {
public:
  enum Suit {
    clubs,
    diamonds,
    hearts,
    spades,

    max_suits,
  };

  enum Rank {
    rank_2,
    rank_3,
    rank_4,
    rank_5,
    rank_6,
    rank_7,
    rank_8,
    rank_9,
    rank_10,
    rank_jack,
    rank_queen,
    rank_king,
    rank_ace,

    max_ranks,
  };

private:
  Rank m_rank{};
  Suit m_suit{};

public:
  Card() = default;
  Card(Rank rank, Suit suit) : m_rank{rank}, m_suit{suit}{}

  void print() const {
    switch (m_rank) {
      case Rank::rank_2: std::cout << '2'; break;
      case Rank::rank_3: std::cout << '3'; break;
      case Rank::rank_4: std::cout << '4'; break;
      case Rank::rank_5: std::cout << '5'; break;
      case Rank::rank_6: std::cout << '6'; break;
      case Rank::rank_7: std::cout << '7'; break;
      case Rank::rank_8: std::cout << '8'; break;
      case Rank::rank_9: std::cout << '9'; break;
      case Rank::rank_10: std::cout << 'T'; break;
      case Rank::rank_jack: std::cout << 'J'; break;
      case Rank::rank_queen: std::cout << 'Q'; break;
      case Rank::rank_king: std::cout << 'K'; break;
      case Rank::rank_ace: std::cout << 'A'; break;
      default: std::cout << '?'; break;
    }
    switch(m_suit) {
      case Suit::clubs: std::cout << 'C'; break;
      case Suit::diamonds: std::cout << 'D'; break;
      case Suit::hearts: std::cout << 'H'; break;
      case Suit::spades: std::cout << 'S'; break;
      default: std::cout << '?'; break;
    }
  }
  int value() const {
    switch (m_rank) {
      case Rank::rank_2: return 2;
      case Rank::rank_3: return 3;
      case Rank::rank_4: return 4;
      case Rank::rank_5: return 5;
      case Rank::rank_6: return 6;
      case Rank::rank_7: return 7;
      case Rank::rank_8: return 8;
      case Rank::rank_9: return 9;
      case Rank::rank_10: return 10;
      case Rank::rank_jack: return 10;
      case Rank::rank_queen: return 10;
      case Rank::rank_king: return 10;
      case Rank::rank_ace: return 11;
      default: assert(false && "should never happened"); return 0;
    }
  }
};

int main() {

  Card card{Card::rank_queen, Card::diamonds};
  card.print();
  std::cout << " has value " << card.value() << '\n';

  return 0;
}
