#include <stdio.h>
#include "log.h" 

/* Enumerated type for events to log:
 *     ILLEGAL:  input virtual address out of range
 *     FROM_PT:  computed physical address using the page table
 *     FROM_TLB:  computed physical address from the tlb
 *     PAGE_FAULT:  physical address could not be determined  */

FILE *log_file = NULL;

void start_logging() {
/* TODO:  modify the log file name to contain your userid rather than mine: */
  log_file = fopen("awebb3_lab3.log","w");
}

void stop_logging() {
    fclose(log_file);
}


void log_it(log_type entry, int va, int pa) {
/* param1:  event type
 * param2:  virtual address
 * param3:  physical address (ignored if ILLEGAL or PAGE_FAULT event)
 */
   switch(entry) {
      case ILLEGAL:  fprintf(log_file,"Illegal address: 0x%x\n",va); break;
      case FROM_PT:  fprintf(log_file,"Page table maps 0x%x to 0x%x\n",va,pa); break;
      case FROM_TLB:  fprintf(log_file,"TLB maps 0x%x to 0x%x\n",va,pa); break;
      case PAGE_FAULT:  fprintf(log_file,"Page fault: 0x%x\n",va); break;
   }
}

