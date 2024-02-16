#include <bits/stdc++.h>
#include <ctime>
using namespace std;


class CNF{

    private: 
        string formula ; 

        int search_for_next_bracket( int i ){ 
            if(formula[i] != '(') return i ; 
            stack<int> st; 
            st.push(i);
            i++;
            while(i < formula.size() ){
                if(formula[i] == '(') {
                    st.push(i);
                }else if(formula[i] == ')'){
                    st.pop();
                    if(st.empty()) return i ; 
                }
                i++;
            }
            return -1; 
        }


        int search_for_prev_bracket(int i ){ 
            if(formula[i] != ')') return i ; 
            stack<int> st; 
            st.push(i);
            i--;
            while(i >= 0 ){
                if(formula[i] == ')') {
                    st.push(i);
                }else if(formula[i] == '('){
                    st.pop();
                    if(st.empty()) return i ; 
                }
                i--;
            }
            return -1; 
        }


        void add_bracket_not_operator( ) {
            int n = formula.size() ; 

            for(int i = 0;i<n;i++){
                if(formula[i] == '!' and formula[i+1] != '!') {
                    int start = i + 1 ; 
                    int end = search_for_next_bracket( i + 1 ) ; 
                    if(i - 1 >= 0 and end + 1 < n and formula[i-1] == '(' and formula[end + 1] == ')') continue;
                    string parenthesize =  "(" + formula.substr(i , end - i + 1) + ")" ; 
                    formula.replace( i , end - i + 1 , parenthesize) ; 
                    add_bracket_not_operator();
                    return; 
                }
            }
        }

        void add_bracket_and_operator(){
            int n = formula.size() ; 

            for(int i = 0;i<n;i++){
                if(formula[i] == '&'){
                    int prev_start = search_for_prev_bracket( i - 1); 
                    int prev_end = i - 1 ; 
                    int next_start = i + 1 ; 
                    int next_end = search_for_next_bracket(i + 1 );  
                    if(prev_start == 0 or formula[prev_start - 1] != '(' ) {
                        string parenthesize =  "(" + formula.substr( prev_start , next_end - prev_start + 1) + ")" ; 
                        formula.replace( prev_start , next_end - prev_start + 1  , parenthesize) ; 
                        add_bracket_and_operator();
                        return;
                    }
                }
            }
        }


        void add_bracket_or_operator(){
            int n = formula.size() ; 

            for(int i = 0;i<n;i++){
                if(formula[i] == '|'){
                    int prev_start = search_for_prev_bracket( i - 1); 
                    int prev_end = i - 1 ; 
                    int next_start = i + 1 ; 
                    int next_end = search_for_next_bracket( i + 1 );  
                    if(prev_start == 0 or formula[prev_start - 1] != '(' ) {
                        string parenthesize =  "(" + formula.substr( prev_start , next_end - prev_start + 1) + ")" ; 
                        formula.replace( prev_start , next_end - prev_start + 1  , parenthesize) ; 
                        add_bracket_or_operator();
                        return;
                    }
                }
            }
        }


        void add_bracket_implication(){
            int n = formula.size() ; 

            for(int i = 0;i<n;i++){
                if(formula[i] == '>'){
                    int prev_start = search_for_prev_bracket( i - 1); 
                    int prev_end = i - 1 ; 
                    int next_start = i + 1 ; 
                    int next_end = search_for_next_bracket( i + 1 );  
                    if(prev_start == 0 or formula[prev_start - 1] != '(' ) {
                        string parenthesize =  "(" + formula.substr( prev_start , next_end - prev_start + 1) + ")" ; 
                        formula.replace( prev_start , next_end - prev_start + 1  , parenthesize) ; 
                        add_bracket_implication();
                        return;
                    }
                }
            }
        }


        void add_bracket_biconditional(){
            int n = formula.size() ; 

            for(int i = 0;i<n;i++){
                if(formula[i] == '='){
                    int prev_start = search_for_prev_bracket( i - 1); 
                    int prev_end = i - 1 ; 
                    int next_start = i + 1 ; 
                    int next_end = search_for_next_bracket( i + 1 );  
                    if(prev_start == 0 or formula[prev_start - 1] != '(' ) {
                        string parenthesize =  "(" + formula.substr( prev_start , next_end - prev_start + 1) + ")" ; 
                        formula.replace( prev_start , next_end - prev_start + 1  , parenthesize) ; 
                        add_bracket_biconditional();
                        return;
                    }
                }
            }
        }


