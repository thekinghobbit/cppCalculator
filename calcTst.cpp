#include <iostream>
using namespace std;

#include "calc.h"

/*
    Leif Forrest
    CPSC 122
    This is a command line calculator made using stacks and linked lists

    To Run program use "make clean" then run "make" then "./calc "((A+B)*(X+Y))"" 
    remember to use quotation marks around expression and use parends around the whole eqxpression
*/


int main(int argc, char* argv[])
{
    Calc* C = new Calc(argv[1]);
    C->DisplayInFix();
    C->DisplayPostFix();
    cout << C->Evaluate() << endl;

//  delete C;
 return 0;
}
