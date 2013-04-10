/******* BEGIN LICENCE BLOCK *******

    NanoJsonHttpd
    Copyright (C) 2012 Yomei.
    yomei.otani@gmail.com

    This program is free software; you can redistribute it and/or modify it under the terms of the BSD License.

******* END LICENCE BLOCK *******/

#include "String_.h"

#ifdef _MSC_VER
#if _MSC_VER >= 1400
#pragma warning( disable : 4996 )
#pragma warning( disable : 4819 )
#endif
#endif


// for Visual Studio 6 , Visual Studio 2002 ,Visual Studio 2003
#if defined(_MSC_VER) && (_MSC_VER<1700)
static int snprintf(char * buf,size_t n,const char *format,...)
{
	int ret;
	va_list ap;
    va_start(ap, format);
    ret = vsprintf(buf,format, ap);
    va_end(ap);
	return ret;
}
#endif

static void mystrcpy(char* d,char* s){
	if(s==NULL || d==NULL)return;
	while(*s)*d++=*s++;
	*d=0;
}
static void mystrcat(char* d,char* s){
	if(s==NULL || d==NULL)return;
	while(*d)d++;
	while(*s)*d++=*s++;
	*d=0;
}

// Global variables ....
//String *String::_global_String = NULL; // global var

//list<String>                 String::explodeH;

String::String()
{
        ////debug("In cstr()", "ok");
        sval = (char *) malloc(sizeof(char)* INITIAL_SIZE);
		sval[0]=0;
        _pString = NULL;
}

String::String(char *bb)
{
        unsigned long tmpii = (unsigned long)strlen(bb);
        sval = (char *) malloc(sizeof(char)* tmpii+1);
        strncpy(sval, bb, tmpii);
        sval[tmpii] = '\0';

        //debug("In cstr(char *bb) bb", bb);
        //debug("In cstr(char *bb) sval", sval);
        #ifdef DEBUG
                //fprintf(stderr, "\nAddress of sval=%x\n", & sval);
                //fprintf(stderr, "\nAddress of this-pointer=%x\n", this);
        #endif // DEBUG

        _pString = NULL;
}

String::String(char *bb, int start, int slength)
{
        unsigned long tmpii = (unsigned long)strlen(bb);
        if (start > (int) tmpii || start < 0)
        {
                //cerr << "\nString(char *, int, int) - start is  out of bounds!!\n" << endl;
                exit(1);
        }
        sval = (char *) malloc(sizeof(char)* slength+1);
        strncpy(sval, & bb[start], slength);
        sval[slength] = '\0';

        ////debug("In cstr(char *bb) bb", bb);
        //debug("In cstr(char *bb) sval", sval);
        #ifdef DEBUG
                //fprintf(stderr, "\nAddress of sval=%x\n", & sval);
                //fprintf(stderr, "\nAddress of this-pointer=%x\n", this);
        #endif // DEBUG

        _pString = NULL;
}

String::String(char *bb, int start, int slength,String s)
{
        unsigned long tmpii = (unsigned long)strlen(bb);
        if (start > (int) tmpii || start < 0)
        {
                //cerr << "\nString(char *, int, int) - start is  out of bounds!!\n" << endl;
                exit(1);
        }
        sval = (char *) malloc(sizeof(char)* slength+1);
        strncpy(sval, & bb[start], slength);
        sval[slength] = '\0';

        ////debug("In cstr(char *bb) bb", bb);
        //debug("In cstr(char *bb) sval", sval);
        #ifdef DEBUG
                //fprintf(stderr, "\nAddress of sval=%x\n", & sval);
                //fprintf(stderr, "\nAddress of this-pointer=%x\n", this);
        #endif // DEBUG

        _pString = NULL;
}

String::String(int a)
{
        sval = NULL;
        _pString = NULL;
}

String::String(int a,int bb)
{
        sval = (char *) malloc(NUMBER_LENGTH); // integers 70 digits max
        snprintf(sval,NUMBER_LENGTH, "%d", bb);
        //debug("In cstr(int bb) sval", sval);

        _pString = NULL;
}

String::String(int a,unsigned long bb)
{
        sval = (char *) malloc(NUMBER_LENGTH); // long 70 digits max
        snprintf(sval,NUMBER_LENGTH, "%lu", bb);
        //debug("In cstr(unsigned long bb) sval", sval);

        _pString = NULL;
}

String::String(int a,long bb)
{
        sval = (char *) malloc(NUMBER_LENGTH); // long 70 digits max
        snprintf(sval, NUMBER_LENGTH,"%ld", bb);
        //debug("In cstr(long bb) sval", sval);

        _pString = NULL;
}

String::String(int a,float bb)
{
        sval = (char *) malloc(NUMBER_LENGTH); // float 70 digits max
        snprintf(sval,NUMBER_LENGTH, "%f", bb);
        //debug("In cstr(float bb) sval", sval);

        _pString = NULL;
}

String::String(int a,double bb)
{
        sval = (char *) malloc(NUMBER_LENGTH); // double 70 digits max
        snprintf(sval,NUMBER_LENGTH, "%f", bb);
        //debug("In cstr(double bb) sval", sval);

        _pString = NULL;
}

// Copy Constructor needed by operator +
String::String(const String & rhs)
{
        // Do a deep-copy instead of compiler's default shallow copy copy-cstr
        //debug("In copy-cstr()", "ok");
	if(rhs.sval){
        unsigned long tmpii = (unsigned long)strlen(rhs.sval);
        sval = (char *) malloc(sizeof(char)* tmpii+1);
        strncpy(sval, rhs.sval, tmpii);
        sval[tmpii] = '\0';
	}else{
		sval=NULL;
	}
        _pString = NULL;
}


// For use by StringBuffer class. Put a dummy
// variable for different signature.
// StringBuffer class imitates Java's StringBuffer object
String::String(int size, bool dummy)
{
        sval = (char *) malloc(sizeof(char)* size);
        //debug("In cstr(int size, bool dummy) sval", sval);
        #ifdef DEBUG
                //fprintf(stderr, "\nAddress of sval=%x\n", & sval);
                //fprintf(stderr, "\nAddress of this-pointer=%x\n", this);
        #endif // DEBUG

        _pString = NULL;
}

String::~String()
{
        //debug("In dstr sval", sval);
        #ifdef DEBUG
                //fprintf(stderr, "\nAddress of sval=%x\n", & sval);
                //fprintf(stderr, "\nAddress of this-pointer=%x\n", this);
        #endif // DEBUG
        free(sval);
        //delete [] sval;
        sval = NULL;

        delete _pString; _pString = NULL;
}

char* String::val()
{
	return sval;
}

unsigned long String::length()
{
	return (unsigned long)strlen(sval);
}

void String::_allocpString()
{
        // _pString will be deleted in destructor
        if (!_pString)  // if (_pString == NULL)
                _pString = new String(this->sval); 
        else
                *_pString = this->sval;
}

// MUST use pointer-to-pointer **aa, otherwise the argument
// is NOT freed !!
/*
inline void String::_free_glob(String **aa)
{
        //debug("called _free_glob()", "ok" );
        if (*aa != NULL)  // (*aa != NULL)
        {
                //debug("*aa is not null", "ok");
                delete *aa;
                *aa = NULL;
        }
        //else
                //debug("*aa is null", "ok");

        //if (*aa == NULL)
        //debug("*aa set to null", "ok");
}
*/

// Imitating Java's charAt string function...
char String::charAt(int where)
{
        verifyIndex(where);
        return (sval[where]);
}

// Imitate Java's getChars function...
// The sourceStart specifies the index of the beginning of the substring
// and sourceEnd specifies an index that is one past the end of desired
// substring. Thus the substring contains characters from sourceStart 
// through (sourceEnd - 1). The array that will receive the characters
// is specified by target. The index within target at which the substring
// will be copied is passed in targetStart. Care must be taken to assure
// that the target array is large enough to hold the number of characters
// in the specified substring.
// For e.g.  getChars(3, 6, aa, 0) on "ABCDEFGHIJK" gives aa ="DEF"
void String::getChars(int sourceStart, int sourceEnd, char target[], int targetStart)
{
        verifyIndex(sourceStart);
        verifyIndex(sourceEnd);

        if (sourceEnd >= sourceStart)
        {
                strncpy(& target[targetStart], & sval[sourceStart], sourceEnd - sourceStart);
                target[targetStart + (sourceEnd - sourceStart)] = 0;
        }
        else
        {
                //cerr << "\ngetChars() - SourceEnd is greater than SourceStart!!\n" << endl;
                exit(1);
        }
}