        void add_brackets(  ) {
            remove_redundant_brackets();
            add_bracket_not_operator();
            add_bracket_and_operator();
            add_bracket_or_operator();
            add_bracket_implication();
            add_bracket_biconditional();
        }


        void remove_implication( ) {
            int n = formula.size() ; 
            for(int i = 0;i<n;i++) {
                if(formula[i] == '>'){
                    int prev_start = search_for_prev_bracket( i - 1); 
                    int prev_end = i - 1 ; 
                    int next_start = i + 1 ; 
                    int next_end = search_for_next_bracket(i + 1 ); 
                    formula[i] = '|' ; 
                    formula += '#' ; 
                    formula += '#' ; 
                    formula += '#' ; 
                    n = formula.size() - 1 ; 
                    for(int j = n ; j > i + 2  ; j-- ) formula[j] = formula[j-3] ; 
                    for(int j = i + 1 ; j > prev_start ; j--) formula[j] = formula[j-2] ; 
                    formula[prev_start ] = '(' ; 
                    formula[prev_start + 1] = '!' ; 
                    formula[i + 2 ] = ')' ; 
                    remove_implication()  ; 
                    return;
                }
            }

        }


        void remove_biconditional( ) {
            int n = formula.size() ; 
            for(int i = 0;i<n;i++){
                if(formula[i] == '='){
                    int prev_start = search_for_prev_bracket( i -1 ) ; 
                    int prev_end = i - 1 ; 
                    int next_start = i + 1 ; 
                    int next_end = search_for_next_bracket( i + 1 ) ; 

                    string first = formula.substr( prev_start , prev_end - prev_start + 1 ) ; 
                    string second = formula.substr( next_start , next_end - next_start + 1 ) ; 

                    string biconditional_to_implication = "(" + first + ">" + second + ")" + "&" + "(" + second + ">" + first + ")";

                    formula.replace( prev_start , next_end - prev_start + 1 , biconditional_to_implication ) ; 
                    
                    remove_biconditional() ; 
                    return;
                }
            }
        }


        void apply_negation(int i ) {
            int start = i + 1 ; 
            int end = search_for_next_bracket( i + 1 ) ; 
            if(start == end ) return;

            int prev_start = i + 1 ;
            int prev_end = search_for_next_bracket( i + 1) ; 
            int next_start = search_for_prev_bracket(end - 1) ; 
            int next_end = end - 1 ; 

            if(formula[next_start - 1] == '&'){
                formula[next_start-1] = '|' ; 
            
                swap(formula[i] , formula[prev_start] ) ; 

                int n = formula.size() ; 
                formula += '#' ; 
                for(int j = n;j > next_start ; j--) formula[j] = formula[j-1] ; 
                formula[next_start] = '!' ; 
                add_bracket_not_operator();
                apply_negation( prev_start) ; 
                apply_negation( next_start ) ; 

            }
            else if(formula[next_start - 1] == '|'){
                formula[next_start - 1] = '&' ; 

                swap(formula[i] , formula[prev_start]) ; 
                int n = formula.size() ; 
                formula += '#' ; 
                for(int j = n;j > next_start ; j--) formula[j] = formula[j-1] ; 
                formula[next_start] = '!' ; 
                add_bracket_not_operator();
                apply_negation( prev_start) ; 
                apply_negation( next_start ) ; 
            } 
            else if(start + 1 < formula.size() and formula[start + 1] == '!'){
                formula.erase(end , 1 ) ;
                formula.erase( start + 1 , 1  ) ; 
                formula.erase(start  , 1 ) ; 
                formula.erase(start-1 , 1 ) ;  
            }
        }


        void move_negation_inward( ){
            int n =formula.size() ; 
            for(int i = 0;i<n;i++){
                
                if(formula[i] == '!' and formula[i+1] == '('){
                    apply_negation( i ) ; 
                    move_negation_inward() ; 
                    return;
                }
            }
        }


