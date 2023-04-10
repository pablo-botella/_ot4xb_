
#xtranslate __asm mov eax , eax   => __asm__ += __i8( 0x8B,0xC0 )
#xtranslate __asm mov eax , ecx   => __asm__ += __i8( 0x8B,0xC1 )
#xtranslate __asm mov eax , edx   => __asm__ += __i8( 0x8B,0xC2 )
#xtranslate __asm mov eax , ebx   => __asm__ += __i8( 0x8B,0xC3 )
#xtranslate __asm mov eax , esp   => __asm__ += __i8( 0x8B,0xC4 )
#xtranslate __asm mov eax , ebp   => __asm__ += __i8( 0x8B,0xC5 )
#xtranslate __asm mov eax , esi   => __asm__ += __i8( 0x8B,0xC6 )
#xtranslate __asm mov eax , edi   => __asm__ += __i8( 0x8B,0xC7 )

#xtranslate __asm mov ecx , eax   => __asm__ += __i8( 0x8B,0xC8 )
#xtranslate __asm mov ecx , ecx   => __asm__ += __i8( 0x8B,0xC9 )
#xtranslate __asm mov ecx , edx   => __asm__ += __i8( 0x8B,0xCA )
#xtranslate __asm mov ecx , ebx   => __asm__ += __i8( 0x8B,0xCB )
#xtranslate __asm mov ecx , esp   => __asm__ += __i8( 0x8B,0xCC )
#xtranslate __asm mov ecx , ebp   => __asm__ += __i8( 0x8B,0xCD )
#xtranslate __asm mov ecx , esi   => __asm__ += __i8( 0x8B,0xCE )
#xtranslate __asm mov ecx , edi   => __asm__ += __i8( 0x8B,0xCF )

#xtranslate __asm mov edx , eax   => __asm__ += __i8( 0x8B,0xD0 )
#xtranslate __asm mov edx , ecx   => __asm__ += __i8( 0x8B,0xD1 )
#xtranslate __asm mov edx , edx   => __asm__ += __i8( 0x8B,0xD2 )
#xtranslate __asm mov edx , ebx   => __asm__ += __i8( 0x8B,0xD3 )
#xtranslate __asm mov edx , esp   => __asm__ += __i8( 0x8B,0xD4 )
#xtranslate __asm mov edx , ebp   => __asm__ += __i8( 0x8B,0xD5 )
#xtranslate __asm mov edx , esi   => __asm__ += __i8( 0x8B,0xD6 )
#xtranslate __asm mov edx , edi   => __asm__ += __i8( 0x8B,0xD7 )

#xtranslate __asm mov ebx , eax   => __asm__ += __i8( 0x8B,0xD8 )
#xtranslate __asm mov ebx , ecx   => __asm__ += __i8( 0x8B,0xD9 )
#xtranslate __asm mov ebx , edx   => __asm__ += __i8( 0x8B,0xDA )
#xtranslate __asm mov ebx , ebx   => __asm__ += __i8( 0x8B,0xDB )
#xtranslate __asm mov ebx , esp   => __asm__ += __i8( 0x8B,0xDC )
#xtranslate __asm mov ebx , ebp   => __asm__ += __i8( 0x8B,0xDD )
#xtranslate __asm mov ebx , esi   => __asm__ += __i8( 0x8B,0xDE )
#xtranslate __asm mov ebx , edi   => __asm__ += __i8( 0x8B,0xDF )

#xtranslate __asm mov esp , eax   => __asm__ += __i8( 0x8B,0xE0 )
#xtranslate __asm mov esp , ecx   => __asm__ += __i8( 0x8B,0xE1 )
#xtranslate __asm mov esp , edx   => __asm__ += __i8( 0x8B,0xE2 )
#xtranslate __asm mov esp , ebx   => __asm__ += __i8( 0x8B,0xE3 )
#xtranslate __asm mov esp , esp   => __asm__ += __i8( 0x8B,0xE4 )
#xtranslate __asm mov esp , ebp   => __asm__ += __i8( 0x8B,0xE5 )
#xtranslate __asm mov esp , esi   => __asm__ += __i8( 0x8B,0xE6 )
#xtranslate __asm mov esp , edi   => __asm__ += __i8( 0x8B,0xE7 )

