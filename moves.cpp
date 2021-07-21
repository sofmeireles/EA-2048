#include <iostream> 
#include <vector> 
#include <chrono> 
#include <queue> 
#include <math.h> 
using namespace std;
using namespace std::chrono; 

int moves;
int best;
int dim;
int conta_moves;

void print_arr(vector<vector<int>> &v){
    for (int i = 0; i <dim; i++) { 
        for (int j = 0; j <dim; j++) 
            cout << v[i][j] << " "; 
        cout << endl; 
    }
}

vector<vector<int>> move_down_handler(vector<vector<int>> v){
    int saved_line=0;
    int saved=-1;
    int zeros=0;
    int aux;

    for(int col=0;col<dim;col++){
        for(int line=dim-1; line>=0;line--){
            if(saved!=v[line][col] && v[line][col]!=0){
                saved=v[line][col];
                saved_line=line;
            }
            else if(saved==v[line][col]){
                v[saved_line][col]=2*saved;
                v[line][col]=0;
                saved=-1;
            }
        }
        for(int line=dim-1;line>=0;line--){        
            if(v[line][col]!=0 && zeros!=0){
                aux=v[line][col];
                v[line+zeros][col]=aux;
                v[line][col]=0;
            }
            else if(v[line][col]==0){
                zeros++;
            }
        }
        saved_line=0;
        saved=-1;
        zeros=0;
    }
    return v;
}

vector<vector<int>> move_up_handler(vector<vector<int>> v){
    int saved_line=0;
    int saved=-1;
    int zeros=0;
    int aux;
    
    for(int col=0;col<dim;col++){
        for(int line=0; line<dim;line++){
            if(saved!=v[line][col] && v[line][col]!=0){
                saved=v[line][col];
                saved_line=line;
            }
            else if(saved==v[line][col]){
                v[saved_line][col]=2*saved;
                v[line][col]=0;
                saved=-1;
            }
        }
        for(int line=0;line<dim;line++){            
            if(v[line][col]!=0 && zeros!=0){
                aux=v[line][col];
                v[line-zeros][col]=aux;
                v[line][col]=0;
            }
            else if(v[line][col]==0){
                zeros++;
            }
        }
        saved_line=0;
        saved=-1;
        zeros=0;
    }
    return v;
}

vector<vector<int>> move_right_handler(vector<vector<int>> v){
    int saved_col=0;
    int saved=-1;
    int zeros=0;

    for(int line=0;line<dim;line++){
        for(int col=dim-1; col>=0;col--){
            if(saved!=v[line][col] && v[line][col]!=0){
                saved=v[line][col];
                saved_col=col;
            }
            else if(saved==v[line][col]){
                v[line][saved_col]=2*saved;
                v[line][col]=0;
                saved=-1;
                zeros++;
            }
            else if(v[line][col]==0){
                zeros++;
            } 
        }
        for(int col = 0; col<dim;col++){
            if(v[line][col]==0){
                v[line].erase(v[line].begin() + col);
                v[line].insert(v[line].begin(), 0);
            }
        }
        saved_col=0;
        saved=-1;
        zeros=0;
    }
    return v;
}


vector<vector<int>> move_left_handler(vector<vector<int>> v){
    int saved_col=dim-1;
    int saved=-1;
    int zeros=0;


    for(int line=0;line<dim;line++){
        for(int col=0; col<dim;col++){
            if(saved!=v[line][col] && v[line][col]!=0){
                saved=v[line][col];
                saved_col=col;
            }
            else if(saved==v[line][col]){
                v[line][saved_col]=2*saved;
                v[line][col]=0;
                saved=-1;
            }
        }

        for(int col=0;col<dim;col++){
            if(v[line][col]!=0 && zeros!=0){
                v[line][col-zeros]=v[line][col];
                v[line][col]=0;
            }
            else if(v[line][col]==0){
                zeros++;
            }
        }
        saved_col=0;
        saved=-1;
        zeros=0;
    }
    return v;
}

bool check_possible(vector<vector<int>> &v){
    if(dim==3){
        if(v[0][0]==v[0][2] && v[0][1]==v[0][0]*2){
            return false;
        }
        else if(v[0][0]==v[2][0] && v[1][0]==v[0][0]*2){
            return false;
        }
    }
    return true;
}

bool check_end(vector<vector<int>> &v){
    int n_zeros=0;
    int total_zeros= dim*dim-1;

    for(int line=0;line<dim;line++){
        for(int col=0;col<dim;col++){
            if(v[line][col]==0){
                n_zeros++;
            }
        }
    }
    if(n_zeros==total_zeros){
        //cout << "true\n";
        return true;
    }
    else{
        //out << "false\n";
        return false;
    }
}

