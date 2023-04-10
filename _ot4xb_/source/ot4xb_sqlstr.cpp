//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma optimize( "t", on )
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_(__SQLSTR_MONEY) // __sqlstr_money(v, {flags,pad})
{
	TXppParamList xpp(pl, 2);
	LONGLONG qn = xpp[1]->GetSqlStrMoney();
	DWORD flags = 0;
	DWORD pad   = 0;
	ULONG np = xpp.PCount();
	TXbCPItem* xxb;
	if (np > 0)
	{
		xxb = xpp._get_(np);
		if (xxb->CheckType(XPP_ARRAY))
		{
			DWORD dwc = xxb->con_size();
			np--;
			if (dwc > 0) { flags = _conArrayGetNL(xxb->con(), 1, 0); }
			if (dwc > 1) { pad = _conArrayGetNL(xxb->con(), 2, 0); }
		}
	}

	xpp[0]->PutSqlStrMoney(qn, flags, pad);
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __sqlstr_str2money(LPSTR buffer, DWORD buffer_cb, LONGLONG & qn)
{
	

	DWORD dw_bp;
	DWORD decimal_places = 0;
	char  dc_sep = 0;
	char  th_sep = 0;
	qn = 0LL;
	if (!buffer) { return FALSE; }
	if (!buffer_cb) { return FALSE; }


	for (dw_bp = 0; dw_bp < buffer_cb; dw_bp++)
	{
		char ch = buffer[dw_bp];
		switch (ch)
		{
			case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
			{
				qn = qn * 10LL;
				qn += (LONGLONG)(ch - '0');
				if (dc_sep)
				{
					decimal_places++;
					if (decimal_places > 2) { th_sep = dc_sep; dc_sep = 0; decimal_places = 0; }
				}
				break;
			}
			case '.': case ',':
			{
				if (dc_sep) { th_sep = dc_sep; dc_sep = 0; decimal_places = 0; break; }
				if (th_sep == ch) { break; }
				dc_sep = ch;
				break;
			}
			case ' ': case '\t':
			{
				break;
			}
			case '-':
			{
				qn = qn * -1LL;
				break;
			}
			case 'c': case 'C':
			{
				qn = qn * -1LL;
				dw_bp = buffer_cb + 1;
				break;
			}
			default:
			{
				dw_bp = buffer_cb + 1;
				break;
			}
		}

	}
	while (decimal_places < 2)
	{
		qn = qn * 10LL;
		decimal_places++;
	}
	return TRUE;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void money_sum_internal(XppParamList pl, BOOL bSubstract)
{
	TXppParamList xpp(pl, 0);
	ULONG np = xpp.PCount();
	ULONG n;
	DWORD flags = 0;
	DWORD pad = 0;
	TXbCPItem* xxb;


	LONGLONG qt = 0LL;
	if( np > 0)
	{
		xxb = xpp._get_(np);
		if( xxb->CheckType(XPP_ARRAY) )
		{
			DWORD dwc = xxb->con_size();
			np--;
			if (dwc > 0) { flags = _conArrayGetNL(xxb->con(), 1, 0);}
			if (dwc > 1) { pad   = _conArrayGetNL(xxb->con(), 2, 0); }
		}
	}


	for (n = 1; n <= np; n++)
	{
		LONGLONG qn = xpp._get_(n)->GetSqlStrMoney();
		if (flags && 1) 
		{ 
			if (qn < 0) { qn = qn * -1LL; } 
		}
		if (n > 1 && bSubstract)
		{
			qt -= qn;
		}
		else
		{
			qt += qn;
		}
	}
	xpp[0]->PutSqlStrMoney(qt, flags, pad);
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_(__SQLSTR_MONEY_SUM)  // __sqlstr_money_sum(...)
{
	money_sum_internal(pl, 0);
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_(__SQLSTR_MONEY_SUBSTRACT) // __sqlstr_money_sum(...)
{
	money_sum_internal(pl, 1);
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------