#xtranslate __asm mov dword ptr eax , eax  => __asm__ += __i8( 0x89,0x00  )
#xtranslate __asm mov dword ptr ecx , eax  => __asm__ += __i8( 0x89,0x01  )
#xtranslate __asm mov dword ptr edx , eax  => __asm__ += __i8( 0x89,0x02  )
#xtranslate __asm mov dword ptr ebx , eax  => __asm__ += __i8( 0x89,0x03  )
#xtranslate __asm mov dword ptr esp , eax  => __asm__ += __i8( 0x89,0x04  )
#xtranslate __asm mov dword ptr ebp , eax  => __asm__ += __i8( 0x89,0x05  )
#xtranslate __asm mov dword ptr esi , eax  => __asm__ += __i8( 0x89,0x06  )
#xtranslate __asm mov dword ptr edi , eax  => __asm__ += __i8( 0x89,0x07  )

#xtranslate __asm mov dword ptr eax , ecx  => __asm__ += __i8( 0x89,0x08  )
#xtranslate __asm mov dword ptr ecx , ecx  => __asm__ += __i8( 0x89,0x09  )
#xtranslate __asm mov dword ptr edx , ecx  => __asm__ += __i8( 0x89,0x0A  )
#xtranslate __asm mov dword ptr ebx , ecx  => __asm__ += __i8( 0x89,0x0B  )
#xtranslate __asm mov dword ptr esp , ecx  => __asm__ += __i8( 0x89,0x0C  )
#xtranslate __asm mov dword ptr ebp , ecx  => __asm__ += __i8( 0x89,0x0D  )
#xtranslate __asm mov dword ptr esi , ecx  => __asm__ += __i8( 0x89,0x0E  )
#xtranslate __asm mov dword ptr edi , ecx  => __asm__ += __i8( 0x89,0x0F  )

#xtranslate __asm mov dword ptr eax , edx  => __asm__ += __i8( 0x89,0x10  )
#xtranslate __asm mov dword ptr ecx , edx  => __asm__ += __i8( 0x89,0x11  )
#xtranslate __asm mov dword ptr edx , edx  => __asm__ += __i8( 0x89,0x12  )
#xtranslate __asm mov dword ptr ebx , edx  => __asm__ += __i8( 0x89,0x13  )
#xtranslate __asm mov dword ptr esp , edx  => __asm__ += __i8( 0x89,0x14  )
#xtranslate __asm mov dword ptr ebp , edx  => __asm__ += __i8( 0x89,0x15  )
#xtranslate __asm mov dword ptr esi , edx  => __asm__ += __i8( 0x89,0x16  )
#xtranslate __asm mov dword ptr edi , edx  => __asm__ += __i8( 0x89,0x17  )

#xtranslate __asm mov dword ptr eax , ebx  => __asm__ += __i8( 0x89,0x18  )
#xtranslate __asm mov dword ptr ecx , ebx  => __asm__ += __i8( 0x89,0x19  )
#xtranslate __asm mov dword ptr edx , ebx  => __asm__ += __i8( 0x89,0x1A  )
#xtranslate __asm mov dword ptr ebx , ebx  => __asm__ += __i8( 0x89,0x1B  )
#xtranslate __asm mov dword ptr esp , ebx  => __asm__ += __i8( 0x89,0x1C  )
#xtranslate __asm mov dword ptr ebp , ebx  => __asm__ += __i8( 0x89,0x1D  )
#xtranslate __asm mov dword ptr esi , ebx  => __asm__ += __i8( 0x89,0x1E  )
#xtranslate __asm mov dword ptr edi , ebx  => __asm__ += __i8( 0x89,0x1F  )

#xtranslate __asm mov dword ptr eax , esp  => __asm__ += __i8( 0x89,0x20  )
#xtranslate __asm mov dword ptr ecx , esp  => __asm__ += __i8( 0x89,0x21  )
#xtranslate __asm mov dword ptr edx , esp  => __asm__ += __i8( 0x89,0x22  )
#xtranslate __asm mov dword ptr ebx , esp  => __asm__ += __i8( 0x89,0x23  )
#xtranslate __asm mov dword ptr esp , esp  => __asm__ += __i8( 0x89,0x24  )
#xtranslate __asm mov dword ptr ebp , esp  => __asm__ += __i8( 0x89,0x25  )
#xtranslate __asm mov dword ptr esi , esp  => __asm__ += __i8( 0x89,0x26  )
#xtranslate __asm mov dword ptr edi , esp  => __asm__ += __i8( 0x89,0x27  )

