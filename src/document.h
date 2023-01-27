#ifndef DOCUMENT_HEADER
#define DOCUMENT_HEADER


#include <QObject>


class Document : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString text MEMBER _text NOTIFY textChanged FINAL)
public:
    explicit Document(QObject *parent = nullptr);

    void setText(const QString &text);
    QString text() const;

signals:
    void textChanged(const QString &text);

private:
    QString _text;
};


#endif
