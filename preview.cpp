#include "preview.h"

#include <QDesktopServices>
#include <QString>
#include <QWebEnginePage>

bool Preview::acceptNavigationRequest(const QUrl &url,
                                      QWebEnginePage::NavigationType type,
                                      bool isMainFrame) {
  if (type == QWebEnginePage::NavigationTypeLinkClicked) {
    QDesktopServices::openUrl(url);
    return false;
  }
  return true;
}

void Preview::scrollDown() {
  QString scrollDown("window.scrollBy(0, 50)");
  runJavaScript(scrollDown);
}

void Preview::scrollUp() {
  QString scrollUp("window.scrollBy(0, -50)");
  runJavaScript(scrollUp);
}

void Preview::scrollLeft() {
  QString scrollUp("window.scrollBy(-50, 0)");
  runJavaScript(scrollUp);
}

void Preview::scrollRight() {
  QString scrollUp("window.scrollBy(50, 0)");
  runJavaScript(scrollUp);
}

void Preview::resetZoom() { setZoomFactor(1.0); }
