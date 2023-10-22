//this program simulates the working of pass 1 of a two pass assembler in SIC
//input.txt contains the SIC program
//intermediate.txt is the file generated as output containing the address of each instruction
//length.txt is the file generated as output containing the length of the program
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct symbol
{
 char label[20];
 int address;
};
void main()
{
        FILE *f1,*f2,*f3,*f4,*f5;
        int lc,sa,l,op1,o,len,i;
        char m1[20],la[20],op[20],otp[20];
        f1=fopen("input.txt","r");
        f3=fopen("symtab.txt","w");
        f4=fopen("intermediate.txt","w");
        f5=fopen("length.txt","w");
        fscanf(f1,"%s%s%x",la,m1,&op1);
        struct symbol s[100];
        int symcount=0;
        if(strcmp(m1,"START")==0)
        {
                sa=op1;
                lc=sa;
                //printf("\t%s\t%s\t%d\n",la,m1,op1);
        }
        else
        {
                lc=0;
        }
        fscanf(f1,"%s%s",la,m1);
        while(!feof(f1))
        {
                fscanf(f1,"%s",op);
                fprintf(f4,"\n%x\t%s\t%s\t%s\n",lc,la,m1,op);
                if(strcmp(la,"START")!=0 &&
                   strcmp(la,"ADD")!=0 &&
                   strcmp(la,"SUB")!=0 &&
                   strcmp(la,"LDA")!=0 &&
                   strcmp(la,"STA")!=0 &&
                   strcmp(la,"WORD")!=0 &&
                   strcmp(la,"BYTE")!=0 &&
                   strcmp(la,"RESW")!=0 &&
                   strcmp(la,"END")!=0  &&
                   strcmp(la,"RESB")!=0) {
                if(strcmp(la,"$")!=0)
                {
                   int exists=0;
                   for(i=0;i<symcount;i++)
                   {
                    if(strcmp(la,s[i].label)==0)
                    {
                     exists=1;
                     break;
                    }
                   } 
                  if(!exists)
                  {
                   fprintf(f3,"\n%x\t%s\n",lc,la);
                   strncpy(s[symcount].label,la,sizeof(s[symcount].label)-1);
                   symcount++;
                  }    
                }
                }
                f2=fopen("optab.txt","r");
                fscanf(f2,"%s%d",otp,&o);
                while(!feof(f2))
                {
                        if(strcmp(m1,otp)==0)
                        {
                                //lc=lc+3;
                                break;
                        }
                        fscanf(f2,"%s%d",otp,&o);
                        }
                        fclose(f2);
                        //lc=lc+3;
                        if(strcmp(m1,"WORD")==0)
                        {
                                lc=lc+3;
                        }
                        else if(strcmp(m1,"RESW")==0)
                        {
                                op1=atoi(op);
                                lc=lc+(3*op1);
                        }
                        else if(strcmp(m1,"BYTE")==0)
                        {
                                if(op[0]=='X')
                                {
                                        lc=lc+1;
                                }
                                else
                                {
                                        len=strlen(op)-3;
                                        lc=lc+len;
                                }
                        }
                        else if(strcmp(m1,"RESB")==0)
                        {
                                op1=atoi(op);
                                lc=lc+op1;
                        }
                        else
                         lc+=3;
                        fscanf(f1,"%s%s",la,m1);
                }
                //if(strcmp(m1,"END")==0)
                {
                        int length=lc-sa-3;
                        fprintf(f5,"program length=\n%d",length);
                }
                fclose(f5);
                fclose(f1);
                fclose(f3);
}
