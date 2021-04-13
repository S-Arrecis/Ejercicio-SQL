
#include <iostream>
#include <mysql.h>
#include <string.h>
#include <conio.h>

using namespace std;

int q_estado;
MYSQL* conectar;
MYSQL_ROW fila;
MYSQL_RES* resultado;

void menu();
void ver();
void ver2();
void ingresar_marcas();
void ingresar_productos();
void ver_marcas();
void ver_productos();
void eliminar_marcas();
void eliminar_productos();
void modificar_marcas();
void modificar_productos();

int main(){

    conectar = mysql_init(0);
    conectar = mysql_real_connect(conectar, "localhost", "usr_empresa", "Empres@123", "ejercicio_c_mysql", 3306, NULL, 0);

    if (conectar) {
        system("color 02");
        cout << "\n\n\t\tConexion exitosa...\n\n" << endl;
        system("pause");

        menu();
    }

    else {
        system("color 0c");
        cout << "\n\n\t\tError al realizar la conexion..\n\n" << endl;
        system("pause");
    }
    

    system("pause");

    return 0;
}

void menu() {
    system("color 07");
    system("cls");
    int opcion;

    do {
        
        cout << "\n\t\t\t.:Bienvenido:.\n\n" << endl;
        cout << "1. Ingresar Marcas. " << endl;
        cout << "2. Ingresar Productos. " << endl;
        cout << "3. Modificar Marcas. " << endl;
        cout << "4. Modificar Productos." << endl;
        cout << "5. Eliminar Marcas. " << endl;
        cout << "6. Eliminar Productos. " << endl;
        cout << "7. Ver Marcas. " << endl;
        cout << "8. Ver Productos. " << endl;
        cout << "9. Salir. " << endl;
        cout << "\nDigite una opcion: ";
        cin >> opcion;

        switch (opcion){
        case 1: system("cls"); ingresar_marcas(); break;
        case 2: system("cls"); ingresar_productos(); break;
        case 3: system("cls"); modificar_marcas(); break;
        case 4: system("cls"); modificar_productos(); break;
        case 5: system("cls"); eliminar_marcas(); break;
        case 6: system("cls"); eliminar_productos(); break;
        case 7: system("cls"); ver_marcas(); break;
        case 8: system("cls"); ver_productos(); break;
        case 9: system("cls"); cout << "Saliendo del sistema..\n\n" << endl; system("pause"); exit(1); break;

        default: system("cls"); cout << "La opcion no es valida.." << endl; system("pause"); menu();
        }
    
    
    } while (opcion!=9);
}

void ingresar_marcas() {
    system("cls");
    cout << "\n\n\t\t.:Ingresar Marca:.\n\n" << endl;
    string marca;
    cout << "Ingrese Nombre de la Marca: ";
    cin >> marca;
    string insert = "insert into Marcas(marca) values('" + marca + "')";
    const char* insertar = insert.c_str();
    q_estado = mysql_query(conectar, insertar);

    if (!q_estado) {

        system("color 02");
        cout << "\n\n\t\tDatos agregados con exito...\n\n" << endl;
        system("pause");
        menu();
    }
    else {
        system("color 0c");
        cout << "\n\n\t\tError al agregar los datos..\n\n" << endl;
        cout << "\n\n\t\tIniciando conexion de nuevo..\n\n" << endl;
        system("pause");
        main();
    }
}

void ver() {
    system("cls");
    
    string consulta = "select *from Marcas";
    const char* consultar = consulta.c_str();
    q_estado = mysql_query(conectar, consultar);

    if (!q_estado) {
        resultado = mysql_store_result(conectar);

        while (fila = mysql_fetch_row(resultado)) {

            cout << fila[0] << ", " << fila[1] << endl;
        }
    }
    else {
        cout << "xxx Error al consulta xxx" << endl;
    }
}

void ver2() {

    system("cls");

    string consulta = "select *from productos";
    const char* consultar = consulta.c_str();
    q_estado = mysql_query(conectar, consultar);

    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        system("color 02");

        while (fila = mysql_fetch_row(resultado)) {

            cout << fila[0] << " - " << fila[1] << " - " << fila[2] << " - " << fila[3] << " - " << fila[4] << " - " << fila[5] << " - " << fila[6] << " - " << fila[7] << endl;
        }
      
    }
    else {
        system("color 0c");
        cout << "xxx Error al consulta xxx" << endl;
        main();
    }


}

