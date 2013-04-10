/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/


#ifndef __STRING_H_
#define __STRING_H_

//#include <iostream> // do not use iostream as program becomes bulky..
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h> // for free() amd malloc()
#include <string.h> // for strcpy()
#include <ctype.h> // for isspace()
#include <stdio.h> // for sprintf()
//#include <list.h> // for sprintf()
#include <math.h> // for modf(), rint()

//#include "my_malloc.h"
//#include "debug.h" // debug_(name, value)  debug2_(name, value, LOG_YES)

const short INITIAL_SIZE =      50;
const short NUMBER_LENGTH = 70;
const int MAX_ISTREAM_SIZE = 2048;

//class StringBuffer;

// a small class with a VERY MINIMUM of functions and variables...
// This class to be kept small... 
class String
{
        public:
                String();
                String(char bb[]);  // needed by operator+
                String(char bb[], int start, int slength); // subset of chars
                String(char bb[], int start, int slength,String s); // subset of chars

                String(int bb);  // needed by operator+

                String(int,int bb);  // needed by operator+
                String(int,unsigned long bb);  // needed by operator+
                String(int,long bb);  // needed by operator+
                String(int,float bb);  // needed by operator+
                String(int,double bb);  // needed by operator+
                String(const String & rhs);  // Copy Constructor needed by operator+
                //String(StringBuffer sb);  // Java compatibility
                String(int bb, bool dummy);  // for StringBuffer class
                ~String();

                char *val();

                // Functions below imitate Java language's String object 
                unsigned long length();
                char charAt(int where);
                void getChars(int sourceStart, int sourceEnd, 
                                char target[], int targetStart);
                char* toCharArray();
                char* getBytes();
                char* getBytes(char* utf);
                char* getBytes(String utf);

                bool equals(String str2); // See also == operator
                bool equals(char *str2); // See also == operator
                bool equalsIgnoreCase(String str2);

                bool regionMatches(int startIndex, String str2, 
                                int str2StartIndex, int numChars);
                bool regionMatches(bool ignoreCase, int startIndex, 
                                String str2, int str2StartIndex, int numChars);

                String toUpperCase();
                String toLowerCase();

                bool startsWith(String str2);
                bool startsWith(char *str2);

                bool endsWith(String str2);
                bool endsWith(char *str2);

                int compareTo(String str2);
                int compareTo(char *str2);
                int compareToIgnoreCase(String str2);
                int compareToIgnoreCase(char *str2);

                int indexOf(char ch, int startIndex = 0);
                int indexOf(char *str2, int startIndex = 0);
                int indexOf(String str2, int startIndex = 0);

                int lastIndexOf(char ch, int startIndex = 0);
                int lastIndexOf(char *str2, int startIndex = 0);
                int lastIndexOf(String str2, int startIndex = 0);

                String substring(int startIndex, int endIndex = 0);
                String replace(char original, char replacement);
                String replace(char *original, char *replacement);

                String trim(); // See also overloaded trim()

                String concat(String str2);  // See also operator +
                String concat(char *str2); // See also operator +

                String reverse(); // See also overloaded reverse()
                String deleteCharAt(int loc);
                String deleteStr(int startIndex, int endIndex); // Java's "delete()"

                String valueOf(char ch);
                String valueOf(char chars[]);
                String valueOf(char chars[], int startIndex, int numChars);
                String valueOf(bool tf);
                String valueOf(int num);
                String valueOf(long num);
                String valueOf(float num);
                String valueOf(double num);

                // See also StringBuffer class in this file given below

                // ---- End of Java like String object functions -----

                //////////////////////////////////////////////////////
                //              List of additonal functions not in java
                //////////////////////////////////////////////////////
                String ltrim();
                void ltrim(bool dummy); // dummy to get different signature
                String rtrim();
                void rtrim(bool dummy); // dummy to get different signature

                void chopall(char ch='\n'); // removes trailing character 'ch'
                void chop(); // removes one trailing character

                void roundf(float input_val, short precision);
                void decompose_float(long *integral, long *fraction); 

