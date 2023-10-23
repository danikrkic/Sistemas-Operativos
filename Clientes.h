#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct clavesacceso{
	char* contrasena;
	char* usuario;
} clavesAcceso;

typedef struct informacionPersonal
{
	char* nombre;
	int edad;
	char* curp;
	int telefono;
	char* domicilio;
	char* RFC;

}I_Personal;

typedef struct informacionBancaria
{
	int numCuenta;
	int estadoCuenta;
	char* nombreBanco;

}I_Bancaria;

typedef I_Personal* I_PERSONAL;
typedef I_Bancaria* I_BARNCARIA;
typedef clavesAcceso* C_ACCESO;

typedef struct clientes
{
	struct clientes* siguiente;
	struct clientes* anterior;

	I_PERSONAL infoPersonal;
	I_BARNCARIA infoBancaria;
	C_ACCESO Claves;
	
}Cliente;


int obtenerLongitudCadena(char* arreglo){
	if(arreglo == NULL)
	{
		puts("error! nombre vacio");
		exit(0);
	}

	int iterador = 0;

	while(*(arreglo + iterador) != '\n')
	{
		iterador++;
	}

	return iterador;

}

void obtenerCURP(char* arreglo)
{

	char CURP[18];
	puts("ingrese el curp");
	scanf("%['\n']",CURP);
	arreglo = (char*)malloc(sizeof(char)*18);
	strcpy(arreglo,CURP);


}


void obtenerNombre(char* arreglo)
{
	char nombre[50];
	if (fgets(nombre, sizeof(nombre), stdin) != NULL) {
        printf("Has ingresado: %s", nombre);
    } else {
        printf("Error al leer la línea.");
        exit(0);
    }
	arreglo = (char*)malloc(sizeof(char)*obtenerLongitudCadena(nombre));
	strcpy(arreglo, nombre);
}

int obtenerEdad()
{
	puts("Ingrese su edad:");
	int edad;
	scanf("%d",&edad);

	return edad;
}

int obtenerTelefono()
{
	puts("")
}

void llenarInfoPersonal(I_PERSONAL nuevoIPersonal)
{
	if(nuevoIPersonal == NULL)
	{
		puts("Error al crear espacio para la informacion personal");
		exit(0);
	}

	obtenerNombre(nuevoIPersonal->nombre);	
	nuevoIPersonal->edad = obtenerEdad();
	obtenerCURP(nuevoIPersonal->curp);

}

I_PERSONAL crearIPERSONAL()
{
	I_PERSONAL nuevoIPersonal = (I_PERSONAL)malloc(sizeof(I_Personal));

	if(nuevoIPersonal ==  NULL)
	{
		puts("Error al almacenar la informacion personal");
		exit(0);
	}
	

	return nuevoIPersonal;
}


I_BARNCARIA crearIBANCARIA()
{
	I_BARNCARIA nuevoIBancaria = (I_BARNCARIA)malloc(sizeof(I_Bancaria));
	if(nuevoIBancaria == NULL)
	{
		puts("Error al ingresar la informacion bancaria");
		exit(0);
	}	

	return nuevoIBancaria; 
}

C_ACCESO nuevoAcceso()
{
	C_ACCESO nuevasClaves = (C_ACCESO)malloc(sizeof(clavesAcceso));

	if(nuevasClaves == NULL)
	{
		puts("Error al crear las credenciales del usuario");
		exit(0);
	}
	
	return nuevasClaves;
}
