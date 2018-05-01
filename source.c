#include <p18f4550.h>

#pragma config FOSC=INTOSCIO_EC
#pragma config WDT = OFF, MCLRE = OFF
#define dado1 0x05
#define dado0 0x01
#define comando1 0x04
#define comando0 0x00

int countms =0, aux;

unsigned char ch1, ch2, ch3, ch4,volta=0, j, k, dezenaS, dezenaM,centM, milM, dezenaMin, unidadeS, unidadeM, unidadeMin, count_d=1;

void countmr (void);
void botao (void);
void mostraNumero(void);
void delayM(void);

#pragma code tmr0 = 0x18
void interrupt_at_tmr0(void){
	_asm GOTO countmr _endasm
}
#pragma code

#pragma code teste = 0x08
void interrupt_at_teste(void){
	_asm GOTO botao _endasm
}
#pragma code



#pragma interrupt countmr
void countmr (void){
	if(!INTCONbits.TMR0IF){}
	else{
		INTCONbits.TMR0IF = 0;
		TMR0L=0xFD;
		
		countms++;
		if(countms==10){
			countms = 0;
			dezenaM++;
			if(dezenaM == 10){
				dezenaM = 0;
				centM++;
				if(centM == 10){
					centM = 0;
					milM++;
					if(milM == 10){
						milM = 0;
						j++;
						if(j == 60){
							j=0;
							k++;
							if(k == 60){
								k=0;
								}
							}
						}
						
					}
				}
			}
	}
}

#pragma interrupt botao

void botao (void){
	if(!INTCON3bits.INT1IF){}
	else{
		INTCON3bits.INT1IF = 0;
		PORTCbits.RC4 = !PORTCbits.RC4;
		if(volta < 3){
			volta++;
			delayM();
		}
		else{
			T0CONbits.TMR0ON=0;
		}
	}
}


void setPin(void){
	ADCON1 = 0xFF;
	OSCCON=0B01110010;
	TRISC = 0b00000000;
	TRISB = 0b00000011;
	TRISD = 0;
	PORTC = 0;
	PORTD = 0;
//	LATBbits.LATB1 = 1;
	RCONbits.IPEN = 1; // Habilita interrupção
	INTCONbits.GIE = 1; // Habilita interrupção de todas as fontes
	INTCONbits.GIEH = 1;
	INTCON3bits.INT1IE = 1;
	INTCON3bits.INT1IF = 0;
	INTCON3bits.INT1IP = 1;
	INTCON2bits.INTEDG1 = 1;
/*	INTCONbits.INT0IE = 1; // Habilita interrupção pino RB0(INT0)
	INTCON2bits.INTEDG0 = 1; // Interrupção na borda de subida - 1
	INTCONbits.INT0IF = 0; // 0 - Não ocorreu interrupção / 1 - Ocorreu interrupção
*/	PORTCbits.RC4 = 0;
	INTCONbits.GIEL = 1;
	
}


void delayM(){
	int k;
	for (k=0; k<=520;k++){}
}

void set_LCD(){
	PORTD = 0x38;
	delayM();
	PORTC = comando1;
	PORTC = comando0;
	PORTD = 0x38;
	delayM();
	PORTC = comando1;
	PORTC = comando0;
	PORTD = 0x06;
	delayM();
	PORTC = comando1;
	PORTC = comando0;
	PORTD = 0x0C;
	delayM();
	PORTC = comando1;
	PORTC = comando0;
	PORTD = 0x01;
	delayM();
	PORTC = comando1;
	PORTC = comando0;
	PORTD = 0x84;
	delayM();
	PORTC = comando1;
	PORTC = comando0;
}

int converte(int c){
	int conv;
	int teste = c;
	if(teste == 0){
		conv = 0x30;
	}
	if(teste == 1){
		conv = 0x31;
	}
	if(teste == 2){
		conv = 0x32;
	}
	if(teste == 3){
		conv = 0x33;
	}
	if(teste == 4){
		conv = 0x34;
	}
	if(teste == 5){
		conv = 0x35;
	}
	if(teste == 6){
		conv = 0x36;
	}
	if(teste == 7){
		conv = 0x37;
	}
	if(teste == 8){
		conv = 0x38;
	}
	if(teste == 9){
		conv = 0x39;
	}
	return conv;
}

