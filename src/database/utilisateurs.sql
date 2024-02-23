-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Hôte : localhost
-- Généré le : ven. 23 fév. 2024 à 14:08
-- Version du serveur : 10.5.21-MariaDB-0+deb11u1
-- Version de PHP : 7.4.33

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données : `RFID`
--

-- --------------------------------------------------------

--
-- Structure de la table `utilisateurs`
--

CREATE TABLE `utilisateurs` (
  `id` int(11) NOT NULL,
  `uid` varchar(20) NOT NULL,
  `prenom` varchar(200) NOT NULL,
  `nom` varchar(200) NOT NULL,
  `classe` varchar(20) NOT NULL,
  `administrateur` varchar(5) NOT NULL,
  `photo` varchar(3000) NOT NULL,
  `regime` varchar(10) NOT NULL,
  `naissance` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Déchargement des données de la table `utilisateurs`
--

INSERT INTO `utilisateurs` (`id`, `uid`, `prenom`, `nom`, `classe`, `administrateur`, `photo`, `regime`, `naissance`) VALUES
(1, '3EDD8299', 'Thibaut', 'Tiennot', 'BTSSN2', 'oui', '3EDD8299', 'EXT', '03/10/2003'),
(2, 'BE544299', 'Hugo', 'Tabary', 'BTSSN2', 'oui', 'BE544299', 'DEP4', '28/03/2005'),
(3, 'E425799', 'Faustin', 'Botel', 'BTSSN2', 'non', 'E425799', 'EXT', '17/05/2003'),
(4, '8E457F99', 'Edouard', 'Hautemanière', 'BTSSN2', 'oui', '8E457F99', 'DEP5', '09/01/2003'),
(5, 'DE807B99', 'Mathias', 'Senepart', 'BTSSN2', 'non', 'DE807B99', 'DEP5', '28/04/2003'),
(6, '2E3B6799', 'Quentin', 'Pollet', 'BTSSN2', 'non', '2E3B6799', 'EXT', '15/10/2004'),
(11, ':uid', ' :prenom', ' :nom', ' :classe', ' :oui', ' :photo', ' :regime', ' :naissance');

--
-- Index pour les tables déchargées
--

--
-- Index pour la table `utilisateurs`
--
ALTER TABLE `utilisateurs`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT pour les tables déchargées
--

--
-- AUTO_INCREMENT pour la table `utilisateurs`
--
ALTER TABLE `utilisateurs`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
