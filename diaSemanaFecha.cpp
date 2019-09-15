
/**
   Mostrará por pantalla el día de la semana en el que
   cae la fecha que se pedirá al usuario por teclado.
   El valor del año estará entre 1601 y 3000
*/

using namespace std;

#include <iostream>
#include <string>

//Declaración de funciones
bool isDateOk(string dateC);
bool separadorOk(string dateC);
bool isNumberDate(string dateC);
bool isLeapYear(int year);
bool monthOk(int month);
bool yearOk(int year);
bool dayOk(int day, int month, int year);
int firstDayYear(int year);
int firstDayMonth(int year, int month);
string dayWeekText(int dW);


int main() {
    string dateC,d;
	int year,month,day,fDM,D,dW;
	bool S,OK;
	char seguir;

	S=true;
	while(S){
        //Pedir por teclado la fecha indicando el formato
        cout<<"\nINTRODUCE UNA FECHA (DD/MM/AAAA)....";
        cin>>dateC;

        //Comprobar que la fecha es válida
        OK=isDateOk(dateC);
        if (OK){
                //Se convierten los caracteres a números para poder operar con ellos
                d=dateC.at(0);
                d+=dateC.at(1);
                day=stoi(d);
                d=dateC.at(3);
                d+=dateC.at(4);
                month=stoi(d);
                d=dateC.at(6);
                d+=dateC.at(7);
                d+=dateC.at(8);
                d+=dateC.at(9);
                year=stoi(d);

                fDM=firstDayMonth(year,month);     //Primer día del mes
                D=(day-1)%7;
				dW=fDM+D;       // Día de la semana en que cae la fecha
				if (dW>7){
					dW-=7;
				}
				cout<<endl;
				cout<<endl;
				cout<<"LA FECHA ";
				cout<<dateC;
				cout<<" CAE EN ";
				cout<<dayWeekText(dW);
				cout<<endl;
				cout<<endl;
            }
			else{
                // Si la fecha no es correcta
				cout<<"FECHA INCORRECTA. INTÉNTALO DE NUEVO."<<endl;
            }
		cout<<"Pulsar la tecla S para continuar ...";
		cin>>seguir;
        if ((seguir=='S') || (seguir=='s')){
			S=true;
        }
        else{
			S=false;
        }
	}

    return 0;
}

//Definición de funciones
/**
   Comprueba que la fecha tiene el formato correcto
   y que es una fecha válida
 */
bool isDateOk(string dateC){
	bool OK;
	int lDate, month, year, day;
	string d;

	lDate=dateC.length();
	if (lDate != 10) {
		OK=false;				// La cadena no tiene 10 caracteres, luego es incorrecta
	}
	else{
		// Comprobar si los caracteres de separación son los correctos
		OK=separadorOk(dateC);
		if (OK){
            //Comprobar que los demás caracteres sean todos numéricos
            OK=isNumberDate(dateC);
            if (OK){
                //Si todos son numéricos convertir a número para poder calcular
                d=dateC.at(0);
                d+=dateC.at(1);
                day=stoi(d);
                d=dateC.at(3);
                d+=dateC.at(4);
                month=stoi(d);
                d=dateC.at(6);
                d+=dateC.at(7);
                d+=dateC.at(8);
                d+=dateC.at(9);
                year=stoi(d);
                // Comprobar si el mes es correcto
               OK=monthOk(month);
                if (OK){
                    // Comprobar si el año es correcto
					OK=yearOk(year);
					if (OK){
						OK=dayOk(day,month,year);
					}
                }
            }
		}
	}

return OK;
}

/**
   Comprueba que los caracteres separadores son los correctos
*/
bool separadorOk(string dateC) {
    bool OK;
    if ((dateC.at(2)=='/') && (dateC.at(5)=='/')) {
        OK=true;
    }
    else {
            if ((dateC.at(2)=='-') && (dateC.at(5)=='-')) {
                OK=true;
            }
            else {
                OK=false;
            }
    }

	return OK;
}

/**
    Comprueba que los caracteres del día, mes y año sean numéricos
*/
bool isNumberDate(string dateC){
	// Declarar variables
	bool OK;
	int i;
	i=0;
	while (i<=9) {
		if ((i==2) || (i==5)) {
			i++;
		}
		else {
			if (isdigit(dateC.at(i))) {
				OK=true;
				i++;
			}
			else {
                OK=false;
				i=10;
            }
		}
	}

return OK;
}

