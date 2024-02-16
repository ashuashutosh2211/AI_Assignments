#include <bits/stdc++.h> 
using namespace std;

bool check_sorted( vector<double> & v , int n ) {
    for(int i= 1;i<n;i++) {
        if(v[i-1] > v[i]) return false; 
    } 
    return true; 
}

void print(vector<double> & v ) {
    for(auto i : v ) cout<<i<<" " ; 
    cout<<endl; 
}
bool print_path = true;
int bfs( vector<double> & v , int n ) {
    queue<vector<double>> q; 
    q.push(v) ; 
    set<vector<double>> vis ; 
    vis.insert(v);
    int steps = 0 ; 
    while(!q.empty()){ 
        vector<double> x = q.front() ; q.pop() ;   
        if(print_path) print(x);
        if(check_sorted(x , n )) {
            break; 
        } 
        steps++;
        for(int i =0;i<n-1;i++){
            swap(x[i] , x[i+1] )  ;  

            if(vis.find(x) == vis.end()){ vis.insert(x) ;q.push(x) ; }
        
            swap(x[i] , x[i+1]) ; 
        }
    } 
    // cout<<steps<<endl; 
    return steps;
}

int dfs( vector<double> & v , int n ) {
    stack<vector<double>> s; 
    s.push(v) ; 
    set<vector<double>> vis ; 
    vis.insert(v); 
    int steps = 0 ; 
    while(!s.empty()){ 
        
        vector<double> x = s.top() ; s.pop() ;   
        if(print_path) print(x);
        if(check_sorted(x , n )) {
            break; 
        } 
        steps++;
        for(int i =0;i<n-1;i++){
            swap(x[i] , x[i+1] )  ;  
            if(vis.find(x) == vis.end()){ vis.insert(x) ;s.push(x) ; }
            swap(x[i] , x[i+1]) ; 
        }
    } 
    // cout<<steps<<endl; 
    return steps;
}

bool dfs_depth( vector<double> & v , int n , int max_depth , int & steps) {
    stack<pair<vector<double> , int> > s ; 
    s.push({v , max_depth}) ; 
    set<vector<double>> vis ; 
    vis.insert(v); 
    while(!s.empty()){  
        vector<double> x = s.top().first ;  
        int depth = s.top().second;
        s.pop() ;   
        if(print_path) print(x);
        if(check_sorted(x , n )){
            return true;
        }
        
        steps++;
        if( depth == 0 ) {
            continue;
        } 
        for(int i = 0;i<n-1;i++){
            swap(x[i] , x[i+1]) ; 
            if(vis.find(x) == vis.end()){
                vis.insert(x) ; 
                s.push({x , depth - 1 }) ; 
            } 
            swap(x[i] , x[i+1]) ; 
        }
    } 
    return false;
} 

int iterative_deepening( vector<double> & v , int n ) { 
    int count = 0 ; 
    for(int i = 1;i<INT_MAX;i++){
        bool found = dfs_depth(v , n , i , count ) ; 
        if(found ) break;
    }
    // cout<<count<<endl; 
    return count;
}

int ucs( vector<double> & v , int n ) {
    priority_queue<pair<int,vector<double>> , vector<pair<int,vector<double>>>  ,greater<pair<int,vector<double>>> > pq; 
    pq.push({0 , v }) ; 
    set<vector<double>> vis ; 
    // vis.insert(v);
    int steps = 0 ; 
    while(!pq.empty()){ 
        int cost = pq.top().first; 
        vector<double> x = pq.top().second ; pq.pop() ;    
        if(vis.find(x ) != vis.end()) continue;
        if(print_path) print(x);
        vis.insert(x) ;
        if(check_sorted(x , n )) {
            break; 
        } 
        steps++;
        for(int i =0;i<n-1;i++){
            swap(x[i] , x[i+1] )  ;  
            if(vis.find(x) == vis.end()){ pq.push({cost + 1 , x}) ; }
            swap(x[i] , x[i+1]) ; 
        }
    } 
    // cout<<steps<<endl; 
    return steps;
}

int heuristic_function1(vector<double> & v , int n ) {
    int count = 0 ;
    for(int i = 0;i<n;i++){
        for(int j = i + 1;j<n;j++){
            if(v[j] < v[i]) count++;
        }
    } 
    return count; 
}

int greedy( vector<double> & v , int n ) {
    priority_queue<pair<int,vector<double>> , vector<pair<int,vector<double>>>  ,greater<pair<int,vector<double>>> > pq; 
    int heuristic = heuristic_function1( v , n  )  ; 
    pq.push({ heuristic, v }) ; 
    set<vector<double>> vis ; 
    vis.insert(v);
    int steps = 0 ; 
    while(!pq.empty()){ 
        int cost = pq.top().first; 
        vector<double> x = pq.top().second ; pq.pop() ;   
        if(print_path) print(x);
        vis.insert(x) ;
        if(check_sorted(x , n )) {
            break; 
        } 
        steps++;
        for(int i =0;i<n-1;i++){
            swap(x[i] , x[i+1] )  ;   
            int new_cost = heuristic_function1(x, n  );
            if(vis.find(x) == vis.end()){ pq.push({ new_cost, x}) ; }
            swap(x[i] , x[i+1]) ; 
        }
    } 
    // cout<<steps<<endl; 
    return steps;
}

