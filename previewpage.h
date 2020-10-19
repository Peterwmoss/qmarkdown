#ifndef PREVIEWPAGE_HEADER
#define PREVIEWPAGE_HEADER

#include <QWebEnginePage>

class PreviewPage : public QWebEnginePage {
public:
  explicit PreviewPage(QObject *parent = nullptr) : QWebEnginePage(parent) {}
};

#endif