void modificar_marcas() {

    string consulta,dato_antiguo,dato_nuevo;
    ver();
    cout << "\n\n\t\t.:Modificar Marcas:. \n\n" << endl;
    cout << "\nDigite el ID de la marca a modificar: ";
    cin >> dato_antiguo;

 
    cout << "Digite el nuevo Nombre: ";
    cin >> dato_nuevo;
    
    consulta = "update marcas set marca = '" + dato_nuevo + "' where id_marca = ('" + dato_antiguo + "'); ";
    const char* insertar = consulta.c_str();
    q_estado = mysql_query(conectar, insertar);

            if (!q_estado) {

                system("color 02");
                cout << "\n\n\t\tDatos agregados con exito...\n\n" << endl;
                system("pause");
                menu();
            }
            else {
                system("color 0c");
                cout << "\n\n\t\tError al agregar los datos..\n\n" << endl;
                cout << consulta;
                cout << "\n\n\t\tIniciando conexion de nuevo..\n\n" << endl;
                system("pause");
                main();
            }
            

    
    
}

void eliminar_marcas() {

    string consulta, dato_antiguo, dato_nuevo;

    cout << "\n\n\t\t.:Eliminar Marcas:. \n\n" << endl;
    ver();

    cout << "\nDigite el ID de la marca a eliminar: ";
    cin >> dato_antiguo;

    cout << "Esta seguro que desa eliminar el dato (s/n): "; cin >> dato_nuevo;
    
    if (dato_nuevo == "s" || dato_nuevo == "S") {
        consulta = "delete from marcas  where id_marca = '" + dato_antiguo + "'";
        const char* insertar = consulta.c_str();
        q_estado = mysql_query(conectar, insertar);

    }

    else if(dato_nuevo == "n" || dato_nuevo == "N"){
        cout << " \n\nDatos no eliminados.."<<endl;
        menu();
    }


    if (!q_estado) {

        system("color 02");
        cout << "\n\n\t\tDatos eliminados con exito...\n\n" << endl;
        system("pause");
        menu();
    }
    else {
        system("color 0c");
        cout << "\n\n\t\tError al agregar los datos..\n\n" << endl;
        cout << consulta;
        cout << "\n\n\t\tIniciando conexion de nuevo..\n\n" << endl;
        system("pause");
        main();
    }

}

void ver_marcas() {

    system("cls");

    cout << "\n\n\t\t\t.: Marcas Registradas:.\n\n " << endl;

    string consulta = "select *from marcas";
    const char* consultar = consulta.c_str();
    q_estado = mysql_query(conectar, consultar);

    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        system("color 02");

        while (fila = mysql_fetch_row(resultado)) {

            cout << fila[0] << " - " << fila[1] << endl;
        }
        cout << "\n\n\n"; system("pause");
        menu();
    }
    else {
        system("color 0c");
        cout << "xxx Error al consulta xxx" << endl;
        main();
    }
}

void ingresar_productos() {
    fflush(stdin);
    system("cls");
    ver();
    fflush(stdin);
    fflush(stdin);
    cout << "\n\n\t\t.:Ingresar Producto:.\n\n" << endl;
    string producto,id_marca,descripcion,precio_costo,precio_venta,existencia,fecha;
    cout << "Ingrese Nombre del producto: ";
    cin >> producto;
    fflush(stdin);
    fflush(stdin);
    cout << "Ingresse el ID de la Marca: ";
    cin >> id_marca;
    fflush(stdin);
    fflush(stdin);
    cout << "Ingrese la descripcion: ";
    cin>>descripcion;
    fflush(stdin);
    fflush(stdin);
    cout << "Digita el Precio de compra del producto: ";
    cin >> precio_costo;
    fflush(stdin);
    fflush(stdin);
    cout << "Digita el precio de venta del producto: ";
    cin >> precio_venta;
    fflush(stdin);
    fflush(stdin);
    cout << "Digita cuantas existencias hay de este producto: ";
    cin >> existencia;
    fflush(stdin);
    fflush(stdin);
    fecha = "now()";
    string insert = "insert into productos(producto,id_marca,descripcion,precio_costo,precio_venta,existencia,fecha_ingreso) values('" + producto + "',"+ id_marca+",'"+ descripcion+ "',"+ precio_costo + ","+ precio_venta + ","+ existencia + ","+ fecha +")";
    
    const char* insertar = insert.c_str();
    q_estado = mysql_query(conectar, insertar);

    if (!q_estado) {

        system("color 02");
        cout << "\n\n\t\tDatos agregados con exito...\n\n" << endl;
        system("pause");
        menu();
    }
    else {
        system("color 0c");
        cout << "\n\n\t\tError al agregar los datos..\n\n" << endl;
        cout << insert;
        cout << "\n\n\t\tIniciando conexion de nuevo..\n\n" << endl;
        system("pause");
        main();
    }
}


