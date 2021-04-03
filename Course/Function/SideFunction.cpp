#include "Header.h"
void date_format(char* &x, string myStr) {
	int len = myStr.length();
	x = new char[len + 1];
	for (int i = 0; i < len + 1; ++i) 
		x[i] = myStr[i];	
	for (int i = 0; i < len + 1; ++i) {
		if (x[i] == '/')
			x[i] = ' ';
	}
}