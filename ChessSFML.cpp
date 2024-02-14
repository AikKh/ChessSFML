#include "h/Game.h"

int main()
{
    Drawer drawer = Drawer();
    Dragger dragger = Dragger();

    Selector* selector = new ClassicSelector();
    
    Validator* validator = new AdvancedValidator(*selector);

    Game game("Chess", drawer, dragger, *validator);
    game.Run();

    delete validator;
    delete selector;

    return 0;
}