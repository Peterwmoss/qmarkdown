#include "mainwindow.h"
#include "document.h"
#include "webpage.h"
#include "resgen.h"

#include <QDir>
#include <QResource>
#include <QTextStream>
#include <QWebEnginePage>


MainWindow::MainWindow(const QString &index_file, const QString &file, QWidget *parent) :
    QMainWindow(parent),
    _file_input(this),
    _web_view(this),
    _status_bar(this),
    _channel(this),
    _page(this),
    _file_info(file),
    _watcher(this),
    _shortcuts{
        // Vim keys to move
        QShortcut(Qt::Key_K, this, &_page, &WebPage::scrollUp),
        QShortcut(Qt::Key_J, this, &_page, &WebPage::scrollDown),
        QShortcut(Qt::Key_H, this, &_page, &WebPage::scrollLeft),
        QShortcut(Qt::Key_L, this, &_page, &WebPage::scrollRight),
        QShortcut(Qt::Key_G, this, &_page, &WebPage::scrollTop),
        QShortcut(Qt::Modifier::SHIFT | Qt::Key_G, this, &_page, &WebPage::scrollBottom),
        // 0 to reset zoom
        QShortcut(Qt::Key_0, this, &_page, &WebPage::resetZoom),

        QShortcut(Qt::Key_O, this, this, &MainWindow::openFileInput),
        QShortcut(Qt::Key_Escape, this, this, &MainWindow::closeFileInput),

        QShortcut(Qt::Key_Tab, &_file_input, &_file_input, &FileInput::autoComplete),
        QShortcut(Qt::Key_Return, &_file_input, this, &MainWindow::openFile),
        // Q to close
        QShortcut(Qt::Key_Q, this, this, &MainWindow::close)
    }
{
    if (objectName().isEmpty())
        setObjectName(QStringLiteral("MainWindow"));
    setWindowTitle(QStringLiteral("qMarkdown"));
    resize(800, 600);

    _file_input.setObjectName(QStringLiteral("fileInput"));
    _file_input.setPlaceholderText(QStringLiteral("File"));
    setMenuWidget(&_file_input);
    _file_input.hide();

    _channel.registerObject(QStringLiteral("content"), &_content);
    _page.setWebChannel(&_channel);
    _web_view.setPage(&_page);
    _web_view.setContextMenuPolicy(Qt::NoContextMenu);
    setCentralWidget(&_web_view);

    setStatusBar(&_status_bar);
    _status_bar.hide();

    loadHtml(index_file);
    loadFile(_file_info.filePath());

    connect(&_watcher, &QFileSystemWatcher::fileChanged, this, &MainWindow::reloadFile);
}

void MainWindow::notify(const QString &message, int timeout) {
    _status_bar.show();
    _status_bar.showMessage(message, timeout);
}

bool MainWindow::loadFile(const QString &file_path) {
    QFileInfo file_info(file_path);
    file_info.makeAbsolute();
    if (file_info.isFile()) {
        QFile file(file_info.filePath());
        if (file.open(QIODevice::ReadOnly)) {
            QTextStream stream(&file);
            auto content = stream.readAll();
            file.close();
            if (loadImages(file_info.path())) {
                _content.setText(content);
                _watcher.removePath(_file_info.filePath()); // Stop monitoring current file
                _file_info = file_info;
                _watcher.addPath(_file_info.filePath()); // Start monitoring new file
                QDir::setCurrent(_file_info.path());
                return true;
            }
        }
    }
    return false;
}

bool MainWindow::reloadFile() {
    if (_current_text != _content.text()) {
        _current_text = _content.text();
        loadImages(_file_info.path());
    }
    if (_file_info.isFile()) {
        QFile file(_file_info.filePath());
        if (file.open(QIODevice::ReadOnly)) {
            QTextStream stream(&file);
            _content.setText(stream.readAll());
            file.close();
            return true;
        }
    }
    notify(QStringLiteral("File is deleted or not available: '%1'").arg(_file_info.filePath()));
    return false;
}

bool MainWindow::loadHtml(const QString &index_file) {
    QFile file(index_file);
    if (!file.open(QIODevice::ReadOnly))
        return false;
    QTextStream stream(&file);
    _web_view.setHtml(stream.readAll(), QUrl("qrc:/"));
    file.close();
    return true;
}

bool MainWindow::loadImages(const QString &directory_path) {
    generateResources();

    QString qpath = directory_path + QLatin1Char('/') + QRC_FILE;

    if (QFileInfo::exists(qpath)) {
        QResource::registerResource(qpath);
        QFile::remove(QRC_FILE);
        /*system(("rm -f " + QRC_FILE).c_str());*/
    }
    return true;
}

bool MainWindow::setFile(const QString &file_path) {
    if (loadFile(file_path))
        return true;
    notify(QStringLiteral("File not found: '%1'").arg(file_path));
    return false;
}

void MainWindow::fileEnter() {
    _web_view.setFocus();
    _file_input.hide();
    _file_input.clear();
}

void MainWindow::openFileInput() {
    _file_input.show();
    _file_input.setFocus();
}

void MainWindow::closeFileInput() {
    if (_status_bar.isVisible())
        _status_bar.hide();
    else if (_file_input.isVisible())
        fileEnter();
}

void MainWindow::openFile() {
    if (setFile(_file_input.text()))
        fileEnter();
}

MainWindow::~MainWindow() {
    // Cleanup
    QFile::remove(QRC_FILE);
    /*system(("rm -f " + QRC_FILE).c_str());*/
}