        void remove_redundant_brackets( ) {
            int n = formula.size() ; 
            for(int i = 0;i<n;i++){
                if(formula[i] == '!' ) {
                    int start = i - 1 ; 
                    int end = search_for_next_bracket( i - 1 ) ; 
                    if(start - 1 >= 0 and formula[start -1 ] == '(' and end + 1 < n and formula[end + 1 ] == ')'){
                        formula.erase(end + 1 , 1 ) ; 
                        formula.erase(start -1 , 1 ) ; 
                        remove_redundant_brackets() ; 
                        return;
                    }
                }else if(formula[i] == '&' or formula[i] == '|' or formula[i] == '>' or formula[i] == '='){
                    int start = search_for_prev_bracket( i - 1 ) ; 
                    int end = search_for_next_bracket( i + 1 )  ; 
                    if(start - 2 >= 0 and formula[start -2 ] == '(' and end + 2 < n and formula[end + 2 ] == ')'){
                        formula.erase(end + 2 , 1 ) ; 
                        formula.erase(start -2 , 1 ) ; 
                        remove_redundant_brackets() ; 
                        return;
                    }
                }else{
                    int start = i - 1 ;
                    int end = i + 1 ; 
                    if(start >=0 and end < n and formula[start] == '(' and formula[end] == ')') {
                        formula.erase(end , 1 ) ; 
                        formula.erase(start , 1 ) ; 
                        remove_redundant_brackets();
                        return;
                    }
                }
            }
        }


        void distribute_or_over_and(){

            int n = formula.size() ;
            
            for(int i = 0 ;i<n;i++){
                if(formula[i] == '&'){
                    int prev_start = search_for_prev_bracket( i - 1 ) ; 
                    int prev_end = i - 1 ; 
                    int next_start = i + 1 ; 
                    int next_end = search_for_next_bracket( i + 1 ) ; 

                    if(prev_start - 2 >= 0 and formula[prev_start -2 ] == '|'){
                        int left_start = search_for_prev_bracket( prev_start - 3 ) ; 
                        int left_end = prev_start - 3; 

                        string left_term = formula.substr(left_start , left_end - left_start + 1 ) ; 

                        string rep = "(" + left_term + "|" + formula.substr(prev_start , prev_end - prev_start + 1 ) + ")&(" + left_term + "|" + formula.substr(next_start , next_end - next_start + 1 ) + ")" ; 

                        formula.replace(left_start , next_end - left_start + 1 + 1 , rep );
                        remove_redundant_brackets();
                        distribute_or_over_and();
                        return;
                    }
                    else if(next_end + 2  < n   and formula[next_end + 2] == '|'){
                        int right_start = next_end + 3 ;    
                        int right_end = search_for_next_bracket( right_start);

                        string right_term = formula.substr(right_start , right_end - right_start + 1 ) ; 

                        string rep = "(" + formula.substr(prev_start , prev_end - prev_start + 1 )+ "|" +  right_term 
                                + ")&(" + formula.substr(next_start , next_end - next_start + 1 ) + "|" + right_term + ")" ; 

                        formula.replace(prev_start - 1, right_end  - prev_start + 2, rep );
                        remove_redundant_brackets();
                        distribute_or_over_and() ; 
                        return;
                    }  
                }

            }
        }


        void get_each_clause( int start , int end , vector<string> &v) {

            int prev_start = start + 1 ; 
            int prev_end = search_for_next_bracket( prev_start);
            int next_start = search_for_prev_bracket( end - 1 ) ; 
            int next_end = end - 1 ; 
            if(formula[next_start - 1] != '&'){
                v.push_back(formula.substr(start , end - start + 1 )) ; 
                return;
            }

            get_each_clause( prev_start , prev_end, v  ) ; 
            get_each_clause( next_start , next_end , v ) ; 

        }

        
        void get_clause(vector<string> &v){
            get_each_clause(0, formula.size() - 1 , v ) ; 
        }


