//---------------------------------------------------------------------------

#pragma hdrstop

#include "languages.h"
#include <cstdarg>
//---------------------------------------------------------------------------
#pragma package(smart_init)

extern Options myOptions;

wchar_t *getLangText(int item)
{
	return languages[myOptions.Lang][item];
}

UnicodeString getText(int item)
{
	return UnicodeString(getLangText(item));
}

UnicodeString getFullText(int item, ...)
{
	va_list args;
    va_start(args, item);

	int count = 1;
	int *c = &item;

	while (*c != 0) {
		int i = va_arg(args, int);
        ++count;
		++c;
	}
	va_end(args);

	c = &item;
	UnicodeString r;
	//if (!wcscmp(languages[myOptions.Lang][L_LEFT_TO_RIGHT], L"true")) {
		for (int j = 0; j < count; j++) {
			r = r + UnicodeString(getLangText(c[j]));
		}
	//}
	return r;
}

void applyLangBySystem()
{
	int l = PRIMARYLANGID(GetUserDefaultLangID());
	if(l == LANG_RUSSIAN || l == LANG_UKRAINIAN || l == LANG_BELARUSIAN)
	{
		myOptions.Lang = MY_LANG_RUSSIAN;
	}
	else if(l == LANG_PERSIAN)
	{
		myOptions.Lang = MY_LANG_FARSI;
	}
	else
	{
		myOptions.Lang = MY_LANG_ENGLISH;
	}
}
