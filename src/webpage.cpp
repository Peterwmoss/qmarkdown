#include "webpage.h"

#include <QDesktopServices>
#include <QString>
#include <QWebEnginePage>

bool WebPage::acceptNavigationRequest(const QUrl &url,
                                      QWebEnginePage::NavigationType type,
                                      bool isMainFrame) {
  if (type == QWebEnginePage::NavigationTypeLinkClicked) {
    QDesktopServices::openUrl(url);
    return false;
  }
  return true;
}

void WebPage::scrollDown() {
  QString scrollDown("window.scrollBy(0, 50)");
  runJavaScript(scrollDown);
}

void WebPage::scrollUp() {
  QString scrollUp("window.scrollBy(0, -50)");
  runJavaScript(scrollUp);
}

void WebPage::scrollLeft() {
  QString scrollUp("window.scrollBy(-50, 0)");
  runJavaScript(scrollUp);
}

void WebPage::scrollRight() {
  QString scrollUp("window.scrollBy(50, 0)");
  runJavaScript(scrollUp);
}

void WebPage::scrollTop() {
  QString scrollUp("window.scrollTo(0,0)");
  runJavaScript(scrollUp);
}

void WebPage::scrollBottom() {
  QString scrollUp("window.scrollTo(0,document.body.scrollHeight)");
  runJavaScript(scrollUp);
}

void WebPage::resetZoom() { setZoomFactor(1.0); }
