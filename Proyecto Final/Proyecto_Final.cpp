#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <string.h>
#include <vector>
using namespace std;

#define U "Admin"
#define P "Admin"

FILE *pf_Usuarios,*pf_A, *pf_Productos, *pf_Ventas, *pf_Papelera_Usuarios, *pf_Papelera_Productos, *pf_Reportes, *pf_Mermas;

char CodigoP[7]; int Moneda;
bool Sin_Registros, AdministradorON, UsuarioON;
string productos,usuario,clave_usuario,matricula, precio, cantidad,cantidad_comprar,moneda;

int Menu();//Funcion Menu
void Iniciar_Sesion_Administrador(void);
void Iniciar_Sesion_Usuario(void);
void Creacion_Archivos(void);
void Ventas(void);
void Mostrar(void);
void Fecha_y_Hora(void);
void Alta(void);
void Agregar_Productos(void);
void Agregar_Usuarios(void);
void Menu_Principal(void);
void Baja(void);
void Eliminar_Productos(void);
void Eliminar_Usuarios(void);
void Eliminar_Mermas(void);
void Edicion(void);
void Editar_Productos(void);
void Editar_Usuarios(void);
void Consulta(void);
void Consulta_General(void);
void Consulta_Productos(void);
void Consulta_Usuarios(void);














void Producto_Validado(void);
void Cantidad_Validado(void);
void Precio_Validado(void);
void Cantidad_Comprar_Validado(void);
void Matricula_Validado(void);
void Clave_Usuario_Validado(void);
void Usuario_Validado(void);
void Moneda_Validado(void);

void gotoxy(int,int);//Funcion Gotoxy.
void D_X(void);
void D_Y(void);
//***************************************FUNCION ENCRIPTAR Y DESENCRIPTAR*******************************************************//
void Encriptar(void);
void Desencriptar(void);
void Comprobar(void);
//***************************************FUNCION ENCRIPTAR Y DESENCRIPTAR*******************************************************//

struct Tienda
{
	int Bandera;//Bandera
	char ID_Usuario[7];//Clave del registro de usuario.
	char ID_Producto[7];//Clave de registro del producto.
	char Productos[20];//Productos.
	char Usuarios[20];//Usuarios.
	char Clave_Usuario[20];//Contraseña del usuario.
	int Precio;//Costo del producto.
	int	Cantidad_Productos;//Numero de productos existentes.
	char Fecha[11];//Fechar de la venta.
	char Hora[10];//Hora de la venta.
	int Cantidad_Productos_Comprados;
	int Total;
	int Auxiliar;
};
struct Tienda Dulceria;

/****************************************************************************MAIN***********************************************************************/
int main(void) 
{
	D_X();	D_Y();
	
	Creacion_Archivos();
	Menu_Principal();
	
	char opc='\0';
	
	do
	{
		
		opc=Menu();
		switch(opc)
		{
			case 27://ESC.
				system("color 0C");
				system("cls");
				gotoxy(40,2);cout<<"Adios, gracias por usar el programa.";
				exit(0);
				
			break;
			
			case 8://Retroceso para regresar al menu principal.
				system("color 0F");
				Menu_Principal();
			break;
			
			case 49://Numero 1.//Ventas.//Puede acceder el usuario.
				system("color 0F");
				Ventas();
			break;
			
			case 50://Numero 2.//Alta.//No puede acceder el usuario.
				system("color 0F");
				if(UsuarioON==true)
				{
					system("cls"); system("color 0C");
					gotoxy(38,4);cout<<"NO TIENES PERMISO PARA ACCEDER AQUI.";
					Sleep(1300);
					opc=10;
				}
				else
				{
					Alta();
				}
				
			break;
			
			case 51://Numero 3.//Baja.//No puede acceder el usuario.
				system("color 0F");
				if(UsuarioON==true)
				{
					system("cls"); system("color 0C");
					gotoxy(38,4);cout<<"NO TIENES PERMISO PARA ACCEDER AQUI.";
					Sleep(1300);
					opc=10;
				}
				else
				{
					Baja();
				}
				
			break;
			
			case 52://Numero 4.//Edicion.//No puede acceder el usuario.
				system("color 0F");
				if(UsuarioON==true)
				{
					system("cls"); system("color 0C");
					gotoxy(38,4);cout<<"NO TIENES PERMISO PARA ACCEDER AQUI.";
					Sleep(1300);
					opc=10;
				}
				else
				{
					Edicion();
				}
				
			break;
			
			case 53://Numero 5.//Consultas.//Puede acceder el usuario.
				system("color 0F");
				Consulta();
				
			break;
	
			/*case 54://Numero 6.//Reportes.//Puede acceder el usuario.
				system("color 0F");
				//	
			break;
			
			case 55://Numero 7.//Papelera De Reciclaje.//No puede acceder el usuario.
				system("color 0F");
				if(UsuarioON==true)
				{
					system("cls"); system("color 0C");
					gotoxy(38,4);cout<<"NO TIENES PERMISO PARA ACCEDER AQUI.";
					Sleep(1300);
					opc=10;
				}
			break;*/
			
			default:
				if(opc!=27)
				{
					Beep(1000,100);
				}
		}
		
	}while(opc!=27);

	return 0;
}
/***************************************************************************MAIN************************************************************************/

/***************************************************************************MENU************************************************************************/
int Menu()
{
	system("color 0F");
	char opc1='\0';
	system("cls");
	
	D_X();	D_Y();
	gotoxy(38,2);cout<<"********DULCERIA BLAKK********";
	gotoxy(46,4);cout<<"[ESC] Salir.";
	gotoxy(46,5);cout<<"[ 1 ] Ventas";
	gotoxy(46,6);cout<<"[ 2 ] Alta.";
	gotoxy(46,7);cout<<"[ 3 ] Baja.";
	gotoxy(46,8);cout<<"[ 4 ] Edicion.";
	gotoxy(46,9);cout<<"[ 5 ] Consultas.";
	gotoxy(46,10);cout<<"[ 6 ] Reportes.";
	gotoxy(46,11);cout<<"[ 7 ] Papelera De Reciclaje.";
	gotoxy(46,12);cout<<"[RETROCESO] Menu Principal.";
	gotoxy(56,13);opc1=getch();
}
/***************************************************************************MENU************************************************************************/

