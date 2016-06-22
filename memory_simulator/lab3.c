#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "log.c"

#define ROW 128
#define TLBROW 8
#define COL 2
#define TLBCOL 3
#define OFFSET 10
#define VPNBITS 7
#define PPNBITS 15
#define MAXVPN 127
#define LRGST17BIT 131071

void read_pagetable(FILE *results,int p_table[][COL]);
int page_table_lookup(int va, int vpn, int vpo, int p_table[][COL]);
int create_mask(int bit_start, int bit_finish);
int tlb_lookup(int va, int vpn, int vpo, int tlb[8][3], int p_table[][COL]);
void zero_2d(int tlb[TLBROW][TLBCOL]);

int main(int argc, char **argv)
{
	FILE *f = fopen(strcat(argv[1],".pt"),"r");	//open the file where the pagetable is stored
	int p_table[ROW][COL];				//initialize our page table array
	int tlb[TLBROW][TLBCOL];
	int exit_flag  = 0;				//status of user input loop
	int user_input = 0;
	int va  = 0;
	int pa  = 0;
	int vpn = 0;
	int vpo = 0;
	char in;
	char c;
	int i;

	read_pagetable(f, p_table);							//read from file
	zero_2d(tlb);									//init the TLB
	start_logging();								//start the log

	while(exit_flag == 0){								//acquire the user input
		printf("Enter a virtual address or -1 to exit:  ");
		if(scanf("%d%c", &user_input, &in) != 2 || in != '\n'){			//hacked way to check for integer only
			printf("Please enter a single integer\n");
			while(c != '\n'){						//gross
			c = getchar();							//disgusting
			}
			c='`';								//more gross
		}
		else{
		if(user_input == -1){
			exit_flag = 1;
			return;
		}
		va = user_input;
		vpn = (va >> OFFSET);
		vpo = (va & create_mask(0,10));
		if(((va >= 0) && (va <= LRGST17BIT)) && (vpn <= MAXVPN)){		//va must be: non-negative
			printf("Virtual Address: 0x%x\n", va);				//	  17 bits or less
											//	  127 base_10 or less
			tlb_lookup(va, vpn, vpo, tlb, p_table);
		}
		else{									//return not valid VA
			log_it(ILLEGAL, va, 0);
			printf("Illegal virtual address\n");
		}
		}
	}
	fclose(f);
	stop_logging();
	exit(0);
}
int tlb_lookup(int va, int vpn, int vpo, int tlb[TLBROW][TLBCOL], int p_table[][COL])
{											//8 entries | 3 columns	0:tag 1:ppn 2:validity
	int tlbi = 0;
	int tlbt = 0;
	int ppn  = 0;
	int pa   = 0;
	int fail = -1;

	tlbi = (vpn & create_mask(0,2));
	tlbt = (vpn >> 3);

	if(tlb[tlbi][2] == 0){								//when the location is invalid at this index
		tlb[tlbi][0] = tlbt; 							//replace the tag
		tlb[tlbi][1] = page_table_lookup(va, vpn, vpo, p_table);		//replace the ppn
		if(tlb[tlbi][1] != fail){						//if there was not a page fault
			tlb[tlbi][2] = 1;						//set to valid
		}
	}
	else{										//there was  tlb hit
		if(tlb[tlbi][0] == tlbt){						//the tag matches
			ppn = tlb[tlbi][1];//update the ppn
			pa  = ((ppn <<10) + vpo);
			printf("Physical Address: 0x%x from the tlb\n", pa);
			log_it(FROM_TLB, va, pa);
			return;
		}
		else{									//the tag doesnt match, tlb miss, go to page table
			ppn = page_table_lookup(va, vpn, vpo, p_table);
			if(ppn != fail){						//a page fault did not occur
				tlb[tlbi][0] = tlbt;					//update the tlbt with the newly found item
				tlb[tlbi][1] = ppn;
				return;
			}
		}
	}
	return 0;
}
int page_table_lookup(int va, int vpn, int vpo, int p_table[][COL])
{											//128 rows, 2 columns   0:validity 1:ppn
	int ppn  = 0;
	int ppo  = vpo;
	int pa   = 0;
	int fail = -1;
	if(p_table[vpn][0] == 1){							//found in page table and is valid
		ppn = (p_table[vpn][1]);
		pa  = ((ppn << 10)  + ppo);
		printf("Physical Address: 0x%x from the page table\n", pa);
		log_it(FROM_PT, va, pa);
	}
	else{										//cant find in page table
		printf("Page Fault\n");
		log_it(PAGE_FAULT, va, pa);
		return fail;
	}
	return ppn;
}
void read_pagetable(FILE *pt_in, int p_table[][COL])
{
	int row, item;
	for(row = 0; row < ROW; row++){							//read all the lines and store in our page_table array
		item = fscanf(pt_in, "%d%d", &p_table[row][0], &p_table[row][1]);
	}
}
int create_mask(int bit_start, int bit_finish)
{											//create a mask for the range from bit_start to bit_finish
	int mask = 0;
	int i    = 0;
	for (i = bit_start; i <= bit_finish; i++)
		mask |= 1 << i;
	return mask;
}
void zero_2d(int tlb[TLBROW][TLBCOL]){							//initialize tlb with zero entries
	int i;
	for(i = 0; i < 8; i++){
		tlb[i][0] = 0;
		tlb[i][1] = 0;
		tlb[i][2] = 0;
	}
}