int A_star( vector<double> & v , int n) {
    priority_queue<pair<int , pair<vector<double> , int >> , vector<pair<int , pair<vector<double> , int>>>  ,greater<pair<int , pair<vector<double> , int>>> > pq; 
 
    int heuristic = heuristic_function1( v , n  )  ; 
    int cost =  0 ; 
    pq.push({ heuristic + cost  , {v , cost  }}) ; 
    set<vector<double>> vis ; 
    vis.insert(v);
    int steps = 0 ; 
    while(!pq.empty()){ 
        int cost = pq.top().second.second; 
        vector<double> x = pq.top().second.first ; pq.pop() ;   
        if(print_path) print(x);
        vis.insert(x) ;
        if(check_sorted(x , n )) {
            break; 
        } 
        steps++;
        for(int i =0;i<n-1;i++){
            swap(x[i] , x[i+1] )  ;   
            int new_cost = heuristic_function1(x, n  ) + cost + 1 ;
            if(vis.find(x) == vis.end()){ pq.push({ new_cost , { x , cost + 1 }  }) ; }
            swap(x[i] , x[i+1]) ; 
        }
    } 
    // cout<<steps<<endl; 
    return steps;
}  

int heuristic_function2( vector<double> & v , int n ) { 
    int count = 0 ; 
    for(int i = 0;i<n - 1;i++){
        if(v[i] > v[i + 1 ] ) count++;
    } 
    return count ; 
}

int hill_climbing( vector<double> arr , int n  ) {
    vector<double> v = arr ; 
    int current_heuristic = heuristic_function2(v , n ) ; 

    int steps = 0;
    while(true){
        // print(v);
        if(check_sorted(v , n )) {
            break;
        }
        bool less = false;
        vector<double> x = v ;
        for(int i = 0;i<n-1;i++){
            swap(x[i] , x[i+1]) ; 
            int heuristic = heuristic_function2( x , n ) ; 
            if(heuristic < current_heuristic){
                v = x ; 
                current_heuristic = heuristic; 
                less = true;
            }
            swap(x[i] , x[i+1]) ; 
        } 
        if(less == false ) {
            break;
        }
        steps++;
    }
    if(print_path ) (v); // final _state 
    return steps;
}

int main() {
    int n;
    cin>>n;
    vector<double> v(n) ;  
    for(int i = 0;i<n;i++) cin>>v[i] ; 
    // cout<<bfs(v , n ) <<endl; 
    // cout<<dfs(v , n ) <<endl; 
    // cout<<iterative_deepening(v , n ) <<endl; 
    // cout<<ucs(v , n ) <<endl; 
    // cout<<greedy(v , n  ) <<endl; 
    // cout<<A_star(v , n ) <<endl;
    // cout<<hill_climbing(v, n ) <<endl; 
    // return 0;
    double bfs_av = 0 ; 
    double dfs_av = 0 ; 
    double iter_deepen = 0 ; 
    double ucs_av = 0 ; 
    double greedy_av = 0 ; 
    double a_star_av = 0 ; 
    double hill_climb = 0 ; 
    for(int i = 0;i<20;i++ ) {
        print_path = false;
        std::random_device rd;
        std::mt19937 gen(rd());
        double min_value = -10.0;
        double max_value = 10.0; 
        std::uniform_real_distribution<double> distribution(min_value, max_value);
        for(int i =0;i<n;i++) {
            v[i] = distribution(gen);
        }
        bfs_av += bfs(v , n ) ; 
        dfs_av += dfs(v , n  ) ; 
        iter_deepen += iterative_deepening(v , n ) ; 
        ucs_av += ucs(v , n ) ; 
        greedy_av += greedy( v , n ) ; 
        a_star_av += A_star( v , n ) ;
        hill_climb += hill_climbing( v , n )  ;  
        // cout<<i<<endl;
    } 
    bfs_av /= 20 ; 
    dfs_av /= 20 ; 
    iter_deepen /= 20; 
    ucs_av /= 20; 
    greedy_av /= 20; 
    a_star_av /= 20; 
    hill_climb /= 20; 
    cout<<"Average number of steps for breadth first search " << bfs_av <<endl; 
    cout<<"Average number of steps for depth first search " << dfs_av <<endl; 
    cout<<"Average number of steps for iterative_deepening " << iter_deepen <<endl; 
    cout<<"Average number of steps for uniform cost search " << ucs_av <<endl; 
    cout<<"Average number of steps for greedy search " << greedy_av <<endl; 
    cout<<"Average number of steps for A star search " << a_star_av <<endl; 
    cout<<"Average number of steps for hill climbing search " << hill_climb <<endl; 
}