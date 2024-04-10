#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"




enum COLOR {RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET};

enum procstate { UNUSED, USED, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };



#include "kernel/pstat.h" // Include the definition of the pstat structure

// Helper function to convert color enum to string
const char* color_to_string(enum COLOR c) {
    switch (c) {
        case RED: printf("%s","RED");
        case ORANGE: return "ORANGE";
        case YELLOW: return "YELLOW";
        case GREEN: return "GREEN";
        case BLUE: return "BLUE";
        case INDIGO: return "INDIGO";
        case VIOLET: return "VIOLET";
        default: return "UNKNOWN";
    }
}

// Helper function to convert state enum to string
const char* state_to_string(enum procstate s) {
    switch (s) {
        case UNUSED: return "UNUSED";
        case USED: return "USED";
        case SLEEPING: return "SLEEPING";
        case RUNNABLE: return "RUNNABLE";
        case RUNNING: return "RUNNING";
        case ZOMBIE: return "ZOMBIE";
        default: return "UNKNOWN";
    }
}


void ps() 
{
    struct pstat ps;

    // Invoke the getpinfo system call to fetch process information
    int sys_call_ret = getpinfo(&ps);

    if (sys_call_ret == -1) {
        printf("Error retrieving process information\n");
        return;
    }

    // Print the header
    printf("NAME\tPID\tSTATUS\t\tCOLOR\tTICKETS\n");

    // Iterate over the process table and print process information
    for (int i = 0; i < NPROC; i++) 
    {
        
        if (ps.inuse[i]) 
        {
 
            printf("%s\t%d\t", ps.name[i], ps.pid[i]);
        
            switch (ps.state[i]) 
            {
                case UNUSED:
                    printf("UNUSED\t\t");
                break;
                case USED:
                    printf("USED\t\t");
                    break;
                case SLEEPING:
                    printf("SLEEPING\t");
                    break;
                case RUNNABLE:
                    printf("RUNNABLE\t");
                    break;
                case RUNNING:
                    printf("RUNNING\t\t");
                    break;
                case ZOMBIE:
                    printf("ZOMBIE\t\t");
                    break;
                default:
                    printf("UNKNOWN\t\t");
            }
        
            switch (ps.color[i]) 
            {
                case RED:
                    printf("RED\t");
                    break;
                case ORANGE:
                    printf("ORANGE\t");
                    break;
                case YELLOW:
                    printf("YELLOW\t");
                    break;
                case GREEN:
                    printf("GREEN\t");
                    break;
                case BLUE:
                    printf("BLUE\t");
                    break;
                case INDIGO:
                    printf("INDIGO\t");
                    break;
                case VIOLET:
                    printf("VIOLET\t");
                    break;
                default:
                    printf("UNKNOWN\t");
            }
        
            printf("%d\n", ps.tickets[i]);
        }

    }
    
}

int main(int argc, char *argv[]) {
    ps(); // Call the ps function to display process information
    return 0;
}