        string get_term_of_clause(string &clause ){
            string ans = "";
            int n = clause.size();
            for(int i = 0;i<n;i++){
                if(clause[i] == '|'){
                    if(i-3 >= 0 and clause[i-3] == '!'){
                        // cout<<clause.substr(i-4 , 4 )<<endl ; 
                        ans += clause.substr(i-4 , 4 ) ; 
                        ans += "|" ; 
                    }
                    if(i + 2 < n and clause[i+2] == '!'){
                        // cout<<clause.substr(i + 1 , 4 ) << endl; 
                        ans += clause.substr( i+1 , 4 ) ; 
                        ans += "|" ; 
                    }
                    if(clause[i-1] != ')' ) {
                        // cout<<clause[i-1]<<endl;
                        ans = ans + clause[i-1] + "|";
                    }
                    if(clause[i+1] != '('){
                        // cout<<clause[i+1]<<endl;
                        ans = ans + clause[i+1] + "|";
                    }
                }
            }
            if(ans.size() == 0 and clause.size() > 0 ) ans = clause + "|";
            ans.pop_back();
            return ans;
        }


        void convert_each_term(vector<string> &clauses){
            for(int i = 0;i<clauses.size();i++){
                // cout<<clauses[i]<<endl;
                clauses[i] = get_term_of_clause(clauses[i]) ; 
            }
        }


    public:
        vector<string> clauses;

        CNF(string &formula){
            this->formula = formula ; 
        }

        string convert_to_cnf(){
            // remvoving redundant brackets int the input string if any 
            remove_redundant_brackets();
            // if brackets are not in the input string then adding brackets
            add_brackets();
            // in case any extra bracket is there after adding brackets removing it
            remove_redundant_brackets();
            // removing biconditional (p = q --> (p>q)&(q>p))
            remove_biconditional();
            // removing implication ( p>q ---> (!p|q))
            remove_implication();
            // removing redundant brackets if there are any after doing above operations
            remove_redundant_brackets();
            // moving negation inwards by applying demorgan's law !(p|q) -- (!p&!q) , !(p&q) -- (!p|!q)
            move_negation_inward();
            // removing redunction brackets if there are any after moving negation inwards 
            remove_redundant_brackets();
            // converting to clauses of conjunction ( e.g. -- (a|b|c)&(!d|a)&(a|!h))
            distribute_or_over_and();
            // removing redundant brackets
            remove_redundant_brackets(); 
            // getting all the clauses in a vector for strings  
            get_clause(clauses); 
            // simplifying each clause term ( (a|(b|c)) --->> a|b|c) 
            convert_each_term(clauses); 
            return formula; 
        }
};


class Node{
    private: 
        vector<string> kb; 
        vector<Node *> children;
        bool goal = false; 
        
    public: 
        string operation ; 
        Node(vector<string> kb ) {
            this->kb = kb; 
        }
        void insert(Node * next ) {
            this->children.push_back(next);
        }
        void set_goal(){
            this->goal = true;
        }
        bool is_goal_state(){
            return this->goal; 
        }
        vector<string> get_kb(){
            return this->kb;
        }
        vector<Node*> get_children(){
            return this->children;
        }

};




vector<string> convert_to_kb(vector<string> &v ){
    vector<string> kb ; 
    for(auto i : v ){
        CNF cnf(i);
        string i_converted = cnf.convert_to_cnf();
        vector<string> temp_kb = cnf.clauses;
        for(auto j : temp_kb ) kb.push_back(j); 
    } 
    return kb; 
}


vector<string> add_negation_of_query(vector<string>&kb , string &query){    
    string negation_query = "!(" + query + ")" ; 
    CNF cnf(negation_query);
    negation_query = cnf.convert_to_cnf();
    vector<string> negation_kb = cnf.clauses;
    for(auto i : negation_kb) kb.push_back(i);
    return kb; 
}


vector<string> get_split(string &clause){
    vector<string> clause_terms ; 
    int i = 0; 
    string temp = "";
    int n = clause.size();
    while(i < n ){
        if(clause[i] == '|'){
            clause_terms.push_back(temp);
            temp = "";
        }
        else temp += clause[i];
        i++;
    }
    clause_terms.push_back(temp);
    return clause_terms;
}


bool can_resolve(vector<string> &clause_term1 , vector<string> &clause_term2){
    for(auto i : clause_term1){ 
        string h = "!" + i ; 
        CNF cnf( h );
        string not_i = cnf.convert_to_cnf();
        
        for(auto j : clause_term2) if( j == not_i ) return true; 

    }
    return false; 
}


bool negation_present(vector<string> &clause , string p ){
    string not_p = "!" + p ;
    CNF cnf(not_p);
    not_p = cnf.convert_to_cnf(); 
    for(auto i : clause) if(i == not_p ) return true; 
    return false; 
}

