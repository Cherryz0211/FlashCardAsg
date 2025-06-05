#include <iostream>
#include <string>
#include <vector> //resizable array
using namespace std;

//FlashCard class-> holds answer, questions & score
class Flashcard {
    private://untouched variables
        string ques;
        string ans;
        int score;

    public:
        Flashcard (string q, string a){
            ques=q;ans=a;score=0;
        }
        //the getters
        string getQues()const {return ques;}
        string getAns()const {return ans;}
        int getScore()const {return score;}

        //Score control functions
        void UPDATEscore (const char& feedback){
            if (feedback == 'Y' || feedback =='y'){
                    score++;
            }else if (feedback == 'N' || feedback =='n'){
                score--;
            }else{
                cout<<"Invalid input... no change in score.";
            }
        }

        void RESETscore(){
            score = 0;
        }

};

//to sort, add, review flashcards
class Flashcard_Deck{
    private:
        vector<Flashcard> cards;

    public:
        //add in new cards to deck
        void ADDcard(const Flashcard& card){
            cards.push_back(card);
            cout << "Added in deck!\n";
        }

        //list/view the flashcards
        void LISTcard() const{
            if (cards.size()==0){
                cout<<"Empty deck...\n";
                return;
            }

            cout<< "\n---Flashcard List:---\n";

            for(size_t i = 0; i<cards.size(); i++){
                    cout<<(i+1)<<". "
                        << "Q: " << cards[i].getQues()
                        << "\tA: " << cards[i].getAns()
                        << "\tScore: " << cards[i].getScore()
                        <<endl;
            }
        }

        vector<Flashcard>& getCards(){
            return cards;}
};

class Flashcard_App {
    private:
        Flashcard_Deck deck;

    public:
        void run() { //keeps the program running till user wants to exit
            int choice;

            do(
                //printing menu
                cout<< "\n----------------------------------\n"
                    << "\t  FLASHCARD PROGRAM  \n"
                    << "\n----------------------------------\n"
                    << "1. Add flashcards\n"
                    << "2. Review/Test flashcards\n"
                    << "3. List all flashcards"
                    << "4. Exit/End\n"
                    << "\n----------------------------------\n";
                cout<< "Choose an option: ";
                cin>>option;
                cin.ignore();

                switch(choice){
                case 1: {
                    string q, a, repeat;

                    do{
                        cout <<"\nEnter Q: ";
                        getline(cin, q);
                        cout << "Enter A:";
                        getline(cin,a);

                        Flashcard NEWcard(q,a);
                        deck.ADDcard(NEWcard);

                        cout<<"Add another? [Yes/No]: ";
                        getline(cin,repeat);
                    }while(repeat == "Yes" || repeat == "yes");

                        break;
                }
                case 2: {
                    void LISTcard() const{
                        if (cards.size()==0){
                            cout<<"Empty deck...\n";
                        return;
                    }
                    cout<< "\n----------------------------------\n"
                    << "\t  Review/Test Flashcards \n"
                    << "\n----------------------------------\n";
                    cout << "Q: " << card.getQues() << endl;
                    cout << "A: (Press Enter to reveal answer) ";
                    cin.ignore(); // to pause

                    cout << "Correct Answer: " << card.getAns() << endl;

                    char userInput;
                    cout << "Do you remember this? (type 'Y' if you do or any others if you don't): ";
                    cin>>userInput;

                    card.UPDATEscore(userInput);

                    cout << "Current Score for this card: " << card.getScore() << endl;

                    break;
                }
                case 3: {
                    }
                    }
                    )

        }
        };

int main() {
    /*
    Flashcard card("What is the capital of Malaysia?", "Kuala Lumpur");

    cout << "Q: " << card.getQues() << endl;
    cout << "A: (Press Enter to reveal answer) ";
    cin.ignore(); // to pause

    cout << "Correct Answer: " << card.getAns() << endl;

    char userInput;
    cout << "Do you remember this? (type 'Y' if you do or any others if you don't): ";
    cin>>userInput;

    card.UPDATEscore(userInput);

    cout << "Current Score for this card: " << card.getScore() << endl;
    */
    Flashcard_Deck deck;
    // Add two cards manually
    Flashcard c1("What is the capital of France?", "Paris");
    Flashcard c2("What is 2 + 2?", "4");

    deck.ADDcard(c1);
    deck.ADDcard(c2);

    // List them
    deck.LISTcard();

    return 0;
}

