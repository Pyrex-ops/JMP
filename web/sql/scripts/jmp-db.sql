-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: mysql
-- Creato il: Apr 28, 2023 alle 19:45
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

CREATE TABLE `allenamento` (
  `IDAllenamento` int NOT NULL,
  `IDUtente` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dump dei dati per la tabella `allenamento`
--

INSERT INTO `allenamento` (`IDAllenamento`, `IDUtente`) VALUES
(1, 1);

-- --------------------------------------------------------

--
-- Struttura della tabella `dispositivo`
--

CREATE TABLE `dispositivo` (
  `IDDispositivo` int NOT NULL,
  `IDUtente` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dump dei dati per la tabella `dispositivo`
--

INSERT INTO `dispositivo` (`IDDispositivo`, `IDUtente`) VALUES
(1, 1);

-- --------------------------------------------------------

--
-- Struttura della tabella `misura`
--

CREATE TABLE `misura` (
  `IDMisura` int NOT NULL,
  `IDAllenamento` int NOT NULL,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `valore` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dump dei dati per la tabella `misura`
--

INSERT INTO `misura` (`IDMisura`, `IDAllenamento`, `timestamp`, `valore`) VALUES
(1, 1, '2023-04-28 19:25:34', 1),
(2, 1, '2023-04-28 19:30:20', 2),
(3, 1, '2023-04-28 19:30:22', 2),
(4, 1, '2023-04-28 19:30:23', 2),
(5, 1, '2023-04-28 19:30:24', 2);

-- --------------------------------------------------------

--
-- Struttura della tabella `provaClassifica`
--

CREATE TABLE `provaClassifica` (
  `id` int NOT NULL,
  `idutente` int NOT NULL,
  `frequency` int NOT NULL,
  `time` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dump dei dati per la tabella `provaClassifica`
--

INSERT INTO `provaClassifica` (`id`, `idutente`, `frequency`, `time`) VALUES
(1, 0, 10, 30),
(2, 1, 2, 6),
(3, 2, 15, 1),
(4, 3, 33, 99),
(5, 4, 12, 7),
(6, 5, 7, 12),
(7, 6, 48, 35),
(8, 7, 9, 36),
(9, 7, 48, 130),
(10, 0, 12, 33),
(11, 0, 12, 33),
(12, 0, 14, 68),
(13, 1, 22, 54),
(14, 1, 2, 99),
(15, 1, 15, 18),
(16, 2, 8, 24);

-- --------------------------------------------------------

--
-- Struttura della tabella `utente`
--

CREATE TABLE `utente` (
  `IDUtente` int NOT NULL,
  `username` varchar(30) NOT NULL,
  `passwordhash` varchar(60) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dump dei dati per la tabella `utente`
--

INSERT INTO `utente` (`IDUtente`, `username`, `passwordhash`) VALUES
(1, 'user', '$2y$10$0aoe.lyHAoWiQ3KPV4GhE.Md7LuODGQ9OayiUkIQBd47Q/X71Z76S'),
(2, 'user', '$2y$10$TCMqd4y2jtLJ4R9SH65T6.NDQTOlBCTe5Wja7Me3cK1NdjhRlLe1C'),
(3, 'user', '$2y$10$Ekn7f9fOe8F9.lWjF5bTe.tL1e1YRx0OreGiu2PC1nz7WDPZz0rXm'),
(4, 'user', '$2y$10$RNQa89i/xCeJ8oPxNzSoweTYgO8uHpu6ph0vS0L5gpZshdxcCsmJa');

--
-- Indici per le tabelle scaricate
--

--
-- Indici per le tabelle `allenamento`
--
ALTER TABLE `allenamento`
  ADD PRIMARY KEY (`IDAllenamento`);

--
-- Indici per le tabelle `dispositivo`
--
ALTER TABLE `dispositivo`
  ADD PRIMARY KEY (`IDDispositivo`);

--
-- Indici per le tabelle `misura`
--
ALTER TABLE `misura`
  ADD PRIMARY KEY (`IDMisura`);

--
-- Indici per le tabelle `provaClassifica`
--
ALTER TABLE `provaClassifica`
  ADD PRIMARY KEY (`id`);

--
-- Indici per le tabelle `utente`
--
ALTER TABLE `utente`
  ADD PRIMARY KEY (`IDUtente`);

--
-- AUTO_INCREMENT per le tabelle scaricate
--

--
-- AUTO_INCREMENT per la tabella `allenamento`
--
ALTER TABLE `allenamento`
  MODIFY `IDAllenamento` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT per la tabella `dispositivo`
--
ALTER TABLE `dispositivo`
  MODIFY `IDDispositivo` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT per la tabella `misura`
--
ALTER TABLE `misura`
  MODIFY `IDMisura` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT per la tabella `provaClassifica`
--
ALTER TABLE `provaClassifica`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=17;

--
-- AUTO_INCREMENT per la tabella `utente`
--
ALTER TABLE `utente`
  MODIFY `IDUtente` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