/**********************************************************************FUNCIONES************************************************************************/
void Iniciar_Sesion_Administrador()
{
	system("cls");
	system("color 0F");
	string Usuario,Clave;
	bool Incorrecto;
	D_X();	D_Y();
	gotoxy(40,5);cout<<"INICIO DE SESION ADMINISTRADOR";
	
	do
	{
		gotoxy(39,12);cout<<"Usuario: ";
		gotoxy(39,13);cout<<"Clave: ";
		gotoxy(48,12);getline(cin,Usuario);
		gotoxy(46,13);cout<<" ";
		char caracter;
		caracter=getch();
		Clave="";
		while(caracter !=13)
		{
			
			Clave.push_back(caracter);
			cout<<"*";
			caracter=getch();
		}
		
		if(Usuario!=U && Clave!=P)
		{
			system("color 0C");
			gotoxy(48,12);cout<<"                                                  ";
			gotoxy(46,13);cout<<"                                            ";
			gotoxy(48,12);cout<<"Usuario Incorecto";
			gotoxy(46,13);cout<<"Clave Incorrecta";
			Sleep(1200);			
			gotoxy(48,12);cout<<"                                             ";
			gotoxy(46,13);cout<<"                                            ";
			Incorrecto=true;
			system("color 0F");
		}
		else if(Usuario!=U)
		{
			system("color 0C");
			gotoxy(48,12);cout<<"                                                  ";
			gotoxy(48,12);cout<<"Usuario Incorecto";
			gotoxy(46,13);cout<<"                                            ";
			Sleep(1200);
			gotoxy(48,12);cout<<"                                                  ";
			Incorrecto=true;
			system("color 0F");
		}
		else if(Clave!=P)
		{
			system("color 0C");
			gotoxy(46,13);cout<<"                                            ";
			gotoxy(46,13);cout<<"Clave Incorrecta";
			gotoxy(48,12);cout<<"                                                  ";
			Sleep(1200);
			gotoxy(46,13);cout<<"                                            ";
			Incorrecto=true;
			system("color 0F");
		}
		else
		{
			system("color 0A");
			gotoxy(50,15);cout<<"BIENVENIDO AL PROGRAMA.";
			Sleep(1200);
			Incorrecto=false;
			AdministradorON=true;
			UsuarioON=false;
			system("color 0F");
		}
	}while(Incorrecto==true);
	
}
void Iniciar_Sesion_Usuario()
{
	system("cls");
	system("color 0F");
	string usuario,clave;
	char Usuario_2[20], Clave_2[20];
	bool Incorrecto=true, Error=true;
	int contador=0,c=0, Longitud=0,Longitud2=0,Encontrado=0;
	D_X();	D_Y();
	gotoxy(40,5);cout<<"INICIO DE SESION USUARIO.";
	
	pf_Usuarios =fopen("Usuarios.bin","rb");
	do
	{
		fread(&Dulceria,sizeof(&Dulceria),1,pf_Usuarios);
		if(!feof(pf_Usuarios))
		{
			contador++;
		}
	}while(!feof(pf_Usuarios));
	
	fclose(pf_Usuarios);
	
	if(contador!=0)
	{
		pf_Usuarios= fopen("Usuarios.bin", "rb");
		do
		{
			gotoxy(39,12);cout<<"Usuario: ";gotoxy(39,13);cout<<"Clave:";
			gotoxy(48,12);cin>>usuario;gotoxy(46,13);cout<<" ";
			char caracter;
			caracter=getch();
			clave="";
			while(caracter !=13)
			{	
				clave.push_back(caracter);
				cout<<"*";
				caracter=getch();
			}
			
			memset(&Clave_2,0,sizeof(&Clave_2));
			memset(&Usuario_2,0,sizeof(&Usuario_2));
			Longitud= clave.length();
			Longitud2= usuario.length();
			
			for(int z=0;z<=Longitud;z++)
			{
				Clave_2[z]=clave[z];
			}
			for(int y=0;y<=Longitud2;y++)
			{
				Usuario_2[y]=usuario[y];
			}
				
			do
			{
				memset(&Dulceria,0,sizeof(&Dulceria));
				fread(&Dulceria.ID_Usuario,sizeof(Dulceria.ID_Usuario),1,pf_Usuarios);
				fread(&Dulceria.Usuarios,sizeof(Dulceria.Usuarios),1,pf_Usuarios);
				fread(&Dulceria.Clave_Usuario,sizeof(Dulceria.Clave_Usuario),1,pf_Usuarios);
				fread(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Usuarios);
				fgetc(pf_Usuarios);
				fgetc(pf_Usuarios);
				
				if(!feof(pf_Usuarios) && strcmp(Usuario_2, Dulceria.Usuarios)==0 && strcmpi(Clave_2, Dulceria.Clave_Usuario)==0)
				{
					system("color 0A");
					gotoxy(50,15);cout<<"BIENVENIDO AL PROGRAMA.";
					Sleep(1200);
					Incorrecto=false;
					Sin_Registros=false;
					UsuarioON=true;
					AdministradorON=false;
					Encontrado=1;
					Error=false;
					system("color 0F");
				}
				else
				{
					Error=true;
				}
				
			}while(!feof(pf_Usuarios) && Encontrado!=1);
			
			if(Error==true)
			{
				if(strcmpi(Usuario_2, Dulceria.Usuarios)!=0 && strcmpi(Clave_2, Dulceria.Clave_Usuario)!=0)
				{
					system("color 0C");
					gotoxy(48,12);cout<<"                                                  ";
					gotoxy(46,13);cout<<"                                            ";
					gotoxy(48,12);cout<<"Usuario Incorecto";
					gotoxy(46,13);cout<<"Clave Incorrecta";
					Sleep(1200);			
					gotoxy(48,12);cout<<"                                             ";
					gotoxy(46,13);cout<<"                                            ";
					Incorrecto=true;
					system("color 0F");
				}
				else if(strcmpi(Usuario_2, Dulceria.Usuarios)!=0)
				{
					system("color 0C");
					gotoxy(48,12);cout<<"                                                  ";
					gotoxy(48,12);cout<<"Usuario Incorecto";
					gotoxy(46,13);cout<<"                                            ";
					Sleep(1200);
					gotoxy(48,12);cout<<"                                                  ";
					Incorrecto=true;
					system("color 0F");
				}
				else if(strcmpi(Clave_2, Dulceria.Clave_Usuario)!=0)
				{
					system("color 0C");
					gotoxy(46,13);cout<<"                                            ";
					gotoxy(46,13);cout<<"Clave Incorrecta";
					gotoxy(48,12);cout<<"                                                  ";
					Sleep(1200);
					gotoxy(46,13);cout<<"                                            ";
					Incorrecto=true;
					system("color 0F");
				}
			}
			fseek(pf_Usuarios,0,SEEK_SET);
			
		}while(Incorrecto==true);
		
		fclose(pf_Usuarios);
		
	}
	else
	{
		system("color 0C");
		gotoxy(40,10);cout<<"AUN NO HAY USUARIOS REGISTRADOS.";
		Sleep(1300);
		system("color 0F");
		Sin_Registros=true;
	}
}
void Creacion_Archivos()
{	
	pf_Usuarios =fopen("Usuarios.bin","rb");
	pf_Productos =fopen("Productos.bin","rb");
	pf_Ventas =fopen("Ventas.bin","rb");
	pf_Papelera_Usuarios =fopen("Papelera_Usuarios.bin","rb");
	pf_Papelera_Productos =fopen("Papelera_Productos.bin","rb");
	pf_Reportes =fopen("Reportes.bin","rb");
	pf_Mermas =fopen("Mermas.bin","rb");
	if(pf_Usuarios==NULL && pf_Productos==NULL && pf_Ventas==NULL && pf_Papelera_Productos==NULL && pf_Papelera_Usuarios==NULL&& pf_Reportes==NULL && pf_Mermas==NULL)
	{
		pf_Usuarios =fopen("Usuarios.bin","wb");
		pf_Productos =fopen("Productos.bin","wb");
		pf_Ventas =fopen("Ventas.bin","wb");
		pf_Papelera_Usuarios =fopen("Papelera_Usuarios.bin","wb");
		pf_Papelera_Productos =fopen("Papelera_Productos.bin","wb");
		pf_Reportes =fopen("Reportes.bin","wb");
		pf_Mermas =fopen("Mermas.bin","wb");
	}
	
	fclose(pf_Usuarios);
	fclose(pf_Productos);
	fclose(pf_Ventas);
	fclose(pf_Papelera_Usuarios);
	fclose(pf_Papelera_Productos);
	fclose(pf_Reportes);
	fclose(pf_Mermas);
}
void Agregar_Productos()//Cada registro de los productos vale 41 Bytes.
{
	system("cls"); system("color 0F");
	D_X(); D_Y();
	pf_Productos =fopen("Productos.bin","rb+");
	pf_Papelera_Productos = fopen("Papelera_Productos.bin","rb+");
	
	if(pf_Productos==NULL && pf_Papelera_Productos==NULL)
	{
		gotoxy(50,10);cout<<"NO FUE POSIBLE ENCONTRAR EL ARCHIVO, PERO SE CREARA. ";
		pf_Productos =fopen("Productos.bin","wb");
		pf_Papelera_Productos = fopen("Papelera_Productos.bin","wb");
		fclose(pf_Productos);
		fclose(pf_Papelera_Productos);
		pf_Productos =fopen("Productos.bin","rb+");
		pf_Papelera_Productos = fopen("Papelera_Productos.bin","rb+");
	}
	
	bool bandera=true, Borrado=true;
	int X=1, Numero_Productos=0, ContadorPf=0;
	for(int x=2;x<=119;x++)
	{
		gotoxy(X,2);cout<<"~"; 
		gotoxy(X,4);cout<<"~"; 
		X++;
	}X=0;
	
	//***************Para el ID del Producto.*******//
	int T=0,Numero_Usuario;
	if(!feof(pf_Productos))
	{
		fseek(pf_Productos, 0, SEEK_END );
		T=ftell(pf_Productos);
		Numero_Productos=(T/41)+1;
		
	}
	//***************Para el ID del Producto.*******//
	
	gotoxy(50,3);cout<<"[AGREGAR PRODUCTOS]";
	
	do
	{	
		//***Papelera***//
		memset(&Dulceria,0,sizeof(&Dulceria));
		fread(&Dulceria.ID_Producto,sizeof(Dulceria.ID_Producto),1,pf_Papelera_Productos);
		fread(&Dulceria.Productos,sizeof(Dulceria.Productos),1,pf_Papelera_Productos);
		fread(&Dulceria.Precio,sizeof(Dulceria.Precio),1,pf_Papelera_Productos);
		fread(&Dulceria.Cantidad_Productos,sizeof(Dulceria.Cantidad_Productos),1,pf_Papelera_Productos);
		fread(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Papelera_Productos);
		fgetc(pf_Papelera_Productos);
		fgetc(pf_Papelera_Productos);
		
	}while(!feof(pf_Papelera_Productos));
	
	do
	{
		//***Productos***//
		memset(&Dulceria,0,sizeof(&Dulceria));
		fread(&Dulceria.ID_Producto,sizeof(Dulceria.ID_Producto),1,pf_Productos);
		fread(&Dulceria.Productos,sizeof(Dulceria.Productos),1,pf_Productos);
		fread(&Dulceria.Precio,sizeof(Dulceria.Precio),1,pf_Productos);
		fread(&Dulceria.Cantidad_Productos,sizeof(Dulceria.Cantidad_Productos),1,pf_Productos);
		fread(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Productos);
		fgetc(pf_Productos);
		fgetc(pf_Productos);
		ContadorPf++;
		
		if(Dulceria.Bandera==1)
		{
			bandera=false;
			Borrado=false;
			fseek(pf_Usuarios,(ContadorPf-1)*41,0);
		}
	}while(!feof(pf_Usuarios) && bandera==true);
	//*********************Generador del ID_Producto.*****************************//
	if(Borrado==true)
	{
		memset(&Dulceria.ID_Producto,0,sizeof(&Dulceria.ID_Producto));
		memset(&CodigoP,0,sizeof(&CodigoP));
		if(Numero_Productos<10)
		{
			strcat(Dulceria.ID_Producto,"ID_00");
			itoa(Numero_Productos,CodigoP,10);
			strcat(Dulceria.ID_Producto,CodigoP);
		}
		else if(Numero_Productos<100)
		{
			strcat(Dulceria.ID_Producto,"ID_0");
			itoa(Numero_Productos,CodigoP,10); 
			strcat(Dulceria.ID_Producto,CodigoP);
		}
		else if(Numero_Productos<1000)
		{
			strcat(Dulceria.ID_Producto,"ID_");
			itoa(Numero_Productos,CodigoP,10); 
			strcat(Dulceria.ID_Producto,CodigoP);
		}
	}
	//*********************Generador del ID_Producto.*****************************//
	
	gotoxy(40,5);cout<<Dulceria.ID_Producto;
	gotoxy(40,6);cout<<"NOMBRE PRODUCTO:";
	gotoxy(40,7);cout<<"PRECIO:"; gotoxy(48,7);cout<<"$"; gotoxy(60,7);cout<<"(RECUERDA QUE EL PRECIO ES POR UNIDAD).";
	gotoxy(40,8);cout<<"CANTIDAD:";
	
	gotoxy(57,6);getline(cin,productos);Producto_Validado();
	gotoxy(49,7);getline(cin,precio);Precio_Validado();
	gotoxy(50,8);getline(cin,cantidad);Cantidad_Validado();
	Dulceria.Bandera=0;
	//***************************AGREGA AL ARCHIVO DE USUARIOS*****************************//
	fwrite(&Dulceria.ID_Producto,sizeof(Dulceria.ID_Producto),1,pf_Productos);
	fwrite(&Dulceria.Productos,sizeof(Dulceria.Productos),1,pf_Productos);
	fwrite(&Dulceria.Precio,sizeof(Dulceria.Precio),1,pf_Productos);
	fwrite(&Dulceria.Cantidad_Productos,sizeof(Dulceria.Cantidad_Productos),1,pf_Productos);
	fwrite(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Productos);
	fprintf(pf_Productos,"\r\n");
	//***************************SE AGREGA A PAPELERA***********************************************//
	fwrite(&Dulceria.ID_Producto,sizeof(Dulceria.ID_Producto),1,pf_Papelera_Productos);
	fwrite(&Dulceria.Productos,sizeof(Dulceria.Productos),1,pf_Papelera_Productos);
	fwrite(&Dulceria.Precio,sizeof(Dulceria.Precio),1,pf_Papelera_Productos);
	fwrite(&Dulceria.Cantidad_Productos,sizeof(Dulceria.Cantidad_Productos),1,pf_Papelera_Productos);
	fwrite(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Papelera_Productos);
	fprintf(pf_Papelera_Productos,"\r\n");
	
	fseek(pf_Productos,0,2);
	fseek(pf_Papelera_Productos,0,2);
	
	system("color 0A");
	gotoxy(50,10);cout<<"DATOS GUARDADOS CORRECTAMENTE.";
	Sleep(1200);
	fclose(pf_Productos);
	fclose(pf_Papelera_Productos);
	system("color 0F");
	
}
void Agregar_Usuarios()//Cada registro de registrar archivos vale 53 Bytes.
{
	system("cls"); system("color 0F");
	D_X(); D_Y();
	pf_Usuarios =fopen("Usuarios.bin","rb+");
	pf_Papelera_Usuarios =fopen("Papelera_Usuarios.bin","rb+");
	if(pf_Usuarios==NULL && pf_Papelera_Usuarios==NULL)
	{
		gotoxy(50,10);cout<<"NO FUE POSIBLE ENCONTRAR EL ARCHIVO, PERO SE CREARA. ";
		pf_Usuarios =fopen("Usuarios.bin","wb");
		pf_Papelera_Usuarios =fopen("Papelera_Usuarios.bin","wb");
		fclose(pf_Usuarios);
		fclose(pf_Papelera_Usuarios);
		pf_Usuarios =fopen("Usuarios.bin","rb+");
		pf_Papelera_Usuarios =fopen("Papelera_Usuarios.bin","rb+");
	}
		
	int X=1,ContadorPf=0;
	bool bandera=true,Borrado=true;
	for(int x=2;x<=119;x++)
	{
		gotoxy(X,2);cout<<"~"; 
		gotoxy(X,4);cout<<"~"; 
		X++;
	}X=0;
	
	//***************Para el ID del Usuario.*******//
	int Tamanio=0,Numero_Usuario;
	if(!feof(pf_Usuarios))
	{
		fseek(pf_Usuarios, 0, SEEK_END );
		Tamanio=ftell(pf_Usuarios);
		Numero_Usuario=(Tamanio/53)+1;
		
	}
	//***************Para el ID del Usuario.*******//
	gotoxy(50,3);cout<<"[AGREGAR USUARIOS]";
	
	do
	{
		//***Papelera***//	
		memset(&Dulceria,0,sizeof(&Dulceria));
		fread(&Dulceria.ID_Usuario,sizeof(Dulceria.ID_Usuario),1,pf_Papelera_Usuarios);
		fread(&Dulceria.Usuarios,sizeof(Dulceria.Usuarios),1,pf_Papelera_Usuarios);
		fread(&Dulceria.Clave_Usuario,sizeof(Dulceria.Clave_Usuario),1,pf_Papelera_Usuarios);
		fread(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Papelera_Usuarios);
		fgetc(pf_Papelera_Usuarios);
		fgetc(pf_Papelera_Usuarios);
		
	}while(!feof(pf_Papelera_Usuarios));
	
	do
	{
		//***Usuario***//
		memset(&Dulceria,0,sizeof(&Dulceria));
		fread(&Dulceria.ID_Usuario,sizeof(Dulceria.ID_Usuario),1,pf_Usuarios);
		fread(&Dulceria.Usuarios,sizeof(Dulceria.Usuarios),1,pf_Usuarios);
		fread(&Dulceria.Clave_Usuario,sizeof(Dulceria.Clave_Usuario),1,pf_Usuarios);
		fread(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Usuarios);
		fgetc(pf_Usuarios);
		fgetc(pf_Usuarios);
		ContadorPf++;
		if(Dulceria.Bandera==1)
		{
			bandera=false;
			Borrado=false;
			fseek(pf_Usuarios,(ContadorPf-1)*53,0);
		}
	}while(!feof(pf_Usuarios) && bandera==true);
	//*********************Generador del ID_Usuario.*****************************//
	if(Borrado==true)
	{
		memset(&Dulceria,0,sizeof(&Dulceria));
		memset(&CodigoP,0,sizeof(&CodigoP));
		if(Numero_Usuario<10)
		{
			strcat(Dulceria.ID_Usuario,"ID_00");
			itoa(Numero_Usuario,CodigoP,10);
			strcat(Dulceria.ID_Usuario,CodigoP);
		}
		else if(Numero_Usuario<100)
		{
			strcat(Dulceria.ID_Usuario,"ID_0");
			itoa(Numero_Usuario,CodigoP,10); 
			strcat(Dulceria.ID_Usuario,CodigoP);
		}
		else if(Numero_Usuario<1000)
		{
			strcat(Dulceria.ID_Usuario,"ID_");
			itoa(Numero_Usuario,CodigoP,10); 
			strcat(Dulceria.ID_Usuario,CodigoP);
		}
	}
	//*********************Generador del ID_Usuario.*****************************//	
	gotoxy(45,6);cout<<Dulceria.ID_Usuario;//Muestra el ID del Usuario.
	gotoxy(40,7);cout<<"NOMBRE:";//Usuario.
	gotoxy(40,8);cout<<"CLAVE:";//Contraseña.
	
	gotoxy(48,7);getline(cin,usuario);Usuario_Validado();
	gotoxy(47,8);getline(cin,clave_usuario);Clave_Usuario_Validado();
	Dulceria.Bandera=0;
	//**********************AGREGA AL ARCHIVO USUARIOS************************//
	fwrite(&Dulceria.ID_Usuario,sizeof(Dulceria.ID_Usuario),1,pf_Usuarios);
	fwrite(&Dulceria.Usuarios,sizeof(Dulceria.Usuarios),1,pf_Usuarios);
	fwrite(&Dulceria.Clave_Usuario,sizeof(Dulceria.Clave_Usuario),1,pf_Usuarios);
	fwrite(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Usuarios);
	fprintf(pf_Usuarios,"\r\n");
	//*************************AGREGA AL ARCHIVO DE LA PEPELERA USUARIOS****************//
	fwrite(&Dulceria.ID_Usuario,sizeof(Dulceria.ID_Usuario),1,pf_Papelera_Usuarios);
	fwrite(&Dulceria.Usuarios,sizeof(Dulceria.Usuarios),1,pf_Papelera_Usuarios);
	fwrite(&Dulceria.Clave_Usuario,sizeof(Dulceria.Clave_Usuario),1,pf_Papelera_Usuarios);
	fwrite(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Papelera_Usuarios);
	fprintf(pf_Papelera_Usuarios,"\r\n");
	
	fseek(pf_Usuarios,0,2);
	fseek(pf_Papelera_Usuarios,0,2);
	
	system("color 0A");
	gotoxy(50,10);cout<<"DATOS GUARDADOS CORRECTAMENTE.";
	Sleep(1200);
	fclose(pf_Usuarios);
	fclose(pf_Papelera_Usuarios);
	system("color 0F");
}
void Alta()
{
	system("cls");
	system("color 0F");
	D_X(); D_Y();
	int opcion_invalida; char opcion='\0';
	do
	{
		gotoxy(38,2);cout<<"INGRESA LA OPCION QUE DESEAS DAR DE ALTA.";
		gotoxy(38,4);cout<<"[ 1 ] PRODUCTOS.";
		gotoxy(38,5);cout<<"[ 2 ] USUARIO.";
		gotoxy(38,6);cout<<"[RRETROCESO] VOLVER A MENU.";
		gotoxy(43,7);opcion=getch();
		switch(opcion)
		{
			case 8:
				Menu();
			break;
			
			case 49://Productos.
				Agregar_Productos();
				opcion_invalida=0;
			break;
			
			case 50://Usuarios.	
				Agregar_Usuarios();
				opcion_invalida=0;
			break;
			
			default:
				if(opcion!=27)
				{
					Beep(1000,100);
					opcion_invalida=1;
				}
		}
	}while(opcion_invalida==1);
	
}
void Menu_Principal()//Funcion donde estará el menú para iniciar sesión.
{
	char opcion='\0';
	int opcion_invalida;
	do
	{
		system("color 0F"); system("cls");
		gotoxy(38,2);cout<<"MENU PRINCIPAL";
		gotoxy(38,4);cout<<"[ 1 ] INICIAR SESION COMO ADMINISRADOR.";
		gotoxy(38,5);cout<<"[ 2 ] INICIAR SESION COMO USUARIO.";
		gotoxy(38,6);cout<<"[ESC] SALIR.";
		gotoxy(43,7);opcion=getch();
		switch(opcion)
		{
			case 27:
				system("color 0C");
				system("cls");
				gotoxy(40,2);cout<<"Adios, gracias por usar el programa.";
				exit(0);
			break;
			
			case 49:
				Iniciar_Sesion_Administrador();
				opcion_invalida=0;
			break;
			
			case 50:
				Iniciar_Sesion_Usuario();
				if(Sin_Registros==true)
				{
					opcion_invalida=1;
				}
				else
				{
					opcion_invalida=0;
				}
			break;
			
			default:
				if(opcion!=27)
				{
					Beep(1000,100);
					opcion_invalida=1;
				}
		}
	}while(opcion_invalida==1);
}
void Baja()
{
	system("cls");
	system("color 0F");
	D_X(); D_Y();
	int opcion_invalida; char opcion='\0';
	do
	{
		gotoxy(38,2);cout<<"INGRESA LA OPCION QUE DESEAS DAR DE BAJA.";
		gotoxy(38,4);cout<<"[ 1 ] PRODUCTOS.";
		gotoxy(38,5);cout<<"[ 2 ] MERMAS.";
		gotoxy(38,6);cout<<"[ 3 ] USUARIO.";
		gotoxy(38,7);cout<<"[RRETROCESO] VOLVER A MENU.";
		gotoxy(43,8);opcion=getch();
		switch(opcion)
		{
			case 8:
				Menu();
			break;
			
			case 49://Productos.
				Eliminar_Productos();
				opcion_invalida=0;
			break;
			
			case 50://Mermas.	
				Eliminar_Mermas();
				opcion_invalida=0;
			break;
			
			case 51://Usuarios.
				Eliminar_Usuarios();
				opcion_invalida=0;
			break;
			
			default:
				if(opcion!=27)
				{
					Beep(1000,100);
					opcion_invalida=1;
				}
		}
	}while(opcion_invalida==1);	
}
void Eliminar_Productos()
{
	system("cls"); system("color 0F");
	D_X(); D_Y();
	pf_Productos =fopen("Productos.bin","r+b");
	if(pf_Productos==NULL)
	{
		gotoxy(50,10);cout<<"NO FUE POSIBLE ENCONTRAR EL ARCHIVO, PERO SE CREARA. ";
		pf_Productos =fopen("Productos.bin","wb");
		fclose(pf_Productos);
		pf_Productos =fopen("Productos.bin","r+b");
	}
	int X=1,Contador_Productos=0,Contador_Registros_Existentes=0;
	char Buscar[20]; string resp;
	for(int x=2;x<=119;x++)
	{
		gotoxy(X,2);cout<<"~"; 
		gotoxy(X,4);cout<<"~"; 
		X++;
	}X=0;
	
	gotoxy(50,3);cout<<"[ELIMINAR PRODUCTOS]";
	memset(Buscar,0,sizeof(Buscar));
	
	gotoxy(26,5);cout<<"INGRESA EL NOMBRE DEL PRODUCTO:";gotoxy(58,5);gets(Buscar);
	do
	{
		memset(&Dulceria,0,sizeof(&Dulceria));
		fread(&Dulceria.ID_Producto,sizeof(Dulceria.ID_Producto),1,pf_Productos);
		fread(&Dulceria.Productos,sizeof(Dulceria.Productos),1,pf_Productos);
		fread(&Dulceria.Precio,sizeof(Dulceria.Precio),1,pf_Productos);
		fread(&Dulceria.Cantidad_Productos,sizeof(Dulceria.Cantidad_Productos),1,pf_Productos);
		fread(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Productos);
		fgetc(pf_Productos);
		fgetc(pf_Productos);
		Contador_Productos++;
		
		if(!feof(pf_Productos) && strcmpi(Buscar, Dulceria.Productos)==0 && Dulceria.Bandera==0)
		{
			gotoxy(26,8);cout<<"CODIGO:";gotoxy(43,8);cout<<Dulceria.ID_Producto;
			gotoxy(26,9);cout<<"PRODUCTO:";gotoxy(43,9);cout<<Dulceria.Productos;
  			gotoxy(26,10);cout<<"PRECIO:";gotoxy(43,10);cout<<Dulceria.Precio;
  			gotoxy(26,11);cout<<"CANTIDAD:";gotoxy(43,11);cout<<Dulceria.Cantidad_Productos;
   			Contador_Registros_Existentes++;
   			gotoxy(20,13);cout<<"Son estos los datos que desea eliminar?";
   			gotoxy(20,14);cout<<"Escribe Si/No.        ->";getline(cin,resp);
			if(resp=="Si"|resp=="si"|resp=="SI"|resp=="sI")
			{
				system("cls");
				Dulceria.Bandera=1;
				
				fseek(pf_Productos,(Contador_Productos-1)*41,0);
				fwrite(&Dulceria.ID_Producto,sizeof(Dulceria.ID_Producto),1,pf_Productos);
				fwrite(&Dulceria.Productos,sizeof(Dulceria.Productos),1,pf_Productos);
				fwrite(&Dulceria.Precio,sizeof(Dulceria.Precio),1,pf_Productos);
				fwrite(&Dulceria.Cantidad_Productos,sizeof(Dulceria.Cantidad_Productos),1,pf_Productos);
				fwrite(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Productos);
				fprintf(pf_Productos,"\r\n");
				fseek(pf_Productos,0,2);
				
				system("cls"); system("color 0A");
				gotoxy(26,7);cout<<"PRODUCTO ELIMINADO CON EXITO.";
				Sleep(1200);
				system("color 0F");
				
			}
			else if(resp=="No"|resp=="no"|resp=="NO"|resp=="nO")
			{
				system("cls");
				system("color 0A");
				gotoxy(30,7);cout<<"ENTENDIDO, NO SE ELIMINARA.";
				Sleep(1200);
				system("color 0F");
			}
			else
			{
				system("cls");
				system("color 0C");
				gotoxy(30,7);cout<<"CARACTER INVALIDO.";
				Sleep(1200);
				system("color 0F");
			}
		}
		
	}while(!feof(pf_Productos));
	
	if(Contador_Registros_Existentes==0)
	{
		system("cls"); system("color 0C");
		gotoxy(30,7);cout<<"NO EXISTE NINGUN PRODUCTO CON ESE NOMBRE.";
		Sleep(1200);
		system("color 0F");
	}
	fclose(pf_Productos);
}
void Eliminar_Usuarios()
{
	system("cls"); system("color 0F");
	D_X(); D_Y();
	pf_Usuarios =fopen("Usuarios.bin","r+b");
	if(pf_Usuarios==NULL)
	{
		gotoxy(50,10);cout<<"NO FUE POSIBLE ENCONTRAR EL ARCHIVO, PERO SE CREARA. ";
		pf_Usuarios =fopen("Usuarios.bin","wb");
		fclose(pf_Productos);
		pf_Usuarios =fopen("Usuarios.bin","r+b");
	}
	int X=1,Contador_Usuarios=0,Contador_Registros_Existentes=0;
	char Buscar[20]; string resp;
	for(int x=2;x<=119;x++)
	{
		gotoxy(X,2);cout<<"~"; 
		gotoxy(X,4);cout<<"~"; 
		X++;
	}X=0;
	
	gotoxy(50,3);cout<<"[ELIMINAR USUARIOS]";
	memset(Buscar,0,sizeof(Buscar));
	
	gotoxy(26,5);cout<<"INGRESA EL NOMBRE DEL USUARIO:";gotoxy(57,5);gets(Buscar);
	do
	{
		memset(&Dulceria,0,sizeof(&Dulceria));
		fread(&Dulceria.ID_Usuario,sizeof(Dulceria.ID_Usuario),1,pf_Usuarios);
		fread(&Dulceria.Usuarios,sizeof(Dulceria.Usuarios),1,pf_Usuarios);
		fread(&Dulceria.Clave_Usuario,sizeof(Dulceria.Clave_Usuario),1,pf_Usuarios);
		fread(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Usuarios);
		fgetc(pf_Usuarios);
		fgetc(pf_Usuarios);
		Contador_Usuarios++;
		
		if(!feof(pf_Usuarios) && strcmpi(Buscar, Dulceria.Usuarios)==0 && Dulceria.Bandera==0)
		{
			gotoxy(26,8);cout<<"CODIGO:";gotoxy(50,8);cout<<Dulceria.ID_Usuario;
			gotoxy(26,9);cout<<"USUARIO:";gotoxy(50,9);cout<<Dulceria.Usuarios;
  			gotoxy(26,10);cout<<"CLAVE:";gotoxy(50,10);cout<<Dulceria.Clave_Usuario;
   			Contador_Registros_Existentes++;
   			gotoxy(20,13);cout<<"Son estos los datos que desea eliminar?";
   			gotoxy(20,14);cout<<"Escribe Si/No.        ->";getline(cin,resp);
			if(resp=="Si"|resp=="si"|resp=="SI"|resp=="sI")
			{
				system("cls");
				Dulceria.Bandera=1;
				
				fseek(pf_Usuarios,(Contador_Usuarios-1)*53,0);
				fwrite(&Dulceria.ID_Usuario,sizeof(Dulceria.ID_Usuario),1,pf_Usuarios);
				fwrite(&Dulceria.Usuarios,sizeof(Dulceria.Usuarios),1,pf_Usuarios);
				fwrite(&Dulceria.Clave_Usuario,sizeof(Dulceria.Clave_Usuario),1,pf_Usuarios);
				fwrite(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Usuarios);
				fprintf(pf_Usuarios,"\r\n");
				fseek(pf_Usuarios,0,2);
				
				system("cls"); system("color 0A");
				gotoxy(26,7);cout<<"USUARIO ELIMINADO CON EXITO.";
				Sleep(1200);
				system("color 0F");
				
			}
			else if(resp=="No"|resp=="no"|resp=="NO"|resp=="nO")
			{
				system("cls");
				system("color 0A");
				gotoxy(30,7);cout<<"ENTENDIDO, NO SE ELIMINARA.";
				Sleep(1200);
				system("color 0F");
			}
			else
			{
				system("cls");
				system("color 0C");
				gotoxy(30,7);cout<<"CARACTER INVALIDO.";
				Sleep(1200);
				system("color 0F");
			}
		}
		
	}while(!feof(pf_Usuarios));
	
	if(Contador_Registros_Existentes==0)
	{
		system("cls"); system("color 0C");
		gotoxy(30,7);cout<<"NO EXISTE NINGUN PRODUCTO CON ESE NOMBRE.";
		Sleep(1200);
		system("color 0F");
	}
	fclose(pf_Usuarios);
}
void Eliminar_Mermas()//SOLO HACE FALTA SABER EL NUMERO DE BYTES DEL REGISTRO.
{
	system("cls"); system("color 0F");
	D_X(); D_Y();
	pf_Mermas =fopen("Mermas.bin","r+b");
	if(pf_Mermas==NULL)
	{
		gotoxy(50,10);cout<<"NO FUE POSIBLE ENCONTRAR EL ARCHIVO, PERO SE CREARA. ";
		pf_Mermas =fopen("Mermas.bin","wb");
		fclose(pf_Mermas);
		pf_Mermas =fopen("Mermas.bin","r+b");
	}

	int X=1,Contador_Mermas=0,Mermas_Registrados=0,Contador_Registros_Existentes=0;
	char Buscar[20]; string resp;

	do
	{
		fread(&Dulceria,sizeof(&Dulceria),1,pf_Mermas);
		if(!feof(pf_Mermas))
		{
			Mermas_Registrados++;
		}
		
	}while(!feof(pf_Mermas));
	
	fclose(pf_Mermas);
	
	if(Mermas_Registrados != 0)
	{
		pf_Mermas =fopen("Mermas.bin","r+b");
		if(pf_Mermas==NULL)
		{
			gotoxy(50,10);cout<<"NO FUE POSIBLE ENCONTRAR EL ARCHIVO, PERO SE CREARA. ";
			pf_Mermas =fopen("Mermas.bin","wb");
			fclose(pf_Mermas);
			pf_Mermas =fopen("Mermas.bin","r+b");
		}
		
		for(int x=2;x<=119;x++)
		{
			gotoxy(X,2);cout<<"~"; 
			gotoxy(X,4);cout<<"~"; 
			X++;
		}X=0;
		
		gotoxy(50,3);cout<<"[MERMAS]";
		memset(Buscar,0,sizeof(Buscar));
		
		gotoxy(26,5);cout<<"INGRESA EL NOMBRE DEL PRODUCTO AFECTADO:";gotoxy(67,5);gets(Buscar);
		do
		{
			memset(&Dulceria,0,sizeof(&Dulceria));
			fread(&Dulceria.ID_Producto,sizeof(Dulceria.ID_Producto),1,pf_Mermas);
			fread(&Dulceria.Productos,sizeof(Dulceria.Productos),1,pf_Mermas);
			fread(&Dulceria.Precio,sizeof(Dulceria.Precio),1,pf_Mermas);
			fread(&Dulceria.Cantidad_Productos,sizeof(Dulceria.Cantidad_Productos),1,pf_Mermas);
			fread(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Mermas);
			fgetc(pf_Mermas);
			fgetc(pf_Mermas);
			Contador_Mermas++;
			
			if(!feof(pf_Mermas) && strcmpi(Buscar, Dulceria.Productos)==0 && Dulceria.Bandera==0)
			{
				gotoxy(26,8);cout<<"CODIGO:";gotoxy(43,8);cout<<Dulceria.ID_Producto;
				gotoxy(26,9);cout<<"PRODUCTO:";gotoxy(43,9);cout<<Dulceria.Productos;
	  			gotoxy(26,10);cout<<"PRECIO:";gotoxy(43,10);cout<<Dulceria.Precio;
	  			gotoxy(26,11);cout<<"CANTIDAD:";gotoxy(43,11);cout<<Dulceria.Cantidad_Productos;
	   			Contador_Registros_Existentes++;
	   			gotoxy(20,13);cout<<"Son estos los datos que desea eliminar?";
	   			gotoxy(20,14);cout<<"Escribe Si/No.        ->";getline(cin,resp);
				if(resp=="Si"|resp=="si"|resp=="SI"|resp=="sI")
				{
					system("cls");
					Dulceria.Bandera=1;
					
					fseek(pf_Mermas,(Contador_Mermas-1)*41,0);//AUN NO SE SABE LOS BYTES QUE TENDRA EL REGISTRO.
					fwrite(&Dulceria.ID_Producto,sizeof(Dulceria.ID_Producto),1,pf_Mermas);
					fwrite(&Dulceria.Productos,sizeof(Dulceria.Productos),1,pf_Mermas);
					fwrite(&Dulceria.Precio,sizeof(Dulceria.Precio),1,pf_Mermas);
					fwrite(&Dulceria.Cantidad_Productos,sizeof(Dulceria.Cantidad_Productos),1,pf_Mermas);
					fwrite(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Mermas);
					fprintf(pf_Mermas,"\r\n");
					fseek(pf_Mermas,0,2);
					
					system("cls"); system("color 0A");
					gotoxy(26,7);cout<<"MERMA ELIMINADO CON EXITO.";
					Sleep(1200);
					system("color 0F");
					
				}
				else if(resp=="No"|resp=="no"|resp=="NO"|resp=="nO")
				{
					system("cls");
					system("color 0A");
					gotoxy(30,7);cout<<"ENTENDIDO, NO SE ELIMINARA.";
					Sleep(1200);
					system("color 0F");
				}
				else
				{
					system("cls");
					system("color 0C");
					gotoxy(30,7);cout<<"CARACTER INVALIDO.";
					Sleep(1200);
					system("color 0F");
				}
			}
			
		}while(!feof(pf_Mermas));
		
		if(Contador_Registros_Existentes==0)
		{
			system("cls"); system("color 0C");
			gotoxy(30,7);cout<<"NO EXISTE NINGUN PRODUCTO CON ESE NOMBRE.";
			Sleep(1200);
			system("color 0F");
		}
		fclose(pf_Mermas);	
	}
	else
	{
		system("color 0C");
		gotoxy(40,10);cout<<"AUN NO HAY MERMAS EN EL ARCHIVO.";
		Sleep(1300);
		system("color 0F");
	}
	
}
void Consulta()
{
	system("cls");
	system("color 0F");
	D_X(); D_Y();
	int opcion_invalida; char opcion='\0';
	do
	{
		gotoxy(38,2);cout<<"INGRESA LA OPCION QUE DESEAS CONSULTAR.";
		gotoxy(38,4);cout<<"[ 1 ] INVENTARIO GENERAL.";
		gotoxy(38,5);cout<<"[ 2 ] PRODUCTOS.";
		gotoxy(38,6);cout<<"[ 3 ] USUARIO.";
		gotoxy(38,7);cout<<"[RRETROCESO] VOLVER A MENU.";
		gotoxy(43,8);opcion=getch();
		switch(opcion)
		{
			case 8:
				Menu();
			break;
			
			case 49://INVENTARIO GENERAL.
				Consulta_General();
				opcion_invalida=0;
			break;
			
			case 50://PRODUCTOS.	
				Consulta_Productos();
				opcion_invalida=0;
			break;
			
			case 51://USUARIOS.
				Consulta_Usuarios();
				opcion_invalida=0;
			break;
			
			default:
				if(opcion!=27)
				{
					Beep(1000,100);
					opcion_invalida=1;
				}
		}
	}while(opcion_invalida==1);
}
void Consulta_General()
{
	system("cls");
	D_X(); D_Y();
	char Buscar[20]; int X=1,Renglon=0;
	pf_Productos= fopen("Productos.bin", "rb");
	if(pf_Productos==NULL)
	{
		gotoxy(50,10);cout<<"NO FUE POSIBLE ENCONTRAR EL ARCHIVO, PERO SE CREARA. ";
		pf_Productos =fopen("Productos.bin","wb");
		fclose(pf_Productos);
		pf_Productos =fopen("Productos.bin","rb");
	}
	for(int x=2;x<=119;x++)
	{
		gotoxy(X,2);cout<<"~"; 
		gotoxy(X,4);cout<<"~"; 
		X++;
	}X=0;
	
	gotoxy(50,3);cout<<"[INVENTARIO GENERAL]";
	do
	{
		memset(&Dulceria,0,sizeof(&Dulceria));
		fread(&Dulceria.ID_Producto,sizeof(Dulceria.ID_Producto),1,pf_Productos);
		fread(&Dulceria.Productos,sizeof(Dulceria.Productos),1,pf_Productos);
		fread(&Dulceria.Precio,sizeof(Dulceria.Precio),1,pf_Productos);
		fread(&Dulceria.Cantidad_Productos,sizeof(Dulceria.Cantidad_Productos),1,pf_Productos);
		fread(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Productos);
		fgetc(pf_Productos);
		fgetc(pf_Productos);
		
		Renglon++;
		
		if(!feof(pf_Productos) && Dulceria.Bandera==0)
			{
				cout<<"\n\n\n";
				cout<<"   CODIGO: "<<Dulceria.ID_Producto<<"\n";
   				cout<<"   PRODUCTO: "<<Dulceria.Productos<<"\n";
   				cout<<"   PRECIO: $"<<Dulceria.Precio<<"\n";
   				cout<<"   CANTIDAD: "<<Dulceria.Cantidad_Productos<<"\n";
   				
				if(Renglon==3)
				{
   					Renglon=0;getch();
					system("cls");
					D_X(); D_Y();
					gotoxy(50,3);cout<<"[INVENTARIO GENERAL]";
				}
			}
			
	}while(!feof(pf_Productos));
	getch();
	fclose(pf_Productos);
}
void Consulta_Productos()
{
	system("cls");
	D_X(); D_Y();
	char Buscar[20]; int X=1,Contador_Registros_Existentes=0;
	pf_Productos= fopen("Productos.bin", "rb");
	if(pf_Productos==NULL)
	{
		gotoxy(50,10);cout<<"NO FUE POSIBLE ENCONTRAR EL ARCHIVO, PERO SE CREARA. ";
		pf_Productos =fopen("Productos.bin","wb");
		fclose(pf_Productos);
		pf_Productos =fopen("Productos.bin","rb");
	}
	fseek(pf_Productos, 0, SEEK_CUR );
	
	for(int x=2;x<=119;x++)
	{
		gotoxy(X,2);cout<<"~"; 
		gotoxy(X,4);cout<<"~"; 
		X++;
	}X=0;
	
	gotoxy(50,3);cout<<"[BUSCAR PRODUCTOS]";
	memset(Buscar,0,sizeof(Buscar));
	fseek(pf_Productos,0,0);
	gotoxy(26,5);cout<<"INGRESA EL NOMBRE DEL PRODUCTO:";gotoxy(58,5);gets(Buscar);
		
	do
	{
		memset(&Dulceria,0,sizeof(&Dulceria));
		fread(&Dulceria.ID_Producto,sizeof(Dulceria.ID_Producto),1,pf_Productos);
		fread(&Dulceria.Productos,sizeof(Dulceria.Productos),1,pf_Productos);
		fread(&Dulceria.Precio,sizeof(Dulceria.Precio),1,pf_Productos);
		fread(&Dulceria.Cantidad_Productos,sizeof(Dulceria.Cantidad_Productos),1,pf_Productos);
		fread(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Productos);
		fgetc(pf_Productos);
		fgetc(pf_Productos);
			
		if(!feof(pf_Productos) && strcmpi(Buscar, Dulceria.Productos)==0 && Dulceria.Bandera==0)
		{
			cout<<"\n";
			cout<<"CODIGO:";cout<<Dulceria.ID_Producto<<"\n";
			cout<<"PRODUCTO:";cout<<Dulceria.Productos<<"\n";
			cout<<"PRECIO: $";cout<<Dulceria.Precio<<"\n";
			cout<<"CANTIDAD:";cout<<Dulceria.Cantidad_Productos<<"\n";
			getch();
			Contador_Registros_Existentes++;
		}		
	}while(!feof(pf_Productos));
	
	fclose(pf_Productos);
}
void Consulta_Usuarios()
{
	system("cls");
	D_X(); D_Y();
	char Buscar[20]; int X=1,Contador_Registros_Existentes=0;
	pf_Usuarios= fopen("Usuarios.bin", "rb");
	if(pf_Usuarios==NULL)
	{
		gotoxy(50,10);cout<<"NO FUE POSIBLE ENCONTRAR EL ARCHIVO, PERO SE CREARA. ";
		pf_Usuarios =fopen("Usuarios.bin","wb");
		fclose(pf_Usuarios);
		pf_Usuarios =fopen("Usuarios.bin","rb");
	}
	fseek(pf_Usuarios, 0, SEEK_CUR );
	
	for(int x=2;x<=119;x++)
	{
		gotoxy(X,2);cout<<"~"; 
		gotoxy(X,4);cout<<"~"; 
		X++;
	}X=0;
	
	gotoxy(50,3);cout<<"[BUSCAR USUARIOS]";
	memset(Buscar,0,sizeof(Buscar));
	
	gotoxy(26,5);cout<<"INGRESA EL NOMBRE DEL USUARIO:";gotoxy(58,5);gets(Buscar);
		
	do
	{
		memset(&Dulceria,0,sizeof(&Dulceria));
		fread(&Dulceria.ID_Usuario,sizeof(Dulceria.ID_Usuario),1,pf_Usuarios);
		fread(&Dulceria.Usuarios,sizeof(Dulceria.Usuarios),1,pf_Usuarios);
		fread(&Dulceria.Clave_Usuario,sizeof(Dulceria.Clave_Usuario),1,pf_Usuarios);
		fread(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Usuarios);
		fgetc(pf_Usuarios);
		fgetc(pf_Usuarios);
					
		if(!feof(pf_Usuarios) && strcmpi(Buscar, Dulceria.Usuarios)==0 && Dulceria.Bandera==0)
		{
			cout<<"\n";
			cout<<"CODIGO:";cout<<Dulceria.ID_Usuario<<"\n";
			cout<<"USUARIO:";cout<<Dulceria.Usuarios<<"\n";
  			cout<<"CLAVE:";cout<<Dulceria.Clave_Usuario<<"\n";
			Contador_Registros_Existentes++;
			getch();
		}		
	}while(!feof(pf_Usuarios));
		
	if(Contador_Registros_Existentes==0)
	{
		system("cls"); system("color 0C");
		gotoxy(30,7);cout<<"NO EXISTE NINGUN PRODUCTO CON ESE NOMBRE.";
		Sleep(1200);
		system("color 0F");
	}
	fclose(pf_Usuarios);
}
void Edicion()
{
	system("cls");
	system("color 0F");
	D_X(); D_Y();
	int opcion_invalida; char opcion='\0';
	do
	{
		gotoxy(38,2);cout<<"INGRESA LA OPCION QUE DESEAS EDITAR.";
		gotoxy(38,4);cout<<"[ 1 ] PRODUCTOS.";
		gotoxy(38,5);cout<<"[ 2 ] USUARIO.";
		gotoxy(38,6);cout<<"[RRETROCESO] VOLVER A MENU.";
		gotoxy(43,7);opcion=getch();
		switch(opcion)
		{
			case 8:
				Menu();
			break;
			
			case 49://PRODUCTOS.
				Editar_Productos();
				opcion_invalida=0;
			break;
			
			case 50://USUARIOS.	
				Editar_Usuarios();
				opcion_invalida=0;
			break;
			
			default:
				if(opcion!=27)
				{
					Beep(1000,100);
					opcion_invalida=1;
				}
		}
	}while(opcion_invalida==1);
}
void Editar_Productos()
{
	system("cls"); system("color 0F");
	D_X(); D_Y();
	pf_Productos =fopen("Productos.bin","r+b");
	pf_Papelera_Productos =fopen("Papelera_Productos.bin","r+b");
	
	if(pf_Productos==NULL && pf_Papelera_Productos==NULL)
	{
		gotoxy(50,10);cout<<"NO FUE POSIBLE ENCONTRAR EL ARCHIVO, PERO SE CREARA. ";
		pf_Productos =fopen("Productos.bin","wb");
		pf_Papelera_Productos =fopen("Papelera_Productos.bin","Wb");
		fclose(pf_Productos);
		fclose(pf_Papelera_Productos);
		pf_Productos =fopen("Productos.bin","r+b");
		pf_Papelera_Productos =fopen("Papelera_Productos.bin","r+b");
	}
	int X=1,Contador_Productos=0,Contador_Registros_Existentes=0;
	char Buscar[20]; string resp;
	for(int x=2;x<=119;x++)
	{
		gotoxy(X,2);cout<<"~"; 
		gotoxy(X,4);cout<<"~"; 
		X++;
	}X=0;
	
	gotoxy(50,3);cout<<"[EDITAR PRODUCTOS]";
	memset(Buscar,0,sizeof(Buscar));
	
	gotoxy(26,5);cout<<"INGRESA EL NOMBRE DEL PRODUCTO:";gotoxy(58,5);gets(Buscar);
	do
	{
		memset(&Dulceria,0,sizeof(&Dulceria));
		fread(&Dulceria.ID_Producto,sizeof(Dulceria.ID_Producto),1,pf_Productos);
		fread(&Dulceria.Productos,sizeof(Dulceria.Productos),1,pf_Productos);
		fread(&Dulceria.Precio,sizeof(Dulceria.Precio),1,pf_Productos);
		fread(&Dulceria.Cantidad_Productos,sizeof(Dulceria.Cantidad_Productos),1,pf_Productos);
		fread(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Productos);
		fgetc(pf_Productos);
		fgetc(pf_Productos);
		Contador_Productos++;
		
		if(!feof(pf_Productos) && strcmpi(Buscar, Dulceria.Productos)==0 && Dulceria.Bandera==0)
		{
			gotoxy(26,8);cout<<"CODIGO:";gotoxy(43,8);cout<<Dulceria.ID_Producto;
			gotoxy(26,9);cout<<"PRODUCTO:";gotoxy(43,9);cout<<Dulceria.Productos;
  			gotoxy(26,10);cout<<"PRECIO:";gotoxy(43,10);cout<<Dulceria.Precio;
  			gotoxy(26,11);cout<<"CANTIDAD:";gotoxy(43,11);cout<<Dulceria.Cantidad_Productos;
   			Contador_Registros_Existentes++;
   			gotoxy(20,13);cout<<"Son estos los datos que desea eliminar?";
   			gotoxy(20,14);cout<<"Escribe Si/No.        ->";getline(cin,resp);
			
			if(resp=="Si"|resp=="si"|resp=="SI"|resp=="sI")
			{
				system("cls");
				char opcion_editar='\0';
				gotoxy(38,2);cout<<"INGRESA LA OPCION DEL PARTE QUE DESEAS EDITAR.";
				gotoxy(38,4);cout<<"[ 1 ] NOMBRE DEL PRODUCTO.";
				gotoxy(38,5);cout<<"[ 2 ] PRECIO DEL PRODUCTO.";
				gotoxy(38,6);cout<<"[ 3 ] CANTIDAD DEL PRODUCTO.";
				gotoxy(38,7);cout<<"[RRETROCESO] VOLVER A MENU.";
				gotoxy(43,8);opcion_editar=getch();
				
				if(opcion_editar==49)
				{
					system("cls");
					gotoxy(40,5);cout<<"[EDITAR NOMBRE DEL PRODUCTO]";
					gotoxy(40,6);cout<<"NOMBRE PRODUCTO:";
					gotoxy(57,6);getline(cin,productos);Producto_Validado();
					
					system("cls");
					//********************ESCRIBE EN EL ARCHIVO ORIGNIAL.*************************************//
					fseek(pf_Productos,(Contador_Productos-1)*41,0);
					fwrite(&Dulceria.ID_Producto,sizeof(Dulceria.ID_Producto),1,pf_Productos);
					fwrite(&Dulceria.Productos,sizeof(Dulceria.Productos),1,pf_Productos);
					fwrite(&Dulceria.Precio,sizeof(Dulceria.Precio),1,pf_Productos);
					fwrite(&Dulceria.Cantidad_Productos,sizeof(Dulceria.Cantidad_Productos),1,pf_Productos);
					fwrite(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Productos);
					fprintf(pf_Productos,"\r\n");
					fseek(pf_Productos,0,2);
					//********************ESCRIBE EN EL ARCHIVO ORIGNIAL.*************************************//
					
					//********************ESCRIBE EN EL ARCHIVO PAPELERA.*************************************//
					//41 BYTES.
					fseek(pf_Papelera_Productos,(Contador_Productos-1)*41,0);
					fwrite(&Dulceria.ID_Producto,sizeof(Dulceria.ID_Producto),1,pf_Papelera_Productos);
					fwrite(&Dulceria.Productos,sizeof(Dulceria.Productos),1,pf_Papelera_Productos);
					fwrite(&Dulceria.Precio,sizeof(Dulceria.Precio),1,pf_Papelera_Productos);
					fwrite(&Dulceria.Cantidad_Productos,sizeof(Dulceria.Cantidad_Productos),1,pf_Papelera_Productos);
					fwrite(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Papelera_Productos);
					fprintf(pf_Papelera_Productos,"\r\n");
					fseek(pf_Papelera_Productos,0,2);
					//********************ESCRIBE EN EL ARCHIVO PAPELERA.*************************************//
					
					system("cls"); system("color 0A");
					gotoxy(26,7);cout<<"NOMBRE DE PRODUCTO EDITADO CON EXITO.";
					Sleep(1200);
					system("color 0F");
					
				}
				else if(opcion_editar==50)
				{
					system("cls");
					gotoxy(40,5);cout<<"[EDITAR PRECIO DEL PRODUCTO]";
					gotoxy(40,7);cout<<"PRECIO:"; gotoxy(48,7);cout<<"$"; gotoxy(60,7);cout<<"(RECUERDA QUE EL PRECIO ES POR UNIDAD).";
					gotoxy(49,7);getline(cin,precio);Precio_Validado();
					
					system("cls");
					//********************ESCRIBE EN EL ARCHIVO ORIGNIAL.*************************************//
					fseek(pf_Productos,(Contador_Productos-1)*41,0);
					fwrite(&Dulceria.ID_Producto,sizeof(Dulceria.ID_Producto),1,pf_Productos);
					fwrite(&Dulceria.Productos,sizeof(Dulceria.Productos),1,pf_Productos);
					fwrite(&Dulceria.Precio,sizeof(Dulceria.Precio),1,pf_Productos);
					fwrite(&Dulceria.Cantidad_Productos,sizeof(Dulceria.Cantidad_Productos),1,pf_Productos);
					fwrite(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Productos);
					fprintf(pf_Productos,"\r\n");
					fseek(pf_Productos,0,2);
					//********************ESCRIBE EN EL ARCHIVO ORIGNIAL.*************************************//
					
					//********************ESCRIBE EN EL ARCHIVO PAPELERA.*************************************//
					//41 BYTES.
					fseek(pf_Papelera_Productos,(Contador_Productos-1)*41,0);
					fwrite(&Dulceria.ID_Producto,sizeof(Dulceria.ID_Producto),1,pf_Papelera_Productos);
					fwrite(&Dulceria.Productos,sizeof(Dulceria.Productos),1,pf_Papelera_Productos);
					fwrite(&Dulceria.Precio,sizeof(Dulceria.Precio),1,pf_Papelera_Productos);
					fwrite(&Dulceria.Cantidad_Productos,sizeof(Dulceria.Cantidad_Productos),1,pf_Papelera_Productos);
					fwrite(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Papelera_Productos);
					fprintf(pf_Papelera_Productos,"\r\n");
					fseek(pf_Papelera_Productos,0,2);
					//********************ESCRIBE EN EL ARCHIVO PAPELERA.*************************************//
					system("cls"); system("color 0A");
					gotoxy(26,7);cout<<"PRECIO DEL PRODUCTO EDITADO CON EXITO.";
					Sleep(1200);
					system("color 0F");
				}
				else if(opcion_editar==51)
				{
					system("cls");
					gotoxy(40,5);cout<<"[EDITAR LA CANTIDAD DEL PRODUCTO]";
					gotoxy(40,8);cout<<"CANTIDAD:";
					gotoxy(50,8);getline(cin,cantidad);Cantidad_Validado();
					
					system("cls");
					//********************ESCRIBE EN EL ARCHIVO ORIGNIAL.*************************************//
					fseek(pf_Productos,(Contador_Productos-1)*41,0);
					fwrite(&Dulceria.ID_Producto,sizeof(Dulceria.ID_Producto),1,pf_Productos);
					fwrite(&Dulceria.Productos,sizeof(Dulceria.Productos),1,pf_Productos);
					fwrite(&Dulceria.Precio,sizeof(Dulceria.Precio),1,pf_Productos);
					fwrite(&Dulceria.Cantidad_Productos,sizeof(Dulceria.Cantidad_Productos),1,pf_Productos);
					fwrite(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Productos);
					fprintf(pf_Productos,"\r\n");
					fseek(pf_Productos,0,2);
					//********************ESCRIBE EN EL ARCHIVO ORIGNIAL.*************************************//
					
					//********************ESCRIBE EN EL ARCHIVO PAPELERA.*************************************//
					//41 BYTES.
					fseek(pf_Papelera_Productos,(Contador_Productos-1)*41,0);
					fwrite(&Dulceria.ID_Producto,sizeof(Dulceria.ID_Producto),1,pf_Papelera_Productos);
					fwrite(&Dulceria.Productos,sizeof(Dulceria.Productos),1,pf_Papelera_Productos);
					fwrite(&Dulceria.Precio,sizeof(Dulceria.Precio),1,pf_Papelera_Productos);
					fwrite(&Dulceria.Cantidad_Productos,sizeof(Dulceria.Cantidad_Productos),1,pf_Papelera_Productos);
					fwrite(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Papelera_Productos);
					fprintf(pf_Papelera_Productos,"\r\n");
					fseek(pf_Papelera_Productos,0,2);
					//********************ESCRIBE EN EL ARCHIVO PAPELERA.*************************************//
					
					system("cls"); system("color 0A");
					gotoxy(26,7);cout<<"PRECIO DEL PRODUCTO EDITADO CON EXITO.";
					Sleep(1200);
					system("color 0F");
				}
				
			}
			else if(resp=="No"|resp=="no"|resp=="NO"|resp=="nO")
			{
				system("cls");
				system("color 0A");
				gotoxy(30,7);cout<<"ENTENDIDO, NO SE EDITARA.";
				Sleep(1200);
				system("color 0F");
			}
			else
			{
				system("cls");
				system("color 0C");
				gotoxy(30,7);cout<<"CARACTER INVALIDO.";
				Sleep(1200);
				system("color 0F");
			}
		}
		
	}while(!feof(pf_Productos));
	
	if(Contador_Registros_Existentes==0)
	{
		system("cls"); system("color 0C");
		gotoxy(30,7);cout<<"NO EXISTE NINGUN PRODUCTO CON ESE NOMBRE.";
		Sleep(1200);
		system("color 0F");
	}
	fclose(pf_Productos);
	fclose(pf_Papelera_Productos);
}
void Editar_Usuarios()
{
	system("cls"); system("color 0F");
	D_X(); D_Y();
	pf_Productos =fopen("Usuarios.bin","r+b");
	pf_Papelera_Usuarios =fopen("Papelera_Usuarios.bin","r+b");
	
	if(pf_Productos==NULL && pf_Papelera_Usuarios==NULL)
	{
		gotoxy(50,10);cout<<"NO FUE POSIBLE ENCONTRAR EL ARCHIVO, PERO SE CREARA. ";
		pf_Productos =fopen("Usuarios.bin","wb");
		pf_Papelera_Usuarios =fopen("Papelera_Usuarios.bin","Wb");
		fclose(pf_Productos);
		fclose(pf_Papelera_Usuarios);
		pf_Productos =fopen("Usuarios.bin","r+b");
		pf_Papelera_Usuarios =fopen("Papelera_Usuarios.bin","r+b");
	}
	int X=1,Contador_Usuarios=0,Contador_Registros_Existentes=0;
	char Buscar[20]; string resp;
	for(int x=2;x<=119;x++)
	{
		gotoxy(X,2);cout<<"~"; 
		gotoxy(X,4);cout<<"~"; 
		X++;
	}X=0;
	
	gotoxy(50,3);cout<<"[EDITAR USUARIOS]";
	memset(Buscar,0,sizeof(Buscar));
	
	gotoxy(26,5);cout<<"INGRESA EL NOMBRE DEL USUARIO:";gotoxy(58,5);gets(Buscar);
	do
	{
		memset(&Dulceria,0,sizeof(&Dulceria));
		fread(&Dulceria.ID_Usuario,sizeof(Dulceria.ID_Usuario),1,pf_Usuarios);
		fread(&Dulceria.Usuarios,sizeof(Dulceria.Usuarios),1,pf_Usuarios);
		fread(&Dulceria.Clave_Usuario,sizeof(Dulceria.Clave_Usuario),1,pf_Usuarios);
		fread(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Usuarios);
		fgetc(pf_Usuarios);
		fgetc(pf_Usuarios);
		Contador_Usuarios++;
		
		if(!feof(pf_Usuarios) && strcmpi(Buscar, Dulceria.Usuarios)==0 && Dulceria.Bandera==0)
		{
			gotoxy(26,8);cout<<"CODIGO:";gotoxy(50,8);cout<<Dulceria.ID_Usuario;
			gotoxy(26,9);cout<<"USUARIO:";gotoxy(50,9);cout<<Dulceria.Usuarios;
  			gotoxy(26,10);cout<<"CLAVE:";gotoxy(50,10);cout<<Dulceria.Clave_Usuario;
   			Contador_Registros_Existentes++;
   			gotoxy(20,13);cout<<"Son estos los datos que desea eliminar?";
   			gotoxy(20,14);cout<<"Escribe Si/No.        ->";getline(cin,resp);
			
			if(resp=="Si"|resp=="si"|resp=="SI"|resp=="sI")
			{
				system("cls");
				char opcion_editar='\0';
				gotoxy(38,2);cout<<"INGRESA LA OPCION DEL PARTE QUE DESEAS EDITAR.";
				gotoxy(38,4);cout<<"[ 1 ] NOMBRE DEL USUARIO.";
				gotoxy(38,5);cout<<"[ 2 ] CLAVE DEL USUARIO.";
				gotoxy(38,6);cout<<"[RRETROCESO] VOLVER A MENU.";
				gotoxy(43,7);opcion_editar=getch();
				
				if(opcion_editar==49)
				{
					system("cls");
					gotoxy(40,5);cout<<"[EDITAR NOMBRE DEL USUARIO]";
					gotoxy(40,7);cout<<"NOMBRE:";//Usuario.
					gotoxy(48,7);getline(cin,usuario);Usuario_Validado();
					
					system("cls");
					//********************ESCRIBE EN EL ARCHIVO ORIGNIAL.*************************************//
					fseek(pf_Usuarios,(Contador_Usuarios-1)*53,0);
					fwrite(&Dulceria.ID_Usuario,sizeof(Dulceria.ID_Usuario),1,pf_Usuarios);
					fwrite(&Dulceria.Usuarios,sizeof(Dulceria.Usuarios),1,pf_Usuarios);
					fwrite(&Dulceria.Clave_Usuario,sizeof(Dulceria.Clave_Usuario),1,pf_Usuarios);
					fwrite(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Usuarios);
					fprintf(pf_Usuarios,"\r\n");
					fseek(pf_Usuarios,0,2);
					//********************ESCRIBE EN EL ARCHIVO ORIGNIAL.*************************************//
					
					//********************ESCRIBE EN EL ARCHIVO PAPELERA.*************************************//
					//53 BYTES.
					fseek(pf_Papelera_Usuarios,(Contador_Usuarios-1)*53,0);
					fwrite(&Dulceria.ID_Usuario,sizeof(Dulceria.ID_Usuario),1,pf_Papelera_Usuarios);
					fwrite(&Dulceria.Usuarios,sizeof(Dulceria.Usuarios),1,pf_Papelera_Usuarios);
					fwrite(&Dulceria.Clave_Usuario,sizeof(Dulceria.Clave_Usuario),1,pf_Papelera_Usuarios);
					fwrite(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Papelera_Usuarios);
					fprintf(pf_Papelera_Usuarios,"\r\n");
					fseek(pf_Papelera_Usuarios,0,2);
					//********************ESCRIBE EN EL ARCHIVO PAPELERA.*************************************//
					
					system("cls"); system("color 0A");
					gotoxy(26,7);cout<<"NOMBRE DE PRODUCTO EDITADO CON EXITO.";
					Sleep(1200);
					system("color 0F");
					
				}
				else if(opcion_editar==50)
				{
					system("cls");
					gotoxy(40,5);cout<<"[EDITAR CLAVE DEL USUARIO]";
					gotoxy(40,8);cout<<"CLAVE:";//Contraseña.
					gotoxy(47,8);getline(cin,clave_usuario);Clave_Usuario_Validado();
					
					system("cls");
					//********************ESCRIBE EN EL ARCHIVO ORIGNIAL.*************************************//
					fseek(pf_Usuarios,(Contador_Usuarios-1)*53,0);
					fwrite(&Dulceria.ID_Usuario,sizeof(Dulceria.ID_Usuario),1,pf_Usuarios);
					fwrite(&Dulceria.Usuarios,sizeof(Dulceria.Usuarios),1,pf_Usuarios);
					fwrite(&Dulceria.Clave_Usuario,sizeof(Dulceria.Clave_Usuario),1,pf_Usuarios);
					fwrite(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Usuarios);
					fprintf(pf_Usuarios,"\r\n");
					fseek(pf_Usuarios,0,2);
					//********************ESCRIBE EN EL ARCHIVO ORIGNIAL.*************************************//
					
					//********************ESCRIBE EN EL ARCHIVO PAPELERA.*************************************//
					//53 BYTES.
					fseek(pf_Papelera_Usuarios,(Contador_Usuarios-1)*53,0);
					fwrite(&Dulceria.ID_Usuario,sizeof(Dulceria.ID_Usuario),1,pf_Papelera_Usuarios);
					fwrite(&Dulceria.Usuarios,sizeof(Dulceria.Usuarios),1,pf_Papelera_Usuarios);
					fwrite(&Dulceria.Clave_Usuario,sizeof(Dulceria.Clave_Usuario),1,pf_Papelera_Usuarios);
					fwrite(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Papelera_Usuarios);
					fprintf(pf_Papelera_Usuarios,"\r\n");
					fseek(pf_Papelera_Usuarios,0,2);
					//********************ESCRIBE EN EL ARCHIVO PAPELERA.*************************************//
					system("cls"); system("color 0A");
					gotoxy(26,7);cout<<"PRECIO DEL PRODUCTO EDITADO CON EXITO.";
					Sleep(1200);
					system("color 0F");
				}
			}
			else if(resp=="No"|resp=="no"|resp=="NO"|resp=="nO")
			{
				system("cls");
				system("color 0A");
				gotoxy(30,7);cout<<"ENTENDIDO, NO SE EDITARA.";
				Sleep(1200);
				system("color 0F");
			}
			else
			{
				system("cls");
				system("color 0C");
				gotoxy(30,7);cout<<"CARACTER INVALIDO.";
				Sleep(1200);
				system("color 0F");
			}
		}
		
	}while(!feof(pf_Productos));
	
	if(Contador_Registros_Existentes==0)
	{
		system("cls"); system("color 0C");
		gotoxy(30,7);cout<<"NO EXISTE NINGUN PRODUCTO CON ESE NOMBRE.";
		Sleep(1200);
		system("color 0F");
	}
	fclose(pf_Productos);
	fclose(pf_Papelera_Usuarios);
}
void Ventas()
{
	system("cls"); system("color 0F");
	D_X(); D_Y();
	pf_Ventas =fopen("Ventas.bin","ab");
	pf_Productos =fopen("Productos.bin","r+b");
	pf_Papelera_Productos =fopen("Papelera_Productos.bin","r+b");
	if(pf_Ventas==NULL && pf_Productos==NULL && pf_Papelera_Productos==NULL)
	{
		gotoxy(50,10);cout<<"NO FUE POSIBLE ENCONTRAR EL ARCHIVO, PERO SE CREARA. ";
		pf_Ventas =fopen("Ventas.bin","wb");
		pf_Productos =fopen("Productos.bin","wb");
		pf_Papelera_Productos =fopen("Papelera_Productos.bin","wb");
		fclose(pf_Ventas);
		fclose(pf_Productos);
		fclose(pf_Papelera_Productos);
		pf_Ventas =fopen("Ventas.bin","ab");
		pf_Productos =fopen("Productos.bin","r+b");
		pf_Papelera_Productos =fopen("Papelera_Productos.bin","r+b");
	}
	char Buscar[20];
	int Contador_Registros_Existentes=0,Total=0,Cambio=0,Contador_Productos=0;
	bool Encontrado;
	
	gotoxy(57,2);cout<<"[VENTAS]";
	
	Mostrar();//Función para mostrar los articulos disponibles en la tienda.
	
	fseek(pf_Productos,0,0);
	
	//REVISAR DESDE AQUI//POSIBLE CAUSA ERA QUE NO RECORRIA HASTA EL PRINCIPIO EL ARCHIVO.
	memset(Buscar,0,sizeof(Buscar));
	gotoxy(20,10);cout<<"ESCRIBE EL NOMBRE DEL PRODUCTO:";gotoxy(52,10);gets(Buscar);
	do
	{
		memset(&Dulceria,0,sizeof(&Dulceria));
		fread(&Dulceria.ID_Producto,sizeof(Dulceria.ID_Producto),1,pf_Productos);
		fread(&Dulceria.Productos,sizeof(Dulceria.Productos),1,pf_Productos);
		fread(&Dulceria.Precio,sizeof(Dulceria.Precio),1,pf_Productos);
		fread(&Dulceria.Cantidad_Productos,sizeof(Dulceria.Cantidad_Productos),1,pf_Productos);
		fread(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Productos);
		fgetc(pf_Productos);
		fgetc(pf_Productos);
		Contador_Productos++;
		if(!feof(pf_Productos) && strcmpi(Buscar, Dulceria.Productos)==0 && Dulceria.Bandera==0)
		{
			gotoxy(20,5);cout<<"CODIGO:";cout<<Dulceria.ID_Producto;
			gotoxy(20,6);cout<<"PRODUCTO:";cout<<Dulceria.Productos;
			gotoxy(20,7);cout<<"PRECIO: $";cout<<Dulceria.Precio<<"  (RECUERDA QUE EL PRECIO ES POR UNIDAD).";
			gotoxy(20,8);cout<<"CANTIDAD:";cout<<Dulceria.Cantidad_Productos;
			Contador_Registros_Existentes++;
			Encontrado=true;
		}		
	}while(!feof(pf_Productos)&&Encontrado==false);
	
	gotoxy(20,10);cout<<"SELECCIONA LA CANTIDAD QUE DESEA COMPRAR:";
	gotoxy(20,11);cout<<"TOTAL:";
	
	gotoxy(20,14);cout<<"ESCRIBE CON CUANTO PAGARAS:";gotoxy(48,14);cout<<"$";
	gotoxy(20,15);cout<<"CAMBIO: $";
	
	gotoxy(62,10);getline(cin,cantidad_comprar);Cantidad_Comprar_Validado();
	
	Dulceria.Total=(Dulceria.Precio*Dulceria.Cantidad_Productos_Comprados);
	gotoxy(29,11);cout<<Dulceria.Total;
	gotoxy(49,14);getline(cin,moneda);Moneda_Validado();
	Cambio=(Moneda-Dulceria.Total);
	gotoxy(30,15);cout<<Cambio;
	
	Dulceria.Auxiliar=Dulceria.Cantidad_Productos;
	memset(&Dulceria.Cantidad_Productos,0,sizeof(&Dulceria.Cantidad_Productos));
	Dulceria.Cantidad_Productos=Dulceria.Auxiliar-Dulceria.Cantidad_Productos_Comprados;
	
	cout<<"VALOR DE DULCERIA = "<<Dulceria.Cantidad_Productos;
	getch();
	//********************ESCRIBE EN EL ARCHIVO ORIGNIAL.*************************************//
	fseek(pf_Productos,(Contador_Productos-1)*41,0);
	fwrite(&Dulceria.ID_Producto,sizeof(Dulceria.ID_Producto),1,pf_Productos);
	fwrite(&Dulceria.Productos,sizeof(Dulceria.Productos),1,pf_Productos);
	fwrite(&Dulceria.Precio,sizeof(Dulceria.Precio),1,pf_Productos);
	fwrite(&Dulceria.Cantidad_Productos,sizeof(Dulceria.Cantidad_Productos),1,pf_Productos);
	fwrite(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Productos);
	fprintf(pf_Productos,"\r\n");
	fseek(pf_Productos,0,2);
	//********************ESCRIBE EN EL ARCHIVO ORIGNIAL.*************************************//
			
	//********************ESCRIBE EN EL ARCHIVO PAPELERA.*************************************//
	fseek(pf_Papelera_Productos,(Contador_Productos-1)*41,0);
	fwrite(&Dulceria.ID_Producto,sizeof(Dulceria.ID_Producto),1,pf_Papelera_Productos);
	fwrite(&Dulceria.Productos,sizeof(Dulceria.Productos),1,pf_Papelera_Productos);
	fwrite(&Dulceria.Precio,sizeof(Dulceria.Precio),1,pf_Papelera_Productos);
	fwrite(&Dulceria.Cantidad_Productos,sizeof(Dulceria.Cantidad_Productos),1,pf_Papelera_Productos);
	fwrite(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_Papelera_Productos);
	fprintf(pf_Papelera_Productos,"\r\n");
	fseek(pf_Papelera_Productos,0,2);
	//********************ESCRIBE EN EL ARCHIVO PAPELERA.*************************************//

	Fecha_y_Hora();
	fwrite(&Dulceria.Fecha,sizeof(Dulceria.Fecha),1,pf_Ventas);
	fwrite(&Dulceria.Hora,sizeof(Dulceria.Hora),1,pf_Ventas);
	fwrite(&Dulceria.ID_Producto,sizeof(Dulceria.ID_Producto),1,pf_Ventas);
	fwrite(&Dulceria.Productos,sizeof(Dulceria.Productos),1,pf_Ventas);
	fwrite(&Dulceria.Cantidad_Productos_Comprados,sizeof(Dulceria.Cantidad_Productos_Comprados),1,pf_Ventas);
	fwrite(&Dulceria.Total,sizeof(Dulceria.Total),1,pf_Ventas);
	fprintf(pf_Papelera_Productos,"\r\n");
	
	fclose(pf_Papelera_Productos);
	fclose(pf_Ventas);
	fclose(pf_Productos);
}
void Mostrar()
{
	D_X(); D_Y();
	char Buscar[20]; int X=1,Renglon=0,Registro=0;
	pf_A= fopen("Productos.bin", "rb");
	if(pf_A==NULL)
	{
		gotoxy(50,10);cout<<"NO FUE POSIBLE ENCONTRAR EL ARCHIVO, PERO SE CREARA. ";
		pf_A =fopen("Productos.bin","wb");
		fclose(pf_A);
		pf_A =fopen("Productos.bin","rb");
	}
	for(int x=2;x<=119;x++)
	{
		gotoxy(X,3);cout<<"~"; 
		gotoxy(X,5);cout<<"~"; 
		X++;
	}X=0;
	
	gotoxy(40,4);cout<<"[PRODUCTOS DISPONIBLES EN LA TIENDA]";
	do
	{
		memset(&Dulceria,0,sizeof(&Dulceria));
		fread(&Dulceria.ID_Producto,sizeof(Dulceria.ID_Producto),1,pf_A);
		fread(&Dulceria.Productos,sizeof(Dulceria.Productos),1,pf_A);
		fread(&Dulceria.Precio,sizeof(Dulceria.Precio),1,pf_A);
		fread(&Dulceria.Cantidad_Productos,sizeof(Dulceria.Cantidad_Productos),1,pf_A);
		fread(&Dulceria.Bandera,sizeof(Dulceria.Bandera),1,pf_A);
		fgetc(pf_A);
		fgetc(pf_A);
		
		Renglon++;
		Registro++;
		
		if(!feof(pf_A) && Dulceria.Bandera==0)
			{
				gotoxy(20,5+(Registro*5));cout<<"CODIGO: "<<Dulceria.ID_Producto;
   				gotoxy(20,6+(Registro*5));cout<<"PRODUCTO: "<<Dulceria.Productos;
   				gotoxy(20,7+(Registro*5));cout<<"PRECIO: $"<<Dulceria.Precio<<"(RECUERDA QUE ES POR UNIDAD).";
   				gotoxy(20,8+(Registro*5));cout<<"CANTIDAD: "<<Dulceria.Cantidad_Productos;
   				
				if(Renglon==3)
				{
   					Renglon=0; Registro=0; getch();
					system("cls");
					D_X(); D_Y();
					for(int x=2;x<=119;x++)
					{
						gotoxy(X,3);cout<<"~"; 
						gotoxy(X,5);cout<<"~"; 
						X++;
					}X=0;
					gotoxy(50,4);cout<<"[PRODUCTOS DISPONIBLES EN LA TIENDA]";
				}
			}
			
	}while(!feof(pf_A));
	fclose(pf_A);
	getch();
	system("cls");
	D_X(); D_Y();
	for(int x=2;x<=119;x++)
	{
		gotoxy(X,3);cout<<"~"; 
		gotoxy(X,5);cout<<"~"; 
		X++;
	}X=0;
	gotoxy(50,4);cout<<"[PRODUCTOS DISPONIBLES EN LA TIENDA]";
	gotoxy(57,2);cout<<"[VENTAS]";
}

