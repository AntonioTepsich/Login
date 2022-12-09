#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#define data "/home/antonio/Desktop/Proyectos/Gui/Login/"
#define archivo "usuarios.csv"

std::vector<std::vector<std::string>> PrimScan(){
    std::string un,pw,linea;
    std::vector<std::string> as; 
    std::vector<std::vector<std::string>> todo;
    std::ifstream read(data archivo);
    char delimiador=';';
    size_t i=0;

    while(getline(read,linea)){
        std::stringstream stream(linea);
        getline(stream,un,delimiador);
        getline(stream,pw,delimiador);

        as.push_back(un);
        as.push_back(pw);

        todo.push_back(as);   
        as.clear();
        i++;
    }
    return todo;
}

bool validarUsuario(std::string username,std::vector<std::vector<std::string>> todo){
    std::string us;
    for(const auto h:todo){
        us=h.at(0);
        if(us==username){
            return true;
        }
    }
    return false;
}
bool validarContra(std::string password,std::vector<std::vector<std::string>> todo){
    std::string pw;
    for(const auto h:todo){
        pw=h.at(1);

        if(pw==password){
            return true;
        }
    }
    return false;
}

bool IsLoggedIn(std::vector<std::vector<std::string>> todo){
    std::string username, password,un,pw,linea;
    bool valC,valU;

    std::cout<<"---------------------------------"<<std::endl;
    std::cout<<"Ingrese Usuario: "; std::cin>>username;
    std::cout<<"Ingrese Contraseña: "; std::cin>>password;

    valC=validarContra(password,todo);
    valU=validarUsuario(username,todo);

    if(valC && valU){
        std::cout<<std::endl;
        std::cout<<"Bienvenido "<<username<<"!!"<<std::endl;
        std::cout<<"---------------------------------"<<std::endl;
        return true;
    }
    else if(!valU){
        std::cout<<std::endl;
        std::cout<<"No existe el usuario"<<std::endl;
        std::cout<<"---------------------------------"<<std::endl;
        return false;
    }
    std::cout<<std::endl;
    std::cout<<"No coincide la contrasena"<<std::endl;
    std::cout<<"---------------------------------"<<std::endl;
    return false;

}

std::vector<std::vector<std::string>> registrar(std::vector<std::vector<std::string>> todo){
    std::string username,password;
    std::vector<std::string> as;

    std::cout<<"---------------------------------"<<std::endl;
    std::cout<<"Seleccione un Usuario: "; std::cin>>username;
    std::cout<<"Seleccione una Contraseña: "; std::cin>>password;

    if(!validarUsuario(username,todo)){
        as.push_back(username);
        as.push_back(password);
        todo.push_back(as);

        std::cout<<std::endl;
        std::cout<<"Registro exitoso!!"<<std::endl;
        std::cout<<"---------------------------------"<<std::endl;

        return todo;
    }
    else{
        std::cout<<std::endl;
        std::cout<<"Usuario existente"<<std::endl;
        std::cout<<"---------------------------------"<<std::endl;
        return todo;
    }

}

void modArchivo(std::vector<std::vector<std::string>> todo){
        std::ofstream file;
        file.open(data archivo);
        for(size_t i=0;i<todo.size();i++){
            file<<todo.at(i).at(0)<<";"<<todo.at(i).at(1)<<std::endl;
        }
        file.close();
        std::cout<<std::endl;
}


int main()
{
    int choice;

    std::cout<<"1: Registrarse\n2: Ingresar\n3: EXIT\n\nTu eleccion: "; std::cin>> choice;

    std::vector<std::vector<std::string>> todo=PrimScan();


    while(choice==1 || choice==2){
        if(choice==1){
            todo=registrar(todo);
        }
        else if(choice==2){
            IsLoggedIn(todo);
        }
        std::cout<<"1: Registrarse\n2: Ingresar\n3: EXIT\n\nTu eleccion: "; std::cin>> choice;
    }
    modArchivo(todo);

    return 0;
    
}
