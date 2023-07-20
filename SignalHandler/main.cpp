#include "signalhandler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SignalHandler w;
    w.show();

    return a.exec();
}