string get_resolvant( vector<string> &clause1 , vector<string> &clause2 , string resolver ){
    string resolvant = "";
    set<string> added; 
    for(auto i : clause1 ) {
        if(i != resolver and added.find("" + i) == added.end()){
            resolvant = resolvant + i + "|";
            added.insert("" + i ) ; 
        }
    }
    string not_resolver = "!" + resolver ; 
    CNF cnf(not_resolver);
    not_resolver = cnf.convert_to_cnf(); 

    for(auto i : clause2 ) {
        if(i!= not_resolver and added.find("" + i) == added.end()){
            resolvant = resolvant + i + "|";
            added.insert("" + i ) ; 
        }
    }

    if(resolvant.empty()) return resolvant;
    resolvant.pop_back();
    return resolvant;

}


bool resolution_refutation_bfs(Node * root , int &nodes_explored ){
    vector<string> kb = root->get_kb();
    int n = kb.size();
    bool entail = false;
    set<string> visited ; 
    queue<pair<Node* , set<string> > > q ; 
    q.push({ root , visited  });

    while(!q.empty()){
        Node * ptr = q.front().first;
         visited = q.front().second;
        q.pop();
        nodes_explored++;
        kb = ptr->get_kb();
        n = kb.size();
        for(int i=0;i<n;i++){ 

            vector<string> clause_term1 = get_split(kb[i]) ; 

            for(int j = i + 1 ; j<n;j++){

                if(visited.find(kb[i]) != visited.end() or visited.find(kb[j])!= visited.end()) continue;
                vector<string> clause_term2 = get_split(kb[j]);
                for(auto x : clause_term1){

                    if(negation_present(clause_term2 , x )) {
                        visited.insert(kb[i]);
                        visited.insert(kb[j]);
                        string resolvant = get_resolvant(clause_term1 , clause_term2 , x  ) ; 
                        kb.push_back(resolvant ) ; 
                        Node * next = new Node(kb);
                        if(!resolvant.empty()) next->operation = "Resolving " + kb[i] +" and " + kb[j] + " and addding " + resolvant + " to knowledge base" ; 
                        else next->operation = "Have contradiction in knowledge base if we resolve " + kb[i] + " and " + kb[j] ; 
                        ptr->insert(next); 
                        if(resolvant.empty()) {
                            next->set_goal();
                            return true;
                        }
                        q.push( {next , visited  });
                        visited.erase(kb[i]);
                        visited.erase(kb[j]); 
                        kb.pop_back();
                    }
                }
            }
        }
    }
    return false;
}


int heuristics(vector<string> &kb){
    if(kb.empty()) return 0 ; 
    auto i = kb.back();
    int count = 0 ;  
    if(i.empty()) return 0; 
    for(auto j : i ){
        if( j == '|'){
            count++;
        }
    }
    count++;
    return count;
}

bool resolution_refutation_with_heuristics( Node * root , int &nodes_explored){

    priority_queue<pair<int, pair<Node*, set<string>>> , vector<pair<int , pair<Node*, set<string>>>>, greater<pair<int , pair<Node*, set<string>>>> > pq; 
    vector<string> kb = root->get_kb();
    set<string> visited ;
    pq.push({heuristics(kb)  , {root , visited } }) ; 
    
    while(!pq.empty()){
        Node * ptr = pq.top().second.first ; 
        visited = pq.top().second.second; 
        kb = ptr->get_kb();
        int n = kb.size();
        pq.pop();
        nodes_explored++;
        cout<<nodes_explored<<endl;
        for(int i=0;i<n;i++){ 

            vector<string> clause_term1 = get_split(kb[i]) ; 

            for(int j = i + 1 ; j<n;j++){

                if(visited.find(kb[i]) != visited.end() or visited.find(kb[j])!= visited.end()) continue;

                vector<string> clause_term2 = get_split(kb[j]);
                
                for(auto x : clause_term1){
                    if(negation_present(clause_term2 , x )) {
                        visited.insert(kb[i]);
                        visited.insert(kb[j]);
                        string resolvant = get_resolvant(clause_term1 , clause_term2 , x  ) ; 
                        
                        kb.push_back(resolvant ) ; 

                        Node * next = new Node(kb);
                        if(!resolvant.empty()) next->operation = "Resolving " + kb[i] +" and " + kb[j] + " and addding " + resolvant + " to knowledge base" ; 
                        else next->operation = "Have contradiction in knowledge base if we resolve " + kb[i] + " and " + kb[j] ; 
                        if(resolvant.empty()) {
                            next->set_goal();
                            ptr->insert(next);
                            return true;
                        }
                        ptr->insert(next);
                        
                        int heur = heuristics(kb);
                        pq.push({heur , {next , visited } }) ;
                        visited.erase(kb[i]);
                        visited.erase(kb[j]); 

                        kb.pop_back();
                    }
                }
            }
        }
    }
    return false;
}