// Imitate Java's getChars string function...
// Returns array of characters for the entire string
char* String::toCharArray()
{
        return (sval);
}

// Imitate Java's getBytes string function...
// Returns array of characters for the entire string
char* String::getBytes()
{
        return (sval);
}
char* String::getBytes(char *str)
{
        return (sval);
}
char* String::getBytes(String s)
{
        return (sval);
}

// Imitate Java's equals string function...
bool String::equals(String str2)  // See also == operator
{
        return ( _equalto(str2.sval));
}

// Imitate Java's equals string function...
bool String::equals(char *str2)  // See also == operator
{
        return ( _equalto(str2));
}

// Imitate Java's equalsIgnoreCase string function...
bool String::equalsIgnoreCase(String str2)
{
        String  aa, bb;
        aa = this->toLowerCase();
        bb = str2.toLowerCase();
        return (aa._equalto(bb.sval));
}

// Imitate Java's regionMatches string function...
// The startIndex specifies the index at which the region begins within
// the invoking String object. The string being compared is str2. The
// index at which comparison will start within str2 is specified by
// str2Index. The length of the substring being compared is numChars.
bool String::regionMatches(int startIndex, String str2, int str2StartIndex, int numChars)
{
        verifyIndex(startIndex);
        str2.verifyIndex(str2StartIndex);
        if (strncmp(& this->sval[startIndex], & str2.sval[str2StartIndex], numChars) == 0)
                return true;
        else
                return false;
}

// Imitate Java's regionMatches string function...
// This is overloaded function of regionMatches
// If ignoreCase is true, the case of the characters is ignored, otherwise
// case is significant (i.e. if ignoreCase is true then ignore the 
// case and compare)
// The startIndex specifies the index at which the region begins within
// the invoking String object. The string being compared is str2. The
// index at which comparison will start within str2 is specified by
// str2Index. The length of the substring being compared is numChars.
bool String::regionMatches(bool ignoreCase, int startIndex, String str2, int str2StartIndex, int numChars)
{
        if (ignoreCase)  // if (ignoreCase == true)
        {
                verifyIndex(startIndex);
                str2.verifyIndex(str2StartIndex);
                String string1, string2;
                string1 = this->toLowerCase();
                string2 = str2.toLowerCase();
                if (strncmp(& string1.sval[startIndex], & string2.sval[str2StartIndex], numChars) == 0)
                        return true;
                else
                        return false;
        }
        else
        {
                return regionMatches(startIndex, str2, str2StartIndex, numChars);
        }
}

// Imitate Java's toLowerCase string function...
//       String  ss("sometest");
//       String  egg = ss.toLowerCase();
String String::toLowerCase()
{
        _allocpString();

        for (long tmpii = (long)strlen(_pString->sval); tmpii >= 0; tmpii--)
        {
                _pString->sval[tmpii] = tolower(_pString->sval[tmpii]);
        }
		return *_pString;
}

// Imitate Java's toUpperCase string function...
//       String  ss("sometest");
//       String  egg = ss.toUpperCase();
String String::toUpperCase()
{
        _allocpString();

        for (long tmpii = (long)strlen(_pString->sval); tmpii >= 0; tmpii--)
        {
                _pString->sval[tmpii] = toupper(_pString->sval[tmpii]);
        }
        return *_pString;  // return the object now
}

// Imitate Java's startsWith string function...
bool String::startsWith(String str2)
{
        if (!strncmp(this->sval, str2.sval, strlen(str2.sval) )) // if (strncmp() == 0)
                return true;
        else
                return false;
}

// Imitate Java's startsWith string function...
// overloaded function
bool String::startsWith(char *str2)
{
        int lenstr2 = (int)strlen(str2);
        if (!strncmp(this->sval, str2, lenstr2)) // if (strncmp() == 0)
                return true;
        else
                return false;
}

// Imitate Java's endsWith string function...
bool String::endsWith(String str2)
{
        // string length of str2 should be less than current string
        if (strlen(str2.sval) > strlen(sval))
                return false;

        if (!strncmp(& this->sval[strlen(sval) - strlen(str2.sval)], str2.sval, strlen(str2.sval) )) // if (strncmp() == 0)
                return true;
        else
                return false;
}

// Imitate Java's endsWith string function...
bool String::endsWith(char *str2)
{
        // string length of str2 should be less than current string
        if (strlen(str2) > strlen(sval))
                return false;

        if (!strncmp(& this->sval[strlen(sval) - strlen(str2)], str2, strlen(str2) ) ) // if (strncmp() == 0)
                return true;
        else
                return false;
}

// Imitate Java's compareTo string function...
// For sorting applications, you need to know which is less than, equal to
// or greater than the next. 
// A string is less than another if it comes before the other in dictionary
// order. A string is greater than another if it comes after the other in
// dictionary order.
//  Less than zero  --> The invoking string is less than str2
//  Greater than zero  --> The invoking string is greater than str2
//  Zero  --> The two strings are equal.
int String::compareTo(String str2)
{
        int  flag = 0;
        // Compare letters in string to each letter in str2
        for (int tmpii = 0, tmpjj = (int)strlen(sval), tmpkk = (int)strlen(str2.sval); tmpii < tmpjj; tmpii++)
        {
                if (tmpii > tmpkk)
                        break;
                if (sval[tmpii] == str2.sval[tmpii])
                        flag = 0;
                else
                if (sval[tmpii] > str2.sval[tmpii])
                {
                        flag = 1;
                        break;
                }
                else // if (sval[tmpii] < str2.sval[tmpii])
                {
                        flag = -1;
                        break;
                }
        }
        return flag;
}

// Imitate Java's compareTo string function...
// Overloaded function of compareTo
int String::compareTo(char *str2)
{
        int  flag = 0;
        // Compare letters in string to each letter in str2
        for (int tmpii = 0, tmpjj = (int)strlen(sval), tmpkk = (int)strlen(str2); tmpii < tmpjj; tmpii++)
        {
                if (tmpii > tmpkk)
                        break;
                if (sval[tmpii] == str2[tmpii])
                        flag = 0;
                else
                if (sval[tmpii] > str2[tmpii])
                {
                        flag = 1;
                        break;
                }
                else // if (sval[tmpii] < str2[tmpii])
                {
                        flag = -1;
                        break;
                }
        }
        return flag;
}

// Imitate Java's compareToIgnoreCase string function...
int String::compareToIgnoreCase(String str2)
{
        String tmpaa = this->toLowerCase(),
        tmpbb = str2.toLowerCase();

        return tmpaa.compareTo(tmpbb);
}

// Imitate Java's compareToIgnoreCase string function...
// Overloaded function
int String::compareToIgnoreCase(char *str2)
{
        String tmpaa = this->toLowerCase(),
        tmpcc(str2), tmpbb = tmpcc.toLowerCase();

        return tmpaa.compareTo(tmpbb);
}

// Imitate Java's indexOf string function...
// Searches for the first occurence of a character or string
// Return the index at which the character or substring was
// found, or -1 on failure.
int String::indexOf(char ch, int startIndex)
{
        verifyIndex(startIndex);
        int ii = startIndex;
        for (; ii < (int) strlen(sval); ii++)
        {
                if (sval[ii] == ch)
                        break;
        }
        if (ii == (int) strlen(sval))
                return -1;
        return ii;
}

// Imitate Java's indexOf string function...
// Overloaded function
int String::indexOf(char *str2, int startIndex)
{
        verifyIndex(startIndex);
        char * tok;
        long res = -1;

        if ( !isNull() )
        {
                tok = strstr(sval + startIndex, str2);
                if (tok == NULL)
                        res = -1;
                else
                        res = (int) (tok - sval);
        }
        return res;
}

