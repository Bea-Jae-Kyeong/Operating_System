# Operating_System
The work done in Operation System

Logical address를 physical address로 변환하는 프로그램이다. 가상 주소의 크기는 32bit에서 사용
하지 않는 앞 쪽 16bit를 제외한 나머지 16bit, 즉 65536 바이트이다. TLB는 table을 빠르게 참
조하기 위한 효과적인 메모리 접근 방법으로, 메모리에 한 번 접근하고 TLB를 사용하는 방법이
다. 없을 경우에는 메모리에 두 번 접근하게 된다.

CPU가 가상 주소 즉 logical address를 발생시키면 page number와 offset으로 나누고 TLB 안에
logical address의 엔트리가 있는지 확인한다. 있으면 곧바로 frame number 값을 가져오고, 없을
경우에만 메인 메모리에 접근하여 page table에서 frame number를 가져온다. Frame number 값과
offset을 이용하여 physical address를 구하고 physical memory에 접근하게 된다.
프로그램의 작동 과정은 logical address를 받아와 page table과 TLB에 저장하고 physical
address로 변환하는 것이다. Page table는 구조체로, TLB와 Frame table은 구조체 배열로 생성하였
다.

먼저 addresses.txt에서 logical address 값을 읽어오고, 16 bit 중 앞 8 bit는 page number, 나머
지 8 bit는 offset으로 가진다. Page table에는 frame number 값을 배열로 받는 page_table 배열과
page number, frame number, 1은 valid 0은 invalid로 구분하는 valid_bit 배열이 있다. Frame table
에는 frame number가 free인지 used인지를 알아내는 free or used와 page number가 있다. TLB는
FIFO로, TLB안에는 page number와 frame number가 있고, 수시로 바뀔 수 있는 32개의 page
table 엔트리가 들어갈 수 있다. 만약 TLB에 page number가 들어있다면 32번의 검색만으로
frame number를 가져올 수 있다. TLB 배열 속 page number가 logical address의 page number와
일치한다면 TLB hit이 발생한 것이고, 일치하지 않는다면 TLB miss가 발생하였다고 한다. 찾으려던
page가 invalid 한 경우 page fault가 발생하였다고 한다. TLB miss이면 page table에 접근하게 되
고, TLB에 page number와 frame number 엔트리를 cache로서 기억하도록 한다. Page table의
page number에 frame number를 저장하고, 그 page number가 invalid에서 valid하게 되므로 1로
설정한다. TLB에 엔트리가 32개를 넘으면 맨 처음에 저장되었던 엔트리부터 다시 새로 저장하는
TLB replacement가 발생한다. page table의 frame number는 page number의 위치에 0에서 255
사이의 값으로 0부터 순차적으로 저장된다. Frame table의 free or used는 number에 해당되는 위
치가 frame을 사용중이므로 1로 설정된다.

Physical memory에는 256개의 frame들이 있고 한 frame의 사이즈는 256 byte 이므로 frame들
의 총 크기는 65536 byte가 된다. Physical address는 frame number와 frame size를 곱하여 offset
을 더한 값으로 구할 수 있다. 마침내 변환된 Physical address로 physical memory에 접근하게 된
다. Physical.txt에 physical address를 쓴다.

Page fault rate는 page fault에서 page를 찾던 횟수를 나눈 것이다. TLB hit rate는 TLB hit에서
전체 TLB 접근 횟수를 나눈 것이다. TLB.txt에 TLB hit rate와 TLB의 page number, frame number를
쓴다. Frame table.txt에 0부터 255까지의 frame number와 free인지 used인지를 알아내는 valid
invalid bit, 그리고 page number를 쓴다.
