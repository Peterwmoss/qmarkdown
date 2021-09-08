#ifndef UI_MAINWINDOW_HEADER
#define UI_MAINWINDOW_HEADER

#include "fileinput.h"

#include "qmainwindow.h"
#include <QLineEdit>
#include <QShortcut>
#include <QStatusBar>
#include <QWebEngineView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QStackedLayout>

QT_BEGIN_NAMESPACE

class Ui_MainWindow {
public:
  QWebEngineView *WebView;
  FileInput *Input;
  QStatusBar *StatusBar;
  QStackedLayout *Layout;

  void setupUi(QMainWindow *MainWindow) {
    if (MainWindow->objectName().isEmpty())
      MainWindow->setObjectName("MainWindow");
    MainWindow->resize(800, 600);
    WebView = new QWebEngineView(MainWindow);

    Input = new FileInput();
    Input->setObjectName("fileInput");
    Input->setPlaceholderText("File");
    Input->hide();

    StatusBar = new QStatusBar();
    StatusBar->hide();

    MainWindow->setMenuWidget(Input);
    MainWindow->setCentralWidget(WebView);
    MainWindow->setStatusBar(StatusBar);

    MainWindow->setWindowTitle("qMarkdown");
  }
};

namespace Ui {
class MainWindow : public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif
