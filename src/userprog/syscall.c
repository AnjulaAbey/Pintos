#include "userprog/syscall.h"
#include "filesys/file.h"
#include "filesys/filesys.h"
#include "lib/stdio.h"
#include "threads/interrupt.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include <stdio.h>
#include <syscall-nr.h>

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

void get_three_arguments(struct intr_frame *f, int choose_syscall, void *args){
  int fd = *(int *)args + 4;
  void *buffer = *(int *)args + 8;
  unsigned size = *(int *)args + 12;

  switch (choose_syscall) {
    
    case SYS_WRITE:
      
      f->eax = write(fd, buffer, size);
      break;

    default:
      break;
  }
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  printf ("system call!\n");
  void *args = *(int *)f->esp;
  int syscall_num = *(int *)f->esp;

  printf ("syscall_num: %d \n", syscall_num);

  switch (syscall_num) {

    case SYS_WRITE:
      get_three_arguments(f, SYS_WRITE, args);
      break;

    case SYS_HALT:

      shutdown_power_off();

      break;


    case SYS_EXIT:
      
      int exit_bit = *(int *)args + 4;
      exit(exit_bit);
      break;


    case SYS_EXEC:
      printf ("exec system call!\n");
      break;


    case SYS_WAIT:
      printf ("wait system call!\n");
      break;


    case SYS_CREATE:
      printf ("create system call!\n");
      break;


    case SYS_REMOVE:
      printf ("remove system call!\n");
      break;


    case SYS_OPEN:
      printf ("open system call!\n");
      break;


    case SYS_FILESIZE:
      printf ("filesize system call!\n");
      break;


    case SYS_READ:
      printf ("read system call!\n");
      break;

    case SYS_SEEK:
      printf ("seek system call!\n");
      break;


    case SYS_TELL:
      printf ("tell system call!\n");
      break;


    case SYS_CLOSE:
      printf ("close system call!\n");
      break;


    default:
      break;

  }
  thread_exit ();
}


int write(int fd, const void *buffer, unsigned size) {
  printf ("write system call!\n");
  return 0;
}