// Imitate Java's indexOf string function...
// Overloaded function
int String::indexOf(String str2, int startIndex)
{
        verifyIndex(startIndex);
        char * tok;
        long res = -1;

        if ( !isNull() )
        {
                tok = strstr(sval + startIndex, str2.sval);
                if (tok == NULL)
                        res = -1;
                else
                        res = (int) (tok - sval);
        }
        return res;
}

// Imitate Java's lastIndexOf string function...
// Searches for the last occurence of a character or string
// Return the index at which the character or substring was
// found, or -1 on failure.
int String::lastIndexOf(char ch, int startIndex)
{
        verifyIndex(startIndex);
        int ii;

        // Begin search from the last character of string
        if (!startIndex) // if (startIndex == 0)
                ii = (int)strlen(sval);
        else
                ii = startIndex;
        for (; ii > -1; ii--)
        {
                if (sval[ii] == ch)
                        break;
        }
        if (!ii && sval[ii] != ch) // if (ii == 0)
                return -1;
        return ii;
}

// Imitate Java's lastIndexOf string function...
// Overloaded function
int String::lastIndexOf(char *str2, int startIndex)
{
        verifyIndex(startIndex);
    char *tok = NULL;
    int res = -1;
 
    register char *tmpaa = strdup(sval);  // malloc here
    if (!tmpaa) // tmpaa == NULL
    {
        //cerr << "\nMemory alloc failed in strdup in lastIndexOf()\n" << endl;
        exit(-1);
    }
 
    if (!startIndex) // if (startIndex == 0)
        startIndex = (int)strlen(sval);
    else
        tmpaa[startIndex+1] = 0;
 
    for (int ii = 0; ii <= startIndex; ii++)
    {
        tok = strstr(& tmpaa[ii], str2);
        if (tok == NULL)
            break;
        else
        {
            res = (int) (tok - tmpaa);
                        //debug("res", res);
            ii = res; // jump to where it matched (+1 in for loop)
        }
    }
    free(tmpaa);
        //debug("res", res);
        //debug("indexOf", & sval[res]);

        return res;
}

// Imitate Java's lastIndexOf string function...
// Overloaded function
int String::lastIndexOf(String str2, int startIndex)
{
        verifyIndex(startIndex);
    char *tok = NULL;
    int res = -1;
 
    register char *tmpaa = strdup(sval);  // malloc here
    if (!tmpaa) // tmpaa == NULL
    {
        //cerr << "\nMemory alloc failed in strdup in lastIndexOf()\n" << endl;
        exit(-1);
    }
 
    if (!startIndex) // if (startIndex == 0)
        startIndex = (int)strlen(sval);
    else
        tmpaa[startIndex+1] = 0;
 
    for (int ii = 0; ii <= startIndex; ii++)
    {
        tok = strstr(& tmpaa[ii], str2.sval);
        if (tok == NULL)
            break;
        else
        {
            res = (int) (tok - tmpaa);
                        //debug("res", res);
            ii = res; // jump to where it matched (+1 in for loop)
        }
    }
    free(tmpaa);
        //debug("res", res);
        //debug("indexOf", & sval[res]);

        return res;
}

// Imitate Java's substring string function...
// The startIndex specifies the beginning index, and endIndex specifies
// the stopping point. The string returned contains all the characters
// from the beginning index, up to, but not including, the ending index.
String String::substring(int startIndex, int endIndex)
{
        String tmpstr = String(sval);
        tmpstr._substring(startIndex, endIndex);
        return tmpstr;
}

// Imitate Java's concat string function...
String String::concat(String str2)
{
        return (*this + str2);
}

// Imitate Java's concat string function...
// overloaded function
String String::concat(char *str2)
{
        return (*this + str2);
}

// Imitate Java's replace string function...
// Replace all occurences of string 'original' with 
// 'replacement' in 'sval'
String String::replace(char original, char replacement)
{
        // For example -
        //              replace('A', 'B') on sval = "some AAA and AAACC"
        //              reurns sval = "some BBB and BBBCC"
        //String *tmpstr = new String(sval); Use default copy cstr
        String tmpstr(sval);
        for (int ii = 0, len = (int)strlen(sval); ii < len; ii++)
        {
                if (tmpstr.sval[ii] == original)
                        tmpstr.sval[ii] = replacement;
        }
        return tmpstr; // this will use copy constructor to make a default copy
}

// Imitate Java's replace string function...
// overloaded function
// Replace all occurences of string 'original' with
// 'replacement' in 'sval'
String String::replace(char *original, char *replacement)
{
        char *tok = NULL, *bb;
        register char *aa = strdup(sval);
        int lenrepl = (int)strlen(replacement);
        int lenorig = (int)strlen(original);

        // Allocate space for bb
        { // local scope
                int tmpii = 0;
                for (int ii = 0; ;ii++)
                {
                        tok = strstr(& aa[ii], original);
                        if (tok == NULL)
                                break;
                        else
                        {
							    //yomei fixed
                                //ii = ii + (int) (tok -aa);
                                ii =(int) (tok -aa);
                                tmpii++;
                        }
                }
                if (!tmpii){ // tmpii == 0, no match of 'original' found
						free(aa);
                        return (String(sval)); // return original string
				}
                tmpii = (int)strlen(sval) + (tmpii * lenrepl) + 20;
                //debug("strstr tmpii", tmpii );
                bb = (char *) malloc(tmpii);
                memset(bb, 0, tmpii);
        }

        for (int res = -1; ;)
        {
                //debug("aa", aa);
                tok = strstr(aa, original);
                if (tok == NULL)
                {
                        mystrcat(bb, aa);
                        break;
                }
                else
                {
                        res = (int) (tok - aa);
                        strncat(bb, aa, res);
                        mystrcat(bb, replacement);
                        //bb[strlen(bb)] = 0;
                        //debug("res", res );
                        //debug("bb", bb );
						//
                        mystrcpy(aa, & aa[res+lenorig]);
                }
        }
        //debug("bb", bb );
        free(aa);
        String tmpstr(bb);
        free(bb);
        return tmpstr;
}
/*
another method of doing replace function but slow..
String String::replace(char *original, char *replacement)
{
        // For example -
        //              replace("AAA", "BB") on sval = "some AAA and AAACC"
        //              reurns sval = "some BB and BBCC"
        String bb(this->before(original).sval);
        if (strlen(bb.sval) == 0)
                return String(sval); // return original string
        bb += replacement;

        String tmpaa(this->sval), cc, dd;
        for (;;)
        {
                cc = tmpaa.after(original).sval;
                //debug("cc", cc.sval );
                if (!strlen(cc.sval)) // if (strlen(cc.sval) == 0)
                        break;

                dd = cc.before(original).sval;
                if (strlen(dd.sval) == 0)
                {
                        bb += cc;
                        break;
                }
                else
                {
                        bb += dd;
                        bb += replacement;
                }
                tmpaa = cc;
        }
        //debug("bb.sval", bb.sval );
        return bb;
}
*/

// Imitate Java's replace function -  StringBuffer 
String String::replace (int startIndex, int endIndex, String str)
{
        verifyIndex(startIndex);
        verifyIndex(endIndex);
        int tmpjj = (int)strlen(str.sval);
        if (tmpjj == 0)
                return *this;
        int tmpii = endIndex-startIndex-1;
        if (tmpjj < tmpii) // length of str is less than specified indexes.
                tmpii = tmpjj;
        //debug("sval", sval);
        //debug("str.sval", str.sval);
        strncpy(& sval[startIndex], str.sval, tmpii);
        sval[startIndex+tmpii] = 0;
        //debug("sval", sval);
        return *this;
}

// Imitate Java's trim string function...
String String::trim()
{
        //String *tmpstr = new String(sval);
        String tmpstr(sval);
        tmpstr._trim();
        //debug("tmpstr.sval", tmpstr.sval);
        return tmpstr; // this will use copy constructor to make a default copy
}

// Imitate Java's insert string function...
String String::insert(int index, String str2)
{
        String tmpstr(this->insert(str2.sval, index).sval);
        //debug("tmpstr.sval", tmpstr.sval);
        return tmpstr;
}

// Imitate Java's insert string function...
String String::insert(int index, char ch)
{
        char aa[2];
        aa[0] = ch;
        aa[1] = 0;
        String tmpstr(this->insert(aa, index).sval);
        //debug("tmpstr.sval", tmpstr.sval);
        return tmpstr;
}

