#include <iostream>
#include "Window.h"

int main()
{
Window screen(800, 600, "Test");
while(screen.isRunning()){
    screen.Update();
}
screen.CloseWindow();

}

