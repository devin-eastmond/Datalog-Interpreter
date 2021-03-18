#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Parser/DatalogProgram.h"
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Lexer/Token.h"
#include "Interpreter/Interpreter.h"

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
    
    Interpreter* interpreter = new Interpreter();
    interpreter->Run(datalogProgram);
    delete datalogProgram;
    
    delete interpreter;
//    Database* database = new Database();
//    database->AddRelation(new Relation("SK", new Header({"A", "B"})));
//    database->GetRelation(0)->AddTuple(new Tuple({"a", "c"}));
//    database->GetRelation(0)->AddTuple(new Tuple({"b", "c"}));
//    database->GetRelation(0)->AddTuple(new Tuple({"b", "b"}));
//    database->GetRelation(0)->AddTuple(new Tuple({"b", "c"}));
//
//    cout << database->ToString() << endl;
//
//    Relation* selectTest = database->GetRelation(0)->Select(0, "a");
//    cout << selectTest->ToString() << endl;
//
//    Relation* selectTest2 = database->GetRelation(0)->Select(0, 1);
//    cout << selectTest2->ToString() << endl;
//
//    Relation* projectTest = database->GetRelation(0)->Project({"A"});
//    cout << projectTest->ToString() << endl;
//
//    Relation* projectTest2 = database->GetRelation(0)->Project({"B"});
//    cout << projectTest2->ToString() << endl;
//
    
    return 0;
}
