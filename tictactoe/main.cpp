#include <algorithm>
#include <iostream>
using namespace std;

#define GRID_SIZE 3

class Game
{
  private:
    char grid[GRID_SIZE][GRID_SIZE];
    char player1;
    char player2;
    
  public:
    Game(char player1)
      : player1(player1), player2((player1 == 'X') ? 'O' : 'X')
    {
      makeGrid();
      while (PlayOn())
      {
        cout<<"\x1B[2J\x1B[H";
        PlayOn();
        displayGrid();
        askTurn();
      }
    }

  //------------------------------------------------------

    void makeGrid(){
      char n = '1';
      for(int i=0; i<GRID_SIZE; i++){
        for(int j=0; j<GRID_SIZE; j++){
          grid[i][j] = n;
          n++;
        }
      }
    }

  //------------------------------------------------------

    void displayGrid(){
      cout<<endl<<" +---+---+---+"<<endl;
      for(int i=0; i<GRID_SIZE; i++){
        cout<<" |";
        for(int j=0; j<GRID_SIZE; j++){

          //colorize bg
          if(grid[i][j] == 'X'){
            cout << "\x1B[41;30m";
          }
          else if(grid[i][j] == 'O'){
            cout << "\x1B[42;30m";
          }
          cout << " " << grid[i][j] << " " << "\x1B[39;49m" << "|";
        }
        cout<<endl<<" +---+---+---+"<<endl;
      }
    }

//------------------------------------------------------
    string winningMoves[8] = {
      "123",
      "456",
      "789",
      "147",
      "258",
      "369",
      "159",
      "357"
    };
//------------------------------------------------------

    bool Player1sTurn = true;
    void askTurn(){
      int position;
      cout<< ((Player1sTurn) ? player1 : player2) << "'s turn" << endl;
      cout<<"Where would you like to place?\n";
      cin>>position;

      int row = (position - 1) / GRID_SIZE;
      int col = (position - 1) % GRID_SIZE;

      if(grid[row][col] == 'X' || grid[row][col] == 'O'){
        cout<<"Place already taken"<<endl;
      }else {
        grid[row][col] = (Player1sTurn) ? player1 : player2;

        for(auto& move: winningMoves){
          for(auto& place: move){
            int pos = place - '0';
            if(pos == position)
              place = grid[row][col];
          }
        }
        Player1sTurn = !Player1sTurn;
      }
    }

//------------------------------------------------------

    bool PlayOn(){
      for(const auto& move: winningMoves){
        if (move[0] == move[1] && move[1] == move[2]) {
          cout<<"\x1B[2J\x1B[H";
          displayGrid(); //displayGrid for the last time, it won't run in while loop above
          cout<<" Player "<< move[0] <<" wins ";
          return false;
        }
      }
      cout<<endl;
      return true;
    }
};

int main ()
{
  std::cout << "Player 1 char: ";
  Game game(std::cin.get());

  return 0;
}
