#ifndef DOCUMENT_HEADER
#define DOCUMENT_HEADER

#include <QObject>
#include <QString>

class Document : QObject {
public:
  explicit Document() : QObject() {}

  void setText(const QString &text);

private:
  QString m_text;
};

#endif
