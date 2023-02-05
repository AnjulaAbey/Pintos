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

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  printf ("system call!\n");
  void *args = *(int *)f->esp;
  int syscall_num = *(int *)f->esp;

  printf ("syscall_num: %d \n", syscall_num);

  switch (syscall_num) {

    case SYS_WRITE:{
      int fd = *((int *)f->esp+1);
      void *buffer = *((int *)f->esp+2);
      unsigned size = *((unsigned *)f->esp+3);

      f->eax = write(fd, buffer, size);

      break;}

    case SYS_HALT:
    {
      shutdown_power_off();
      break;
    }

    case SYS_EXIT:{
      
      int exit_bit = *((int *)f->esp + 1);
      exit(exit_bit);
      break;
      }

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
  // thread_exit ();
}


int write(int fd, const void *buffer, unsigned size) {

  // printf("fd: %d\n", fd);
  printf("size: %d\n", (int)size);
  // printf("buffer[0]: %c\n", *(char*)buffer);
  if (fd == 1){
    putbuf((const char *)buffer, size);
    return size;
  }

  return 0;
}

void exit(int exit_bit) {
  struct thread *cur = thread_current();
  printf("%s: exit(%d)\n", cur->name, exit_bit);

  thread_exit();
}