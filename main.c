#include "msp.h"

static int count = 0;
uint16_t timer[3]={163840,98304,32768};
int main(){
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_PW;//disable wdt
	
	P1SEL0 &= ~(BIT0 | BIT1 | BIT4);
	P1SEL1 &= ~(BIT0 | BIT1 | BIT4);
	
	P2SEL0 &= ~(BIT0 | BIT1 | BIT2);
	P2SEL1 &= ~(BIT0 | BIT1 | BIT2);
	
	P1DIR &= ~(BIT1 | BIT4);
	P1DIR |= (BIT0);
	P2DIR |= (BIT0 | BIT1 | BIT2);
	
	P1REN |= (BIT1 | BIT4);
	
	P1OUT |= (BIT1 | BIT4);
	P1OUT &= ~(BIT0);
	
	P2OUT &= ~(BIT0 | BIT1| BIT2);
	
	P1IES |= (BIT1 | BIT4);
	P1IFG &= ~(BIT1 | BIT4);
	P1IE |= (BIT1 | BIT4);
	

	
	NVIC_SetPriority(TA0_N_IRQn, 2);
	NVIC_ClearPendingIRQ(TA0_N_IRQn);
	NVIC_EnableIRQ(TA0_N_IRQn);
	
	TA0CTL &= ~(BIT4 | BIT5);//STOP TIMER
	TA0CTL &= ~(BIT0);//CLEAR INTERRUPT FLAG
	TA0CCR0 = (uint16_t) (163840);
	TA0CTL |= (BIT1);//INTERRUPT ENABLE
	TA0CTL |= (BIT4); //UP MODE
	TA0CTL |= (BIT8); //SET TA
	
	__ASM("CPSIE I");
	
	while(1){
		
	}
	

}

	
void TA0_N_IRQHandler(void){
	
	TA0CTL &= ~BIT0; //CLEAR INTERRUPT FLAG
	//P1OUT ^= BIT0;
	count=(count+1)%3;
	TA0CCR0 = (uint16_t)(timer[count]);
	if (count==0){
		P2->OUT=2;
	}
	else if (count==1){
		P2->OUT=3;
	}else{
		P2->OUT=1;
	}
	
	
}
