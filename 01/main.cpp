#include <iostream>
#include <string> 
#include <vector>
#include <cstdlib>
#include <cmath>
using namespace std;

const double EPS = 1e-16;
enum LexemType
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
};

struct LexemHandler
{
    LexemType type;
    double num;
};

//LexemHandler curLexem = {BEGIN, 0.};
//size_t curPosition = 0;

ostream & operator <<(ostream & os, const LexemHandler& lexem);

void getNextLexem(const string& input, size_t& curPosition, LexemHandler& curLexem) ;

double expression(const string& input, size_t& curPosition, LexemHandler& curLexem);
double item(const string& input, size_t& curPosition, LexemHandler& curLexem);
double mult(const string& input, size_t& curPosition, LexemHandler& curLexem); 

void checkInput(const string& input);

int main(int argc, char ** argv)
{
    if(argc != 2)
    {
        cout << "error" << endl;
        return EXIT_FAILURE;
    }
    string input(argv[1]);
    LexemHandler curLexem = {BEGIN, 0.};
    size_t curPosition = 0;
    try
    {
        checkInput(input);
        getNextLexem(input, curPosition, curLexem);
        cout << expression(input, curPosition, curLexem) << endl;
    }
    catch(const std::exception& e)
    {
        cout << e.what() << endl;
        return EXIT_FAILURE;
    }
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
    else 
        throw runtime_error("UNKNOWN_LEXEM_OPERATOR<<");
    return os;
}
void getNextLexem(const string& input, size_t& curPosition, LexemHandler& curLexem)
{
    while(curPosition < input.size() && input[curPosition] == ' ')
        curPosition++;
    if(curPosition == input.size())
    {
        curLexem.type = END;
        return ;
    }
    if(input[curPosition] - '0' < 10 && input[curPosition] - '0' >= 0)
    {
        string buffer;
        while(curPosition < input.size() &&((input[curPosition] - '0' < 10 && input[curPosition] - '0' >= 0) || input[curPosition] == '.'))
        {
            buffer.push_back(input[curPosition]);
            curPosition++;
        }        
        curLexem.type = NUM;
        curLexem.num =  stod(buffer);
    } 
    else if (input[curPosition] == '(')
    {
        curLexem.type = OPEN_BRAKE;
        curPosition++;
    }
    else if(input[curPosition] == ')')
    {
        curLexem.type = CLOSE_BRAKE;
        curPosition++;
    }
    else if(input[curPosition] == '+') 
    {
        curLexem.type = PLUS;
        curPosition++;
    }
    else if(input[curPosition] == '-')
    {
        if(curLexem.type != BEGIN &&(curLexem.type == CLOSE_BRAKE || curLexem.type == NUM))
        {
            curLexem.type = MINUS;
            curPosition++;
        }
        else
        {
            curLexem.type = UN_MINUS;
            curPosition++;
        }
    }
    else if(input[curPosition] == '*')
    {
        curLexem.type = MULT;
        curPosition++;
    }
    else if(input[curPosition] == '/')
    {
        curLexem.type = DIV;
        curPosition++;
    }
    else 
        throw runtime_error("unknown_lexem");
}
double expression(const string& input, size_t& curPosition, LexemHandler& curLexem)
{
    double tmp = 0;
    tmp = item(input, curPosition, curLexem);
    while(curLexem.type == PLUS || curLexem.type == MINUS)
    {
        if(curLexem.type == PLUS)
        {
            getNextLexem(input, curPosition, curLexem);
            tmp += item(input, curPosition, curLexem);  
        }
        else if(curLexem.type == MINUS)
        {
            getNextLexem(input, curPosition, curLexem);
            tmp -= item(input, curPosition, curLexem);
        }
    }
    return tmp;
}
double item(const string& input, size_t& curPosition, LexemHandler& curLexem)
{
    double tmp = 1;
    tmp = mult(input, curPosition, curLexem);
    while(curLexem.type == MULT || curLexem.type == DIV)
    {
        if(curLexem.type == MULT)
        {
            getNextLexem(input, curPosition, curLexem);
            tmp *= mult(input, curPosition, curLexem);
        }
        else if(curLexem.type == DIV)
        {
            getNextLexem(input, curPosition, curLexem);
            double res = mult(input, curPosition, curLexem);
            if(fabs(res) < EPS)
            {
                throw runtime_error("division_by_0");
            }
            tmp /= res;
        }
    }
    return tmp;
}
double mult(const string& input, size_t& curPosition, LexemHandler& curLexem)
{
    double tmp = 0;
    if(curLexem.type == NUM)
    {
        tmp = curLexem.num;
        getNextLexem(input, curPosition, curLexem); 
    }
    else if(curLexem.type == OPEN_BRAKE)
    {
        getNextLexem(input, curPosition, curLexem);
        tmp = expression(input, curPosition, curLexem);
        if(curLexem.type == CLOSE_BRAKE)
        {
            getNextLexem(input, curPosition, curLexem);
        }
    }    
    else if(curLexem.type == UN_MINUS)
    {
        curLexem.type = MULT;
        return -1;
    }
    return tmp;
}  

