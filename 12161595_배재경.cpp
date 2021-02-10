#include <iostream>
#include <fstream>
using namespace std;

const int PAGE_SIZE = 256;
const int FRAME_SIZE = 256;
const int TLB_SIZE = 32;
ifstream Read;
ofstream Write;

int physicalAddress = 0;
int page_fault = 0;
int tlb_hit = 0;
double page_faultRate = 0.0;
int i = 0;
int line;
int offset;

typedef struct PAGE_TABLE {
	int page_number = 0;
	int frame_number = 0;
	int valid_bit;
}PAGE_TABLE;
PAGE_TABLE pt[PAGE_SIZE];

typedef struct FRAME_TABLE {
	int page_number = 0;
	int free_or_used = 0;
}FRAME_TABLE;
FRAME_TABLE ft[FRAME_SIZE];

typedef struct TLB {
	int page_number = 0;
	int frame_number = 0;
}TLB;
TLB tlb[TLB_SIZE];

int main() {
	int count = 0;
	Read.open("addresses.txt");
	Write.open("Physical.txt");

	while (!Read.eof()) {
		Read >> line;
		pt[line / 256].page_number = line / 256;
		offset = line % 256;

		for (i = 0; i < TLB_SIZE; i++) {
			if (tlb[i].page_number == pt[i].page_number &&  pt[i].page_number != 0) {
				tlb_hit++;		
				pt[i].valid_bit = 1;
			}
		}
		if (pt[page_number].valid_bit != 1) {
			page_fault++;
			pt[pt.page_number].valid_bit = 1;
			if (count >= TLB_SIZE)	
				count = 0;
			tlb[count].page_number = pt[pt.page_number].page_number;
			tlb[count].frame_number = pt[pt.page_number].frame_number;
			count++;
			ft[pt.frame_number].free_or_used = 1;
			ft[pt.frame_number].page_number = pt[pt.page_number].frame_number;
			pt[pt.page_number].frame_number++;
		}
		physicalAddress = pt[pt.page_number].frame_number* FRAME_SIZE) + offset;
	}
	Write.close();

	Write.open("Frame_table.txt");
	for (i = 0; i < FRAME_SIZE; i++)
	{
		Write << i << " " << ft[i].free_or_used << " " << ft[i].page_number << endl;
	}
	Write.close();



	page_faultRate = (double)page_fault / (pt[pt.page_number].frame_number + tlb_hit);
	cout << "page fault Rate = " << page_faultRate << endl;


	Write.open("TLB.txt");
	Write << "TLB hit ratio = " << (float)tlb_hit / (pt[pt.page_number].frame_number + tlb_hit) << endl;
	for (i = 0; i < count; i++)
		Write << tlb[i].page_number << " " << tlb[i].frame_number << endl;
	Write.close();

	Read.close();

	return 0;

}