// Imitate Java's deleteCharAt string function...
String String::deleteCharAt(int loc)
{
        String tmpstr(sval);
        tmpstr._deleteCharAt(loc);
        return tmpstr;
}

// Imitate Java's delete string function...
// Note: -->Java name is "delete()", cannot use reserved name delete() in C++
// The startIndex specifies the index of the first character to remove,
// and endIndex specifies an index one past the last character to remove.
// Thus, the substring deleted runs from startIndex to (endIndex - 1)
String String::deleteStr(int startIndex, int endIndex)
{
        // For example -
        //      deleteStr(3,3) on val = 'pokemon' returns 'poon'
        String tmpstr(sval);
        tmpstr._deleteStr(startIndex, endIndex);
        return tmpstr;
}

// Imitate Java's reverse string function...
String String::reverse()
{
        // For example -
        //              reverse() on "12345" returns "54321"
        String tmpstr(sval);
        tmpstr._reverse();
        return tmpstr;
}

// Imitate Java's valueOf string function...
String String::valueOf(char ch)
{
	char aa[2]; aa[0]=ch; aa[1]=0;
	return String(aa);
}
String String::valueOf(char chars[])
{
	return String(chars);
}
String String::valueOf(bool tf)
{
	if (tf) return String((char*)"true");
	else return String((char*)"false");
}
String String::valueOf(int num)
{
	return String(0,num);
}
String String::valueOf(long num)
{
	return String(0,num);
}
String String::valueOf(float num)
{
	return String(0,num);
}
String String::valueOf(double num) {
	return String(0,num);
}
String String::valueOf(char chars[], int startIndex, int numChars)
{
        verifyIndex(startIndex);
        int ii = (int)strlen(chars);
        if (startIndex > ii)
        {
                //cerr << "\nvalueOf() - startIndex greater than string length of"
                //        << "string passed" << endl;
                exit(0);
        }
        if ( (numChars+startIndex) > ii)
        {
                //cerr << "\nvalueOf() - numChars exceeds the string length of"
                //        << "string passed" << endl;
                exit(0);
        }

        char *aa = strdup(chars);
        aa[startIndex + numChars] = 0;
        String tmpstr(& aa[startIndex]);
        free(aa);
        return tmpstr;
}

// Imitate Java's ensureCapacity string function...
// For use by StringBuffer class. 
// Pre-allocate room for certain number of chars, useful
// if you know in advance that you will be appending a large
// number of small strings to StringBuffer
void String::ensureCapacity(int capacity)
{
        sval = (char *) realloc(sval, capacity);
        sval[0] = '\0';
        //debug("In ensureCapacity(int capacity) sval", sval);
}

// Imitate Java's setLength string function...
// For use by StringBuffer class. 
void String::setLength(int len)
{
        sval = (char *) realloc(sval, len);
        sval[0] = '\0';
        //debug("In ensureCapacity(int len) sval", sval);
}

// Imitate Java's setCharAt function -  StringBuffer 
void String::setCharAt(int where, char ch)
{
        verifyIndex(where);
        sval[where] = ch;
        //debug("in StringBuffer dstr()", "ok");
}


// required by java's Integer class, Long, Double classes
int String::parseInt(String ss)
{
	return ss.toInteger();
}
int String::parseInt(String ss,int dd)
{
	return ss.toInteger(dd);
}
int String::parseInt(char *ss)
{
	String tmpstr(ss); return tmpstr.toInteger();
}
int String::parseInt(char *ss,int dd)
{
	String tmpstr(ss); return tmpstr.toInteger(dd);
}
long String::parseLong(String ss) {
	return ss.parseLong();
}
long String::parseLong(char *ss)
{
	String tmpstr(ss); return tmpstr.parseLong();
}
float String::floatValue()
{
	return (float) toDouble(); 
}
double String::doubleValue(){
	return toDouble(); 
}

// ---- End of Java like String object functions -----

// overloaded function - directly changes object
// Variable dummy will give different signature to function
void String::substring(int startIndex, int endIndex, bool dummy)
{
        this->_substring(startIndex, endIndex);
}

inline void String::_substring(int startIndex, int endIndex)
{
        verifyIndex(startIndex);
        verifyIndex(endIndex);
        if (!endIndex) // endIndex == 0
                mystrcpy(sval, & sval[startIndex] ) ;
        else
        {
                if (endIndex > startIndex)
                {
                        mystrcpy(sval, & sval[startIndex] ) ;
                        sval[endIndex -startIndex] = 0;
                }
                else
                {
                        //cerr << "\n_substring() - startIndex is greater than endIndex!!\n" 
                        //        << endl;
                        exit(-1);
                }
        }
}

// overloaded function - directly changes object
String String::deleteStr(int startIndex, int endIndex, bool dummy)
{
        this->_deleteStr(startIndex, endIndex);
        return *this;
}

inline void String::_deleteStr(int startIndex, int endIndex)
{
        verifyIndex(startIndex);
        verifyIndex(endIndex);
        // For example -
        //      deleteStr(3,3) on val = 'pokemon' returns 'poon'
        char *tmpaa = strdup(sval); // malloc here
        mystrcpy(& tmpaa[startIndex], & tmpaa[endIndex]);
        *this = tmpaa;
        free(tmpaa);
}

// overloaded function - directly changes object
String String::deleteCharAt(int loc, bool dummy)
{
        this->_deleteCharAt(loc);
        return *this;
}

inline void String::_deleteCharAt(int loc)
{
        char *tmpaa = strdup(sval); // malloc here
        mystrcpy(& tmpaa[loc], & tmpaa[loc+1]);
        *this = tmpaa;
        free(tmpaa);
}

// Returns string before regx. Matches first occurence of regx
String String::at(char *regx)
{
        char *tok = NULL;
        tok = strstr(sval, regx);
        if (tok == NULL)
                return(String((char*)""));
        else
        {
                int res = (int) (tok - sval);
                char *lefttok = strdup(sval);
                memset(lefttok, 0, strlen(sval));
                mystrcpy(lefttok, & sval[res]);
                String tmpstr(lefttok);
                free(lefttok);
                return(tmpstr);
        }
}

// Returns string before regx. Matches first occurence of regx
String String::before(char *regx)
{
        char *tok = NULL;
        tok = strstr(sval, regx);
        if (tok == NULL)
                return(String((char*)""));
        else
        {
                int res = (int) (tok - sval);
                char *lefttok = strdup(sval);
                lefttok[res] = 0;
                String tmpstr(lefttok);
                free(lefttok);
                return(tmpstr);
        }
}

// Returns string after regx. Matches first occurence of regx
String String::after(char *regx)
{
        char *tok = NULL;
        tok = strstr(sval, regx);
        if (tok == NULL)
                return(String((char*)""));
        else
        {
                int res = (int) (tok - sval);
                char *lefttok = strdup(sval);
                memset(lefttok, 0, strlen(sval));
                mystrcpy(lefttok, & sval[res + strlen(regx)]);
                String tmpstr(lefttok);
                free(lefttok);
                return(tmpstr);
        }
}



// Implodes the strings in the list-head 
// pointer explodeH and returns the String class 
void String::implode(char *glue)
{
}

// Joins the strings in the list-head 
// pointer explodeH and returns the String class 
void String::join(char *glue)
{
        implode(glue);
}

// Repeat the input string n times
String String::repeat(char *input, unsigned int multiplier)
{
        // For example -
        // repeat("k", 4) returns "kkkk"
        if (!input) // input == NULL
        {
                return (String((char*)""));
        }

        char *aa = (char *) malloc(strlen(input) * multiplier+1);
		*aa=0;
        for (unsigned int tmpii = 0; tmpii < multiplier; tmpii++)
        {
                mystrcat(aa, input);
        }
        String tmpstr(aa);
        free(aa);
        return tmpstr;
}

