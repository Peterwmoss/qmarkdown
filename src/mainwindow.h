#ifndef MAINWINDOW_HEADER
#define MAINWINDOW_HEADER

#include "document.h"
#include "preview.h"

#include <QFile>
#include <QMainWindow>
#include <QShortcut>
#include <QString>
#include <QTimer>
#include <string>

#define NUM_SHORTCUTS 12

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;

} // namespace Ui
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(std::string path, QString *file,
                      QWidget *parent = nullptr);
  ~MainWindow();

  bool setFile(QString path);

private:
  // Shortcuts
  QShortcut *shortcuts[NUM_SHORTCUTS];
  void setupShortcuts();

  // UI
  Ui::MainWindow *ui;
  Preview *page;

  // Backend
  Document m_content;
  QString current_text;
  std::string current_path;
  QWebChannel *channel;
  QTimer *reload;
  QFile *m_file;
  void loadImages();
  void loadFile();
  void reloadFile();
};

#endif
