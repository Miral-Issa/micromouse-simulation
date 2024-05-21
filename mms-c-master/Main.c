/*#include <stdio.h>

#include "API.h"

void log(char* text) {
    fprintf(stderr, "%s\n", text);
    fflush(stderr);
}

int main(int argc, char* argv[]) {
    log("Running... ");
    API_setColor(0, 0, 'G');
    API_setText(0, 0, "start");
    while (1) {
        if (!API_wallLeft()) {
            API_turnLeft();
        }
        while (API_wallFront()) {
            API_turnRight();
        }
        API_moveForward();
    }
}*/

#include <stdio.h>
#include "API.h"

struct Cell
{
    //coordinations
    int coordinationX;
    int coordinationY;
    //walls
    int walls[4]; //north, south, west, east
    //number of visited times
    int visited;
};

//struct Cell visited[16][16];
int visited[16][16] = { 0 };
char direction;
int x, y;

void movingToNextCell(char turnTo); //return 1 if calculate coordenation without error, return 0 if error 
void calculateNewCoordination(int coordination[]);

// Function to implement the left-hand algorithm
/*void leftHandAlgorithm() {
    int turned;
    while (1) {
        // If no wall on the left, turn left and move forward
        while (!API_wallLeft()) {
            API_turnLeft();
            if (API_moveForward() == 0) {
                // Handle crash or end of maze
                return;
            }
            else
            {
                turned = movingToNextCell('L');
            }
        }

        // If no wall in front, move forward
        if (!API_wallFront()) {
            
            if (API_moveForward() == 0){ //|| movingToNextCell('F') == 0) {
                // Handle crash or end of maze
                return;
            }
            else
            {
                turned = movingToNextCell('F');
            }
        }
        else {
            // Turn right if there is a wall on the left and front
            API_turnRight();
            if(API_moveForward() != 0)
                turned = movingToNextCell('R');
        }
    }
}*/
void log(char* text) {
    fprintf(stderr, "%s\n", text);
    fflush(stderr);
}

void leftHandAlgorithm()
{
    while (1) {

        int coo[] = {x,y};
        movingToNextCell('L');
        calculateNewCoordination(coo);
        movingToNextCell('R');
        int coo2[] = { x,y };
        movingToNextCell('R');
        calculateNewCoordination(coo2);
        movingToNextCell('L');

       /* if (visited[coo[1]][coo[0]] > 1 || visited[coo2[1]][coo2[0]] > 1)
        {
            if (visited[coo[1]][coo[0]] < visited[coo2[1]][coo2[0]]  && !API_wallLeft())
            {
                API_turnLeft();
            }
            else if(visited[coo[1]][coo[0]] > visited[coo2[1]][coo2[0]]  && !API_wallRight())
            {
                API_turnRight();
            }

            API_moveForward();

            int coordination[] = { x,y };
            calculateNewCoordination(coordination);
            x = coordination[0];
            y = coordination[1];

            API_setColor(y, x, 'Y');
            API_setText(y, x, "V");
            visited[y][x]++;

            char str[20];
            sprintf(str, "x=%d, y=%d", x, y);
            log(str);

            continue;
        }*/

        if (!API_wallLeft()) {
            API_turnLeft();
            movingToNextCell('L');
        }
        while (API_wallFront()) {
            API_turnRight();
            movingToNextCell('R');
        }
        API_moveForward();
        
        int coordination[] = { x,y };
        calculateNewCoordination(coordination);
        x = coordination[0];
        y = coordination[1];

        API_setColor(y, x, 'Y');
        API_setText(y, x, "V");
        visited[y][x]++;

        char str[20];
        sprintf(str, "x=%d, y=%d", x,y);
        log(str);
    }
}

int main() {
    // Initialize maze parameters
    int width = API_mazeWidth();
    int height = API_mazeHeight();

    // Set the starting position and direction of the micromouse
    int startX = 0;
    int startY = 0;
    //char startDir = 'N'; // Assuming North as the starting direction
    direction = 'N';
    x = 0;
    y = 0;

    char str[20];
    sprintf(str, "direction = %c", direction);
    log(str);

    // Set initial position and direction
    API_setText(startX, startY, "S"); // S for starting point
    API_setColor(startX, startY, 'G'); // Green color for starting point

    // Implement the left-hand algorithm
    leftHandAlgorithm();

    // Add any additional code for final actions or cleanup

    return 0;
}

void movingToNextCell(char turnTo)
{
    int nextCellCordinat[2];
    //turnTo = 'L' -> left/ 'R' -> right

    if (turnTo == 'L')
    {
        switch (direction)
        {
            case 'N':
                direction = 'W';
               // y--;
                break;
            case 'S':
                direction = 'E';
               // y++;
                break;
            case 'W':
                direction = 'S';
               // x--;
                break;
            case 'E':
                direction = 'N';
               // x++;
                break;
            default:
                //return 0;
                break;
        }
    }
    else if (turnTo == 'R')
    {
        switch (direction)
        {
            case 'N':
                direction = 'E';
               // y++;
                break;
            case 'S':
                direction = 'W';
               // y--;
                break;
            case 'W':
                direction = 'N';
               // x++;
                break;
            case 'E':
                direction = 'S';
               // x--;
                break;
        default:
            //return 0;
            break;
        }
    }

}
void calculateNewCoordination(int coordination[])//coo[0]=x,coo[1]=y
{
    switch (direction)
    {
    case 'N':
        //x++;
        coordination[0]++;
        break;
    case 'S':
        //x--;
        coordination[0]--;
        break;
    case 'W':
        //y--;
        coordination[1]--;
        break;
    case 'E':
        //y++;
        coordination[1]++;
        break;
    default:
        break;
    }
}

/*void addCellToVisited()
{
    if (visited[y][x] == null)
    {
        struct Cell newCell;
        newCell.coordinationX = x;
        newCell.coordinationY = y;
        newCell.visited=1;
    }
}*/