void contaMil_un(){
	ch4 = converte(unidadeM);
	PORTD = ch4;
	delayM();
	PORTC = dado1;
	PORTC = dado0;
	PORTD = 0x84;// volta para o inicio do relogio
	delayM();
	PORTC = comando1;
	PORTC = comando0;
/*
 Precisa alterar essa função e as demais correspondetes de milisegundo para funcionar como milisegundo
*/
	
}

void contaMil_dez(){
	ch3 = converte(dezenaM);
	PORTD = ch3;
	delayM();
	PORTC = dado1;
	PORTC = dado0;

}

void contaMil_cent(){
	ch2 = converte(centM);
	PORTD = ch2;
	delayM();
	PORTC = dado1;
	PORTC = dado0;
	
}

void contaMil_mil(){
	ch1 = converte(milM);
	PORTD = ch1;
	delayM();
	PORTC = dado1;
	PORTC = dado0;
	
}


void contaSeg_un(){
	unidadeS = converte(j%10);
	PORTD = unidadeS;
	delayM();
	PORTC = dado1;
	PORTC = dado0;
	PORTD = 0x3A;
	delayM();
	PORTC = dado1;
	PORTC = dado0;

}

void contaSeg_dez(){
	dezenaS = converte(j/10);
	PORTD = dezenaS;
	delayM();
	PORTC = dado1;
	PORTC = dado0;
}

void contaMin_un(){
	unidadeMin = converte(k%10);
	PORTD = unidadeMin;
	delayM();
	PORTC = dado1;
	PORTC = dado0;
	PORTD = 0x3A;
	delayM();
	PORTC = dado1;
	PORTC = dado0;

}

void contaMin_dez(){
	dezenaMin = converte(k/10);
	PORTD = dezenaMin;
	delayM();
	PORTC = dado1;
	PORTC = dado0;

}

void mostravolta(){
	PORTD = 0x56;
	delayM();
	PORTC = dado1;
	PORTC = dado0;
	PORTD = 0x6F;
	delayM();
	PORTC = dado1;
	PORTC = dado0;
	PORTD = 0x6C;
	delayM();
	PORTC = dado1;
	PORTC = dado0;
	PORTD = 0x74;
	delayM();
	PORTC = dado1;
	PORTC = dado0;
	PORTD = 0x61;
	delayM();
	PORTC = dado1;
	PORTC = dado0;
	PORTD = 0X73;
	delayM();
	PORTC = dado1;
	PORTC = dado0;
	PORTD = 0x3A;
	delayM();
	PORTC = dado1;
	PORTC = dado0;
	aux = converte (volta);
	PORTD = aux;
	delayM();
	PORTC = dado1;
	PORTC = dado0;
	PORTD = 0xC3;
	delayM();
	PORTC = comando1;
	PORTC = comando0;
	
}

void mostraNumero(){
		
		contaMin_dez();
		contaMin_un();
		contaSeg_dez();
		contaSeg_un();
		contaMil_mil();
		contaMil_cent();
		contaMil_dez();
		contaMil_un();

}

void main (void){
	setPin();
	set_LCD();

	// Configuração do TIMER0

	INTCONbits.TMR0IE = 1; // Habilita interrupção por interrupção timer0
	INTCONbits.TMR0IF = 0; // 0 - Não estorou o timer0 / 1 - estorou o timer0
	INTCON2bits.TMR0IP = 0; // Alta prioridade = 1
	T0CONbits.TMR0ON=1;	// 	Habilita timer0 a contar
	T0CONbits.T08BIT=1;	// 	timer0 com 8 bits
	T0CONbits.T0CS=0;	//	modo timer fonte interna (8Mhz/4=2MHz)
	T0CONbits.PSA=0;	// 	com prescaler
	T0CONbits.T0PS0=1;
	T0CONbits.T0PS1=0;
	T0CONbits.T0PS2=1;	// prescaler=64
	TMR0L=0xFD;				//valor de recarga para 1 milissegundo

	while(1){
		mostravolta();
		mostraNumero();
		/* Atualizar para valores atuais
		mostraNumero();
		delayB3();
		counterms(); // precisa retirar pois esta na interrupção
		if( countms == 1000){
			countms = 0;
			counterJ();
			if (j==60){
				j = 0;
				counterK();
				if (k ==60){
					k = 0;
				}	
			}	
		}
		*/
	}
	
}