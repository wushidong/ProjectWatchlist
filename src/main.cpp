#include <QtGui/QApplication>
#include <QDeclarativeContext>
#include "qmlapplicationviewer.h"
#include "controller.h"
#include "tvshowdata.h"
#include "database.h"
#include <QtDeclarative>
#include "cursorshapearea.h"

#include "NcFramelessHelper.h"

#include <QVBoxLayout>

#include "mainview.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainView* view = new MainView;

    QMainWindow window;

    QWidget* widgi = new QWidget;
    QVBoxLayout* box = new QVBoxLayout;

    box->setMargin(1);

    NcFramelessHelper helper;

    helper.activateOn(widgi);
    helper.setWidgetMovable(true);
    helper.setWidgetResizable(true);

    box->addWidget(&window);
    widgi->setLayout(box);
    widgi->setWindowFlags(Qt::FramelessWindowHint);

    window.setCentralWidget(view);

    // Set up controller
    Controller c;
    view->setResizeMode(QDeclarativeView::SizeRootObjectToView);
    QDeclarativeContext *ctxt = view->rootContext();

    //init DB
    Database db;
    db.load();

    // hand database to controller
    c.data = db.data;

    // Set up Datalist and Controller for qml
    ctxt->setContextProperty("datalist", c.data);
    ctxt->setContextProperty("controller", &c);
    ctxt->setContextProperty("mainwindow", &window);

    qmlRegisterType<QsltCursorShapeArea>("Cursors", 1, 0, "CursorShapeArea");
    QObject::connect((QObject*)view->engine(), SIGNAL(quit()), &app, SLOT(quit()));
    view->setMinimumSize(QSize(500,500));


    view->setSource(QUrl("qrc:///qml/main.qml"));


    // window.setStyleSheet("background:transparent;");
    window.setAttribute(Qt::WA_TranslucentBackground);
    window.setWindowFlags(Qt::FramelessWindowHint);
    widgi->show();

    return app.exec();
}
