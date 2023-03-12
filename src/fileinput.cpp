#include "fileinput.h"

#include <QDir>


FileInput::FileInput(QWidget *parent) : QLineEdit(parent) {}

void FileInput::autoComplete() {
    QFileInfoList directories, md_files;
    auto path = text().trimmed();
    if (path.endsWith(QLatin1Char('/'))) {
        QDir directory(path);
        directories = directory.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs);
        md_files = directory.entryInfoList({QStringLiteral("*.md")}, QDir::Files);
    } else {
        QFileInfo file_info(path);
        QString wildcard = file_info.fileName() + QLatin1Char('*');
        QDir directory(file_info.dir());
        directories = directory.entryInfoList({wildcard}, QDir::NoDotAndDotDot | QDir::Dirs);
        md_files = directory.entryInfoList({wildcard + QStringLiteral(".md")}, QDir::Files);
    }
    switch (directories.size()) {
    case 0:
        if (md_files.size() == 1)
            setText(md_files[0].filePath());
        break;
    case 1:
        if (md_files.size() == 0)
            setText(directories[0].filePath() + QLatin1Char('/'));
    }
}
