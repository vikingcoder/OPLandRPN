#ifndef CONVERTOPL_H
#define CONVERTOPL_H
#include "stack.h"
#include "map"
using stackTypePtr =  std::shared_ptr<Stack<std::string>>;

class ConvertOPL
{
    std::string output;
    std::map<char,int> map{{'(',1},
                           {'+',2},
                           {'-',2},
                           {'*',3},
                           {'/',3},
                           {'^',4},
                           {'%',3},};

    std::map<char,optype> map2{{'+',plus},
                           {'-', minus},
                           {'*',multiply},
                           {'/',devide},
                           {'^',power},};

public:
    ConvertOPL();
    void fromOPL(std::string);
    void isNumber(int &,std::string &,std::string & );
    void isNumber(std::shared_ptr<Stack<std::string> > &st,int &i,std::string & input);
    void fromRPN(std::string);
    void isZnack(std::shared_ptr<Stack<std::string> > &st, int& i, std::string & input,  std::shared_ptr<Stack<std::string>> &h1, stackTypePtr & h2);
    void printOutput(std::shared_ptr<Stack<std::string>>  & st, std::string & input);
    bool determinationOfZhack(optype &type, int &i, std::string &input);
    bool checkDataStack(std::string & tmp,stackTypePtr &stack2, stackTypePtr & stack1,stackTypePtr & m_stack);
    bool theFormationOfParentheses(stackTypePtr & stack2, std::string & tmp, std::string &input, optype & type, int jump, int &i);
    void concatStack(stackTypePtr &stack2,stackTypePtr &stack1,stackTypePtr &m_stack,std::string & tmp,optype type);
    template <class T>
    void printOutput(T & st, std::string & input);
    template <class T>
    void definitionBrackets(int &i,std::string & c,T & st);
    template <class T>
    void workWhistOper(int & i,  std::string & c, T & st);


};

template <typename T>
void ConvertOPL::workWhistOper(int & i,  std::string & c, T& st){
    const char*a = c.c_str();

    if (map.find(a[0]) != map.end()) {
        std::string t ="";
        if(st->getStateHead()){
            t =st->pop();
        }
        const char * b = t.c_str();
        auto it = map.find(a[0]);
        auto it2 = map.find(b[0]);
        if(it->second > it2->second ){
            st->puch(t);
            st->puch(c);
            i++;
        }
        else if (c == "(") {
            st->puch(c);
            i++;
        }
        else {
            st->puch(c);
            output+=t;
            i++;
        }

    }

}

template <class T>
void ConvertOPL::definitionBrackets(int &i,std::string & c,T & st){
    if (c == ")") {
        do{
            std::string a = st->pop();
            if(a != "("){
                output +=a;
            }
            else {
                i++;
                break;
            }
        }
        while (1) ;

    }
}
template <class T>
void ConvertOPL::printOutput(T & st, std::string & input)
{
    while (st->getStateHead()) {
        output+= st->pop();

    }
    std::cout<<input<<'\n';
    std::cout<<output;
}
#endif // CONVERTOPL_H
