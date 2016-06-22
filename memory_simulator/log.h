/* Enumerated type for events to log:
 *     ILLEGAL:  input virtual address out of range
 *     FROM_PT:  computed physical address using the page table
 *     FROM_TLB:  computed physical address from the tlb
 *     PAGE_FAULT:  physical address could not be determined  */

typedef enum{ ILLEGAL, FROM_PT, FROM_TLB, PAGE_FAULT} log_type;

void log_it(log_type,int,int);
//  param1:  event type
//  param2:  virtual address
//  param3:  physical address (ignored if ILLEGAL or PAGE_FAULT event)
//
//  Call the above once for every virtual address from the user
 

void start_logging(), stop_logging();
// open/close the file
// Call start_logging() when your program first starts
// Call stop_logging() before your program terminates

