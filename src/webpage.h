#ifndef PREVIEW_HEADER
#define PREVIEW_HEADER


#include <QObject>
#include <QShortcut>
#include <QWebEnginePage>


class WebPage : public QWebEnginePage {
    Q_OBJECT

public:
    WebPage(QObject *parent = nullptr) : QWebEnginePage(parent) {}

    bool acceptNavigationRequest(
        const QUrl &url,
        QWebEnginePage::NavigationType type,
        bool isMainFrame
    );
public slots:

    void scrollUp();
    void scrollDown();
    void scrollLeft();
    void scrollRight();
    void scrollTop();
    void scrollBottom();

    void resetZoom();

private:
    void _scrollBy(int h, int v);
};


#endif