#xtranslate __asm mov dword ptr eax , ebp  => __asm__ += __i8( 0x89,0x28  )
#xtranslate __asm mov dword ptr ecx , ebp  => __asm__ += __i8( 0x89,0x29  )
#xtranslate __asm mov dword ptr edx , ebp  => __asm__ += __i8( 0x89,0x2A  )
#xtranslate __asm mov dword ptr ebx , ebp  => __asm__ += __i8( 0x89,0x2B  )
#xtranslate __asm mov dword ptr esp , ebp  => __asm__ += __i8( 0x89,0x2C  )
#xtranslate __asm mov dword ptr ebp , ebp  => __asm__ += __i8( 0x89,0x2D  )
#xtranslate __asm mov dword ptr esi , ebp  => __asm__ += __i8( 0x89,0x2E  )
#xtranslate __asm mov dword ptr edi , ebp  => __asm__ += __i8( 0x89,0x2F  )

#xtranslate __asm mov dword ptr eax , esi  => __asm__ += __i8( 0x89,0x30  )
#xtranslate __asm mov dword ptr ecx , esi  => __asm__ += __i8( 0x89,0x31  )
#xtranslate __asm mov dword ptr edx , esi  => __asm__ += __i8( 0x89,0x32  )
#xtranslate __asm mov dword ptr ebx , esi  => __asm__ += __i8( 0x89,0x33  )
#xtranslate __asm mov dword ptr esp , esi  => __asm__ += __i8( 0x89,0x34  )
#xtranslate __asm mov dword ptr ebp , esi  => __asm__ += __i8( 0x89,0x35  )
#xtranslate __asm mov dword ptr esi , esi  => __asm__ += __i8( 0x89,0x36  )
#xtranslate __asm mov dword ptr edi , esi  => __asm__ += __i8( 0x89,0x37  )

#xtranslate __asm mov dword ptr eax , edi  => __asm__ += __i8( 0x89,0x38  )
#xtranslate __asm mov dword ptr ecx , edi  => __asm__ += __i8( 0x89,0x39  )
#xtranslate __asm mov dword ptr edx , edi  => __asm__ += __i8( 0x89,0x3A  )
#xtranslate __asm mov dword ptr ebx , edi  => __asm__ += __i8( 0x89,0x3B  )
#xtranslate __asm mov dword ptr esp , edi  => __asm__ += __i8( 0x89,0x3C  )
#xtranslate __asm mov dword ptr ebp , edi  => __asm__ += __i8( 0x89,0x3D  )
#xtranslate __asm mov dword ptr esi , edi  => __asm__ += __i8( 0x89,0x3E  )
#xtranslate __asm mov dword ptr edi , edi  => __asm__ += __i8( 0x89,0x3F  )



#ifdef _RT_ASM_VS2017_STYLE
#xtranslate __asm mov ebp , eax   => __asm__ += __i8( 0x8B,0xE8 )
#xtranslate __asm mov ebp , ecx   => __asm__ += __i8( 0x8B,0xE9 )
#xtranslate __asm mov ebp , edx   => __asm__ += __i8( 0x8B,0xEA )
#xtranslate __asm mov ebp , ebx   => __asm__ += __i8( 0x8B,0xEB )
#xtranslate __asm mov ebp , esp   => __asm__ += __i8( 0x8B,0xEC )
#xtranslate __asm mov ebp , ebp   => __asm__ += __i8( 0x8B,0xED )
#xtranslate __asm mov ebp , esi   => __asm__ += __i8( 0x8B,0xEE )
#xtranslate __asm mov ebp , edi   => __asm__ += __i8( 0x8B,0xEF )
#else
#xtranslate __asm mov ebp , esp  => __asm__ += __i8( 0x89,0xE5 )
#endif













