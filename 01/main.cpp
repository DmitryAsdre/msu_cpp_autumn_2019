#include <iostream>
#include <string> 
#include <vector>
#include <cstdlib>
#include <cmath>
using namespace std;

const double EPS = 1e-16;
typedef enum 
{
    NUM,
    OPEN_BRAKE,
    CLOSE_BRAKE,
    PLUS, 
    MINUS,
    UN_MINUS,
    MULT,
    DIV,
    END,
    BEGIN
}LexemType;

typedef struct
{
    LexemType type;
    double num;
}LexemHandler;

LexemHandler curLexem = {BEGIN, 0.};
size_t curPosition = 0;

ostream & operator <<(ostream & os, const LexemHandler& lexem);

LexemHandler getNextLexem(const string& input);

double expression(const string& input);
double item(const string& input);
double mult(const string& input); 

bool checkInput(const string& input);

int main(int argc, char ** argv)
{
    if(argc != 2)
    {
        cout << "error" << endl;
        return EXIT_FAILURE;
    }
    string input(argv[1]);
    checkInput(input);
    curLexem = getNextLexem(input);
    cout << expression(input) << endl;
    return EXIT_SUCCESS;
}
ostream& operator <<(ostream& os, const LexemHandler& lexem)
{
    if(lexem.type == NUM)
        os << "NUM" << " " << lexem.num;
    else if(lexem.type == OPEN_BRAKE)
        os << "OPEN_BRAKE";
    else if(lexem.type == CLOSE_BRAKE)
        os << "CLOSE_BRAKE";
    else if(lexem.type == PLUS)
        os << "PLUS";
    else if(lexem.type == MINUS)
        os << "MINUS";
    else if(lexem.type == UN_MINUS)
        os << "UN_MINUS";
    else if(lexem.type == MULT)
        os << "MULT";
    else if(lexem.type == DIV)
        os << "DIV";
    else if(lexem.type == END)
        os << "END";
    else if(lexem.type == BEGIN)
        os << "BEGIN";
    return os;
}
LexemHandler getNextLexem(const string& input)
{
    LexemHandler lexem;
    while(curPosition < input.size() && input[curPosition] == ' ')
        curPosition++;
    if(curPosition == input.size())
    {
        lexem.type = END;
        return lexem;
    }
    if(input[curPosition] - '0' < 10 && input[curPosition] - '0' >= 0)
    {
        string buffer;
        while(curPosition < input.size() &&((input[curPosition] - '0' < 10 && input[curPosition] - '0' >= 0) || input[curPosition] == '.'))
        {
            buffer.push_back(input[curPosition]);
            curPosition++;
        }        
        lexem.type = NUM;
        lexem.num =  stod(buffer);
    } 
    else if (input[curPosition] == '(')
    {
        lexem.type = OPEN_BRAKE;
        curPosition++;
    }
    else if(input[curPosition] == ')')
    {
        lexem.type = CLOSE_BRAKE;
        curPosition++;
    }
    else if(input[curPosition] == '+') 
    {
        lexem.type = PLUS;
        curPosition++;
    }
    else if(input[curPosition] == '-')
    {
        if(curLexem.type != BEGIN &&(curLexem.type == CLOSE_BRAKE || curLexem.type == NUM))
        {
            lexem.type = MINUS;
            curPosition++;
        }
        else
        {
            lexem.type = UN_MINUS;
            curPosition++;
        }
    }
    else if(input[curPosition] == '*')
    {
        lexem.type = MULT;
        curPosition++;
    }
    else if(input[curPosition] == '/')
    {
        lexem.type = DIV;
        curPosition++;
    }
    else 
    {
        cout << "error" << endl;
        exit(EXIT_FAILURE);
    }
    return lexem;
}
double expression(const string& input)
{
    double tmp = 0;
    tmp = item(input);
    while(curLexem.type == PLUS || curLexem.type == MINUS)
    {
        if(curLexem.type == PLUS)
        {
            curLexem = getNextLexem(input);
            tmp += item(input);  
        }
        else if(curLexem.type == MINUS)
        {
            curLexem =  getNextLexem(input);
            tmp -= item(input);
        }
    }
    return tmp;
}
double item(const string& input)
{
    double tmp = 1;
    tmp = mult(input);
    while(curLexem.type == MULT || curLexem.type == DIV)
    {
        if(curLexem.type == MULT)
        {
            curLexem = getNextLexem(input);
            tmp *= mult(input);
        }
        else if(curLexem.type == DIV)
        {
            curLexem = getNextLexem(input);
            double res = mult(input);
            if(fabs(res) < EPS)
            {
                cout << "error" << endl;
                exit(EXIT_FAILURE);
            }
            tmp /= res;
        }
    }
    return tmp;
}
double mult(const string& input)
{
    double tmp = 0;
    if(curLexem.type == NUM)
    {
        tmp = curLexem.num;
        curLexem = getNextLexem(input); 
    }
    else if(curLexem.type == OPEN_BRAKE)
    {
        curLexem = getNextLexem(input);
        tmp = expression(input);
        if(curLexem.type == CLOSE_BRAKE)
        {
            curLexem = getNextLexem(input);
        }
    }    
    else if(curLexem.type == UN_MINUS)
    {
        curLexem.type = MULT;
        return -1;
    }
    return tmp;
}  
bool checkInput(const string& input)
{
    LexemHandler previousLexem = {BEGIN, 0.};
    LexemHandler currentLexem = {BEGIN, 0.};
    LexemHandler nextLexem = {BEGIN, 0.};
    curLexem = getNextLexem(input);
    currentLexem = curLexem;
    curLexem = getNextLexem(input);
    nextLexem = curLexem;
    long long int counter = 0;
    while(currentLexem.type != END)
    {
        //cout << previousLexem << " " <<  currentLexem << " " << nextLexem << endl;
        if(currentLexem.type == PLUS || currentLexem.type == MINUS || currentLexem.type == MULT || currentLexem.type == DIV)
        {
            if(previousLexem.type != CLOSE_BRAKE && previousLexem.type != NUM)
            {
                cout << "error" << endl;
                exit(EXIT_FAILURE);
            }
            if(nextLexem.type != OPEN_BRAKE && nextLexem.type != NUM && nextLexem.type != UN_MINUS)
            {
                cout << "error" << endl;
                exit(EXIT_FAILURE);
            }
        }
        else if(currentLexem.type == UN_MINUS)
        {
            if(nextLexem.type != OPEN_BRAKE && nextLexem.type != NUM && nextLexem.type != UN_MINUS)
            {
                cout << "error" << endl;
                exit(EXIT_FAILURE);
            }
        }
        else if(currentLexem.type == OPEN_BRAKE)
        {
            counter++;
            if(previousLexem.type == NUM || previousLexem.type == CLOSE_BRAKE ) 
            {
                cout << "error" << endl;
                exit(EXIT_FAILURE);
            }
            if(nextLexem.type == CLOSE_BRAKE || nextLexem.type == END)
            {
                cout << "error" << endl;
                exit(EXIT_FAILURE);
            }
        }
        else if(currentLexem.type == CLOSE_BRAKE)
        {
            counter--;
            if(nextLexem.type == NUM || nextLexem.type == OPEN_BRAKE)
            {
                cout << "error" << endl;
                exit(EXIT_FAILURE);
            }
            if(previousLexem.type == BEGIN)
            {
                cout << "error" << endl;
                exit(EXIT_FAILURE);
            }
        }
        else if(currentLexem.type == NUM)
        {
            if(previousLexem.type == NUM)
            {
                cout << "error" << endl;
                exit(EXIT_FAILURE);
            }
        }            
        previousLexem = currentLexem;
        currentLexem = nextLexem;
        curLexem = getNextLexem(input);
        nextLexem = curLexem;
    }
    if(abs(counter)> 0)
    {
        cout << "error" << endl;
        exit(EXIT_FAILURE);
    }
    curPosition = 0;
    curLexem = {BEGIN, 0.};
}