#include <iostream>
#include <string>       // for string
#include <vector>       // to allow vector usage @ Flashcard_Deck
#include <algorithm>    // for SORTcard
#include <fstream>      // for file save/load
using namespace std;

//FlashCard class
class Flashcard {
private:
    string ques;
    string ans;
    int score;

public:
    Flashcard(string q, string a) {
        ques = q; ans = a; score = 0;
    }

    string getQues() const { return ques; }
    string getAns() const { return ans; }
    int getScore() const { return score; }

    void UPDATEscore(const char& reply) {
        if (reply == 'Y' || reply == 'y') {
            score++;
        } else if (reply == 'N' || reply == 'n') {
            score--;
        } else {
            cout << "Invalid input... no change in score.\n";
        }
    }

    void RESETscore() {
        score = 0;
    }
};

class Flashcard_Deck {
private:
    vector<Flashcard> cards;

public:
    void ADDcard(const Flashcard& card) {
        cards.push_back(card);
        cout << "Added in deck!\n\n";
    }

    void LISTcard() const {
        if (cards.empty()) {
            cout << "Empty deck...\n";
            return;
        }

        cout << "\n\t\tFlashcard List:\n";

        for (size_t i = 0; i < cards.size(); i++) {
            cout << (i + 1) << ". "
                 << "Q: " << cards[i].getQues()
                 << "\tA: " << cards[i].getAns()
                 << "\tScore: " << cards[i].getScore()
                 << endl;
        }
    }

    vector<Flashcard>& getCards() {
        return cards;
    }

    void SORTcard() {
        sort(cards.begin(), cards.end(), [](const Flashcard& a, const Flashcard& b) {
            return a.getScore() < b.getScore();
        });
    }
};

class File_Manager {
public:
    static void saveFileIn(const vector<Flashcard>& cards, const string& fname) {
        ofstream outFile(fname);
        if (!outFile) {
            cout << "Error: Unable to open file...\n";
            return;
        }

        for (const Flashcard& card : cards) {
            outFile << card.getQues() << "|" << card.getAns() << "|" << card.getScore() << "\n";
        }

        outFile.close();
        cout << "Flashcards saved to " << fname << endl;
    }

    static vector<Flashcard> loadFromFile(const string& filename) {
        vector<Flashcard> cards;
        ifstream inFile(filename);
        if (!inFile) {
            cout << "No saved flashcards found...\n";
            return cards;
        }

        string line;
        while (getline(inFile, line)) {
            size_t pos1 = line.find('|');
            size_t pos2 = line.rfind('|');

            if (pos1 == string::npos || pos2 == string::npos || pos1 == pos2) continue;

            string q = line.substr(0, pos1);
            string a = line.substr(pos1 + 1, pos2 - pos1 - 1);
            int s = stoi(line.substr(pos2 + 1));

            Flashcard card(q, a);
            while (card.getScore() < s) card.UPDATEscore('Y');
            while (card.getScore() > s) card.UPDATEscore('N');

            cards.push_back(card);
        }

        inFile.close();
        cout<< "-------------------------------------------\n";
        cout << "Loaded " << cards.size() << " flashcards from " << filename << endl;
        return cards;
    }
};

class Flashcard_App {
private:
    Flashcard_Deck deck;
    string filename = "flashcards.txt"; // FIX: define filename here

public:
    void run() {
        int option;

        do {
            cout<< "\n------------------------------------------\n"
                << "\t  FLASHCARD PROGRAM  \n"
                << "-------------------------------------------\n"
                << "1. Add flashcards\n"
                << "2. Review/Test flashcards\n"
                << "3. List all flashcards\n"
                << "4. Save flashcards in file\n"
                << "5. Load all saved flashcards\n"
                << "6. Exit/End\n"
                << "___________________________________________\n"
                << "Choose an option: ";
            cin >> option;
            cin.ignore();

            switch (option) {
                case 1: {
                    string q, a, repeat;

                    cout << "___________________________________________\n";
                    cout << "\n****ADDING FLASHCARDS****\n";

                    do {
                        cout << "\nEnter Question: ";
                        getline(cin, q);
                        cout << "Enter Answer: ";
                        getline(cin, a);

                        Flashcard NEWcard(q, a);
                        deck.ADDcard(NEWcard);

                        cout << "Add another? [Y/N]: ";
                        getline(cin, repeat);
                    } while (repeat == "Y" || repeat == "y");
                    break;
                }

                case 2: {
                    if (deck.getCards().empty()) {
                        cout << "Empty deck..\n";
                        break;
                    }

                    deck.SORTcard();

                    cout<< "___________________________________________\n"
                        << "\n****VIEWING FLASHCARDS****\n";

                    for (Flashcard& card : deck.getCards()) {
                        cout << "\nQ: " << card.getQues() << endl;
                        cout << "A: (Press ENTER to reveal the answer)";
                        cin.ignore();

                        cout << card.getAns() << endl;

                        char reply;
                        cout << "Do you remember the answer? [Y/N]: ";
                        cin >> reply;
                        cin.ignore();

                        card.UPDATEscore(reply);
                        cout << "Score: " << card.getScore() << "\n";
                    }
                    cout << "\n****REACHED THE END OF THE FLASHCARD****\n";

                    break;
                }

                case 3:
                    deck.LISTcard();
                    break;

                case 4:
                    File_Manager::saveFileIn(deck.getCards(), filename);
                    break;

                case 5: {
                    deck = Flashcard_Deck(); // clear the current deck

                    vector<Flashcard> loaded = File_Manager::loadFromFile(filename);
                    for (const Flashcard& card : loaded) {
                        deck.ADDcard(card);
                    }

                    // Immediately show what was loaded
                    cout<< "\n****LOADING FLASHCARDS****\n";
                    deck.LISTcard();

                    break;
                }


                case 6:

                    cout<< "-------------------------------------------\n";
                    cout<<"Exiting..."<<endl;
                    cout << "Goodbye!\n";
                    break;

                default:
                    cout << "Invalid option. Try again.\n";
            }

        } while (option != 6);  // FIX: you had `!= 5`
    }
};

int main() {
    Flashcard_App app;
    app.run();
    return 0;
}
