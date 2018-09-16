#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    int position;
    getline(std::cin, text);
    if(text.length()==0)
    {
        std::cout << "Empty string" << std::endl;
        return 0;
    }

    Bracket temp = Bracket(text[0],0);

    std::stack <Bracket> opening_brackets_stack;
    for (position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            opening_brackets_stack.push(Bracket(next,position));
        }

        if (next == ')' || next == ']' || next == '}') {
            if(opening_brackets_stack.empty())
            {
                temp = Bracket(next,position);
                break;
            }

            temp = opening_brackets_stack.top();

            if(!temp.Matchc(next))
            {
                temp = Bracket(next,position);
                break;
            }

            temp = Bracket('1',-1);
            opening_brackets_stack.pop();

        }
    }

    if(position!=text.length())
        position=1;

    if(!opening_brackets_stack.empty() && temp.position!=-1)
        std::cout<< temp.position + 1 << std::endl;
    else if(temp.position==-1 && !opening_brackets_stack.empty())
        std::cout << position  << std::endl;
    else
        std::cout << "Success" << std::endl;
    return 0;
}
