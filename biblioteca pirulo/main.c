#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "string.h"

#define ESC 27

//!   cant de dias - deuda
#define DEUDA3DIAS 50
#define DEUDA15DIAS 100
#define DEUDA90DIAS 400

///--------------------------------ESTRUCTURAS--------------------------------------------------

typedef struct
{
    int dia;
    int mes;
    int anio;
} Fecha;

typedef struct
{
    char nombre[30];
    char apellido[30];
    int anioNacimiento;
    char paisNacimiento[30];

} Autor;

typedef struct
{
    Autor caracteristicas;
    char titulo[30];
    int cantPaginas;
    char genero[30];
    char editorial[30];
    int anioLanzamiento;
    int tipoLibro; //1- tapa dura, 2- tapa blanda, 3- ed.bolsillo
    char isbn[30];
    int diasPrestamo; //cant de dias validos
    int cantPrestamos; //cant de veces que se presto
    float puntuacion; //puntuacion del cliente una vez devuelto
    int estado; //1 prestado 2 disponible

} Libro;

typedef struct
{
    char calle[30];
    int numero;
    char municipio[30];

} Direccion;

typedef struct
{
    char nombre[30];
    char apellido[30];
    Fecha Nacimiento;
    char dni[10];
    Direccion domicilio;
    char telefono[30];
    char email[30];
    int deuda;
    int cantLibros; //!los libros que tiene prestados la persona

} Persona;

typedef struct
{
    char idInterno[30];
    char isbn[30];
    int estado;//1-prestada, 2-disponible

} Copia;

typedef struct
{
    char idInterno[30];
    char dni[10];
    Fecha retirado;
    Fecha devolucion;

} Prestamo;

typedef struct
{
    char genero [30];
} GeneroStruct;

///-------------------------PROTOTIPADO--------------------------------------------
void menu();
Libro cargaUnLibro(char num[30],char archiGenero[]);
Copia cargaCopia(char copiaArchi[30], char codigo[30]);
int posIdInternoCopia(char copiaArchi[30], char dato [30]);
void cargaLibros(char archivo[30], char archiCopia[30],char archiGenero[]);
int posISBNlibro(char archivo[30], char clave[30]);
void buscarLibro(char archLibro [30],char archiCopia [30],char archiGenero[]);
void buscarXestado(char archi[30], char copiaArchi[30]);
void buscarEstados(char archi[30], char copiaArchi[30], int estado);
void buscarXgenero(char archi[30], char copiaArchi[30],char archiGenero[]);
void buscarXtitulo(char archi[30], char copiaArchi[30]);
void buscarXisbn(char archi[30], char copiaArchi[30]);
void buscarXautor(char archi[30], char copiaArchi[30]);
void buscarXidInterno(char archi[30], char copiaArchi[30]);
void mostrarLibro(Libro librito, int num);
void mostrarCopia(Copia ditto);
void muestraLibroXpos(char archi[30], int pos, char isbn[30], int num);
void muestraCopiaXpos(char copiaArchi[30], int posCopia);
void menuBuscaLibro();
int posAutorLibro(char archivo[30], char nombre[30],char apellido[30], int pos);
int posEstadoCopia(char archivo[30],int estado,int pos, int isbn);
int posISBNcopia(char archivo[30], char clave[30], int pos);
int posTituloLibro(char archivo[30], char titulo[30], int pos);
int posGeneroLibro(char archivo[30], char genero[30], int pos);
void ingresaGenero(char archiGenero[], char genero[30]);
int mostrarGenero(char archiGenero[], char genero[30]);
void ingresaGeneroPos(char archiGenero[], char genero[], int pos);
void cargarGeneroNuevo(char archiGenero[], char genero[30]);
int buscar_pos_usuario(char archivo[],char dniIngresado[30]);
void mostrar_usuario(Persona p);
Persona cargar_datos_persona(char dniIngresado[30]);
Persona buscar_persona_segun_pos(char archivo[],int pos);
void ingreso_Dni(char dni[30]);
void nuevo_usuario(char archivo[]);
void verificacion_usuario(char archivo[30]);
Prestamo carga_datos_entrega(char idInternoIngresado[30],char dniIngresado[10]);
void sumar_posesion(char archivo[],int pos);
Copia buscar_copia_segun_pos(char archivo[],int pos);
void cambiar_estado_prestado(char archivo[],int pos);
int buscar_pos_libro(char archivo[],char isbn[30]);
Libro buscar_libro_segun_pos(char archivo[],int pos);
void aumentar_cantPrestamos_libro(char archivo[],int pos);
void nuevo_prestamo(char archiPrestamos[],char archiLibros[],char archiCopiaLibros[],char archiUsuarios[]);
int buscar_id_prestamos(char archPrestamos[],char idIngresado[30]);
Prestamo buscar_prestamo_segun_pos(char archPrestamos[],int posId);
void mostrar_prestamo_hecho(Prestamo entregaHecha);
Prestamo cargar_fecha_devolucion(char archPrestamos[],int posId);
int cantidad_dias_prestados(Prestamo devolucionHecha);
int calcular_deuda(int cantDias, int cantDiasPermitidos);
void cargar_deuda_usuario(char archivo[],int pos,int deuda);
void puntuar_libro(char archivo[],int pos);
void cambiar_estado_disponible(char archivo[],int pos);
void decrementar_prestacion(char archivo[],int pos);
void nueva_devolucion(char archPrestamos[],char archLibros[],char archCopias[],char archUsuarios[]);
int pasar_libros(char archiLibros[],Libro libros[500]);
void intercambiar_datos(Libro libros[500],int origen,int destino);
void ordenamiento_insercion(Libro libros[500],int validos);
void escribir_top(char archiTop[],int validos,Libro libros[500]);
void mostar_top(char archiTop[],int validos);
void libros_populares(char archiLibros[],char archiTop[]);
///-----------------------------MAIN--------------------------------------------

int main()
{
    /**NOMBRES DE ARCHIVOS**/
    char opcion;
    char archiLibro[]="archLibro.info";
    char archiUsuario[]="archUsuario.info";
    char archiCopiaLibro[]="archCopia.info";
    char archiGeneros[]="archGeneros.info";
    char archiPrestamo[]="archPrestamo.info";
    char archiTop10[]="archTop.info";

    do
    {
        system("cls");//limpia pantalla
        Beep(300,100);//sonido

        system("COLOR 8f");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);

        printf(" _____________________________________________________\n");
        printf("               BIBLIOTECA PIRULO                       \n");
        printf(" _____________________________________________________\n");

        printf("       .--.           .---.        .-.\n");
        printf("   .---|--|   .-.     | A |  .---. |~|    .--.\n");
        printf(".--|===|Ch|---|_|--.__| S |--|:::| |~|-==-|==|---.\n");
        printf("|%%%%|NT2|oc|===| |~~|%%%%| C |--|   |_|~|CATS|  |___|-.\n");
        printf("|  |   |ah|===| |==|  | I |  |:::|=| |    |GB|---|=|\n");
        printf("|  |   |ol|   |_|__|  | I |__|   | | |    |  |___| |\n");
        printf("|~~|===|--|===|~|~~|%%%%|~~~|--|:::|=|~|----|==|---|=|\n");
        printf("^--^---'--^---^-^--^--^---'--^---^-^-^-==-^--^---^-'\n");

        printf("_____________________________________________________\n");
        printf("                      MENU                       \n");
        printf("_____________________________________________________\n");


        menu();

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
        fflush(stdin);
        scanf("%c", &opcion);
        Beep(600,100);

        system("cls");

        switch(opcion)
        {
        case 48:
            printf("\nChau!\n");
            break;

        case 49:
            //cargar un nuevo libro
            cargaLibros(archiLibro, archiCopiaLibro, archiGeneros);
            break;

        case 50:
            //cargar un nuevo usuario
            nuevo_usuario(archiUsuario);
            break;

        case 51:
            //verificacion de existenia de usuario
            verificacion_usuario(archiUsuario);
            system("pause");
            break;

        case 52:
            //cargar un prestamo
            nuevo_prestamo(archiPrestamo,archiLibro,archiCopiaLibro,archiUsuario);
            break;

        case 53:
            //cargar una devolucion
            nueva_devolucion(archiPrestamo,archiLibro,archiCopiaLibro,archiUsuario);
            break;

        case 54:
            //buscar libro
            buscarLibro(archiLibro,archiCopiaLibro,archiGeneros);
            break;

        case 55:
            //top 10 mejor puntuacion
            libros_populares(archiLibro,archiTop10);
            break;

        default:
            Beep(70,200);//sonido
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 | BACKGROUND_INTENSITY);
            printf("\nError: opcion no valida.\n");
            system("pause");
        }


        system("cls");

    }while(opcion!=48);

    return 0;
}

///-----------------------------FUNCIONES--------------------------------------------

void menu()
{
    printf("        CARGAS      \n");
    printf("1. Cargar un nuevo libro\n");
    printf("2. Cargar un nuevo usuario\n\n");
    printf("        USUARIO      \n");
    printf("3. Buscar un usuario\n");
    printf("4. Cargar un prestamo\n");
    printf("5. Cargar una devolucion\n\n");
    printf("        LIBROS      \n");
    printf("6. Buscar un libro\n");
    printf("7. Mostrar top 10\n");

    printf("\n0. Para salir\n");
}

