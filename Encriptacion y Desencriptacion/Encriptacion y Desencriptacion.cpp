//*****************************************************************ENCRIPTACION**************************************************************************//
#include <iostream>
#include <stdlib.h>
#include <conio.h> 
using namespace std;
 
FILE *archivo,*nuevo;
 
int main()
{
    char car;
    int opc;
    string Resp;
    
	do
	{
		cout<<"Escribe la opcion: \n[1] Encriptar.\n[2] Desencriptar.\n";
    	cin>>opc;
		switch(opc)
		{
			case 1://ENCRIPTACION.
				archivo=fopen("C:/Users/carme/Desktop/1.bin","rb");
   				nuevo=fopen("C:/Users/carme/Desktop/1.bin","r+b");
    			if(nuevo==NULL && archivo==NULL)
				{
        			cout<<"Error al abrir el archivo nuevo\n";
    			}
        		while(fread(&car,1,1,archivo)!=0)
				{
        			if(car=='\r' && car=='\n')
        			{
        				fprintf(nuevo,"\r\n");
					}
					car+=20;
        			fwrite(&car,1,1,nuevo);
    			}
    			fclose(nuevo);
    			fclose(archivo);
    			cout<<"Seguir en el programa?"<<endl;
    			cin>>Resp;
			break;
		
			case 2://DESENCRIPTACION.
				char car;
    			archivo=fopen("C:/Users/carme/Desktop/1.bin","rb");
    			nuevo=fopen("C:/Users/carme/Desktop/1.bin","r+b");
	    		if(nuevo==NULL && archivo==NULL)
				{
        			cout<<"Error al abrir el archivo nuevo\n";
    			}
			    while(fread(&car,1,1,archivo)!=0)
				{
        			car-=20;
       				fwrite(&car,1,1,nuevo);
    			}
   				fclose(nuevo);
    			fclose(archivo);
    			cout<<"Seguir en el programa?"<<endl;
    			cin>>Resp;
			break;
		}
	}while(Resp=="si");
}
//*****************************************************************ENCRIPTACION**************************************************************************//