void checkInput(const string& input)
{
    LexemHandler previousLexem = {BEGIN, 0.};
    LexemHandler currentLexem = {BEGIN, 0.};
    LexemHandler nextLexem = {BEGIN, 0.};
    LexemHandler curLexem = {BEGIN, 0};
    size_t curPosition = 0;
    getNextLexem(input, curPosition, curLexem);
    currentLexem = curLexem;
    getNextLexem(input, curPosition, curLexem); 
    nextLexem = curLexem;
    long long int counter = 0;
    if(currentLexem.type == END && previousLexem.type == BEGIN)
    {
        throw runtime_error("empty_input");
    }
    while(currentLexem.type != END)
    {
        //cout << previousLexem << " " <<  currentLexem << " " << nextLexem << endl;
        if(currentLexem.type == PLUS || currentLexem.type == MINUS || currentLexem.type == MULT || currentLexem.type == DIV)
        {
            if(previousLexem.type != CLOSE_BRAKE && previousLexem.type != NUM)
                throw runtime_error("binary_operator_error");
            if(nextLexem.type != OPEN_BRAKE && nextLexem.type != NUM && nextLexem.type != UN_MINUS)
                throw runtime_error("binary_operator_error");
        }
        else if(currentLexem.type == UN_MINUS)
        {
            if(nextLexem.type != OPEN_BRAKE && nextLexem.type != NUM && nextLexem.type != UN_MINUS)
                throw runtime_error("un_minus_error");
        }
        else if(currentLexem.type == OPEN_BRAKE)
        {
            counter++;
            if(previousLexem.type == NUM || previousLexem.type == CLOSE_BRAKE )
                throw runtime_error("open_bracket_error");
            if(nextLexem.type == CLOSE_BRAKE || nextLexem.type == END)
                throw runtime_error("open_bracket_error");
        }
        else if(currentLexem.type == CLOSE_BRAKE)
        {
            counter--;
            if(nextLexem.type == NUM || nextLexem.type == OPEN_BRAKE)
                throw runtime_error("close_braсket_error");
            if(previousLexem.type == BEGIN)
                throw runtime_error("close_bracket_error");
        }
        else if(currentLexem.type == NUM)
        {
            if(previousLexem.type == NUM)
                throw runtime_error("num_error");
        }
        previousLexem = currentLexem;
        currentLexem = nextLexem;
        getNextLexem(input, curPosition, curLexem);
        nextLexem = curLexem;
    }
    if(abs(counter)> 0)
    {
        cout << "error_bracket" << endl;
        exit(EXIT_FAILURE);
    }
    curPosition = 0;
    curLexem = {BEGIN, 0.};
}