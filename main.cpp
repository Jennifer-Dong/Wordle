/*
 * Jennifer Dong
 * Main file for the Wordle Application
 * 2023-10-3
 */

#include <Wt/WApplication.h>
#include "WordleApplication.h"

int main(int argc, char **argv)
{
  return Wt::WRun(argc, argv, [](const Wt::WEnvironment &env) { //executes environment of the web request
    return std::make_unique<WordleApplication>(env);            //instance of WordleApplication created
  });
}
