#include <iostream>
#include "Manager.h"

using namespace ClassProject;

Manager::Manager(){

    std::string s_1 = std::to_string(0);
    std::string s_2 = std::to_string(1);
    std::string false_string = s_1 +"_"+s_1+"_"+s_1;
    std::string true_string = s_2 +"_"+s_2+"_"+s_2;
    std::string false_str = "False";
    std::string true_str = "True";
    BDD_node node1(0,0,0,0,false_str);
    BDD_node node2(1,1,1,1,true_str);
    unique_table.push_back(node1);
    unique_table.push_back(node2);
    reverse_computed_table.insert({false_string,0});
    reverse_computed_table.insert({true_string,1});
}

BDD_ID Manager::createVar(const std::string &label) {

    BDD_node new_var(uniqueTableSize(),1,0,uniqueTableSize(), (std::string&)label);
    std::string s_4 = std::to_string(1);
    std::string s_5 = std::to_string(0);
    std::string s_6 = std::to_string(uniqueTableSize());
    std::string Node_string = s_4 +"_"+s_5+"_"+s_6;
    unique_table.push_back(new_var);
    reverse_computed_table.insert({Node_string,uniqueTableSize()-1});

    return new_var.id;
}

void Manager::addNode(BDD_ID p_id, BDD_ID p_high, BDD_ID p_low, BDD_ID p_topvar, std::string &p_label){
    BDD_node new_var(p_id,p_high,p_low,p_topvar, (std::string&)p_label);
    unique_table.push_back(new_var);
}

BDD_ID Manager::uniqueTableSize(){
    size_t number_nodes;
    number_nodes = unique_table.size();
    return number_nodes;
}

const BDD_ID &Manager::True() {
    return unique_table[1].id;
}

const BDD_ID &Manager::False(){
    return unique_table[0].id;
}

bool Manager::isVariable(BDD_ID x){
    if (unique_table[x].high==1 and unique_table[x].low==0){
        return true;
    }
    return false;
}

std::string Manager::getTopVarName(const BDD_ID &root) {

    BDD_ID id=unique_table[root].topvar;
    return unique_table[id].label;
}

void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) {

    if(nodes_of_root.find(root)==nodes_of_root.end()){

        nodes_of_root.insert(root);
    }

    if (root !=1 and root !=0){

        findNodes(unique_table[root].high,nodes_of_root);
        findNodes(unique_table[root].low,nodes_of_root);
    }

}

void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root){
    std::set<BDD_ID> a={};
    findNodes(root,a);
    for ( std::set<BDD_ID>::iterator itr = a.begin(); itr != a.end(); itr++) {
        if(*itr !=0 and *itr!=1){     //we can replace this by Is_constant function
            vars_of_root.insert(unique_table[*itr].topvar);
        }
    }
}

bool Manager::isConstant(BDD_ID f) {
    bool is_leaf = true;

    if (unique_table[f].id == 0 or unique_table[f].id == 1){
        is_leaf = true;
    }
    else{
        is_leaf = false;
    }

    return is_leaf;
}

BDD_ID Manager::topVar(BDD_ID f){
    return unique_table[f].topvar;
}

void Manager::printUniqueTable( void ){
    std::cout << "ID\t" << "Label\t" << "High\t" << "Low\t" << "TopVar\t\n";
    for( int i = 0; i < uniqueTableSize(); i++){
        std::cout << unique_table[i].id << "\t" << unique_table[i].label << "\t" << unique_table[i].high << "\t" <<
        unique_table[i].low << "\t" << unique_table[i].topvar << "\t\n";
    }
}

BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x){
    BDD_ID T, F;
    //The topVar is the variable with smaller ID in an expression
    //If topVar(f) > x, then x won't compose f, hence it makes no
    //difference for f if x is 1, hence it's a terminal case.
    if( isConstant(f) || isConstant(x) || topVar(f) > x )
        return f;
    if( topVar(f) == x )
        return unique_table[f].high;
    else{ //if topVar(f) < x, then f may depend on x, hence the need of recursion
        T = coFactorTrue( unique_table[f].high, x );
        F = coFactorTrue( unique_table[f].low, x );
        return ite( topVar(f), T, F );
    }
}

BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x) {
    BDD_ID T, F;
    //The topVar is the variable with smaller ID in an expression
    //If topVar(f) > x, then x won't compose f, hence it makes no
    //difference for f if x is 0, hence it's a terminal case.
    if( isConstant(f) || isConstant(x) || topVar(f) > x )
        return f;
    if( topVar(f) == x )
        return unique_table[f].low;
    else{ //if topVar(f) < x, then f may depend on x, hence the need of recursion
        T = coFactorFalse( unique_table[f].high, x );
        F = coFactorFalse( unique_table[f].low, x );
        return ite( topVar(f), T, F );
    }
}

BDD_ID Manager::coFactorTrue(BDD_ID f){
    return unique_table[f].high;
}

BDD_ID Manager::coFactorFalse(BDD_ID f){
    return unique_table[f].low;
}

BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e){
    BDD_ID* id_ptr;
    auto s_1 = std::to_string(i);
    auto s_2 = std::to_string(t);
    auto s_3 = std::to_string(e);
    std::string ite_string = s_1 +"_"+s_2+"_"+s_3;

    //The terminal cases were put before the recursion to avoid overheads
    //if the terminal cases are put after, the coFactors will be calculated
    //unnecessarily. So, the same result would be reached, but with more
    //computations.
    std::unordered_map<std::string,BDD_ID>::const_iterator got = computed_table.find (ite_string);
    if( i == 1 ){
        return t;
    }
    //terminal case
    else if( i == 0 ){
        return e;
    }
    //terminal case
    else if( t == e ){
        return t;
    }
    //terminal case
    else if( t == 1 && e == 0 ){
        return i;
    }
    else if(got != computed_table.end()){
        return got->second;
    }

    //not a terminal case, starts recursions with the ite + coFactors
    else{

        //this part to get the correct topVar
        BDD_ID topVar;
        BDD_ID topVar1=unique_table[i].topvar;
        BDD_ID topVar2=unique_table[t].topvar;
        BDD_ID topVar3=unique_table[e].topvar;


        if(isVariable(topVar1) and (topVar1<=topVar2 or isConstant(topVar2)) and (topVar1<=topVar3 or isConstant(topVar3)))
            topVar=topVar1;
        else {
            if(isVariable(topVar2) and (topVar2<=topVar1 or isConstant(topVar1)) and (topVar2<=topVar3 or isConstant(topVar3)))
                topVar=topVar2;
            else
                topVar=topVar3;
        }

        BDD_ID highSuccessor = ite(coFactorTrue(i,topVar), coFactorTrue(t,topVar),
                                         coFactorTrue(e, topVar));

        BDD_ID lowSuccessor = ite(coFactorFalse(i,topVar), coFactorFalse(t,topVar),
                                        coFactorFalse(e,topVar));

        if (highSuccessor == lowSuccessor){
            computed_table.insert({ite_string,highSuccessor});
            return highSuccessor;
        }

        std::string s_4 = std::to_string(highSuccessor);
        std::string s_5 = std::to_string(lowSuccessor);
        std::string s_6 = std::to_string(topVar);
        std::string Node_string = s_4 +"_"+s_5+"_"+s_6;
        BDD_ID exist = checkExistance(Node_string);


        if (exist == 0) { //check if there is another node with the same top_var high Low
            std::string x = "newNode";
            addNode(uniqueTableSize(), highSuccessor, lowSuccessor, topVar, (std::string &) x);
            computed_table.insert({ite_string,uniqueTableSize()-1});
            reverse_computed_table.insert({Node_string,uniqueTableSize()-1});
            return uniqueTableSize() - 1;
        } else{
            computed_table.insert({ite_string,exist});
            return exist;}
    }
}

BDD_ID Manager::checkExistance(std::string Node_string) {

    std::unordered_map<std::string,BDD_ID>::const_iterator got = reverse_computed_table.find (Node_string);
    if(got!=reverse_computed_table.end()){
        return got->second;
    }
    return  0;
}

BDD_ID Manager::neg(BDD_ID a){

    return ite(a,0,1);

}

BDD_ID Manager::or2(BDD_ID a, BDD_ID b){

    return ite(a,1,b);

}

BDD_ID Manager::and2(BDD_ID a, BDD_ID b){

    return ite(a,b,0);

}

BDD_ID Manager::nor2(BDD_ID a, BDD_ID b){

    return ite(a,0,neg(b));

}

BDD_ID Manager::nand2(BDD_ID a, BDD_ID b){

    return ite(a,neg(b),1);

}

BDD_ID Manager::xor2(BDD_ID a, BDD_ID b) {

    return ite(a, neg(b), b);

}

BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b) {

    return ite(a, b, neg(b));

}