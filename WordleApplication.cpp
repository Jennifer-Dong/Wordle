/*
 * Jennifer Dong
 * Code file for the Wordle Application
 * 2023-10-3
 */

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include "WordleApplication.h"
using namespace Wt;


WordleApplication::WordleApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env), guesses_(0) {
    setTitle("Wordle");

    root_ = root();
    answer_ = root_->addWidget(std::make_unique<Wt::WText>(""));

    std::vector<std::string> wordList;                                      //to store the words
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string word;
        while (std::getline(file, word)) {                                  //goes through each line, stores it in word
            wordList.push_back(word);                                       //add the word to list
        }
        file.close();
        std::srand(std::time(0));                                           //generates random number using the time
        
        std::string randomWord = getAnswer(wordList);                       // Randomly select a word from the list to be the answer word
        answer_->setText(randomWord);
        answer_->setHidden(true);
    }

    outputText_ = root_->addWidget(std::make_unique<Wt::WText>(""));
    statusText_=root()->addWidget(std::make_unique<Wt::WText>("Enter guess, 5 letters only: "));
    inputField_ = root_->addWidget(std::make_unique<Wt::WLineEdit>());
    button_ = root_->addWidget(std::make_unique<Wt::WPushButton>("Submit"));
    restart_ = root()->addWidget(std::make_unique<Wt::WPushButton>("Restart?"));
    restart_->setHidden(true);
    button_->clicked().connect(this, &WordleApplication::checkInput);
    restart_->clicked().connect(this, &WordleApplication::restart);
}


//determine the answer word
std::string WordleApplication::getAnswer(const std::vector<std::string>& words) {
    if (words.empty()) {                                                    //if the vector is empty, nothing to select
        return "No words available";
    }
    int randomIndex = std::rand() % words.size();                           //gets random index to choose the word
    return words[randomIndex];
}


//check the input against the answer
void WordleApplication::checkInput() {
    Wt::WString text = inputField_->text();                                 //get text from input

    if (text.toUTF8().length() != 5) {                                      //checks if input is 5 letters
      statusText_->setText("Input must be exactly 5 letters.");
      return;                                                               // Exit the function without processing the input
    }

    //if we have less than 6 guesses so far
    if (guesses_ < 6) {
        
        std::string input = text.toUTF8();                                  //input as string
        std::string randomWord = answer_->text().toUTF8();                  //the answer word as string

        // Convert input to lowercase and check each character is a letter
        for (char &c : input) {
            if (!std::isalpha(c)) {
              statusText_->setText("Enter a word containing only letters.");
              return;
            }
            c = std::tolower(c);
        }

        std::string coloredInput = "";                                      //to store the colored string

        for (size_t i = 0; i < input.size(); ++i) {
            char inputChar = input[i]; 
            char randomChar = randomWord[i];

            if (inputChar == randomChar) {                                  //characters here match, add it as green
                coloredInput += "<span style='color: green;'>" + std::string(1, inputChar) + "</span>";
            } else if (randomWord.find(inputChar) != std::string::npos) {   //returns true if the current input character is in the answer word
                coloredInput += "<span style='color: red;'>" + std::string(1, inputChar) + "</span>";
            } else {                                                        //letter not in the word
                coloredInput += inputChar;
            }
        }

        // Append a line break at the end
        coloredInput += "<br/>";

        // Append the colored input to the existing output text
        outputText_->setText(outputText_->text() + coloredInput);
        statusText_->setText("Enter guess, 5 letters only:");               //set statusText_ back in case it was changed
        
        //guessed the right word!
        if (input == randomWord) {
            statusText_->setText("You guessed correctly! Play again?");
            inputField_->hide();
            button_->hide();
            restart_->setHidden(false);
        }
        
        inputField_->setText("");
        guesses_++;

        //guessed wrong word 6 times
        if (guesses_ == 6) {
            statusText_->setText("You are out of guesses! Play again?");
            inputField_->hide();
            button_->hide();
            restart_->setHidden(false);
        }
    }
}


//restarts the game
void WordleApplication::restart(){
    guesses_ = 0;
    inputField_->setHidden(false);
    button_->setHidden(false);
    button_->setText("Submit");
    restart_->setHidden(true);
    outputText_->setText("");
    statusText_->setText("Enter guess, 5 letters only:");

    std::vector<std::string> wordList; 
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string word;
        while (std::getline(file, word)) { 
            wordList.push_back(word); 
        }
        file.close();
        std::srand(std::time(0));
        std::string randomWord = getAnswer(wordList);
        answer_->setText(randomWord);
    }
}
