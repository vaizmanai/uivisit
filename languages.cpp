//---------------------------------------------------------------------------

#pragma hdrstop

#include "languages.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

extern Options myOptions;

UnicodeString getLangText(int item)
{
	return languages[myOptions.Lang][item];
}
