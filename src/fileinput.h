#ifndef FILEINPUT_HEADER
#define FILEINPUT_HEADER


#include <QLineEdit>


class FileInput : public QLineEdit {
    Q_OBJECT
public:
    FileInput(QWidget *parent = nullptr);
public slots:
    void autoComplete();
};


#endif
