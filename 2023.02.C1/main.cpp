#include <iostream>

using namespace std;

/*
Requerimiento del enunciado:
Si por algún motivo necesita calcular la cantidad de cifras de un número 
debe utilizar si o si estructuras iterativas, no puede utilizar ninguna fórmula.
*/
int obtenerLongitudNumero(string sNumeroEvaluar) {
    int iLongitud = 0;
    while (sNumeroEvaluar[iLongitud] != '\0') {
        iLongitud++;
    }
    return iLongitud;
}

bool isNumericChar(char c) {
    return (c >= '0' && c <= '9');
}

bool contieneOcho(int sNumeroEvaluar, int iOcho) {
    /*Función que se encarga de validar si el número ingresado presenta el dígito 8, 
    ya sea en la parte 1 o parte 2*/
    while (sNumeroEvaluar > 0) {
        int iDigitoActual = sNumeroEvaluar % 10;
        if (iDigitoActual == iOcho)
        {
            cout << "Existe el digito 8 en la parte 1 o parte 2 del numero." << endl;
            return true;
        }
        //Continua buscando en el siguiente numero
        sNumeroEvaluar /= 10;
    }
    return false; //No contiene un digito Ocho
}

bool sonConsecutivosOrdenados(int sNumeroEvaluar) {
    /* Los dígitos de la parte 1 del número deben ser consecutivos y ordenados de forma ascendente 
    de izquierda a derech  */
    int iDigitoPrevio = sNumeroEvaluar % 10;
    sNumeroEvaluar /= 10;
    while (sNumeroEvaluar > 0) {
        int iDigitoActual = sNumeroEvaluar % 10;
        if (iDigitoActual + 1 != iDigitoPrevio)
        {
            cout << "Los digitos de la parte 1 del numero, no son consecutivos." << endl;
            return false;

        }
        iDigitoPrevio = iDigitoActual;
        sNumeroEvaluar /= 10;
    }
    return true; //Los digitos si son consecutivos
}

int main() {
    string sNumeroEvaluar;
    bool bPrimeraVez = true;
    //Bucle principal
    while (true) {
        if (!bPrimeraVez)
        {   //La primera vez no se ejecuta
            string sSalir;
            cout << "Desea salir? (S o s): ";
            cin >> sSalir;

            if (sSalir == "S" || sSalir == "s")
                break;
            
        }
        bPrimeraVez = false; //Para que se ejecute de aqui en adelante

        cout << "Ingrese el numero a evaluar: ";
        cin >> sNumeroEvaluar;

        int iNumeroCurioso = 0;
        bool isValidInput = true;
        int iLongitudNumeroCurioso = obtenerLongitudNumero(sNumeroEvaluar);
        for (int i = 0; i < iLongitudNumeroCurioso; ++i) {
            char cDigito = sNumeroEvaluar[i];
            if (cDigito >= '0' && cDigito <= '9') {
                iNumeroCurioso = iNumeroCurioso * 10 + (cDigito - '0');
            }
            else {
                cout << "Entrada invalida. Ingrese un numero valido." << endl;
                isValidInput = false;
                break;
            }
        }

        if (!isValidInput)
            continue; //Bucle principal

        int iParte_1 = iNumeroCurioso / 10;
        int iParte_2 = iNumeroCurioso % 10;

        if (iParte_2 != 9) {
            cout << "La parte 2 del numero no es 9." << endl;
            continue; //Bucle principal
        }

        if (contieneOcho(iParte_1, 8) || !sonConsecutivosOrdenados(iParte_1)) {
            continue; //Bucle principal
        }
        //Fin de validaciones
        
        //Como el número es válido, evaluamos si el número iNumeroCurioso cumple con la propiedad:
        bool bProductoCurioso = true;
        for (int i = 9; i <= 81; i += 9) {
            //Multiplicamos iNumeroCurioso x 9/18/27/.../81
            int iNumeroMultiplo9 = iNumeroCurioso * i;
            //Extraemos el ultimo digito:
            int iUltimoDigito = iNumeroMultiplo9 % 10; 
            while (iNumeroMultiplo9 > 0) {
                //Comparamos el ultimo digito de iNumeroMultiplo9 con iUltimoDigito
                if (iNumeroMultiplo9 % 10 != iUltimoDigito) {
                    //El numero no cumple
                    bProductoCurioso = false; 
                    break; //Sale del bucle While
                }
                //Eliminamos el ultimo digito para continuar evaluando la propiedad
                iNumeroMultiplo9 /= 10; 
            }
            if (bProductoCurioso)
            {
                //Mensaje de cada iteración [9/18/27/.../81] correcta
                cout << iNumeroCurioso << " x " << i << " = " << (iNumeroCurioso * i) << ", se cumple la propiedad." << endl;
            }
            else
            {
                //Mensaje que no cumple la propiedad:
                cout << iNumeroCurioso << " x " << i << " = " << (iNumeroCurioso * i) << ", no cumple la propiedad." << endl;
                break; //Sale del bucle FOR
            }
        }
        
    }

    cout << "Programa finalizado." << endl;
    cout << "Ing. Manuel Chavez - PUCP.LPOO.2023.2" << endl;
    return 0;
}