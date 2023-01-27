#include "document.h"


Document::Document(QObject *parent) : QObject(parent) {}

void Document::setText(const QString &text) {
    if (text != _text) {
        _text = text;
        emit textChanged(_text);
    }
}

QString Document::text() const {
    return _text;
}
