/*
 * Jennifer Dong
 * Header file for the Wordle Application
 * 2023-10-3
 */

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <fstream>                                                //file operations
#include <vector>
#include <cstdlib>                                                //random number

//guard
#ifndef Wordle_Header
#define Wordle_Header


class WordleApplication : public Wt::WApplication {
  public:
    WordleApplication(const Wt::WEnvironment& env);

private:
    Wt::WContainerWidget* root_;
    Wt::WText *statusText_;                                       //to set the text to prompt the user
    Wt::WLineEdit* inputField_;                                   //takes input
    Wt::WPushButton* button_;                                     //submit button
    Wt::WPushButton* restart_;                                    //submit button
    Wt::WText* outputText_;                                       //print 
    int guesses_;                                                 //number of guesses
    Wt::WText* answer_;                                           //the chosen word to guess


    

    void checkInput();                                            //function to evaluate the input given
    void restart();                                               //restart game
    std::string getAnswer(const std::vector<std::string>& words); //for possible words to guess
};
#endif //Wordle_Header