// Reverse the string
// Overloaded version of reverse(). This will directly
// change the object.
void String::reverse(bool dummy)
{
        this->_reverse();
}
inline void String::_reverse()
{
        // For example -
        //              reverse() on "12345" returns "54321"
        char aa;
        unsigned long tot_len = (int)strlen(sval);
        unsigned long midpoint = tot_len / 2;
        for (unsigned long tmpjj = 0; tmpjj < midpoint; tmpjj++)
        {
                aa = sval[tmpjj];  // temporary storage var
                sval[tmpjj] = sval[tot_len - tmpjj - 1];  // swap the values
                sval[tot_len - tmpjj - 1] = aa; // swap the values
        }
}

// Translate certain chars
// For e.g ("abcd", "ABC") translates all occurences of each 
// character in 'from' to corresponding character in 'to'
String String::tr(char *from, char *to)
{
        int lenfrom = (int)strlen(from), lento = (int)strlen(to);
        if (lento > lenfrom)
                lento = lenfrom; // set it to least
        else
        if (lento < lenfrom)
                lenfrom = lento; // set it to least 
        //debug("lento", lento);

        register char *aa = strdup(sval);
        for (int ii = 0, jj = (int)strlen(sval); ii < jj; ii++) // for every char in val
        {
                for (int kk = 0; kk < lento; kk++) // for every char in "from" string
                {
                        if (aa[ii] == from[kk])
                                aa[ii] = to[kk];
                }
        }
        String tmpstr(aa);
        free(aa);
        return tmpstr;
}

// Center the text
String String::center(int padlength, char padchar)
{
        // For example -
        //              center(10, '*') on sval="aa" returns "****aa****"
        //              center(10) on sval="aa" returns "    aa    "
        // The result is a string of 'padlength' characters with sval centered in it.
        int tmpii = sizeof(char) * (padlength + (int)strlen(sval) + 10);
        char *aa = (char *) malloc(tmpii);
		int jj,kk;
        memset(aa, 0, tmpii);

        for (jj = 0, kk = (int) padlength/2; jj < kk; jj++)
        {
                aa[jj] = padchar;
        }
        mystrcat(aa, sval);
        for (jj = (int)strlen(aa), kk = jj + (int) padlength/2; jj < kk; jj++)
        {
                aa[jj] = padchar;
        }
        String tmpstr(aa);
        free(aa);
        return tmpstr;
}

// Formats the original string by placing <number> of <padchar> characters
// between each set of blank-delimited words. Leading and Trailing blanks
// are always removed. If <number> is omitted or is 0, then all spaces are
// in the string are removed. The default number is 0 and 
// default padchar ' '
String String::space(int number, char padchar )
{
        // For example -
        //              space(3) on sval = "I do not know" 
        //                              will return "I   do   not   know"
        //              space(1, '_') on sval = "A deep black space"  
        //                              will return "A_deep_black_space"
        //              space() on sval = "I   know     this"
        //                              will return "Iknowthis"

        //debug("this->sval", this->sval );
        String tmpstr = this->trim().sval;
        //debug("tmpstr.sval", tmpstr.sval );

        // count spaces
        int spacecount = 0;
		int ii,jj;
        for (ii = 0, jj = (int)strlen(tmpstr.sval); ii < jj; ii++)
        {
                if (tmpstr.sval[ii] == ' ')
                        spacecount++;
        }
        //debug("spacecount", spacecount);

        char ee[2];
        ee[0] = padchar;
        ee[1] = 0;
        String bb = tmpstr.repeat(ee, spacecount);

        int tmpii = sizeof(char) * ((int)strlen(tmpstr.sval) + (number * spacecount) + 20);
        char *aa = (char *) malloc(tmpii);
        memset(aa, 0, tmpii);
        for (ii = 0, jj = (int)strlen(tmpstr.sval); ii < jj; ii++)
        {
                if (tmpstr.sval[ii] == ' ')
                        mystrcat(aa, bb.sval);
                else
                {
                        ee[0] = sval[ii];
                        mystrcat(aa, ee);
                }
        }
        tmpstr = aa;
        free(aa);
        return tmpstr;
}

// The result is string comprised of all characters between 
// and including <start> and <end>
String String::xrange(char start, char end)
{
        // For example -
        //      xrange('a', 'j') returns val = "abcdefghij"
        //      xrange(1, 8) returns val = "12345678"

        if (end < start)
        {
                //cerr << "\nThe 'end' character is less than 'start' !!" << endl;
                return String((char*)"");
        }

        // Note: The 'end' is greater than 'start'!! And add +1
        int tmpii = sizeof(char) * (end - start + 11); 
        char *aa = (char *) malloc(tmpii);
        memset(aa, 0, tmpii);
        //debug("xrange tmpii", tmpii);
        for (int ii = start, jj = 0; ii <= end; ii++, jj++)
        {
                aa[jj] = ii;
                //debug("xrange aa[jj]", aa[jj] );
        }
        String tmpstr(aa);
        free(aa);
        return tmpstr;
}

// Removes any characters contained in <list>. The default character
// for <list> is a blank ' '
String String::compress(char *list)
{
        // For example -
        //      compress("$,%") on sval = "$1,934" returns "1934"
        //      compress() on sval = "call me alavoor vasudevan" returns "callmealavoorvasudevan"
        int lenlist = (int)strlen(list);
        register char *aa = strdup(sval);
        for (int ii = 0, jj = (int)strlen(sval); ii < jj; ii++) // for every char in sval
        {
                for (int kk = 0; kk < lenlist; kk++) // for every char in "from" string
                {
                        if (aa[ii] == list[kk])
                        {
                                mystrcpy(& aa[ii], & aa[ii+1]);
                        }
                }
        }
        String tmpstr(aa);
        free(aa);
        return tmpstr;
}

// The <newstr> is inserted into sval beginning at <start>. The <newstr> will
// be padded or truncated to <length> characters. The default <length> is 
// string length of newstr
String String::insert(char *newstr, int start , int lengthstr, char padchar )
{
        // For example -
        //      insert("something new", 4, 20, '*') on sval = "old thing" 
        //              returns "old something new*******thing"
        int tmplen = sizeof(char) * (int)strlen(sval) + (int)strlen(newstr) + lengthstr + 10;
        char *tmpaa = (char *) malloc (tmplen);
        memset(tmpaa, 0, tmplen);
        if (!start) // start == 0
        {
                mystrcpy(tmpaa, newstr);
                mystrcat(tmpaa, this->sval);
        }
        else
        {
                strncpy(tmpaa, this->sval, start);
                mystrcat(tmpaa, newstr);
                mystrcat(tmpaa, & this->sval[start]);
        }

        String tmpstr(tmpaa);
        free(tmpaa);
        return tmpstr;
}

// overloaded insert function...
String String::insert(int index, String str2, bool dummy)
{
        *this =  this->insert(str2.sval, index).sval;
        ////debug("tmpstr.sval", tmpstr.sval);
        return *this;
}

// overloaded insert function...
String String::insert(int index, char ch, bool dummy)
{
        char aa[2];
        aa[0] = ch;
        aa[1] = 0;
        *this = this->insert(aa, index).sval;
        ////debug("tmpstr.sval", tmpstr.sval);
        return *this;
}

// The result is string of <length> chars madeup of leftmost chars in sval.
// Quick way to left justify a string.
String String::left(int slength , char padchar )
{
        // For example -
        //      left(15) on sval = "Wig"       returns "Wig            "
        //      left(4) on  sval = "Wighat"    returns "Wigh"
        //      left() on   sval = "   Wighat" returns "Wighat   "
        if (!slength) // slength == 0
                slength = (int)strlen(sval);
        //debug("left() slength", slength);

        int tmpii = slength + 20;
        char *aa = (char *) malloc(tmpii);
        memset(aa, 0, tmpii);
        //debug("this->ltrim().sval ", this->ltrim().sval);
        mystrcpy(aa, this->ltrim().sval);
        //debug("left() aa", aa );

        int currlen = (int)strlen(aa);
        if (currlen < slength)  
        {
                // pad the string now
                char ee[2];
                ee[0] = padchar;
                ee[1] = 0;
                mystrcat(aa, this->repeat(ee, (unsigned int) (slength-currlen) ).sval);
        }
        else
        {
                aa[slength] = 0;
        }

        //debug("left() aa", aa );
        String tmpstr(aa);
        free(aa);
        return tmpstr;
}