/**
    Comprueba si el mes de la fecha es válido
*/
bool monthOk(int month){
	bool OK;

	if (month>=1 && month<=12){
		OK=true;
	}
	else{
		OK=false;
	}

	return OK;
}

/**
    Comprueba si el año de la fecha es válido
*/
bool yearOk(int year){
    // Declarar variables
	bool OK;

	if (year>=1601 && year<=3000){
		OK=true;
	}
	else{
		OK=false;
	}

	return OK;
}

/**
    Comprueba si el día de la fecha es válido
*/
bool dayOk(int day, int month, int year){
	bool OK;

	if (day>=1 && day<=31){
		switch(day){
			case 31:
				if (month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12){
					OK=true;
				}
				else{
					OK=false;
				}
				break;
			case 30:
				if (month==2){
					OK=false;
				}
				else{
                    OK=true;
				}
				break;
			case 29:
				if ((month==1) || (month>=3 && month<=12) || ((month==2) && isLeapYear(year))){
					OK=true;
				}
				else{
					OK=false;
				}
				break;
			default:
				OK=true;
		}
	}
	return OK;
}

/**
    Recibe el año (year) y devuelve (lY) si es bisiesto o no
*/
bool isLeapYear(int year){
    bool lY;

	//Si el año es múltiplo de 4
	if (year%4==0){
		lY=true;
		//Si además es múltiplo de 100 y de 400
		if ((year%100!=0) || (year%400==0)){
			lY=true;
		}
		else{
			lY=false;
		}
	}
	else{
		lY=false;
	}

	return lY;
}

/**
    Recibe el año (year) y mes (month) correspondientes y
    devuelve el día de la semana (dW) en el que cae el primer día del mes de ese año
*/
int firstDayMonth(int year, int month){
    int fDY,dW,i;
	bool lY;
	lY=isLeapYear(year); // ¿Es un año bisiesto?
	fDY=firstDayYear(year); // Primer día de la semana del año

	for(i=1; i<=month; i++){
		// Si es enero, el primer día será el primer día del año
		if (i==1){
			dW=fDY;
		}
		// Si es marzo, el primer día dependerá de si el año es bisiesto o no
		if (i==3){
			if(lY){
				dW++;
			}
			else{
				dW=dW;
			}
		}
		// Si es un mes precedido de otro de 31 días, se le sumarán 3 días
		if ((i==2) || (i==4) || (i==6) || (i==8) || (i==9) || (i==11)){
			dW+=3;
		}
		// Si es un mes precedido de otro de 30 días, se le sumarán 2 días
		if ((i==5) || (i==7) || (i==10) || (i==12)){
			dW+=2;
		}
		// Si llega a 8, es lunes
		if (dW==8){
			dW=1;
		}
		// Si llega a 9, es martes
		if (dW==9){
			dW=2;
		}
		// Si llega a 10, es miércoles
		if (dW==10){
			dW=3;
		}
	}

	return dW;
}

/**
    Recibe el año (year) correspondiente y
    devuelve el día de la semana (dW) en el que cae el primer día de dicho año
*/
int firstDayYear(int year){
    int dW,i;
	bool lY;

	if (year==1601){
		// Si es 1601, el primer día del año es Lunes
		dW=1;
	}
	else{
		// Si el año es mayor que 1601
		// Buscar primer día del año
		dW=1; // Se comienza en lunes
		for(i=1602; i<=year; i++){
			// Si el año anterior fue bisiesto el día la semana
			// habrá que sumarle dos más, y sino uno.
			lY=isLeapYear(i-1);
			if(lY){
                dW+=2;
			}
			else{
				dW++;
			}
			// Si se llega a 8, es lunes
            if (dW==8){
				dW=1;
            }
			// Si se llega a 9, es martes
			if(dW==9){
				dW=2;
			}
		}
	}

	return dW;
}

/**
    Devuelve el día de la semana (dW) en texto
*/
string dayWeekText(int dW){
	string dWT;

	switch(dW){
		case 1:
			dWT="LUNES";
			break;
		case 2:
			dWT="MARTES";
			break;
		case 3:
			dWT="MIÉRCOLES";
			break;
		case 4:
			dWT="JUEVES";
			break;
		case 5:
			dWT="VIERNES";
			break;
		case 6:
			dWT="SÁBADO";
			break;
		case 7:
			dWT="DOMINGO";
			break;
		default:
			dWT="PARECE QUE HAY ALGÚN ERROR";
	}

	return dWT;
}
