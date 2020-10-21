#ifndef UI_MAINWINDOW_HEADER
#define UI_MAINWINDOW_HEADER

#include "qmainwindow.h"
#include <QLineEdit>
#include <QShortcut>
#include <QStatusBar>
#include <QWebEngineView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow {
public:
  QWidget *centralwidget;
  QWebEngineView *Preview;
  QLineEdit *FileInput;
  QStatusBar *StatusBar;

  void setupUi(QMainWindow *MainWindow) {
    if (MainWindow->objectName().isEmpty())
      MainWindow->setObjectName("MainWindow");
    MainWindow->resize(800, 600);
    Preview = new QWebEngineView(MainWindow);
    Preview->setObjectName("preview");

    FileInput = new QLineEdit();
    FileInput->setObjectName("fileInput");
    FileInput->setPlaceholderText("File");
    FileInput->hide();

    StatusBar = new QStatusBar();
    StatusBar->hide();

    MainWindow->setMenuWidget(FileInput);
    MainWindow->setCentralWidget(Preview);
    MainWindow->setStatusBar(StatusBar);

    MainWindow->setWindowTitle(
        QCoreApplication::translate("MainWindow", "MarkDown Editor", nullptr));

    QMetaObject::connectSlotsByName(MainWindow);
  }
};

namespace Ui {
class MainWindow : public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif
