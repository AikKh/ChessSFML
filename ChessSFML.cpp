#include "h/Game.h"

int main()
{

    Selector* selector = new ClassicSelector();
    Validator* validator = new AdvancedValidator();
    
    Dragger dragger = Dragger(*validator);
    Drawer drawer = Drawer();

    Game game("Chess", drawer, dragger, *selector);
    game.Run();

    delete validator;
    delete selector;

    return 0;
}