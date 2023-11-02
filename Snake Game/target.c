#define IN_TARGET
#include "config.h"


void __irq IRQ_Exception(void)
   {
   while(1);
   }
   /********************************************/ 
   void FIQ_Exception(void)
   {
      while(1);
      }
   /*********** Target  limit  ***********/
      void TargetInit(void)
      {
	 
      }
      
      void TargetResetInit(void)
      {
	 
	 MAMCR=2;
	 
	 #if Fcclk < 20000000
	 MAMTIM=1;
	 #else
	 #if Fcclk < 40000000
	 MAMTIM=2;
	 #else
	 MAMTIM= 3;
	 #endif
	 #endif
	 
	 VICIntEnClr=0xffffffff;
	 VICVectAddr=0;
	 VICIntSelect=0;
	 
      }
      
      #include "rt_sys.h"
      #include "stdio.h"
      
      #pragma import(__use_no_semihosting_swi)
      #pragma import(__use_two_region_memory)
      
      int __rt_div0(int a)
      {
	 a = a;
	 return 0;
      }
      
      int fputc(int ch,FILE*f)
      {
	 ch = ch;
	 f = f;
	 return 0;
      }
      
      int fgetc(FILE*f)
      {
	 f = f;
	 return 0;
      }
      
      int _sys_close(FILEHANDLE fh)
      {
	 fh = fh;
	 return 0;
      }
      
      int _sys_write(FILEHANDLE fh,const unsigned char *buf,
      unsigned len, int mode)
      {
	 
	 fh = fh;
	 buf = buf;
	 len =len;
	 mode = mode;
	 return 0;
      }
      
       int _sys_read(FILEHANDLE fh, unsigned char *buf,
      unsigned len, int mode)
      {
	  fh = fh;
	 buf = buf;
	 len =len;
	 mode = mode;
	 return 0;
      }
             void _ttywrch(int ch)
    {  
	 ch=ch;
      }
      int _sys_istty(FILEHANDLE fh)
      {
	 fh = fh;
	 return 0;
      }
      
      int _sys_seek(FILEHANDLE fh,long pos)
      {
	 fh = fh;
	 return 0;
      }
      int _sys_ensure(FILEHANDLE fh)
      {
	 fh = fh;
	 return 0;
      }
      long _sys_flen(FILEHANDLE fh)
      {
	 fh =fh;
	 return 0;
      }
      int _sys_tmpnam(char * name, int sig, unsigned maxlen)
      {
	 name = name;
	 sig = sig;
	 maxlen=maxlen;
	 return 0;
      }
      void _sys_exit(int returncode)
      {
	 returncode = returncode;
      }
      char* _sys_command_string(char * cmd, int len)
      {
	 cmd = cmd;
	 len = len;
	 return 0;
      }
