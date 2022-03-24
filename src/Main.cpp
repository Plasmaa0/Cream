#include <iostream>

#include "Lexer.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{
    Lexer lexer("examples/test2.cr");
    std::vector<Token> tokens = lexer.GetTokenArray();
    for (auto &&tok : tokens)
    {
        cout << TokenNames[tok.GetType()];
        if (tok.HaveContents())
        {
            cout << ' ' << tok.GetContents();
        }
        cout << endl;
    }
    // std::string str;
    // cout << "str: ";
    // cin >> str;
    // Tokenizer t;
    // Token tok = t.Tokenize(str);
    // cout << TokenNames[tok.GetType()] << endl;
    return 0;
}