#xtranslate __asm mov esi , eax   => __asm__ += __i8( 0x8B,0xF0 )
#xtranslate __asm mov esi , ecx   => __asm__ += __i8( 0x8B,0xF1 )
#xtranslate __asm mov esi , edx   => __asm__ += __i8( 0x8B,0xF2 )
#xtranslate __asm mov esi , ebx   => __asm__ += __i8( 0x8B,0xF3 )
#xtranslate __asm mov esi , esp   => __asm__ += __i8( 0x8B,0xF4 )
#xtranslate __asm mov esi , ebp   => __asm__ += __i8( 0x8B,0xF5 )
#xtranslate __asm mov esi , esi   => __asm__ += __i8( 0x8B,0xF6 )
#xtranslate __asm mov esi , edi   => __asm__ += __i8( 0x8B,0xF7 )

#xtranslate __asm mov edi , eax   => __asm__ += __i8( 0x8B,0xF8 )
#xtranslate __asm mov edi , ecx   => __asm__ += __i8( 0x8B,0xF9 )
#xtranslate __asm mov edi , edx   => __asm__ += __i8( 0x8B,0xFA )
#xtranslate __asm mov edi , ebx   => __asm__ += __i8( 0x8B,0xFB )
#xtranslate __asm mov edi , esp   => __asm__ += __i8( 0x8B,0xFC )
#xtranslate __asm mov edi , ebp   => __asm__ += __i8( 0x8B,0xFD )
#xtranslate __asm mov edi , esi   => __asm__ += __i8( 0x8B,0xFE )
#xtranslate __asm mov edi , edi   => __asm__ += __i8( 0x8B,0xFF )



#xtranslate __asm mov dword  var <nVar>  , val <nValue> => __asm__ += __i8(0xC7,0x45,dwminus(<nVar>*4)) + __i32(<nValue>)


#xtranslate __asm mov var <nVar>  , eax => __asm__ += __i8(0x89,0x45,dwminus(<nVar>*4))
#xtranslate __asm mov var <nVar>  , ecx => __asm__ += __i8(0x89,0x4D,dwminus(<nVar>*4))
#xtranslate __asm mov var <nVar>  , edx => __asm__ += __i8(0x89,0x55,dwminus(<nVar>*4))
#xtranslate __asm mov var <nVar>  , ebx => __asm__ += __i8(0x89,0x5D,dwminus(<nVar>*4))
#xtranslate __asm mov var <nVar>  , esp => __asm__ += __i8(0x89,0x65,dwminus(<nVar>*4))
#xtranslate __asm mov var <nVar>  , ebp => __asm__ += __i8(0x89,0x6D,dwminus(<nVar>*4))
#xtranslate __asm mov var <nVar>  , esi => __asm__ += __i8(0x89,0x75,dwminus(<nVar>*4))
#xtranslate __asm mov var <nVar>  , edi => __asm__ += __i8(0x89,0x7D,dwminus(<nVar>*4))

#xtranslate __asm mov arg <nArg>  , eax => __asm__ += __i8(0x89,0x45,((<nArg>*4)+4) )
#xtranslate __asm mov arg <nArg>  , ecx => __asm__ += __i8(0x89,0x4D,((<nArg>*4)+4) )
#xtranslate __asm mov arg <nArg>  , edx => __asm__ += __i8(0x89,0x55,((<nArg>*4)+4) )
#xtranslate __asm mov arg <nArg>  , ebx => __asm__ += __i8(0x89,0x5D,((<nArg>*4)+4) )
#xtranslate __asm mov arg <nArg>  , esp => __asm__ += __i8(0x89,0x65,((<nArg>*4)+4) )
#xtranslate __asm mov arg <nArg>  , ebp => __asm__ += __i8(0x89,0x6D,((<nArg>*4)+4) )
#xtranslate __asm mov arg <nArg>  , esi => __asm__ += __i8(0x89,0x75,((<nArg>*4)+4) )
#xtranslate __asm mov arg <nArg>  , edi => __asm__ += __i8(0x89,0x7D,((<nArg>*4)+4) )


