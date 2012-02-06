#ifndef __SmartComString_H__
#define __SmartComString_H__

#ifdef SMARTCOMSTRING_EXPORTS_MACRO
#define SMARTCOMSTRING_API __declspec(dllexport)
#else
#define SMARTCOMSTRING_API __declspec(dllimport)
#endif

namespace SmartCom{
  	class SMARTCOMSTRING_API string{
	public:
		 string();
		 string(const char* str);
		 string(const string& s);
		
		 ~string();

		string& operator=(const char* ch);
		string& operator=(const string& rs);
		string& operator+=(const char* ch);
		string& operator+=(const string& rs);
		inline string operator+(const char* ch);
		inline string operator+(const string& rs);
		bool operator==(const char* ch);
		bool operator==(const string&rs);
		bool operator!=(const char* ch);
		bool operator!=(const string&rs);
		friend SMARTCOMSTRING_API string operator+(const char* ch,const string& rs);
		friend SMARTCOMSTRING_API bool operator ==(const char* ch,const string& rs);
		friend SMARTCOMSTRING_API bool operator !=(const char* ch,const string& rs);
		
        inline const char* c_str();//返回c形式的字符串
	   	inline int length();
	    inline void append(const char* str);
	   	inline void append(const string& rs);

	private:
		int m_nlength;  //字符串长度
		int size; //目前拥有的内存大小
		char* m_pData;
		inline char& operator[](int i);

		
	};

}

#endif