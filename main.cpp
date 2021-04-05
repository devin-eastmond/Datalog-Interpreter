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
//    if (argc != 2) {
//        cout << "Usage:" << endl;
//        cout << "    ./lab1 [infile]" << endl;
//        return 0;
//    }
//
//    string filename = argv[1];
//    ifstream f(filename);
//    string input;
//    if (f) {
//       ostringstream ss;
//       ss << f.rdbuf();
//       input = ss.str();
//    } else {
//        cout << " Error: " << filename << ": No such file or directory" << endl;
//        return 0;
//    }

//    Lexer* lexer = new Lexer();
//    lexer->Run(input);
//    vector<Token*> tokens = lexer->GetTokens();
//    delete lexer;
//
//    Parser* parser = new Parser();
//    DatalogProgram* datalogProgram = parser->Parse(tokens);
//    delete parser;
//
//    Interpreter* interpreter = new Interpreter();
//    interpreter->Run(datalogProgram);
//    delete datalogProgram;
//
//    delete interpreter;
    Database* database = new Database();
    database->AddRelation(new Relation("SK", new Header({"cat", "fish"})));
    database->GetRelation("SK")->AddTuple(new Tuple({"1", "2"}));
    database->GetRelation("SK")->AddTuple(new Tuple({"1", "4"}));
    database->GetRelation("SK")->AddTuple(new Tuple({"2", "3"}));
    database->GetRelation("SK")->AddTuple(new Tuple({"3", "3"}));
    database->GetRelation("SK")->AddTuple(new Tuple({"6", "7"}));
    
    database->AddRelation(new Relation("SK2", new Header({"cow", "dog"})));
    database->GetRelation("SK2")->AddTuple(new Tuple({"3", "4"}));
    database->GetRelation("SK2")->AddTuple(new Tuple({"6", "4"}));
//    database->GetRelation("SK2")->AddTuple(new Tuple({"4", "3"}));
//    database->GetRelation("SK2")->AddTuple(new Tuple({"1", "5"}));
//    database->GetRelation("SK2")->AddTuple(new Tuple({"1", "5"}));

    cout << database->ToString() << endl;
    
    Relation* relation = database->GetRelation("SK")->Join(database->GetRelation("SK2"));
    
    cout << relation->ToString() << endl;
    
    return 0;
}
