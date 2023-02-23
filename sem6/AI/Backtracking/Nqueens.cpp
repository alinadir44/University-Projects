#include <iostream>
using namespace std;

//20K0325

int gameOver(int **board,int n){
    int count=0;
    for (int i = 0; i < n; i++)
    {
       for (int j = 0; j < n; j++)
       {
            if(board[i][j]==1)
            count++;
       }
       
    }

    return count==n?true:false;
    
}

int isValid1(int **board,int n,int i,int j){
    cout<<"In isValid\n";
    for (int i1 = i; i1>=0; i1--){
        if(board[i1][j]==1)
        return 0;
    }
    for (int i1 = i,j1=j; i1>=0 && j1<n; i1--,j1++){
        if(board[i1][j1]==1)
        return 0;
    }
    for (int i1 = i,j1=j; i1>=0 && j1>=0; i1--,j1--){
        if(board[i1][j1]==1)
        return 0;
    }
    cout<<"("<<i<<","<<j<<") is Valid\n";
    return 1;
}

int isValid(int **board,int n,int i,int j){
    cout<<"in isValid\n";
    int count=0;
    for (int j1 = 0; j1 < n; j1++)
    {
        if(board[i][j1]==1)
        count++;

    }
    if(count>1)
    return 0;

    count=0;
    for (int i1 = 0; i1 < n; i1++)
    {
        if(board[i1][j]==1)
        count++;
    }
    if(count>1)
    return 0;
    
    count=0;
    for (int j1 = j,i1=i,i2=i,j2=j; (j1 < n && i1<n) || (j2>0  && i2>0); j1++,i1++,j2--,i2--){
        if(j1 < n && i1<n){
        if(board[i1][j1]==1)
        count++;
        }
        if(j2>0  && i2>0){
        if(board[i2][j2]==1)
        count++;
        }
    }
    
    if(count>1)
    return 0;
    
    count=0;
    for (int j1 = j,i1=i,i2=i,j2=j;(j1 < n && i1>0) || (j2>0  && i2<n); j1++,i1--,j2--,i2++){
        if(j1 < n && i1>0){
        if(board[j1][j1]==1)
        count++;
        }
        if(j2>0  && i2<n){
        if(board[i2][j2]==1)
        count++;
        }
    }
    
    if(count>1)
    return 0;

    return 1;

}

bool nqueens(int **board,int n,int i,int pos){
    static int qcount=0;
    if(gameOver(board,n))
    return true;
    else{
    for (int j1 = pos; j1 <n; j1++){
        if (isValid1(board,n,i,j1)){
            cout<<"Placed queen at ("<<i<<","<<j1<<")\n";
            board[i][j1]=1;
            if(!nqueens(board,n,i+1,0)){
                cout<<"Removing queen from ("<<i<<","<<j1<<")\n";
                board[i][j1]=0;
            }
            else
            return true;
    }
    }
    return false;
}
}

void printBoard(int **board,int n){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
    
}

int main(){
    int n,pos;
    do{
        cout<<"\nEnter value of N: ";
        cin>>n;
        cout<<"\nEnter value of initial position of first queen (1-N): ";
        cin>>pos;
    }while(!(n>0 && n<=8 && pos>0 && pos<=n));
    int **board=new int* [n];
    for (int i = 0; i < n; i++)
    {
        board[i]=new int[n];
        for (int j = 0; j < n; j++)
        {
            board[i][j]=0;
        }
        
    }
    cout<<"Initial state of board: \n";
    printBoard(board,n);
    cout<<endl;
    nqueens(board,n,0,pos-1);
    cout<<endl<<"Solution: \n";
    printBoard(board,n);
}