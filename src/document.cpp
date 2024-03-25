#include "document.h"

#include <QByteArray>
#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <QBuffer>
#include <qdir.h>

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

QString Document::imageToBase64(const QString &imagePath) {
    QFileInfo f(imagePath);
    QString absolutePath = f.absoluteFilePath();

    QFile imageFile(absolutePath);
    QFileInfo fileInfo(absolutePath);

    // Check if the file path is valid
    if (!fileInfo.exists()) {
        qDebug() << "File does not exist:" << absolutePath;
        return QString();
    }

    // Check if the file is readable
    if (!fileInfo.isReadable()) {
        qDebug() << "File is not readable:" << absolutePath;
        return QString();
    }

    if (!imageFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file:" << absolutePath;
        return QString();
    }

    QByteArray imageByteArray = imageFile.readAll();
    QByteArray base64Image = imageByteArray.toBase64();

    QString contentType = "image/png"; // Default content type
    if (imagePath.endsWith(".jpg") || imagePath.endsWith(".jpeg")) {
        contentType = "image/jpeg";
    } else if (imagePath.endsWith(".gif")) {
        contentType = "image/gif";
    } else if (imagePath.endsWith(".svg")) {
        contentType = "image/svg+xml";
    }

    QString base64Url = QString("data:%1;base64,%2").arg(contentType, QString(base64Image));
    return base64Url;
}
