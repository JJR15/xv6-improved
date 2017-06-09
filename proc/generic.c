#include "internal.h"
#include "xv6/defs.h"
#define NPDE 100

struct {
    struct spinlock lock;
    struct proc_dir_entry pde[NPDE];
} pde_table;

struct proc_dir_entry *pde_alloc(void)
{
  acquire(&pde_table.lock);
  for(int i=0; i<NPDE;i++)
  {
    if(pde_table[i].pdestate==UNUSED)
    {
      pde_table[i].pdestate=USED;
      release(&pde_table.lock);
      return &pde_table[i];
    }
  }
  release(&pde_table.lock);
  return 0;
}
struct proc_dir_entry *proc_mkdir(const char *name,unsigned int mode,struct proc_dir_entry *parent, void *data)
{
  
}

void remove_proc_entry(const char *name, struct proc_dir_entry *parent)
{
  
}

struct proc_dir_entry *proc_lookup(const char *path)//ʶ����Ժ����·��
{
  if(!name)
    return;
  int currentIndex = 0;
  int nextIndex = 1;
  proc_dir_entry* currentPDE = proc_root;
  bool findFlag = false;
  while(path[currentIndex] == '/')
  {
    while(path[nextIndex] != '/' && path[nextIndex] != '\0')
      nextIndex++;
    while(currentPDE != NULL)
    {
      if(currentPDE->namelen != nextIndex - currentIndex - 1)
      {
        currentPDE = currentPDE->next;
        continue;
      }
      for(int i = currentIndex + 1; i < nextIndex; ++i)
      {
        if(path[i] != currentPDE->name[i - currentIndex - 1])
        {
          currentPDE = currentPDE->next;
          continue;
        }
      }
      findFlag = true;
      currentPDE = currentPDE->subdir;
      break;
    }
    if(!findFlag)
    {
      cprintf("file not found!");
      return 0;
    }
    currentIndex = nextIndex;
    nextIndex++;
  }
  return currentPDE;
}
//proc��_root_lookup proc_lookup proc_pid_lookup 

