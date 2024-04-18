#pragma once
#include <QString>
#include <QObject>
#include <QMap>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariant>
#include <qdebug.h>
#include <iostream>

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
	utilisateur(){}
	utilisateur(const utilisateur& other)
	{
		id = other.id;
		isadmin = other.isadmin;
		nom = other.nom;
		prenom = other.prenom;
		classe = other.classe;
		badge = other.badge;
		photo = other.photo;
		password = other.password;
		telephone = other.telephone;
		mail = other.mail;
		infos = other.infos;
		quota = other.quota;
	}

	void formUser() {
		// Si aucun utilisateur n'est trouvé, demander les informations manquantes à l'utilisateur
		std::string prenom_str, nom_str, classe_str, tel_str, mail_str, infos_str, password_str;
		float quota_str;
		std::cout << "Saisir prenom : ";
		std::cin >> prenom_str;
		std::cout << "Saisir nom : ";
		std::cin >> nom_str;
		std::cout << "Saisir classe : ";
		std::cin >> classe_str;
		std::cout << "Saisir tel : ";
		std::cin >> tel_str;
		std::cout << "Saisir mail : ";
		std::cin >> mail_str;
		std::cout << "Saisir password : ";
		std::cin >> password_str;
		std::cout << "Saisir infos : ";
		std::getline(std::cin.ignore(), infos_str);
		std::cout << "Saisir quota : ";
		std::cin >> quota_str;

		QString prenom = QString::fromStdString(prenom_str);
		QString nom = QString::fromStdString(nom_str);
		QString classe = QString::fromStdString(classe_str);
		QString tel = QString::fromStdString(tel_str);
		QString mail = QString::fromStdString(mail_str);
		QString password = QString::fromStdString(password_str);
		QString infos = QString::fromStdString(infos_str);
		//QString quota = QString::fromStdString(quota_str);
	}

	QList<utilisateur> utilisateur::toUncypherJSON(const QByteArray& jsonData);
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
	QString getPrenom() {
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
	QString setPhone(QString phone) {
		this->telephone = phone;
	}
	QString getPhone() {
		return this->telephone;
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

	friend QDebug operator<<(QDebug debug, const utilisateur& user);
};

QDebug operator<<(QDebug debug, const utilisateur& user);