bool get_path(Node * root , vector<pair<string , vector<string>>> &path ) {
    if(root->is_goal_state()) {
        path.push_back({root->operation , root->get_kb() }) ;
        return true; 
    }
    path.push_back({root->operation , root->get_kb() }) ;

    vector<Node*> children = root->get_children();
    
    for(auto j : children){
        bool temp = get_path( j  , path ) ; 
        if(temp) return true; 
    }
    path.pop_back();
    return false;
}


void print_steps(Node * root ){
    vector<pair<string , vector<string> > > path ; 
    get_path(root, path ); 
    for(auto i : path ) {
        cout<<i.first<<endl;
        for(auto j : i.second ) {
            cout<<j<<endl;
        }
        cout<<endl<<endl;
    }
}


int count_steps(Node * root ){
    int count = 0 ; 
    queue<pair<int,Node* >> q ; 
    q.push({count , root }) ; 
    while(!q.empty()){
        count = q.front().first;
        Node * ptr = q.front().second; 
        q.pop();
        if(ptr->is_goal_state()){
            return count;
        }
        vector<Node*> children = ptr->get_children();
        for(auto j : children) q.push( {count + 1 , j }) ; 
    }
    return count ; 
}


int main(){
    
    int n,m;
    cin>>n>>m;
    vector<string> v(n); 
    for(int i = 0;i<n;i++){
        cin>>v[i];
    }
    
    string query ;
    cin>>query;



    vector<string> kb = convert_to_kb(v);
    kb = add_negation_of_query(kb , query);

    cout<<"Knowledge base after adding negation of query to it and converting to CNF : "<<endl;
    for(auto i : kb ) cout<<i<<endl;
    cout<<endl;


    int node_uninformed = 0 ;
    Node * root_uninfomred = new Node(kb);
    cout<<"Executing uninformed search (Breadth First Search) .... " <<endl;
    clock_t start1 = clock();
    if(resolution_refutation_bfs(root_uninfomred , node_uninformed) ) {
        cout<<"Query entails the knowledge base." <<endl;
        cout<<"Number of Nodes Explored : " << node_uninformed<<endl;
        cout<<"Number of Steps required : " << count_steps(root_uninfomred) << endl; 
        if(m == 1 ) print_steps(root_uninfomred);
    }
    else{
        cout<<"Query does not entails the knowledge base." <<endl;
    }
    clock_t end1 = clock();
    double time_taken1 =1000.0 * (end1 - start1) / CLOCKS_PER_SEC ;
    cout<<"Time taken by uninformed search is " << time_taken1  <<" milliseconds " <<endl;

    cout<<endl;
    cout<<endl;

    int node_informed = 0 ; 
    Node * root_infomred = new Node(kb);
    cout<<"Executing Greedy Search .... " <<endl;
    clock_t start2 = clock();                                                
    if(resolution_refutation_with_heuristics(root_infomred , node_informed ) ) {
        cout<<"Query entails the knowledge base." <<endl;
        cout<<"Number of Nodes Explored : " << node_informed<<endl;
        cout<<"Number of Steps required : " << count_steps(root_infomred) << endl; 
        if(m == 1 ) print_steps(root_infomred);
    } else{
        cout<<"Query does not entails the knowledge base." <<endl;
    }
    clock_t end2 = clock();
    double time_taken2 = 1000.0 * (end2 - start2 ) / CLOCKS_PER_SEC ; 
    cout<<"Time taken by greedy search is " << time_taken2 << " milliseconds " <<endl;
}   