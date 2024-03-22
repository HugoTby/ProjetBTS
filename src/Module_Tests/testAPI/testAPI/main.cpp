#include <QtCore/QCoreApplication>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    QNetworkAccessManager manager;
    //QUrl url("http://192.168.64.148/testAPI/index.php"); test en local
    QUrl url("http://192.168.65.105:5001/utilisateurs");

    QJsonObject jsonObject;
    jsonObject.insert("nom_utilisateur", "tienot");
    jsonObject.insert("prenom_utilisateur", "thibut");
    jsonObject.insert("classe_utilisateur", "SN2");
    jsonObject.insert("badge_utilisateur", "RTU856");
    //jsonObject.insert("photo_utilisateur", "lien_photo.jpg");
    jsonObject.insert("password_utilisateur", "thjkl452");
    jsonObject.insert("telephone_utilisateur", "0621000000");
    jsonObject.insert("mail_utilisateur", "thib.tieot@gmail.com");
    //jsonObject.insert("infos_utilisateur", "In2fos supplémentaires");
    jsonObject.insert("quota_utilisateur", "15");

    QJsonDocument jsonDoc(jsonObject);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QByteArray data = jsonDoc.toJson(QJsonDocument::Compact);

    QNetworkReply* reply = manager.post(request, data);
    //QNetworkReply* reply = manager.get(request);

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
