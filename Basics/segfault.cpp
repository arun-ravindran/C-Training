/* Example installation of Linux signal handlers for handling SIGSEGV - Segmentation fault */
/* From https://gist.github.com/fairlight1337/55978671ace2c75020eddbfbdd670221 */


#include <iostream>
#include <string.h>
#include <signal.h>

// int nSignum - the number of the signal that caused invocation of the handler
// siginfo_t A pointer to a siginfo_t, which is a structure containing
// further information about the signal (see man page, its got 24 fields!)
//  vconntext: The structure pointed to by this field contains signal context
// information that was saved on the user-space stack by the kernel

void handler(int nSignum, siginfo_t* si, void* vcontext) 
{
  std::cout << "Segmentation fault" << std::endl;
  
  ucontext_t* context = (ucontext_t*)vcontext; //ucontext_t is user context
  context->uc_mcontext.gregs[REG_RIP]++; //Increment instruction pointer in 64 bit machine to get past segfault
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
  sigaction(SIGSEGV, &action, NULL);
  
  // Test - Cause a seg fault
  int* x = 0;
  int y = *x;
  
  std::cout << "Phew! Escaped without crashing!!!" << std::endl;
  
  return 0;
}
