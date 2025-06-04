#include <iostream>
#include <vector>
#include <string>

using namespace std;

// === FlashCard class ===
class FlashCard {
private:
    string question;
    string answer;
    int difficulty;

public:
    FlashCard(string q, string a) : question(q), answer(a), difficulty(0) {}

    string getQuestion() const { return question; }
    string getAnswer() const { return answer; }
    int getDifficulty() const { return difficulty; }

    void increaseDifficulty() { difficulty++; }
    void decreaseDifficulty() { if (difficulty > 0) difficulty--; }
};

// === FlashCardDeck class ===
class FlashCardDeck {
private:
    vector<FlashCard> cards;

public:
    void addCard(const FlashCard& card) {
        cards.push_back(card);
        cout << "Flashcard added!\n";
    }

   void reviewCards() {
    if (cards.empty()) {
        cout << "No flashcards to review.\n";
        return;
    }

    for (FlashCard& card : cards) {
        cout << "\nQuestion: " << card.getQuestion() << endl;
        cout << "Your answer (type 'idk' if you don't remember): ";
        string userAnswer;
        getline(cin, userAnswer);

        if (userAnswer == "idk") {
            cout << "No worries! The correct answer is: " << card.getAnswer() << endl;
            cout << "🟡 Difficulty remains unchanged.\n";
            // Do nothing
        } else {
            // Compare (case-insensitive)
            string correct = card.getAnswer();
            string response = userAnswer;

            transform(correct.begin(), correct.end(), correct.begin(), ::tolower);
            transform(response.begin(), response.end(), response.begin(), ::tolower);

            if (correct == response) {
                cout << "✅ Correct!\n";
                card.decreaseDifficulty();
            } else {
                cout << "❌ Wrong. The correct answer is: " << card.getAnswer() << endl;
                card.increaseDifficulty();
            }
        }

        cout << "Current difficulty: " << card.getDifficulty() << endl;
    }
}


    void listCards() {
        cout << "\nAll flashcards:\n";
        for (const FlashCard& card : cards) {
            cout << "Q: " << card.getQuestion() << " | A: " << card.getAnswer() << " | Difficulty: " << card.getDifficulty() << endl;
        }
    }
};

// === Main Menu ===
void showMenu() {
    cout << "\n===== Flashcard App =====\n";
    cout << "1. Add Flashcard\n";
    cout << "2. Review Flashcards\n";
    cout << "3. List All Flashcards\n";
    cout << "4. Exit\n";
    cout << "Choose: ";
}

int main() {
    FlashCardDeck deck;
    int choice;

    do {
        showMenu();
        cin >> choice;
        cin.ignore(); // consume newline

        switch (choice) {
            case 1: {
                string q, a;
                cout << "Enter question: ";
                getline(cin, q);
                cout << "Enter answer: ";
                getline(cin, a);
                deck.addCard(FlashCard(q, a));
                break;
            }
            case 2:
                deck.reviewCards();
                break;
            case 3:
                deck.listCards();
                break;
            case 4:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    return 0;
}
