/*#######################################
 #	MACSCrypt [MACSptian Crypto System]	#
 #	By : Amahdy [www.amahdy.com]		#
 #######################################*/

#include "Stdafx.h"
#include <time.h>

using namespace MACSCrypt;
using namespace std;

int CMACSCrypt::getKeyLength() 
{ 
	int modKeyLength=(Mode==CMODE::ECB)?1:2;
	int algKeyLength;
	switch(Algorithm)
	{ 
		case CALGORITHM::DES:algKeyLength=8;break;
		case CALGORITHM::AES:algKeyLength=16;break;
		case CALGORITHM::DES3:algKeyLength=16;break;
		case CALGORITHM::AES3:algKeyLength=32;break; 
	}
	return algKeyLength*modKeyLength;
}
void CMACSCrypt::String_To_char(String^ str, char* chStr,bool ANSI)
{
	convertTxt=true;
	char temp[8];
	unsigned char t;
	int number;
	int E=(ANSI)?1:2;
	for(int i=0 ; i<str->Length;i++)
	{
		number = (int)str[i]; 
		for(int j=0; j<E; j++)
		{
			for(int z=0;z<8;z++)
				temp[z]=0;
			for(int z=0; z<8; z++, number /=2)
				temp[7-z] = (number%2)?1:0;
			t =128*temp[0]+64*temp[1]+32*temp[2]+16*temp[3]+8*temp[4]+4*temp[5]+2*temp[6]+temp[7];
			chStr[(i*E)+j] =(char)t;
		}
	}
	convertTxt=false;
}
String^ CMACSCrypt::char_To_String(char* ch, int charLenght, bool ANSI)
{
	convertTxt=true;
	String^ str="";
	Char wch;
	if(!ANSI)
		for(int i=0; i<charLenght; i++)
		{
			wch =(unsigned char)ch[i];
			wch +=256*(unsigned char)ch[++i];
			str +=(wchar_t) wch;
		}
	else
		for(int i=0; i<charLenght; i++)
		{
			wch =(unsigned char)ch[i];
			str +=(wchar_t) wch;
		}
	convertTxt=false;
	return str;
}
char* CMACSCrypt::MACSGenerateKey(bool IncludeNumbers,bool IncludeSpecialChars)
{
	int keyLength=getKeyLength();
	char *validchars="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_!@#$%&*()-=+/";
	int start=(IncludeNumbers)?0:10;
	int end=(IncludeSpecialChars)?76:62;
	char *key=new char[keyLength+1];
	srand((unsigned)time(NULL));
	for(int i=0; i<keyLength; i++)
		key[i]=validchars[(int)(rand()%(end-start))+start];
	key[keyLength]=0;
	return key;
}
String^ CMACSCrypt::MACSEncrypt(String^ Input,String^ Key, int NumberOfRounds, int Length)
{
	int len=Key->Length;
	bool ANSI=true;
	for(int i=0; i<len; i++)
		if(Key[i]>254)
		{
			ANSI=false;
			len *=2;
			break;
		}
	char *key=new char[len];
	String_To_char(Key,key,ANSI);

	switch(Algorithm)
	{
		case CALGORITHM::DES:hashLength=8;break;
		case CALGORITHM::DES3:hashLength=8;break;
		case CALGORITHM::AES:hashLength=16;break;	
		case CALGORITHM::AES3:hashLength=16;break;
		default: /*algorithm not implemented yet.*/	;
	}
	len=Input->Length*2;
	len+=hashLength-(len%hashLength);
	char *input=new char[len];
	for(int i=0; i<len; i++)input[i]=0;
	String_To_char(Input,input,false);

	if(Length)
	{
		char* cipher=MACSEncrypt(input,key,NumberOfRounds,len);
		String^ str = char_To_String(cipher,len,false);
		delete[] key;
		delete[] input;
		delete[] cipher;
		return str;
	}else
	{
		char* cipher=MACSEncrypt(input,key,NumberOfRounds,0);
		String^ str = char_To_String(cipher,len,false);
		delete[] key;
		delete[] input;
		delete[] cipher;
		return str;
	}
}
String^ CMACSCrypt::MACSDecrypt(String^ Input,String^ Key, int NumberOfRounds, int Length)
{
	int len=Key->Length;
	bool ANSI=true;
	for(int i=0; i<len; i++)
		if(Key[i]>254)
		{
			ANSI=false;
			len *=2;
			break;
		}
	char *key=new char[len];
	String_To_char(Key,key,ANSI);

	switch(Algorithm)
	{
		case CALGORITHM::DES:hashLength=8;break;
		case CALGORITHM::DES3:hashLength=8;break;
		case CALGORITHM::AES:hashLength=16;break;	
		case CALGORITHM::AES3:hashLength=16;break;
		default: /*algorithm not implemented yet.*/	;
	}
	len=Input->Length*2;
	len += hashLength-(len%hashLength);
	char *input=new char[len];
	for(int i=0; i<len; input[i++]=0);
	String_To_char(Input,input,false);

	if(Length)
	{
		char* cipher=MACSDecrypt(input,key,NumberOfRounds,len);
		String^ str = char_To_String(cipher,len,false);
		delete[] key;
		delete[] input;
		delete[] cipher;
		return str;
	}else
	{
		char* cipher=MACSDecrypt(input,key,NumberOfRounds,0);
		String^ str = char_To_String(cipher,len,false);
		delete[] key;
		delete[] input;
		delete[] cipher;
		return str;
	}}
char* CMACSCrypt::MACSEncrypt(char *Input, const char *Key, int NumberOfRounds, int Length)
{
	crypting=true;
	RunAlgorithm(NumberOfRounds);
	char *Buffer=ReadBuffer(Input, Length);
	char *xBuffer=new char[Length+1];
	char *xored=new char[hashLength];	
	char* nextKey=new char[hashLength];
	//char* thisBuff;
	switch(Mode)
	{
	default:case 0: //ECB [Electronic Code Book]
		MACSCrypt->KeyGen(Key);
		for(process=0; process<length; process++)
		{
			CopyKey(MACSCrypt->Encrypt(Buffer+(process*hashLength)),xBuffer+(process*hashLength));
		}
		break;
	case 1:			//CBC [Cipher Block Chaining]
		MACSCrypt->KeyGen(Key);
		CopyKey(Key+hashLength,nextKey);
		for(process=0; process<length; process++)
		{
			XOR(Buffer+(process*hashLength),nextKey,xored);
			CopyKey(MACSCrypt->Encrypt(xored),xBuffer+(process*hashLength));
			CopyKey(xBuffer+(process*hashLength),nextKey);
		}
		break;
	case 2:			//CFB [Cipher Feed Back]
		MACSCrypt->KeyGen(Key);
		CopyKey(Key+hashLength,nextKey);
		for(process=0; process<length; process++)
		{
			XOR(Buffer+(process*hashLength),MACSCrypt->Encrypt(nextKey),xored);
			CopyKey(xored,xBuffer+(process*hashLength));
			CopyKey(xBuffer+(process*hashLength),nextKey);
		}
		break;
	case 3:			//OFB [Output Feed Back]
		MACSCrypt->KeyGen(Key);
		CopyKey(Key+hashLength,nextKey);
		for(process=0; process<length; process++)
		{
			nextKey=MACSCrypt->Encrypt(nextKey);
			XOR(nextKey,Buffer+(process*hashLength),xored);
			CopyKey(xored,xBuffer+(process*hashLength));
		}
		break;
	case 4:			//CTR [Counter]
		MACSCrypt->KeyGen(Key);
		CopyKey(Key+hashLength,nextKey);
		for(process=0; process<length; process++)
		{
			XOR(MACSCrypt->Encrypt(nextKey),Buffer+(process*hashLength),xored);
			CopyKey(xored,xBuffer+(process*hashLength));
			AddHex(nextKey,0x01);
		}
		break;
	case 5:			//AMPM 1
		{
			int kLen=getKeyLength();
			char *xKey=new char[kLen];
			const char *xx=Key;
			Shift(Key,xKey,NumberOfRounds,kLen);
			MACSCrypt->KeyGen(xKey);
			for(process=0; process<length; process++)
			{
				CopyKey(MACSCrypt->Encrypt(Buffer+(process*hashLength)),xBuffer+(process*hashLength));
			}
			delete[] xKey;
			break;
		}
	case 6:			//AMPM 2
		MACSCrypt->KeyGen(Key);
		CopyKey(Key+hashLength,nextKey);
		for(process=0; process<length; process++)
		{
			XOR(MACSCrypt->Encrypt(nextKey),Buffer+(process*hashLength),xored);
			CopyKey(xored,xBuffer+(process*hashLength));
			AddHex(nextKey,Key[process%hashLength]);
		}
		break;
	}
	delete MACSCrypt;
	delete[] Buffer;
	delete[] nextKey;
	delete[] xored;
	xBuffer[Length]=0;
	crypting=false;
	return xBuffer;
}
char* CMACSCrypt::MACSDecrypt(char *Input, const char *Key, int NumberOfRounds, int Length)
{
	crypting=true;
	RunAlgorithm(NumberOfRounds);
	char *Buffer=ReadBuffer(Input, Length);
	char *xBuffer=new char[Length+1];
	char *xored=new char[hashLength];	
	char* nextKey=new char[hashLength];
	switch(Mode)
	{
	default:case 0: //ECB [Electronic Code Book]
		MACSCrypt->KeyGen(Key);
		for(process=0; process<length; process++)
		{
			CopyKey(MACSCrypt->Decrypt(Buffer+(process*hashLength)),xBuffer+(process*hashLength));
		}
		break;

	case 1:			//CBC [Cipher Block Chaining]
		MACSCrypt->KeyGen(Key);
		CopyKey(Key+hashLength,nextKey);
		for(process=0; process<length; process++)
		{
			XOR(MACSCrypt->Decrypt(Buffer+(process*hashLength)),nextKey,xored);
			CopyKey(xored,xBuffer+(process*hashLength));
			CopyKey(Buffer+(process*hashLength),nextKey);
		}
		break;

	case 2:			//CFB [Cipher Feed Back]
		MACSCrypt->KeyGen(Key);
		CopyKey(Key+hashLength,nextKey);
		for(process=0; process<length; process++)
		{
			XOR(Buffer+(process*hashLength),MACSCrypt->Encrypt(nextKey),xored);
			CopyKey(xored,xBuffer+(process*hashLength));
			CopyKey(Buffer+(process*hashLength),nextKey);
		}
		break;

	case 3:			//OFB [Output Feed Back]
		MACSCrypt->KeyGen(Key);
		CopyKey(Key+hashLength,nextKey);
		for(process=0; process<length; process++)
		{
			nextKey=MACSCrypt->Encrypt(nextKey);
			XOR(nextKey,Buffer+(process*hashLength),xored);
			CopyKey(xored,xBuffer+(process*hashLength));
		}
		break;
	case 4:			//CTR [Counter]
		MACSCrypt->KeyGen(Key);
		CopyKey(Key+hashLength,nextKey);
		for(process=0; process<length; process++)
		{
			XOR(MACSCrypt->Encrypt(nextKey),Buffer+(process*hashLength),xored);
			CopyKey(xored,xBuffer+(process*hashLength));
			AddHex(nextKey,0x01);
		}
		break;
	case 5:		//AMPM 1
		{
			int kLen=getKeyLength();
			char *xKey=new char[kLen];
			Shift(Key,xKey,NumberOfRounds,kLen);
			MACSCrypt->KeyGen(xKey);
			for(process=0; process<length; process++)
			{
				CopyKey(MACSCrypt->Decrypt(Buffer+(process*hashLength)),xBuffer+(process*hashLength));
			}
			delete[] xKey;
			break;
		}
	case 6:			//AMPM 2
		MACSCrypt->KeyGen(Key);
		CopyKey(Key+hashLength,nextKey);
		for(process=0; process<length; process++)
		{
			XOR(MACSCrypt->Encrypt(nextKey),Buffer+(process*hashLength),xored);
			CopyKey(xored,xBuffer+(process*hashLength));
			AddHex(nextKey,Key[process%hashLength]);
		}
		break;
	}
	delete MACSCrypt;
	delete[] Buffer;
	delete[] nextKey;
	delete[] xored;
	xBuffer[Length]=0;
	crypting=false;
	return xBuffer;
}
bool CMACSCrypt::wFile(char* Input, char* path, char* Opath,bool encrypt)
{
	int Length=0;
	ReadBuffer(Opath,Length);
	int l=-1;
	while(path[++l]);
	ofstream file;
	file.open(path,ios::out|ios::binary);
	if(!file)
		return false;
	file.write(Input,Length);
	file.close();
	return true;
}

