#pragma once
#include <QString>
#include <QObject>
#include <QMap>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
class utilisateur : public QObject
{
	Q_OBJECT
private:
	int id;
	bool isadmin;
	QString nom;
	QString prenom;
	QString classe;
	QString badge;
	QString photo;
	QString password;
	QString telephone;
	QString mail;
	QString infos = NULL;
	float quota;
private slots:

signals:

public:
	static QMap<QString, QVariant> toUncypherJSON(const QByteArray& jsonData);
	int setId(int id) {
		this->id = id;
	}
	int getId() {
		return id;
	}
	bool setIsAdmin(bool isadmin) {
		this->isadmin = isadmin;
	}
	bool getIsAdmin() {
		return isadmin;
	}
	QString setNom(QString nom) {
		this->nom = nom;
	}
	QString getNom() {
		return this->nom;
	}
	QString setPrenom(QString prenom) {
		this->prenom = prenom;
	}
	QString getprenom() {
		return this->prenom;
	}
	QString setClasse(QString classe) {
		this->classe = classe;
	}
	QString getClasse() {
		return this->classe;
	}
	QString setBadge(QString badge) {
		this->badge = badge;
	}
	QString getBadge() {
		return this->badge;
	}
	QString setPhoto(QString photo) {
		this->photo = photo;
	}
	QString getPhoto() {
		return this->photo;
	}
	QString setPassword(QString password) {
		this->password = password;
	}
	QString getPassword() {
		return this->password;
	}
	QString setEmail(QString mail) {
		this->mail = mail;
	}
	QString getEmail() {
		return this->mail;
	}
	QString setInfos(QString infos) {
		this->infos = infos;
	}
	QString getInfos() {
		return this->infos;
	}
	float setQuota(float quota) {
		this->quota = quota;
	}
	float getQuota() {
		return this->quota;
	}
};