void Fecha_y_Hora()
{
	time_t now= time(0);//Fecha y hora basado en el sistema actual.
	tm * time= localtime(&now);//OBjeto de una estructura tm con fehca/hora local.
	
	vector<string> Mes;
	Mes.push_back("Enero");
	Mes.push_back("Febrero");
	Mes.push_back("Marzo");
	Mes.push_back("Abril");
	Mes.push_back("Mayo");
	Mes.push_back("Junio");
	Mes.push_back("Julio");
	Mes.push_back("Agosto");
	Mes.push_back("Septiembre");
	Mes.push_back("Octubre");
	Mes.push_back("Noviembre");
	Mes.push_back("Diciembre");
	
	char dia[2],mes[12],yearchar[4],hora[2],minuto[2],segundo[2]; string MesString; int Longitud=0, year =1990+time->tm_year;
	
	MesString=Mes[time->tm_mon];//Se le asigna el La variable/Arreglo Mes string a MesString que solo es String.
	Longitud=MesString.length();//Se le saca la longitud al mes.
	for(int x=0;x<=Longitud;x++)
	{
		mes[x]=MesString[x];//Convierte el MesString en MesChar;
	}
	//Para vaciar las variables char y no haya basura en un futuro.
	memset(&Dulceria.Fecha,0,sizeof(&Dulceria.Fecha));
	memset(&Dulceria.Hora,0,sizeof(&Dulceria.Hora));
	
	itoa(time->tm_mday,dia,10);//Convierte el dia en char.
	strcat(Dulceria.Fecha,dia);//Concatena el dia char en la variable estructura.
	strcat(Dulceria.Fecha,"/");//Concatena el separador del dia.
	strcat(Dulceria.Fecha,mes);//Concatena el mes a la variable de la estructura.
	strcat(Dulceria.Fecha,"/");//Concatena el separador del mes.
	itoa(year,yearchar,10);//Convierte el año entero en un char.
	strcat(Dulceria.Fecha,yearchar);//Concatena por ultimo el año a la variable estructura.
	strcat(Dulceria.Fecha," ");
	
	itoa(time->tm_hour,hora,10);//Convierte la hora entera en un char.
	itoa(time->tm_min,minuto,10);//Convierte el minuto entero en un char.
	itoa(time->tm_sec,segundo,10);//Convierte el segundo entero en un char.
	strcat(Dulceria.Hora,hora);//Concatena la hora a la variable de la estructura.
	strcat(Dulceria.Hora,":");//Concatena el separador de la hora a la variable estructura.
	strcat(Dulceria.Hora,minuto);//Concatena el minuto a la variable estructura.
	strcat(Dulceria.Hora,":");//concatena el separador del minuto a la variable estructura.
	strcat(Dulceria.Hora,segundo);//Concatena el segundo a la variable estructura.}
	strcat(Dulceria.Hora," ");
}






/***************************************************************************FUNCIONES***************************************************************/

/***************************************************************************VALIDADCIONES***************************************************************/
void Usuario_Validado()
{
	string Validar;
	int Longitud=0;
	size_t correcto;
	
	do
	{
		Validar=usuario;
		correcto= Validar.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ  ");
		Longitud= Validar.length();
		
		if(correcto !=std::string::npos | Longitud<=2 | Longitud>20|Validar[0]==32)
		{
			Beep(1000,100);
			system("color 0C");
			gotoxy(48,7);cout<<"ERROR                                   ";
			Sleep(1500);
			gotoxy(48,7);cout<<"                                   ";
			system("color 0F");
			gotoxy(40,7);cout<<"NOMBRE:";gotoxy(48,7);getline(cin,Validar);
		
			correcto = Validar.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXY  ");
			Longitud=Validar.length();
		}
	}while(correcto != std::string::npos | Longitud<=2 | Longitud>20|Validar[0]==32);
	
	memset(Dulceria.Usuarios,0,sizeof(Dulceria.Usuarios));
		
	for(int y=0; y<Longitud; y++)
	{
		Dulceria.Usuarios[y]=Validar[y];
	}
}

void Producto_Validado()
{
	string Validar;
	int Longitud=0;
	size_t correcto;
	
	do
	{
		Validar=productos;
		correcto= Validar.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ  ");
		Longitud= Validar.length();
		
		if(correcto !=std::string::npos | Longitud<=2 | Longitud>20|Validar[0]==32)
		{
			Beep(1000,100);
			system("color 0C");
			gotoxy(57,6);cout<<"ERROR                                   ";
			Sleep(1500);
			gotoxy(57,6);cout<<"                                   ";
			system("color 0F");
			gotoxy(40,6);cout<<"NOMBRE PRODUCTO:";gotoxy(57,6);getline(cin,Validar);
		
			correcto = Validar.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ");
			Longitud=Validar.length();
		}
	}while(correcto != std::string::npos | Longitud<=2 | Longitud>20|Validar[0]==32);
	
	memset(Dulceria.Productos,0,sizeof(Dulceria.Productos));
		
	for(int y=0; y<Longitud; y++)
	{
		Dulceria.Productos[y]=Validar[y];
	}
	
}

void Clave_Usuario_Validado()
{
	string Validar;
	int Longitud=0;
	size_t correcto;
	
	do
	{
		Validar=clave_usuario;
		correcto= Validar.find_first_not_of("0987654321abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
		Longitud= Validar.length();
		
		if(correcto !=std::string::npos | Longitud<2 | Longitud>20|Validar[0]==32)
		{
			Beep(1000,100);
			system("color 0C");
			gotoxy(47,8);cout<<"ERROR                                   ";
			Sleep(1500);
			gotoxy(47,8);cout<<"                                   ";
			system("color 0F");
			gotoxy(40,8);cout<<"CLAVE:";gotoxy(47,8);getline(cin,Validar);
		
			correcto = Validar.find_first_not_of("0987654321abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
			Longitud=Validar.length();
		}
	}while(correcto != std::string::npos | Longitud<2 | Longitud>20|Validar[0]==32);

	memset(Dulceria.Clave_Usuario,0,sizeof(Dulceria.Clave_Usuario));
	for(int y=0; y<Longitud; y++)
	{
		Dulceria.Clave_Usuario[y]=Validar[y];
	}
}

void Cantidad_Validado()
{
	string Validar;
	int Longitud=0;
	size_t correcto;
	
	do
	{
		Validar=cantidad;
		correcto= Validar.find_first_not_of("0987654321 ");
		Longitud= Validar.length();
		
		if(correcto !=std::string::npos | Longitud<1 | Longitud>3|Validar[0]==32)
		{
			system("color 0C");
			Beep(1000,100);
			gotoxy(50,8);cout<<"ERROR                            ";
			Sleep(1500);
			system("color 0F");
			gotoxy(50,8);cout<<"                                   ";
			gotoxy(40,8);cout<<"CANTIDAD:";gotoxy(50,8);getline(cin,Validar);
		
			correcto = Validar.find_first_not_of("0987654321 ");
			Longitud=Validar.length();
		}
	}while(correcto != std::string::npos | Longitud<1 | Longitud>3|Validar[0]==32);
	
	Dulceria.Cantidad_Productos=0;
	Dulceria.Cantidad_Productos=atoi(Validar.c_str());
}

void Precio_Validado()
{
	string Validar;
	int Longitud=0;
	size_t correcto;
	
	do
	{
		Validar=precio;
		correcto= Validar.find_first_not_of("0987654321 ");
		Longitud= Validar.length();
		
		if(correcto !=std::string::npos | Longitud<1 | Longitud>3|Validar[0]==32)
		{
			system("color 0C");
			Beep(1000,100);
			gotoxy(48,7);cout<<"ERROR                                              ";
			Sleep(1500);
			system("color 0F");
			gotoxy(48,7);cout<<"                                                    ";
			gotoxy(40,7);cout<<"PRECIO:";gotoxy(48,7);cout<<"$";gotoxy(49,7);
			getline(cin,Validar); gotoxy(60,7);cout<<"(RECUERDA QUE EL PRECIO ES POR UNIDAD).";
		
			correcto = Validar.find_first_not_of("0987654321 ");
			Longitud=Validar.length();
		}
	}while(correcto != std::string::npos | Longitud<1 | Longitud>3|Validar[0]==32);
	
	Dulceria.Precio=0;
	Dulceria.Precio=atoi(Validar.c_str());
}
void Cantidad_Comprar_Validado()
{
	string Validar,Auxliar_Cantidad;
	int Longitud=0,Validar2=0,Productos_Disponibles=0;
	size_t correcto;
	
	do
	{
		Validar=cantidad_comprar;
		correcto= Validar.find_first_not_of("0987654321 ");
		Longitud= Validar.length();
		
		/*Productos_Disponibles=Dulceria.Cantidad_Productos;
		Auxliar_Cantidad=cantidad_comprar;
		Validar2=atoi(Auxliar_Cantidad.c_str());*/
		
		if(correcto !=std::string::npos | Longitud<1 | Longitud>3|Validar[0]==32|Validar2>Productos_Disponibles)
		{
			system("color 0C");
			Beep(1000,100);
			gotoxy(62,10);cout<<"ERROR                            ";
			Sleep(1500);
			system("color 0F");
			gotoxy(62,10);cout<<"                                   ";
			gotoxy(20,10);cout<<"SELECCIONA LA CANTIDAD QUE DESEA COMPRAR:";gotoxy(62,10);getline(cin,Validar);
		
			correcto = Validar.find_first_not_of("0987654321 ");
			Longitud=Validar.length();
		}
	}while(correcto != std::string::npos | Longitud<1 | Longitud>3|Validar[0]==32|Validar2>Productos_Disponibles);
	
	Dulceria.Cantidad_Productos_Comprados=0;
	Dulceria.Cantidad_Productos_Comprados=atoi(Validar.c_str());
}

void Moneda_Validado()
{
	string Validar,Auxiliar_Total;
	int Longitud=0,Costo_Total=0,Validar2=0;
	size_t correcto;

	do
	{
		Validar=moneda;
		correcto= Validar.find_first_not_of("0987654321 ");
		Longitud= Validar.length();
		
		Costo_Total=Dulceria.Total;
		Auxiliar_Total=moneda;
		Validar2=atoi(Auxiliar_Total.c_str());
		
		if(correcto !=std::string::npos | Longitud<1 | Longitud>3|Validar[0]==32|Validar2<Costo_Total)
		{
			system("color 0C");
			Beep(1000,100);
			gotoxy(48,14);cout<<"ERROR                                              ";
			Sleep(1500);
			system("color 0F");
			gotoxy(48,14);cout<<"                                                    ";
			gotoxy(20,14);cout<<"ESCRIBE CON CUANTO PAGARAS:";gotoxy(48,14);cout<<"$";gotoxy(49,14);getline(cin,Validar);
			correcto = Validar.find_first_not_of("0987654321 ");
			Longitud=Validar.length();
		}
	}while(correcto != std::string::npos | Longitud<1 | Longitud>3|Validar[0]==32|Validar2<Costo_Total);
	
	Moneda=0;
	Moneda=atoi(Validar.c_str());	
}
/***************************************************************************VALIDADCIONES***************************************************************/

//****************************************************************DISEÑO******************************************************************************//
void D_X()
{
	int X=0;
	for(int x=0;x<=119;x++)
	{
		gotoxy(X,0);cout<<"°";
		X++;
	}
	X=0;
	for(int x=0;x<=119;x++)
	{
		gotoxy(X,29);cout<<"°";
		X++;
	}
}
void D_Y()
{
	int Y=0;
	for(int y=0;y<=29;y++)
	{
		gotoxy(0,Y);cout<<"°";
		Y++;
	}
	Y=0;
	for(int y=0;y<=29;y++)
	{
		gotoxy(119,Y);cout<<"°";
		Y++;
	}
}
//****************************************************************DISEÑO******************************************************************************//	

/************************************************************************FUNCION GOTXY******************************************************************/
void gotoxy(int x, int y)
{
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon,dwPos);
}
/************************************************************************FUNCION GOTXY******************************************************************/

/*************************************************************METODO DE DES/ENCRIPTAMIENTO*************************************************************/
/*void Encriptar()
{
	char car='\0';
	
	pf_A=fopen(Nombre_Archivo,"rb");
   	pf=fopen(Nombre_Archivo,"r+b");
    if(pf==NULL && pf_A==NULL)
	{
    	cout<<"Error al abrir el archivo nuevo\n";
    }
    while(fread(&car,1,1,pf_A)!=0)
	{
     	if(car=='\r' && car=='\n')
        {
        	fprintf(pf,"\r\n");
		}
		car+=20;
        fwrite(&car,1,1,pf);
    }
    fclose(pf);
    fclose(pf_A);
}

void Desencriptar()
{
	char car='\0';
    pf_A=fopen(Nombre_Archivo,"rb");
    pf=fopen(Nombre_Archivo,"r+b");
	if(pf==NULL && pf_A==NULL)
	{
     	cout<<"Error al abrir el archivo nuevo\n";
    }
	while(fread(&car,1,1,pf_A)!=0)
	{
    	car-=20;
    	fwrite(&car,1,1,pf);
   	}
   	fclose(pf);
    fclose(pf_A);
}

void Comprobar()
{
	pf=fopen(Nombre_Archivo,"rb");
				int contador=0;
				do
				{
					fread(&CD,sizeof(&CD),1,pf);
					if(!feof(pf))
					{
						contador++;
					}
				}while(!feof(pf));
				if(contador!=0)
				{
					Desencriptar();
				}
				fclose(pf);
}
*/
/*************************************************************METODO DE DES/ENCRIPTAMIENTO*************************************************************/
