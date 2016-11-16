//*****************************************************************************
// This program models life in a society of organisms using two dimensional array 
// of size 30 x 30. The rules of birth, death, and survival for the organisms are 
// as follows: an organism is born in any empty cell having exactly three neighbors, 
// the organism dies from isolation if it has fewer than two neighbors, the organism 
// dies from overcrowding if it has more than three neighbors. All other organisms 
// survive to the next generation.
//*****************************************************************************

#include <iostream>
#include <string>
using namespace std;

void print_life_array(string life_array[30][30], int generation);

int main(){
    string life_array[30][30];
    int number_initial_cells, total_generations;
    
    //fill the array with string empty
    for(int row = 0; row < 30; row++){
        for (int col = 0; col < 30; col++){
            life_array[row][col] = "empty";
        }
    }
    
    char do_again;
    int counter = 0;
    do {
        if(counter > 0){
            while(cin.get() != '\n');
        }
        
        //ask user for the number of cells in first generation
        cout << "Please enter the number of initial cells: ";
        cin >> number_initial_cells;

        //ask user for position of those cells in 
        int cell = 1, first_pos, second_pos;
        while(cell <= number_initial_cells){
            cout << "Enter the position of cell number " << cell << ": ";
            cin >> first_pos >> second_pos;
            life_array[first_pos][second_pos] = "old__";
            cell++;
        }

        cout << "How many generations do you want to display? ";
        cin >> total_generations;
        cout << endl;
        
        char key_to_continue;
        for(int generation = 1; generation <= total_generations; generation++){
            print_life_array(life_array, generation);
            cout << endl << endl;
            cin.get(key_to_continue);
            if(generation < total_generations){
                cout << "Press any key to continue ";
                cin.get(key_to_continue);
            } else {
                cout << "Do you want to do it again? (Yes/No): ";
                cin >> do_again;
            }
        }
        counter++;
    } while (do_again == 'Y' || do_again == 'y');
    return 0;
}


void print_life_array(string life_array[30][30], int generation){
    //print life_array if generation is 1
    if(generation == 1 ){
        cout << "Generation " << generation << ": " << endl;
        for(int row = 0; row < 30; row++){
            for (int col = 0; col < 30; col++){
                string element = life_array[row][col];
                if(element == "empty") cout << "." << " ";
                else cout << "@" << " ";
            }
            cout << endl;
        }
    } else {
        //to determine which cell will have new organisms born
        for(int row = 0; row < 30; row++){
            for(int col = 0; col < 30; col++){
                //Establishing neighbors of a cell
                string up_left, up, up_right, left, right, down_left, down, down_right;
                string value = life_array[row][col];
                if(value == "empty"){
                    if(row - 1 >= 0 && col - 1 >= 0){
                        up_left = life_array[row - 1][col - 1];
                    }
                    if(row - 1 >= 0){
                        up = life_array[row - 1][col];
                    }
                    if(row - 1 >= 0 && col + 1 < 30){
                        up_right = life_array[row - 1][col + 1];
                    }
                    if(col - 1 >= 0){
                        left = life_array[row][col - 1];
                    }
                    if(col + 1 < 30){
                        right = life_array[row][col + 1];
                    }
                    if(row + 1 < 30 && col - 1 >= 0){
                        down_left = life_array[row + 1][col - 1];
                    }
                    if(row + 1 < 30){
                        down = life_array[row + 1][col];
                    }
                    if(row + 1 < 30 && col + 1 < 30){
                        down_right = life_array[row + 1][col + 1];
                    }
                    
                    string neighbors_array[] = {up_left, up, up_right, left, right, down_left, down, down_right};
                    int counter = 0;
                    
                    for(int i = 0; i < 8; i++){
                        string neighbor_value = neighbors_array[i];
                        if(neighbor_value == "old__"){
                            counter++;
                        }
                    }
                    if(counter == 3){
                        life_array[row][col] = "new__";
                    }
                }       
            }
        }
        
        //to determine which cells will the old organisms die
        string cells_to_empty[30][30];
        for(int row = 0; row < 30; row++){
            for(int col = 0; col < 30; col++){
                //Establishing neighbors of a cell
                string up_left, up, up_right, left, right, down_left, down, down_right;
                string value = life_array[row][col];
                if(value == "old__"){
                    if(row - 1 >= 0 && col - 1 >= 0){
                        up_left = life_array[row - 1][col - 1];
                    }
                    if(row - 1 >= 0){
                        up = life_array[row - 1][col];
                    }
                    if(row - 1 >= 0 && col + 1 < 30){
                        up_right = life_array[row - 1][col + 1];
                    }
                    if(col - 1 >= 0){
                        left = life_array[row][col - 1];
                    }
                    if(col + 1 < 30){
                        right = life_array[row][col + 1];
                    }
                    if(row + 1 < 30 && col - 1 >= 0){
                        down_left = life_array[row + 1][col - 1];
                    }
                    if(row + 1 < 30){
                        down = life_array[row + 1][col];
                    }
                    if(row + 1 < 30 && col + 1 < 30){
                        down_right = life_array[row + 1][col + 1];
                    }
                    
                    string neighbors_array[] = {up_left, up, up_right, left, right, down_left, down, down_right};
                    int counter = 0;
                    
                    for(int i = 0; i < 8; i++){
                        string neighbor_value = neighbors_array[i];
                        if(neighbor_value == "old__"){
                            counter++;
                        }
                    }
                    if(counter <= 1 || counter >= 4){
                        cells_to_empty[row][col] = life_array[row][col];
                    }
                }       
            }
        }
        
        //empty the elements that have less than 2 or greater than 3 neighbors
        for(int row = 0; row < 30; row++){
            for (int col = 0; col < 30; col++){
                string value = cells_to_empty[row][col];
                if(value == "old__"){
                    life_array[row][col] = "     ";
                }
            }
        }
        
        //print array at the end of generation 2 and later
        cout << "Generation " << generation << ": " << endl;
        for(int row = 0; row < 30; row++){
            for (int col = 0; col < 30; col++){
                string element = life_array[row][col];         
                if(element == "empty") cout << "." << " ";
                else if (element == "     ") cout << "." << " ";
                else cout << "@" << " ";
            }
            cout << endl;
        }
        
        for(int row = 0; row < 30; row++){
            for (int col = 0; col < 30; col++){
                string element = life_array[row][col];
                if(element == "new__"){
                    life_array[row][col] = "old__";
                } if(element == "     "){
                    life_array[row][col] = "empty";
                }
            }
        }   
    }
}