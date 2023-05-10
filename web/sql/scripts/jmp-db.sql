-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: mysql
-- Creato il: Mag 10, 2023 alle 09:50
-- Versione del server: 8.0.33
-- Versione PHP: 8.1.17

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `jmp-db`
--

-- --------------------------------------------------------

--
-- Struttura della tabella `allenamento`
--

CREATE TABLE IF NOT EXISTS `allenamento` (
  `IDAllenamento` int NOT NULL AUTO_INCREMENT,
  `IDUtente` int NOT NULL,
  `IDObiettivo` int DEFAULT NULL,
  PRIMARY KEY (`IDAllenamento`),
  KEY `IDUtente` (`IDUtente`),
  KEY `IDObiettivo` (`IDObiettivo`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Struttura della tabella `categoriaObiettivo`
--

CREATE TABLE IF NOT EXISTS `categoriaObiettivo` (
  `IDCategoria` int NOT NULL AUTO_INCREMENT,
  `Descrizione` text NOT NULL,
  PRIMARY KEY (`IDCategoria`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Struttura stand-in per le viste `classificadurata`
-- (Vedi sotto per la vista effettiva)
--
CREATE TABLE IF NOT EXISTS `classificadurata` (
`durataAllenamento` bigint
,`username` varchar(255)
);

-- --------------------------------------------------------

--
-- Struttura stand-in per le viste `classificanumsalti`
-- (Vedi sotto per la vista effettiva)
--
CREATE TABLE IF NOT EXISTS `classificanumsalti` (
`numSalti` decimal(32,0)
,`username` varchar(255)
);

-- --------------------------------------------------------

--
-- Struttura della tabella `dispositivo`
--

CREATE TABLE IF NOT EXISTS `dispositivo` (
  `IDDispositivo` char(17) NOT NULL,
  `IDUtente` int NOT NULL,
  PRIMARY KEY (`IDDispositivo`),
  KEY `IDUtente` (`IDUtente`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='IDDispositivo è il MAC Address';

-- --------------------------------------------------------

--
-- Struttura della tabella `misura`
--

CREATE TABLE IF NOT EXISTS `misura` (
  `IDMisura` int NOT NULL AUTO_INCREMENT,
  `IDAllenamento` int NOT NULL,
  `numeroSalti` int NOT NULL,
  `timestamp` timestamp NOT NULL,
  PRIMARY KEY (`IDMisura`),
  KEY `IDAllenamento` (`IDAllenamento`)
) ;

-- --------------------------------------------------------

--
-- Struttura della tabella `obiettivo`
--

CREATE TABLE IF NOT EXISTS `obiettivo` (
  `IDObiettivo` int NOT NULL AUTO_INCREMENT,
  `IDCategoria` int NOT NULL,
  `parametro` int NOT NULL,
  PRIMARY KEY (`IDObiettivo`),
  KEY `IDCategoria` (`IDCategoria`)
) ;

-- --------------------------------------------------------

--
-- Struttura della tabella `utente`
--

CREATE TABLE IF NOT EXISTS `utente` (
  `IDUtente` int NOT NULL AUTO_INCREMENT,
  `username` varchar(255) NOT NULL,
  `passwordHash` char(60) NOT NULL,
  `peso` int NOT NULL,
  `altezza` int NOT NULL,
  `dataNascita` date NOT NULL,
  `genere` enum('maschio','femmina') NOT NULL,
  `partecipazioneClassifica` tinyint(1) NOT NULL DEFAULT '0',
  `IDObiettivo` int DEFAULT NULL,
  PRIMARY KEY (`IDUtente`),
  UNIQUE KEY `username` (`username`),
  KEY `IDObiettivo` (`IDObiettivo`)
) ;

-- --------------------------------------------------------

--
-- Struttura per vista `classificadurata`
--
DROP TABLE IF EXISTS `classificadurata`;

CREATE ALGORITHM=UNDEFINED DEFINER=`jmp-user`@`%` SQL SECURITY DEFINER VIEW `classificadurata`  AS SELECT `utente`.`username` AS `username`, (unix_timestamp(max(`misura`.`timestamp`)) - unix_timestamp(min(`misura`.`timestamp`))) AS `durataAllenamento` FROM ((`misura` join `allenamento` on((`misura`.`IDAllenamento` = `allenamento`.`IDAllenamento`))) join `utente` on((`allenamento`.`IDUtente` = `utente`.`IDUtente`))) WHERE (`utente`.`partecipazioneClassifica` = 1) GROUP BY `misura`.`IDAllenamento` ORDER BY `durataAllenamento` DESC ;

-- --------------------------------------------------------

--
-- Struttura per vista `classificanumsalti`
--
DROP TABLE IF EXISTS `classificanumsalti`;

CREATE ALGORITHM=UNDEFINED DEFINER=`jmp-user`@`%` SQL SECURITY DEFINER VIEW `classificanumsalti`  AS SELECT `utente`.`username` AS `username`, sum(`misura`.`numeroSalti`) AS `numSalti` FROM ((`misura` join `allenamento` on((`misura`.`IDAllenamento` = `allenamento`.`IDAllenamento`))) join `utente` on((`allenamento`.`IDUtente` = `utente`.`IDUtente`))) WHERE (`utente`.`partecipazioneClassifica` = 1) GROUP BY `allenamento`.`IDAllenamento` ORDER BY `numSalti` DESC ;

--
-- Limiti per le tabelle scaricate
--

--
-- Limiti per la tabella `allenamento`
--
ALTER TABLE `allenamento`
  ADD CONSTRAINT `allenamento_ibfk_1` FOREIGN KEY (`IDUtente`) REFERENCES `utente` (`IDUtente`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `allenamento_ibfk_2` FOREIGN KEY (`IDObiettivo`) REFERENCES `obiettivo` (`IDObiettivo`) ON DELETE SET NULL ON UPDATE CASCADE;

--
-- Limiti per la tabella `dispositivo`
--
ALTER TABLE `dispositivo`
  ADD CONSTRAINT `dispositivo_ibfk_1` FOREIGN KEY (`IDUtente`) REFERENCES `utente` (`IDUtente`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Limiti per la tabella `misura`
--
ALTER TABLE `misura`
  ADD CONSTRAINT `misura_ibfk_1` FOREIGN KEY (`IDAllenamento`) REFERENCES `allenamento` (`IDAllenamento`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Limiti per la tabella `obiettivo`
--
ALTER TABLE `obiettivo`
  ADD CONSTRAINT `obiettivo_ibfk_1` FOREIGN KEY (`IDCategoria`) REFERENCES `categoriaObiettivo` (`IDCategoria`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Limiti per la tabella `utente`
--
ALTER TABLE `utente`
  ADD CONSTRAINT `utente_ibfk_1` FOREIGN KEY (`IDObiettivo`) REFERENCES `obiettivo` (`IDObiettivo`) ON DELETE SET NULL ON UPDATE SET NULL;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