                void roundd(double input_val, short precision);
                void decompose_double(long *integral, long *fraction); 

//                void explode(char *seperator); // see also token() and overloaded explode()
//                String *explode(int & strcount, char seperator = ' '); // see also token()
                void implode(char *glue);
                void join(char *glue);
                String repeat(char *input, unsigned int multiplier);
                String tr(char *from, char *to); // translate characters
                String center(int padlength, char padchar = ' ');
                String space(int number = 0, char padchar = ' ');
                String xrange(char start, char end);
                String compress(char *list = " ");
                String left(int slength = 0, char padchar = ' ');
                String right(int slength = 0, char padchar = ' ');
                String overlay(char *newstr, int start = 0, int slength = 0, char padchar = ' ');

                String at(char *regx); // matches first match of regx
                String before(char *regx); // returns string before regx
                String after(char *regx); // returns string after regx
                String mid(int startIndex = 0, int length = 0);

                bool isNull();  
                bool isInteger();
                bool isInteger(int pos);
                bool isNumeric();
                bool isNumeric(int pos);
                bool isEmpty();  // same as length() == 0
                bool isUpperCase();
                bool isUpperCase(int pos);
                bool isLowerCase();
                bool isLowerCase(int pos);
                bool isWhiteSpace();
                bool isWhiteSpace(int pos);
                bool isBlackSpace();
                bool isBlackSpace(int pos);
                bool isAlpha();
                bool isAlpha(int pos);
                bool isAlphaNumeric();
                bool isAlphaNumeric(int pos);
                bool isPunct();
                bool isPunct(int pos);
                bool isPrintable();
                bool isPrintable(int pos);
                bool isHexDigit();
                bool isHexDigit(int pos);
                bool isCntrl();
                bool isCntrl(int pos);
                bool isGraph();
                bool isGraph(int pos);

                void clear();
                int toInteger();
                int toInteger(int dd);
                long parseLong();

                double toDouble();
                String token(char seperator = ' '); // ref StringTokenizer, explode()
                String crypt(char *original, char *salt);
                //String getline(FILE *infp = stdin); // see also putline()
                //String getline(fstream *infp = stdin); // see also putline()

                void putline(FILE *outfp = stdout); // see also getline()
                //void putline(fstream *outfp = stdout); // see also getline()

                void swap(String aa, String bb); // swap aa to bb
                String *sort(String aa[]);  // sorts array of strings
                String sort(int startIndex = 0, int length = 0);  // sorts characters inside a string
                int freq(char ch); // returns the number of distinct, nonoverlapping matches
                void Format(const char *fmt, ...);
                String replace (int startIndex, int endIndex, String str);

                void substring(int startIndex, int endIndex, bool dummy);
                void reverse(bool dummy); // dummy to get different signature
                String deleteCharAt(int loc, bool dummy);
                String deleteStr(int startIndex, int endIndex, bool dummy);
                void trim(bool dummy); // dummy to get different signature
                String insert(int index, String str2);
                String insert(int index, String str2, bool dummy);
                String insert(int index, char ch);
                String insert(int index, char ch, bool dummy);
                String insert(char *newstr, int start = 0, int length = 0, char padchar = ' ');

                // required by java's StringBuffer
                void ensureCapacity(int capacity);
                void setLength(int len);
                void setCharAt(int where, char ch);

                // required by java's Integer class, Long, Double classes
                int parseInt(String ss);
                int parseInt(String ss,int dd);
                int parseInt(char *ss);
                int parseInt(char *ss,int dd);
                long parseLong(String ss);
                long parseLong(char *ss);
                float floatValue();
                double doubleValue();

                ///////////////////////////////////////////////
                //              List of duplicate function names
                ///////////////////////////////////////////////
                // char * c_str() // use val()
                // bool find();  // Use regionMatches()
                // bool search();  // Use regionMatches()
                // bool matches(); // Use regionMatches()
                // int rindex(String str2, int startIndex = 0); Use lastIndexOf()
                // String blanks(int slength);  // Use repeat()
                // String append(String str2); // Use concat() or + operator
                // String prepend(String str2);  // Use + operator. See also append()
                // String split(char seperator = ' ');  // Use token()
                bool contains(char *str2, int startIndex = 0); // use indexOf()
                // void empty(); Use is_empty()
                // void vacuum(); Use clear()
                // void erase(); Use clear()
                // void zero(); Use clear()
                // bool is_float(); Use is_numeric();
                // bool is_decimal(); Use is_numeric();
                // bool is_Digit(); Use is_numeric();
                // float float_value(); Use toDouble();
                // float tofloat(); Use toDouble();
                // double double_value(); Use toDouble();
                // double numeric_value(); Use toDouble();
                // int int_value(); Use toInteger()
                // int tonumber(); Use toInteger()
                // String get(); Use substring() or val() but prefer java's substring
                // String getFrom(); Use substring() or val() but prefer java's substring
                // String head(int len); Use substring(0, len)
                // String tail(int len); Use substring(length()-len, length())
                // String cut(); Use deleteCharAt() or deleteStr()
                // String cutFrom(); Use deleteCharAt() or deleteStr()
                // String paste(); Use insert()
                // String fill(); Use replace()
                // char firstChar(); // Use substring(0, 1);
                // char lastChar(); // Use substring(length()-1, length());
                // String findNext(); Use token()

                // begin();  iterator. Use operator [ii]
                // end();  iterator. Use operator [ii]
                // copy();  Use assignment =  operator, String aa = bb;
                // clone();  Use assignment =  operator, String aa = bb;

                // All Operators ...
                String operator+ (const String & rhs);
                friend String operator+ (const String & lhs, const String & rhs);

                String& operator+= (const String & rhs); // using reference will be faster

                String& operator= (const String & rhs); // using reference will be faster
                String& operator= (String * rhs); // using reference will be faster


                operator char*(); // using reference will be faster

                bool operator== (const String & rhs); // using reference will be faster
                bool operator== (const char *rhs);
                bool operator!= (const String & rhs);
                bool operator!= (const char *rhs); 
                char operator [] (unsigned long Index) const;
                char& operator [] (unsigned long Index);
//                friend ostream &  operator<< (ostream & Out, const String & str2);
//               friend istream &  operator>> (istream & In, String & str2);

//                static  list<String>                 explodeH;  // list head

        protected:
                char *sval; // Not safe to make sval public
                inline void verifyIndex(unsigned long index) const;
                inline void verifyIndex(unsigned long index, char *aa) const;

                void _str_cat(char bb[]);
                void _str_cat(int bb);
                void _str_cat(unsigned long bb);
                void _str_cat(float bb);

        private:
                // Note: All the private variables and functions begin
                // with _ (underscore)
                
                //static String *_global_String; // for use in add operator
                //inline void _free_glob(String **aa);
                void _no_null();
                void _str_cpy(char bb[]);
                void _str_cpy(int bb); // itoa
                void _str_cpy(unsigned long bb);
                void _str_cpy(float bb); // itof

                bool _equalto(const String & rhs, bool type = false);
                bool _equalto(const char *rhs, bool type = false);
                String *_pString;  // temporary pointer for internal use..
                inline void _allocpString();
                inline void _reverse();
                inline void _deleteCharAt(int loc);
                inline void _deleteStr(int startIndex, int endIndex);
                inline void _trim();
                inline void _ltrim();
                inline void _rtrim();
                inline void _substring(int startIndex, int endIndex);
};


//String& operator= (char* p,String& rhs);


//static String Integer("0"); // java's Integer.parseInt(String);
class MyInteger:public String
{
	public:
		MyInteger(String str);
		String toHexString(int a);
};
static MyInteger Integer((char*)"0");



static String Long((char*)"0"); // java's Long.parseLong(String);

// Imitate java's Float class and Float.floatValue()
// provided to compile java code in C++
class Float: public String
{
        public:
                Float(String str);
                Float valueOf(String str2);
                float floatValue();
};

// Imitate java's Double class and Double.doubleValue()
// provided to compile java code in C++
class Double: public String
{
        public:
                Double(String str);
                Double valueOf(String str2);
                double doubleValue();
};



// Global variables are defined in String.cpp

#endif // __STRING_H_