#xtranslate __asm mov eax ,  arg <nArg>  => __asm__ += __i8(0x8B,0x45,((<nArg>*4)+4) )
#xtranslate __asm mov ecx ,  arg <nArg>  => __asm__ += __i8(0x8B,0x4D,((<nArg>*4)+4) )
#xtranslate __asm mov edx ,  arg <nArg>  => __asm__ += __i8(0x8B,0x55,((<nArg>*4)+4) )
#xtranslate __asm mov ebx ,  arg <nArg>  => __asm__ += __i8(0x8B,0x5D,((<nArg>*4)+4) )
#xtranslate __asm mov esp ,  arg <nArg>  => __asm__ += __i8(0x8B,0x65,((<nArg>*4)+4) )
#xtranslate __asm mov ebp ,  arg <nArg>  => __asm__ += __i8(0x8B,0x6D,((<nArg>*4)+4) )
#xtranslate __asm mov esi ,  arg <nArg>  => __asm__ += __i8(0x8B,0x75,((<nArg>*4)+4) )
#xtranslate __asm mov edi ,  arg <nArg>  => __asm__ += __i8(0x8B,0x7D,((<nArg>*4)+4) )

#xtranslate __asm mov eax ,  var <nVar> => __asm__ += __i8(0x8B,0x45,dwminus(<nVar>*4) )
#xtranslate __asm mov ecx ,  var <nVar> => __asm__ += __i8(0x8B,0x4D,dwminus(<nVar>*4) )
#xtranslate __asm mov edx ,  var <nVar> => __asm__ += __i8(0x8B,0x55,dwminus(<nVar>*4) )
#xtranslate __asm mov ebx ,  var <nVar> => __asm__ += __i8(0x8B,0x5D,dwminus(<nVar>*4) )
#xtranslate __asm mov esp ,  var <nVar> => __asm__ += __i8(0x8B,0x65,dwminus(<nVar>*4) )
#xtranslate __asm mov ebp ,  var <nVar> => __asm__ += __i8(0x8B,0x6D,dwminus(<nVar>*4) )
#xtranslate __asm mov esi ,  var <nVar> => __asm__ += __i8(0x8B,0x75,dwminus(<nVar>*4) )
#xtranslate __asm mov edi ,  var <nVar> => __asm__ += __i8(0x8B,0x7D,dwminus(<nVar>*4) )

#xtranslate __asm mov eax ,  val <nVal> => __asm__ += __i8(0xB8) + __i32(<nVal>)
#xtranslate __asm mov ecx ,  val <nVal> => __asm__ += __i8(0xB9) + __i32(<nVal>)
#xtranslate __asm mov edx ,  val <nVal> => __asm__ += __i8(0xBA) + __i32(<nVal>)
#xtranslate __asm mov ebx ,  val <nVal> => __asm__ += __i8(0xBB) + __i32(<nVal>)
#xtranslate __asm mov esp ,  val <nVal> => __asm__ += __i8(0xBC) + __i32(<nVal>)
#xtranslate __asm mov ebp ,  val <nVal> => __asm__ += __i8(0xBD) + __i32(<nVal>)
#xtranslate __asm mov esi ,  val <nVal> => __asm__ += __i8(0xBE) + __i32(<nVal>)
#xtranslate __asm mov edi ,  val <nVal> => __asm__ += __i8(0xBF) + __i32(<nVal>)









#xtranslate __asm call eax         => __asm__ += __i8(0xFF,0xD0)
#xtranslate __asm call ecx         => __asm__ += __i8(0xFF,0xD1)
#xtranslate __asm call edx         => __asm__ += __i8(0xFF,0xD2)
#xtranslate __asm call ebx         => __asm__ += __i8(0xFF,0xD3)
//#xtranslate __asm call esp       => __asm__ += __i8(0xFF,0xD4) // nobody will want to do this
//#xtranslate __asm call ebp       => __asm__ += __i8(0xFF,0xD5) // ... or this
#xtranslate __asm call esi         => __asm__ += __i8(0xFF,0xD6)
#xtranslate __asm call edi         => __asm__ += __i8(0xFF,0xD7)





#xtranslate __asm retn <n>         => __asm__ += __i8(0xC2) + __i16(<n>)
#xtranslate __asm retn_0           => __asm__ += __i8(0xC3)

#xtranslate __asm push eax         => __asm__ += __i8(0x50)
#xtranslate __asm push ecx         => __asm__ += __i8(0x51)
#xtranslate __asm push edx         => __asm__ += __i8(0x52)
#xtranslate __asm push ebx         => __asm__ += __i8(0x53)
#xtranslate __asm push esp         => __asm__ += __i8(0x54)
#xtranslate __asm push ebp         => __asm__ += __i8(0x55)
#xtranslate __asm push esi         => __asm__ += __i8(0x56)
#xtranslate __asm push edi         => __asm__ += __i8(0x57)

