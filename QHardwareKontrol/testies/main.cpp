#include <QtCore/QCoreApplication>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    vector <int> vec;
    vec.push_back( 10 );
    vec.push_back( 20 );

    for (int &i : vec ) {
        cout << i;
    }
    return a.exec();
}
