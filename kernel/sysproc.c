#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "pstat.h"


uint64
sys_setTickets(void)
{
  int tickets;
  argint(0, &tickets);
  setColor(myproc(), tickets);
  return 0;
}



uint64
sys_setColor(void)
{
  int color;
  argint(0, &color);
  setColor(myproc(), (enum COLOR)color);
  return 0;
}

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_getpinfo(struct pstat * pstats)
{
   // struct pstat *pstat_ptr;
  uint64 i;
  argaddr(0, &i);
   // if (argaddr(0, (void*)&pstat_ptr, sizeof(struct pstat)) < 0) {
   //     return -1; 
  
  struct pstat j;

    
    int result = getpinfo(&j);
    if(result<0){
      return -1;
    }
    int k = either_copyout(1, i, &j, sizeof(struct pstat));
    if (k<0) {
        return -1; 
    }

  return 0;
}