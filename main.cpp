#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Parser/DatalogProgram.h"
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Lexer/Token.h"

using namespace std;

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        cout << "Usage:" << endl;
        cout << "    ./lab1 [infile]" << endl;
        return 0;
    }
    
    string filename = argv[1];
    ifstream f(filename);
    string input;
    if (f) {
       ostringstream ss;
       ss << f.rdbuf();
       input = ss.str();
    } else {
        cout << " Error: " << filename << ": No such file or directory" << endl;
        return 0;
    }
    
    Lexer* lexer = new Lexer();
    lexer->Run(input);
    vector<Token*> tokens = lexer->GetTokens();
    delete lexer;
    
    Parser* parser = new Parser();
    DatalogProgram* datalogProgram = parser->Parse(tokens);
    delete parser;
    
    delete datalogProgram;
    
    return 0;
}
