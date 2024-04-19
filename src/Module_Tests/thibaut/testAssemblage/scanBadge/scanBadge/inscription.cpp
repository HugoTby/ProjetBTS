#include "inscription.h"

QStringList inscription::formUser()
{
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
    QString quota = QString::number(quota_str);

    QStringList tab;
    tab << prenom << nom << classe << tel << mail << password << infos << quota;
    return tab;
}
