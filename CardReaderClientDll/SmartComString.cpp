#include "stdafx.h"

// #define SMARTCOMSTRING_EXPORTS_MACRO
// #define CARDREADERCLIENTDLL_EXPORTS

#include "SmartComString.h"

#define  INCREMENT (31)
using namespace SmartCom;

    string::string()
	{
		m_nlength=0;
		m_pData=new char[INCREMENT+1];
		m_pData[0]='\0';
		size=INCREMENT+1;
	}

	string::string(const char* str)
	{
		if(str!=0)
		{
            m_nlength=strlen(str);
			m_pData=new char[m_nlength+1+INCREMENT];
			size=m_nlength+1+INCREMENT;
     	    strcpy(m_pData,str);
		}
		else
		{
			m_nlength=0;
			m_pData=new char[INCREMENT+1];
			m_pData[0]='\0';
		    size=INCREMENT+1;
		}			
	}

	string::string(const string& rs)
	{
        m_nlength=rs.m_nlength;
		m_pData=new char[m_nlength+1+INCREMENT];
		size=m_nlength+1+INCREMENT;
		strcpy(m_pData,rs.m_pData);
	}

	string::~string()
	{
		delete[] m_pData;
	}

	string& string::operator =(const char* str)
	{
		if(0==str)
			return *this;
		int len=strlen(str);
		if(size-1<len)
		{
			delete[] m_pData;
			m_pData=new char[len+1+INCREMENT];
			size=len+1+INCREMENT;
		}
		m_nlength=len;
		strcpy(m_pData,str);
		return *this;
	}
	
	string& string::operator =(const string& rs)
	{
		if(this==&rs)
			return *this;
		int len=rs.m_nlength;
		if(size-1<len)
		{
			delete[] m_pData;
			m_pData=new char[len+1+INCREMENT];
			size=len+1+INCREMENT;
		}
		m_nlength=len;
		strcpy(m_pData,rs.m_pData);
		return *this;
	}

	string& string::operator +=(const char* str)
	{
		if(0==str)
			return *this;
		int len=strlen(str);
		if(size-1<len+m_nlength)
		{
			char *temp=new char[len+m_nlength+1+INCREMENT];
			strcpy(temp,m_pData);
			delete[] m_pData;
			m_pData=temp;
			size=len+m_nlength+1+INCREMENT;
		}
		m_nlength+=len;
		strcat(m_pData,str);
		return *this;
	}

	string& string::operator +=(const string& rs)
	{
        int len=rs.m_nlength;
		if(size-1<len+m_nlength)
		{
			char *temp=new char[len+m_nlength+1+INCREMENT];
			strcpy(temp,m_pData);
			delete[] m_pData;
			m_pData=temp;
			size=len+m_nlength+1+INCREMENT;
		}
		m_nlength+=len;
		strcat(m_pData,rs.m_pData);
		return *this;
	}

	string string::operator +(const char* str)
	{
		if(0==str)
			return *this;
		string temp(*this);
		temp+=str;
		return temp;
	}

	void string::append(const string& rs)
	{
		(*this)+=rs;
	}

	void string::append(const char* str)
	{
		(*this)+=str;
	}
	
	string string::operator +(const string& rs)
	{
		string temp(*this);
		temp+=rs;
		return temp;
	}

	char& string::operator [](int i)
	{
		if(i<0)
			i=0;
		if(i>m_nlength-1)
			i=m_nlength-1;
		return *(m_pData+i);
	}

	const char* string::c_str()
	{
		return m_pData;
	}

	int string::length()
	{
		return m_nlength;
	}

	SMARTCOMSTRING_API string SmartCom::operator +(const char* ch,const string&rs)
	{
		string temp;
		temp+=ch;
		temp+=rs;
		return temp;
	}

	bool string::operator ==(const char* ch)
	{
		if(ch==0)
			return false;
		int j=strlen(ch);
		if(m_nlength!=j)
			return false;
		for(int i=0;i<j;i++)
		{
			if(*(m_pData+i)!=*(ch+i))
				return false;
		}
		return true;
	}

	bool string::operator !=(const char* ch)
	{
		if(ch==0)
			return true;
		int j=strlen(ch);
		if(m_nlength!=j)
			return true;
		for(int i=0;i<j;i++)
		{
			if(*(m_pData+i)!=*(ch+i))
				return true;
		}
		return false;
	}

	bool string::operator ==(const string& rs)
	{
		if(m_nlength!=rs.m_nlength)
			return false;
		for(int i=0;i<m_nlength;i++)
		{
			if(*(m_pData+i)!=*(rs.m_pData+i))
				return false;
		}
		return true;
	}

	bool string::operator !=(const string& rs)
	{
		if(m_nlength!=rs.m_nlength)
			return true;
		for(int i=0;i<m_nlength;i++)
		{
			if(*(m_pData+i)!=*(rs.m_pData+i))
				return true;
		}
		return false;
	}


	SMARTCOMSTRING_API bool SmartCom::operator ==(const char* ch,const string& rs)
	{
		string temp=rs;
		if(temp==ch)
			return true;
		return false;
	}

	SMARTCOMSTRING_API bool SmartCom::operator !=(const char* ch,const string& rs)
	{
		string temp=rs;
		if(temp!=ch)
			return true;
		return false;
	}