// The result is string of <length> chars madeup of rightmost chars in sval.
// Quick way to right justify a string.
String String::right(int slength , char padchar )
{
        // For example -
        //      right(10) on sval = "never to saying   " returns " to saying"
        //      right(4) on  sval = "Wighat"             returns "ghat"
        //      right(8) on  sval = "4.50"               returns "    4.50"
        //      right() on   sval = "  4.50     "        returns "       4.50"

        if (!slength) // slength == 0
                slength = (int)strlen(sval);
        //debug("right() slength", slength);

        int tmpii = slength + 20;
        char *aa = (char *) malloc(tmpii);
        memset(aa, 0, tmpii);

        int currlen = (int)strlen(this->rtrim().sval);
        //debug("right() currlen", currlen );
        if (currlen < slength)  
        {
                // pad the string now
                char ee[2];
                ee[0] = padchar;
                ee[1] = 0;
                mystrcpy(aa, this->repeat(ee, (unsigned int) (slength-currlen) ).sval);
                mystrcat(aa, this->rtrim().sval);
                //debug("right() aa", aa );
        }
        else
        {
                mystrcpy(aa, this->rtrim().sval);
                mystrcpy(aa, & aa[currlen-slength]);
                aa[slength] = 0;
        }

        //debug("right() aa", aa );
        String tmpstr(aa);
        free(aa);
        return tmpstr;
}

// The <newstr> is overlayed into sval beginning at <start>. The <newstr> will
// be padded or truncated to <length> characters. The default <length> is 
// string length of newstr
String String::overlay(char *newstr, int start , int slength , char padchar )
{
        // For example -
        //      overlay("12345678", 4, 10, '*') on sval = "oldthing is very bad"
        //              returns "old12345678**ery bad"
        //      overlay("12345678", 4, 5, '*') on sval = "oldthing is very bad"
        //              returns "old12345ery bad"
        int len_newstr = (int)strlen(newstr);
        if (!slength) // slength == 0
                slength = len_newstr;
        char *aa = (char *) malloc(slength + len_newstr + 10);
        aa[0] = 0;
        char ee[2];
        ee[0] = padchar;
        ee[1] = 0;
        if (len_newstr < slength)
        {
                // pad it now
                mystrcpy(aa, newstr);
                mystrcat(aa, this->repeat(ee, (slength-len_newstr)).sval );
        }
        else
        {
                mystrcpy(aa, newstr);
                aa[slength] = 0;
        }

        // Now overlay the string.
        String tmpstr(sval);

        //debug("tmpstr.sval", tmpstr.sval);
        for (int ii=start, jj=(int)strlen(tmpstr.sval), kk=start+slength, mm=0; 
                                ii < jj; ii++, mm++)
        {
                if (ii == kk)
                        break;
                if (mm == slength)
                        break;
                tmpstr.sval[ii] = aa[mm];
        }
        free(aa);
        //debug("tmpstr.sval", tmpstr.sval);
        return tmpstr;
}

// If string is literrally equal to .. or not equal to
// If type is false than it is ==
bool String::_equalto(const String & rhs, bool type )
{
        if (type == false) // test for ==
        {
                if (strlen(rhs.sval) == strlen(sval))
                {
                        if (!strncmp(rhs.sval, sval, strlen(sval))) //  == 0
                                return true;
                        else
                                return false;
                }
                else
                        return false;
        }
        else // test for !=
        {
                if (strlen(rhs.sval) != strlen(sval))
                {
                        if (!strncmp(rhs.sval, sval, strlen(sval))) //  == 0
                                return true;
                        else
                                return false;
                }
                else
                        return false;
        }
}

// If string is literrally equal to .. or not equal to
// If type is false than it is ==
bool String::_equalto(const char *rhs, bool type )
{
        if (type == false) // test for ==
        {
                if (strlen(rhs) == strlen(sval))
                {
                        if (!strncmp(rhs, sval, strlen(sval))) //  == 0
                                return true;
                        else
                                return false;
                }
                else
                        return false;
        }
        else // test for !=
        {
                if (strlen(rhs) != strlen(sval))
                {
                        if (!strncmp(rhs, sval, strlen(sval))) //  == 0
                                return true;
                        else
                                return false;
                }
                else
                        return false;
        }
}

// Synonym function is vacuum()
void String::clear()
{
        sval = (char *) realloc(sval, 10);
        sval[0] = '\0';
}

// Remove trailing ALL given character 'ch' - see also chop()
// For example : 
//      sval = "abcdef\n\n\n" then chopall() = "abcdef"
//      sval = "abcdefffff" then chopall('f') = "abcde"
void String::chopall(char ch)
{
        unsigned long tmpii = (unsigned long)strlen(sval) - 1 ;
        for (; tmpii >= 0; tmpii--)
        {
                if (sval[tmpii] == ch)
                        sval[tmpii] = 0;
                else
                        break;
        }
}

// Remove trailing character - see also chopall()
// chop() is often used to remove trailing newline character
void String::chop()
{
        sval[strlen(sval)-1] = 0;
}

// Overloaded version of trim(). This will directly
// change the object.
void String::trim(bool dummy)
{
        this->_trim();
}

inline void String::_trim()
{
        this->rtrim(true);
        this->ltrim(true);
        //debug("this->sval", this->sval);
}

// Overloaded version of ltrim(). This will directly
// change the object.
void String::ltrim(bool dummy)
{
        this->_ltrim();
}

inline void String::_ltrim()
{
        // May cause problems in my_realloc since 
        // location of bb will be destroyed !!
        char *bb = sval;

        if (bb == NULL)
                return;

        while (isspace(*bb))
                bb++;
        //debug("bb", bb);

        if (bb != NULL && bb != sval)
        {
                //debug("doing string copy", "done");
                _str_cpy(bb); // causes problems in my_realloc and bb is getting destroyed!!
        }
        //else
                //debug("Not doing string copy", "done");
}

String String::ltrim()
{
        String tmpstr(sval);
        tmpstr._ltrim();
        return tmpstr;
}

// Overloaded version of rtrim(). This will directly
// change the object.
void String::rtrim(bool dummy)
{
        this->_rtrim();
}

inline void String::_rtrim()
{
        for (long tmpii = (long)strlen(sval) - 1 ; tmpii >= 0; tmpii--)
        {
                if ( isspace(sval[tmpii]) )
                        sval[tmpii] = '\0';
                else
                        break;
        }
}

String String::rtrim()
{
        String tmpstr(sval);
        tmpstr._rtrim();
        return tmpstr;
}

// Use for rounding off fractions digits of floats
// Rounds-off floats with given precision and then
// stores the result into String's sval field
// Also returns the result as a char *
void String::roundf(float input_val, short precision)
{
        float   integ_flt, deci_flt;
        const   short MAX_PREC = 4;

        //debug("In roundf", "ok");

        if (precision > MAX_PREC) // this is the max reliable precision
                precision = MAX_PREC;

        // get the integral and decimal parts of the float value..
        deci_flt = modff(input_val, & integ_flt);

        for (int tmpzz = 0; tmpzz < precision; tmpzz++)
        {
                //debug("deci_flt", deci_flt);
                deci_flt *= 10;
        }
        //debug("deci_flt", deci_flt);

        //unsigned long deci_int = (unsigned long) ( rint(deci_flt) );
        unsigned long deci_int = (unsigned long) ( floor(deci_flt+0.3) );

		if(sval)free(sval);
        sval = (char *) malloc(NUMBER_LENGTH); // float 70 digits max

        if (deci_int > 999) // (MAX_PREC) digits
                snprintf(sval,NUMBER_LENGTH, "%lu.%lu", (unsigned long) integ_flt, deci_int); 
        else
        if (deci_int > 99) // (MAX_PREC - 1) digits
                snprintf(sval,NUMBER_LENGTH, "%lu.0%lu", (unsigned long) integ_flt, deci_int); 
        else
        if (deci_int > 9) // (MAX_PREC - 2) digits
                snprintf(sval,NUMBER_LENGTH, "%lu.00%lu", (unsigned long) integ_flt, deci_int); 
        else
                snprintf(sval,NUMBER_LENGTH, "%lu.00000%lu", (unsigned long) integ_flt, deci_int); 
}

