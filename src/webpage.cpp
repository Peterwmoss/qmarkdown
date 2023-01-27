#include "webpage.h"

#include <QDesktopServices>


bool WebPage::acceptNavigationRequest(const QUrl &url, QWebEnginePage::NavigationType type, bool) {
    if (type != QWebEnginePage::NavigationTypeLinkClicked)
        return true;
    QDesktopServices::openUrl(url);
    return false;
}

void WebPage::scrollDown() {
    _scrollBy(0, 50);
}

void WebPage::scrollUp() {
    _scrollBy(0, -50);
}

void WebPage::scrollLeft() {
    _scrollBy(-50, 0);
}

void WebPage::scrollRight() {
    _scrollBy(50, 0);
}

void WebPage::scrollTop() {
    runJavaScript(QStringLiteral("window.scrollTo(0,0)"));
}

void WebPage::scrollBottom() {
    runJavaScript(QStringLiteral("window.scrollTo(0,document.body.scrollHeight)"));
}

void WebPage::resetZoom() {
    setZoomFactor(1.0);
}

void WebPage::_scrollBy(int h, int v) {
    runJavaScript(QStringLiteral("window.scrollBy(%1,%2)").arg(h).arg(v));
}
