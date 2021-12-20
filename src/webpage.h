#ifndef PREVIEW_HEADER
#define PREVIEW_HEADER

#include <QObject>
#include <QShortcut>
#include <QWebEnginePage>

class WebPage : public QWebEnginePage {
  Q_OBJECT

public:
  WebPage(QObject *parent = nullptr) : QWebEnginePage(parent) {}

  bool acceptNavigationRequest(const QUrl &url,
                               QWebEnginePage::NavigationType type,
                               bool isMainFrame);
  void scrollUp();
  void scrollDown();
  void scrollLeft();
  void scrollRight();
  void scrollTop();
  void scrollBottom();

  void resetZoom();
};

#endif