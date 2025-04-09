#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

struct card {
    std::string suit{""};
    std::string rank{""};
    int value{0};
    card(std::string suit, std::string rank, int value)
        : suit(suit), rank(rank), value(value) {}
    std::string card_info() {
        return (rank + " of " + suit);
    }   
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

class player {
    private:
        std::string name{""};
        std::vector<card> hand; // this is used as the players deck in war
    
    public:
        player(std::string player_name) : name(player_name) {}
        
        void draw_card(deck &deck_to_draw_from) {
                hand.push_back(deck_to_draw_from.draw_card());
            }
            
        card draw_first_card () { // draws the first card in hand, or from the players deck in war
            card first_card_in_hand = hand.front();
            hand.erase(hand.begin());
            return first_card_in_hand;
        }  
        
        void pick_up_card(card &card_picked_up) {
            hand.push_back(card_picked_up);
        }
        
        int card_count() {
            return hand.size();   
        }
        
        std::string get_name() {
            return name;   
        }
};

class war {
    private:
        card player_one_card;
        card player_two_card;
        player player_one;
        player player_two;
        std::vector<card> war_pile;
        bool autorun{false};
    
    public:
        war(std::string player_one_name, std::string player_two_name, bool autorun) : player_one_card("none", "none", 0), player_two_card("none", "none", 0), player_one(player_one_name), player_two(player_two_name), autorun(autorun) {}
    
        void setup_game() {
            deck mydeck;
            mydeck.make_deck();
            mydeck.shuffle_deck();
            for(int i = 0; i < 52; i++) { // splits the deck in two for both players decks 
                if((i & 1) == 0) {
                    player_one.draw_card(mydeck);
                } else {
                    player_two.draw_card(mydeck);
                }
            } 
        }
        
        void pickup_war_pile(player &winning_player) {
            if(war_pile.size() != 0) {
                std::cout << winning_player.get_name() << " won the war and took the cards: ";
                for(card selected_card : war_pile) {
                    std::cout << selected_card.card_info() << ", ";
                    winning_player.pick_up_card(selected_card);
                }
                war_pile.clear();
                std::cout << '\n';
            }
        }
        
        void battle() {
            player_one_card = player_one.draw_first_card();
            player_two_card = player_two.draw_first_card();
            std::cout << player_one.get_name() << " drew the " << player_one_card.rank << " of " << player_one_card.suit << '\n'; 
            std::cout << player_two.get_name() << " drew the " << player_two_card.rank << " of " << player_two_card.suit << '\n';
            if(player_one_card.value == player_two_card.value) {
                war_pile.push_back(player_one_card);
                war_pile.push_back(player_two_card);
                std::cout << "its a tie go to war\n\n";
                battle();
            } else if(player_one_card.value > player_two_card.value) {
                std::cout << player_one.get_name() << " wins and takes the " << player_two_card.card_info() << " and the " << player_one_card.card_info() << '\n';
                player_one.pick_up_card(player_two_card);
                player_one.pick_up_card(player_one_card);
                pickup_war_pile(player_one);
            } else {
                std::cout << player_two.get_name() << " wins and takes the " << player_one_card.card_info() << " and the " << player_two_card.card_info() << '\n';
                player_two.pick_up_card(player_one_card);
                player_two.pick_up_card(player_two_card);
                pickup_war_pile(player_two);
            } 
        }
        
        void start_game() {
            while(player_one.card_count() != 0 && player_two.card_count() != 0) {
                battle();
                if(autorun) {std::cout << '\n';}
                else{std::cin.get();}
            }
            if(player_one.card_count() < player_two.card_count()) {
                std::cout << player_two.get_name() << " won because " << player_one.get_name() << " ran out of cards\n";
            } else {
                std::cout << player_one.get_name() << " won because " << player_two.get_name() << " ran out of cards\n";
            }   
        }
};

int main() {
    
    war war_game("bot", "Undeciphered", true);
    war_game.setup_game();
    war_game.start_game();
    
    return 0;
}
