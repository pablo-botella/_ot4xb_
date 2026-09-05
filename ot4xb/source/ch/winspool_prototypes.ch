
#xtranslate winspool.EnumPrinters( [<params,...>])  =>;
FpQCall({"winspool.drv","EnumPrintersA"},"__bo__ul__pt__ul__pt__ul_@ul_@ul" [,<params>] )
//----------------------------------------------------------------------------------------------------------------------
#xtranslate winspool.OpenPrinter( [<params,...>])  =>;
FpQCall({"winspool.drv","OpenPrinterA"},"__bo__pt_@ul__pt" [,<params>] )
//----------------------------------------------------------------------------------------------------------------------
#xtranslate winspool.ClosePrinter( [<params,...>])  =>;
FpQCall({"winspool.drv","ClosePrinter"},"__bo__sl" [,<params>] )
//----------------------------------------------------------------------------------------------------------------------
#xtranslate winspool.GetPrinter( [<params,...>])  =>;
FpQCall({"winspool.drv","GetPrinterA"},"__bo__sl__ul__pt__ul_@ul" [,<params>] )
//----------------------------------------------------------------------------------------------------------------------
#xtranslate winspool.EnumJobs( [<params,...>])  =>;
FpQCall({"winspool.drv","EnumJobsA"},"__bo__sl__ul__ul__ul__pt__ul_@ul_@ul" [,<params>] )
//----------------------------------------------------------------------------------------------------------------------