#xtranslate __asm pop eax          => __asm__ += __i8(0x58)
#xtranslate __asm pop ecx          => __asm__ += __i8(0x59)
#xtranslate __asm pop edx          => __asm__ += __i8(0x5A)
#xtranslate __asm pop ebx          => __asm__ += __i8(0x5B)
#xtranslate __asm pop esp          => __asm__ += __i8(0x5C)
#xtranslate __asm pop ebp          => __asm__ += __i8(0x5D)
#xtranslate __asm pop esi          => __asm__ += __i8(0x5E)
#xtranslate __asm pop edi          => __asm__ += __i8(0x5F)




#xtranslate __asm add eax, <n>     => __asm__ += __i8(0x83,0xC0,<n>)
#xtranslate __asm add ecx, <n>     => __asm__ += __i8(0x83,0xC1,<n>)
#xtranslate __asm add edx, <n>     => __asm__ += __i8(0x83,0xC2,<n>)
#xtranslate __asm add ebx, <n>     => __asm__ += __i8(0x83,0xC3,<n>)
#xtranslate __asm add esp, <n>     => __asm__ += __i8(0x83,0xC4,<n>)
#xtranslate __asm add ebp, <n>     => __asm__ += __i8(0x83,0xC5,<n>)
#xtranslate __asm add esi, <n>     => __asm__ += __i8(0x83,0xC6,<n>)
#xtranslate __asm add edi, <n>     => __asm__ += __i8(0x83,0xC7,<n>)



#xtranslate __asm add eax, eax     => __asm__ += __i8(0x03,0xC0)
#xtranslate __asm add eax, ecx     => __asm__ += __i8(0x03,0xC1)
#xtranslate __asm add eax, edx     => __asm__ += __i8(0x03,0xC2)
#xtranslate __asm add eax, ebx     => __asm__ += __i8(0x03,0xC3)
#xtranslate __asm add eax, esp     => __asm__ += __i8(0x03,0xC4)
#xtranslate __asm add eax, ebp     => __asm__ += __i8(0x03,0xC5)
#xtranslate __asm add eax, esi     => __asm__ += __i8(0x03,0xC6)
#xtranslate __asm add eax, edi     => __asm__ += __i8(0x03,0xC7)


#xtranslate __asm add ecx, eax     => __asm__ += __i8(0x03,0xC8)
#xtranslate __asm add ecx, ecx     => __asm__ += __i8(0x03,0xC9)
#xtranslate __asm add ecx, edx     => __asm__ += __i8(0x03,0xCA)
#xtranslate __asm add ecx, ebx     => __asm__ += __i8(0x03,0xCB)
#xtranslate __asm add ecx, esp     => __asm__ += __i8(0x03,0xCC)
#xtranslate __asm add ecx, ebp     => __asm__ += __i8(0x03,0xCD)
#xtranslate __asm add ecx, esi     => __asm__ += __i8(0x03,0xCE)
#xtranslate __asm add ecx, edi     => __asm__ += __i8(0x03,0xCF)


#xtranslate __asm add edx, eax     => __asm__ += __i8(0x03,0xD0)
#xtranslate __asm add edx, ecx     => __asm__ += __i8(0x03,0xD1)
#xtranslate __asm add edx, edx     => __asm__ += __i8(0x03,0xD2)
#xtranslate __asm add edx, ebx     => __asm__ += __i8(0x03,0xD3)
#xtranslate __asm add edx, esp     => __asm__ += __i8(0x03,0xD4)
#xtranslate __asm add edx, ebp     => __asm__ += __i8(0x03,0xD5)
#xtranslate __asm add edx, esi     => __asm__ += __i8(0x03,0xD6)
#xtranslate __asm add edx, edi     => __asm__ += __i8(0x03,0xD7)


#xtranslate __asm add ebx, eax     => __asm__ += __i8(0x03,0xD8)
#xtranslate __asm add ebx, ecx     => __asm__ += __i8(0x03,0xD9)
#xtranslate __asm add ebx, edx     => __asm__ += __i8(0x03,0xDA)
#xtranslate __asm add ebx, ebx     => __asm__ += __i8(0x03,0xDB)
#xtranslate __asm add ebx, esp     => __asm__ += __i8(0x03,0xDC)
#xtranslate __asm add ebx, ebp     => __asm__ += __i8(0x03,0xDD)
#xtranslate __asm add ebx, esi     => __asm__ += __i8(0x03,0xDE)
#xtranslate __asm add ebx, edi     => __asm__ += __i8(0x03,0xDF)

#xtranslate __asm sub eax, <n>     => __asm__ += __i8(0x83,0xE8,<n>)
#xtranslate __asm sub ecx, <n>     => __asm__ += __i8(0x83,0xE9,<n>)
#xtranslate __asm sub edx, <n>     => __asm__ += __i8(0x83,0xEA,<n>)
#xtranslate __asm sub ebx, <n>     => __asm__ += __i8(0x83,0xEB,<n>)
#xtranslate __asm sub esp, <n>     => __asm__ += __i8(0x83,0xEC,<n>)
#xtranslate __asm sub ebp, <n>     => __asm__ += __i8(0x83,0xED,<n>)
#xtranslate __asm sub esi, <n>     => __asm__ += __i8(0x83,0xEE,<n>)
#xtranslate __asm sub edi, <n>     => __asm__ += __i8(0x83,0xEF,<n>)

#xtranslate __asm sub  eax, eax     => __asm__ += __i8(0x2B,0xC0)
#xtranslate __asm sub  eax, ecx     => __asm__ += __i8(0x2B,0xC1)
#xtranslate __asm sub  eax, edx     => __asm__ += __i8(0x2B,0xC2)
#xtranslate __asm sub  eax, ebx     => __asm__ += __i8(0x2B,0xC3)
#xtranslate __asm sub  eax, esp     => __asm__ += __i8(0x2B,0xC4)
#xtranslate __asm sub  eax, ebp     => __asm__ += __i8(0x2B,0xC5)
#xtranslate __asm sub  eax, esi     => __asm__ += __i8(0x2B,0xC6)
#xtranslate __asm sub  eax, edi     => __asm__ += __i8(0x2B,0xC7)

#xtranslate __asm sub  ecx, eax     => __asm__ += __i8(0x2B,0xC8)
#xtranslate __asm sub  ecx, ecx     => __asm__ += __i8(0x2B,0xC9)
#xtranslate __asm sub  ecx, edx     => __asm__ += __i8(0x2B,0xCA)
#xtranslate __asm sub  ecx, ebx     => __asm__ += __i8(0x2B,0xCB)
#xtranslate __asm sub  ecx, esp     => __asm__ += __i8(0x2B,0xCC)
#xtranslate __asm sub  ecx, ebp     => __asm__ += __i8(0x2B,0xCD)
#xtranslate __asm sub  ecx, esi     => __asm__ += __i8(0x2B,0xCE)
#xtranslate __asm sub  ecx, edi     => __asm__ += __i8(0x2B,0xCF)

#xtranslate __asm sub  edx, eax     => __asm__ += __i8(0x2B,0xD0)
#xtranslate __asm sub  edx, ecx     => __asm__ += __i8(0x2B,0xD1)
#xtranslate __asm sub  edx, edx     => __asm__ += __i8(0x2B,0xD2)
#xtranslate __asm sub  edx, ebx     => __asm__ += __i8(0x2B,0xD3)
#xtranslate __asm sub  edx, esp     => __asm__ += __i8(0x2B,0xD4)
#xtranslate __asm sub  edx, ebp     => __asm__ += __i8(0x2B,0xD5)
#xtranslate __asm sub  edx, esi     => __asm__ += __i8(0x2B,0xD6)
#xtranslate __asm sub  edx, edi     => __asm__ += __i8(0x2B,0xD7)

#xtranslate __asm sub  ebx, eax     => __asm__ += __i8(0x2B,0xD8)
#xtranslate __asm sub  ebx, ecx     => __asm__ += __i8(0x2B,0xD9)
#xtranslate __asm sub  ebx, edx     => __asm__ += __i8(0x2B,0xDA)
#xtranslate __asm sub  ebx, ebx     => __asm__ += __i8(0x2B,0xDB)
#xtranslate __asm sub  ebx, esp     => __asm__ += __i8(0x2B,0xDC)
#xtranslate __asm sub  ebx, ebp     => __asm__ += __i8(0x2B,0xDD)
#xtranslate __asm sub  ebx, esi     => __asm__ += __i8(0x2B,0xDE)
#xtranslate __asm sub  ebx, edi     => __asm__ += __i8(0x2B,0xDF)

