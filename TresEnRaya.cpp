#include <iostream>
#include <string>
#include <limits>



struct rep_posi{
    bool ocupada;
    std::string tipo;
};
typedef rep_posi*posi;

void Imprimir(posi cel){
    std::cout<<"\n";
    std::cout<<cel[0].tipo<<"|"<<cel[1].tipo<<"|"<<cel[2].tipo<<"\n";
    std::cout<<      "--- "<<       "--- "<<           "---\n";
    std::cout<<cel[3].tipo<<"|"<<cel[4].tipo<<"|"<<cel[5].tipo<<"\n";
    std::cout<<      "--- "<<       "--- "<<           "---\n";
    std::cout<<cel[6].tipo<<"|"<<cel[7].tipo<<"|"<<cel[8].tipo<<"\n";

}


posi crearceldas(){
    posi celda = new rep_posi[9];
    for (int i = 0; i < 9; i++){
        celda[i].ocupada = false;
        celda[i].tipo = "   ";
    }
    return celda;
}


void limpiartabla(posi tabla){
    for (int i = 0; i < 9; i++){
        tabla[i].ocupada = false;
        tabla[i].tipo = "   ";
    }
}


void borrartabla(posi tabla){
    delete[] tabla;
    tabla = NULL;
}


void marcar(posi &tabla, int turno, int numpartidas){
    bool sejugo = false;
    while (!sejugo){  
        int p;
        std::cout<<"Seleccione una posicion: "; 
        std::cin>>p;
        if (std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout<<"Se a ingresado Algo no Valido\n";
            continue;
        }
        if (( p < 1 ) || ( p > 9 ) || ( tabla[p-1].ocupada == true) ){
            std::cout<<"Seleccione una posicion valida\n";
            Imprimir(tabla);
            continue;
        }
        else{
            if( ( numpartidas % 2 ) == 1){
                tabla[p-1].ocupada = true;
                if (turno % 2 == 1){
                    tabla[p-1].tipo = " x ";
                }
                else
                    tabla[p-1].tipo = " o ";
                sejugo = true;
            }
            else{
                tabla[p-1].ocupada = true;
                if (turno % 2 == 1){
                    tabla[p-1].tipo = " o ";
                }
                else
                    tabla[p-1].tipo = " x ";
                sejugo = true;
            }
        }
    }
}

bool wincheck(posi tabla){
    std::string equis;
    equis = " x ";
    std::string circu;
    circu = " o ";
    //checkeo las filas
    if( (tabla[0].ocupada == true) && (tabla[1].ocupada == true) && (tabla[2].ocupada == true)){
        if ( (tabla[0].tipo == equis) && (tabla[1].tipo == equis) && (tabla[2].tipo == equis) || ( (tabla[0].tipo == circu) && (tabla[1].tipo == circu) && (tabla[2].tipo == circu) )){
            return true;
        }
    }
    if ( ( ( tabla[3].ocupada == true ) && ( tabla[4].ocupada == true ) && ( tabla[5].ocupada == true )) ){
        if ( (tabla[3].tipo == equis) && (tabla[4].tipo == equis) && (tabla[5].tipo == equis) || ( (tabla[3].tipo == circu) && (tabla[4].tipo == circu) && (tabla[5].tipo == circu) )){
            return true;
        }
    }
    if ( ( ( tabla[6].ocupada == true )&& (tabla[7].ocupada == true ) && ( tabla[8].ocupada == true ) ) ){
        if ( (tabla[6].tipo == equis) && (tabla[7].tipo == equis) && (tabla[8].tipo == equis) || ( (tabla[6].tipo == circu) && (tabla[7].tipo == circu) && (tabla[8].tipo == circu) )){
            return true;
        }
    }

    //chekeo las columnas

    if ( ( ( tabla[0].ocupada == true ) && ( tabla[3].ocupada == true ) && ( tabla[6].ocupada == true ) ) ){
        if ( ( tabla[0].tipo == equis ) && ( tabla[3].tipo == equis ) && ( tabla[6].tipo == equis ) || ( (tabla[0].tipo == circu) && (tabla[3].tipo == circu) && (tabla[6].tipo == circu) )){
            return true;
        }
    }
    if ( ( ( tabla[1].ocupada == true ) && ( tabla[4].ocupada == true ) && ( tabla[7].ocupada == true ) ) ){
        if ( (tabla[1].tipo == equis) && (tabla[4].tipo == equis) && (tabla[7].tipo == equis) || ( (tabla[1].tipo == circu) && (tabla[4].tipo == circu) && (tabla[7].tipo == circu) )){
            return true;
        }
    }
    if ( ( ( tabla[2].ocupada == true )&& ( tabla[5].ocupada == true ) && ( tabla[8].ocupada == true )) ){
        if ( (tabla[2].tipo == equis) && (tabla[5].tipo == equis) && (tabla[8].tipo == equis) || ( ( tabla[2].tipo == circu ) && ( tabla[5].tipo == circu ) && ( tabla[8].tipo == circu ) )){
            return true;
        }
    }

    //chekeo Diagonales

    if ( ( ( tabla[0].ocupada == true ) && ( tabla[4].ocupada == true ) && ( tabla[8].ocupada == true ) ) ){
        if ( (tabla[0].tipo == equis) && (tabla[4].tipo == equis) && (tabla[8].tipo == equis) || ( (tabla[0].tipo == circu) && (tabla[4].tipo == circu) && (tabla[8].tipo == circu) ) ){
            return true;
        }
    }
    if ( ( ( tabla[2].ocupada == true ) && ( tabla[4].ocupada == true ) &&  ( tabla[6].ocupada == true ) ) ){
        if ( (tabla[2].tipo == equis) && (tabla[4].tipo == equis) && (tabla[6].tipo == equis) || ( (tabla[2].tipo == circu) && (tabla[4].tipo == circu) && (tabla[6].tipo == circu) )){
            return true;
        }
    }
    return false;
}


