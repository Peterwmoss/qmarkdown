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
  QShortcut *q, *o, *h, *j, *k, *l, *zero, *esc, *ret;
  Ui::MainWindow *ui;
  Document m_content;
  QFile *m_file;
  void setupShortcuts(Preview *page);
  void loadFile();
};

#endif
