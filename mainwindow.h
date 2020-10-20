#ifndef MAINWINDOW_HEADER
#define MAINWINDOW_HEADER

#include "document.h"
#include "preview.h"
#include <QFile>
#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QFile *file, QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  QString m_filePath;
  Document m_content;
  void setupShortcuts(Preview *page);
  void loadFile(QFile *file);
};

#endif
