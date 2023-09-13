#include<pic.h>
__CONFIG(0X2CE4);
#define _XTAL_FREQ 4000000
void delay(unsigned int t)
{
	while(t--);
}
void txs(const char *p)
{
	while(*p)
	{
		TXREG=*p;
		while(TXIF==0);
				p++;
				TXIF=0;
	}
}
void txc(const char c)
{
	TXREG=c;
	while(TXIF==0);
	TXIF=0;
}
void main()
{
	PORTC=0X00;
	TRISC=0X80;
	ANSEL=0X00;
	ANSELH=0X00;
	TXSTA=0x24;
	RCSTA=0x90;
	SPBRG=25;
	while(1)
	{
		txs("AT");
		txc(0x0d);
		txc(0x0A);
		
			
		txs("AT+CMGF=1");   // text format
		txc(0x0d);
		txc(0x0A);
		delay(10000);
		
		txs("AT+CMGS=\"+91XXXXXXXXXX\"");
		txc(0x0d);
		txc(0x0A);
		delay(10000);
		
		txs("Object detected");
		txc(0x1A);    // end of the line
		txc(0x0d);   
		txc(0x0A);
		txc(0x26);   // <ctrl+z>
		delay(10000);
	}
}