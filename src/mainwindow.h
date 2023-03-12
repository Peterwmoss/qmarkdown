#ifndef MAINWINDOW_HEADER
#define MAINWINDOW_HEADER

#include "document.h"
#include "fileinput.h"
#include "webpage.h"

#include <QFileInfo>
#include <QFileSystemWatcher>
#include <QMainWindow>
#include <QShortcut>
#include <QStatusBar>
#include <QWebChannel>
#include <QWebEngineView>


const auto SHORTCUT_COUNT = 12u;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(
        const QString &color_scheme,
        const QString &file,
        QWidget *parent = nullptr
    );
    ~MainWindow();

    bool setFile(const QString &file_path);

private:
    // UI
    FileInput _file_input;
    QWebEngineView _web_view;
    QStatusBar _status_bar;
    // Backend
    Document _content;
    QString _current_text;
    QWebChannel _channel;
    WebPage _page;
    QFileInfo _file_info;
    QFileSystemWatcher _watcher;
    // Shortcuts
    QShortcut _shortcuts[SHORTCUT_COUNT];

    void notify(const QString &message, int timeout = 10000);
    bool loadFile(const QString &file_path);
    bool reloadFile();
    bool loadHtml(const QString &index_file);
    bool loadImages(const QString &directory_path);

private slots:
    void fileEnter();
    void openFileInput();
    void closeFileInput();
    void openFile();
};

#endif