#xtranslate __asm lea eax ,  var <nVar>  => __asm__ += __i8(0x8D,0x45,dwminus(<nVar>*4))
#xtranslate __asm lea ecx ,  var <nVar>  => __asm__ += __i8(0x8D,0x4D,dwminus(<nVar>*4))
#xtranslate __asm lea edx ,  var <nVar>  => __asm__ += __i8(0x8D,0x55,dwminus(<nVar>*4))
#xtranslate __asm lea ebx ,  var <nVar>  => __asm__ += __i8(0x8D,0x5D,dwminus(<nVar>*4))
#xtranslate __asm lea esp ,  var <nVar>  => __asm__ += __i8(0x8D,0x65,dwminus(<nVar>*4))
#xtranslate __asm lea ebp ,  var <nVar>  => __asm__ += __i8(0x8D,0x6D,dwminus(<nVar>*4))
#xtranslate __asm lea esi ,  var <nVar>  => __asm__ += __i8(0x8D,0x75,dwminus(<nVar>*4))
#xtranslate __asm lea edi ,  var <nVar>  => __asm__ += __i8(0x8D,0x7D,dwminus(<nVar>*4))

#xtranslate __asm lea eax ,  arg <nArg>  => __asm__ += __i8(0x8D,0x45,((<nArg>*4)+4))
#xtranslate __asm lea ecx ,  arg <nArg>  => __asm__ += __i8(0x8D,0x4D,((<nArg>*4)+4))
#xtranslate __asm lea edx ,  arg <nArg>  => __asm__ += __i8(0x8D,0x55,((<nArg>*4)+4))
#xtranslate __asm lea ebx ,  arg <nArg>  => __asm__ += __i8(0x8D,0x5D,((<nArg>*4)+4))
#xtranslate __asm lea esp ,  arg <nArg>  => __asm__ += __i8(0x8D,0x65,((<nArg>*4)+4))
#xtranslate __asm lea ebp ,  arg <nArg>  => __asm__ += __i8(0x8D,0x6D,((<nArg>*4)+4))
#xtranslate __asm lea esi ,  arg <nArg>  => __asm__ += __i8(0x8D,0x75,((<nArg>*4)+4))
#xtranslate __asm lea edi ,  arg <nArg>  => __asm__ += __i8(0x8D,0x7D,((<nArg>*4)+4))



#xtranslate __asm push byte  <nVal> => __asm__ += __i8(0x6A,<nVal>)

#xtranslate __asm push dword <nVal> => __asm__ += __i8(0x68) + __i32(<nVal>)

#xtranslate __asm jle short <n> => __asm__ += __i8(0x7E,<n>)
#xtranslate __asm jmp short <n> => __asm__ += __i8(0xEB,<n>)

#xtranslate __asm test eax eax  => __asm__ += __i8(0x85,0xC0)
#xtranslate __asm jz short <n>  => __asm__ += __i8(0x74,<n>)
#xtranslate __asm jnz short <n> => __asm__ += __i8(0x75,<n>)




// ----------------------------------------------------------------------------------------------------------------

#xtranslate __asm __call__cdecl(<fp> , <nParams> ) ;
            =>   __asm mov  eax , val <fp> ;
               ; __asm call eax ;
               ; __asm add esp, (<nParams> * 4)




#xtranslate __asm __cdecl_prolog_( <nVars> )         ;
            =>   __asm push ebp                      ;
               ; __asm mov ebp, esp                  ;
               ; __asm sub esp, ( <nVars> * 4 )

#xtranslate __asm __stdcall_prolog_( <nVars> ) => __asm __cdecl_prolog_( <nVars> )

#xtranslate __asm __cdecl_epilog_() ;
            =>  __asm mov esp , ebp            ;
              ; __asm pop ebp                  ;
              ; __asm retn_0

#xtranslate __asm __stdcall_epilog_( <nArgs> ) ;
            =>  __asm mov esp , ebp            ;
              ; __asm pop ebp                  ;
              ; __asm retn (<nArgs> * 4)







