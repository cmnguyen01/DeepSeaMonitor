#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QtSql>
#include <thread>
#include "fileutils.h"
#include "udphandler.h"
#include <thread>

using namespace std;

void startThread();

int main(int argc, char *argv[])
{

    thread * listener;
    listener = new class thread(&startThread);

    /*
    char * test = "127.0.0.1";
    UdpHandler handler(test,1024,7676);
    handler.startListening();

    // Sleep to See if thread is working;
    //cout << " Started Sleeping " << endl;
    //cout << " Stopped Sleeping " << endl;
    */

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    a.exec();

    //handler.stopListening();

    //databaseManager * dm = new databaseManager();
    //dm->test();

    return 0;//a.exec();
}

void startThread()
{
    char * test = "127.0.0.1";
    UdpHandler handler(test, 1024, 7678);
    handler.startListening();

    // Sleep to See if thread is working;
    cout << " Started Sleeping " << endl;

    sleep(300);

    cout << " Stopped Sleeping " << endl;
    //handler.stopListening();
    //return &handler;
}






