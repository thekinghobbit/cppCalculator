#include <iostream>
using namespace std;

#include "calc.h"
#include <cstring>

// Write functions in this order.  Constructor and destructor will be built as the
// functions it invokes are written

Calc::Calc(char *argvIn)
{
    inFix = argvIn;
    stk = new Stack;
    if(!CheckTokens())
    {
        cout << "invalid character(s)\n";
        exit(EXIT_FAILURE);
    }
    if(!CheckParens())
    {
        cout << "parens not equal\n";
        exit(EXIT_FAILURE);
    }
    MakeValueTbl();
    Parse();
    InFixToPostFix();
}

Calc::~Calc()
{
    delete[] inFix;
    delete[] valueTbl;
    delete stk;
}

bool Calc::CheckTokens()
{
    
    bool token = true;
    int count = 0;
    while (inFix[count] != '\0')
    {   
        char ch = inFix[count];
        if(!isupper(ch) and !isdigit(ch) and ch!='(' and ch!=')' and ch!='+' and ch!='-' and ch!='/' and ch!='*'){
            token = false;
            break; 
        }
        
        count++;
    }
    return token;
}

void Calc::MakeValueTbl()
{
    valueIdx = 0;
    valueTbl = new int[26];
    for (int i = 0; i < 26; i++)
    {
        valueTbl[i] = 0;
    }
}

void Calc::Parse()
{
    int tmpIdx = 0;
    int strCount = 0;
    int tmpLast;
    int len = strlen(inFix);
    char *tmpStr = new char[len + 1];


    while (inFix[tmpIdx] != '\0')
    {
        if (isdigit(inFix[tmpIdx]))
        {
            tmpStr[strCount] = 'A' + valueIdx;
            strCount++;
            int last = FindLast(tmpIdx);
            int num = 0;

            for (int j = tmpIdx; j <= last; j++)
            {
                num = num * 10 + (inFix[j] - 48);
            }

            tmpIdx = last;

            valueTbl[valueIdx] = num;
            valueIdx++;
        }
        else
        {
            tmpStr[strCount] = inFix[tmpIdx];
            strCount++;
        }

        tmpIdx++;
    }
    tmpStr[tmpIdx] = '\0';
    inFix = tmpStr;
}
int Calc::FindLast(int cur)
{
    int tmp = cur;

    while (isdigit(inFix[tmp + 1]))
    {
        tmp++;
    }
    return tmp;
}

bool Calc::CheckParens()// push '(', pop ')' stack will be empty if parens are even
{
    int i = 0;
    char ch = inFix[i];
    bool balanced = true;
    while(balanced && ch != '\0')
    {
        if(ch == '(')
        {
            stk->Push('(');
        }
        else if (ch == ')')
        {
            if(!stk->IsEmpty())
            {
                stk->Pop();
            }
            else{
                balanced = false;
            }
        }
        ch = inFix[++i];
    }
    return (balanced && stk->IsEmpty());
}

void Calc::DisplayInFix()
{
    cout << inFix << endl;
}
void Calc::DisplayPostFix()
{
    cout << postFix << endl;
}

void Calc::InFixToPostFix()
{
    char ch = inFix[0];
    int count = 0;
    int countPost = 0;
    postFix = new char[strlen(inFix)+1];
    while(ch != '\0')
    {
        ch = inFix[count];
        if(isupper(ch))
        {
            postFix[countPost] = ch;
            countPost++;
        }
        if(ch =='+' or ch =='-' or ch =='/' or ch =='*')
        {
            stk->Push(ch);
        }

        if(ch =='(')
        {
            stk->Push(ch);
        }
        if(ch ==')')
        {
            while(stk->Peek() != '(' )
            {
                postFix[countPost] = stk->Peek();
                stk->Pop();
                countPost++;
            }
            stk->Pop();
        }
        count++;
    }
    postFix[countPost] = '\0';
}

int Calc::Evaluate()
{
    int count = 0;
    char ch;
    int result;
    while (postFix[count] != '\0')
    {
        ch = postFix[count];
        if (isalpha(ch))
        {
            stk->Push(ch);
        }
        else
        {
            char op1 = stk->Peek();
            stk->Pop();
            char op2 = stk->Peek();
            stk->Pop();

            
            int o1 = valueTbl[op1-65];
            int o2 = valueTbl[op2-65];
            
            if(ch == '+')
            {
                result = o2 + o1;
            }
            if(ch == '-')
            {
                result = o2 - o1;
            }
            if(ch == '/')
            {
                result = o2 / o1;
            }
            if(ch == '*')
            {
                result = o2 * o1;
            }
            valueTbl[valueIdx] = result;
            stk->Push((valueIdx+65));
        }
       count++;
    }
    stk->Pop();
    return result;

}
