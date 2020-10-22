#ifndef MAINWINDOW_HEADER
#define MAINWINDOW_HEADER

#include "document.h"
#include "preview.h"
#include <QFile>
#include <QMainWindow>
#include <QShortcut>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QString *file, QWidget *parent = nullptr);
  ~MainWindow();

  bool setFile(QString path);

private:
  // Shortcuts
  QShortcut *q, *o, *h, *j, *k, *l, *zero, *esc, *ret;
  void setupShortcuts(Preview *page);

  // UI
  Ui::MainWindow *ui;
  Preview *page;

  // Backend
  Document m_content;
  QWebChannel *channel;
  QFile *m_file;
  void loadFile();
};

#endif
