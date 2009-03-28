#pragma once

using namespace System;

namespace MACSCrypt
{
	public enum class CALGORITHM
	{DES,AES,DES3,AES3};
	public enum class CMODE
	{ECB,CBC,CFB,OFB,CTR,AMPM1,AMPM2};

	public ref class CMACSCrypt
	{
		Crypt *MACSCrypt;
		int hashLength;
		static int length, process;
		static bool crypting, convertTxt, readingLength;
		//char *Buffer;
		char* ReadBuffer(char*,int&);
		void CopyKey(const char*, char*);
		void XOR(char* a, char* b,char* c);
		void AddHex(char* key,char Add);
		void RunAlgorithm(int);
		void String_To_char(String^, char*,bool);
		String^ char_To_String(char*, int,bool);
		void Shift(const char*, char*, int,int);
		
	public:
		CALGORITHM Algorithm;
		CMODE Mode;
		CMACSCrypt();
		~CMACSCrypt();
		int getKeyLength();
		bool wFile(char*,char*,char*,bool);
		String^ MACSEncrypt(String^,String^,int,int);
		String^ MACSDecrypt(String^,String^,int,int);
		char* MACSEncrypt(char*,const char*,int,int);
		char* MACSDecrypt(char*,const char*,int,int);
		char* MACSGenerateKey(bool,bool);

		static int getLength() {return length;}
		static int getProcess() {return process;}
		static bool getReadingLength() {return readingLength;}
		static bool getConvertTxt() {return convertTxt;}
		static bool getCrypting() {return crypting;}
	};
}