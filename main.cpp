#include <bits/stdc++.h>
using namespace std;
vector<char> GRID;
vector<vector<int>> ROWS;
vector<vector<int>> COLS;
const int NODES = 24;
int WHITE ,BLACK ,W_on_GRID ,B_on_GRID;
char player[2] = {'W','B'};
void generate_All(){
    for (int i = 0; i < NODES; ++i) {
        GRID.push_back('S');
    }
    ROWS = {{0,1,2},{3,4,5},{6,7,8},{9,10,11},{12,13,14},{15,16,17},{18,19,20},{21,22,23}};
    COLS = {{0,9,21},{3,10,18},{1,4,7},{6,11,15},{8,12,17},{5,13,20},{2,14,23},{16,19,22}};
    BLACK = WHITE = 9;
    B_on_GRID = W_on_GRID = 0;
}
void print_GRID(){
    cout<<GRID[0]<<"------------"<<GRID[1]<<"------------"<<GRID[2]<<endl;
    cout<<"|            |            |"<<endl;
    cout<<"|    "<<GRID[3]<<"-------"<<GRID[4]<<"-------"<<GRID[5]<<"    |"<<endl;
    cout<<"|    |       |       |    |"<<endl;
    cout<<"|    |   "<<GRID[6]<<"---"<<GRID[7]<<"---"<<GRID[8]<<"   |    |"<<endl;
    cout<<"|    |   |       |   |    |"<<endl;
    cout<<GRID[9]<<" __ "<<GRID[10]<<" __"<<GRID[11]<<"       "<<GRID[12]<<" __"<<GRID[13]<<" __ "<<GRID[14]<<endl;
    cout<<"|    |   |       |   |    |"<<endl;
    cout<<"|    |   "<<GRID[15]<<"---"<<GRID[16]<<"---"<<GRID[17]<<"   |    |"<<endl;
    cout<<"|    |       |       |    |"<<endl;
    cout<<"|    "<<GRID[18]<<"-------"<<GRID[19]<<"-------"<<GRID[20]<<"    |"<<endl;
    cout<<"|            |            |"<<endl;
    cout<<GRID[21]<<"------------"<<GRID[22]<<"------------"<<GRID[23]<<endl;
}
int binary_search(int left,int right,vector<int> arr,int target){
    if(left <= right){
        int mid = left + ((right - left) / 2);
        if(arr[mid] == target){
            return mid;
        }
        if(arr[mid] > target){
            return binary_search(left,mid-1,arr,target);
        }
        if(arr[mid] < target){
            return binary_search(mid+1,right,arr,target);
        }
    }
    return -1;
}
int get_adjs_index(vector<vector<int>> vec, int index)
{
    int search_idx = INT_MIN;
    for(int i = 0; i < vec.size(); i++)
    {
        search_idx = binary_search(0,vec[i].size()-1,vec[i],index);
        if(search_idx >= 0)
        {
            return i;
        }
    }
    return -1;
}
bool check_valid_move2(int from, int to)
{
    int i = get_adjs_index(ROWS, from);
    int j = get_adjs_index(COLS, from);
    for(int f = 0; f < ROWS[i].size() - 1; f++)
    {
        if((ROWS[i][f] == from && ROWS[i][f+1] == to && GRID[to] == 'S') || (ROWS[i][f] == to && ROWS[i][f+1] == from && GRID[to] == 'S'))
            return true;
        if((COLS[j][f] == from && COLS[j][f+1] == to && GRID[to] == 'S') || (COLS[j][f] == to && COLS[j][f+1] == from && GRID[to] == 'S'))
            return true;
    }
    return false;
}
void move(int from , int to , char player){
    if(from == INT_MIN){
        GRID[to] = player;
    }
    else{
        GRID[to] = GRID[from];
        GRID[from] = 'S';
    }
}
bool check_input(int index)
{
    if(index < 0 || index > 23 || GRID[index] != 'S')
        return false;
    return true;
}
bool check_input(int from, int to, char player)
{
    if(GRID[from] != player || GRID[to] != 'S')
        return false;
    return true;
}
void take_input(int &idx){
    cout<<"Enter the index: "<<endl;
    cin>>idx;
    if(!check_input(idx))
        take_input(idx);
}
void take_input(int &from, int &to, char player){
    cout<<"Enter the index 1: "<<endl;
    cin>>from;
    cout<<"Enter the index 2: "<<endl;
    cin>>to;
    if(!check_input(from,to,player) || !check_valid_move2(from,to))
        take_input(from,to,player);
}
void take_remove_input(int &idx,char player){
    cout<<"Enter index you want to remove: "<<endl;
    cin>>idx;
    if(GRID[idx] == player || GRID[idx] == 'S'){
        take_remove_input(idx,player);
    }
}
void remove_color(int idx,int P){
    GRID[idx] = 'S';
    switch (P) {
        case 0:
            B_on_GRID --;
            break;
            case 1:
                W_on_GRID --;
                break;
    }
}
bool check_adjacent(int index, char player)
{
    int counter =0;
    int j = get_adjs_index(ROWS, index);
    for(int i = 0; i < ROWS[j].size(); i++)
    {
        if(GRID[ROWS[j][i]] == player)
            counter++;
    }
    if(counter == 3)
        return true;
    counter = 0;
    j = get_adjs_index(COLS, index);
    for(int i = 0; i < COLS[j].size(); i++)
    {
        if(GRID[COLS[j][i]] == player)
            counter++;
    }
    if(counter == 3)
        return true;
    return false;
}
bool check_valid_moves(char player)
{
    for(int i = 0; i < GRID.size(); i++)
    {
        if(GRID[i] == player)
        {
            int j = get_adjs_index(ROWS, i);
            int k = get_adjs_index(COLS, i);
            for(int f = 0; f < 3; f++)
            {
                if(check_valid_move2(i , ROWS[j][f]) || check_valid_move2(i , COLS[k][f]))
                {
                    cout << "true" << endl;
                    return true;
                }
            }
        }
    }
    return false;
}
bool check_win()
{
    if((W_on_GRID <= 2 && WHITE == 0) || (!check_valid_moves(player[0]) && W_on_GRID > 0))
        cout << "BLACK IS WINNER!!" << endl;
    else if((B_on_GRID <= 2 && BLACK == 0) || (!check_valid_moves(player[1]) && B_on_GRID > 0))
        cout << "WHITE IS WINNER!!" << endl;
    else
        return false;
    return true;
}
void play_game(){
    generate_All();
    int P = 1;
    while (true){
        print_GRID();
        P = 1 - P;
        cout<<"Player "<<player[P]<<" Turn :"<<endl;
        int from = INT_MIN, to;
        if((P == 0 && WHITE > 0) || (P == 1 && BLACK > 0)){
            take_input(to);
        }
        else{
            take_input(from,to,player[P]);
        }
        move(from,to,player[P]);
        if(P == 0 && WHITE > 0){
            WHITE --;
            W_on_GRID ++;
        } else if(P == 1 && BLACK > 0){
            BLACK --;
            B_on_GRID ++;
        }
        int rem_idx;
        if(check_adjacent(to,player[P])){
            take_remove_input(rem_idx,player[P]);
            remove_color(rem_idx,P);
        }
        if(check_win()){
            break;
        }
    }
}
int main()
{
    play_game();
}