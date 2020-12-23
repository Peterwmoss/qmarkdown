#ifndef MAINWINDOW_HEADER
#define MAINWINDOW_HEADER

#include "document.h"
#include "preview.h"

#include <QFile>
#include <QMainWindow>
#include <QShortcut>
#include <QString>
#include <QTimer>

#define NUM_SHORTCUTS 12

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;

} // namespace Ui
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QString *colorscheme, QString *file,
                      QWidget *parent = nullptr);
  ~MainWindow();

  bool setFile(QString path);

private slots:
  void resetZoom();
  void scrollUp();
  void scrollDown();
  void scrollLeft();
  void scrollRight();
  void scrollTop();
  void scrollBottom();

  void openFileInput();
  void closeFileInput();

  void openFile();
  void autoComplete();

private:
  // Shortcuts
  QShortcut *m_shortcuts[NUM_SHORTCUTS];
  void setupShortcuts();

  // UI
  Ui::MainWindow *m_ui;

  // Backend
  Preview *m_page;
  Document m_content;
  QString m_current_text;
  QString m_current_path;
  QWebChannel *m_channel;
  QTimer *m_reload;
  QFile *m_file;
  void loadImages();
  void loadFile();
  void reloadFile();
};

#endif
