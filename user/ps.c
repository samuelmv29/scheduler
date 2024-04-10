#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

enum COLOR {RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET};

enum procstate { UNUSED, USED, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

#include "kernel/pstat.h"

int main(int argc, char *argv[]) 
{

  struct pstat process_state;

  int sys_call_ret = getpinfo(&process_state);

  if (sys_call_ret == -1) 
  {
    return -1;
  }

  
  printf("NAME\tPID\tSTATUS\t\tCOLOR\tTICKETS\n");

  
  for (int i = 0; i < NPROC; i++) 
  {
    if (process_state.inuse[i]) 
    {
        printf("%s\t%d\t", process_state.name[i], process_state.pid[i]);

      
        if (process_state.state[i] == UNUSED)
        {
            printf("UNUSED\t\t");
        }
        
        else if (process_state.state[i] == USED)
        {
            printf("USED\t\t");
        }
        else if (process_state.state[i] == SLEEPING)
        {
            printf("SLEEPING\t");
        }

        else if (process_state.state[i] == RUNNABLE)
        {
            printf("RUNNABLE\t");
        }
        
        else if (process_state.state[i] == RUNNING)
        {
            printf("RUNNING\t\t");
        }
        
        else if (process_state.state[i] == ZOMBIE)
        {
            printf("ZOMBIE\t\t");
        }
        
        else
        {
            printf("UNKNOWN\t\t");
        }



        if (process_state.color[i] == RED)
        {
            printf("RED\t");
        }

        else if (process_state.color[i] == ORANGE)
        {
            printf("ORANGE\t");
        }

        else if (process_state.color[i] == YELLOW)
        {
            printf("YELLOW\t");
        }
        
        else if (process_state.color[i] == GREEN)
        {
            printf("GREEN\t");
        }
        
        else if (process_state.color[i] == BLUE)
        {
            printf("BLUE\t");
        }

        else if (process_state.color[i] == INDIGO)
        {
            printf("INDIGO\t");
        }

        else if (process_state.color[i] == VIOLET)
        {
            printf("VIOLET\t");
        }
        
        else
        {
            printf("UNKNOWN\t");
        }
        
        printf("%d\n", process_state.tickets[i]);
    }
  }

  return 0;
}