void modificar_productos() {
    string producto, id_marca, descripcion, precio_costo, precio_venta, existencia, fecha,dato_antiguo;

    ver2();
    cout << "\n\n\t\t.:Modificar Producto:. \n\n" << endl;
    cout << "\nDigite el ID del producto a modificar: ";
    cin >> dato_antiguo;

    cout << "Ingrese Nombre del producto: ";
    cin >> producto;
    fflush(stdin);
    fflush(stdin);
    cout << "Ingresse el ID de la Marca: ";
    cin >> id_marca;
    fflush(stdin);
    fflush(stdin);
    cout << "Ingrese la descripcion: ";
    cin >> descripcion;
    fflush(stdin);
    fflush(stdin);
    cout << "Digita el Precio de compra del producto: ";
    cin >> precio_costo;
    fflush(stdin);
    fflush(stdin);
    cout << "Digita el precio de venta del producto: ";
    cin >> precio_venta;
    fflush(stdin);
    fflush(stdin);
    cout << "Digita cuantas existencias hay de este producto: ";
    cin >> existencia;
    fflush(stdin);
    fflush(stdin);
    fecha = "now()";

    string consulta = "UPDATE productos SET producto = '" + producto + "' , id_marca= '" + id_marca + "', descripcion= '" + descripcion + "', precio_costo = '" + precio_costo +"' , precio_venta = '" + precio_venta +"',existencia ='" + existencia + "' WHERE id_productos = '"+dato_antiguo+"'";

    const char* insertar = consulta.c_str();
    q_estado = mysql_query(conectar, insertar);

    if (!q_estado) {

        system("color 02");
        cout << "\n\n\t\tDatos agregados con exito...\n\n" << endl;
        cout << consulta<<"\n\n"<<endl;
        system("pause");
        menu();
    }
    else {
        system("color 0c");
        cout << "\n\n\t\tError al agregar los datos..\n\n" << endl;
        cout << consulta;
        cout << "\n\n\t\tIniciando conexion de nuevo..\n\n" << endl;
        system("pause");
        main();
    }

}



void eliminar_productos() {

    string consulta, dato_antiguo, dato_nuevo;

    cout << "\n\n\t\t.:Eliminar Producto:. \n\n" << endl;
    ver2();

    cout << "\nDigite el ID del producto a eliminar: ";
    cin >> dato_antiguo;

    cout << "Esta seguro que desa eliminar el dato (s/n): "; cin >> dato_nuevo;

    if (dato_nuevo == "s" || dato_nuevo == "S") {
        consulta = "delete from productos  where id_marca = '" + dato_antiguo + "'";
        const char* insertar = consulta.c_str();
        q_estado = mysql_query(conectar, insertar);

    }

    else if (dato_nuevo == "n" || dato_nuevo == "N") {
        cout << " \n\nDatos no eliminados.." << endl;
        menu();
    }


    if (!q_estado) {

        system("color 02");
        cout << "\n\n\t\tDatos eliminados con exito...\n\n" << endl;
        system("pause");
        menu();
    }
    else {
        system("color 0c");
        cout << "\n\n\t\tError al agregar los datos..\n\n" << endl;
        cout << consulta;
        cout << "\n\n\t\tIniciando conexion de nuevo..\n\n" << endl;
        system("pause");
        main();
    }

}



void ver_productos() {
    system("cls");

    cout << "\n\n\t\t\t.: Productos Registrados:.\n\n " << endl;

    string consulta = "select *from productos";
    const char* consultar = consulta.c_str();
    q_estado = mysql_query(conectar, consultar);

    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        system("color 02");

        while (fila = mysql_fetch_row(resultado)) {

            cout << fila[0] << " - " << fila[1] << " - " << fila[2] << " - " << fila[3] << " - " << fila[4] << " - " << fila[5] << " - " << fila[6] << " - " << fila[7] << endl;
        }
        cout << "\n\n\n"; system("pause");
        menu();
    }
    else {
        system("color 0c");
        cout << "xxx Error al consulta xxx" << endl;
        main();
    }
}