void indicadorwin(posi tabla, int turno, int numpartidas){
    Imprimir(tabla);
    std::cout<<"\n\n** GANO ";
    if (numpartidas % 2 == 1){
        if (turno % 2 == 0){
            std::cout<<" O **\n\n";
        }
        else{
            std::cout<<" X **\n";
        }
    }
    else{
        if (turno % 2 == 0){
            std::cout<<" X **\n\n";
        }
        else{
            std::cout<<" O **\n";
        }
    }

    limpiartabla(tabla);

}


void contador(int &winx, int &wino,int numpartidas,int turno){
    if( (numpartidas % 2) == 1 ){
        if (turno % 2 == 1)
            winx++;
        else
            wino++;   
    }
    else{
        if (turno % 2 == 0)
            winx++;
        else
            wino++;
    }
}




int main(){
    bool jugar = true;
    int turno;
    int winx,wino;
    int numpartidas;
    bool chek;
    numpartidas = 0;
    winx = 0;
    wino = 0;
    posi tabla = crearceldas();
    while( jugar == true ){
        int opcion;
        std::cout<<":::  Tres En Raya  :::\n\n";
        std::cout<<"1- Jugar     2- Cerrar\n";
        std::cin>>opcion;

        if (std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout<<"Se a ingresado Algo no Valido\n";
            continue;
        }

        turno = 1;
        
        switch (opcion){
        case 1:
            numpartidas+=1;
            std::cout<<"\nNumero de Partidas: "<<numpartidas << "\n";
            std::cout<<"Ganadas de X: "<< winx << "  Ganadas de O : "<< wino;
            while(turno <= 9){
                Imprimir(tabla);
                std::cout<<"\n\nTurno N-"<<turno<<" de: ";
                if (numpartidas % 2 == 1){
                    if (turno % 2 == 1){
                        std::cout<<"x ";
                    }
                    else{
                        std::cout<<"o ";
                    }
                    marcar(tabla, turno, numpartidas);
                    if (wincheck(tabla)){
                        contador(winx,wino,numpartidas,turno);
                        indicadorwin(tabla,turno, numpartidas);
                        break;
                    }
                }
                else{
                    if (turno % 2 == 1){
                        std::cout<<"o ";
                    }
                    else{ 
                        std::cout<<"x ";
                    }
                    marcar(tabla, turno, numpartidas);
                    if (wincheck(tabla)){
                        contador(winx,wino,numpartidas,turno);
                        indicadorwin(tabla, turno, numpartidas);
                        break;
                    }
                }
                turno++;
            }
            
            if (turno > 9){
                Imprimir(tabla);
                limpiartabla(tabla);
                std::cout<<"\n** Empate **\n\n";
            }
            
            continue;
        case 2:
            borrartabla(tabla);
            jugar = false;
            continue;
        
        default:
            std::cout<<"Error de Seleccion\n";
            std::cout<<"Seleccione una de las Opciones\n";
            continue;;
        }
    }
}
