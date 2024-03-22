-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Hôte : localhost
-- Généré le : ven. 15 mars 2024 à 16:27
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
-- Base de données : `projet_bts`
--

-- --------------------------------------------------------

--
-- Structure de la table `box`
--

CREATE TABLE `box` (
  `id_box` int(10) NOT NULL,
  `id_statut_box` tinyint(1) DEFAULT NULL,
  `id_utilisateur_box` int(10) DEFAULT NULL,
  `temps_edf_box` int(50) NOT NULL,
  `temps_vert_box` int(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Déchargement des données de la table `box`
--

INSERT INTO `box` (`id_box`, `id_statut_box`, `id_utilisateur_box`, `temps_edf_box`, `temps_vert_box`) VALUES
(1, 0, NULL, 0, 0),
(2, 0, NULL, 0, 0),
(3, 0, NULL, 0, 0),
(4, 1, 1, 2, 4),
(5, 0, NULL, 0, 0),
(6, 0, NULL, 0, 0),
(7, 1, 2, 3, 1),
(8, 0, NULL, 0, 0);

-- --------------------------------------------------------

--
-- Structure de la table `occupation`
--

CREATE TABLE `occupation` (
  `id_occupation` int(11) NOT NULL,
  `id_utilisateur_occupation` int(11) NOT NULL,
  `id_box_occupation` int(11) NOT NULL,
  `heure_depot_occupation` datetime NOT NULL,
  `heure_retrait_occupation` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Déchargement des données de la table `occupation`
--

INSERT INTO `occupation` (`id_occupation`, `id_utilisateur_occupation`, `id_box_occupation`, `heure_depot_occupation`, `heure_retrait_occupation`) VALUES
(21, 90, 1, '2024-03-15 08:00:00', '2024-03-15 10:00:00'),
(22, 91, 2, '2024-03-15 09:30:00', '2024-03-15 11:45:00'),
(23, 92, 3, '2024-03-15 10:45:00', '2024-03-15 13:15:00'),
(24, 93, 4, '2024-03-15 12:15:00', '2024-03-15 14:30:00'),
(25, 94, 5, '2024-03-15 13:45:00', '2024-03-15 16:00:00'),
(26, 95, 6, '2024-03-15 15:00:00', '2024-03-15 17:30:00'),
(27, 96, 7, '2024-03-15 16:30:00', '2024-03-15 19:00:00'),
(28, 97, 8, '2024-03-15 18:00:00', '2024-03-15 20:15:00'),
(29, 98, 1, '2024-03-15 19:45:00', '2024-03-15 22:00:00'),
(30, 99, 2, '2024-03-15 21:00:00', '2024-03-15 23:30:00');

-- --------------------------------------------------------

--
-- Structure de la table `utilisateur`
--

CREATE TABLE `utilisateur` (
  `id_utilisateur` int(11) NOT NULL COMMENT 'Auto-increment / AI',
  `isadmin_utilisateur` tinyint(1) DEFAULT 0 COMMENT 'default = 0/false',
  `nom_utilisateur` varchar(50) NOT NULL COMMENT 'required from an external source or by the owner',
  `prenom_utilisateur` varchar(50) NOT NULL COMMENT 'required from an external source or by the owner',
  `classe_utilisateur` varchar(20) NOT NULL COMMENT 'required from an external source or by the owner',
  `badge_utilisateur` varchar(20) NOT NULL COMMENT 'required from an external source or by the owner',
  `photo_utilisateur` varchar(5000) DEFAULT NULL COMMENT 'default = null',
  `password_utilisateur` varchar(200) NOT NULL COMMENT 'required from an external source',
  `telephone_utilisateur` varchar(10) DEFAULT NULL COMMENT 'default = null\r\nand default call sign is +33(0) [FRA]',
  `mail_utilisateur` varchar(100) DEFAULT NULL COMMENT 'default = null',
  `infos_utilisateur` varchar(2000) DEFAULT NULL COMMENT 'default = null',
  `quota_utilisateur` float DEFAULT NULL COMMENT 'default = null'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Déchargement des données de la table `utilisateur`
--

INSERT INTO `utilisateur` (`id_utilisateur`, `isadmin_utilisateur`, `nom_utilisateur`, `prenom_utilisateur`, `classe_utilisateur`, `badge_utilisateur`, `photo_utilisateur`, `password_utilisateur`, `telephone_utilisateur`, `mail_utilisateur`, `infos_utilisateur`, `quota_utilisateur`) VALUES
(88, 0, 'Dupont', 'Jean', 'ciel1', 'ABCDEZ', 'lien_vers_photo1.jpg', 'Motdepasse1!', '0612345678', 'jean.dupont@example.com', NULL, 12.34),
(89, 0, 'Martin', 'Marie', 'sn2', 'FGHIJK', 'lien_vers_photo2.jpg', 'Motdepasse2!', '0678901234', 'marie.martin@example.com', NULL, 15.67),
(90, 0, 'Dubois', 'Pierre', 'elec1', 'LMNOPQ', 'lien_vers_photo3.jpg', 'Motdepasse3!', '0612345679', 'pierre.dubois@example.com', NULL, 8.9),
(91, 0, 'Bernard', 'Sophie', 'ciel1', 'RSTUVW', 'lien_vers_photo4.jpg', 'Motdepasse4!', '0678901235', 'sophie.bernard@example.com', NULL, 16.23),
(92, 0, 'Lefebvre', 'Thomas', 'sn2', 'XYZABC', 'lien_vers_photo5.jpg', 'Motdepasse5!', '0678901236', 'thomas.lefebvre@example.com', NULL, 3.45),
(93, 0, 'Moreau', 'Camille', 'elec1', 'DEFGHI', 'lien_vers_photo6.jpg', 'Motdepasse6!', '0612345670', 'camille.moreau@example.com', NULL, 11.78),
(94, 0, 'Roux', 'Julie', 'ciel1', 'JKLMNOP', 'lien_vers_photo7.jpg', 'Motdepasse7!', '0678901231', 'julie.roux@example.com', NULL, 7.89),
(95, 0, 'Leroy', 'Lucas', 'sn2', 'QRSTUV', 'lien_vers_photo8.jpg', 'Motdepasse8!', '0612345671', 'lucas.leroy@example.com', NULL, 18.9),
(96, 0, 'Fournier', 'Emma', 'elec1', 'WXYZAB', 'lien_vers_photo9.jpg', 'Motdepasse9!', '0678901232', 'emma.fournier@example.com', NULL, 2.34),
(97, 0, 'Garcia', 'Hugo', 'ciel1', 'CDEFGH', 'lien_vers_photo10.jpg', 'Motdepasse10!', '0612345672', 'hugo.garcia@example.com', NULL, 10.11),
(98, 0, 'Hubert', 'Léa', 'sn2', 'IJKLMN', 'lien_vers_photo11.jpg', 'Motdepasse11!', '0678901233', 'lea.hubert@example.com', NULL, 5.67),
(99, 0, 'Robin', 'Louis', 'elec1', 'OPQRST', 'lien_vers_photo12.jpg', 'Motdepasse12!', '0612345673', 'louis.robin@example.com', NULL, 14.45),
(100, 0, 'Chevalier', 'Chloé', 'ciel1', 'UVWXYZ', 'lien_vers_photo13.jpg', 'Motdepasse13!', '0678901237', 'chloe.chevalier@example.com', NULL, 6.78),
(101, 0, 'Girard', 'Adam', 'sn2', 'ABCDEF', 'lien_vers_photo14.jpg', 'Motdepasse14!', '0612345674', 'adam.girard@example.com', NULL, 19.01),
(102, 0, 'Sanchez', 'Manon', 'elec1', 'GHIJKL', 'lien_vers_photo15.jpg', 'Motdepasse15!', '0678901238', 'manon.sanchez@example.com', NULL, 3.21),
(103, 0, 'Caron', 'Inès', 'ciel1', 'MNOPQR', 'lien_vers_photo16.jpg', 'Motdepasse16!', '0612345675', 'ines.caron@example.com', NULL, 13.45),
(104, 0, 'Renaud', 'Noah', 'sn2', 'STUVWX', 'lien_vers_photo17.jpg', 'Motdepasse17!', '0678901239', 'noah.renaud@example.com', NULL, 17.89),
(105, 0, 'Guerin', 'Léa', 'elec1', 'YZABCD', 'lien_vers_photo18.jpg', 'Motdepasse18!', '0612345676', 'lea.guerin@example.com', NULL, 1.23),
(106, 0, 'Meyer', 'Mathis', 'ciel1', 'EFGHIJ', 'lien_vers_photo19.jpg', 'Motdepasse19!', '0678901240', 'mathis.meyer@example.com', NULL, 11.22),
(107, 0, 'Marchand', 'Clara', 'sn2', 'KLMNOP', 'lien_vers_photo20.jpg', 'Motdepasse20!', '0612345677', 'clara.marchand@example.com', NULL, 9.87);

--
-- Index pour les tables déchargées
--

--
-- Index pour la table `box`
--
ALTER TABLE `box`
  ADD PRIMARY KEY (`id_box`),
  ADD UNIQUE KEY `id_utilisateur_box_2` (`id_utilisateur_box`),
  ADD KEY `id_utilisateur_box` (`id_utilisateur_box`);

--
-- Index pour la table `occupation`
--
ALTER TABLE `occupation`
  ADD PRIMARY KEY (`id_occupation`),
  ADD KEY `id_utilisateur_occupation` (`id_utilisateur_occupation`,`id_box_occupation`),
  ADD KEY `id_box_occupation` (`id_box_occupation`);

--
-- Index pour la table `utilisateur`
--
ALTER TABLE `utilisateur`
  ADD PRIMARY KEY (`id_utilisateur`),
  ADD UNIQUE KEY `telephone_utilisateur` (`telephone_utilisateur`),
  ADD UNIQUE KEY `mail_utilisateur` (`mail_utilisateur`);

--
-- AUTO_INCREMENT pour les tables déchargées
--

--
-- AUTO_INCREMENT pour la table `box`
--
ALTER TABLE `box`
  MODIFY `id_box` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;

--
-- AUTO_INCREMENT pour la table `occupation`
--
ALTER TABLE `occupation`
  MODIFY `id_occupation` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=31;

--
-- AUTO_INCREMENT pour la table `utilisateur`
--
ALTER TABLE `utilisateur`
  MODIFY `id_utilisateur` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Auto-increment / AI', AUTO_INCREMENT=108;

--
-- Contraintes pour les tables déchargées
--

--
-- Contraintes pour la table `occupation`
--
ALTER TABLE `occupation`
  ADD CONSTRAINT `occupation_ibfk_1` FOREIGN KEY (`id_utilisateur_occupation`) REFERENCES `utilisateur` (`id_utilisateur`),
  ADD CONSTRAINT `occupation_ibfk_2` FOREIGN KEY (`id_box_occupation`) REFERENCES `box` (`id_box`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
