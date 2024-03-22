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

    // Créer un objet QUrlQuery pour ajouter le paramètre de requête
    QUrlQuery query;
    query.addQueryItem("badge_utilisateur", "ABCDEZ");

    // Ajouter le paramètre de requête à l'URL
    url.setQuery(query);

    QNetworkRequest request(url);

    // Utilisez la méthode GET pour récupérer les informations
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