bool check_equal(vector<vector<int>> &v, vector<vector<int>> &copy){

    int c = 0;

    for (int i = 0; i < dim; i++){
        if(v[i] == copy[i]){
            c++;
        }
    }
    
    if ( c == dim){
        return true;
    }
    else
        return false;

}

vector<vector<int>> copy_array(vector<vector<int>> &v){
   
    vector<vector<int>> v2;

    for (int i = 0; i < dim; i++){
        v2.push_back(v[i]);
    }
    return v2;
}


void play(vector<vector<int>> v, int n_moves, vector<vector<int>> old1, vector<vector<int>> old2, vector<vector<int>> old3, vector<vector<int>> old4){

    vector<vector<int>> copy = v;
    vector<vector<int>> copy2 = copy;
    conta_moves++;

    
    //print_arr(v);
    //cout << "número de moves atual: " << n_moves << "\n";
    /*
    cout <<"v:\n";
    print_arr(v);
    cout <<"old1:\n";
    print_arr(old1);
    cout <<"old2:\n";
    print_arr(old2);*/

    if (check_end(v)==true || n_moves > moves){
        if(n_moves<best){
            best=n_moves;
            //cout << best << "- MELHOR\n";
        }
        //cout << "FIM\n\n";
        return;
    }

    //move right
    copy2=move_right_handler(copy);
    if (!check_equal(v, copy2) && !check_equal(copy2,old1) && !check_equal(copy2,old2) && !check_equal(copy2,old3) && !check_equal(copy2,old4) && !(n_moves+1==best)){
        old4=old3;
        old3=old2;
        old2=old1;
        old1=v;
        v = copy2;
        //cout << "Moved right\n\n";
        play(v,n_moves+1,old1,old2,old3,old4);
    }
    
    //move up
    copy2=move_up_handler(copy);
    
    if (!check_equal(v, copy2) && !check_equal(copy2,old1) && !check_equal(copy2,old2) && !check_equal(copy2,old3) && !check_equal(copy2,old4) && !(n_moves+1==best)){
        old4=old3;
        old3=old2;
        old2=old1;
        old1=v;
        v = copy2;
        //cout << "Moved up\n\n";
        play(v,n_moves+1,old1,old2,old3,old4);
    }

    //move left
    copy2=move_left_handler(copy);
    if (!check_equal(v, copy2) && !check_equal(copy2,old1) && !check_equal(copy2,old2) && !check_equal(copy2,old3) && !check_equal(copy2,old4) && !(n_moves+1==best)){
        //cout << "Moved left\n\n";
        old4=old3;
        old3=old2;
        old2=old1;
        old1=v;
        v = copy2;
        //cout << "Moved right\n\n";
        play(v,n_moves+1,old1,old2,old3,old4);
    }

     //move down
    copy2=move_down_handler(copy);
    if (!check_equal(v, copy2) && !check_equal(copy2,old1) && !check_equal(copy2,old2) && !check_equal(copy2,old3) && !check_equal(copy2,old4) && !(n_moves+1==best)){
        //cout << "Moved Down\n\n";
        old4=old3;
        old3=old2;
        old2=old1;
        old1=v;
        v = copy2;
        play(v,n_moves+1,old1,old2,old3,old4);
    }
   
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int maximo, n;
    int sum=0;
    conta_moves=0;
    best=1000000;
    vector<vector<int>> v,old1,old2,old3,old4;

    //auto start = high_resolution_clock::now();
    cin >> maximo;
    for( int i = 0; i < maximo; i++){
        cin >> dim >> moves;
        v = vector<vector<int>> (dim,vector<int> (dim, 0));
        old1=v;
        old2=v;
        old3=v;
        old4=v;
        for (int line = 0; line < dim ; line ++){
            for (int col = 0; col < dim ; col ++){
                cin >> n;
                sum+=n;
                v[line][col]=n;
            }
        }
        
        if((sum & (sum - 1)) == 0){
                //print_arr(v);
                //cout << "ola\n";
                //move_right_handler(v);
                //print_arr(v);
                play(v,0,old1,old2,old3,old4);
                if(best<= moves){
                    cout << best << "\n";
                    //cout << best << " n moves="<< conta_moves <<"\n";
                }
                else if(best>moves){
                    //cout << "best: " << best;
                    cout << "no solution\n";
                    //cout << "no solution  n moves="<< conta_moves <<"\n";
                }
        }
        else{
            cout << "no solution\n";
            //cout << "no solution  n moves="<< conta_moves <<"\n";
        }
        sum=0;
        best=1000000;
    }
    //}
    //auto stop = high_resolution_clock::now(); 
    //auto duration = duration_cast<microseconds>(stop - start); 
    //cout << "Time taken by function: "
    //<< duration.count()*0.001 << " ms" << endl; 
  
}