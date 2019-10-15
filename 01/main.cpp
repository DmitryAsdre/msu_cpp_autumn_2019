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

void checkLexems(LexemHandler& previousLexem, LexemHandler& curLexem, long long int& bCount);
//ostream & operator <<(ostream & os, const LexemHandler& lexem);

void getNextLexem(const string& input, size_t& curPosition, LexemHandler& curLexem, long long int& bCount) ;

double expression(const string& input, size_t& curPosition, LexemHandler& curLexem, long long int& bCount);
double item(const string& input, size_t& curPosition, LexemHandler& curLexem, long long int& bCount);
double mult(const string& input, size_t& curPosition, LexemHandler& curLexem, long long int& bCount); 


int main(int argc, char ** argv)
{
    if(argc != 2)
    {
        cout << "unexpected_input" << endl;
        return EXIT_FAILURE;
    }
    string input(argv[1]);
    LexemHandler curLexem = {BEGIN, 0.};
    size_t curPosition = 0;
    long long int bCount = 0;
    try
    {
        getNextLexem(input, curPosition, curLexem, bCount);
        double tmp = expression(input, curPosition, curLexem, bCount);
        while(curLexem.type != END)
            getNextLexem(input, curPosition, curLexem, bCount);
        cout << tmp << endl;
    }
    catch(const exception& e)
    {
        cout << e.what() << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
/*ostream& operator <<(ostream& os, const LexemHandler& lexem)
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
*/
void getNextLexem(const string& input, size_t& curPosition, LexemHandler& curLexem, long long int& bCount)
{ 
    LexemHandler previousLexem = curLexem;

    while(curPosition < input.size() && input[curPosition] == ' ')
        curPosition++;
    if(curPosition == input.size())
        curLexem.type = END;
    else if(input[curPosition] - '0' < 10 && input[curPosition] - '0' >= 0)
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
    checkLexems(previousLexem, curLexem, bCount);
}
void checkLexems(LexemHandler& previousLexem, LexemHandler& curLexem, long long int& bCount)
{
    if(curLexem.type == PLUS || curLexem.type == MINUS || curLexem.type == MULT || curLexem.type == DIV)
    {
        if(previousLexem.type != NUM && previousLexem.type != CLOSE_BRAKE)
            throw runtime_error("binary_operator_error");
    }
    else if(curLexem.type == CLOSE_BRAKE)
    {
        bCount--;
        if(previousLexem.type != NUM && previousLexem.type != CLOSE_BRAKE)
            throw runtime_error("brackets_error");        
    }
    else if(curLexem.type == OPEN_BRAKE)
    {
        bCount++;
        if(previousLexem.type == CLOSE_BRAKE || previousLexem.type == NUM)
            throw runtime_error("brackets_error");
    }
    else if(curLexem.type == UN_MINUS)
    {
    }
    else if(curLexem.type == NUM)
    {
        if(previousLexem.type == NUM || previousLexem.type == CLOSE_BRAKE)
            throw runtime_error("num_error");
    }
    else if(curLexem.type == END)
    {
        //cout << bCount << endl;
        if(previousLexem.type != CLOSE_BRAKE && previousLexem.type != NUM)
            throw runtime_error("unexpected_end");
        if(abs(bCount) != 0)
            throw runtime_error("brackets_error");
    }
}
double expression(const string& input, size_t& curPosition, LexemHandler& curLexem, long long int& bCount)
{
    double tmp = 0;
    tmp = item(input, curPosition, curLexem, bCount);
    while(curLexem.type == PLUS || curLexem.type == MINUS)
    {
        if(curLexem.type == PLUS)
        {
            getNextLexem(input, curPosition, curLexem, bCount);
            tmp += item(input, curPosition, curLexem, bCount);  
        }
        else if(curLexem.type == MINUS)
        {
            getNextLexem(input, curPosition, curLexem, bCount);
            tmp -= item(input, curPosition, curLexem, bCount);
        }
    }
    return tmp;
}
double item(const string& input, size_t& curPosition, LexemHandler& curLexem, long long int& bCount)
{
    double tmp = 1;
    tmp = mult(input, curPosition, curLexem, bCount);
    while(curLexem.type == MULT || curLexem.type == DIV)
    {
        if(curLexem.type == MULT)
        {
            getNextLexem(input, curPosition, curLexem, bCount);
            tmp *= mult(input, curPosition, curLexem, bCount);
        }
        else if(curLexem.type == DIV)
        {
            getNextLexem(input, curPosition, curLexem, bCount);
            double res = mult(input, curPosition, curLexem, bCount);
            if(fabs(res) < EPS)
            {
                throw runtime_error("division_by_0");
            }
            tmp /= res;
        }
    }
    return tmp;
}
double mult(const string& input, size_t& curPosition, LexemHandler& curLexem, long long int& bCount)
{
    double tmp = 0;
    if(curLexem.type == NUM)
    {
        tmp = curLexem.num;
        getNextLexem(input, curPosition, curLexem, bCount); 
    }
    else if(curLexem.type == OPEN_BRAKE)
    {
        getNextLexem(input, curPosition, curLexem, bCount);
        tmp = expression(input, curPosition, curLexem, bCount);
        if(curLexem.type == CLOSE_BRAKE)
        {
            getNextLexem(input, curPosition, curLexem, bCount);
        }
    }    
    else if(curLexem.type == UN_MINUS)
    {
        curLexem.type = MULT;
        return -1;
    }
    return tmp;
}  