/*	==============================================
	BUFFER READER
	>load the data into the memory to start 
	 encrypt/decrypt it, 'Length' is :
		ZERO: the buffer is passed by a file path
		O.W.: the buffer is passed directly
	 the return will be a multiple of hashLength.
	==============================================	*/
char* CMACSCrypt::ReadBuffer(char* Input, int& Length)
{
	readingLength=true;
	if(!Length)
	{
		//implement a file reader
		ifstream file;
		file.open(Input,ios::in|ios::binary);
		if(!file)
			return "File Error!";
		file.seekg(0,ios::end);
		Length=file.tellg();
		file.seekg(0,ios::beg);
		char* retVal=new char[Length];
		file.read(retVal,Length);
		file.close();
		return ReadBuffer(retVal,Length);
	}
	else
	{
		int exeed=Length%hashLength;
		if(exeed)
		{
			Length+=(hashLength-exeed);
			char *retVal=new char[Length];
			int i=0;
			for(; i<Length-(hashLength-exeed); retVal[i]=Input[i++]);
			for(; i<Length; retVal[i++]=0);
			length=Length/hashLength;
			delete[] Input;
			readingLength=false;
			return retVal;
		}
		else
		{
			length=Length/hashLength;
			readingLength=false;
			return Input;
		}
	}
}
void CMACSCrypt::CopyKey(const char* data,char* retVal)
{
	for(int i=0; i<hashLength; i++)
		retVal[i]=data[i];
	return;
}
void CMACSCrypt::XOR(char* a, char* b,char* c)
{
	for(int i=0; i<hashLength; i++)
		c[i]=a[i]^b[i];
}
void CMACSCrypt::AddHex(char* key,char Add)
{
	for(int x=hashLength-1; x>=0; x--)
	{
		if((int)key[x] + (int)Add<128)
		{
			key[x] += Add;
			break;
		}
		else
		{
			Add += key[x]- 128;
			key[x]=127;
		}
		if(!x)
		{
			for(int i=0; i<hashLength-1; key[i++]=0);
			key[hashLength]=1;
			x=hashLength-1;
		}
		
	}
}
void CMACSCrypt::RunAlgorithm(int NumberOfRounds)
{
	switch(Algorithm)
	{
	case CALGORITHM::DES:
		MACSCrypt=new CDES(NumberOfRounds);
		hashLength=8;
		break;
	case CALGORITHM::AES:
		MACSCrypt=new CAES(NumberOfRounds);
		hashLength=16;
		break;
	case CALGORITHM::DES3:
		MACSCrypt=new CDES3(NumberOfRounds);
		hashLength=8;
		break;
	case CALGORITHM::AES3: //NEW!
		MACSCrypt=new CAES3(NumberOfRounds);
		hashLength=16;
		break;
	default:
		//algorithm not implemented yet.
		;
	}
	return;
}
void CMACSCrypt::Shift(const char *key,char *xKey, int shift,int keyLen)
{
	shift %=keyLen;
	int len=keyLen-shift;
	char *sh=new char[shift];
	int i,j;
	for(i=0; i<shift; i++)
		sh[i]=key[i];
	for(j=0; j<len; j++,i++)
		xKey[j]=key[i];		
	for(i=0; j<keyLen; j++,i++)
		xKey[j]=sh[i];
	delete[] sh;
}
CMACSCrypt::CMACSCrypt()
{
	Algorithm=CALGORITHM::AES;
	Mode=CMODE::ECB;
	return;
}
CMACSCrypt::~CMACSCrypt()
{
	return;
}