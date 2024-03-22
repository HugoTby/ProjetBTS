#include <QtCore/QCoreApplication>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    QNetworkAccessManager manager;
    QUrl url("http://192.168.65.105:5001/utilisateurs/badge_utilisateur");

    // Cr�er un objet QUrlQuery pour ajouter le param�tre de requ�te
    QUrlQuery query;
    query.addQueryItem("badge_utilisateur", "ABCDEZ");

    // Ajouter le param�tre de requ�te � l'URL
    url.setQuery(query);

    QNetworkRequest request(url);

    // Utilisez la m�thode GET pour r�cup�rer les informations
    QNetworkReply* reply = manager.get(request);

    QObject::connect(reply, &QNetworkReply::finished, [&]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            qDebug() << "Response:" << responseData;
        }
        else {
            qDebug() << "Error:" << reply->errorString();
        }

        reply->deleteLater();
        a.quit();
        });

    return a.exec();
}
