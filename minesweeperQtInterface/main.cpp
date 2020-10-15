#include "menu.h"


int main(int argc, char *argv[]){
    //On ultilisera un Devise Manager pour tous l'application
    QApplication app(argc, argv);
    Menu m;
    m.setFixedSize(400,200);
    m.show();
    return app.exec();
}
