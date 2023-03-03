#include<stc8h.h>
void initS()
{
	P1M0&=0xfc;
	P1M1&=0xfc;
	P1|=0x03;
	P_SW2&=0xfe;
	S2CON=0x52;
	AUXR|=0x04;
	T2L=0xE8;
	T2H=0xFF;
	AUXR|=0x10;
}
char readS_nb(char* _buf)
{
	if(S2CON&0x01)
	{
		*(_buf)=S2BUF;
		S2CON&=0xfe;
		return 0;
	}
	else
	{
		return 1;
	}
}
char readS()
{
	char _tmpbuf;
	while(readS_nb(&_tmpbuf));
	return _tmpbuf;
}
void writeS(char _wtr)
{
	while(!(S2CON&0x02));
	S2CON&=0xfd;
	S2BUF=_wtr;
}
void initM()
{
	P2M0|=0x80;
	P2M1&=0x7f;
	P2&=0x7f;
	ADC_CONTR|=0x88;
	ADC_CONTR&=0xc8;
	ADCCFG|=0x20;
	ADCCFG&=0xf0;
}
char readADC_nb(int* _buf1)
{
	if(ADC_CONTR&0x20)
	{
		*((char*)_buf1)=ADC_RES;
		*((char*)_buf1+1)=ADC_RESL;
		ADC_CONTR&=0xdf;
		return 0;
	}
	else
	{
		return 1;
	}
}
int readADC()
{
	int _tmpbuf1;
	ADC_CONTR|=0x40;
	while(readADC_nb(&_tmpbuf1));
	return _tmpbuf1;
}
char readIO(char _ioid,char _bitid)
{
	if(_ioid==0)
	{
		return (P0>>_bitid)&0x01;
	}
	else if(_ioid==1)
	{
		return (P1>>_bitid)&0x01;
	}
	else if(_ioid==2)
	{
		return (P2>>_bitid)&0x01;
	}
	else
	{
		return -1;
	}
}
void writeIO(char _ioid1,char _bitid1,char _wtrbit)
{
	if(_ioid1==0)
	{
		if(_wtrbit)
		{
			P0|=0x01<<_bitid1;
		}
		else
		{
			P0&=~(0x01<<_bitid1);
		}
	}
	else if(_ioid1==1)
	{
		if(_wtrbit)
		{
			P1|=0x01<<_bitid1;
		}
		else
		{
			P1&=~(0x01<<_bitid1);
		}
	}
	else if(_ioid1==2)
	{
		if(_wtrbit)
		{
			P2|=0x01<<_bitid1;
		}
		else
		{
			P2&=~(0x01<<_bitid1);
		}
	}
}
void trADC()
{
	int _temp=readADC();
	writeS(_temp&0x00ff);
	writeS(_temp>>8);
}
void main()
{
	char temp;
	initM();
	initS();
	while(1)
	{
		temp=readS();
		if(temp=='B')
		{
			writeIO(2,7,1);
		}
		else if(temp=='E')
		{
			writeIO(2,7,0);
		}
		else if(temp=='V')
		{
			trADC();
		}
		else if(temp=='H')
		{
			writeS(readIO(2,6));
		}
		else if(temp=='M')
		{
			writeS(readIO(2,5));
		}
		else if(temp=='L')
		{
			writeS(readIO(2,4));
		}
	}
}