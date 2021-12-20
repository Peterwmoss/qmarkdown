#ifndef MAINWINDOW_HEADER
#define MAINWINDOW_HEADER

#include "document.h"
#include "webpage.h"

#include <QFile>
#include <QMainWindow>
#include <QShortcut>
#include <QString>
#include <QTimer>

#define NUM_SHORTCUTS 13 

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

  void nextAutocomplete();
  void prevAutocomplete();

private:
  // Shortcuts
  QShortcut *m_shortcuts[NUM_SHORTCUTS];
  void setupShortcuts();

  // UI
  Ui::MainWindow *m_ui;

  // Backend
  WebPage *m_page;
  Document m_content;
  QString m_current_text;
  QString m_current_path;
  QWebChannel *m_channel;
  QTimer *m_reload;
  QFile *m_file;
  void load_images();
  void load_file();
  void load_html(QString index_file);
  void reload_file();
};

#endif