void String::roundd(double input_val, short precision)
{
        double  integ_flt, deci_flt;
        const   short MAX_PREC = 6;

        if (precision > MAX_PREC) // this is the max reliable precision
                precision = MAX_PREC;

        //debug("In roundd", "ok");
        // get the integral and decimal parts of the double value..
        deci_flt = modf(input_val, & integ_flt);

        for (int tmpzz = 0; tmpzz < precision; tmpzz++)
        {
                //debug("deci_flt", deci_flt);
                deci_flt *= 10;
        }
        //debug("deci_flt", deci_flt);
		if(sval)free(sval);
        sval = (char *) malloc(NUMBER_LENGTH); // double 70 digits max

        //unsigned long deci_int = (unsigned long) ( rint(deci_flt) );
        unsigned long deci_int = (unsigned long) ( floor(deci_flt+0.3) );

        if (deci_int > 99999) // (MAX_PREC) digits
                snprintf(sval,NUMBER_LENGTH, "%lu.%lu", (unsigned long) integ_flt, deci_int); 
        else
        if (deci_int > 9999) // (MAX_PREC - 1) digits
                snprintf(sval,NUMBER_LENGTH, "%lu.0%lu", (unsigned long) integ_flt, deci_int); 
        else
        if (deci_int > 999) // (MAX_PREC - 2) digits
                snprintf(sval,NUMBER_LENGTH, "%lu.00%lu", (unsigned long) integ_flt, deci_int); 
        else
        if (deci_int > 99) // (MAX_PREC - 3) digits
                snprintf(sval,NUMBER_LENGTH, "%lu.000%lu", (unsigned long) integ_flt, deci_int); 
        else
        if (deci_int > 9) // (MAX_PREC - 4) digits
                snprintf(sval,NUMBER_LENGTH, "%lu.0000%lu", (unsigned long) integ_flt, deci_int); 
        else // (MAX_PREC - 5) digits
                snprintf(sval,NUMBER_LENGTH, "%lu.00000%lu", (unsigned long) integ_flt, deci_int); 
}

// Provided for documentation purpose only
// You must use the function indexOf()
bool String::contains(char *str2, int startIndex) 
{
        // For example -
        //              if (indexOf("ohboy") > -1 )
        //                      cout << "\nString contains 'ohboy'" << endl;
        //              if (indexOf("ohboy") < 0 )
        //                      cout << "\nString does NOT contain 'ohboy'" << endl;
        //              if (indexOf("ohboy", 4) > -1 )
        //                      cout << "\nString contains 'ohboy'" << endl;
        //              if (indexOf("ohboy", 4) < 0 )
        //                      cout << "\nString does NOT contain 'ohboy'" << endl;
        //cerr << "\nYou must use indexOf() function instead of contains()\n" << endl;
        exit(-1);
}

// Synonym function is empty()
bool String::isNull()
{
        if (sval[0] == '\0')
                return true;
        else
        {
                if (sval == NULL)
                        return true;
                else
                        return false;
        }
}

// Leading, trailing white-spaces of string are ignored
bool String::isInteger()
{
        String tmpstr(sval);
        tmpstr.trim(true);
        //debug("tmpstr.sval", tmpstr.sval );
        if ( strspn ( tmpstr.sval, "0123456789" ) != strlen(tmpstr.sval) )
                return ( false ) ;
        else
                return ( true ) ;
}

// overloaded func
bool String::isInteger(int pos) 
{
        verifyIndex(pos);
        return (isdigit(sval[pos]))?true:false;
}

// Leading, trailing white-spaces of string are ignored
bool String::isNumeric()
{
        String tmpstr(sval);
        tmpstr.trim(true);
        //debug("tmpstr.sval", tmpstr.sval );
        if ( strspn ( tmpstr.sval, "0123456789.+-e" ) != strlen(tmpstr.sval) )
                return ( false ) ;
        else
                return ( true ) ;
}

// overloaded func
bool String::isNumeric(int pos) 
{
        verifyIndex(pos);
        return (isdigit(sval[pos]))?true:false;
}

bool String::isEmpty()
{
        if (strlen(sval) == 0)
                return true;
        else
                return false;
}

// See also explode()
//      Warning : The String instance is modified by removing
//                    the returned token from the string. It is advised
//                        that you save the original string before calling
//                        this function like for example : 
//              String savestr = origstr;
//              String aa, bb, cc;
//              aa = origstr.token();
//              bb = origstr.token();
//              cc = origstr.token();
//
//  This routine returns the first non-'seperator' (default 
//  white-space) token string from the String instance
String String::token(char seperator ) 
{
        char ee[2];
        ee[0] = seperator;
        ee[1] = 0;
        char *res = strtok(sval, ee);
        if (!res) // if res == NULL
        {
                //debug("token", res);
                //debug("sval", sval);
                return(String(sval));
        }
        else
        {
                String tmpstr(res);

                // Should take string length of sval and not res
                // because strtok() had put a NULL ('\0') at the location
                // and also strtok() ignores the leading blanks of sval
                mystrcpy(sval, & sval[strlen(sval)+1]);
                //debug("token", res);
                //debug("sval", sval);
                return tmpstr;
        }
}

String String::crypt(char *original, char *salt)
{
        return String((char*)"");
}

int String::toInteger()
{
        if ( strlen(sval) == 0 ) {
                //cerr << "Cannot convert a zero length string "
                //<< " to a numeric" << endl ;
                abort() ;
        }

        if ( ! isInteger() ) {
                //cerr << "Cannot convert string [" << sval
                //<< "] to an integer numeric string" << endl ;
                abort() ;
        }

        return ( atoi ( sval ) ) ;
}



int String::toInteger(int dd)
{
        if ( strlen(sval) == 0 ) {
                //cerr << "Cannot convert a zero length string "
                //<< " to a numeric" << endl ;
                abort() ;
        }

        if ( ! isInteger() ) {
                //cerr << "Cannot convert string [" << sval
                //<< "] to an integer numeric string" << endl ;
                abort() ;
        }

        return ( strtol ( sval,NULL,dd ) ) ;
}

long String::parseLong()
{
        if ( strlen(sval) == 0 ) {
                //cerr << "Cannot convert a zero length string "
                //<< " to a numeric" << endl ;
                abort() ;
        }

        if ( ! isInteger() ) {
                //cerr << "Cannot convert string [" << sval
                //<< "] to an integer numeric string" << endl ;
                abort() ;
        }

        return ( atol ( sval ) ) ;
}

double String::toDouble()
{
        if ( strlen(sval) == 0 ) {
                //cerr << "Cannot convert a zero length string "
                //<< " to a numeric" << endl ;
                abort() ;
        }

        if ( ! isNumeric() ) {
                //cerr << "Cannot convert string [" << sval
                //<< "] to a double numeric string" << endl ;
                abort() ;
        }

        double d = atof ( sval ) ;

        return ( d ) ;
}

/*
void String::Format(const char *fmt, ... )
{
        va_list iterator;
        va_start(iterator, fmt );
        va_end(iterator);
}
*/

// checks for the out of bounds values
inline void String::verifyIndex(unsigned long index) const
{
        if (index < 0 || index > strlen(sval) )
        {
                // throw "Index Out Of Bounds Exception";
                //cerr << "Index Out Of Bounds Exception at ["
                //                << index << "] in:\n" << sval << endl;
                exit(1);
        }
}

// checks for the out of bounds values
inline void String::verifyIndex(unsigned long index, char *aa) const
{
        if (!aa) // aa == NULL
        {
                //cerr << "\nverifyIndex(long, char *) str null value\n" << endl;
                exit(-1);
        }
        if (index < 0 || index >= strlen(aa) )
        {
                //cerr << "Index Out Of Bounds Exception at ["
                 //               << index << "] in:\n" << aa << endl;
                exit(1);
        }
}

