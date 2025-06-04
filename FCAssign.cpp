#include <iostream>
#include <string>
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
            }else{
                score--;
            }
        }

        void RESETscore(){
            score = 0;
        }

};

int main() {
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

    return 0;
}

