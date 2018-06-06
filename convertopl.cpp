#include "convertopl.h"

ConvertOPL::ConvertOPL()
{

}


void ConvertOPL::fromOPL(std::string input){
    std::shared_ptr<Stack<std::string>> st(new Stack<std::string> );
    int i =0;

    while(i!=input.length()) {
        std::string c,a;
        c = input.at(i);
        isNumber(i,input,c);
        workWhistOper(i,c,st);
        definitionBrackets(i,c,st);

    }
    printOutput(st,input);
}

void ConvertOPL::isNumber(int & i,std::string & input,std::string & c )
{
    if (c >= "0" && c <= "9") {
        while (c >= "0" && c <= "9"){
            output += input.at(i);
            i++;
            if(i<input.length()){
                c = input.at(i);
            }
            else break;
        }
    }
}

void ConvertOPL::isNumber(std::shared_ptr<Stack<std::string> > &st, int &i, std::string &input)
{
    std::string c,v = "";

    c= input.at(i);
    if (c >= "0" && c <= "9") {
        while (c >= "0" && c <= "9"){

            v+=input.at(i);
            i++;
            c = input.at(i);
        }
        st->puch(v,null);
    }
    else{
        i++;
    }
}

void ConvertOPL::fromRPN(std::string input)
{
    stackTypePtr m_stack(new Stack<std::string>());
    stackTypePtr stack1(new Stack<std::string>());
    stackTypePtr stack2(new Stack<std::string>());
    int i=0;
    while(i!=input.length()-1) {

        isNumber(m_stack,i,input);
        isZnack(m_stack,i,input,stack2,stack1);
    }
    printOutput(m_stack,input);
}

void ConvertOPL::isZnack(std::shared_ptr<Stack<std::string> > &m_stack, int& i, std::string & input,  stackTypePtr &stack2, stackTypePtr & stack1)
{
    if(!m_stack->getStateHead() == NULL){
        std::string tmp = " ";
        optype type;
        if(determinationOfZhack(type,i,input)){
            if( checkDataStack(tmp,stack2,stack1,m_stack)){
                theFormationOfParentheses(stack2,tmp,input,type,1,i);
                theFormationOfParentheses(stack1,tmp,input,type,0,i);
                concatStack(stack2,stack1,m_stack,tmp,type);
            }
        }
    }
    else{
        exit(0);
    }

}

void ConvertOPL::printOutput(std::shared_ptr<Stack<std::string> > &m_stack, std::string &input)
{
    while (m_stack->getStateHead()) {
        output+= m_stack->pop();

    }
    std::cout<<input<<'\n';
    std::cout<<output<<'\n';
}

bool ConvertOPL::checkDataStack(std::string & tmp,stackTypePtr &stack2, stackTypePtr & stack1,stackTypePtr & m_stack)
{
    tmp =m_stack->pop();
    if(tmp!="empty"){
        stack1->puch(tmp);
    }
    else return false;
    tmp = m_stack->pop();
    if(tmp!="empty"){
        stack2->puch(tmp);
        return true;
    }
    else {
        m_stack->puch(stack1->pop());
        return false;};
}

void ConvertOPL::concatStack(stackTypePtr &stack2,stackTypePtr &stack1,stackTypePtr &m_stack,std::string & tmp,optype type)
{
    std::string sStack2 =stack2->pop();
    tmp = sStack2 + stack1->pop();
    m_stack->puch(tmp);
    stack2->puch(sStack2,type);
}

bool ConvertOPL::theFormationOfParentheses(stackTypePtr & stack,std::string & tmp, std::string &input,optype & type,int jump, int & i)
{
    auto it = map2.find(input[i]);
    if(jump == 1){
        if(stack->getOptype()!=null && stack->getOptype()<type) {
            tmp="(" + stack->pop()+it->first;
            stack->puch(tmp);
            tmp= " ";
        }
        else{
            tmp=stack->pop()+input[i];
            stack->puch(tmp);
        }
    }
    else{
        if(stack->getOptype()!=null && stack->getOptype()<type){
            tmp+=stack->pop()+")";
            stack->puch(tmp);
            tmp=" ";
        }
    }
}



bool ConvertOPL::determinationOfZhack(optype &type,int & i,std::string & input)
{
    if(map2.find(input[i]) != map2.end()){
        auto it = map2.find(input[i]);
        type = it->second;
        return true;
    }
}








