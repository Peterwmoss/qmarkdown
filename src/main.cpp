#include "mainwindow.h"

#include <QApplication>
#include <QFileInfo>


bool parseFile(const char *arg, QString &file) {
    file = arg;
    return QFileInfo(file).isFile();
}

bool parseColor(QString &index_file, const QString &color_scheme) {
    if (color_scheme == QStringLiteral("l") || color_scheme == QStringLiteral("light")) {
        index_file = QStringLiteral(":/index-light.html");
        return true;
    }
    if (color_scheme == QStringLiteral("d") || color_scheme == QStringLiteral("dark")) {
        index_file = QStringLiteral(":/index-dark.html");
        return true;
    }
    return false;
}

bool parseArguments(
    QString &index_file,
    QString &file,
    const char *color_argument,
    const char *file_argument
) {
    if (color_argument[0] != '-')
        return false;
    return parseColor(index_file, color_argument + 1 + (color_argument[1] == '-'))
        && parseFile(file_argument, file);
}

enum LoadArgsResult {
    OK,
    NOT_FOUND,
    CANNOT_PARSE_ARGS,
    INVALID_ARGS
};

LoadArgsResult loadArgs(int argc, char *argv[], QString &file, QString &index_file) {
    if (argc == 2 && argv[1][0] != '-') { // Only file as argument
        index_file = QStringLiteral(":/index-light.html");
        return parseFile(argv[1], file) ? OK : NOT_FOUND;
    } else if (argc == 3) // File and colorscheme
        return (
            parseArguments(index_file, file, argv[1], argv[2])
            ||
            parseArguments(index_file, file, argv[2], argv[1])
        ) ? OK : CANNOT_PARSE_ARGS;
    return INVALID_ARGS;
}

int main(int argc, char *argv[]) {
    QCoreApplication::setOrganizationName(QStringLiteral("qMarkdown"));
    QApplication app(argc, argv);

    QString file, index_file;
    auto result = loadArgs(argc, argv, file, index_file);
    if (result) {
        // Die
        const char *messages[] = {
            "Error: File not found",
            "Error: Could not parse arguments",
            "Error: Please pass valid arguments"
        };
        puts(messages[result - 1]);
        puts("Usage: Usage `qmarkdown [colorscheme] <file>.md`\n");
        exit(1);
    }

    MainWindow window(index_file, file);
    window.show();

    return app.exec();
}
