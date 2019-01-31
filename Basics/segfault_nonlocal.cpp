/* Example installation of Linux signal handlers for handling SIGSEGV - Segmentation fault */
/* Alternate solution using non-local jumps */
/* Useful reference - Computer Systems by Bryant and O'Hallaron */

#include <iostream>
#include <string.h>
#include <signal.h>
#include <setjmp.h>

sigjmp_buf buf;

void handler(int nSignum, siginfo_t* si, void* vcontext) 
{
  std::cout << "Segmentation fault" << std::endl;
 
  // Fix the cause of seg fault here...

  siglongjmp(buf, 1); // program execution continues past sigsetjmp()
  
}


int main() 
{
  std::cout << "Start" << std::endl;
  
  struct sigaction action;
  memset(&action, 0, sizeof(struct sigaction));
  action.sa_flags = SA_SIGINFO; // Handler takes 3 arguments
  action.sa_sigaction = handler;

// The sigaction() system call is used to change the action taken by a process on receipt of a specific signal.
// int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
  if (!sigsetjmp(buf, 1)) // Saves the calling env and signal context
    sigaction(SIGSEGV, &action, NULL);
  
  // Test - Cause a seg fault
  int* x = 0;
  int y = *x;
  
  std::cout << "Phew! Escaped without crashing!!!" << std::endl;
  
  return 0;
}

