#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM_FLOORS 5

void open_closed_door(void);
void move_elevator(int floor);

int currentfloor=1;   // Assuming the elevator starts at the first floor
int targetfloor=1;   // The floor requested by a user




int main()
{
    //simulate the elevator operation

    printf("Elevator Simulation \n");
    while(1)
    {
        int floor;
        printf("Enter the floor Number (1 to %d) or 0 to exit :",NUM_FLOORS);
        scanf("%d",&floor);
        if(floor>=1 && floor<=NUM_FLOORS)
        {
            if (floor!=currentfloor)
            {
                move_elevator(floor);
                open_closed_door();
            }
            else
            {
                printf("Already at floor %d \n",floor);
                open_closed_door();
            }

        }
        else if(0==floor)
        {
            break;
        }
        else
        {
            printf("invalid floor number. please try again.\n");
        }
    }
    return 0;
}

void open_closed_door(void)  // Function to open the elevator door
{
    sleep(1);
    printf("Openning door at floor %d\n",currentfloor);
    sleep(1);
    printf("closing the door \n\n");
}


void move_elevator(int floor)    // Function to move the elevator to the target floor
{
    printf("Call button pressed on floor %d \n",floor);
    targetfloor=floor;
    if(currentfloor<targetfloor)
    {
        printf("Moving up.....\n");
        while(currentfloor<targetfloor)
        {
            currentfloor++;
            sleep(1);
            printf("floor %d\n",currentfloor);
        }
    }
    else
        {
            printf("Moving dowing.....\n");
            while(currentfloor>targetfloor)
            {
                currentfloor--;
                sleep(1);
                printf("Floor %d \n",currentfloor);
            }
        }
}
