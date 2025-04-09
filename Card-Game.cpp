#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

struct card {
    std::string suit{""};
    std::string rank{""};
    int value{0};
    card(std::string &suit, std::string &rank, int &value)
        : suit(suit), rank(rank), value(value) {}
};

class deck {
    private:
        std::vector<std::string> card_suits = {"hearts", "diamonds", "clubs", "spades"};
        std::vector<std::string> card_ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
        std::vector<card> cards;
        std::vector<card> discard_pile;
        std::random_device rd;
        std::mt19937 g;
        
    public:
        deck() : g(rd()) {}
        
        void make_deck() {
            for(std::string suit : card_suits) {
                int current_value{0};
                for(std::string rank : card_ranks) {
                    current_value++;
                    cards.push_back(card(suit, rank, current_value));
                }
            }   
        }
        
        void print_deck() {
            for(card selected_card : cards) {
                std::cout << selected_card.rank << " of " << selected_card.suit << '\n';
            }   
        }
        
        void shuffle_deck() {
            std::shuffle(cards.begin(), cards.end(), g);
        }
        
        card draw_card() {
            card drawn_card = cards.front();
            cards.erase(cards.begin());
            return drawn_card;  
        }
};

int main() {
    
    
    deck mydeck;
    mydeck.make_deck();
    mydeck.shuffle_deck();
    card drawn_card = mydeck.draw_card();
    std::cout << drawn_card.rank << " of " << drawn_card.suit;
    
    return 0;
}