Libro cargaUnLibro(char num[30],char archiGenero[])
{
    Libro librito;//defino un dato de tipo libro
    int flag=0;//inicializo una bandera en 0
    char genero[30];

    //copio el isbn ya ingresado antes de la verificacion
    strcpy(librito.isbn,num);

    librito.cantPrestamos=0;//inicializo la cantidad de prestamos en 0
    librito.puntuacion=0;//inicializo la puntuacion en 0

    ///ingreso de datos
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("\nTitulo: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    gets(librito.titulo);
    Beep(600,100);//sonido

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("\nCantidad de paginas: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    scanf("%d", &librito.cantPaginas);
    Beep(600,100);//sonido

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("\nGenero: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    //da opciones de genero ingresadas anteriormente o cargar nuevo
    ingresaGenero(archiGenero, genero);
    strcpy(librito.genero,genero);//copio el genero ingresado en librito


    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("\nEditorial: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    gets(librito.editorial);
    Beep(600,100);//sonido

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("\nAnio de lanzamiento: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    scanf("%d", &librito.anioLanzamiento);
    Beep(600,100);//sonido

    do
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
        //pregunta el tipo de libro hasta que de una opcion valida
        printf("\nTipo de libro: \n");
        printf("               1. Tapa dura\n");
        printf("               2. Tapa blanda\n");
        printf("               3. Ed. bolsillo\n");

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
        fflush(stdin);
        scanf("%d", &librito.tipoLibro);
        Beep(600,100);//sonido

        //verifico que la opcion sea valida
        if((librito.tipoLibro!=1)&&(librito.tipoLibro!=2)&&(librito.tipoLibro!=3))
        {
            //si ingreso una opcion no valida le informa
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 | BACKGROUND_INTENSITY);
            Beep(70,200);//sonido
            printf("\nERROR: Opcion no valida, vuelva a intentarlo.\n");
            system("pause");
        }
        else
        {
            flag=1;
        }
    }
    while(flag==0);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("\nPlazo de prestamo (dias): ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    scanf("%d", &librito.diasPrestamo);
    Beep(600,100);//sonido


    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    //ingresando datos del autor
    printf("DATOS DEL AUTOR\n");
    printf("------------------------------------------------------\n");

    printf("\nNombre del autor: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    gets(librito.caracteristicas.nombre);
    Beep(600,100);//sonido

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("\nApellido del autor: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    gets(librito.caracteristicas.apellido);
    Beep(600,100);//sonido

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("\nAnio de nacimiento: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    scanf("%d", &librito.caracteristicas.anioNacimiento);
    Beep(600,100);//sonido

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("\nPais de nacimiento: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    gets(librito.caracteristicas.paisNacimiento);
    Beep(600,100);//sonido

    return librito;//devuelvo el libro cargado
}

Copia cargaCopia(char copiaArchi[30], char codigo[30])
{
    Copia aux;

    int flag=0;
    char id [30];

    strcpy(aux.isbn,codigo);
    aux.estado=2;

    do
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
        printf("\nId. interno de la copia: ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
        fflush(stdin);
        gets(id);
        Beep(600,100);//sonido

        if(posIdInternoCopia(copiaArchi,id)==-1)
        {
            //si el id no existe levanto la bandera
            flag=1;
            strcpy(aux.idInterno,id);//copio el id en el archivo
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 | BACKGROUND_INTENSITY);
            Beep(70,200);//sonido
            printf("\nERROR: ese id ya existe. Vuelva a intentarlo.\n");
        }
    }
    while(flag==0);

    return aux;
}

int posIdInternoCopia(char copiaArchi[30], char dato [30])
{
    //declaro una bandera
    int flag=-1;
    //declaro un contador
    int contador=0;

    //declaro una variable de tipo Copia
    Copia aux;

    FILE * archi;
    //abro el archivo en modo lectura
    archi=fopen(copiaArchi,"rb");

    if(archi!=NULL)
    {
        while((flag==-1)&&(fread(&aux,sizeof(Copia),1,archi)>0))
        {
            if(strcmp(aux.idInterno,dato)==0)
            {
                //si el id es igual devuelvo la posicion
                flag=contador;
            }
            contador++;//incremento el contador siempre que este en el loop
        }
    }
    fclose(archi);//cierro el archivo
    //si no encuentra el isbn devuelve -1, sino la posicion
    return flag;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void cargaLibros(char archivo[30], char archiCopia[30],char archiGenero[])
{
    char mander='s';
    Libro libroCarga;
    Copia libroCopia;
    FILE *bufferArchi;
    FILE *bufferCopia;
    char num[30];
    system("cls");

    Beep(400,500);//sonido

    if(bufferArchi!=NULL)
    {
        while(mander=='s')
        {
            system("COLOR 8f");
            printf(" ------------------------- \n");
            printf("|    CARGANDO UN LIBRO    |\n");
            printf(" ------------------------- \n\n");

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
            printf("\n\nDATOS DEL LIBRO\n");
            printf("------------------------------------------------------\n");

            printf("\nISBN: ");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
            fflush(stdin);
            gets(num); //pregunto primero el isbn y verifico si existe
            Beep(600,100);//sonido

            if(posISBNlibro(archivo,num)==-1)
            {
                //abro el archivo en modo escritura
                bufferArchi=fopen(archivo,"ab");

                //si el ISBN no existe cargo un nuevo libro
                libroCarga=cargaUnLibro(num,archiGenero);//carga un libro

                if(bufferArchi!=NULL)
                {
                    //escribo el libro en el archivo
                    fwrite(&libroCarga,sizeof(Libro),1,bufferArchi);//guarda el libro
                }

                //cierro el archivo
                fclose(bufferArchi);
            }
            else
            {
                Beep(600,100);//sonido
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
                printf("\nEl libro existe en el archivo.\n");
                //informo la existencia del libro y sigue con los datos de la copia
            }

            //cargo la informacion de la copia
            libroCopia=cargaCopia(archiCopia, libroCarga.isbn);

            //abro el archibo, escribo la copia y cierro el archivo
            bufferCopia=fopen(archiCopia, "ab");
            if(bufferCopia!=NULL)
            {
                fwrite(&libroCopia,sizeof(Copia),1,bufferCopia);
            }
            fclose(bufferCopia);

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
            printf("LIBRO:\n");
            mostrarLibro(libroCarga,0);
            mostrarCopia(libroCopia);

            //pregunto si quiere seguir cargando libros
            printf("\nDesea cargar mas libros? (s/n): ");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
            fflush(stdin);
            scanf("%c", &mander);

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
            system("pause");

            system("cls");//limpio pantalla
        }
    }
}

int posISBNlibro(char archivo[30], char clave[30])
{
    //declaro una bandera
    int flag=-1;
    //declaro un contador
    int contador=0;

    //declaro una variable de tipo libro
    Libro aux;

    FILE * archi;
    //abro el archivo en modo lectura
    archi=fopen(archivo,"rb");

    if(archi!=NULL)
    {
        while((flag==-1)&&(fread(&aux,sizeof(Libro),1,archi)>0))
        {
            if(strcmp(aux.isbn,clave)==0)
            {
                //si el isbn es igual devuelvo la posicion
                flag=contador;
            }
            contador++;//incremento el contador siempre que este en el loop
        }
    }
    fclose(archi);//cierro el archivo
    //si no encuentra el isbn devuelve -1, sino la posicion
    return flag;
}

/**********************************************************************************
***********************************************************************************/

void buscarLibro(char archLibro [30],char archiCopia [30],char archiGenero[])//////////////////////////////////////////////
{
    int opcion;

    system("cls");//limpio pantalla
    Beep(400,500);//sonido
    menuBuscaLibro();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    scanf("%d", &opcion);
    switch(opcion)
    {
    case 1:
        //busca por autor
        Beep(400,500);//sonido
        buscarXautor(archLibro,archiCopia);
        break;
    case 2:
        Beep(400,500);//sonido
        //busca por titulo
        buscarXtitulo(archLibro,archiCopia);
        break;
    case 3:
        Beep(400,500);//sonido
        //busca por genero
        buscarXgenero(archLibro,archiCopia,archiGenero);
        break;
    case 4:
        Beep(400,500);//sonido
        //busca por isbn
        buscarXisbn(archLibro,archiCopia);
        break;
    case 5:
        Beep(400,500);//sonido
        //busca por id.Interno
        buscarXidInterno(archLibro,archiCopia);
        break;
    case 6:
        Beep(400,500);//sonido
        buscarXestado(archLibro,archiCopia);
        break;
    default:
        Beep(70,200);//sonido
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 | BACKGROUND_INTENSITY);
        printf("\nERROR: opcion no valida.\n");
        system("pause");
        break;
    }
    system("cls");
}

void buscarXestado(char archi[30], char copiaArchi[30])
{
    int estado;

    int pos=0;//inicializo la posicion en 0
    int posCopia=0;
    char codigo [30];
    int num=1;

    system("cls");//limpio pantalla

    system("COLOR 8f");
    printf(" --------------------------- \n");
    printf("|     BUSCAR POR ESTADO     |\n");
    printf(" --------------------------- \n\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("1. Disponibles\n");
    printf("2. Prestados\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    scanf("%d", &estado);

    switch(estado)
    {
    case 1:
        system("cls");
        system("COLOR 8f");
        printf(" ---------------------------- \n");
        printf("|     LIBROS DISPONIBLES     |\n");
        printf(" ---------------------------- \n\n");
        //mostrar disponibles
        estado=2;
        break;
    case 2:
        system("cls");
        system("COLOR 8f");
        printf(" -------------------------- \n");
        printf("|     LIBROS PRESTADOS     |\n");
        printf(" -------------------------- \n\n");
        //mostrar prestados
        estado=1;
        break;
    default:
        Beep(70,200);//sonido
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 | BACKGROUND_INTENSITY);
        printf("\nERROR: opcion no valida.\n");
        system("pause");
        break;
    }
    if((estado==1)||(estado==2))
    {
        Beep(600,100);//sonido
        buscarEstados(archi,copiaArchi,estado);//muestra libros segun estado
    }
}

void buscarEstados(char archi[30], char copiaArchi[30], int estado)
{
    int posCopia=0;
    int posEstado=0;
    int pos=0;
    char isbn[30];
    int num=1;
    char copiaIsbn[30];

    Copia ditto;
    FILE * copiaDitto;

    //primero busca si hay uno por ese estado
    //si no hay avisa que no hay ningun libro disponible o prestado
    posEstado=posEstadoCopia(copiaArchi,estado,posEstado, isbn);

    if(posEstado==-1)
    {
        Beep(70,200);//sonido
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
        printf("\nNo se encontro ningun libro\n");
        system("pause");
    }
    else
    {
        while(posEstado!=-1)
        {
            //si el isbn no coincide con el anterior(para no repetir libros)
            if(strcmp(isbn,copiaIsbn)!=0)
            {
                posCopia=0;//reinicio la posicion de la copia x cada libro
                pos=posISBNlibro(archi,isbn);//busco la pos del libro
                muestraLibroXpos(archi,pos,isbn,num);//muestro el libro
                num++;//incremento el contador

                strcpy(copiaIsbn,isbn);
                posCopia=posISBNcopia(copiaArchi,isbn,posCopia);//busco primer pos


                //recorro las copias de ese libro
                while(posCopia!=-1)
                {
                    copiaDitto=fopen(copiaArchi,"rb");//abro el archivo

                    if(copiaDitto!=NULL)
                    {
                        fseek(copiaDitto,sizeof(Copia)*posCopia,SEEK_SET);//busco la posicion
                        fread(&ditto,sizeof(Copia),1,copiaDitto);//abro el archivo
                        if(ditto.estado==estado)
                        {
                            //si el estado coincide lo muestro
                            muestraCopiaXpos(copiaArchi,posCopia);
                        }
                    }

                    fclose(copiaDitto);//cierro el archivo


                    posCopia=posISBNcopia(copiaArchi,isbn,posCopia+1);//busco nueva pos
                }
            }

            //vuelo a verificar si hay mas elementos en ese estado
            posEstado=posEstadoCopia(copiaArchi,estado,posEstado+1, isbn);
        }
        system("pause");
    }
}

void buscarXgenero(char archi[30], char copiaArchi[30],char archiGenero[])/////////////////////////////////////////////////////////////
{
    FILE * bufferGenero;
    GeneroStruct aux;

    char genero[30];

    int pos=0;//inicializo la posicion en 0
    int posCopia=0;
    char codigo [30];
    int num=1;

    system("cls");//limpio pantalla

    system("COLOR 8f");
    printf(" --------------------------- \n");
    printf("|     BUSCAR POR GENERO     |\n");
    printf(" --------------------------- \n\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("Generos disponibles: \n");
    bufferGenero=fopen(archiGenero,"rb");

    if(bufferGenero!=NULL)
    {
        while(fread(&aux,sizeof(GeneroStruct),1,bufferGenero)>0)
        {
            printf("                      %s\n", aux.genero);
        }
    }

    fclose(bufferGenero);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    gets(genero);
    Beep(600,100);//sonido

    //paso el titulo a minuscula
    //asi la busqueda funciona independientemente de si hay uper case o no
    strlwr(genero);

    pos=posGeneroLibro(archi,genero,pos);//valido si existe al menos 1

    //verifico la posicion
    if(pos==-1)
    {
        //no existe
        Beep(70,200);//sonido
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 | BACKGROUND_INTENSITY);
        printf("\nERROR: El genero que busca no se encuentra en el archivo.\n");
    }
    else
    {
        //encontro una posicion valida
        //busco la posicion y lo muestro
        while(pos!=-1)
        {
            posCopia=0;
            muestraLibroXpos(archi,pos,codigo,num);
            num++;

            posCopia=posISBNcopia(copiaArchi,codigo,posCopia);//busco pos de copia

            printf("\n------------------------------\n");
            printf("            COPIAS: \n");

            while(posCopia!=-1)
            {
                muestraCopiaXpos(copiaArchi,posCopia);

                posCopia=posISBNcopia(copiaArchi,codigo,posCopia+1);//busca nueva posicion
            }

            ///busca proxima coincidencia---------------------------------------
            pos=posGeneroLibro(archi,genero,pos+1);
        }
    }
    system("pause");
}

void buscarXtitulo(char archi[30], char copiaArchi[30])
{
    //muestra todos los libros de un autor
    char titulo[30];

    int pos=0;//inicializo la posicion en 0
    int posCopia=0;
    char codigo [30];
    int num=1;

    system("cls");//limpio pantalla

    system("COLOR 8f");
    printf(" --------------------------- \n");
    printf("|     BUSCAR POR TITULO     |\n");
    printf(" --------------------------- \n\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("Titulo: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    gets(titulo);
    Beep(600,100);//sonido

    //paso el titulo a minuscula
    //asi la busqueda funciona independientemente de si hay uper case o no
    strlwr(titulo);

    pos=posTituloLibro(archi,titulo,pos);//valido si existe al menos 1

    //verifico la posicion
    if(pos==-1)
    {
        //no existe
        Beep(70,200);//sonido
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 | BACKGROUND_INTENSITY);
        printf("\nERROR: El titulo que busca no se encuentra en el archivo.\n");
    }
    else
    {
        //encontro una posicion valida
        //busco la posicion y lo muestro
        while(pos!=-1)
        {
            posCopia=0;
            muestraLibroXpos(archi,pos,codigo,num);
            num++;

            posCopia=posISBNcopia(copiaArchi,codigo,posCopia);//busco pos de copia

            printf("\n------------------------------\n");
            printf("            COPIAS: \n");

            while(posCopia!=-1)
            {
                muestraCopiaXpos(copiaArchi,posCopia);

                posCopia=posISBNcopia(copiaArchi,codigo,posCopia+1);//busca nueva posicion
            }

            ///busca proxima coincidencia---------------------------------------
            pos=posTituloLibro(archi,titulo,pos+1);
        }
    }
    system("pause");
}

void buscarXisbn(char archi[30], char copiaArchi[30])
{
    char clave[30];
    int pos=0;
    int posCopia=0;

    system("cls");//limpio pantalla

    system("COLOR 8f");
    printf(" ------------------------- \n");
    printf("|     BUSCAR POR ISBN     |\n");
    printf(" ------------------------- \n\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("ISBN: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    gets(clave);
    Beep(600,100);//sonido

    pos=posISBNlibro(archi,clave);

    if(pos!=-1)
    {
        pos=posISBNlibro(archi,clave);//busco posicion del libro
        printf(" ");
        muestraLibroXpos(archi,pos,clave,1);//muestro el libro en la posicion

        posCopia=posISBNcopia(copiaArchi,clave,posCopia);//busco pos de copia

        printf("\n------------------------------\n");
        printf("            COPIAS: \n");

        while(posCopia!=-1)
        {
            muestraCopiaXpos(copiaArchi,posCopia);//muestra copia en la posicion

            posCopia=posISBNcopia(copiaArchi,clave,posCopia+1);//busca nueva posicion
        }

    }
    else
    {
        Beep(70,200);//sonido
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 | BACKGROUND_INTENSITY);
        printf("\nERROR: El ISBN ingresado no existe\n");
    }
    system("pause");
}

void buscarXautor(char archi[30], char copiaArchi[30])
{
    //muestra todos los libros de un autor
    char nombre[30];
    char apellido[30];
    int pos=0;//inicializo la posicion en 0
    int posCopia=0;
    char codigo [30];
    int num=1;

    system("cls");//limpio pantalla

    system("COLOR 8f");
    printf(" -------------------------- \n");
    printf("|     BUSCAR POR AUTOR     |\n");
    printf(" -------------------------- \n\n");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("Nombre del autor: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    gets(nombre);
    Beep(600,100);//sonido

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("Apellido del autor: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    gets(apellido);
    Beep(600,100);//sonido

    //paso el nombre y apellido a minuscula
    //asi la busqueda funciona independientemente de si hay uper case o no
    strlwr(nombre);
    strlwr(apellido);

    pos=posAutorLibro(archi,nombre,apellido,pos);//valido si existe al menos 1

    //verifico la posicion
    if(pos==-1)
    {
        //no existe
        Beep(70,200);//sonido
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 | BACKGROUND_INTENSITY);
        printf("\nERROR: El autor que busca no se encuentra en el archivo.\n");
    }
    else
    {
        //encontro una posicion valida
        //busco la posicion y lo muestro
        while(pos!=-1)
        {
            posCopia=0;
            muestraLibroXpos(archi,pos,codigo,num);
            num++;

            posCopia=posISBNcopia(copiaArchi,codigo,posCopia);//busco pos de copia

            printf("\n------------------------------\n");
            printf("            COPIAS: \n");

            while(posCopia!=-1)
            {
                muestraCopiaXpos(copiaArchi,posCopia);

                posCopia=posISBNcopia(copiaArchi,codigo,posCopia+1);//busca nueva posicion
            }

            ///busca proxima coincidencia---------------------------------------
            pos=posAutorLibro(archi,nombre,apellido,pos+1);
        }
    }
    system("pause");
}

void buscarXidInterno(char archi[30], char copiaArchi[30])
{
    char clave[30];
    char isbn[30];
    int pos=0;
    int posCopia=0;

    FILE *archivoCopia;

    Copia ditto;

    system("cls");//limpio pantalla

    system("COLOR 8f");
    printf(" -------------------------------- \n");
    printf("|     BUSCAR POR  ID.INTERNO     |\n");
    printf(" -------------------------------- \n\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("Id.Interno: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    gets(clave);
    Beep(600,100);//sonido

    posCopia=posIdInternoCopia(copiaArchi,clave);//busco la posicion del id.interno


    if(posCopia!=-1)
    {
        //abro el archivo copia
        archivoCopia=fopen(copiaArchi,"rb");

        if(archivoCopia!=NULL)
        {
            //leo el archivo y obtengo el isbn
            fseek(archivoCopia,sizeof(Copia)*posCopia,SEEK_SET);
            fread(&ditto,sizeof(Copia),1,archivoCopia);
            strcpy(isbn,ditto.isbn);
        }

        fclose(archivoCopia);//cierro el archivo

        pos=posISBNlibro(archi,isbn);//busco posicion del libro
        printf(" ");
        muestraLibroXpos(archi,pos,isbn,1);//muestro el libro en la posicion

        printf("\n------------------------------\n");
        printf("            COPIAS: \n");

        muestraCopiaXpos(copiaArchi,posCopia);//muestra copia en la posicion

    }
    else
    {
        Beep(70,200);//sonido
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 | BACKGROUND_INTENSITY);
        printf("ERROR: El Id.Interno ingresado no existe");
    }
    system("pause");
}

void mostrarLibro(Libro librito, int num)
{

    char mander[30];

    if(librito.tipoLibro==1)
    {
        strcpy(mander,"Tapa dura");
    }
    else if(librito.tipoLibro==2)
    {
        strcpy(mander,"Tapa blanda");
    }
    else
    {
        strcpy(mander,"Ed. bolsillo");
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);

    printf("\n---------------------------------------------------------------------------------- %d.\n", num);
    printf("\n%cTitulo:................%s\n",175, librito.titulo);
    printf("%cAutor:................ %s %s\n", 175, librito.caracteristicas.nombre, librito.caracteristicas.apellido);
    printf("     Nacimiento:....... %d\n", librito.caracteristicas.anioNacimiento);
    printf("     Pais:............. %s\n\n", librito.caracteristicas.paisNacimiento);
    printf("%cEditorial:.............%s\n",175, librito.editorial);
    printf("%cGenero:................%s\n",175,librito.genero);
    printf("%cCant. paginas:.........%d\n",175,librito.cantPaginas);
    printf("%cTipo de libro:.........%s\n",175,mander);
    printf("%cISBN: .................%s\n",175,librito.isbn);
    printf("%cCant de prestamos:.....%d\n",175,librito.cantPrestamos);
    printf("%cPuntaje:...............%.2f\n",175,librito.puntuacion);
    printf("%cTiempo de prestamo:....%d dias\n",175,librito.diasPrestamo);
}

void mostrarCopia(Copia ditto)
{
    char estado[30];
    if(ditto.estado==2)
    {
        strcpy(estado,"Disponible");
    }
    else
    {
        strcpy(estado,"Prestado");
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("------------------------------\n");
    printf("%cISBN ..................%s\n",175,ditto.isbn);
    printf("%cId. interno:...........%s\n",175,ditto.idInterno);
    printf("%cEstado:................%s\n",175,estado);
}


void muestraLibroXpos(char archi[30], int pos, char isbn[30], int num)
{
    Libro librito;

    FILE * archivo;

    archivo=fopen(archi,"rb");//abro el archivo en lectura
    if(archivo!=NULL)
    {
        fseek(archivo,sizeof(Libro)*pos,SEEK_SET);//busco la posicion Libro
        fread(&librito,sizeof(Libro),1,archivo);//leo el libro

        mostrarLibro(librito,num);//lo imprime

        strcpy(isbn,librito.isbn);
    }
    //cierro los archivos
    fclose(archivo);

}

void muestraCopiaXpos(char copiaArchi[30], int posCopia)
{
    Copia ditto;
    FILE * copiaDitto;

    copiaDitto=fopen(copiaArchi,"rb");//abro la copia

    if(copiaDitto!=NULL)
    {
        fseek(copiaDitto,sizeof(Copia)*posCopia,SEEK_SET);//busca pos copia
        fread(&ditto,sizeof(Copia),1,copiaDitto);//lee la copia
    }
    fclose(copiaDitto);//cierra arcivo copia
    //imprime copias
    mostrarCopia(ditto);
}

void menuBuscaLibro()
{
    system("COLOR 8f");
    printf(" -----------------------\n");
    printf("|      BUSCAR LIBRO     |\n");
    printf(" -----------------------\n\n");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("1. Por autor\n");
    printf("2. Por titulo\n");
    printf("3. Por genero\n");
    printf("4. Por ISBN\n");
    printf("5. Por id. Interno\n");
    printf("6. Por estado\n");

    printf("\n0. Para volver al menu principal\n");
}

int posAutorLibro(char archivo[30], char nombre[30],char apellido[30], int pos)
{
    //declaro una bandera
    int flag=-1;
    //declaro strings a comparar
    char nombreArchi[30];
    char apellidoArchi[30];

    //declaro una variable de tipo libro
    Libro aux;

    FILE * archi;
    //abro el archivo en modo lectura
    archi=fopen(archivo,"rb");

    if(archi!=NULL)
    {
        //desde que posicon busco
        fseek(archi,sizeof(Libro)*(pos),SEEK_SET);

        while((flag==-1)&&(fread(&aux,sizeof(Libro),1,archi)>0))
        {
            //guardo nombre y apellido del archivo en variables
            strcpy(nombreArchi,aux.caracteristicas.nombre);
            strcpy(apellidoArchi,aux.caracteristicas.apellido);

            //las paso a lower case
            strlwr(nombreArchi);
            strlwr(apellidoArchi);

            if((strcmp(nombreArchi,nombre)==0)&&(strcmp(apellidoArchi,apellido)==0))
            {
                //si el nombre y apellido es igual devuelvo la posicion
                flag=pos;
            }
            pos++;//incremento el contador siempre que este en el loop
        }
    }
    fclose(archi);//cierro el archivo
    //si no encuentra el isbn devuelve -1, sino la posicion
    return flag;
}

int posEstadoCopia(char archivo[30],int estado,int pos, int isbn)
{
    //declaro una bandera
    int flag=-1;

    //declaro una variable de tipo libro
    Copia aux;

    FILE * archi;
    //abro el archivo en modo lectura
    archi=fopen(archivo,"rb");

    //desde que posicon busco
    fseek(archi,sizeof(Copia)*(pos),SEEK_SET);

    if(archi!=NULL)
    {
        while((flag==-1)&&(fread(&aux,sizeof(Copia),1,archi)>0))
        {
            if(aux.estado==estado)
            {
                //si el isbn es igual devuelvo la posicion
                flag=pos;
                strcpy(isbn,aux.isbn);
            }
            pos++;//incremento el contador siempre que este en el loop
        }
    }
    fclose(archi);//cierro el archivo
    //si no encuentra el isbn devuelve -1, sino la posicion
    return flag;
}

int posISBNcopia(char archivo[30], char clave[30], int pos)
{
    //declaro una bandera
    int flag=-1;

    //declaro una variable de tipo libro
    Copia aux;

    FILE * archi;
    //abro el archivo en modo lectura
    archi=fopen(archivo,"rb");

    if(archi!=NULL)
    {
        //desde que posicon busco
        fseek(archi,sizeof(Copia)*(pos),SEEK_SET);

        while((flag==-1)&&(fread(&aux,sizeof(Copia),1,archi)>0))
        {
            if(strcmp(aux.isbn,clave)==0)
            {
                //si el isbn es igual devuelvo la posicion
                flag=pos;
            }
            pos++;//incremento el contador siempre que este en el loop
        }
    }
    fclose(archi);//cierro el archivo
    //si no encuentra el isbn devuelve -1, sino la posicion
    return flag;
}

int posTituloLibro(char archivo[30], char titulo[30], int pos)
{
    //declaro una bandera
    int flag=-1;

    //declaro strings a comparar
    char tituloArchi[30];

    //declaro una variable de tipo libro
    Libro aux;

    FILE * archi;
    //abro el archivo en modo lectura
    archi=fopen(archivo,"rb");

    //desde que posicon busco
    fseek(archi,sizeof(Libro)*(pos),SEEK_SET);

    if(archi!=NULL)
    {
        while((flag==-1)&&(fread(&aux,sizeof(Libro),1,archi)>0))
        {
            //guardo el titulo del archivo en variables
            strcpy(tituloArchi,aux.titulo);

            //las paso a lower case
            strlwr(tituloArchi);

            if((strcmp(tituloArchi,titulo)==0))
            {
                //si el titulo es igual devuelvo la posicion
                flag=pos;
            }
            pos++;//incremento el contador siempre que este en el loop
        }
    }
    fclose(archi);//cierro el archivo
    //si no encuentra el isbn devuelve -1, sino la posicion
    return flag;
}

int posGeneroLibro(char archivo[30], char genero[30], int pos)
{
    //declaro una bandera
    int flag=-1;

    //declaro strings a comparar
    char generoArchi[30];

    //declaro una variable de tipo libro
    Libro aux;

    FILE * archi;
    //abro el archivo en modo lectura
    archi=fopen(archivo,"rb");

    //desde que posicon busco
    fseek(archi,sizeof(Libro)*(pos),SEEK_SET);

    if(archi!=NULL)
    {
        while((flag==-1)&&(fread(&aux,sizeof(Libro),1,archi)>0))
        {
            //guardo nombre y apellido del archivo en variables
            strcpy(generoArchi,aux.genero);

            //las paso a lower case
            strlwr(generoArchi);

            if((strcmp(generoArchi,genero)==0))
            {
                //si el genero es igual devuelvo la posicion
                flag=pos;
            }
            pos++;//incremento el contador siempre que este en el loop
        }
    }
    fclose(archi);//cierro el archivo
    //si no encuentra el isbn devuelve -1, sino la posicion
    return flag;
}

/**
int funcion mostar generos que recibe un string (se modifica dentro de la funcion) y
0 o 1 si es carga o solo muestra(devuelve: si es valido 1 y sino  0, y si quiere cargar
                                 uno nuevo 2)
**/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ingresaGenero(char archiGenero[], char genero[30])
{
    int opcion;

    do
    {
        opcion=mostrarGenero(archiGenero, genero);
        //devuelve 1 si ya cargo o 0 si quiere cargar uno nuevo
    }
    while(opcion==2); //mientras ingrese valores fuera de la lista de generos

    if(opcion==0)
    {
        cargarGeneroNuevo(archiGenero, genero);//carga uno nuevo en el archivo de generos
        //y carga en el array genero
    }
}

int mostrarGenero(char archiGenero[], char genero[30])
{
    int opcion;
    GeneroStruct mander;
    int i=0;

    FILE * bufferGenero;

    bufferGenero=fopen(archiGenero,"rb");

    //muestro los generos guardados en el archivo

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("\nSeleccione un genero de la lista:\n");
    while(fread(&mander,sizeof(GeneroStruct),1,bufferGenero)>0)
    {
        i++;
        printf("       %d. %s\n",i,mander.genero);
    }
    printf("\n0. Si desea ingresar uno nuevo\n");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    scanf("%d", &opcion);//selecciona la posicion del valor a ingresar
    Beep(600,100);//sonido

    fclose(bufferGenero);

    if(opcion>i)
    {
        opcion=2;//error
        Beep(70,200);//sonido
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 | BACKGROUND_INTENSITY);
        printf("\nERROR: ingrese un valor dentro de la lista o 0\n");
        system("pause");
    }
    else if(opcion!=0)
    {
        ingresaGeneroPos(archiGenero, genero, i-1);//guardo el genero en el array genero
        opcion=1;//se cargo el genero
    }

    return opcion;
}

void ingresaGeneroPos(char archiGenero[], char genero[], int pos)
{
    GeneroStruct aux;

    FILE * bufferArchivo;

    bufferArchivo=fopen(archiGenero,"rb");

    if(bufferArchivo!=NULL)
    {
        fseek(bufferArchivo,sizeof(GeneroStruct)*pos,SEEK_SET);
        fread(&aux,sizeof(GeneroStruct),1,bufferArchivo);//asigno el genero de esa pos a genero[]

        strcpy(genero, aux.genero);
    }

    fclose(bufferArchivo);
}

//cargarGeneroNuevo(archiGenero);
void cargarGeneroNuevo(char archiGenero[], char genero[30])
{
    GeneroStruct aux;

    FILE * bufferArchi;

    bufferArchi=fopen(archiGenero,"ab");

    if(bufferArchi!=NULL)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
        printf("\nIngrese el genero a guardar: ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
        fflush(stdin);
        gets(genero);

        strcpy(aux.genero,genero);

        fwrite(&aux,sizeof(GeneroStruct),1,bufferArchi);//guarda nuevo genero en el archivo
    }

    fclose(bufferArchi);
}


/**********************************************************************************
***********************************************************************************/

int buscar_pos_usuario(char archivo[],char dniIngresado[30])
{
    /*verifica la existencia del usuario en el sistema por medio del dni ingresado
    se utiliza una flag para informar 1(existencia) 0(inexistencia), retorna la pos del fichero*/

    int i=0; //contador de posiciones
    int pos=-1; //retornara la posicion del dato buscado
    Persona usuario;
    FILE *arch;

    //abro el archvo con permisos de lectura
    arch=fopen(archivo,"rb");

    //si el archivo se abre correctamente
    if(arch!=NULL)
    {
        //mientras el archivo no este vacio y la pos no este cargada
        while((!feof(arch)) && (pos==-1))
        {
            //se lee una estructura persona del archivo
            fread(&usuario,sizeof(Persona),1,arch);

            //se enceuntra una persona registrada con el mismo dni entonces pos=contador de pos
            if(strcmp(usuario.dni,dniIngresado)==0)
            {
                pos=i;
            }

            //se usa un contador para ir sabiendo las posiciones
            i+=1;
        }
    }

    return pos;
}

void mostrar_usuario(Persona p)
{
    /*muesta la persona pasandole por parametro la variable de la persona en particular*/

    Beep(400,500);
    system("COLOR 8f");
    printf("\t ----------------------\n");
    printf("\t|  USUARIO REGISTRADO  |\n");
    printf("\t ----------------------\n\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);

    printf("\t    Datos personales\n");
    printf("__________________________________________\n\n");

    printf("Nombre: %s\n",p.nombre);
    printf("Apellido: %s\n",p.apellido);
    printf("Fecha de nacimiento: %d/%d/%d\n",p.Nacimiento.dia,p.Nacimiento.mes,p.Nacimiento.anio);
    printf("DNI: %s\n",p.dni);

    printf("\t       Domicilio\n");
    printf("__________________________________________\n\n");

    printf("Direccion: %s %d,%s\n",p.domicilio.calle,p.domicilio.numero,p.domicilio.municipio);

    printf("\n\t   Opciones de contacto\n");
    printf("__________________________________________\n\n");

    printf("Telefono: %s\n",p.telefono);
    printf("Email: %s\n",p.email);

    printf("\n\t   Historial usario\n");
    printf("__________________________________________\n\n");

    printf("Deuda: %d\n",p.deuda);
    printf("Libros en posesion: %d\n",p.cantLibros);

}

Persona cargar_datos_persona(char dniIngresado[30])
{
    /*Ingreso de datos de persona*/
    Persona p;

    printf("Nombre: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    gets(p.nombre);
    Beep(600,100);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("Apellido: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    gets(p.apellido);
    Beep(600,100);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("Fecha nacimiento (--/--/----)");
    printf("\nDia: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    scanf("%d",&p.Nacimiento.dia);
    Beep(600,100);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("Mes: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    scanf("%s",&p.Nacimiento.mes);
    Beep(600,100);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("Anio: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    scanf("%d",&p.Nacimiento.anio);
    Beep(600,100);

    strcpy(p.dni,dniIngresado);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("\t       Domicilio\n");
    printf("__________________________________________\n\n");

    printf("Direccion");
    printf("\nCalle: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    gets(&p.domicilio.calle);
    Beep(600,100);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("Numero: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    scanf("%d",&p.domicilio.numero);
    Beep(600,100);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("Municipio: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    gets(&p.domicilio.municipio);
    Beep(600,100);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("\n\t   Opciones de contacto\n");
    printf("__________________________________________\n\n");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("Telefono: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    gets(p.telefono);
    Beep(600,100);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("Email: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    gets(p.email);
    Beep(600,100);

    p.deuda=0; //se le inicializa la deuda en 0

    p.cantLibros=0;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);

    return p;
}

Persona buscar_persona_segun_pos(char archivo[],int pos)
{
    /*busca un persona en particular sabiendo la posicion del fichero, retorna una estructura temporal de
    la persona en cuestion*/

    FILE *arch;
    Persona usuario;

    //abre el archivo con permisos de lectura
    arch=fopen(archivo,"rb");

    //si se abre correctamente
    if(arch!=NULL)
    {
        //se posiciona el cursor a la pos pasada por parametro
        fseek(arch,sizeof(Persona)*pos,SEEK_SET);

        //se lee la info almacenada en esa pos
        fread(&usuario,sizeof(Persona),1,arch);
    }
    fclose(arch);

    //se devuelve la estructura con la lectura del archivo
    return usuario;
}

void ingreso_Dni(char dni[30])
{
    /*se resaliza una pre carga del dni(utilizada para verificaion)*/
    printf("DNI: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    gets(dni);
    Beep(600,100);
}

void nuevo_usuario(char archivo[])
{

    /*carga un usuario, primero le pregunta el dni, dato con el que verificara la existencia
    del mismo en el archivo de personas cargadas
    si la persona estaba cargada anteriormente, se niega la carga y se muestran los datos
    si la persona no estaba cargada anteriormente se prosigue con la carga de datos
    por ultimo se usa recursividad para preguntarle al usuario si desea cargar un usuario mas*/

    FILE *arch;
    Persona usuario;
    char dniIngresado[30]; //variable temp de dni
    int pos=0; //pos que determina existencia
    int cant=0;

    system("COLOR 8f");
    printf("\t----------------------\n");
    printf("\t|       REGISTRO       |\n");
    printf("\t----------------------\n\n");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("\t    Datos personales\n");
    printf("__________________________________________\n\n");

    //se pide el ingreso del dni que se almacena en una variable temp
    ingreso_Dni(dniIngresado);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    //se verifica el dni enviando por parametro la variable temporal del dni
    pos=buscar_pos_usuario(archivo,dniIngresado);

    //si no existe el usuario
    if(pos==-1)
    {
        //se abre el archivo con permisos para agregar info
        arch=fopen(archivo,"ab");

        //si se abrio correctamente
        if(arch!=NULL)
        {
            //ingreso de datos para registrarse
            usuario=cargar_datos_persona(dniIngresado);

            //se esrbibe la estructura retornada de la funcion anterior en el archivo
            cant=fwrite(&usuario,sizeof(Persona),1,arch);

            system("cls");

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);

            //verificacion de si se cargaron bien los datos
            if(cant==1)
            {
                printf("-------------------------------------------------\n\n");
                printf("\t  Usuario registrado con exito\n\n");
                printf("-------------------------------------------------\n\n");
            }

            fclose(arch);
        }
    }
    else//si existe el usuario
    {
        system("cls");

        //segun la pos obtenida retornamos la estructura en esa pos
        usuario=buscar_persona_segun_pos(archivo,pos);

        //mostramos la estructura
        mostrar_usuario(usuario);
    }

    system("pause");
}

/**********************************************************************************
***********************************************************************************/

void verificacion_usuario(char archivo[30])
{
    /*verificacion de si existe el usuario, si no existe se muestra un mensaje
    informando que no esta logeado, si existe el fichero entonces se lo muestra*/

    char dniIngresado[30];
    int pos=0;
    Persona usuario;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    //se pide el ingreso del dni
    ingreso_Dni(dniIngresado);

    system("cls");

    //se busca la pos del usuario
    pos=buscar_pos_usuario(archivo,dniIngresado);

    //si no se encuentra la pos entonces el usuario no existe
    if(pos==-1)
    {
        Beep(70,200);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 | BACKGROUND_INTENSITY);
        printf("-------------------------------------------------\n\n");
        printf("\t      Usuario no registrado \n\n");
        printf("-------------------------------------------------\n\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);

    }
    else  //si se encontro la pos
    {
        //se retorna la estructura de esa pos
        usuario=buscar_persona_segun_pos(archivo,pos);

        //se muestra la estructura retornada de la fc snterior
        mostrar_usuario(usuario);
    }
}

/**********************************************************************************
***********************************************************************************/

Prestamo carga_datos_entrega(char idInternoIngresado[30],char dniIngresado[10])
{
    Prestamo entrega;

    //se le asignan los datos precargados
    strcpy(entrega.idInterno,idInternoIngresado);
    strcpy(entrega.dni,dniIngresado);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    //se carga el resto de los datos
    printf("\t    Datos de entrega\n");
    printf("__________________________________________\n\n");

    printf("Dia: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    scanf("%d",&entrega.retirado.dia);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("\nMes: ");
    fflush(stdin);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    scanf("%d",&entrega.retirado.mes);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("\nAnio: ");
    fflush(stdin);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    scanf("%d",&entrega.retirado.anio);

    //se inicializan en 0
    entrega.devolucion.dia=0;
    entrega.devolucion.mes=0;
    entrega.devolucion.anio=0;

    return entrega;
}

void sumar_posesion(char archivo[],int pos)
{
    FILE *arch;
    Persona usuario;

    //apertura del archivo
    arch=fopen(archivo,"r+b");

    if(arch!=NULL)
    {
        //posicionamiento del cursor
        fseek(arch,sizeof(Persona)*pos,SEEK_SET);

        fread(&usuario,sizeof(Persona),1,arch);

        //modificacion del contador
        usuario.cantLibros+=1;

        //posicionamiento del cursor
        fseek(arch,sizeof(Persona)*-1,SEEK_CUR);

        //escritura del dato modificado
        fwrite(&usuario,sizeof(Persona),1,arch);
    }

    //cierre de archivo
    fclose(arch);

    fclose(arch);
}

Copia buscar_copia_segun_pos(char archivo[],int pos)
{
    //variable tipo copia que sera retornada
    Copia copiaLibro;
    //buffer de archivo de copias
    FILE *arch;

    //abrimos el archivo con permisos de lectura
    arch=fopen(archivo,"rb");

    if(arch!=NULL)
    {

        //colocamos el cursor en la pos del dato
        fseek(arch,sizeof(Copia)*pos,SEEK_SET);

        //leemos el fichero
        fwrite(&copiaLibro,sizeof(Copia),1,arch);
    }

    //cerramos el archivo
    fclose(arch);

    //retornamos la variable
    return copiaLibro;
}

void cambiar_estado_prestado(char archivo[],int pos)
{
    //abrimos el buffer el archivo de copias
    FILE *arch;

    Copia copiaLibro;

    //abrimos el archivo con permisos de agregar
    arch=fopen(archivo,"r+b");

    if(arch!=NULL)
    {

        //posicionamos el cursor en el dato
        fseek(arch,sizeof(Copia)*pos,SEEK_SET);

        fread(&copiaLibro,sizeof(Copia),1,arch);

        //modificamos el dato
        copiaLibro.estado=1;

        //posicionamos el cursor en el dato
        fseek(arch,sizeof(Copia)*-1,SEEK_CUR);

        //sobreescribimos el dato con la modificacion
        fwrite(&copiaLibro,sizeof(Copia),1,arch);
    }

    //cerramos el buffer
    fclose(arch);
}

int buscar_pos_libro(char archivo[],char isbn[30])
{
    //variable contador de posiciones
    int cant=0;
    //pos retornada 0(inexistencia)
    int pos=-1;
    //variable tipo libro
    Libro libroRegistrado;
    //buffer del archivo de libros
    FILE *arch;

    arch=fopen(archivo,"rb");

    if(arch!=NULL)
    {

        while(!feof(arch) && pos==-1)
        {

            fread(&libroRegistrado,sizeof(Libro),1,arch);

            if(strcmp(libroRegistrado.isbn,isbn)==0)
            {

                pos=cant;
            }

            cant+=1;
        }
    }

    fclose(arch);

    return pos;
}

Libro buscar_libro_segun_pos(char archivo[],int pos)
{
    //variable tipo libro
    Libro librito;
    //archivo de libros
    FILE *arch;

    //abrimos le archivo con permisos de lectura
    arch=fopen(archivo,"rb");

    if(arch!=NULL)
    {
        //posicionamos el cursor en la posicion del dato
        fseek(arch,sizeof(Libro)*pos,SEEK_SET);

        //leemos el fichero
        fread(&librito,sizeof(Libro),1,arch);
    }

    //cerramos el archivo
    fclose(arch);

    //se retorna la variable tipo libro
    return librito;
}

void aumentar_cantPrestamos_libro(char archivo[],int pos)
{
    //vuffer de archivo de libros
    FILE *arch;

    Libro libroRegistrado;

    //abrimos el archivo con permisos de agregado
    arch=fopen(archivo,"r+b");

    if(arch!=NULL)
    {
        //posicionamos el cursor en el dato
        fseek(arch,sizeof(Libro)*pos,SEEK_SET);

        fread(&libroRegistrado,sizeof(Libro),1,arch);

        //modificamos el dato
        libroRegistrado.cantPrestamos+=1;

        //posicionamos el cursor en el dato
        fseek(arch,sizeof(Libro)*-1,SEEK_CUR);

        //escribimos le dato modificado
        fwrite(&libroRegistrado,sizeof(Libro),1,arch);
    }

    //Cerramos el buffer
    fclose(arch);
}

void nuevo_prestamo(char archiPrestamos[],char archiLibros[],char archiCopiaLibros[],char archiUsuarios[])
{
    //varaibles temporales para verificacion de existencia
    char idInternoIngresado[30];
    char dniIngresado[10];
    //variables que informaran sobre la existencia
    int posIdInterno=0;
    int posUsuario=0;
    int posLibro=0;
    //bandera 1(no seguir) 0(seguir)
    int flag=0;
    int exito=0;
    //variable tipo prestamo
    Prestamo entrega;
    //variable de tipo persona
    Persona usuario;
    //variable tipo libro
    Libro libroRegistrado;
    //variable tipo copia
    Copia copiaLibro;
    //archivo
    FILE *archPrestamo;

    system("COLOR 8f");
    printf("\t----------------------\n");
    printf("\t|       PRESTAMO       |\n");
    printf("\t----------------------\n\n");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("\t    Datos del libro\n");
    printf("__________________________________________\n\n");

    //ingreso del id interno
    printf("Id interno: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    gets(idInternoIngresado);
    Beep(600,100);

    //verificacion de existencia de id interno
    posIdInterno=posIdInternoCopia(archiCopiaLibros,idInternoIngresado);

    if(posIdInterno==-1)//inexistencia del id interno
    {
        system("cls");

        Beep(70,200);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 | BACKGROUND_INTENSITY);
        printf("-------------------------------------------------\n\n");
        printf("\t     Id interno inexistente\n\n");
        printf("-------------------------------------------------\n\n");

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
        printf("Sera redirigido al menu principal.\n\n");

        system("pause");

    }
    else    //existencia del id interno
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
        printf("\t    Datos del usuario\n");
        printf("__________________________________________\n\n");

        //ingreso del dni del usuario
        printf("DNI: ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
        fflush(stdin);
        gets(dniIngresado);
        Beep(600,100);

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
        //verificacion de existencia del usuario segun su usuario
        posUsuario=buscar_pos_usuario(archiUsuarios,dniIngresado);

        if(posUsuario==-1)  //inexistencia del usuario
        {
            system("cls");

            Beep(70,200);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 | BACKGROUND_INTENSITY);
            printf("-------------------------------------------------\n\n");
            printf("\t      Usuario no registrado\n\n");
            printf("-------------------------------------------------\n\n");

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
            printf("Antes de realizar un prestamo el usuario debe estar registrado.\n\n");

            printf("Sera redirigido al menu principal.\n\n");

            system("pause");

        }
        else   //existencia del usuario
        {
            //se abre el archivo donde se registran los prestamos
            archPrestamo=fopen(archiPrestamos,"ab");

            //se cargan la variable de tipo prestamo con todos los datos
            entrega=carga_datos_entrega(idInternoIngresado,dniIngresado);

            if(archPrestamo!=NULL)
            {
                //se escribe la entrega en el archivo de prestamos
                exito=fwrite(&entrega,sizeof(Prestamo),1,archPrestamo);

                if(exito==1)
                {
                    system("cls");

                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
                    printf("-------------------------------------------------\n\n");
                    printf("\t Prestamo registrado con exito\n\n");
                    printf("-------------------------------------------------\n\n");
                }

            }

            //se cierra el archivo
            fclose(archPrestamo);

            //modificar la cant de libros en posesion del usuario
            usuario=buscar_persona_segun_pos(archiUsuarios,posUsuario);//retorna la variable
            sumar_posesion(archiUsuarios,posUsuario);//modifica el dato

            //cambiamos el estado de disponibilidad de la copia
            copiaLibro=buscar_copia_segun_pos(archiCopiaLibros,posIdInterno);//retorna la variable
            cambiar_estado_prestado(archiCopiaLibros,posIdInterno);//modifica el dato

            //aumentar cantidad de prestamos del libro
            posLibro=buscar_pos_libro(archiLibros,copiaLibro.isbn);//pos de libro
            libroRegistrado=buscar_libro_segun_pos(archiLibros,posLibro);//retorna la variable
            aumentar_cantPrestamos_libro(archiLibros,posLibro);//modifica el dato

            system("pause");
        }
    }
}

/**********************************************************************************
***********************************************************************************/

int buscar_id_prestamos(char archPrestamos[],char idIngresado[30])
{
    //variable de existencia
    int pos=-1;
    //contador de posiciones
    int cant=0;
    Prestamo entregaHecha;
    FILE *arch;

    //abrimos el archivo de los prestamos en modo lectura
    arch=fopen(archPrestamos,"rb");

    if(arch!=NULL)
    {
        //recorremos todo el archivo hasta encontrar el dato necesitado
        while(!feof(arch) && pos==-1)
        {
            //se hace un alectura
            fread(&entregaHecha,sizeof(Prestamo),1,arch);

            //si se encuentra el dato se le asigna la cant a pos

            if(strcmp(entregaHecha.idInterno,idIngresado)==0)
            {
                pos=cant;
            }

            //se incrementa el contador de posiciones del archivo
            cant+=1;
        }
    }

    fclose(arch);

    //se retorna la pos del dato pedido
    return pos;
}

Prestamo buscar_prestamo_segun_pos(char archPrestamos[],int posId)
{
    Prestamo p;
    FILE *arch;

    arch=fopen(archPrestamos,"rb");

    if(arch!=NULL)
    {
        fseek(arch,sizeof(Prestamo)*posId,SEEK_SET);

        fread(&p,sizeof(Prestamo),1,arch);
    }

    fclose(arch);

    return p;
}

void mostrar_prestamo_hecho(Prestamo entregaHecha)
{
    printf("\t    Datos del usuario\n");
    printf("__________________________________________\n\n");
    printf("%s",entregaHecha.dni);

    printf("\n\t    Datos de entrega\n");
    printf("__________________________________________\n\n");
    printf("Dia: %d",entregaHecha.retirado.dia);
    printf("\nMes: %d",entregaHecha.retirado.mes);
    printf("\nAnio: %d",entregaHecha.retirado.anio);
}

Prestamo cargar_fecha_devolucion(char archPrestamos[],int posId)
{
    FILE *arch;
    Prestamo p;

    //abrimos el archivo con permisos
    arch=fopen(archPrestamos,"r+b");

    //colocamos el cursor en el dato a modificar
    fseek(arch,sizeof(Prestamo)*posId,SEEK_SET);

    fread(&p,sizeof(Prestamo),1,arch);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    //carga de datos en la variable
    printf("\n\t  Datos de devolucion\n");
    printf("__________________________________________\n\n");

    printf("Dia: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    scanf("%d",&p.devolucion.dia);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("Mes: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    scanf("%d",&p.devolucion.mes);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("Anio: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    scanf("%d",&p.devolucion.anio);

    //colocamos el cursor en el dato a modificar
    fseek(arch,sizeof(Prestamo)*(-1),SEEK_CUR);

    //escribimos en el archivo el dato modificado
    fwrite(&p,sizeof(Prestamo),1,arch);

    //Cerramos el archivo
    fclose(arch);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);

    return p;
}

int cantidad_dias_prestados(Prestamo devolucionHecha)
{
    int cant=0;

    int bisiesto[12]= {31,29,31,30,31,30,31,31,30,31,30,31}; //cant de dias de cada mes segun anio bisiesto
    int noBisiesto[12]= {31,28,31,30,31,30,31,31,30,31,30,31}; //cant de dias de cada mes segun anio no bisiesto

    int dias1=0;
    int diasMes1=0;

    int dias2=0;
    int diasMes2=0;

    //primer fecha
    for(int i=1; i<devolucionHecha.retirado.anio; i++)
    {
        if((i%4==0&&i%400!=0)||(i%100==0))// Calcule cuántos años bisiestos hay desde el primer año hasta el año anterior a la fecha y año dados
            dias1++;
    }

    if((devolucionHecha.retirado.anio%4==0&&devolucionHecha.retirado.anio%400!=0)||(devolucionHecha.retirado.anio%100==0))// Determine si el año es bisiesto y luego calcule
    {
        for(int j=0; j<devolucionHecha.retirado.mes; j++)
        {
            diasMes1=diasMes1+bisiesto[j];
        }
    }
    else
    {
        for(int j=0; j<devolucionHecha.retirado.mes; j++)
        {
            diasMes1=diasMes1+noBisiesto[j];
        }
    }
    dias1=(devolucionHecha.retirado.anio-1)*365+dias1+diasMes1+devolucionHecha.retirado.dia; // Agregue el número de días para calcular el número de días desde la primera fecha dada hasta el 1 de enero, 1


    //segunda fecha
    for(int i=1; i<devolucionHecha.devolucion.anio; i++)
    {
        if((i%4==0&&i%400!=0)||(i%100==0))
            dias2++;
    }

    if((devolucionHecha.devolucion.anio%4==0&&devolucionHecha.devolucion.anio%400!=0)||(devolucionHecha.devolucion.anio%100==0))
    {
        for(int j=0; j<devolucionHecha.devolucion.mes; j++)
        {
            diasMes2=diasMes2+bisiesto[j];
        }
    }
    else
    {
        for(int j=0; j<devolucionHecha.devolucion.mes; j++)
        {
            diasMes2=diasMes2+noBisiesto[j];
        }
    }
    dias2=(devolucionHecha.devolucion.anio-1)*365+dias2+diasMes2+devolucionHecha.devolucion.dia;

// Salida de la diferencia en días
    if(dias1>dias2)
    {
        cant=dias1-dias2;
    }
    else
    {
        cant=dias2-dias1;
    }

    return cant;
}

int calcular_deuda(int cantDias, int cantDiasPermitidos)
{
    int deuda=0;
    int diferencia=cantDias-cantDiasPermitidos;

    if(diferencia==0) //no se le palica deuda
    {
        deuda=0;
    }
    else if(diferencia>=3 && diferencia<=14)  //se paso por 3 dias
    {
        deuda=DEUDA3DIAS;
    }
    else if(diferencia>=15 && diferencia<=89)  //se paso por 15 dias
    {
        deuda=DEUDA15DIAS;
    }
    else  //90 dias o mas
    {
        deuda=DEUDA90DIAS;
    }

    return deuda;
}

void cargar_deuda_usuario(char archivo[],int pos,int deuda)
{
    //creamos buffer del archivo de usuarios
    FILE *arch;

    //variable tipo persona
    Persona usuario;

    //abrimos el archivo con permisos de agregado
    arch=fopen(archivo,"r+b");

    if(arch!=NULL)
    {
        //posicionamos el cursor en e dato
        fseek(arch,sizeof(Persona)*pos,SEEK_SET);

        fread(&usuario,sizeof(Persona),1,arch);

        //modificamos el dato
        usuario.deuda+=deuda;

        //posicionamos el cursor en e dato
        fseek(arch,sizeof(Persona)*-1,SEEK_CUR);

        //escribimos el dato modificado
        fwrite(&usuario,sizeof(Persona),1,arch);
    }

    //cerramos el buffer
    fclose(arch);
}

void puntuar_libro(char archivo[],int pos)
{
    FILE *arch;
    Libro librito;
    float puntuacionUsuario=0;
    float aux=0;

    //ingreso de la puntuacion
    printf("\t  Puntuacion del libro\n");
    printf("__________________________________________\n\n");
    printf("Ingrese la puntuacion del libro(0-5): ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    scanf("%f",&puntuacionUsuario);
    Beep(70,200);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);

    arch=fopen(archivo,"r+b");

    //modificacion de la puntuacion en el archivo
    if(arch!=NULL)
    {
        fseek(arch,sizeof(Libro)*pos,SEEK_SET);

        fread(&librito,sizeof(Libro),1,arch);

        //promedio de la puntuacion
        if(librito.puntuacion!=0)
        {
            aux=(puntuacionUsuario+librito.puntuacion)/2;
        }
        else
        {
            aux=puntuacionUsuario;
        }

        //actualizacion de la puntuacion
        librito.puntuacion=aux;

        fseek(arch,sizeof(Libro)*-1,SEEK_CUR);

        fwrite(&librito,sizeof(Libro),1,arch);
    }

    fclose(arch);
}

void cambiar_estado_disponible(char archivo[],int pos)
{
    //abrimos el buffer el archivo de copias
    FILE *arch;
    Copia librito;

    //abrimos el archivo con permisos de agregar
    arch=fopen(archivo,"r+b");

    if(arch!=NULL)
    {
        //posicionamos el cursor en el dato
        fseek(arch,sizeof(Copia)*pos,SEEK_SET);

        fread(&librito,sizeof(Copia),1,arch);

        //modificamos el dato
        librito.estado=2;

        //posicionamos el cursor en el dato
        fseek(arch,sizeof(Copia)*-1,SEEK_CUR);

        //sobreescribimos el dato con la modificacion
        fwrite(&librito,sizeof(Copia),1,arch);
    }

    //cerramos el buffer
    fclose(arch);
}

void decrementar_prestacion(char archivo[],int pos)
{
    FILE *arch;
    Persona usuario;

    arch=fopen(archivo,"r+b");

    if(arch!=NULL)
    {
        //posicionamienot del cursor
        fseek(arch,sizeof(Persona)*pos,SEEK_SET);

        //lee el dato
        fread(&usuario,sizeof(Persona),1,arch);

        //lo modifica
        usuario.cantLibros-=1;

        //vuelve a posicionar el cursor
        fseek(arch,sizeof(Persona)*-1,SEEK_CUR);

        //escribe el dato modificado
        fwrite(&usuario,sizeof(Persona),1,arch);
    }

    fclose(arch);
}

void nueva_devolucion(char archPrestamos[],char archLibros[],char archCopias[],char archUsuarios[])
{
    //variables temporales para ser verificadas
    char idIngresado[30];
    //variables de posicion
    int posId=0;
    int posLibro=0;
    int posCopia=0;
    int posUsuario=0;
    //variable de cantididad de dias del libro en posesion del usuario
    int cantDias=0;
    //variable de deuda
    int plazoDias=0;
    int deuda=0;
    //variable
    Prestamo entregaHecha;
    Prestamo devolucionHecha;
    Copia copiaLibro;
    Libro libroRegistrado;
    Persona usuario;

    system("COLOR 8f");
    printf("\t----------------------\n");
    printf("\t|      DEVOLUCION       |\n");
    printf("\t----------------------\n\n");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    printf("\t    Datos del libro\n");
    printf("__________________________________________\n\n");

    //ingreso del id interno
    printf("Id interno: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | BACKGROUND_INTENSITY);
    fflush(stdin);
    gets(idIngresado);
    Beep(600,100);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
    //verificaiones la existencia del prestamo
    posId=buscar_id_prestamos(archPrestamos,idIngresado);
    if(posId==-1)  //si no se encuentra el prestamos de entrega
    {
        Beep(70,200);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 | BACKGROUND_INTENSITY);
        printf("-------------------------------------------------\n\n");
        printf("\t  Prestamo de entrega no encontrado\n\n");
        printf("-------------------------------------------------\n\n");

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);
        printf("Sera redirigido al menu principal.\n\n");

        system("pause");

    }
    else    //si se encuentra el prestamo de entrega
    {
        //retornamos la variable de la entrega hecha
        entregaHecha=buscar_prestamo_segun_pos(archPrestamos,posId);
        //mostramos la info de cuando se retiro
        mostrar_prestamo_hecho(entregaHecha);
        //se completa la fecha de devolucion y retorna la variable modificada
        devolucionHecha=cargar_fecha_devolucion(archPrestamos,posId);

        //calculo de dias de prestacion
        cantDias=cantidad_dias_prestados(devolucionHecha);

        //verificar si el plazo de dias sobrepasa el del libro en especifico
        posCopia=posIdInternoCopia(archCopias,idIngresado);
        copiaLibro=buscar_copia_segun_pos(archCopias,posCopia);//obtenemos el isbn
        posLibro=buscar_pos_libro(archLibros,copiaLibro.isbn);//pos de libro
        libroRegistrado=buscar_libro_segun_pos(archLibros,posLibro);//retorna la variable

        //pos de usuario y variable
        posUsuario=buscar_pos_usuario(archUsuarios,devolucionHecha.dni);
        usuario=buscar_persona_segun_pos(archUsuarios,posUsuario);

        if(cantDias>libroRegistrado.diasPrestamo)//sobrepasa la cant de dias permitidos?
        {
            deuda=calcular_deuda(cantDias,libroRegistrado.diasPrestamo);

            //carga de deuda al usuario
            if(deuda!=0)
            {
                cargar_deuda_usuario(archUsuarios,posUsuario,deuda);
                printf("\n\t*Deuda aplicada: $%d*\n\n",deuda);
            }
        }

        //ingreso de puntuacion del libro
        puntuar_libro(archLibros,posLibro);

        //cambio del estado de la copia del libro
        cambiar_estado_disponible(archCopias,posCopia); //!poslibro

        //decremeto de la cantidad de libros en posesion del usuaripo
        decrementar_prestacion(archUsuarios,posUsuario);

        system("pause");
        system("cls");

        printf("-------------------------------------------------\n\n");
        printf("\t   Devolucion registrada con exito\n\n");
        printf("-------------------------------------------------\n\n");

        system("pause");
    }
}
/**********************************************************************************
***********************************************************************************/
int pasar_libros(char archiLibros[],Libro libros[500])
{
    FILE *arch;
    Libro librito;
    int validos=0;

    arch=fopen(archiLibros,"rb");

    while(fread(&librito,sizeof(Libro),1,arch)>0 && validos<500)
    {

        libros[validos]=librito;

        validos+=1;
    }

    fclose(arch);

    return validos;
}

void intercambiar_datos(Libro libros[500],int origen,int destino)
{
    Libro aux;
    aux=libros[origen];

    libros[origen]=libros[destino];
    libros[destino]=aux;
}

void ordenamiento_insercion(Libro libros[500],int validos)
{
    int pos=0;

    //se selecciona un elemento para comparar (pos 1)
    for(int i=1; i<validos; i++)
    {
        //se compara con el resto de elementos que tiene antes
        for(int j=i-1; j>=0; j--)
        {
            if(libros[i].puntuacion>libros[j].puntuacion)
            {
                pos=j;
            }
        }
        //se intercambian los datos
        if(libros[i].puntuacion>libros[pos].puntuacion){
            intercambiar_datos(libros,i,pos);
        }
    }


}

void escribir_top(char archiTop[],int validos,Libro libros[500])
{
    FILE *arch;
    Libro librito;

    arch=fopen(archiTop,"wb");

    if(arch!=NULL)
    {
        for(int i=0; i<validos; i++)
        {
            librito=libros[i];
            fwrite(&librito,sizeof(Libro),1,arch);
        }
    }

    fclose(arch);
}

void mostar_top(char archiTop[],int validos)
{
    FILE *arch;
    Libro librito;
    int i=0;


    system("COLOR 8f");
    printf(" ------------------------- \n");
    printf("|          TOP 10         | \n");
    printf(" ------------------------- \n\n");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | BACKGROUND_INTENSITY);

    if(validos==0)
    {

        printf("Todavia no se han cargado libros..\n\n");
    }
    else
    {
        arch=fopen(archiTop,"rb");

        while(fread(&librito,sizeof(Libro),1,arch)>0 && i<10)
        {
            printf("------------%d------------- \n\n",i+1);
            mostrarLibro(librito,1);
            i+=1;
        }
    }

    fclose(arch);
}

void libros_populares(char archiLibros[],char archiTop[])
{
    Libro libros[500];
    int validos=0;

    //pasar libros a arreglo tipo libro
    validos=pasar_libros(archiLibros,libros);

    //ordenar el array
    ordenamiento_insercion(libros,validos);

    //escribir el array en el archivo
    escribir_top(archiTop,validos,libros);

    Beep(400,500);
    //mostrar el top10
    mostar_top(archiTop,validos);

    system("pause");
}
