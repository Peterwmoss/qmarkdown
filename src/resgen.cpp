#include "resgen.h"

#include <QDirIterator>
#include <QTextStream>


void generateResources() {
    QFile image_file(QStringLiteral("images.qrc"));

    if (!image_file.open(QIODevice::WriteOnly))
        return; // TODO: Error return

    QTextStream stream(&image_file);

    stream << "<!DOCTYPE RCC><RCC version='1.0'>\n<qresource>\n";

    auto count = 0u;

    for (
         QDirIterator iterator(
             QStringLiteral("."),
             {
                 QStringLiteral("*.png"),
                 QStringLiteral("*.jpg"),
                 QStringLiteral("*.jpeg"),
                 QStringLiteral("*.gif")
             },
             QDir::NoDotAndDotDot,
             QDirIterator::Subdirectories
         );
         iterator.hasNext();
         ++count
    )
        stream << "<file>" << iterator.next() << "</file>\n";

    stream << "</qresource>\n</RCC>\n";

    image_file.close();

    // Clean up
    if (count)
        system((QStringLiteral("rcc -binary images.qrc -o ") + QRC_FILE).toLocal8Bit());
    image_file.remove();
}