//////////////////////////////////////////////////////////
// Private functions start from here .........
//////////////////////////////////////////////////////////
void String::_str_cpy(char bb[])
{
		_no_null();
        //debug("In _str_cpy bb", bb);
        if (bb == NULL)
        {
                sval[0] = '\0';
                return;
        }

        unsigned long tmpii = (unsigned long)strlen(bb);

        if (tmpii == 0)
        {
                sval[0] = '\0';
                return;
        }

        //debug("In _str_cpy tmpii", tmpii);
        //debug("In _str_cpy sval", sval);
		char* tmp;

        tmp = (char *) malloc(tmpii+1);
        //sval = (char *) realloc(sval, tmpii+1);

        //sval = new char [tmpii + SAFE_MEM_2];
        //debug("In _str_cpy bb", bb);
        
        //strncpy(sval, bb, tmpii);
        //sval[tmpii] = '\0';

        strncpy(tmp, bb, tmpii);
        tmp[tmpii] = '\0';

		free(sval);
		sval=tmp;
        //debug("In _str_cpy sval", sval);
}

void String::_str_cpy(int bb)
{
        char tmpaa[100];
        snprintf(tmpaa,100, "%d", bb);
        _str_cpy(tmpaa);
}

void String::_str_cpy(unsigned long bb)
{
        char tmpaa[100];
        snprintf(tmpaa,100, "%ld", bb);
        _str_cpy(tmpaa);
}

void String::_str_cpy(float bb)
{
        char tmpaa[100];
        snprintf(tmpaa,100, "%f", bb);
        _str_cpy(tmpaa);
}

void String::_no_null()
{
	/* yomei add */
	if(sval!=NULL)return;

	sval=(char*)malloc(5);
	mystrcpy(sval,"null");
}
void String::_str_cat(char bb[])
{
		_no_null();
		if(bb==NULL)bb=(char*)"null";
        unsigned long tmpjj = (unsigned long)strlen(bb), tmpii = (unsigned long)strlen(sval);
        sval = (char *) realloc(sval, tmpii + tmpjj+1);
        //debug("sval in _str_cat() ", sval);
        strncat(sval, bb, tmpjj+1);
}

void String::_str_cat(int bb)
{
		_no_null();

        char tmpaa[100];
        snprintf(tmpaa,100, "%d", bb);

        unsigned long tmpjj = (unsigned long)strlen(tmpaa), tmpii = (unsigned long)strlen(sval);
        sval = (char *) realloc(sval, tmpii + tmpjj+1);
        strncat(sval, tmpaa, tmpjj+1);
}

void String::_str_cat(unsigned long bb)
{
		_no_null();

        char tmpaa[100];
        snprintf(tmpaa,100, "%ld", bb);

        unsigned long tmpjj = (unsigned long)strlen(tmpaa), tmpii = (unsigned long)strlen(sval);
        sval = (char *) realloc(sval, tmpii + tmpjj+1);
        strncat(sval, tmpaa, tmpjj+1);
}

void String::_str_cat(float bb)
{
		_no_null();

        char tmpaa[100];
        snprintf(tmpaa,100, "%f", bb);

        unsigned long tmpjj = (unsigned long)strlen(tmpaa), tmpii = (unsigned long)strlen(sval);
        sval = (char *) realloc(sval, tmpii + tmpjj+1);
        strncat(sval, tmpaa, tmpjj+1);
}

//////////////////////////////////////////////////////////
// All operator functions start from here .........
//////////////////////////////////////////////////////////
String operator+ (const String & lhs, const String & rhs)
{
        /*******************************************************/
        // Note : For adding two char strings, first cast String 
        // as in - 
        //aa = (String) "alkja " + " 99djd " ;
        /*******************************************************/

        String tmp(lhs);
        tmp._str_cat(rhs.sval);
        return(tmp);

        /*
        if (String::_global_String == NULL)
        {
                String::_global_String = new String;
                String::_global_String->_str_cpy(lhs.sval);
                String::_global_String->_str_cat(rhs.sval);
                //return *String::_global_String;
                return String(String::_global_String->val);
        }
        */
        /*
        else
        if (String::_global_String1 == NULL)
        {
                //debug("1)global", "ok" );
                String::_global_String1 = new String;
                String::_global_String1->_str_cpy(lhs.sval);
                String::_global_String1->_str_cat(rhs.sval);
                return *String::_global_String1;
        }
        */
        /*
        else
        {
                fprintf(stderr, "\nError: cannot alloc _global_String\n");
                exit(-1);
        }
        */

        /*
        String *aa = new String;
        aa->_str_cpy(lhs.sval);
        aa->_str_cat(rhs.sval);
        return *aa;
        */
}

String String::operator+ (const String & rhs)
{
        String tmp(*this);
        tmp._str_cat(rhs.sval);
        //debug("rhs.sval in operator+", rhs.sval );
        //debug("tmp.sval in operator+", tmp.sval );
        return (tmp);
}

// Using reference will be faster in = operator
String& String:: operator= ( const String& rhs )
{
		if(rhs.sval==NULL)
		{
			free(sval);
			sval=NULL;
			return *this;
		}
        if (& rhs == this)
        {
                //debug("Fatal Error: In operator(=). rhs is == to 'this pointer'!!", "ok" );
                return *this;
        }

        this->_str_cpy(rhs.sval);
        //debug("rhs value", rhs.sval );

        // Free global vars memory
        //_free_glob(& String::_global_String);
        //if (String::_global_String == NULL)
                //fprintf(stderr, "\n_global_String is freed!\n");

        //return (String(*this));
        return *this;
}

String& String:: operator= ( String* rhs )
{
	int len=0;
	if(sval)free(sval);
	sval=NULL;
	if(rhs==NULL || rhs->sval==NULL)goto end;
	len=(int)strlen(rhs->sval);
	sval=(char*)malloc(len+1);
	mystrcpy(sval,rhs->sval);
end:
	if(rhs)delete rhs;
	return *this;
}



String:: operator char*()
{
	return this->sval;
}
// Using reference will be faster in = operator
String& String::operator+= (const String & rhs)
{
        /*******************************************************/
        // Note : For adding two char strings, first cast String 
        // as in - 
        //aa += (String) "cccc" + "dddd";
        /*******************************************************/

        if (& rhs == this)
        {
                //debug("Fatal error: In operator+= rhs is equals 'this' ptr", "ok");
                return *this;
        }
        this->_str_cat(rhs.sval);
        return *this;
        //return (String(*this));
}

bool String::operator== (const String & rhs)
{
        return(_equalto(rhs.sval));
}

bool String::operator== (const char *rhs)
{
		if(sval==NULL && rhs==NULL)return true;
		if(sval==NULL && rhs!=NULL)return false;
		if(rhs==NULL)return false;
        return(_equalto(rhs));
}

bool String::operator!= (const String & rhs)
{
        return(_equalto(rhs.sval, true));
}

bool String::operator!= (const char *rhs)
{
		if(sval==NULL && rhs==NULL)return false;
		if(sval==NULL && rhs!=NULL)return true;
		if(rhs==NULL)return true;
        return(_equalto(rhs, true));
}

char String::operator[] (unsigned long Index) const
{
        verifyIndex(Index);
        return sval[Index];
}

char & String::operator[] (unsigned long Index)
{
        verifyIndex(Index);
        return sval[Index];
}





//static String Integer("0"); // java's Integer.parseInt(String);
MyInteger::MyInteger(String str)
{
}
String MyInteger::toHexString(int a)
{
	char tmp[32];snprintf(tmp,32,"%x",a);
	return tmp;
}


// Imitate Java's Float class  
// calls base class cstr with string param
Float::Float(String str)
        :String(str.val())  // calls base class cstr
{
        // String(str.val()) -- do not call here in body but call
        // in initialization stage which will avoid extra call on
        // default base-class constructor and will be faster
        // and very efficient
        //debug("in Float cstr(String str)", "ok");
}
Float Float::valueOf(String str2)
{
	return Float(str2);
}
float Float::floatValue()
{
	return (float) toDouble();
}

// Imitate Java's Double class  
// calls base class cstr with string param
Double::Double(String str)
        :String(str.val())  // calls base class cstr
{
        // String(str.val()) -- do not call here in body but call
        // in initialization stage which will avoid extra call on
        // default base-class constructor and will be faster
        // and very efficient
        //debug("in Double cstr(String str)", "ok");
}

Double Double::valueOf(String str2)
{
	return Double(str2);
}
double Double::doubleValue()
{
	return toDouble();
}


//String& operator= (char*,String& rhs)
//{
//}


